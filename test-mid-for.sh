#!/bin/sh
# Keep the selected For bodies on canonical Mid; ordinary run tests check
# values and destruction order, while this gate detects a legacy fallback.
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-for.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
for source in tests/run/mid_for_control_flow.pw tests/run/for_iter_return_arc.pw tests/run/for_call_ref_array.pw tests/run/temp_for_iterable_deinit.pw tests/run/iter_for_bare.pw tests/run/any_for_iterator.pw; do
    echo "check $source(mid-for)" >&2
    if ! "$PLEWC" --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"; then
        cat "$directory/coverage" >&2
        echo "FAIL $source(emit)" >&2
        exit 1
    fi
    if grep -E 'name=(main|choose|nested|firstMatch|breakEarly|walkAll) category=' "$directory/coverage" >&2; then
        echo "FAIL $source(legacy-for)" >&2
        exit 1
    fi
    echo "PASS $source(mid-for)" >&2
done
