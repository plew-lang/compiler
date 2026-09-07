#!/bin/sh
# Closure construction is a Mid value producer.  Keep the two v1 capture
# modes separate: immutable captures become independently-owned environment
# slots, while mutable scalar captures retain one shared cell.
set -eu
cd "$(dirname "$0")"

PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-closure-construction.XXXXXX")
trap 'rm -f "$directory"/*.ll "$directory"/*.coverage; rmdir "$directory"' EXIT HUP INT TERM

for source in tests/run/closure_capture.pw tests/run/closure_mut_capture.pw; do
    stem=$(basename "$source" .pw)
    echo "check $source(closure Mid construction)" >&2
    "$PLEWC" --emit-mid-coverage "$source" >"$directory/$stem.ll" 2>"$directory/$stem.coverage"
    if grep -E 'name=(makeAdder|makeCounter|main) category=' "$directory/$stem.coverage" >&2; then
        echo "FAIL $source(legacy closure construction/body)" >&2
        exit 1
    fi
    echo "PASS $source(mid)" >&2
done
