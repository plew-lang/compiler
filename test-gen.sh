#!/bin/sh
# Metaprogramming (gen) coverage harness — the gen/genreject companion to
# test.sh. For each tests/gen/<name>/App.pw it runs the whole `plew gen`
# pipeline through the compiler:
#
#   1. plewc --gen App.pw            -> harness IR   (the derive-runner)
#   2. clang harness.ll + runtime         -> harness bin
#   3. harness                            -> App.gen.pw   (generated source)
#   4. plewc App.pw                  -> app IR       (auto-parts App.gen.pw)
#   5. clang app.ll + runtime -> run      -> stdout vs tests/gen/<name>/App.out
#
# Every gen case must compile and execute. A genreject case must produce
# a compiler diagnostic (exit 1); crashes are failures, not rejections.
#
# All scratch lives under ./tmp (gitignored); cleanup is encapsulated here so the
# caller never types `rm`. Prereq: ./bootstrap.sh (-> plewc).
set -e
cd "$(dirname "$0")"

LC="${LLVM_CONFIG:-llvm-config}"
command -v "$LC" >/dev/null 2>&1 || {
    [ -x /opt/homebrew/opt/llvm/bin/llvm-config ] && LC=/opt/homebrew/opt/llvm/bin/llvm-config
}
PLEWC="${PLEWC:-./plewc}"
[ -x "$PLEWC" ] || { echo "run ./bootstrap.sh first" >&2; exit 1; }

mkdir -p tmp
# TEMP: Plew.toml pins @Plew/Syntax to the local `path = "../syntax"` (relative to
# the compiler package root) while the syntax parser is iterated on. Each gen test
# runs from a copy under tmp/gen_<name>/, so its `../syntax` resolves to tmp/syntax
# — bridge that to the real package with a symlink. Harmless once Plew.toml reverts
# to the git pin (the symlink is then just unused).
ln -sfn "$(cd ../syntax && pwd)" tmp/syntax
RT=tmp/gen_rt.c
"$PLEWC" --runtime > "$RT"

pass=0; fail=0
failed=""

for app in tests/gen/*/App.pw; do
    [ -f "$app" ] || continue
    echo "check $app(gen)" >&2
    dir=$(dirname "$app")
    name=$(basename "$dir")
    work="tmp/gen_$name"
    rm -rf "$work"
    mkdir -p "$work"
    cp "$dir"/*.pw "$work/" 2>/dev/null || true
    cp Plew.toml Plew.lock "$work/" 2>/dev/null || true
    rm -f "$work"/*.gen.pw

    # 1. harness IR
    if ! "$PLEWC" --gen "$work/App.pw" > "$work/harness.ll" 2>"$work/gen.err"; then
        fail=$((fail + 1)); failed="$failed $name(harness-compile)"; cat "$work/gen.err" >&2; continue
    fi
    # 2+3. link + run the harness -> App.gen.pw
    if ! clang -w "$work/harness.ll" "$RT" $("$LC" --ldflags) -o "$work/harness" 2>/dev/null; then
        fail=$((fail + 1)); failed="$failed $name(harness-link)"; continue
    fi
    if ! "$work/harness" > "$work/App.gen.pw" 2>"$work/harness.err"; then
        fail=$((fail + 1)); failed="$failed $name(harness-run)"; continue
    fi
    # 4. build the app (auto-parts App.gen.pw)
    if ! "$PLEWC" "$work/App.pw" > "$work/app.ll" 2>"$work/app.err"; then
        fail=$((fail + 1)); failed="$failed $name(app-compile)"; cat "$work/app.err" >&2; continue
    fi
    if ! clang -w "$work/app.ll" "$RT" $("$LC" --ldflags) -o "$work/app" 2>/dev/null; then
        fail=$((fail + 1)); failed="$failed $name(app-link)"; continue
    fi
    # 5. run + compare
    status=0
    got=$("$work/app" 2>/dev/null) || status=$?
    if [ "$status" -ne 0 ]; then
        fail=$((fail + 1)); failed="$failed $name(exit:$status)"; continue
    fi
    if [ "$got" = "$(cat "$dir/App.out")" ]; then
        pass=$((pass + 1))
        echo "PASS gen/$name" >&2
    else
        fail=$((fail + 1)); failed="$failed $name"
    fi
done

# genreject/ : `plewc --gen` must REJECT these (e.g. a directive arg setting
# a private macro-struct field). Only the diagnostic exit status is accepted.
rpass=0
for app in tests/genreject/*/App.pw; do
    [ -f "$app" ] || continue
    echo "check $app(genreject)" >&2
    name=$(basename "$(dirname "$app")")
    work="tmp/genreject_$name"
    rm -rf "$work"
    mkdir -p "$work"
    cp "$(dirname "$app")"/*.pw "$work/" 2>/dev/null || true
    cp Plew.toml Plew.lock "$work/" 2>/dev/null || true
    rm -f "$work"/*.gen.pw
    status=0
    "$PLEWC" --gen "$work/App.pw" > /dev/null 2>"$work/gen.err" || status=$?
    if [ "$status" -eq 1 ] && [ -s "$work/gen.err" ]; then
        rpass=$((rpass + 1))
        echo "PASS genreject/$name" >&2
    else
        fail=$((fail + 1)); failed="$failed genreject/$name(exit:$status)"
    fi
done

echo "----"
echo "llvm-gen: pass=$pass  reject=$rpass  skip=0  fail=$fail"
[ -n "$failed" ] && echo "failing:$failed"
[ "$fail" -eq 0 ]
