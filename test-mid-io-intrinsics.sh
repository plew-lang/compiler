#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-io.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
echo 'check Io runtime intrinsic declaration transport' >&2
"$PLEWC" --emit-mid-coverage tests/run/mid_io_intrinsic_calls.pw >"$directory/input.ll" 2>"$directory/coverage"
if grep -E 'name=(sinkText|sinkByte|textFile|byteFile|pathExists|main) category=' "$directory/coverage" >&2; then
    echo 'FAIL Io runtime intrinsics(legacy)' >&2
    exit 1
fi
echo 'PASS Io runtime intrinsics(mid)' >&2
