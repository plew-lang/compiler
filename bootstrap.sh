#!/bin/sh
# Build the self-hosted Plew compiler from the checked-in LLVM IR seed.
# The compiler's only backend is LLVM: it emits textual LLVM IR and links
# libLLVM (the emitter calls libLLVM-C). The seed is the compiler's own IR
# (plewc.seed.ll) plus its runtime (plewc.seed.runtime.c), so
# the build needs clang + libLLVM.
#
#   1. clang the IR seed + runtime + libLLVM  -> plewc0  (a working compiler)
#   2. fetch deps: the compiler depends on @Plew/Syntax (a git package), so the
#      resolver materializes it into the global cache before the compiler is
#      compiled (network only on a cold cache; the committed Plew.lock pins it).
#   3. plewc0 compiles src/_.pw            -> plewc
#   4. fixpoint: the freshly built plewc reproduces the seed IR + runtime exactly,
#      proving the seed matches the current source.
#
# If you change the compiler (src/*.pw) — or bump the @Plew/Syntax version —
# regenerate the seed:
#   ./bootstrap.sh --reseed   (commit the updated seed files + plewc).
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

SEED_LL=plewc.seed.ll
SEED_RT=plewc.seed.runtime.c
# Absolute entry path: the @Plew/Syntax git dependency resolves through this
# package's Plew.toml + Plew.lock (findPkgDir walks up from the entry), which is
# robust no matter the current directory.
PW="$(pwd)/src/_.pw"
LDLIBS="$("$LC" --ldflags --libs core)"
# Optimize the built compiler: plewc is run (not just produced) on every
# self-compile, so -O2 roughly halves self-compile time (measured 89s -> 45s).
# The emitted IR is plewc's deterministic output, independent of this flag, so
# the fixpoint still holds bit-for-bit; -O2 only costs a slower clang link.
OPT="-O2"

[ -f "$SEED_LL" ] || { echo "missing $SEED_LL — cannot bootstrap" >&2; exit 1; }
[ -f "$SEED_RT" ] || { echo "missing $SEED_RT — cannot bootstrap" >&2; exit 1; }

echo "[1/4] clang the IR seed -> plewc0..."
# Built at plewc0 so it resolves @Std from std/ (the std
# root is the binary's directory + std/, see computeStdRoot).
clang -w $OPT "$SEED_LL" "$SEED_RT" $LDLIBS -o plewc0

echo "[2/4] fetch @Plew/Syntax into the cache (resolver)..."
# The resolver (resolve/_.pw) imports only the arena-free toolchain leaves
# (Manifest/Lock/Cache/Fetch/Toml/Version) — NOT @Plew/Syntax — so plewc0 builds
# it offline. Running it reads ./Plew.toml and materializes each git dependency
# at its locked commit into the global cache; the compiler then resolves
# @Plew/Syntax from there. Best-effort: on a warm cache + offline, a failed
# refresh is fine (we rely on what is already cached).
./plewc0 resolve/_.pw > plew-resolve.ll
./plewc0 --runtime > plew-resolve.runtime.c
clang -w $OPT plew-resolve.ll plew-resolve.runtime.c -o plew-resolve
./plew-resolve > /dev/null 2>&1 || echo "  (dep refresh failed — offline? relying on existing cache)"
rm -f plew-resolve.ll plew-resolve.runtime.c

echo "[3/4] plewc0 compiles the compiler -> plewc..."
./plewc0 "$PW" > plewc.ll
./plewc0 --runtime > plewc.runtime.c
clang -w $OPT plewc.ll plewc.runtime.c $LDLIBS -o plewc

if [ "$1" = "--reseed" ]; then
    cp plewc.ll "$SEED_LL"
    cp plewc.runtime.c "$SEED_RT"
    rm -f plewc0 plewc.ll plewc.runtime.c
    echo "[4/4] reseeded $SEED_LL + $SEED_RT from current source"
    echo "  done — commit the seed files + plewc"
    exit 0
fi

echo "[4/4] fixpoint: does the freshly built plewc reproduce the seed?"
./plewc "$PW" > plewc.check.ll
./plewc --runtime > plewc.check.runtime.c
if cmp -s "$SEED_LL" plewc.check.ll && cmp -s "$SEED_RT" plewc.check.runtime.c; then
    rm -f plewc0 plewc.ll plewc.runtime.c \
          plewc.check.ll plewc.check.runtime.c
    echo
    echo "  *** self-host fixpoint reached — seed matches current source ***"
    echo "  canonical compiler: plewc   (usage: plewc file.pw > out.ll)"
else
    rm -f plewc0 plewc.ll plewc.runtime.c \
          plewc.check.ll plewc.check.runtime.c
    echo "!!! seed is STALE: the source changed since the seed was generated." >&2
    echo "    run ./bootstrap.sh --reseed and commit the seed files + plewc." >&2
    exit 1
fi
