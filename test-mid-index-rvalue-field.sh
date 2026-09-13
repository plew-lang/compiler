#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
source=tests/run/mid_index_rvalue_field.pw
echo "check $source(temporary owner and index evaluation)" >&2
"$PLEWC" --require-mid "$source" > /dev/null
echo "PASS $source(mid)" >&2
