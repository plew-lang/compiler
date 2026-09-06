#!/bin/sh
# Access gate only. Global initializer bodies also need independent Mid coverage
# before the global migration is complete; a Mid main alone is not that proof.
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-global.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM
failed=0
check() {
    source=$1
    names=$2
    echo "check $source(global-access)" >&2
    if ! "$PLEWC" --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"; then
        cat "$directory/coverage" >&2
        echo "FAIL $source(emit)" >&2
        failed=1
    elif grep -E "name=($names) category=" "$directory/coverage" >&2; then
        echo "FAIL $source(legacy-global-access)" >&2
        failed=1
    else
        echo "PASS $source(mid-global-access)" >&2
    fi
}
check tests/run/global_var.pw 'main|bump|sumNums|advance'
check tests/run/global_forward_ref.pw 'main'
check tests/run/global_generic_init.pw 'main|makeBox|get'
check tests/run/mid_global_ownership.pw 'main|replace|snapshot|shadow'
check tests/part/default_argument_provenance/Main.pw 'main|exercise|choose|chooseGlobal|message'
exit "$failed"
