#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-for-destructure.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
for name in for_struct_destructure for_struct_destructure_arc for_record_destructure for_record_destructure_arc iter_enumerate iter_enumerate_heap syntax_lower_record_for mid_for_destructure_exit; do
    if ! "$PLEWC" --require-mid --emit-mid-coverage "tests/run/$name.pw" >"$directory/input.ll" 2>"$directory/coverage"; then
        cat "$directory/coverage" >&2
        exit 1
    fi
    echo "PASS $name(mid for destructure)" >&2
done
