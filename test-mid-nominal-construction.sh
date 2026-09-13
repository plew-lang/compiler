#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-nominal-construction.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
source=tests/run/mid_nominal_constructor_identity.pw
if ! "$PLEWC" --require-mid --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"; then
    cat "$directory/coverage" >&2
    echo "FAIL $source(mid nominal construction)" >&2
    exit 1
fi
echo "PASS $source(mid nominal construction)" >&2
