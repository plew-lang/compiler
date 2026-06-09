#!/bin/sh
# LLVM-backend coverage + regression harness. For each tests/run/<name>.pw, run
# the LLVM backend (compiler/plewc-llvm) and compare its program's stdout to the
# same golden `.out` the C backend is held to. Programs using a feature the LLVM
# backend doesn't cover yet are REJECTED LOUDLY by the backend (acceptance
# soundness — no silent miscompile); those count as SKIP (unsupported), not
# failures. So this tracks how much of the suite the LLVM backend already runs
# correctly, and guards against regressions on that subset.
#
# Prereq: ./bootstrap.sh (-> compiler/plewc) and ./build-llvm.sh (-> plewc-llvm).
set -e
cd "$(dirname "$0")"

LC="${LLVM_CONFIG:-llvm-config}"
command -v "$LC" >/dev/null 2>&1 || {
    [ -x /opt/homebrew/opt/llvm/bin/llvm-config ] && LC=/opt/homebrew/opt/llvm/bin/llvm-config
}
PLEWC_LLVM=compiler/plewc-llvm
[ -x "$PLEWC_LLVM" ] || { echo "run ./build-llvm.sh first" >&2; exit 1; }

RT=/tmp/plew_llvm_rt.c
"$PLEWC_LLVM" --runtime > "$RT"

# Known gaps the LLVM backend doesn't model yet (tracked separately so they don't
# mask real regressions). Remove as features land. (Eager value-semantics CoW for
# arrays + struct-with-array now landed; let_infer needs a user Index subscript.)
KNOWN_GAP=" "

pass=0; skip=0; fail=0; gap=0
failed=""
for f in tests/run/*.pw; do
    name=$(basename "$f" .pw)
    out="tests/run/$name.out"
    [ -f "$out" ] || continue
    case "$KNOWN_GAP" in *" $name "*) gap=$((gap + 1)); continue;; esac
    ll="/tmp/llt_$name.ll"
    if ! "$PLEWC_LLVM" "$f" > "$ll" 2>/tmp/llt_err; then
        skip=$((skip + 1)); continue
    fi
    bin="/tmp/llt_$name"
    # optional companion C source (tests/run/<name>.c): linked alongside, for
    # extern(c) FFI tests that provide foreign symbols without a system library.
    extra_c=""
    [ -f "tests/run/$name.c" ] && extra_c="tests/run/$name.c"
    if ! clang -w "$ll" "$RT" $extra_c $("$LC" --ldflags) -o "$bin" 2>/dev/null; then
        fail=$((fail + 1)); failed="$failed $name(link)"; continue
    fi
    infile="tests/run/$name.in"
    if [ -f "$infile" ]; then got=$("$bin" < "$infile" 2>/dev/null) || true
    else got=$("$bin" 2>/dev/null) || true; fi
    if [ "$got" = "$(cat "$out")" ]; then
        pass=$((pass + 1))
    else
        fail=$((fail + 1)); failed="$failed $name"
    fi
done

# --- panic/ : valid code that compiles and links but must ABORT at runtime with
#     the expected panic text (overflow / div-by-zero / OOB / assert). The LLVM
#     backend's checked-arithmetic floor (plew_<w><Op>) is held to the same loud
#     behaviour as the C backend. A program the backend can't lower yet is a SKIP. ---
ppass=0
for pw in tests/panic/*.pw; do
    [ -f "$pw" ] || continue
    name=$(basename "$pw" .pw)
    want=$(cat "tests/panic/$name.panic")
    ll="/tmp/llt_panic_$name.ll"; bin="/tmp/llt_panic_$name"
    if ! "$PLEWC_LLVM" "$pw" > "$ll" 2>/tmp/llt_err; then
        skip=$((skip + 1)); continue
    fi
    if ! clang -w "$ll" "$RT" $("$LC" --ldflags) -o "$bin" 2>/dev/null; then
        fail=$((fail + 1)); failed="$failed panic/$name(link)"; continue
    fi
    code=0
    "$bin" >/dev/null 2>/tmp/llt_perr || code=$?
    if [ "$code" -ne 0 ] && grep -qF "$want" /tmp/llt_perr; then
        ppass=$((ppass + 1))
    else
        fail=$((fail + 1)); failed="$failed panic/$name"
    fi
done

echo "----"
echo "llvm-backend: pass=$pass  panic=$ppass  skip(unsupported)=$skip  cow-gap=$gap  fail=$fail"
[ -n "$failed" ] && echo "failing:$failed"
[ "$fail" -eq 0 ]
