#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-borrow-constant-receiver.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM

source=tests/run/mid_borrow_constant_receiver.pw
echo "check $source(read-only constant receiver)" >&2
"$PLEWC" --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"
if grep -E 'name=literalByteCount category=' "$directory/coverage" >&2; then
    echo "FAIL $source(legacy literal receiver)" >&2
    exit 1
fi
echo "PASS $source(mid)" >&2
