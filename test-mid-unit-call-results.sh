#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-unit-call-results.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM

for source in tests/run/mid_unit_call_results.pw tests/run/mid_dynamic_call_signatures.pw; do
if ! "$PLEWC" --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"; then
    cat "$directory/coverage" >&2
    echo "FAIL $source(emit)" >&2
    exit 1
fi
if grep -E 'name=(main|emit|emitGeneric|emitErased|throughLocal|throughField|throughExistential) category=' "$directory/coverage" >&2; then
    echo "FAIL $source(legacy)" >&2
    exit 1
fi
echo "PASS $source(mid)" >&2
done
