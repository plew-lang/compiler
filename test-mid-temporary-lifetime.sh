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
