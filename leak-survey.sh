#!/bin/sh
# Leak SURVEY over the run corpus: compile each tests/run program with --asan,
# instrument, run with detect_leaks=1, and summarize every LeakSanitizer report.
# A triage tool for rooting out generated-code leaks (the permanent pass/fail
# gate lives in asan-gate.sh level D once the corpus is clean).
set -e
cd "$(dirname "$0")"

LLVM="${LLVM_PREFIX:-/opt/homebrew/opt/llvm}"
OPT="$LLVM/bin/opt"
CLANG="$LLVM/bin/clang"
LC="$LLVM/bin/llvm-config"
PLEWC=./plewc

TMP=/tmp/plew_leaks
mkdir -p "$TMP"
RT="$TMP/rt.c"
"$PLEWC" --runtime > "$RT"

rm -f "$TMP"/leak_*.err
JOBS="${PLEW_TEST_JOBS:-$(sysctl -n hw.ncpu 2>/dev/null || nproc 2>/dev/null || echo 4)}"
PLEW_LD="$("$LC" --ldflags)"
export TMP RT OPT CLANG PLEW_LD

# One test per worker; each prints one LEAK/CLEAN/SKIP line, aggregated (and
# sorted back to glob order) after the fan-out.
results=$(printf '%s\n' tests/run/*.pw | xargs -P "$JOBS" -n 1 sh -c '
    f="$1"; name=$(basename "$f" .pw)
    [ -f "tests/run/$name.out" ] || exit 0
    ll="$TMP/l_$name.ll"; bin="$TMP/l_$name.bin"; err="$TMP/l_$name.err"
    ./plewc --asan "$f" > "$ll" 2>/dev/null || { echo "SKIP $name"; exit 0; }
    "$OPT" -passes=asan -S "$ll" -o "$ll.inst.ll" 2>/dev/null || { echo "SKIP $name"; exit 0; }
    extra_c=""; [ -f "tests/run/$name.c" ] && extra_c="tests/run/$name.c"
    "$CLANG" -fsanitize=address -w "$ll.inst.ll" "$RT" $extra_c $PLEW_LD -o "$bin" 2>/dev/null || { echo "SKIP $name"; exit 0; }
    infile="tests/run/$name.in"
    if [ -f "$infile" ]; then ASAN_OPTIONS=detect_leaks=1 "$bin" < "$infile" > /dev/null 2>"$err" || true
    else ASAN_OPTIONS=detect_leaks=1 "$bin" > /dev/null 2>"$err" || true; fi
    if grep -q "LeakSanitizer: detected memory leaks" "$err"; then
        total=$(grep "SUMMARY: AddressSanitizer:" "$err" | head -1 | sed "s/SUMMARY: AddressSanitizer: //")
        echo "LEAK $name: $total"
        cp "$err" "$TMP/leak_$name.err"
    else
        echo "CLEAN $name"
    fi
' sh)
leaky=$(printf '%s' "$results" | grep -c '^LEAK' || true)
clean=$(printf '%s' "$results" | grep -c '^CLEAN' || true)
skipped=$(printf '%s' "$results" | grep -c '^SKIP' || true)
printf '%s\n' "$results" | grep '^LEAK' | sort > "$TMP/summary.txt" || true
echo "---"
cat "$TMP/summary.txt"
echo "---"
echo "leak survey: leaky=$leaky clean=$clean skipped=$skipped (reports in $TMP/leak_<name>.err)"
