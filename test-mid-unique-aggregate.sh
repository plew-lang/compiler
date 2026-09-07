#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-unique-aggregate.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM

source=tests/run/unique_move_into_field.pw
echo "check $source(unique aggregate move transfer)" >&2
"$PLEWC" --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"
if grep -E 'name=main category=' "$directory/coverage" >&2; then
    echo "FAIL $source(legacy unique aggregate)" >&2
    exit 1
fi
echo "PASS $source(mid)" >&2
