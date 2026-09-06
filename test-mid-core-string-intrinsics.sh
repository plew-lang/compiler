#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-core-string.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
for source in tests/run/mid_core_string_intrinsic_calls.pw tests/run/mid_core_string_intrinsic_same_name.pw; do
    echo "check $source(Core string runtime intrinsic declaration transport)" >&2
    "$PLEWC" --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"
    if grep -E 'name=(fromBytes|fromFloat|floatToString|main) category=' "$directory/coverage" >&2; then
        echo "FAIL $source(legacy)" >&2
        exit 1
    fi
    if [ "$source" = tests/run/mid_core_string_intrinsic_same_name.pw ] && grep -q 'plew_f64_to_str' "$directory/input.ll"; then
        echo "FAIL $source(raw-name-dispatch)" >&2
        exit 1
    fi
    echo "PASS $source(mid)" >&2
done
