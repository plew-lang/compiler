#!/bin/sh
# Canonical AddressSanitizer gate for the self-hosted Plew compiler.
#
# Why a bespoke gate (not just `clang -fsanitize=address`): plewc emits LLVM IR
# textually, and `clang -fsanitize=address` on a `.ll` input instruments NOTHING
# — the asan pass only touches functions carrying the `sanitize_address`
# attribute, which a C frontend adds but a raw `.ll` lacks. The old gate linked
# the bare `.ll` directly, so only the free/double-free *interceptor* layer was
# ever exercised; raw load/store use-after-free sailed through undetected.
#
# The fix: `plewc --asan` stamps the host target triple and marks every DEFINED
# function `sanitize_address`, so a downstream `opt -passes=asan` genuinely
# instruments every load/store. This gate wires that pipeline at three levels:
#
#   A. self-compile — an instrumented `plewc_asan` compiles src/_.pw. The
#      richest single exercise of the compiler's own ARC/CoW memory management.
#   B. compile corpus — `plewc_asan` compiles every test .pw (diverse inputs
#      through the compiler; catches UAF/overflow in the compiler itself).
#   C. run corpus — every tests/run program is compiled WITH --asan, linked, and
#      run; catches UAF in GENERATED code (value ARC, the collections floor).
#
# Deterministic UAF slips through both the fixpoint check and ./test.sh (the
# stale bytes usually still decode correctly), so this ASan gate is the only
# reliable regression net for the memory-management floor. Run it at milestones
# (after ./bootstrap.sh + ./test.sh are green), not on every edit — it builds an
# instrumented compiler and re-links hundreds of programs.
#
# Requires homebrew LLVM (Apple clang rejects the asan ABI v8 the pass emits).
set -e
cd "$(dirname "$0")"

LLVM="${LLVM_PREFIX:-/opt/homebrew/opt/llvm}"
OPT="$LLVM/bin/opt"
CLANG="$LLVM/bin/clang"
LC="$LLVM/bin/llvm-config"
LIB="$LLVM/lib/libLLVM.dylib"
for tool in "$OPT" "$CLANG" "$LC"; do
    [ -x "$tool" ] || { echo "asan-gate: missing $tool (set LLVM_PREFIX)" >&2; exit 1; }
done
PLEWC=./plewc
[ -x "$PLEWC" ] || { echo "asan-gate: run ./bootstrap.sh first" >&2; exit 1; }

TMP=/tmp/plew_asan
mkdir -p "$TMP"
RT="$TMP/rt.c"
"$PLEWC" --runtime > "$RT"
# No leak detection: plewc is a batch compiler with an intentionally un-freed
# arena; abort loudly on any real memory error so the gate fails fast.
export ASAN_OPTIONS=detect_leaks=0:abort_on_error=0

# Levels B/C fan out one test per worker (xargs -P); workers print one status
# line each, aggregated after the barrier. Exported for the worker shells:
JOBS="${PLEW_TEST_JOBS:-$(sysctl -n hw.ncpu 2>/dev/null || nproc 2>/dev/null || echo 4)}"
PLEW_LD="$("$LC" --ldflags)"
export TMP RT OPT CLANG PLEW_LD

fail=0

# Instrumentation note: the instrumented file must keep a .ll extension — clang
# infers input language from it (a .inst suffix would be handed to the linker as
# an object → error).

echo "== building instrumented plewc_asan =="
"$PLEWC" --asan src/_.pw > "$TMP/pc.ll"
"$OPT" -passes=asan -S "$TMP/pc.ll" -o "$TMP/pc.inst.ll" 2>/dev/null
# std/prelude resolution is relative to the compiler binary's directory, so the
# instrumented compiler must live in compiler/ (removed on exit).
"$CLANG" -fsanitize=address -w "$TMP/pc.inst.ll" "$RT" "$LIB" -o ./plewc_asan
trap 'rm -f ./plewc_asan' EXIT

echo "== A. self-compile under ASan =="
if ! ./plewc_asan src/_.pw > /dev/null 2>"$TMP/self.err"; then
    if grep -q "ERROR: AddressSanitizer" "$TMP/self.err"; then
        echo "  FAIL self-compile:"; grep -A3 "ERROR: AddressSanitizer" "$TMP/self.err" | head -8
        fail=1
    fi
fi
[ "$fail" = 0 ] && echo "  clean"

echo "== B. compile corpus under ASan =="
b_results=$(ls tests/run/*.pw tests/reject/*.pw tests/panic/*.pw | xargs -P "$JOBS" -n 1 sh -c '
    f="$1"; err="$TMP/b_$(printf "%s" "$f" | tr "/" "_").err"
    ./plewc_asan "$f" > /dev/null 2>"$err" || true
    if grep -q "ERROR: AddressSanitizer" "$err"; then
        echo "FAIL compiling $f: $(grep "ERROR: AddressSanitizer" "$err" | head -1)"
    fi
' sh)
bfail=$(printf '%s' "$b_results" | grep -c '^FAIL' || true)
if [ "$bfail" = 0 ]; then
    echo "  clean ($(ls tests/run/*.pw tests/reject/*.pw tests/panic/*.pw | wc -l | tr -d ' ') files)"
else
    printf '%s\n' "$b_results" | sed 's/^/  /'
    fail=1
fi

echo "== C. run corpus under ASan =="
c_results=$(printf '%s\n' tests/run/*.pw | xargs -P "$JOBS" -n 1 sh -c '
    f="$1"; name=$(basename "$f" .pw)
    [ -f "tests/run/$name.out" ] || exit 0
    ll="$TMP/c_$name.ll"; bin="$TMP/c_$name.bin"; err="$TMP/c_$name.err"
    ./plewc --asan "$f" > "$ll" 2>/dev/null || exit 0
    extra_c=""; [ -f "tests/run/$name.c" ] && extra_c="tests/run/$name.c"
    "$OPT" -passes=asan -S "$ll" -o "$ll.inst.ll" 2>/dev/null || exit 0
    "$CLANG" -fsanitize=address -w "$ll.inst.ll" "$RT" $extra_c $PLEW_LD -o "$bin" 2>/dev/null || exit 0
    infile="tests/run/$name.in"
    if [ -f "$infile" ]; then "$bin" < "$infile" > /dev/null 2>"$err" || true
    else "$bin" > /dev/null 2>"$err" || true; fi
    if grep -q "ERROR: AddressSanitizer" "$err"; then
        echo "FAIL running $name: $(grep "ERROR: AddressSanitizer" "$err" | head -1)"
    else
        echo "RAN $name"
    fi
' sh)
cn=$(printf '%s' "$c_results" | grep -c '^RAN' || true)
cfail=$(printf '%s' "$c_results" | grep -c '^FAIL' || true)
if [ "$cfail" = 0 ]; then
    echo "  clean ($cn programs)"
else
    printf '%s\n' "$c_results" | grep '^FAIL' | sed 's/^/  /'
    fail=1
fi

echo "---"
if [ "$fail" = 0 ]; then echo "ASan gate: PASS (all levels clean)"; else echo "ASan gate: FAIL"; fi
exit $fail
