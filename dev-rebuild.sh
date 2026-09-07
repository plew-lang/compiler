#!/bin/sh
# Rebuild the canonical `plewc` IN PLACE from the current source.
#
# Why this exists: after editing `src/*.pw`, `plewc` is stale
# until rebuilt. Hand-building a throwaway binary and then accidentally testing
# with the *stale* `plewc` is a recurring mistake. This keeps ONE
# canonical binary: edit source -> `./dev-rebuild.sh` -> always test with
# `plewc`. Never create `/tmp/plewcN`.
#
# The selected input compiler (LLVM backend) recompiles the new source into
# LLVM IR; clang + libLLVM links it into the new binary. This is the fast
# inner-loop rebuild (no fixpoint check, no reseed). It does NOT replace
# `./bootstrap.sh`: once a change is verified, run `./bootstrap.sh --reseed`
# (regenerate the IR seed) + `./bootstrap.sh` (fixpoint) + `./test.sh` before
# committing. The current `plewc` compiles the new source even if the
# new feature isn't used by the compiler itself (ADD->reseed->USE).
set -e
cd "$(dirname "$0")"

LC="${LLVM_CONFIG:-llvm-config}"
command -v "$LC" >/dev/null 2>&1 || {
    [ -x /opt/homebrew/opt/llvm/bin/llvm-config ] && LC=/opt/homebrew/opt/llvm/bin/llvm-config
}
command -v "$LC" >/dev/null 2>&1 || { echo "llvm-config not found (set LLVM_CONFIG)" >&2; exit 1; }
PLEWC="${PLEWC:-./plewc}"
[ -x "$PLEWC" ] || { echo "input compiler missing: $PLEWC" >&2; exit 1; }

# See bootstrap.sh: prefer the selected llvm-config's logical libLLVM path
# over a Homebrew Cellar path, retaining llvm-config --libdir as a fallback.
LLVM_LIBDIR="${LLVM_LIBDIR:-$("$LC" --libdir)}"
LLVM_CONFIG_PATH="$(command -v "$LC")"
LLVM_PREFIX="$(dirname "$(dirname "$LLVM_CONFIG_PATH")")"
if [ -f "$LLVM_PREFIX/lib/libLLVM.dylib" ]; then
    LLVM_LIBDIR="$LLVM_PREFIX/lib"
fi
LDLIBS="-L$LLVM_LIBDIR -lLLVM"
# -O2 to match bootstrap.sh: plewc is run on every self-compile, so optimizing
# the binary roughly halves rebuild/compile time (the emitted IR is unaffected).
OPT="-O2"
"$PLEWC" --trace-phases src/_.pw > /tmp/_plewc.ll
"$PLEWC" --runtime > /tmp/_plewc.runtime.c
clang -w $OPT /tmp/_plewc.ll /tmp/_plewc.runtime.c $LDLIBS -o /tmp/_plewc.new
mv -f /tmp/_plewc.new plewc
echo "rebuilt plewc from current source"
