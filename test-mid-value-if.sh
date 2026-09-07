#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-value-if.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM

echo "check tests/run/mid_value_if_cfg_lowering.pw(value if CFG)" >&2
"$PLEWC" --emit-mid-coverage tests/run/mid_value_if_cfg_lowering.pw >"$directory/input.ll" 2>"$directory/coverage"
if grep -E 'name=(choose|throughCall|throughAggregate|allDiverge) category=' "$directory/coverage" >&2; then
    echo "FAIL mid_value_if_cfg_lowering.pw(legacy value if)" >&2
    exit 1
fi
echo "PASS mid_value_if_cfg_lowering.pw(mid)" >&2
