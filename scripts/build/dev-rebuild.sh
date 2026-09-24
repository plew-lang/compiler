#!/bin/sh
# Rebuild the canonical `plewc` IN PLACE from the current source.
#
# Why this exists: after editing `src/*.pw`, `plewc` is stale
# until rebuilt. Hand-building a throwaway binary and then accidentally testing
# with the *stale* `plewc` is a recurring mistake. This keeps ONE
# canonical binary: edit source -> `./scripts/build/dev-rebuild.sh` -> always test with
# `plewc`. Never create `/tmp/plewcN`.
#
# The selected input compiler (LLVM backend) recompiles the new source into
# a native object; clang + libLLVM links it into the new binary. This is the fast
# inner-loop rebuild (no fixpoint check, no reseed). It does NOT replace
# `./scripts/build/bootstrap.sh`: once a change is verified, run `./scripts/build/bootstrap.sh --reseed`
# (regenerate the IR seed) + `./scripts/build/bootstrap.sh` (fixpoint) + `./tests/harness/test.sh` before
# committing. The current `plewc` compiles the new source even if the
# new feature isn't used by the compiler itself (ADD->reseed->USE).
set -e
cd "$(dirname "$0")/../.."

LC="${LLVM_CONFIG:-llvm-config}"
command -v "$LC" >/dev/null 2>&1 || {
    [ -x /opt/homebrew/opt/llvm/bin/llvm-config ] && LC=/opt/homebrew/opt/llvm/bin/llvm-config
}
command -v "$LC" >/dev/null 2>&1 || { echo "llvm-config not found (set LLVM_CONFIG)" >&2; exit 1; }
PLEWC="${PLEWC:-./plewc}"
[ -x "$PLEWC" ] || { echo "input compiler missing: $PLEWC" >&2; exit 1; }

# See scripts/build/bootstrap.sh: prefer the selected llvm-config's logical libLLVM path
# over a Homebrew Cellar path, retaining llvm-config --libdir as a fallback.
LLVM_LIBDIR="${LLVM_LIBDIR:-$("$LC" --libdir)}"
LLVM_CONFIG_PATH="$(command -v "$LC")"
LLVM_PREFIX="$(dirname "$(dirname "$LLVM_CONFIG_PATH")")"
if [ -f "$LLVM_PREFIX/lib/libLLVM.dylib" ]; then
    LLVM_LIBDIR="$LLVM_PREFIX/lib"
fi
LDLIBS="-L$LLVM_LIBDIR -lLLVM"
# -O2 to match scripts/build/bootstrap.sh: plewc is run on every self-compile, so optimizing
# the binary roughly halves rebuild/compile time (the emitted IR is unaffected).
TRACE_DIR="${DEV_REBUILD_LOG_DIR:-tmp/dev-rebuild}"
mkdir -p "$TRACE_DIR"
python3 ./scripts/support/trace-command.py "$TRACE_DIR/compile.log" -- "$PLEWC" --emit-object /tmp/_plewc.o --trace-phases src/_.pw
"$PLEWC" --runtime > /tmp/_plewc.runtime.c
python3 ./scripts/support/llvm_link.py --compiler-backend --config "$LC" --log-prefix "$TRACE_DIR/link" --object /tmp/_plewc.o --runtime /tmp/_plewc.runtime.c --output /tmp/_plewc.new -- $LDLIBS
mv -f /tmp/_plewc.new plewc
echo "rebuilt plewc from current source"
