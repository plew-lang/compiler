#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-inout-field-argument.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM

source=tests/run/mid_inout_field_argument_cfg_lowering.pw
if ! "$PLEWC" --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"; then
    cat "$directory/coverage" >&2
    echo "FAIL $source(emit)" >&2
    exit 1
fi
if grep -E 'name=grow category=' "$directory/coverage" >&2; then
    echo "FAIL $source(legacy)" >&2
    exit 1
fi
echo "PASS $source(mid)" >&2
