#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-body-receiver.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
for name in enum_extension mid_generic_extension_match extension_trait_subject provided_method_valid generic_extension_receiver_record_direct_field_body generic_bound_trait_path_provided mid_generic_self_match self_param_conformance_enum; do
    if ! "$PLEWC" --require-mid "tests/run/$name.pw" >"$directory/input.ll" 2>"$directory/coverage"; then
        cat "$directory/coverage" >&2
        exit 1
    fi
    echo "PASS $name(mid body receiver)" >&2
done
