#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-newtype-fields.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
for source in tests/run/newtype_heap_struct_arc.pw tests/run/newtype_struct_inherit.pw tests/run/mid_newtype_field_owner.pw; do
if ! "$PLEWC" --require-mid --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"; then
    cat "$directory/coverage" >&2
    echo "FAIL $source(mid newtype fields)" >&2
    exit 1
fi
echo "PASS $source(mid newtype fields)" >&2
done
