#!/bin/sh
# Diagnostic options must compose without changing compilation or gate results.
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
task_dir=$(mktemp -d /tmp/plew-cli-options.XXXXXX)
source=tests/run/mid_build_expr_stmt_category.pw
for mode in --emit-mid-coverage --require-mid; do
    baseline_status=0
    "$PLEWC" "$mode" "$source" > "$task_dir/baseline.ll" 2> "$task_dir/baseline.err" || baseline_status=$?
    [ "$baseline_status" -le 1 ] || exit 1
    [ -s "$task_dir/baseline.ll" ]
    if [ "$mode" = --emit-mid-coverage ]; then
        [ "$baseline_status" -eq 0 ]
    elif grep -q '^mid-coverage ' "$task_dir/baseline.err"; then
        [ "$baseline_status" -eq 1 ]
    else
        [ "$baseline_status" -eq 0 ]
    fi
    for order in before after; do
        printf 'cli-options: %s trace-%s\n' "$mode" "$order" >&2
        observed_status=0
        if [ "$order" = before ]; then
            "$PLEWC" --trace-phases "$mode" "$source" > "$task_dir/observed.ll" 2> "$task_dir/observed.err" || observed_status=$?
        else
            "$PLEWC" "$mode" --trace-phases "$source" > "$task_dir/observed.ll" 2> "$task_dir/observed.err" || observed_status=$?
        fi
        [ "$observed_status" -eq "$baseline_status" ]
        grep -q '^\[trace-phase\] load:start$' "$task_dir/observed.err"
        sed '/^\[trace-phase\]/d' "$task_dir/observed.err" > "$task_dir/coverage.err"
        cmp "$task_dir/baseline.err" "$task_dir/coverage.err"
        cmp "$task_dir/baseline.ll" "$task_dir/observed.ll"
    done
done
printf 'PASS cli-options\n'
