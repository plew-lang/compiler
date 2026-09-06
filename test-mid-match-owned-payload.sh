#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-match-owned-payload.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM

source=tests/run/mid_match_owned_payload.pw
echo "check $source(borrowed ARC match payload)" >&2
"$PLEWC" --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"
if grep -E 'name=describe category=build:match' "$directory/coverage" >&2; then
    echo "FAIL $source(legacy ARC match payload)" >&2
    exit 1
fi
echo "PASS $source(mid)" >&2
