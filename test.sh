#!/bin/sh
# Language test suite for the self-hosted Plew compiler. Drives the `plewc`
# binary (LLVM backend) from the outside: plewc x.pw > x.ll, clang x.ll +
# runtime, run, compare stdout to the golden .out. Covers run/ (stdout),
# panic/ (must abort with the expected text), reject/ (front-end must reject —
# acceptance soundness, incl. the shared verifyProgram pass), and part/
# (multi-file modules). Metaprogramming (gen/) is in ./test-gen.sh.
#
# Prereq: ./bootstrap.sh  (-> compiler/plewc).
set -e
cd "$(dirname "$0")"

LC="${LLVM_CONFIG:-llvm-config}"
command -v "$LC" >/dev/null 2>&1 || {
    [ -x /opt/homebrew/opt/llvm/bin/llvm-config ] && LC=/opt/homebrew/opt/llvm/bin/llvm-config
}
PLEWC=compiler/plewc
[ -x "$PLEWC" ] || { echo "run ./bootstrap.sh first" >&2; exit 1; }

RT=/tmp/plew_rt.c
"$PLEWC" --runtime > "$RT"

pass=0; skip=0; fail=0
failed=""
for f in tests/run/*.pw; do
    name=$(basename "$f" .pw)
    out="tests/run/$name.out"
    [ -f "$out" ] || continue
    ll="/tmp/t_$name.ll"
    if ! "$PLEWC" "$f" > "$ll" 2>/tmp/t_err; then
        fail=$((fail + 1)); failed="$failed $name(reject)"; continue
    fi
    bin="/tmp/t_$name"
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
#     the expected panic text (overflow / div-by-zero / OOB / assert). The
#     checked-arithmetic floor (plew_<w><Op>) is held to loud behaviour. ---
ppass=0
for pw in tests/panic/*.pw; do
    [ -f "$pw" ] || continue
    name=$(basename "$pw" .pw)
    want=$(cat "tests/panic/$name.panic")
    ll="/tmp/t_panic_$name.ll"; bin="/tmp/t_panic_$name"
    if ! "$PLEWC" "$pw" > "$ll" 2>/tmp/t_err; then
        fail=$((fail + 1)); failed="$failed panic/$name(reject)"; continue
    fi
    if ! clang -w "$ll" "$RT" $("$LC" --ldflags) -o "$bin" 2>/dev/null; then
        fail=$((fail + 1)); failed="$failed panic/$name(link)"; continue
    fi
    code=0
    "$bin" >/dev/null 2>/tmp/t_perr || code=$?
    if [ "$code" -ne 0 ] && grep -qF "$want" /tmp/t_perr; then
        ppass=$((ppass + 1))
    else
        fail=$((fail + 1)); failed="$failed panic/$name"
    fi
done

# --- reject/ : spec-invalid code the FRONT-END must reject. The shared frontend
#     (incl. the backend-independent acceptance pass verifyProgram) rejects these. ---
rpass=0
for pw in tests/reject/*.pw; do
    [ -f "$pw" ] || continue
    name=$(basename "$pw" .pw)
    if "$PLEWC" "$pw" > /dev/null 2>/dev/null; then
        fail=$((fail + 1)); failed="$failed reject/$name(accepted)"
    else
        rpass=$((rpass + 1))
    fi
done

# --- part/ : multi-file modules (each subdir's Main.pw stitches siblings via
#     `part`). Compile the root, run, compare to Main.out. ---
qpass=0
for main in tests/part/*/Main.pw tests/part/Main.pw; do
    [ -f "$main" ] || continue
    dir=$(dirname "$main")
    name=$(basename "$dir")
    ll="/tmp/t_part_$name.ll"; bin="/tmp/t_part_$name"
    if ! "$PLEWC" "$main" > "$ll" 2>/tmp/t_err; then
        fail=$((fail + 1)); failed="$failed part/$name(reject)"; continue
    fi
    if ! clang -w "$ll" "$RT" $("$LC" --ldflags) -o "$bin" 2>/dev/null; then
        fail=$((fail + 1)); failed="$failed part/$name(link)"; continue
    fi
    got=$("$bin" 2>/dev/null) || true
    if [ "$got" = "$(cat "$dir/Main.out")" ]; then
        qpass=$((qpass + 1))
    else
        fail=$((fail + 1)); failed="$failed part/$name"
    fi
done

# --- partreject/ : multi-file modules whose Main.pw the FRONT-END must reject —
#     cross-module rules that need real loaded sibling modules (e.g. a circular
#     import, which a single file cannot express). ---
prpass=0
for main in tests/partreject/*/Main.pw; do
    [ -f "$main" ] || continue
    dir=$(dirname "$main")
    name=$(basename "$dir")
    if "$PLEWC" "$main" > /dev/null 2>/tmp/t_err; then
        fail=$((fail + 1)); failed="$failed partreject/$name(accepted)"
    else
        prpass=$((prpass + 1))
    fi
done

echo "----"
echo "plewc: run=$pass  panic=$ppass  reject=$rpass  part=$qpass  partreject=$prpass  skip=$skip  fail=$fail"
[ -n "$failed" ] && echo "failing:$failed"
[ "$fail" -eq 0 ]
