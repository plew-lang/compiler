#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-try.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM

# `try` is not an exception escape hatch. These cases pin the three Mid
# boundaries: direct Err propagation, frontend-selected From conversion, and
# normal cleanup of the live owned frame on the Err return edge.
for source in \
    tests/run/try_coalesce.pw \
    tests/run/try_from_conversion.pw \
    tests/run/try_from_error_overload.pw \
    tests/run/try_from_generic_convert.pw \
    tests/run/try_from_generic_arg_match.pw \
    tests/run/try_err_unwind_arc.pw \
    tests/run/try_expression_statement.pw \
    tests/run/try_place_operand_arc.pw \
    tests/run/try_struct_receiver.pw; do
    echo "check $source(try Mid CFG)" >&2
    "$PLEWC" --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"
    if grep -E 'name=(sumTwo|process|outer|stage|run) category=' "$directory/coverage" >&2; then
        echo "FAIL $source(legacy try)" >&2
        exit 1
    fi
done
echo "PASS try Mid CFG" >&2
