#!/bin/sh
# Internal A/B stage, supervised by asan-schedule.py.
set -eu
cd "$(dirname "$0")/../.."
JOBS="${PLEW_TEST_JOBS:?}"
progress_results() {
    phase=$1
    completed=0
    while IFS= read -r line; do
        completed=$((completed + 1))
        printf '%s\n' "$line"
        printf 'asan: %s completed=%s %s\n' "$phase" "$completed" "$line" >&2
    done
}

fail=0
echo "== A. self-compile under ASan =="
if ! python3 ./scripts/support/trace-command.py "$TMP/self.err" -- ./plewc_asan --trace-phases src/_.pw > /dev/null; then
    if grep -q "ERROR: AddressSanitizer" "$TMP/self.err"; then
        echo "  FAIL self-compile:"; grep -A3 "ERROR: AddressSanitizer" "$TMP/self.err" | head -8
    else
        # a non-ASan failure (crash, reject) must not read as clean.
        echo "  FAIL self-compile (non-ASan):"; head -3 "$TMP/self.err" | sed 's/^/  /'
    fi
    fail=1
fi
[ "$fail" = 0 ] && echo "  clean"

echo "== B. compile corpus under ASan =="
b_results=$(ls tests/fixtures/run/*.pw tests/fixtures/reject/*.pw tests/fixtures/panic/*.pw | xargs -P "$JOBS" -n 1 sh -c '
    f="$1"; err="$TMP/b_$(printf "%s" "$f" | tr "/" "_").err"
    compile_exit=0
    python3 ./scripts/support/trace-command.py "$err" -- ./plewc_asan --trace-phases "$f" > /dev/null || compile_exit=$?
    expected_exit=0
    case "$f" in tests/fixtures/reject/*) expected_exit=1 ;; esac
    if grep -q "ERROR: AddressSanitizer" "$err"; then
        echo "FAIL compiling $f: $(grep "ERROR: AddressSanitizer" "$err" | head -1)"
    elif [ "$compile_exit" -ne "$expected_exit" ]; then
        echo "FAIL compiling $f: expected exit=$expected_exit, got=$compile_exit"
    elif [ "$expected_exit" -eq 1 ] && ! grep -q "^plewc: error:" "$err"; then
        echo "FAIL compiling $f: missing rejection diagnostic"
    else
        echo "RAN $f"
    fi
' sh | progress_results B)
bfail=$(printf '%s' "$b_results" | grep -c '^FAIL' || true)
bn=$(printf '%s\n' "$b_results" | grep -c '^RAN' || true)
bexpected=$(printf '%s\n' tests/fixtures/run/*.pw tests/fixtures/reject/*.pw tests/fixtures/panic/*.pw | wc -l | tr -d ' ')
if [ "$bfail" = 0 ] && [ "$bn" = "$bexpected" ]; then
    echo "  clean ($bn files)"
else
    echo "  completed $bn/$bexpected successful compilations"
    printf '%s\n' "$b_results" | sed 's/^/  /'
    fail=1
fi

exit "$fail"
