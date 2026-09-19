#!/bin/sh
set -eu
cd "$(dirname "$0")/../.."
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-range.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
for name in range_step_boundaries range_iterator_values range_custom_step_arc ambient_core for for_range_bound_temp_arc for_var_type_annotation lit_suffix range_same_type range_for_control range_literal_context generic_enum_payload_context aggregate_field_context; do
    if ! "$PLEWC" --require-mid "tests/run/$name.pw" >"$directory/input.ll" 2>"$directory/coverage"; then
        cat "$directory/coverage" >&2
        exit 1
    fi
    echo "PASS $name(mid range iterator)" >&2
done
