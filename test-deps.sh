#!/bin/sh
# test-deps.sh — end-to-end test of package dependency resolution (spec/17).
# Builds the standalone resolver, sets up throwaway local git repos with tags,
# runs the resolver to produce Plew.lock, and builds+runs consumers whose `@dep`
# imports are backed by the lock + global cache. Covers @Manifest/@Version/@Lock/
# @Cache/@Fetch and the resolver, which the main test.sh (single-file programs)
# does not exercise. Exits non-zero on the first mismatch.
set -e
ROOT=$(cd "$(dirname "$0")" && pwd)
PLEWC="$ROOT/compiler/plewc"
CC=${CC:-clang}
[ -x "$PLEWC" ] || { echo "test-deps: $PLEWC missing — run ./bootstrap.sh" >&2; exit 1; }

WORK=$(mktemp -d /tmp/plew-deptest.XXXXXX)
export PLEW_CACHE="$WORK/cache"
trap 'rm -rf "$WORK"' EXIT

# Build the resolver binary (libc only, like any compiled program).
"$PLEWC" "$ROOT/compiler/resolve/_.pw" > "$WORK/resolve.ll"
"$PLEWC" --runtime > "$WORK/rt.c"
"$CC" -w "$WORK/resolve.ll" "$WORK/rt.c" -o "$WORK/plew-resolve"

gitinit() { git -C "$1" init -q && git -C "$1" add -A && git -C "$1" -c user.email=t@t -c user.name=t commit -qm init; }

# --- leaf git library, two tags ---
LEAF="$WORK/leaf"; mkdir -p "$LEAF/src"
printf 'name = "Acme/Greet"\n' > "$LEAF/Plew.toml"
printf 'export fn hello() -> I64 { return 42I64 }\n' > "$LEAF/src/_.pw"
gitinit "$LEAF"
git -C "$LEAF" tag -a -m v1 1.0.0
git -C "$LEAF" tag -a -m v1 1.2.0

# --- mid git library depending on leaf ---
MID="$WORK/mid"; mkdir -p "$MID/src"
cat > "$MID/Plew.toml" <<EOF
name = "Mid"
[dependencies]
"Acme/Greet" = { git = "$LEAF", version = "1" }
EOF
printf 'import @Acme/Greet with { hello }\nexport fn midVal() -> I64 { return hello() + 1I64 }\n' > "$MID/src/_.pw"
gitinit "$MID"
git -C "$MID" tag -a -m v2 2.0.0

fail=0
check() { # name expected actual
    if [ "$2" = "$3" ]; then echo "ok   $1"; else echo "FAIL $1: expected [$2] got [$3]"; fail=1; fi
}

# --- consumer 1: direct git dep, version "1" -> latest 1.x = 1.2.0 ---
A1="$WORK/app1"; mkdir -p "$A1"
cat > "$A1/Plew.toml" <<EOF
name = "app1"
[dependencies]
"Acme/Greet" = { git = "$LEAF", version = "1" }
EOF
printf 'import @Std/Io with { print }\nimport @Acme/Greet with { hello }\nfn main() { print(hello()) }\n' > "$A1/Main.pw"
( cd "$A1" && "$WORK/plew-resolve" ) > "$A1/Plew.lock"
check "lock picks 1.2.0" "1.2.0" "$(grep -A2 '\[\[package\]\]' "$A1/Plew.lock" | grep version | head -1 | sed 's/.*"\(.*\)".*/\1/')"
"$PLEWC" "$A1/Main.pw" > "$WORK/a1.ll"
"$CC" -w "$WORK/a1.ll" "$WORK/rt.c" -o "$WORK/a1"
check "direct git dep runs" "42" "$("$WORK/a1")"

# --- consumer 2: transitive git dep (app2 -> Mid -> Acme/Greet) ---
A2="$WORK/app2"; mkdir -p "$A2"
cat > "$A2/Plew.toml" <<EOF
name = "app2"
[dependencies]
"Mid" = { git = "$MID", version = "2" }
EOF
printf 'import @Std/Io with { print }\nimport @Mid with { midVal }\nfn main() { print(midVal()) }\n' > "$A2/Main.pw"
( cd "$A2" && "$WORK/plew-resolve" ) > "$A2/Plew.lock"
check "transitive lock has 2 pkgs" "2" "$(grep -c '\[\[package\]\]' "$A2/Plew.lock")"
"$PLEWC" "$A2/Main.pw" > "$WORK/a2.ll"
"$CC" -w "$WORK/a2.ll" "$WORK/rt.c" -o "$WORK/a2"
check "transitive git dep runs" "43" "$("$WORK/a2")"

# --- the `plew` driver: explicit resolve + auto-resolve on a fresh consumer ---
A3="$WORK/app3"; mkdir -p "$A3"
cat > "$A3/Plew.toml" <<EOF
name = "app3"
[dependencies]
"Acme/Greet" = { git = "$LEAF", version = "1.0" }
EOF
printf 'import @Std/Io with { print }\nimport @Acme/Greet with { hello }\nfn main() { print(hello()) }\n' > "$A3/Main.pw"
# explicit resolve (version "1.0" pins 1.0.x -> 1.0.0)
"$ROOT/plew" resolve "$A3" >/dev/null 2>&1
check "driver resolve pins 1.0.0" "1.0.0" "$(grep 'version = "' "$A3/Plew.lock" | head -1 | sed 's/.*"\(.*\)".*/\1/')"
check "driver run after resolve" "42" "$("$ROOT/plew" run "$A3/Main.pw" 2>/dev/null)"
# auto-resolve: remove the lock, a bare run must regenerate it and still work
rm -f "$A3/Plew.lock"
check "driver auto-resolves on run" "42" "$("$ROOT/plew" run "$A3/Main.pw" 2>/dev/null)"
check "auto-resolve wrote the lock" "1" "$([ -f "$A3/Plew.lock" ] && echo 1 || echo 0)"

# --- multi-major coexistence: two versions of one lib in a single build ---
# leaf2 has a v1 (leafval->1) and a v2 (leafval->100); MidA pins "1", MidB pins "2";
# the app uses both, so each must bind ITS OWN leaf version (1 + 100 = 101).
L2="$WORK/leaf2"; mkdir -p "$L2/src"
printf 'name = "L2"\n' > "$L2/Plew.toml"
printf 'export fn leafval() -> I64 { return 1I64 }\n' > "$L2/src/_.pw"
gitinit "$L2"; git -C "$L2" tag -a -m t 1.2.0
printf 'export fn leafval() -> I64 { return 100I64 }\n' > "$L2/src/_.pw"
git -C "$L2" add -A && git -C "$L2" -c user.email=t@t -c user.name=t commit -qm v2; git -C "$L2" tag -a -m t 2.0.0
mkmid() { # name dir leafconstraint exportfn
    mkdir -p "$2/src"
    cat > "$2/Plew.toml" <<EOF
name = "$1"
[dependencies]
"L2" = { git = "$L2", version = "$3" }
EOF
    printf 'import @L2 with { leafval }\nexport fn %s() -> I64 { return leafval() }\n' "$4" > "$2/src/_.pw"
    gitinit "$2"; git -C "$2" tag -a -m t 1.0.0
}
mkmid MidA "$WORK/mida" 1 va
mkmid MidB "$WORK/midb" 2 vb
A4="$WORK/app4"; mkdir -p "$A4"
cat > "$A4/Plew.toml" <<EOF
name = "app4"
[dependencies]
"MidA" = { git = "$WORK/mida", version = "1" }
"MidB" = { git = "$WORK/midb", version = "1" }
EOF
printf 'import @Std/Io with { print }\nimport @MidA with { va }\nimport @MidB with { vb }\nfn main() { print(va() + vb()) }\n' > "$A4/Main.pw"
( cd "$A4" && "$WORK/plew-resolve" ) > "$A4/Plew.lock"
check "lock holds both L2 versions" "2" "$(grep -c "git = \"$L2\"" "$A4/Plew.lock")"
"$PLEWC" "$A4/Main.pw" > "$WORK/a4.ll"
"$CC" -w "$WORK/a4.ll" "$WORK/rt.c" -o "$WORK/a4"
check "coexisting versions each bind own export" "101" "$("$WORK/a4")"

echo "----"
if [ "$fail" = 0 ]; then echo "test-deps: all green"; else echo "test-deps: FAILURES"; exit 1; fi
