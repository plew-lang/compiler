#!/bin/sh
# The input AST may be semantically incomplete; the generated program may not.
set -eu
cd "$(dirname "$0")"
PLEWC="${PLEWC:-./plewc}"
LC="${LLVM_CONFIG:-/opt/homebrew/opt/llvm/bin/llvm-config}"
work=$(mktemp -d tmp/gen_ast.XXXXXX)
trap 'rm -rf "$work"' EXIT HUP INT TERM
cp tests/genast/UnresolvedField.pw "$work/App.pw"
cp Plew.toml Plew.lock "$work/"
# Use the committed dependency manifest and lock, as in test-gen.sh.
printf '%s\n' 'check gen-input-ast: compile derive runner' >&2
"$PLEWC" --gen "$work/App.pw" > "$work/harness.ll"
"$PLEWC" --runtime > "$work/runtime.c"
clang -w "$work/harness.ll" "$work/runtime.c" $("$LC" --ldflags) -o "$work/harness"
printf '%s\n' 'check gen-input-ast: compare generated source' >&2
"$work/harness" > "$work/App.gen.pw"
cmp tests/genast/UnresolvedField.expected "$work/App.gen.pw"
printf '%s\n' 'check gen-input-ast: reject invalid application' >&2
app_exit=0
"$PLEWC" "$work/App.pw" > "$work/app.ll" 2> "$work/app.err" || app_exit=$?
[ "$app_exit" -eq 1 ] && [ -s "$work/app.err" ]
printf '%s\n' 'PASS gen-input-ast' >&2
