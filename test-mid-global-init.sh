#!/bin/sh
# Global initializers are one synthetic Mid body.  Requiring Mid for the
# fixture makes a legacy initializer, or a main body disabled merely because
# globals exist, an immediately visible failure.
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-global-init.XXXXXX")
trap 'rm -f "$directory/input.ll" "$directory/coverage"; rmdir "$directory"' EXIT HUP INT TERM

source=tests/run/mid_global_init_cfg_lowering.pw
echo "check $source(global-init-mid)" >&2
if ! "$PLEWC" --require-mid --emit-mid-coverage "$source" >"$directory/input.ll" 2>"$directory/coverage"; then
    cat "$directory/coverage" >&2
    echo "FAIL $source(global-init legacy)" >&2
    exit 1
fi
if grep -E 'category=' "$directory/coverage" >&2; then
    echo "FAIL $source(global-init coverage)" >&2
    exit 1
fi
echo "PASS $source(mid)" >&2
