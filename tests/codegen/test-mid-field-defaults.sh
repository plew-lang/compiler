#!/bin/sh
set -eu
cd "$(dirname "$0")/../.."
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-field-defaults.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
for name in mid_generic_field_defaults nested_field_array_inout field_defaults_generic field_default_evaluation_occurrence field_default_enum_branch factory_private_default_provenance field_default_named_factory_forward field_default_dictionary field_defaults final_callable_field_default; do
    if ! "$PLEWC" --require-mid "tests/run/$name.pw" >"$directory/input.ll" 2>"$directory/coverage"; then
        cat "$directory/coverage" >&2
        exit 1
    fi
    echo "PASS $name(mid field defaults)" >&2
done
