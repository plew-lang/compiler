#!/bin/sh
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
source=tests/run/mid_hash_seed.pw
echo "check $source(hash seed declaration identity)" >&2
"$PLEWC" --require-mid "$source" > /dev/null
echo "PASS $source(mid)" >&2
