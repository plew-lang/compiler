#!/bin/sh
# Rebuild the canonical `compiler/plewc` IN PLACE from the current source.
#
# Why this exists: after editing `compiler/src/*.pw`, `compiler/plewc` is stale
# until rebuilt. Hand-building a throwaway binary (`/tmp/plewcN`) and then
# accidentally testing with the *stale* `compiler/plewc` is a recurring mistake.
# This keeps ONE canonical binary: edit source -> `./dev-rebuild.sh` -> always
# test with `compiler/plewc`. Never create `/tmp/plewcN`.
#
# This is the fast inner-loop rebuild (no fixpoint check, no reseed). It does NOT
# replace `./bootstrap.sh`: once a change is verified, run `./bootstrap.sh
# --reseed` (regenerate the C seed) + `./bootstrap.sh` (fixpoint) + `./test.sh`
# before committing. The current `compiler/plewc` compiles the new source even if
# the new feature isn't used by the compiler itself (ADD->reseed->USE).
set -e
cd "$(dirname "$0")"
compiler/plewc compiler/src/_.pw > /tmp/_plewc.c
clang -x c /tmp/_plewc.c -o /tmp/_plewc.new
mv -f /tmp/_plewc.new compiler/plewc
echo "rebuilt compiler/plewc from current source"
