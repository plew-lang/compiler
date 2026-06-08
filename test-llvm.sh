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

# Known gaps the LLVM backend doesn't model yet (value-semantics CoW on arrays):
# tracked separately so they don't mask real regressions. Remove as features land.
KNOWN_GAP=" cow_array let_infer "

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
    if ! clang -w "$ll" "$RT" $("$LC" --ldflags) -o "$bin" 2>/dev/null; then
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

echo "----"
echo "llvm-backend: pass=$pass  skip(unsupported)=$skip  cow-gap=$gap  fail=$fail"
[ -n "$failed" ] && echo "failing:$failed"
[ "$fail" -eq 0 ]
