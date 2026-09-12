#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-lifetime.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
if ! "$PLEWC" --emit-mid-coverage tests/run/mid_temporary_lifetime_boundaries.pw >"$directory/input.ll" 2>"$directory/coverage"; then
    cat "$directory/coverage" >&2
    echo 'FAIL mid-temporary-lifetime(emit)' >&2
    exit 1
fi
if grep -E 'name=(ifTemporary|whileTemporary|andTemporary|orTemporary|nestedTemporary|statementTemporary|returnTemporary|contextTypedTemporary|bindingTemporary|assignmentTemporary) category=' "$directory/coverage" >&2; then
    echo 'FAIL mid-temporary-lifetime(legacy)' >&2
    exit 1
fi
echo 'PASS mid-temporary-lifetime' >&2

# Both nested borrowed arguments and receivers keep the unique owner until
# the enclosing full expression ends; consuming a named owner stays a Move.
if ! "$PLEWC" --emit-mid-coverage tests/run/mid_unique_temporary_borrow_scope.pw >"$directory/input.ll" 2>"$directory/coverage"; then
    cat "$directory/coverage" >&2
    echo 'FAIL mid-unique-temporary-borrow(emit)' >&2
    exit 1
fi
if grep -E 'name=(main|positive|observe|consume) category=' "$directory/coverage" >&2; then
    echo 'FAIL mid-unique-temporary-borrow(legacy)' >&2
    exit 1
fi
echo 'PASS mid-unique-temporary-borrow' >&2
