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
# Usage: ./test.sh   (run ./bootstrap.sh first to build compiler/plewc)

cd "$(dirname "$0")"
PLEWC=./compiler/plewc
PW=./compiler/src/_.pw
TMP="${TMPDIR:-/tmp}/plew-test-$$"
mkdir -p "$TMP"
pass=0
fail=0

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
    if ! clang -w "$c" -o "$bin" 2>"$TMP/err"; then
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

# --- reject/ : spec-invalid code must fail to compile ---
for pw in tests/reject/*.pw; do
    name=$(basename "$pw" .pw)
    c="$TMP/reject-$name.c"
    "$PLEWC" "$pw" > "$c" 2>/dev/null
    if clang -w "$c" -o "$TMP/reject-$name" 2>/dev/null; then
        echo "FAIL  reject/$name  (compiled, but should have been rejected)"; fail=$((fail + 1))
    else
        pass=$((pass + 1))
    fi
done

# --- self-host fixpoint ---
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
