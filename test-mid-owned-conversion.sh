#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-conversion.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
failed=0
for boundary in aggregate existential array enum array_call enum_call; do
    name="mid_owned_${boundary}_copy"
    if ! "$PLEWC" --emit-mid-coverage "tests/run/$name.pw" >"$directory/input.ll" 2>"$directory/coverage"; then
        cat "$directory/coverage" >&2
        echo "FAIL $name(emit)" >&2
        failed=1
    elif grep -E 'name=copyBoundary category=' "$directory/coverage" >&2; then
        echo "FAIL $name(legacy-boundary)" >&2
        failed=1
    else
        echo "PASS $name(mid-boundary)" >&2
    fi
done
exit "$failed"
