#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-float.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
echo 'check float literal value/type transport' >&2
"$PLEWC" --emit-mid-coverage tests/run/mid_float_literal.pw >"$directory/input.ll" 2>"$directory/coverage"
if grep -E 'name=(identity|narrow|wide|separated|defaultValue|[$]defaultArgument[0-9]+) category=' "$directory/coverage" >&2; then
    echo 'FAIL float literals(legacy)' >&2
    exit 1
fi
echo 'PASS float literals(mid)' >&2
