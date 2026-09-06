#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-core-numeric-conversion.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
for source in tests/run/mid_core_numeric_conversion_intrinsics.pw tests/run/mid_core_numeric_conversion_same_name.pw; do
    echo "check $source(Core numeric conversion runtime intrinsic declaration transport)" >&2
    "$PLEWC" --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"
    if grep -E 'name=(main|truncU8) category=' "$directory/coverage" >&2; then
        echo "FAIL $source(legacy)" >&2
        exit 1
    fi
    echo "PASS $source(mid)" >&2
done
