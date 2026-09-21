#!/bin/sh
set -eu
cd "$(dirname "$0")/../.."
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-core-string.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
# The ordinary intrinsic-call fixture remains in the run corpus. This check
# protects declaration-based dispatch, which its output alone cannot establish.
source=tests/run/mid_core_string_intrinsic_same_name.pw
echo "check $source(runtime intrinsic declaration transport)" >&2
"$PLEWC" "$source" >"$directory/input.ll" 2>"$directory/coverage"
if grep -q 'plew_f64_to_str' "$directory/input.ll"; then
    echo "FAIL $source(raw-name-dispatch)" >&2
    exit 1
fi
echo "PASS $source(runtime intrinsic identity)" >&2
