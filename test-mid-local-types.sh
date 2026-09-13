#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-local-types.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
for source in tests/run/generic_extension_receiver_record_isolation.pw tests/run/generic_match_result_payload_term.pw tests/run/iter_enumerate.pw tests/run/iter_enumerate_heap.pw tests/run/mid_generic_record_owned_return.pw; do
if ! "$PLEWC" --require-mid --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"; then
    cat "$directory/coverage" >&2
    echo "FAIL $source(mid local types)" >&2
    exit 1
fi
echo "PASS $source(mid local types)" >&2
done
