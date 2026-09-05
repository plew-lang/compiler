#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-copy.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
if ! "$PLEWC" --emit-mid-coverage tests/run/mid_copy_owned_destination.pw >"$directory/input.ll" 2>"$directory/coverage"; then
    cat "$directory/coverage" >&2
    echo 'FAIL mid-copy-owned-destination(emit)' >&2
    exit 1
fi
# Run output plus the ASan run corpus test ownership. This gate additionally
# prevents those tests from silently exercising legacy implementations.
if grep -E 'name=(bindingCopy|returningCopy|runCopies|main) category=' "$directory/coverage" >&2; then
    echo 'FAIL mid-copy-owned-destination(legacy)' >&2
    exit 1
fi
echo 'PASS mid-copy-owned-destination' >&2
