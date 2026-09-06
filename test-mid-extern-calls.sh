#!/bin/sh
# Access-path gate; companion C execution/goldens remain covered by test.sh.
# Foreign bodies themselves are not Plew bodies and need no Mid coverage.
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-extern.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
failed=0
for source in tests/run/mid_extern_scalar_call.pw \
    tests/run/ffi_extern_c.pw tests/run/extern_c_same_name_as_intrinsic.pw \
    tests/run/final_callable_extern_call.pw; do
    echo "check $source(extern-calls)" >&2
    names='main'
    if [ "$source" = tests/run/mid_extern_scalar_call.pw ]; then
        names='main|exercise|mark'
    fi
    if ! "$PLEWC" --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"; then
        cat "$directory/coverage" >&2
        echo "FAIL $source(emit)" >&2
        failed=1
    elif grep -E "name=($names) category=" "$directory/coverage" >&2; then
        echo "FAIL $source(legacy-extern-call)" >&2
        failed=1
    else
        echo "PASS $source(mid-extern-calls)" >&2
    fi
done
exit "$failed"
