#!/bin/sh
# plew gen — run user-defined derive macros (spec/16 metaprogramming).
#
# For each target <Foo>.pw annotated with `@[Name(...)]`, synthesize a derive
# harness, compile+run it, and write the generated Plew source to <Foo>.gen.pw
# (committed; the normal build auto-parts it — the loader pulls in <Foo>.gen.pw
# whenever a file carries `@[...]`). This is a version-agnostic String→String
# step: `plewc --gen` emits the harness C, clang builds it, running it prints the
# generated source. Same plewc|clang|run orchestration as bootstrap.sh/test.sh,
# so no new runtime is needed and the runner never touches the AST types.
#
# Usage: ./plew-gen.sh <file.pw> [<file.pw> ...]

set -e
cd "$(dirname "$0")"
PLEWC=${PLEWC:-compiler/plewc}
CC=${CC:-clang}
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

for pw in "$@"; do
    case "$pw" in
        *.gen.pw) echo "plew gen: skipping generated file $pw" >&2; continue ;;
        *.pw) ;;
        *) echo "plew gen: not a .pw file: $pw" >&2; exit 1 ;;
    esac
    out="${pw%.pw}.gen.pw"
    "$PLEWC" --gen "$pw" > "$TMP/harness.c"
    "$CC" -w -x c "$TMP/harness.c" -o "$TMP/harness"
    "$TMP/harness" > "$out"
    echo "plew gen: $pw -> $out"
done
