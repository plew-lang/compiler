#!/bin/sh
set -eu
cd "$(dirname "$0")/../.."
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-newtype-adapters.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/trace"; rmdir "$directory"' EXIT HUP INT TERM
# Runtime behavior for the other adapter fixtures is checked by the run corpus.
name=newtype_adapter_boundary
echo "check $name(mid newtype adapter)" >&2
if ! "$PLEWC" --require-mid --trace-codegen "tests/run/$name.pw" >"$directory/input.ll" 2>"$directory/trace"; then
    cat "$directory/trace" >&2
    exit 1
fi
python3 - "$directory/trace" <<'CHECK'
import pathlib, re, sys
trace = pathlib.Path(sys.argv[1]).read_text()
# Two source calls share one emitted adapter; an uncalled method emits none.
adapters = re.findall(r"emit index=\d+ method=duplicate .*? receiver=Wrapped ", trace)
assert len(adapters) == 1, f"expected one shared adapter, got {len(adapters)}"
assert not re.search(r"emit index=\d+ method=unused ", trace), "uncalled method was emitted"
CHECK
echo "PASS $name(mid newtype adapter)" >&2
