#!/bin/sh
# Rebuild the canonical `compiler/plewc` IN PLACE from the current source.
#
# Why this exists: after editing `compiler/src/*.pw`, `compiler/plewc` is stale
# until rebuilt. Hand-building a throwaway binary and then accidentally testing
# with the *stale* `compiler/plewc` is a recurring mistake. This keeps ONE
# canonical binary: edit source -> `./dev-rebuild.sh` -> always test with
# `compiler/plewc`. Never create `/tmp/plewcN`.
#
# The current `compiler/plewc` (LLVM backend) recompiles the new source into
# LLVM IR; clang + libLLVM links it into the new binary. This is the fast
# inner-loop rebuild (no fixpoint check, no reseed). It does NOT replace
# `./bootstrap.sh`: once a change is verified, run `./bootstrap.sh --reseed`
# (regenerate the IR seed) + `./bootstrap.sh` (fixpoint) + `./test.sh` before
# committing. The current `compiler/plewc` compiles the new source even if the
# new feature isn't used by the compiler itself (ADD->reseed->USE).
set -e
cd "$(dirname "$0")"

LC="${LLVM_CONFIG:-llvm-config}"
command -v "$LC" >/dev/null 2>&1 || {
    [ -x /opt/homebrew/opt/llvm/bin/llvm-config ] && LC=/opt/homebrew/opt/llvm/bin/llvm-config
}
command -v "$LC" >/dev/null 2>&1 || { echo "llvm-config not found (set LLVM_CONFIG)" >&2; exit 1; }
[ -x compiler/plewc ] || { echo "compiler/plewc missing — run ./bootstrap.sh first" >&2; exit 1; }

LDLIBS="$("$LC" --ldflags --libs core)"
compiler/plewc compiler/src/_.pw > /tmp/_plewc.ll
compiler/plewc --runtime > /tmp/_plewc.runtime.c
clang -w /tmp/_plewc.ll /tmp/_plewc.runtime.c $LDLIBS -o /tmp/_plewc.new
mv -f /tmp/_plewc.new compiler/plewc
echo "rebuilt compiler/plewc from current source"
