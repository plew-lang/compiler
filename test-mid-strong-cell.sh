#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-strong-cell.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/trace"; rmdir "$directory"' EXIT HUP INT TERM
"$PLEWC" --trace-codegen tests/run/mid_strong_cell_creation.pw >"$directory/input.ll" 2>"$directory/trace"
count=$(grep -c 'Mid function emit-done name=value ' "$directory/trace" || true)
if [ "$count" -lt 2 ] || grep -E 'fallback.*callee=(refNew|mutableRefNew)' "$directory/trace" >&2; then
    echo 'FAIL strong cell creation did not use Mid' >&2
    exit 1
fi
echo 'PASS strong cell creation (Ref and MutableRef factories use Mid)' >&2
