#!/bin/sh
set -eu
cd "$(dirname "$0")/../.."
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-cell-control.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
for name in ref_reassign_arc weakref_arc weakref_dance_deferred weakref_match_temp weakref_upgrade_match mid_strong_cell_creation mid_readonly_weak_cell; do
    if ! "$PLEWC" --require-mid --emit-mid-coverage "tests/run/$name.pw" >"$directory/input.ll" 2>"$directory/coverage"; then
        cat "$directory/coverage" >&2
        exit 1
    fi
    echo "PASS $name(mid cell control)" >&2
done
