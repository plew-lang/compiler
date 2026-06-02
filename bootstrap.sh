#!/bin/sh
# Bootstrap the self-hosted Plew compiler and verify the self-host fixpoint.
#
#   stage0 (Rust, bootstrap/) is a throwaway compiler. It exists only to build
#   the real compiler, which is written in Plew: selfhost/plewc.pw (stage1).
#   Post-self-host, stage1 is canonical — new language features go into
#   plewc.pw, not into stage0.
#
# Chain:
#   1. cargo build           -> stage0 `plewc` (Rust)
#   2. stage0 plewc.pw       -> selfhost/plewc          (stage1, built by stage0)
#   3. stage1 plewc.pw > c1  -> clang -> selfhost/plewc-selfbuilt (built by itself)
#   4. selfbuilt plewc.pw>c2 ; assert c1 == c2          (fixpoint)
#
# On success `selfhost/plewc` is a working compiler: `selfhost/plewc foo.pw`
# prints C to stdout (pipe to clang). Requires cargo and clang on PATH.

set -e
cd "$(dirname "$0")"
ROOT="$(pwd)"
PW="$ROOT/selfhost/plewc.pw"

echo "[1/4] building stage0 (Rust)..."
( cd bootstrap && cargo build --release -q )
STAGE0="$ROOT/bootstrap/target/release/plewc"

echo "[2/4] stage0 builds the stage1 compiler from plewc.pw..."
# stage0's CLI builds a native executable next to the .pw (via C + clang).
"$STAGE0" "$PW" >/dev/null
STAGE1="$ROOT/selfhost/plewc"

echo "[3/4] stage1 compiles itself; clang the result..."
"$STAGE1" "$PW" > "$ROOT/selfhost/plewc.c"
clang -Wall -Wextra -Werror "$ROOT/selfhost/plewc.c" -o "$ROOT/selfhost/plewc-selfbuilt"

echo "[4/4] fixpoint check: self-built compiler reproduces its own C..."
"$ROOT/selfhost/plewc-selfbuilt" "$PW" > "$ROOT/selfhost/plewc2.c"
if cmp -s "$ROOT/selfhost/plewc.c" "$ROOT/selfhost/plewc2.c"; then
    echo
    echo "  *** self-host fixpoint reached — stage1 reproduces itself exactly ***"
    echo "  canonical compiler: selfhost/plewc   (usage: selfhost/plewc file.pw | clang -x c -)"
else
    echo "!!! FIXPOINT BROKEN: selfhost/plewc.c and selfhost/plewc2.c differ" >&2
    exit 1
fi

# tidy intermediate C (binaries + .c are gitignored anyway)
rm -f "$ROOT/selfhost/plewc2.c"
