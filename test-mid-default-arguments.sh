#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-default.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
failed=0
for source in tests/run/default_args.pw tests/run/default_arg_array.pw \
    tests/run/default_eval_order.pw tests/run/default_eval_order_method.pw \
    tests/run/default_eval_order_generic_method.pw \
    tests/run/mid_default_argument_lifetime.pw tests/run/mid_default_argument_generic.pw \
    tests/run/mid_default_argument_result_context.pw \
    tests/run/mid_default_argument_internal_lifetime.pw \
    tests/run/mid_factory_evaluation_order.pw \
    tests/part/default_argument_provenance/Main.pw; do
    echo "check $source(default-arguments)" >&2
    names='main|exercise'
    if [ "$source" = tests/run/mid_factory_evaluation_order.pw ]; then
        names='main|explicit|omitted|nested'
    fi
    if ! "$PLEWC" --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"; then
        cat "$directory/coverage" >&2
        echo "FAIL $source(emit)" >&2
        failed=1
    elif grep -E "name=($names) category=" "$directory/coverage" >&2; then
        echo "FAIL $source(legacy-default-argument)" >&2
        failed=1
    else
        echo "PASS $source(mid-default-arguments)" >&2
    fi
done
exit "$failed"
