#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-deinit.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
for name in arc_deinit_order arc_locals_scope_order arg_convention_guaranteed_arc arc_nested_generic_box unique_shadow_commit; do
    if ! "$PLEWC" --require-mid --emit-mid-coverage "tests/run/$name.pw" >"$directory/input.ll" 2>"$directory/coverage"; then
        cat "$directory/coverage" >&2
        echo "FAIL $name(mid deinit receiver)" >&2
        exit 1
    fi
    echo "PASS $name(mid deinit receiver)" >&2
done
