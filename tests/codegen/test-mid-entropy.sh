#!/bin/sh
set -eu
cd "$(dirname "$0")/../.."
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-entropy.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
if ! "$PLEWC" --require-mid --emit-mid-coverage tests/run/random.pw >"$directory/input.ll" 2>"$directory/coverage"; then
    cat "$directory/coverage" >&2
    exit 1
fi
grep -q 'call i64 @plew_random_u64(' "$directory/input.ll"
echo "PASS random(mid entropy)" >&2
