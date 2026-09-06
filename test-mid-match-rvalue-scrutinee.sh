#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-match-rvalue-scrutinee.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM

source=tests/run/mid_match_rvalue_scrutinee.pw
echo "check $source(rvalue match scrutinee)" >&2
"$PLEWC" --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"
if grep -E 'name=describe category=build:match' "$directory/coverage" >&2; then
    echo "FAIL $source(legacy rvalue match)" >&2
    exit 1
fi
echo "PASS $source(mid)" >&2
