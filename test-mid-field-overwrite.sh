#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-field-overwrite.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM

source=tests/run/mid_field_overwrite.pw
echo "check $source(physical field overwrite)" >&2
"$PLEWC" --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"
if grep -E 'name=(replaceField|replaceOwnedField|replaceNestedOwnedField|replaceCallOwnedField|reset|replaceReceiverField) category=' "$directory/coverage" >&2; then
    echo "FAIL $source(legacy field overwrite)" >&2
    exit 1
fi
echo "PASS $source(mid)" >&2
