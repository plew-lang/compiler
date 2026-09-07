#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-value-match.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM

source=tests/run/mid_value_match_cfg_lowering.pw
echo "check $source(value match CFG)" >&2
"$PLEWC" --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"
if grep -E 'name=choose category=' "$directory/coverage" >&2; then
    echo "FAIL $source(legacy value match)" >&2
    exit 1
fi
echo "PASS $source(mid)" >&2
