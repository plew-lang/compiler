#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-value-match.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM

for source in tests/run/mid_value_match_cfg_lowering.pw tests/run/mid_value_match_all_diverge.pw tests/run/mid_value_match_evaluation_boundaries.pw; do
    echo "check $source(value match CFG)" >&2
    "$PLEWC" --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"
    if grep -E 'name=(choose|throughCall|throughAggregate|fromCall|intoBox) category=' "$directory/coverage" >&2; then
        echo "FAIL $source(legacy value match)" >&2
        exit 1
    fi
done
echo "PASS $source(mid)" >&2

for source in tests/run/match_expr_scrutinee_temp_arc.pw tests/run/mid_value_block_context.pw; do
    echo "check $source(contextual value block)" >&2
    "$PLEWC" --require-mid "$source" >"$directory/input.ll" 2>"$directory/coverage"
    echo "PASS $source(mid)" >&2
done
