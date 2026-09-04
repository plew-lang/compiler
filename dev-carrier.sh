#!/bin/sh
# Build an explicitly non-canonical development compiler from a historical
# tracked `plewc`.  This is a temporary escape hatch while the canonical
# self-hosting path is too slow; it must never update plewc or seed artifacts.
set -eu
cd "$(dirname "$0")"

usage() {
    echo "usage: $0 <commit-or-ref>" >&2
    echo "  writes a disposable compiler to tmp/dev-carrier/plewc" >&2
    exit 64
}

[ "$#" -eq 1 ] || usage
ref="$1"
out="tmp/dev-carrier"
stage="$out/plewc-stage"

LC="${LLVM_CONFIG:-llvm-config}"
command -v "$LC" >/dev/null 2>&1 || {
    [ -x /opt/homebrew/opt/llvm/bin/llvm-config ] && LC=/opt/homebrew/opt/llvm/bin/llvm-config
}
command -v "$LC" >/dev/null 2>&1 || { echo "llvm-config not found (set LLVM_CONFIG)" >&2; exit 1; }

mkdir -p "$out"
# Historical plewc locates @Std relative to its executable.  Keep the current
# standard library visible without copying it into, or modifying, the carrier.
ln -sfn ../../std "$out/std"
git show "$ref:plewc" > "$stage"
chmod +x "$stage"

llTmp="$out/compiler.ll.tmp"
runtimeTmp="$out/runtime.c.tmp"
binaryTmp="$out/plewc.tmp"
cleanup() { rm -f "$llTmp" "$runtimeTmp" "$binaryTmp"; }
trap cleanup EXIT HUP INT TERM

"$stage" src/_.pw > "$llTmp"
[ -s "$llTmp" ] || { echo "stage emitted empty LLVM IR" >&2; exit 1; }
"$stage" --runtime > "$runtimeTmp"
[ -s "$runtimeTmp" ] || { echo "stage emitted empty runtime source" >&2; exit 1; }

# Keep the canonical compiler's portable optimization policy.  This artifact
# is outside version control, so it cannot silently become a seed.
clang -w -O2 "$llTmp" "$runtimeTmp" $("$LC" --ldflags --libs core) -o "$binaryTmp"
mv -f "$llTmp" "$out/compiler.ll"
mv -f "$runtimeTmp" "$out/runtime.c"
mv -f "$binaryTmp" "$out/plewc"
trap - EXIT HUP INT TERM

echo "built disposable development carrier: $out/plewc (stage $ref)"
echo "use it explicitly, e.g. PLEWC=$(pwd)/$out/plewc PLEW_TEST_JOBS=1 ./test.sh"
