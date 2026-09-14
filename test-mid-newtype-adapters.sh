#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-newtype-adapters.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/trace"; rmdir "$directory"' EXIT HUP INT TERM
for name in newtype_adapter_boundary newtype_adapter_move newtype_factory_inherit newtype_conformance_self_arguments newtype_unique_inherit any_sendable_newtype unique_move_fn range_custom_step_arc; do
    echo "check $name(mid newtype adapter)" >&2
    if ! "$PLEWC" --require-mid --trace-codegen "tests/run/$name.pw" >"$directory/input.ll" 2>"$directory/trace"; then
        cat "$directory/trace" >&2
        exit 1
    fi
    if [ "$name" = newtype_adapter_boundary ]; then
        python3 - "$directory/trace" <<'CHECK'
import pathlib, re, sys
trace = pathlib.Path(sys.argv[1]).read_text()
# Two source calls share one emitted adapter; an uncalled method emits none.
adapters = re.findall(r"emit index=\d+ method=duplicate .*? receiver=Wrapped ", trace)
assert len(adapters) == 1, f"expected one shared adapter, got {len(adapters)}"
assert not re.search(r"emit index=\d+ method=unused ", trace), "uncalled method was emitted"
CHECK
    fi
    echo "PASS $name(mid newtype adapter)" >&2
done
