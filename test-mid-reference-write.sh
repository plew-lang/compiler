#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-reference-write.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/trace"; rmdir "$directory"' EXIT HUP INT TERM
"$PLEWC" --trace-codegen tests/run/mid_reference_write.pw >"$directory/input.ll" 2>"$directory/trace"
for name in replace nested; do
    if ! grep -q "Mid function emit-done name=$name " "$directory/trace"; then
        echo "FAIL reference write did not use Mid: $name" >&2
        exit 1
    fi
done
echo 'PASS reference writes (replacement lifetime and nested reference use Mid)' >&2
