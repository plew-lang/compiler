#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-direct-extern.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
for name in runtime_intrinsic_numeric_identity runtime_intrinsic_entropy_identity ffi_extern_c mid_ffi_intrinsic_calls mid_ffi_intrinsic_same_name; do
    if ! "$PLEWC" --require-mid --emit-mid-coverage "tests/run/$name.pw" >"$directory/input.ll" 2>"$directory/coverage"; then
        cat "$directory/coverage" >&2
        exit 1
    fi
    echo "PASS $name(mid direct extern)" >&2
done
