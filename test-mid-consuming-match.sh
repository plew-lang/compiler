#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-consuming-match.XXXXXX")
trap 'rm -f "$directory/input.ll"; rmdir "$directory"' EXIT HUP INT TERM
for name in match_move_discard_payload match_move_unique_payload match_move_wildcard_payload unique_enum_arc mid_enum_destructure_runtime mid_enum_destructure_verify; do
    echo "check $name(consuming Mid match)" >&2
    "$PLEWC" --require-mid "tests/run/$name.pw" > "$directory/input.ll"
    echo "PASS $name(consuming Mid match)" >&2
done
