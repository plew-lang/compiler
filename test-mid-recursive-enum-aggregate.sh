#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-recursive-enum-aggregate.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM

source=tests/run/rec_list.pw
echo "check $source(boxed recursive enum aggregate)" >&2
"$PLEWC" --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"
if grep -E 'name=(main|sum|length) category=' "$directory/coverage" >&2; then
    echo "FAIL $source(boxed recursive enum escaped Mid)" >&2
    exit 1
fi
echo "PASS $source(mid)" >&2
