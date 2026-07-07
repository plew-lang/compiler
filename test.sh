#!/bin/sh
# Language test suite for the self-hosted Plew compiler. Drives the `plewc`
# binary (LLVM backend) from the outside: plewc x.pw > x.ll, clang x.ll +
# runtime, run, compare stdout to the golden .out. Covers run/ (stdout),
# panic/ (must abort with the expected text), reject/ (front-end must reject —
# acceptance soundness, incl. the shared verifyProgram pass), and part/
# (multi-file modules). Metaprogramming (gen/) is in ./test-gen.sh.
#
# Tests run PLEW_TEST_JOBS-wide (default: all cores) via xargs -P: each worker
# is one test end-to-end (compile + link + run + compare) printing exactly one
# PASS/FAIL line, aggregated after the fan-out. Observable output (counters,
# failing list, exit code) is identical to the old serial runner.
#
# Prereq: ./bootstrap.sh  (-> plewc).
set -e
cd "$(dirname "$0")"

LC="${LLVM_CONFIG:-llvm-config}"
command -v "$LC" >/dev/null 2>&1 || {
    [ -x /opt/homebrew/opt/llvm/bin/llvm-config ] && LC=/opt/homebrew/opt/llvm/bin/llvm-config
}
PLEWC=plewc
[ -x "$PLEWC" ] || { echo "run ./bootstrap.sh first" >&2; exit 1; }

RT=/tmp/plew_rt.c
"$PLEWC" --runtime > "$RT"

JOBS="${PLEW_TEST_JOBS:-$(sysctl -n hw.ncpu 2>/dev/null || nproc 2>/dev/null || echo 4)}"
PLEW_RT="$RT"
PLEW_LD="$("$LC" --ldflags)"
export PLEW_RT PLEW_LD

# --- run/ : compile, link, run, compare stdout to the golden .out ---
run_results=$(printf '%s\n' tests/run/*.pw | xargs -P "$JOBS" -n 1 sh -c '
    f="$1"; name=$(basename "$f" .pw); out="tests/run/$name.out"
    [ -f "$out" ] || exit 0
    ll="/tmp/t_$name.ll"; bin="/tmp/t_$name"
    if ! ./plewc "$f" > "$ll" 2>/dev/null; then echo "FAIL $name(reject)"; exit 0; fi
    extra_c=""
    [ -f "tests/run/$name.c" ] && extra_c="tests/run/$name.c"
    if ! clang -w "$ll" "$PLEW_RT" $extra_c $PLEW_LD -o "$bin" 2>/dev/null; then echo "FAIL $name(link)"; exit 0; fi
    infile="tests/run/$name.in"
    if [ -f "$infile" ]; then got=$("$bin" < "$infile" 2>/dev/null) || true
    else got=$("$bin" 2>/dev/null) || true; fi
    if [ "$got" = "$(cat "$out")" ]; then echo "PASS $name"; else echo "FAIL $name"; fi
' sh)
pass=$(printf '%s\n' "$run_results" | grep -c '^PASS' || true)
fail=0; failed=""
for n in $(printf '%s\n' "$run_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done
skip=0

# --- panic/ : valid code that compiles and links but must ABORT at runtime with
#     the expected panic text (overflow / div-by-zero / OOB / assert). The
#     checked-arithmetic floor (plew_<w><Op>) is held to loud behaviour. ---
panic_results=$(printf '%s\n' tests/panic/*.pw | xargs -P "$JOBS" -n 1 sh -c '
    pw="$1"; [ -f "$pw" ] || exit 0
    name=$(basename "$pw" .pw)
    want=$(cat "tests/panic/$name.panic")
    ll="/tmp/t_panic_$name.ll"; bin="/tmp/t_panic_$name"; perr="/tmp/t_panic_$name.err"
    if ! ./plewc "$pw" > "$ll" 2>/dev/null; then echo "FAIL panic/$name(reject)"; exit 0; fi
    if ! clang -w "$ll" "$PLEW_RT" $PLEW_LD -o "$bin" 2>/dev/null; then echo "FAIL panic/$name(link)"; exit 0; fi
    code=0
    "$bin" >/dev/null 2>"$perr" || code=$?
    if [ "$code" -ne 0 ] && grep -qF "$want" "$perr"; then echo "PASS panic/$name"; else echo "FAIL panic/$name"; fi
' sh)
ppass=$(printf '%s\n' "$panic_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$panic_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

# --- reject/ : spec-invalid code the FRONT-END must reject. The shared frontend
#     (incl. the backend-independent acceptance pass verifyProgram) rejects these. ---
reject_results=$(printf '%s\n' tests/reject/*.pw | xargs -P "$JOBS" -n 1 sh -c '
    pw="$1"; [ -f "$pw" ] || exit 0
    name=$(basename "$pw" .pw)
    if ./plewc "$pw" > /dev/null 2>/dev/null; then echo "FAIL reject/$name(accepted)"; else echo "PASS reject/$name"; fi
' sh)
rpass=$(printf '%s\n' "$reject_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$reject_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

# --- part/ : multi-file modules (each subdir's Main.pw stitches siblings via
#     `part`). Compile the root, run, compare to Main.out. ---
part_results=$(printf '%s\n' tests/part/*/Main.pw tests/part/Main.pw | xargs -P "$JOBS" -n 1 sh -c '
    main="$1"; [ -f "$main" ] || exit 0
    dir=$(dirname "$main")
    name=$(basename "$dir")
    ll="/tmp/t_part_$name.ll"; bin="/tmp/t_part_$name"
    if ! ./plewc "$main" > "$ll" 2>/dev/null; then echo "FAIL part/$name(reject)"; exit 0; fi
    if ! clang -w "$ll" "$PLEW_RT" $PLEW_LD -o "$bin" 2>/dev/null; then echo "FAIL part/$name(link)"; exit 0; fi
    got=$("$bin" 2>/dev/null) || true
    if [ "$got" = "$(cat "$dir/Main.out")" ]; then echo "PASS part/$name"; else echo "FAIL part/$name"; fi
' sh)
qpass=$(printf '%s\n' "$part_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$part_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

# --- partreject/ : multi-file modules whose Main.pw the FRONT-END must reject —
#     cross-module rules that need real loaded sibling modules (e.g. a circular
#     import, which a single file cannot express). ---
pr_results=$(printf '%s\n' tests/partreject/*/Main.pw | xargs -P "$JOBS" -n 1 sh -c '
    main="$1"; [ -f "$main" ] || exit 0
    name=$(basename "$(dirname "$main")")
    if ./plewc "$main" > /dev/null 2>/dev/null; then echo "FAIL partreject/$name(accepted)"; else echo "PASS partreject/$name"; fi
' sh)
prpass=$(printf '%s\n' "$pr_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$pr_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

echo "----"
echo "plewc: run=$pass  panic=$ppass  reject=$rpass  part=$qpass  partreject=$prpass  skip=$skip  fail=$fail"
[ -n "$failed" ] && echo "failing:$failed"
[ "$fail" -eq 0 ]
