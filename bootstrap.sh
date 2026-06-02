#!/bin/sh
# Build the self-hosted Plew compiler from the checked-in C seed — no Rust,
# no cargo. The compiler is the Plew package in compiler/ (root module
# compiler/src/_.pw); the seed compiler/plewc.seed.c is its C translation,
# committed so the build needs nothing but clang.
#
#   1. clang the seed                  -> plewc0  (a working compiler)
#   2. plewc0 compiles compiler/src/_.pw -> compiler/plewc.c -> compiler/plewc
#   3. fixpoint: the freshly built plewc reproduces the seed's C exactly,
#      proving the seed matches the current source.
#
# If you change compiler/src/_.pw, regenerate the seed:  ./bootstrap.sh --reseed
# (only needed when the new source uses a feature the old compiler couldn't
# emit; the plain build will tell you the seed is stale if so.)
#
# Recovering the original Rust bootstrap (stage0), if ever needed:
#   git checkout stage0-final -- bootstrap

set -e
cd "$(dirname "$0")"
SEED=compiler/plewc.seed.c
PW=compiler/src/_.pw

if [ ! -f "$SEED" ]; then
    echo "missing $SEED — cannot bootstrap" >&2
    exit 1
fi

echo "[1/3] clang the seed -> plewc0..."
clang -w "$SEED" -o compiler/plewc0

echo "[2/3] plewc0 compiles the compiler -> compiler/plewc..."
./compiler/plewc0 "$PW" > compiler/plewc.c
clang -w compiler/plewc.c -o compiler/plewc

if [ "$1" = "--reseed" ]; then
    cp compiler/plewc.c "$SEED"
    echo "[3/3] reseeded $SEED from current source"
    rm -f compiler/plewc0
    echo "  done — commit $SEED"
    exit 0
fi

echo "[3/3] fixpoint: does the freshly built plewc reproduce the seed?"
./compiler/plewc "$PW" > compiler/plewc.check.c
if cmp -s "$SEED" compiler/plewc.check.c; then
    rm -f compiler/plewc0 compiler/plewc.check.c
    echo
    echo "  *** self-host fixpoint reached — seed matches current source ***"
    echo "  canonical compiler: compiler/plewc   (usage: compiler/plewc file.pw | clang -x c -)"
else
    rm -f compiler/plewc0 compiler/plewc.check.c
    echo "!!! seed is STALE: the source changed since the seed was generated." >&2
    echo "    run ./bootstrap.sh --reseed and commit compiler/plewc.seed.c" >&2
    exit 1
fi
