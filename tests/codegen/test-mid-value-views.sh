#!/bin/sh
set -eu
cd "$(dirname "$0")/../.."
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-value-views.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
for source in tests/run/static_view_inout_receiver.pw tests/run/static_view_value_arc.pw tests/run/extension_conformance_only_view.pw tests/run/extension_overload_view.pw tests/run/extension_overload_view_single.pw tests/run/extension_super_chain.pw tests/run/extension_trait_provenance_select.pw tests/run/extension_type_view.pw tests/run/generic_associated_bound_extension_grounding.pw tests/run/generic_extension_trait_view.pw tests/run/multiple_extension_type_view.pw tests/run/primitive_trait_view.pw tests/run/static_extension_view_array_return_source.pw tests/run/static_mixed_view_source_set.pw tests/run/static_trait_view_method_source.pw tests/run/trait_subject_cycle_source_set_removed_allowed.pw tests/run/trait_subject_generic_active_view_acyclic.pw tests/run/trait_subject_select.pw tests/run/trait_view_additive.pw; do
if ! "$PLEWC" --require-mid --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"; then
    cat "$directory/coverage" >&2
    echo "FAIL $source(mid value views)" >&2
    exit 1
fi
echo "PASS $source(mid value views)" >&2
done
