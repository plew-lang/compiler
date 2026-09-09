#!/bin/sh
# The performance harness must measure the compiler it just built, not merely
# the old carrier compiling newer source. Exercise the two-generation path
# with a tiny fake compiler encoded as LLVM, so this test stays fast and does
# not depend on the real compiler currently self-hosting.
set -eu

cd "$(dirname "$0")"

LLVM_CONFIG="${LLVM_CONFIG:-/opt/homebrew/opt/llvm@22/bin/llvm-config}"
if [ ! -x "$LLVM_CONFIG" ]; then
    LLVM_CONFIG="$(command -v llvm-config || true)"
fi
[ -n "$LLVM_CONFIG" ] && [ -x "$LLVM_CONFIG" ] || {
    echo "SKIP self-host-measurement (llvm-config unavailable)"
    exit 0
}

work="$(mktemp -d "${TMPDIR:-/tmp}/plew-self-host-measure.XXXXXX")"
cleanup() { rm -rf "$work"; }
trap cleanup EXIT HUP INT TERM

mkdir -p "$work/source"
printf '%s\n' 'fn main() {}' >"$work/source/_.pw"

# This program is both the stage-1 candidate and its stage-2 successor. Its
# normal mode emits valid LLVM; --runtime emits the empty runtime companion.
printf '%s\n' \
    '#include <stdio.h>' \
    '#include <string.h>' \
    'int main(int argc, char **argv) {' \
    '  if (argc > 1 && strcmp(argv[1], "--runtime") == 0) return 0;' \
    '  fprintf(stderr, "[trace-phase] fake:start\n");' \
    '  puts("; ModuleID = '\''fake'\''");' \
    '  puts("source_filename = \"fake\"");' \
    '  puts("define i32 @main() {");' \
    '  puts("entry:");' \
    '  puts("  ret i32 0");' \
    '  puts("}");' \
    '  fprintf(stderr, "[trace-phase] fake:done\n");' \
    '  return 0;' \
    '}' >"$work/fake.c"
clang -S -emit-llvm -O0 "$work/fake.c" -o "$work/fake.ll"

printf '%s\n' \
    '#!/bin/sh' \
    'if [ "$1" = "--runtime" ]; then exit 0; fi' \
    'printf "%s\\n" "[trace-phase] fake:start" >&2' \
    "cat '$work/fake.ll'" \
    'printf "%s\\n" "[trace-phase] fake:done" >&2' >"$work/carrier"
chmod +x "$work/carrier"

OUT_DIR="$work/artifacts" \
CARRIER="$work/carrier" \
SOURCE="$work/source/_.pw" \
RUNS=2 \
LLVM_CONFIG="$LLVM_CONFIG" \
./measure-self-host.sh >/dev/null

[ -x "$work/artifacts/candidate/plewc" ]
[ -x "$work/artifacts/self-compile-1/next/plewc" ]
[ -x "$work/artifacts/self-compile-2/next/plewc" ]
grep -q '^candidate_build_exit_status=0$' "$work/artifacts/summary.txt"
grep -q '^self_compile_runs=2$' "$work/artifacts/summary.txt"
grep -q '^self_compile_exit_statuses=0,0$' "$work/artifacts/summary.txt"
grep -q '^self_compile_outputs_match=yes$' "$work/artifacts/summary.txt"
cmp -s "$work/artifacts/self-compile-1/compiler.ll" "$work/artifacts/self-compile-2/compiler.ll"

echo "PASS self-host-measurement"
