#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-array-over-buffer.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM

source=tests/run/mid_array_over_buffer_factory.pw
echo "check $source(generic Array.overBuffer aggregate)" >&2
"$PLEWC" --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"
if grep -E 'name=(main|bytes|overBuffer) category=' "$directory/coverage" >&2; then
    echo "FAIL $source(legacy)" >&2
    exit 1
fi
echo "PASS $source(mid)" >&2
