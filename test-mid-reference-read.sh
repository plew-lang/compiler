#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-reference-read.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/trace"; rmdir "$directory"' EXIT HUP INT TERM
"$PLEWC" --trace-codegen tests/run/mid_reference_read.pw >"$directory/input.ll" 2>"$directory/trace"
for name in read readMutable readMethod; do
    if ! grep -q "Mid function emit-done name=$name " "$directory/trace"; then
        echo "FAIL reference read did not use Mid: $name" >&2
        exit 1
    fi
done
echo 'PASS reference reads (Ref, MutableRef, and pointee receiver use Mid)' >&2
