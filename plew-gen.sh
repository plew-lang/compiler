#!/bin/sh
# plew gen — run user-defined derive macros (spec/16 metaprogramming).
#
# For each target <Foo>.pw annotated with `@[Name(...)]`, synthesize a derive
# harness, compile+run it, and write the generated Plew source to <Foo>.gen.pw
# (committed; the normal build auto-parts it — the loader pulls in <Foo>.gen.pw
# whenever a file carries `@[...]`). This is a version-agnostic String→String
# step: `plewc --gen` emits the harness LLVM IR, clang + libLLVM builds it,
# running it prints the generated source. Same plewc|clang|run orchestration as
# bootstrap.sh/test.sh, so the runner never touches the AST types.
#
# Usage: ./plew-gen.sh <file.pw> [<file.pw> ...]

set -e
cd "$(dirname "$0")"
PLEWC=${PLEWC:-compiler/plewc}
CC=${CC:-clang}

LC="${LLVM_CONFIG:-llvm-config}"
command -v "$LC" >/dev/null 2>&1 || {
    [ -x /opt/homebrew/opt/llvm/bin/llvm-config ] && LC=/opt/homebrew/opt/llvm/bin/llvm-config
}
command -v "$LC" >/dev/null 2>&1 || { echo "plew gen: llvm-config not found (set LLVM_CONFIG)" >&2; exit 1; }
LDFLAGS="$("$LC" --ldflags)"

TMP="${TMPDIR:-/tmp}/plew-gen-$$"
mkdir -p "$TMP"
trap 'rm -rf "$TMP"' EXIT

if [ ! -x "$PLEWC" ]; then
    echo "plew gen: $PLEWC not found — run ./bootstrap.sh first" >&2
    exit 1
fi
if [ "$#" -eq 0 ]; then
    echo "usage: ./plew-gen.sh <file.pw> [<file.pw> ...]" >&2
    exit 1
fi

# The generated IR links the program-independent runtime (same as the test harness).
"$PLEWC" --runtime > "$TMP/runtime.c"

for pw in "$@"; do
    case "$pw" in
        *.gen.pw) echo "plew gen: skipping generated file $pw" >&2; continue ;;
        *.pw) ;;
        *) echo "plew gen: not a .pw file: $pw" >&2; exit 1 ;;
    esac
    out="${pw%.pw}.gen.pw"
    "$PLEWC" --gen "$pw" > "$TMP/harness.ll"
    "$CC" -w "$TMP/harness.ll" "$TMP/runtime.c" $LDFLAGS -o "$TMP/harness"
    "$TMP/harness" > "$out"
    echo "plew gen: $pw -> $out"
done
