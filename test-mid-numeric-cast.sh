#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-numeric-cast.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM

source=tests/run/mid_numeric_cast.pw
echo "check $source(frontend-resolved primitive cast)" >&2
"$PLEWC" --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"
if grep -E 'name=main category=' "$directory/coverage" >&2; then
    echo "FAIL $source(legacy primitive cast)" >&2
    exit 1
fi
echo "PASS $source(mid)" >&2
