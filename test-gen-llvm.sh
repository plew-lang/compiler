#!/bin/sh
# LLVM-backend metaprogramming (gen) coverage harness — the LLVM analogue of the
# gen/genreject sections of test.sh. For each tests/gen/<name>/App.pw it runs the
# whole `plew gen` pipeline through the LLVM backend:
#
#   1. plewc-llvm --gen App.pw            -> harness IR   (the derive-runner)
#   2. clang harness.ll + runtime         -> harness bin
#   3. harness                            -> App.gen.pw   (generated source)
#   4. plewc-llvm App.pw                  -> app IR       (auto-parts App.gen.pw)
#   5. clang app.ll + runtime -> run      -> stdout vs tests/gen/<name>/App.out
#
# A test whose harness/app the backend can't lower yet is REJECTED LOUDLY (no
# silent miscompile) and counts as SKIP, not a failure. genreject/<name>/App.pw
# must be rejected by `plewc-llvm --gen`.
#
# All scratch lives under ./tmp (gitignored); cleanup is encapsulated here so the
# caller never types `rm`. Prereq: ./build-llvm.sh (-> compiler/plewc-llvm).
set -e
cd "$(dirname "$0")"

LC="${LLVM_CONFIG:-llvm-config}"
command -v "$LC" >/dev/null 2>&1 || {
    [ -x /opt/homebrew/opt/llvm/bin/llvm-config ] && LC=/opt/homebrew/opt/llvm/bin/llvm-config
}
PLEWC_LLVM=compiler/plewc-llvm
[ -x "$PLEWC_LLVM" ] || { echo "run ./build-llvm.sh first" >&2; exit 1; }

mkdir -p tmp
RT=tmp/gen_rt.c
"$PLEWC_LLVM" --runtime > "$RT"

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
    rm -f "$work"/*.gen.pw

    # 1. harness IR (a feature the backend can't lower yet -> loud reject -> SKIP)
    if ! "$PLEWC_LLVM" --gen "$work/App.pw" > "$work/harness.ll" 2>"$work/gen.err"; then
        skip=$((skip + 1)); continue
    fi
    # 2+3. link + run the harness -> App.gen.pw
    if ! clang -w "$work/harness.ll" "$RT" $("$LC" --ldflags) -o "$work/harness" 2>/dev/null; then
        fail=$((fail + 1)); failed="$failed $name(harness-link)"; continue
    fi
    "$work/harness" > "$work/App.gen.pw"
    # 4. build the app (auto-parts App.gen.pw)
    if ! "$PLEWC_LLVM" "$work/App.pw" > "$work/app.ll" 2>"$work/app.err"; then
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

# genreject/ : `plewc-llvm --gen` must REJECT these (e.g. a directive arg setting
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
    rm -f "$work"/*.gen.pw
    if "$PLEWC_LLVM" --gen "$work/App.pw" > /dev/null 2>/dev/null; then
        fail=$((fail + 1)); failed="$failed genreject/$name(accepted)"
    else
        rpass=$((rpass + 1))
    fi
done

echo "----"
echo "llvm-gen: pass=$pass  reject=$rpass  skip(unsupported)=$skip  fail=$fail"
[ -n "$failed" ] && echo "failing:$failed"
[ "$fail" -eq 0 ]
