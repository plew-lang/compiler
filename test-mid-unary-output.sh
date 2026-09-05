#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-unary.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
for name in final_callable_unary_primitive unary_operator_distinct_output; do
    if ! "$PLEWC" --emit-mid-coverage "tests/run/$name.pw" >"$directory/input.ll" 2>"$directory/coverage"; then
        cat "$directory/coverage" >&2
        echo "FAIL $name(emit)" >&2
        exit 1
    fi
    if grep -E 'name=(main|negativeOutput|logicalOutput|bitwiseOutput|genericNegative) category=' "$directory/coverage" >&2; then
        echo "FAIL $name(legacy)" >&2
        exit 1
    fi
    echo "PASS $name(mid-unary-output)" >&2
done
