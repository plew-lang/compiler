#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-while-true-return.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM

source=tests/run/mid_while_true_return.pw
echo "check $source(unreachable while-true exit)" >&2
"$PLEWC" --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"
if grep -E 'name=select category=' "$directory/coverage" >&2; then
    echo "FAIL $source(legacy while-true exit)" >&2
    exit 1
fi
echo "PASS $source(mid)" >&2
