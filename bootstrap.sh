#!/bin/sh
# Build the self-hosted Plew compiler from the checked-in C seed — no Rust,
# no cargo. The compiler is selfhost/plewc.pw (written in Plew); the seed
# selfhost/plewc.seed.c is its C translation, committed so the build needs
# nothing but clang.
#
#   1. clang the seed              -> plewc0  (a working compiler)
#   2. plewc0 compiles plewc.pw    -> selfhost/plewc.c -> selfhost/plewc
#   3. fixpoint: the freshly built plewc reproduces the seed's C exactly,
#      proving the seed matches the current source.
#
# If you change selfhost/plewc.pw, regenerate the seed:  ./bootstrap.sh --reseed
# (only needed when the new source uses a feature the old compiler couldn't
# emit; the plain build will tell you the seed is stale if so.)
#
# Recovering the original Rust bootstrap (stage0), if ever needed:
#   git checkout stage0-final -- bootstrap

set -e
cd "$(dirname "$0")"
SEED=selfhost/plewc.seed.c
PW=selfhost/plewc.pw

if [ ! -f "$SEED" ]; then
    echo "missing $SEED — cannot bootstrap" >&2
    exit 1
fi

echo "[1/3] clang the seed -> plewc0..."
clang -w "$SEED" -o selfhost/plewc0

echo "[2/3] plewc0 compiles plewc.pw -> selfhost/plewc..."
./selfhost/plewc0 "$PW" > selfhost/plewc.c
clang -w selfhost/plewc.c -o selfhost/plewc

if [ "$1" = "--reseed" ]; then
    cp selfhost/plewc.c "$SEED"
    echo "[3/3] reseeded $SEED from current plewc.pw"
    rm -f selfhost/plewc0
    echo "  done — commit $SEED"
    exit 0
fi

echo "[3/3] fixpoint: does the freshly built plewc reproduce the seed?"
./selfhost/plewc "$PW" > selfhost/plewc.check.c
if cmp -s "$SEED" selfhost/plewc.check.c; then
    rm -f selfhost/plewc0 selfhost/plewc.check.c
    echo
    echo "  *** self-host fixpoint reached — seed matches current source ***"
    echo "  canonical compiler: selfhost/plewc   (usage: selfhost/plewc file.pw | clang -x c -)"
else
    rm -f selfhost/plewc0 selfhost/plewc.check.c
    echo "!!! seed is STALE: plewc.pw changed since the seed was generated." >&2
    echo "    run ./bootstrap.sh --reseed and commit selfhost/plewc.seed.c" >&2
    exit 1
fi
