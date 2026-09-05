#!/bin/sh
# Language test suite for the self-hosted Plew compiler. Drives the `plewc`
# binary (LLVM backend) from the outside: plewc x.pw > x.ll, clang x.ll +
# runtime, run, compare stdout to the golden .out. Covers run/ (stdout),
# panic/ (must abort with the expected text), reject/ (front-end must reject —
# acceptance soundness, incl. the shared verifyProgram pass), and part/
# (multi-file modules). Metaprogramming (gen/) is in ./test-gen.sh.
#
# Tests run PLEW_TEST_JOBS-wide (default: all cores) via xargs -P: each worker
# is one test end-to-end (compile + link + run + compare) printing exactly one
# PASS/FAIL line, aggregated after the fan-out. Observable output (counters,
# failing list, exit code) is identical to the old serial runner.
#
# Prereq: ./bootstrap.sh  (-> plewc).
set -e
cd "$(dirname "$0")"

LC="${LLVM_CONFIG:-llvm-config}"
command -v "$LC" >/dev/null 2>&1 || {
    [ -x /opt/homebrew/opt/llvm/bin/llvm-config ] && LC=/opt/homebrew/opt/llvm/bin/llvm-config
}
PLEWC="${PLEWC:-./plewc}"
[ -x "$PLEWC" ] || { echo "run ./bootstrap.sh first" >&2; exit 1; }

RT=/tmp/plew_rt.c
"$PLEWC" --runtime > "$RT"

JOBS="${PLEW_TEST_JOBS:-$(sysctl -n hw.ncpu 2>/dev/null || nproc 2>/dev/null || echo 4)}"
PLEW_RT="$RT"
PLEW_LD="$("$LC" --ldflags)"
export PLEWC PLEW_RT PLEW_LD

# Test results are collected on stdout so each phase can calculate its final
# summary deterministically.  Mirror bounded progress to stderr instead of
# making a long, healthy parallel phase indistinguishable from a hang.
# Set PLEW_TEST_PROGRESS=0 for the old quiet behaviour.
PLEW_TEST_PROGRESS="${PLEW_TEST_PROGRESS:-1}"
progress_start() {
    [ "$PLEW_TEST_PROGRESS" = 0 ] && return
    printf 'plewc: %s started (%s cases; %s workers)\n' "$1" "$2" "$JOBS" >&2
}
progress_stream() {
    phase="$1" total="$2"
    if [ "$PLEW_TEST_PROGRESS" = 0 ]; then
        cat
        return
    fi
    awk -v phase="$phase" -v total="$total" '
        {
            print
            done += 1
            printf "plewc: %s %d/%d complete: %s\n", phase, done, total, $0 > "/dev/stderr"
            fflush("/dev/stderr")
        }
    '
}
count_cases() {
    count=0
    for case_file in "$@"; do
        [ -f "$case_file" ] && count=$((count + 1))
    done
    printf '%s\n' "$count"
}

# --- suite hygiene: every companion file must pair with a .pw and vice versa.
#     A rename/delete that leaves an orphan .out (or a .pw without its golden)
#     would otherwise silently drop that test from coverage — the runners skip
#     unpaired files without a word. ---
hygiene=""
for f in tests/run/*.out tests/run/*.in tests/run/*.c tests/run/*.ll.expect; do
    [ -f "$f" ] || continue
    case "$f" in
        *.ll.expect) pw="${f%.ll.expect}.pw" ;;
        *) pw="${f%.*}.pw" ;;
    esac
    [ -f "$pw" ] || hygiene="$hygiene orphan:$f"
done
for pw in tests/run/*.pw; do
    [ -f "${pw%.pw}.out" ] || hygiene="$hygiene no-golden:$pw"
done
for f in tests/panic/*.panic; do
    [ -f "$f" ] || continue
    [ -f "${f%.panic}.pw" ] || hygiene="$hygiene orphan:$f"
done
for pw in tests/panic/*.pw; do
    [ -f "${pw%.pw}.panic" ] || hygiene="$hygiene no-golden:$pw"
done

# --- run/ : compile, link, run, compare stdout to the golden .out ---
run_total=$(count_cases tests/run/*.pw)
progress_start run "$run_total"
run_results=$(printf '%s\n' tests/run/*.pw | xargs -P "$JOBS" -n 1 sh -c '
    f="$1"; name=$(basename "$f" .pw); out="tests/run/$name.out"
    [ -f "$out" ] || exit 0
    ll="/tmp/t_$name.ll"; bin="/tmp/t_$name"
    if ! "$PLEWC" "$f" > "$ll" 2>/dev/null; then echo "FAIL $name(reject)"; exit 0; fi
    # A run test may pin a backend-facing invariant whose observable runtime
    # behaviour is intentionally identical to an older lowering.  `.ll.expect`
    # contains one stable literal required in the generated LLVM; normal run
    # tests need no such companion.
    ir_expect="tests/run/$name.ll.expect"
    if [ -f "$ir_expect" ] && ! grep -qF "$(cat "$ir_expect")" "$ll"; then echo "FAIL $name(ir)"; exit 0; fi
    extra_c=""
    [ -f "tests/run/$name.c" ] && extra_c="tests/run/$name.c"
    if ! clang -w "$ll" "$PLEW_RT" $extra_c $PLEW_LD -o "$bin" 2>/dev/null; then echo "FAIL $name(link)"; exit 0; fi
    infile="tests/run/$name.in"
    if [ -f "$infile" ]; then got=$("$bin" < "$infile" 2>/dev/null) || true
    else got=$("$bin" 2>/dev/null) || true; fi
    if [ "$got" = "$(cat "$out")" ]; then echo "PASS $name"; else echo "FAIL $name"; fi
' sh | progress_stream run "$run_total")
pass=$(printf '%s\n' "$run_results" | grep -c '^PASS' || true)
fail=0; failed=""
for n in $hygiene; do
    fail=$((fail + 1)); failed="$failed $n"
done
for n in $(printf '%s\n' "$run_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done
skip=0

# Keep phase tracing composable with both coverage modes used for self-hosting.
if sh ./test-cli-options.sh; then
    :
else
    fail=$((fail + 1)); failed="$failed cli-options"
fi

# Lifetime output alone must not pass through a legacy caller unnoticed.
if sh ./test-mid-temporary-lifetime.sh; then
    :
else
    fail=$((fail + 1)); failed="$failed mid-temporary-lifetime"
fi

# Heap-copy ownership tests must exercise Mid rather than legacy lowering.
if sh ./test-mid-copy-owned-destination.sh; then
    :
else
    fail=$((fail + 1)); failed="$failed mid-copy-owned-destination"
fi

# --- Mid migration coverage: `--emit-mid-coverage` is observational, while
# `--require-mid` is the fail-closed gate over exactly the same frozen body
# instances.  This deliberately does not pin a permanent legacy fallback: as
# the corpus reaches zero coverage the expected gate result changes from 1 to
# 0, but disagreement or unstructured output is always a failure.
mid_coverage_results=$(sh -c '
    source="tests/run/generic_extension_receiver_record_direct_field.pw"
    stem="/tmp/t_mid_coverage_$$"
    coverage="$stem.coverage"; required="$stem.required"
    if ! "$PLEWC" --emit-mid-coverage "$source" >"$stem.ll" 2>"$coverage"; then
        echo "FAIL mid-coverage(emit)"; exit 0
    fi
    records=$(grep -Ec "^mid-coverage body=[0-9]+ fn=[0-9]+ name=[A-Za-z][A-Za-z0-9]* category=[a-z-]+(:[a-z-]+){0,2}$" "$coverage" || true)
    nonempty=$(wc -l <"$coverage" | tr -d " ")
    if [ "$records" != "$nonempty" ]; then
        echo "FAIL mid-coverage(format)"; exit 0
    fi
    # A bare `preflight:call` conflates independent ABI constraints.  If this
    # fixture still reaches call preflight, the record must identify its
    # closed reason so coverage can select the next representation slice.
    if grep -q "category=preflight:call$" "$coverage"; then
        echo "FAIL mid-coverage(call-reason)"; exit 0
    fi
    code=0
    "$PLEWC" --require-mid "$source" >"$stem.require.ll" 2>"$required" || code=$?
    if [ "$records" -eq 0 ]; then
        [ "$code" -eq 0 ] && [ ! -s "$required" ] && echo "PASS mid-coverage" || echo "FAIL mid-coverage(require-zero)"
    else
        [ "$code" -eq 1 ] && cmp -s "$coverage" "$required" && echo "PASS mid-coverage" || echo "FAIL mid-coverage(require-nonzero)"
    fi
' sh)
mcpass=$(printf '%s\n' "$mid_coverage_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$mid_coverage_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

# Coverage reasons are a closed Mid-internal sum. A non-call expression
# statement used to collapse every unsupported operand/form into one label;
# pin one concrete form so coverage remains useful for choosing the next
# lowering slice.
mid_build_reason_results=$(sh -c '
    source="tests/run/mid_build_expr_stmt_category.pw"
    coverage="/tmp/t_mid_build_reason_$$.coverage"
    if ! "$PLEWC" --emit-mid-coverage "$source" >/tmp/t_mid_build_reason_$$.ll 2>"$coverage"; then
        echo "FAIL mid-build-reason(emit)"; exit 0
    fi
    if grep -q "name=ignoredValue category=build:unsupported:expression-statement" "$coverage"; then
        echo "PASS mid-build-reason"
    else
        echo "FAIL mid-build-reason(category)"
    fi
' sh)
mbrpass=$(printf '%s\n' "$mid_build_reason_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$mid_build_reason_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

# `&&` / `||` are source control flow, so a Mid body must branch before it
# evaluates the rhs. The fixture observes both skipped and taken rhs paths;
# this gate prevents those bodies from silently returning to legacy lowering.
mid_short_circuit_results=$(sh -c '
    source="tests/run/mid_short_circuit_cfg_lowering.pw"
    coverage="/tmp/t_mid_short_circuit_$$.coverage"
    if ! "$PLEWC" --emit-mid-coverage "$source" >/tmp/t_mid_short_circuit_$$.ll 2>"$coverage"; then
        echo "FAIL mid-short-circuit(emit)"; exit 0
    fi
    if grep -Eq "name=(andFalse|andTrue|orTrue|orFalse|andLoop|orLoop) category=" "$coverage"; then
        echo "FAIL mid-short-circuit(legacy)"
    else
        echo "PASS mid-short-circuit"
    fi
' sh)
mscpass=$(printf '%s\n' "$mid_short_circuit_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$mid_short_circuit_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

# A statement enum match is ordinary Mid CFG: the selected arm is reached by
# a frozen-layout tag switch and its payload bind is a Place projection.  The
# runtime result alone would also pass through legacy lowering, so coverage
# rejects the temporary `UnsupportedMatch` fallback explicitly.
mid_enum_match_results=$(sh -c '
    source="tests/run/mid_enum_match_cfg_lowering.pw"
    coverage="/tmp/t_mid_enum_match_$$.coverage"
    if ! "$PLEWC" --emit-mid-coverage "$source" >/tmp/t_mid_enum_match_$$.ll 2>"$coverage"; then
        echo "FAIL mid-enum-match(emit)"; exit 0
    fi
    if grep -q "name=score category=build:match" "$coverage"; then
        echo "FAIL mid-enum-match(legacy)"
    else
        echo "PASS mid-enum-match"
    fi
' sh)
mempass=$(printf '%s\n' "$mid_enum_match_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$mid_enum_match_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

# A payloadless enum construction in a return is a semantic aggregate, even
# though it has no payload slots.  Mid must consume Record's aggregate fact
# and preserve MidOperandBuild's default success error; legacy fallback would
# mask both regressions while still printing the right value.
mid_payloadless_enum_return_results=$(sh -c '
    source="tests/run/mid_payloadless_enum_return.pw"
    coverage="/tmp/t_mid_payloadless_enum_return_$$.coverage"
    if ! "$PLEWC" --emit-mid-coverage "$source" >/tmp/t_mid_payloadless_enum_return_$$.ll 2>"$coverage"; then
        echo "FAIL mid-payloadless-enum-return(emit)"; exit 0
    fi
    if grep -q "name=decide category=" "$coverage"; then
        echo "FAIL mid-payloadless-enum-return(legacy)"
    else
        echo "PASS mid-payloadless-enum-return"
    fi
' sh)
mperpass=$(printf '%s\n' "$mid_payloadless_enum_return_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$mid_payloadless_enum_return_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

# A root assignment consumes the resolver-selected declaration identity; Mid
# must never recover the target local by source spelling. The fixture covers
# the ownership-sensitive Overwrite path independently of projection access.
mid_local_assign_results=$(sh -c '
    source="tests/run/mid_local_assign_cfg_lowering.pw"
    coverage="/tmp/t_mid_local_assign_$$.coverage"
    if ! "$PLEWC" --emit-mid-coverage "$source" >/tmp/t_mid_local_assign_$$.ll 2>"$coverage"; then
        echo "FAIL mid-local-assign(emit)"; exit 0
    fi
    if grep -q "name=overwrite category=build:assign" "$coverage"; then
        echo "FAIL mid-local-assign(legacy)"
    else
        echo "PASS mid-local-assign"
    fi
' sh)
mlapass=$(printf '%s\n' "$mid_local_assign_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$mid_local_assign_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

# An authored `Array` read is lowered to a synthetic Index call for the
# general access model, but its frozen addressable place must enter Mid as an
# Index projection.  Runtime output and a bounds-check marker alone could
# both be satisfied by legacy lowering, so pin the selected body separately.
mid_index_place_results=$(sh -c '
    source="tests/run/mid_index_place_runtime_cfg_lowering.pw"
    coverage="/tmp/t_mid_index_place_$$.coverage"
    if ! "$PLEWC" --emit-mid-coverage "$source" >/tmp/t_mid_index_place_$$.ll 2>"$coverage"; then
        echo "FAIL mid-index-place(emit)"; exit 0
    fi
    if grep -q "name=select category=" "$coverage"; then
        echo "FAIL mid-index-place(legacy)"
    else
        echo "PASS mid-index-place"
    fi
' sh)
mipass=$(printf '%s\n' "$mid_index_place_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$mid_index_place_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

# A closed runtime ABI can be emitted by Mid only after its explicit operand
# convention is represented.  Keep this focused fixture separate from the
# aggregate corpus: `appendOnce` must not silently fall back merely because
# unrelated stdlib bodies still emit `mid:` markers.
mid_buffer_append_results=$(sh -c '
    source="tests/run/mid_buffer_append_cfg_lowering.pw"
    coverage="/tmp/t_mid_buffer_append_$$.coverage"
    if ! "$PLEWC" --emit-mid-coverage "$source" >/tmp/t_mid_buffer_append_$$.ll 2>"$coverage"; then
        echo "FAIL mid-buffer-append(emit)"; exit 0
    fi
    if grep -q "name=appendOnce category=preflight:call:buffer" "$coverage"; then
        echo "FAIL mid-buffer-append(legacy)"
    else
        echo "PASS mid-buffer-append"
    fi
' sh)
mbapass=$(printf '%s\n' "$mid_buffer_append_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$mid_buffer_append_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

mid_buffer_reserve_results=$(sh -c '
    source="tests/run/mid_buffer_reserve_cfg_lowering.pw"
    coverage="/tmp/t_mid_buffer_reserve_$$.coverage"
    if ! "$PLEWC" --emit-mid-coverage "$source" >/tmp/t_mid_buffer_reserve_$$.ll 2>"$coverage"; then
        echo "FAIL mid-buffer-reserve(emit)"; exit 0
    fi
    if grep -q "name=reserveEnough category=preflight:call:buffer" "$coverage"; then
        echo "FAIL mid-buffer-reserve(legacy)"
    else
        echo "PASS mid-buffer-reserve"
    fi
' sh)
mbrpass=$(printf '%s\n' "$mid_buffer_reserve_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$mid_buffer_reserve_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

# Replacement has two independent ownership obligations: scalar assignment and
# ARC commit-then-release.  Both helpers must stay on Mid's closed Buffer ABI;
# a generic `mid:` marker elsewhere in the module is not sufficient evidence.
mid_buffer_set_results=$(sh -c '
    for source in tests/run/mid_buffer_set_cfg_lowering.pw tests/run/mid_buffer_set_arc_cfg_lowering.pw; do
        coverage="/tmp/t_mid_buffer_set_$$_$(basename "$source" .pw).coverage"
        if ! "$PLEWC" --emit-mid-coverage "$source" >/tmp/t_mid_buffer_set_$$.ll 2>"$coverage"; then
            echo "FAIL mid-buffer-set(emit)"; exit 0
        fi
        if grep -q "name=replaceFirst category=preflight:call:buffer" "$coverage"; then
            echo "FAIL mid-buffer-set(legacy)"; exit 0
        fi
    done
    echo "PASS mid-buffer-set"
' sh)
mbspass=$(printf '%s\n' "$mid_buffer_set_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$mid_buffer_set_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

# Insertion must preserve both its inclusive bound and its relocation rule:
# the existing suffix receives no ARC traffic while the inserted value becomes
# a new Buffer owner. Keep scalar and ARC fixtures in one focused ABI gate.
mid_buffer_insert_results=$(sh -c '
    for source in tests/run/mid_buffer_insert_cfg_lowering.pw tests/run/mid_buffer_insert_arc_cfg_lowering.pw; do
        coverage="/tmp/t_mid_buffer_insert_$$_$(basename "$source" .pw).coverage"
        if ! "$PLEWC" --emit-mid-coverage "$source" >/tmp/t_mid_buffer_insert_$$.ll 2>"$coverage"; then
            echo "FAIL mid-buffer-insert(emit)"; exit 0
        fi
        if grep -q "category=preflight:call:buffer" "$coverage"; then
            echo "FAIL mid-buffer-insert(legacy)"; exit 0
        fi
    done
    echo "PASS mid-buffer-insert"
' sh)
mbipass=$(printf '%s\n' "$mid_buffer_insert_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$mid_buffer_insert_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

# Removal returns the retired slot's existing ownership to the caller. Scalar
# and ARC cases ensure this remains a transfer rather than a read-plus-copy.
mid_buffer_remove_last_results=$(sh -c '
    for source in tests/run/mid_buffer_remove_last_cfg_lowering.pw tests/run/mid_buffer_remove_last_arc_cfg_lowering.pw; do
        coverage="/tmp/t_mid_buffer_remove_last_$$_$(basename "$source" .pw).coverage"
        if ! "$PLEWC" --emit-mid-coverage "$source" >/tmp/t_mid_buffer_remove_last_$$.ll 2>"$coverage"; then
            echo "FAIL mid-buffer-remove-last(emit)"; exit 0
        fi
        if grep -q "name=popOne category=preflight:call:buffer" "$coverage"; then
            echo "FAIL mid-buffer-remove-last(legacy)"; exit 0
        fi
    done
    echo "PASS mid-buffer-remove-last"
' sh)
mbrlpass=$(printf '%s\n' "$mid_buffer_remove_last_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$mid_buffer_remove_last_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

# Middle removal combines a result ownership transfer with suffix relocation.
# Its ARC fixture proves that neither side of that split loses or duplicates a
# reference while the scalar fixture pins the observable order.
mid_buffer_remove_at_results=$(sh -c '
    for source in tests/run/mid_buffer_remove_at_cfg_lowering.pw tests/run/mid_buffer_remove_at_arc_cfg_lowering.pw; do
        coverage="/tmp/t_mid_buffer_remove_at_$$_$(basename "$source" .pw).coverage"
        if ! "$PLEWC" --emit-mid-coverage "$source" >/tmp/t_mid_buffer_remove_at_$$.ll 2>"$coverage"; then
            echo "FAIL mid-buffer-remove-at(emit)"; exit 0
        fi
        if grep -q "name=takeFirst category=preflight:call:buffer" "$coverage"; then
            echo "FAIL mid-buffer-remove-at(legacy)"; exit 0
        fi
    done
    echo "PASS mid-buffer-remove-at"
' sh)
mbrapass=$(printf '%s\n' "$mid_buffer_remove_at_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$mid_buffer_remove_at_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

# O(1) swap removal has the same result transfer but a distinct relocation
# shape: the former last slot becomes the hole. Keep that ARC boundary pinned.
mid_buffer_swap_remove_results=$(sh -c '
    for source in tests/run/mid_buffer_swap_remove_cfg_lowering.pw tests/run/mid_buffer_swap_remove_arc_cfg_lowering.pw; do
        coverage="/tmp/t_mid_buffer_swap_remove_$$_$(basename "$source" .pw).coverage"
        if ! "$PLEWC" --emit-mid-coverage "$source" >/tmp/t_mid_buffer_swap_remove_$$.ll 2>"$coverage"; then
            echo "FAIL mid-buffer-swap-remove(emit)"; exit 0
        fi
        if grep -q "name=takeFirst category=preflight:call:buffer" "$coverage"; then
            echo "FAIL mid-buffer-swap-remove(legacy)"; exit 0
        fi
    done
    echo "PASS mid-buffer-swap-remove"
' sh)
mbsrpass=$(printf '%s\n' "$mid_buffer_swap_remove_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$mid_buffer_swap_remove_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

# Clear has a commit-then-release boundary: the allocation remains but each
# live ARC element is retired exactly once after the zero-count commit.
mid_buffer_clear_results=$(sh -c '
    for source in tests/run/mid_buffer_clear_cfg_lowering.pw tests/run/mid_buffer_clear_arc_cfg_lowering.pw; do
        coverage="/tmp/t_mid_buffer_clear_$$_$(basename "$source" .pw).coverage"
        if ! "$PLEWC" --emit-mid-coverage "$source" >/tmp/t_mid_buffer_clear_$$.ll 2>"$coverage"; then
            echo "FAIL mid-buffer-clear(emit)"; exit 0
        fi
        if grep -q "name=clearAll category=preflight:call:buffer" "$coverage"; then
            echo "FAIL mid-buffer-clear(legacy)"; exit 0
        fi
    done
    echo "PASS mid-buffer-clear"
' sh)
mbcpass=$(printf '%s\n' "$mid_buffer_clear_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$mid_buffer_clear_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

# Truncate is conditional ownership retirement. Its scalar fixture covers the
# shrink/no-op split; the ARC fixture pins suffix release without touching the
# surviving prefix.
mid_buffer_truncate_results=$(sh -c '
    for source in tests/run/mid_buffer_truncate_cfg_lowering.pw tests/run/mid_buffer_truncate_arc_cfg_lowering.pw; do
        coverage="/tmp/t_mid_buffer_truncate_$$_$(basename "$source" .pw).coverage"
        if ! "$PLEWC" --emit-mid-coverage "$source" >/tmp/t_mid_buffer_truncate_$$.ll 2>"$coverage"; then
            echo "FAIL mid-buffer-truncate(emit)"; exit 0
        fi
        if grep -q "name=shrinkThenKeep category=preflight:call:buffer" "$coverage"; then
            echo "FAIL mid-buffer-truncate(legacy)"; exit 0
        fi
    done
    echo "PASS mid-buffer-truncate"
' sh)
mbtpass=$(printf '%s\n' "$mid_buffer_truncate_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$mid_buffer_truncate_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

mid_buffer_eq_results=$(sh -c '
    source="tests/run/mid_buffer_eq_cfg_lowering.pw"
    coverage="/tmp/t_mid_buffer_eq_$$.coverage"
    if ! "$PLEWC" --emit-mid-coverage "$source" >/tmp/t_mid_buffer_eq_$$.ll 2>"$coverage"; then
        echo "FAIL mid-buffer-eq(emit)"; exit 0
    fi
    if grep -Eq "name=(isBytewise|same) category=preflight:call:buffer" "$coverage"; then
        echo "FAIL mid-buffer-eq(legacy)"
    else
        echo "PASS mid-buffer-eq"
    fi
' sh)
mbeqpass=$(printf '%s\n' "$mid_buffer_eq_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$mid_buffer_eq_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

# The largest self-host coverage class is an `inout` method receiver.  This
# existing generic-bound program reaches that ABI through a resolved trait
# method.  Keep the receiver admission fact separate from ordinary remaining
# Mid gaps, so this test turns green precisely when the receiver itself is a
# first-class Mid parameter place.
mid_inout_receiver_results=$(sh -c '
    source="tests/run/generic_method_bound_inout.pw"
    coverage="/tmp/t_mid_inout_receiver_$$.coverage"
    if ! "$PLEWC" --emit-mid-coverage "$source" >/tmp/t_mid_inout_receiver_$$.ll 2>"$coverage"; then
        echo "FAIL mid-inout-receiver(emit)"; exit 0
    fi
    if grep -q "category=eligibility:inout-receiver" "$coverage"; then
        echo "FAIL mid-inout-receiver(legacy)"
    else
        echo "PASS mid-inout-receiver"
    fi
' sh)
mirpass=$(printf '%s\n' "$mid_inout_receiver_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$mid_inout_receiver_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

# A normal method receiver is a guaranteed (+0) borrow, not a `Copy` merely
# because the ABI passes its representation by value. Runtime output alone
# cannot distinguish the two: copying Array storage makes the later append
# CoW, yet still prints 34. The literal 34 identifies this fixture's one
# source-level append call without pinning generated function ids; its
# enclosing function must contain no raw-buffer retain from either count()
# receiver. The old Mid lowering has two such retains and this is therefore a
# real red gate for the CallResolution passing contract.
mid_borrowed_read_receiver_results=$(
    source="tests/run/mid_borrowed_read_receiver_cfg_lowering.pw"
    ll="/tmp/t_mid_borrowed_read_receiver_$$.ll"
    if ! "$PLEWC" --emit-mid-coverage "$source" >"$ll" 2>/dev/null; then
        echo "FAIL mid-borrowed-read-receiver(emit)"; exit 0
    fi
    if awk '
        /^define / { inside=1; retain=0; marker=0 }
        inside && /call void @plew_rawbuf_retain/ { retain=1 }
        inside && /, i64 34\)/ { marker=1 }
        /^}/ {
            if (inside && marker) { seen=1; if (retain) bad=1 }
            inside=0
        }
        END { exit !(seen && !bad) }
    ' "$ll"; then
        echo "PASS mid-borrowed-read-receiver"
    else
        echo "FAIL mid-borrowed-read-receiver(owned-read)"
    fi
)
mbrrpass=$(printf '%s\n' "$mid_borrowed_read_receiver_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$mid_borrowed_read_receiver_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

# --- panic/ : valid code that compiles and links but must die by SIGABRT
#     (panic = abort, spec/11) with the expected panic text on stderr
#     (overflow / div-by-zero / OOB / assert). The checked-arithmetic floor
#     (plew_<w><Op>) is held to loud behaviour. 134 = 128 + SIGABRT. ---
panic_total=$(count_cases tests/panic/*.pw)
progress_start panic "$panic_total"
panic_results=$(printf '%s\n' tests/panic/*.pw | xargs -P "$JOBS" -n 1 sh -c '
    pw="$1"; [ -f "$pw" ] || exit 0
    name=$(basename "$pw" .pw)
    want=$(cat "tests/panic/$name.panic")
    ll="/tmp/t_panic_$name.ll"; bin="/tmp/t_panic_$name"; perr="/tmp/t_panic_$name.err"
    if ! "$PLEWC" "$pw" > "$ll" 2>/dev/null; then echo "FAIL panic/$name(reject)"; exit 0; fi
    if ! clang -w "$ll" "$PLEW_RT" $PLEW_LD -o "$bin" 2>/dev/null; then echo "FAIL panic/$name(link)"; exit 0; fi
    code=0
    # nested sh: the shell that reaps a SIGABRT child prints "Abort trap" on
    # ITS stderr — run the binary one shell deeper so that note is droppable
    # without touching the binary own stderr capture ($perr).
    sh -c "\"\$1\" >/dev/null 2>\"\$2\"" sh "$bin" "$perr" 2>/dev/null || code=$?
    if [ "$code" -eq 134 ] && grep -qF "$want" "$perr"; then echo "PASS panic/$name"; else echo "FAIL panic/$name(exit=$code)"; fi
' sh | progress_stream panic "$panic_total")
ppass=$(printf '%s\n' "$panic_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$panic_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

# --- reject/ : spec-invalid code the FRONT-END must reject with a DIAGNOSTIC
#     (clean nonzero exit). The shared frontend (incl. the backend-independent
#     acceptance pass verifyProgram) rejects these. A compiler death by signal
#     (>= 128, e.g. its own panic/abort) is a crash, not a rejection — FAIL. ---
reject_total=$(count_cases tests/reject/*.pw)
progress_start reject "$reject_total"
reject_results=$(printf '%s\n' tests/reject/*.pw | xargs -P "$JOBS" -n 1 sh -c '
    pw="$1"; [ -f "$pw" ] || exit 0
    name=$(basename "$pw" .pw)
    want="tests/reject/$name.err"
    perr="/tmp/t_reject_$name.err"
    code=0
    sh -c "\"\$PLEWC\" \"\$1\" >/dev/null 2>\"\$2\"" sh "$pw" "$perr" 2>/dev/null || code=$?
    if [ "$code" -eq 0 ]; then echo "FAIL reject/$name(accepted)"
    elif [ "$code" -ge 128 ]; then echo "FAIL reject/$name(crash=$code)"
    elif [ -f "$want" ] && ! grep -qF "$(cat "$want")" "$perr"; then echo "FAIL reject/$name(diagnostic)"
    else echo "PASS reject/$name"; fi
' sh | progress_stream reject "$reject_total")
rpass=$(printf '%s\n' "$reject_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$reject_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

# --- part/ : multi-file modules (each subdir's Main.pw stitches siblings via
#     `part`). Compile the root, run, compare to Main.out. ---
part_total=$(count_cases tests/part/*/Main.pw tests/part/Main.pw)
progress_start part "$part_total"
part_results=$(printf '%s\n' tests/part/*/Main.pw tests/part/Main.pw | xargs -P "$JOBS" -n 1 sh -c '
    main="$1"; [ -f "$main" ] || exit 0
    dir=$(dirname "$main")
    name=$(basename "$dir")
    ll="/tmp/t_part_$name.ll"; bin="/tmp/t_part_$name"
    if ! "$PLEWC" "$main" > "$ll" 2>/dev/null; then echo "FAIL part/$name(reject)"; exit 0; fi
    if ! clang -w "$ll" "$PLEW_RT" $PLEW_LD -o "$bin" 2>/dev/null; then echo "FAIL part/$name(link)"; exit 0; fi
    got=$("$bin" 2>/dev/null) || true
    if [ "$got" = "$(cat "$dir/Main.out")" ]; then echo "PASS part/$name"; else echo "FAIL part/$name"; fi
' sh | progress_stream part "$part_total")
qpass=$(printf '%s\n' "$part_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$part_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

# --- partreject/ : multi-file modules whose Main.pw the FRONT-END must reject —
#     cross-module rules that need real loaded sibling modules (e.g. a circular
#     import, which a single file cannot express). ---
partreject_total=$(count_cases tests/partreject/*/Main.pw)
progress_start partreject "$partreject_total"
pr_results=$(printf '%s\n' tests/partreject/*/Main.pw | xargs -P "$JOBS" -n 1 sh -c '
    main="$1"; [ -f "$main" ] || exit 0
    name=$(basename "$(dirname "$main")")
    want="$(dirname "$main")/Main.err"
    perr="/tmp/t_partreject_$name.err"
    code=0
    sh -c "\"\$PLEWC\" \"\$1\" >/dev/null 2>\"\$2\"" sh "$main" "$perr" 2>/dev/null || code=$?
    if [ "$code" -eq 0 ]; then echo "FAIL partreject/$name(accepted)"
    elif [ "$code" -ge 128 ]; then echo "FAIL partreject/$name(crash=$code)"
    elif [ -f "$want" ] && ! grep -qF "$(cat "$want")" "$perr"; then echo "FAIL partreject/$name(diagnostic)"
    else echo "PASS partreject/$name"; fi
' sh | progress_stream partreject "$partreject_total")
prpass=$(printf '%s\n' "$pr_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$pr_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

echo "----"
echo "plewc: run=$pass  midcoverage=$mcpass  midbuildreason=$mbrpass  midshortcircuit=$mscpass  midenummatch=$mempass  midpayloadlessenumreturn=$mperpass  midlocalassign=$mlapass  midindexplace=$mipass  midinout=$mirpass  midborrowedread=$mbrrpass  panic=$ppass  reject=$rpass  part=$qpass  partreject=$prpass  skip=$skip  fail=$fail"
[ -n "$failed" ] && echo "failing:$failed"
[ "$fail" -eq 0 ]
