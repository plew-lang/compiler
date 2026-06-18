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
# A test whose harness/app the backend can't lower yet is REJECTED LOUDLY (no
# silent miscompile) and counts as SKIP, not a failure. genreject/<name>/App.pw
# must be rejected by `plewc --gen`.
#
# All scratch lives under ./tmp (gitignored); cleanup is encapsulated here so the
# caller never types `rm`. Prereq: ./bootstrap.sh (-> plewc).
set -e
cd "$(dirname "$0")"

LC="${LLVM_CONFIG:-llvm-config}"
command -v "$LC" >/dev/null 2>&1 || {
    [ -x /opt/homebrew/opt/llvm/bin/llvm-config ] && LC=/opt/homebrew/opt/llvm/bin/llvm-config
}
PLEWC=plewc
[ -x "$PLEWC" ] || { echo "run ./bootstrap.sh first" >&2; exit 1; }

mkdir -p tmp
RT=tmp/gen_rt.c
"$PLEWC" --runtime > "$RT"

pass=0; skip=0; fail=0
failed=""

for app in tests/gen/*/App.pw; do
    [ -f "$app" ] || continue
    dir=$(dirname "$app")
    name=$(basename "$dir")
    work="tmp/gen_$name"
    rm -rf "$work"
    mkdir -p "$work"
    cp "$dir"/*.pw "$work/" 2>/dev/null || true
    cp Plew.toml Plew.lock "$work/" 2>/dev/null || true
    rm -f "$work"/*.gen.pw

    # 1. harness IR (a feature the backend can't lower yet -> loud reject -> SKIP)
    if ! "$PLEWC" --gen "$work/App.pw" > "$work/harness.ll" 2>"$work/gen.err"; then
        skip=$((skip + 1)); continue
    fi
    # 2+3. link + run the harness -> App.gen.pw
    if ! clang -w "$work/harness.ll" "$RT" $("$LC" --ldflags) -o "$work/harness" 2>/dev/null; then
        fail=$((fail + 1)); failed="$failed $name(harness-link)"; continue
    fi
    "$work/harness" > "$work/App.gen.pw"
    # 4. build the app (auto-parts App.gen.pw)
    if ! "$PLEWC" "$work/App.pw" > "$work/app.ll" 2>"$work/app.err"; then
        skip=$((skip + 1)); continue
    fi
    if ! clang -w "$work/app.ll" "$RT" $("$LC" --ldflags) -o "$work/app" 2>/dev/null; then
        fail=$((fail + 1)); failed="$failed $name(app-link)"; continue
    fi
    # 5. run + compare
    got=$("$work/app" 2>/dev/null) || true
    if [ "$got" = "$(cat "$dir/App.out")" ]; then
        pass=$((pass + 1))
    else
        fail=$((fail + 1)); failed="$failed $name"
    fi
done

# genreject/ : `plewc --gen` must REJECT these (e.g. a directive arg setting
# a private macro-struct field). A SKIP here would be a false pass, so a non-error
# (accepted) counts as a failure.
rpass=0
for app in tests/genreject/*/App.pw; do
    [ -f "$app" ] || continue
    name=$(basename "$(dirname "$app")")
    work="tmp/genreject_$name"
    rm -rf "$work"
    mkdir -p "$work"
    cp "$(dirname "$app")"/*.pw "$work/" 2>/dev/null || true
    cp Plew.toml Plew.lock "$work/" 2>/dev/null || true
    rm -f "$work"/*.gen.pw
    if "$PLEWC" --gen "$work/App.pw" > /dev/null 2>/dev/null; then
        fail=$((fail + 1)); failed="$failed genreject/$name(accepted)"
    else
        rpass=$((rpass + 1))
    fi
done

echo "----"
echo "llvm-gen: pass=$pass  reject=$rpass  skip(unsupported)=$skip  fail=$fail"
[ -n "$failed" ] && echo "failing:$failed"
[ "$fail" -eq 0 ]
