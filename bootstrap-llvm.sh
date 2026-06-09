#!/bin/sh
# Build the self-hosted Plew compiler's LLVM backend from the checked-in IR seed.
# The LLVM-only analogue of bootstrap.sh: where the C bootstrap seeds from a C
# translation (plewc.seed.c, clang-only), this seeds from the compiler's own LLVM
# IR (plewc-llvm.seed.ll) plus its runtime (plewc-llvm.seed.runtime.c), so the
# build needs clang + libLLVM (which the LLVM backend links anyway).
#
#   1. clang the IR seed + runtime + libLLVM   -> plewc-llvm0  (a working compiler)
#   2. plewc-llvm0 compiles compiler/src/_llvm.pw -> compiler/plewc-llvm
#   3. fixpoint: the freshly built plewc-llvm reproduces the seed IR + runtime
#      exactly, proving the seed matches the current source.
#
# If you change the compiler (compiler/src/*.pw or the LLVM backend), regenerate
# the seed:  ./bootstrap-llvm.sh --reseed   (commit the updated seed files).
#
# NOTE: the IR seed is LLVM-textual-IR, so it is coupled to the libLLVM version
# that generated it — a major libLLVM upgrade may require a --reseed even with no
# source change (the .ll text drifts). The build still works; only the fixpoint
# check is version-sensitive.
set -e
cd "$(dirname "$0")"

LC="${LLVM_CONFIG:-llvm-config}"
command -v "$LC" >/dev/null 2>&1 || {
    [ -x /opt/homebrew/opt/llvm/bin/llvm-config ] && LC=/opt/homebrew/opt/llvm/bin/llvm-config
}
command -v "$LC" >/dev/null 2>&1 || { echo "llvm-config not found (set LLVM_CONFIG)" >&2; exit 1; }

SEED_LL=compiler/plewc-llvm.seed.ll
SEED_RT=compiler/plewc-llvm.seed.runtime.c
PW=compiler/src/_llvm.pw
LDLIBS="$("$LC" --ldflags --libs core)"

[ -f "$SEED_LL" ] || { echo "missing $SEED_LL — cannot bootstrap" >&2; exit 1; }
[ -f "$SEED_RT" ] || { echo "missing $SEED_RT — cannot bootstrap" >&2; exit 1; }

echo "[1/3] clang the IR seed -> plewc-llvm0..."
# Built at compiler/plewc-llvm0 so it resolves @Std from compiler/std/ (the std
# root is the binary's directory + std/, see computeStdRoot).
clang -w "$SEED_LL" "$SEED_RT" $LDLIBS -o compiler/plewc-llvm0

echo "[2/3] plewc-llvm0 compiles the compiler -> compiler/plewc-llvm..."
./compiler/plewc-llvm0 "$PW" > compiler/plewc-llvm.ll
./compiler/plewc-llvm0 --runtime > compiler/plewc-llvm.runtime.c
clang -w compiler/plewc-llvm.ll compiler/plewc-llvm.runtime.c $LDLIBS -o compiler/plewc-llvm

if [ "$1" = "--reseed" ]; then
    cp compiler/plewc-llvm.ll "$SEED_LL"
    cp compiler/plewc-llvm.runtime.c "$SEED_RT"
    rm -f compiler/plewc-llvm0 compiler/plewc-llvm.ll compiler/plewc-llvm.runtime.c
    echo "[3/3] reseeded $SEED_LL + $SEED_RT from current source"
    echo "  done — commit the seed files"
    exit 0
fi

echo "[3/3] fixpoint: does the freshly built plewc-llvm reproduce the seed?"
./compiler/plewc-llvm "$PW" > compiler/plewc-llvm.check.ll
./compiler/plewc-llvm --runtime > compiler/plewc-llvm.check.runtime.c
if cmp -s "$SEED_LL" compiler/plewc-llvm.check.ll && cmp -s "$SEED_RT" compiler/plewc-llvm.check.runtime.c; then
    rm -f compiler/plewc-llvm0 compiler/plewc-llvm.ll compiler/plewc-llvm.runtime.c \
          compiler/plewc-llvm.check.ll compiler/plewc-llvm.check.runtime.c
    echo
    echo "  *** self-host fixpoint reached — seed matches current source ***"
    echo "  canonical LLVM compiler: compiler/plewc-llvm   (usage: compiler/plewc-llvm file.pw > out.ll)"
else
    rm -f compiler/plewc-llvm0 compiler/plewc-llvm.ll compiler/plewc-llvm.runtime.c \
          compiler/plewc-llvm.check.ll compiler/plewc-llvm.check.runtime.c
    echo "!!! seed is STALE: the source changed since the seed was generated." >&2
    echo "    run ./bootstrap-llvm.sh --reseed and commit the seed files." >&2
    exit 1
fi
