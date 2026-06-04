#!/bin/sh
# Language test suite for the self-hosted Plew compiler — no Rust, no cargo.
# Drives the `plewc` binary from the outside (plewc x.pw | clang | run) so it
# survives stage0's retirement. Three kinds of checks:
#
#   tests/run/*.pw     compile + run; stdout must equal tests/run/<name>.out
#                      (optional tests/run/<name>.in is fed as stdin)
#   tests/reject/*.pw  must NOT compile — encodes "the compiler rejects
#                      spec-invalid code" (acceptance soundness)
#   fixpoint           plewc compiles itself to a stable C output
#
# Usage: ./test.sh           (run ./bootstrap.sh first to build compiler/plewc)
#        ASAN=1 ./test.sh    compile + run the test PROGRAMS under
#                            AddressSanitizer (catches use-after-free /
#                            double-free / heap-overflow once ARC starts
#                            freeing). Green today: nothing is freed yet, and
#                            macOS ASan does not detect leaks by default. When
#                            ARC frees, flip ASAN_OPTIONS detect_leaks=1 below.
#                            The compiler itself (fixpoint/reject) intentionally
#                            leaks, so it stays out of the ASan pass.

cd "$(dirname "$0")"
PLEWC=./compiler/plewc
PW=./compiler/src/_.pw
TMP="${TMPDIR:-/tmp}/plew-test-$$"
mkdir -p "$TMP"
pass=0
fail=0

# Flags for compiling the generated C of *test programs*. ASAN=1 opts into
# AddressSanitizer; leak detection stays off until ARC actually frees memory.
CC_FLAGS="-w"
if [ "${ASAN:-0}" = "1" ]; then
    CC_FLAGS="-w -g -fsanitize=address -fno-omit-frame-pointer"
    export ASAN_OPTIONS="detect_leaks=0"
fi

if [ ! -x "$PLEWC" ]; then
    echo "compiler/plewc not found — run ./bootstrap.sh first" >&2
    exit 1
fi

# --- run/ : golden compile + run ---
for pw in tests/run/*.pw; do
    name=$(basename "$pw" .pw)
    c="$TMP/$name.c"
    bin="$TMP/$name"
    if ! "$PLEWC" "$pw" > "$c" 2>"$TMP/err"; then
        echo "FAIL  $name  (plewc errored)"; fail=$((fail + 1)); continue
    fi
    if ! clang $CC_FLAGS "$c" -o "$bin" 2>"$TMP/err"; then
        echo "FAIL  $name  (clang rejected generated C)"; fail=$((fail + 1)); continue
    fi
    if [ -f "tests/run/$name.in" ]; then
        got=$("$bin" < "tests/run/$name.in")
    else
        got=$("$bin")
    fi
    want=$(cat "tests/run/$name.out")
    if [ "$got" = "$want" ]; then
        pass=$((pass + 1))
    else
        echo "FAIL  $name  (output: got [$got] want [$want])"; fail=$((fail + 1))
    fi
done

# --- part/ : multi-file modules. Each subdir's Main.pw stitches in siblings
#     via `part`; compile the root, run it, and check Main.out. ---
for main in tests/part/*/Main.pw tests/part/Main.pw; do
    [ -f "$main" ] || continue
    dir=$(dirname "$main")
    name=$(basename "$dir")
    [ "$name" = "part" ] && name="part"
    c="$TMP/part-$name.c"
    bin="$TMP/part-$name"
    if ! "$PLEWC" "$main" > "$c" 2>"$TMP/err"; then
        echo "FAIL  part/$name  (plewc errored)"; fail=$((fail + 1)); continue
    fi
    if ! clang $CC_FLAGS "$c" -o "$bin" 2>"$TMP/err"; then
        echo "FAIL  part/$name  (clang rejected generated C)"; fail=$((fail + 1)); continue
    fi
    got=$("$bin")
    want=$(cat "$dir/Main.out")
    if [ "$got" = "$want" ]; then
        pass=$((pass + 1))
    else
        echo "FAIL  part/$name  (output: got [$got] want [$want])"; fail=$((fail + 1))
    fi
done

# --- panic/ : valid code that must compile and link, but abort at *runtime*
#     with a panic. The program must exit non-zero and its stderr must contain
#     the text in tests/panic/<name>.panic (overflow, div-by-zero, OOB, ...). ---
for pw in tests/panic/*.pw; do
    [ -f "$pw" ] || continue
    name=$(basename "$pw" .pw)
    c="$TMP/panic-$name.c"
    bin="$TMP/panic-$name"
    if ! "$PLEWC" "$pw" > "$c" 2>"$TMP/err"; then
        echo "FAIL  panic/$name  (plewc errored — should compile)"; fail=$((fail + 1)); continue
    fi
    if ! clang $CC_FLAGS "$c" -o "$bin" 2>"$TMP/err"; then
        echo "FAIL  panic/$name  (clang rejected generated C)"; fail=$((fail + 1)); continue
    fi
    "$bin" >/dev/null 2>"$TMP/perr"
    code=$?
    want=$(cat "tests/panic/$name.panic")
    if [ "$code" -ne 0 ] && grep -qF "$want" "$TMP/perr"; then
        pass=$((pass + 1))
    else
        echo "FAIL  panic/$name  (exit=$code stderr=[$(cat "$TMP/perr")] want substring [$want])"; fail=$((fail + 1))
    fi
done

# --- reject/ : spec-invalid code must be rejected by plewc itself (it prints
#     a `plewc: error:` diagnostic and exits non-zero). ---
for pw in tests/reject/*.pw; do
    name=$(basename "$pw" .pw)
    c="$TMP/reject-$name.c"
    if "$PLEWC" "$pw" > "$c" 2>/dev/null; then
        echo "FAIL  reject/$name  (plewc accepted it, but it should be rejected)"; fail=$((fail + 1))
    else
        pass=$((pass + 1))
    fi
done

# --- self-host fixpoint ---
# plewc1 resolves `@Std/…` relative to its own binary (computeStdRoot = argv[0]'s
# dir), so the std library must sit next to it in $TMP.
cp -r compiler/std "$TMP/std" 2>/dev/null
if "$PLEWC" "$PW" > "$TMP/a.c" 2>/dev/null \
    && clang -w "$TMP/a.c" -o "$TMP/plewc1" 2>/dev/null \
    && "$TMP/plewc1" "$PW" > "$TMP/b.c" 2>/dev/null \
    && cmp -s "$TMP/a.c" "$TMP/b.c"; then
    pass=$((pass + 1))
else
    echo "FAIL  fixpoint  (plewc does not reproduce its own C)"; fail=$((fail + 1))
fi

rm -rf "$TMP"
echo "----"
echo "pass=$pass fail=$fail"
[ "$fail" -eq 0 ]
