#!/bin/sh
# Build the LLVM-backend compiler `compiler/plewc-llvm` from the LLVM root
# `compiler/src/_llvm.pw`, ON DEMAND, using the already-built C-backend compiler
# `compiler/plewc` (run ./bootstrap.sh first). This is the only binary that links
# libLLVM; the core bootstrap (bootstrap.sh / the C seed) stays clang-only.
#
#   compiler/plewc compiler/src/_llvm.pw  -> plewc-llvm.c   (extern(c) LLVM calls)
#   clang plewc-llvm.c $(llvm-config ... --libs core)       -> compiler/plewc-llvm
#
# Usage of the result:
#   compiler/plewc-llvm prog.pw > prog.ll
#   clang prog.ll <runtime> $(llvm-config --ldflags) -o prog && ./prog
set -e
cd "$(dirname "$0")"

# Locate llvm-config (Homebrew keg-only install isn't on PATH by default).
LC="${LLVM_CONFIG:-llvm-config}"
if ! command -v "$LC" >/dev/null 2>&1; then
    if [ -x /opt/homebrew/opt/llvm/bin/llvm-config ]; then
        LC=/opt/homebrew/opt/llvm/bin/llvm-config
    elif [ -x /usr/local/opt/llvm/bin/llvm-config ]; then
        LC=/usr/local/opt/llvm/bin/llvm-config
    else
        echo "build-llvm.sh: llvm-config not found (set LLVM_CONFIG or install LLVM)" >&2
        exit 1
    fi
fi

if [ ! -x compiler/plewc ]; then
    echo "build-llvm.sh: compiler/plewc missing — run ./bootstrap.sh first" >&2
    exit 1
fi

echo "[1/2] compiler/plewc compiles the LLVM root -> /tmp/plewc-llvm.c..."
compiler/plewc compiler/src/_llvm.pw > /tmp/plewc-llvm.c

echo "[2/2] clang + libLLVM -> compiler/plewc-llvm..."
clang -w /tmp/plewc-llvm.c $("$LC" --ldflags --libs core) \
      -Wl,-rpath,"$("$LC" --libdir)" -o compiler/plewc-llvm

echo "  done — compiler/plewc-llvm  (usage: compiler/plewc-llvm file.pw > out.ll)"
