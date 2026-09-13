#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-struct-pattern.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
for name in struct_pattern mid_struct_pattern_lifetime mid_struct_pattern_reassignment; do
    if ! "$PLEWC" --require-mid "tests/run/$name.pw" >"$directory/input.ll" 2>"$directory/coverage"; then
        cat "$directory/coverage" >&2
        exit 1
    fi
    echo "PASS $name(mid struct pattern)" >&2
done
