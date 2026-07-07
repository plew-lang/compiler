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

leaky=0; clean=0; skipped=0
rm -f "$TMP"/leak_*.err
: > "$TMP/summary.txt"
for f in tests/run/*.pw; do
    name=$(basename "$f" .pw)
    [ -f "tests/run/$name.out" ] || continue
    ll="$TMP/l.ll"; bin="$TMP/l.bin"
    "$PLEWC" --asan "$f" > "$ll" 2>/dev/null || { skipped=$((skipped+1)); continue; }
    "$OPT" -passes=asan -S "$ll" -o "$ll.inst.ll" 2>/dev/null || { skipped=$((skipped+1)); continue; }
    extra_c=""; [ -f "tests/run/$name.c" ] && extra_c="tests/run/$name.c"
    "$CLANG" -fsanitize=address -w "$ll.inst.ll" "$RT" $extra_c $("$LC" --ldflags) -o "$bin" 2>/dev/null || { skipped=$((skipped+1)); continue; }
    infile="tests/run/$name.in"
    if [ -f "$infile" ]; then ASAN_OPTIONS=detect_leaks=1 "$bin" < "$infile" > /dev/null 2>"$TMP/l.err" || true
    else ASAN_OPTIONS=detect_leaks=1 "$bin" > /dev/null 2>"$TMP/l.err" || true; fi
    if grep -q "LeakSanitizer: detected memory leaks" "$TMP/l.err"; then
        leaky=$((leaky+1))
        total=$(grep "SUMMARY: AddressSanitizer:" "$TMP/l.err" | head -1 | sed 's/SUMMARY: AddressSanitizer: //')
        echo "LEAK $name: $total" >> "$TMP/summary.txt"
        cp "$TMP/l.err" "$TMP/leak_$name.err"
    else
        clean=$((clean+1))
    fi
done
echo "---"
cat "$TMP/summary.txt"
echo "---"
echo "leak survey: leaky=$leaky clean=$clean skipped=$skipped (reports in $TMP/leak_<name>.err)"
