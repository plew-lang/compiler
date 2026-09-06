#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-process.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
echo 'check Process runtime intrinsic declaration transport' >&2
"$PLEWC" --emit-mid-coverage tests/run/mid_process_intrinsic_calls.pw >"$directory/input.ll" 2>"$directory/coverage"
if grep -E 'name=main category=' "$directory/coverage" >&2; then
    echo 'FAIL Process runtime intrinsics(legacy)' >&2
    exit 1
fi
echo 'PASS Process runtime intrinsics(mid)' >&2
