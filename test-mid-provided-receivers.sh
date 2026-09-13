#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-provided.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
# The ordinary suite checks outputs; this gate requires the closed Mid path.
for source in tests/part/traitsubjectowner/Main.pw tests/run/extension_trait_path_provided.pw tests/run/generic_bound_trait_path_provided.pw tests/run/generic_bound_trait_path_provided_assoc_output.pw tests/run/generic_bound_view_trait_path_provided.pw tests/run/generic_bound_view_trait_path_provided_assoc_output.pw tests/run/generic_bound_view_trait_path_provided_assoc_output_generic.pw tests/run/provided_associated_forward_trait.pw tests/run/provided_associated_nested_types.pw tests/run/trait_blanket.pw tests/run/trait_subject_chain.pw tests/run/trait_view_single_path.pw; do
    if ! "$PLEWC" --require-mid --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"; then
        cat "$directory/coverage" >&2
        echo "FAIL $source(mid provided receiver)" >&2
        exit 1
    fi
    echo "PASS $source(mid provided receiver)" >&2
done
