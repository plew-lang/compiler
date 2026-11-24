#!/bin/sh
# Production normal-suite case discovery, dispatch and worker entry.
set -e
cd "$(dirname "$0")/../.."
if [ "$1" != --worker ]; then
    phase="$1"
    case "$phase" in
        run|panic|reject) set -- tests/fixtures/"$phase"/*.pw ;;
        part) set -- tests/fixtures/part/*/Main.pw tests/fixtures/part/Main.pw ;;
        partreject) set -- tests/fixtures/partreject/*/Main.pw ;;
        *) echo "unknown normal phase: $phase" >&2; exit 1 ;;
    esac
    exec python3 ./scripts/support/normal-case-dispatch.py "$phase" "$@"
fi
shift
phase="$1"
shift
# Keep case classification at its existing explicit checks; dispatch owns
# unexpected worker exits and missing/malformed results.
case_tmp=$(python3 -B ./scripts/support/normal_case_artifacts.py begin "$phase" "$1") || exit 1
TMPDIR="$case_tmp/"
export TMPDIR
case_result() {
    python3 -B ./scripts/support/normal_case_artifacts.py finish "$case_tmp" "$1" || exit 1
    printf '%s\n' "$1"
    exit 0
}
set +e
case "$phase" in
    run)
    f="$1"; name=$(basename "$f" .pw); out="tests/fixtures/run/$name.out"
    [ -f "$out" ] || exit 0
    ll="${case_tmp}/t_$name.ll"; bin="${case_tmp}/t_$name"
    if ! python3 ./scripts/support/watch-command.py -- "$PLEWC" "$f" > "$ll" 2> "$case_tmp/compile.stderr"; then case_result "FAIL $name(reject)"; fi
    # A run test may pin a backend-facing invariant whose observable runtime
    # behaviour is intentionally identical to an older lowering.  `.ll.expect`
    # contains one stable literal required in the generated LLVM; normal run
    # tests need no such companion.
    ir_expect="tests/fixtures/run/$name.ll.expect"
    if [ -f "$ir_expect" ] && ! grep -qF "$(cat "$ir_expect")" "$ll"; then case_result "FAIL $name(ir)"; fi
    # Runtime output cannot detect an unnecessary metadata read. Check the
    # final-owner release branches in the actual generated LLVM for this fixture.
    if [ "$name" = array_drop_count ] && ! python3 ./tests/compiler/codegen/test-array-release-count.py "$ll" >/dev/null; then
        case_result "FAIL $name(release-count-ir)"
    fi
    extra_c=""
    [ -f "tests/fixtures/run/$name.c" ] && extra_c="tests/fixtures/run/$name.c"
    if ! python3 -B ./scripts/support/native_build.py --clang --log "$bin.link.trace.log" -- clang -w "$ll" "$PLEW_RT" $extra_c $PLEW_LD -o "$bin" 2> "$case_tmp/link.stderr"; then case_result "FAIL $name(link)"; fi
    infile="tests/fixtures/run/$name.in"
    status=0
    if [ -f "$infile" ]; then python3 ./scripts/support/watch-command.py -- "$bin" < "$infile" > "$bin.stdout" 2> "$case_tmp/run.stderr" || status=$?
    else python3 ./scripts/support/watch-command.py -- "$bin" > "$bin.stdout" 2> "$case_tmp/run.stderr" || status=$?; fi
    if [ "$status" -ne 0 ]; then case_result "FAIL $name(exit:$status)"; fi
    # An .out.exact companion opts into byte equality, including trailing newlines.
    if [ -f "$out.exact" ]; then
        if cmp -s "$bin.stdout" "$out"; then case_result "PASS $name"; else case_result "FAIL $name"; fi
    elif [ "$(cat "$bin.stdout")" = "$(cat "$out")" ]; then case_result "PASS $name"; else case_result "FAIL $name"; fi
    ;;
    panic)
    pw="$1"; [ -f "$pw" ] || exit 0
    name=$(basename "$pw" .pw)
    want=$(cat "tests/fixtures/panic/$name.panic")
    ll="${case_tmp}/t_panic_$name.ll"; bin="${case_tmp}/t_panic_$name"; perr="${case_tmp}/t_panic_$name.err"
    if ! python3 ./scripts/support/watch-command.py -- "$PLEWC" "$pw" > "$ll" 2> "$case_tmp/compile.stderr"; then case_result "FAIL panic/$name(reject)"; fi
    if ! python3 -B ./scripts/support/native_build.py --clang --log "$bin.link.trace.log" -- clang -w "$ll" "$PLEW_RT" $PLEW_LD -o "$bin" 2> "$case_tmp/link.stderr"; then case_result "FAIL panic/$name(link)"; fi
    code=0
    # nested sh: the shell that reaps a SIGABRT child prints "Abort trap" on
    # ITS stderr — run the binary one shell deeper so that note is droppable
    # without touching the binary own stderr capture ($perr).
    sh -c "python3 ./scripts/support/watch-command.py -- \"\$1\" >/dev/null 2>\"\$2\"" sh "$bin" "$perr" 2>/dev/null || code=$?
    if [ "$code" -eq 134 ] && grep -qF "$want" "$perr"; then case_result "PASS panic/$name"; else case_result "FAIL panic/$name(exit=$code)"; fi
    ;;
    reject)
    pw="$1"; [ -f "$pw" ] || exit 0
    name=$(basename "$pw" .pw)
    want="tests/fixtures/reject/$name.err"
    perr="${case_tmp}/t_reject_$name.err"
    code=0
    sh -c "python3 ./scripts/support/watch-command.py -- python3 ./scripts/support/compiler_failure_result.py --require-source-rejection -- \"\$PLEWC\" \"\$1\" >/dev/null 2>\"\$2\"" sh "$pw" "$perr" 2>/dev/null || code=$?
    if [ "$code" -ge 128 ]; then case_result "FAIL reject/$name(crash=$code)"
    elif [ "$code" -ne 0 ]; then case_result "FAIL reject/$name(classification=$code)"
    elif grep -Eq "ERROR: (Address|Leak)Sanitizer|AddressSanitizer:DEADLYSIGNAL" "$perr"; then case_result "FAIL reject/$name(sanitizer)"
    elif [ -f "$want" ] && ! grep -qF "$(cat "$want")" "$perr"; then case_result "FAIL reject/$name(diagnostic)"
    else case_result "PASS reject/$name"; fi
    ;;
    part)
    main="$1"; [ -f "$main" ] || exit 0
    dir=$(dirname "$main")
    name=$(basename "$dir")
    ll="${case_tmp}/t_part_$name.ll"; bin="${case_tmp}/t_part_$name"
    if ! python3 ./scripts/support/watch-command.py -- "$PLEWC" "$main" > "$ll" 2> "$case_tmp/compile.stderr"; then case_result "FAIL part/$name(reject)"; fi
    if ! python3 -B ./scripts/support/native_build.py --clang --log "$bin.link.trace.log" -- clang -w "$ll" "$PLEW_RT" $PLEW_LD -o "$bin" 2> "$case_tmp/link.stderr"; then case_result "FAIL part/$name(link)"; fi
    status=0
    got=$(python3 ./scripts/support/watch-command.py -- "$bin" 2> "$case_tmp/run.stderr") || status=$?
    printf '%s' "$got" > "$bin.stdout.normalized" || exit 1
    if [ "$status" -ne 0 ]; then case_result "FAIL part/$name(exit:$status)"; fi
    if ! expected=$(cat "$dir/Main.out"); then case_result "FAIL part/$name(golden)"; fi
    if [ "$got" = "$expected" ]; then case_result "PASS part/$name"; else case_result "FAIL part/$name"; fi
    ;;
    partreject)
    main="$1"; [ -f "$main" ] || exit 0
    name=$(basename "$(dirname "$main")")
    want="$(dirname "$main")/Main.err"
    perr="${case_tmp}/t_partreject_$name.err"
    code=0
    sh -c "python3 ./scripts/support/watch-command.py -- python3 ./scripts/support/compiler_failure_result.py --require-source-rejection -- \"\$PLEWC\" \"\$1\" >/dev/null 2>\"\$2\"" sh "$main" "$perr" 2>/dev/null || code=$?
    if [ "$code" -ge 128 ]; then case_result "FAIL partreject/$name(crash=$code)"
    elif [ "$code" -ne 0 ]; then case_result "FAIL partreject/$name(classification=$code)"
    elif grep -Eq "ERROR: (Address|Leak)Sanitizer|AddressSanitizer:DEADLYSIGNAL" "$perr"; then case_result "FAIL partreject/$name(sanitizer)"
    elif [ -f "$want" ] && ! grep -qF "$(cat "$want")" "$perr"; then case_result "FAIL partreject/$name(diagnostic)"
    else case_result "PASS partreject/$name"; fi
    ;;
    *) echo "unknown normal worker: $phase" >&2; exit 1 ;;
esac
