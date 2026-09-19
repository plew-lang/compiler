#!/bin/sh
set -eu
cd "$(dirname "$0")/../.."
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-self-fields.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
for source in tests/run/array_eq.pw tests/run/array_eq_call_operand.pw tests/run/self_param_conformance.pw; do
if ! "$PLEWC" --require-mid --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"; then
    cat "$directory/coverage" >&2
    echo "FAIL $source(mid Self fields)" >&2
    exit 1
fi
echo "PASS $source(mid Self fields)" >&2
done

# This input retains a separate generic call-conversion gap. The inherited
# Self-parameter implementation itself must already have a closed Mid body.
source=tests/run/newtype_conformance_self_arguments.pw
"$PLEWC" --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"
if grep -E 'name=accept category=' "$directory/coverage" >&2; then
    echo "FAIL $source(inherited Self field body)" >&2
    exit 1
fi
echo "PASS $source(inherited Self field body)" >&2
