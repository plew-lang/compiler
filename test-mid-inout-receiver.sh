#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-inout-receiver.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM

source=tests/run/mid_inout_receiver.pw
if ! "$PLEWC" --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"; then
    cat "$directory/coverage" >&2
    echo "FAIL $source(emit)" >&2
    exit 1
fi
if grep -E 'name=(read|invoke) category=' "$directory/coverage" >&2; then
    echo "FAIL $source(legacy)" >&2
    exit 1
fi
echo "PASS $source(mid)" >&2

for source in tests/run/inout_overlap_ok.pw tests/run/mid_inout_shared_disjoint.pw tests/panic/overlapping_inout_ref.pw tests/panic/overlapping_inout_container.pw tests/panic/overlapping_inout_mixed.pw tests/panic/overlapping_inout_receiver_container.pw; do
    echo "check $source(shared inout Mid)" >&2
    if ! "$PLEWC" --require-mid --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"; then
        cat "$directory/coverage" >&2
        exit 1
    fi
    echo "PASS $source(mid)" >&2
done
for source in tests/run/inout_ref_pin.pw tests/run/mid_inout_shared_writeback_pin.pw; do
    echo "check $source(pin lifetime Mid)" >&2
    "$PLEWC" --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"
    # User deinit/global initializer migration is independent; all bodies
    # lending, rebinding, and writing back the reference must use Mid.
    if grep -E 'name=(main|swapRef|rebindGlobal|replace) category=' "$directory/coverage" >&2; then
        echo "FAIL $source(legacy pin lifetime)" >&2
        exit 1
    fi
    echo "PASS $source(mid)" >&2
done
