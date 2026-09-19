#!/bin/sh
set -eu
cd "$(dirname "$0")/../.."
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-record.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
for name in record_generic_struct_field mid_record_field_context record_basics record_in_optional record_generic_method_arg record_layout_collection record_nested_depth2; do
    if ! "$PLEWC" --require-mid "tests/run/$name.pw" >"$directory/input.ll" 2>"$directory/coverage"; then
        cat "$directory/coverage" >&2
        exit 1
    fi
    echo "PASS $name(mid record construction)" >&2
done
