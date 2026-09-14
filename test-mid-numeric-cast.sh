#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-numeric-cast.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM

for name in cast float_cast mid_numeric_cast mid_cast_literal_context newtype_basics i64_newtype_self newtype_conformance_inherit mid_newtype_literal_context; do
    source="tests/run/$name.pw"
    echo "check $source(frontend-resolved cast)" >&2
    if ! "$PLEWC" --require-mid "$source" >"$directory/input.ll" 2>"$directory/coverage"; then
        cat "$directory/coverage" >&2
        exit 1
    fi
    echo "PASS $source(mid)" >&2
done
