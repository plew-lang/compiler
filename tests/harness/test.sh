#!/bin/sh
# Language test suite for the self-hosted Plew compiler. Drives the `plewc`
# binary (LLVM backend) from the outside: plewc x.pw > x.ll, clang x.ll +
# runtime, run, compare stdout to the golden .out. Covers run/ (stdout),
# panic/ (must abort with the expected text), reject/ (front-end must reject —
# acceptance soundness, incl. the shared verifyProgram pass), and part/
# (multi-file modules). Metaprogramming (gen/) is in ./tests/harness/test-gen.sh.
#
# Tests run PLEW_TEST_JOBS-wide (default: all cores) via xargs -P: each worker
# is one test end-to-end (compile + link + run + compare) printing exactly one
# PASS/FAIL line, aggregated after the fan-out. Observable output (counters,
# failing list, exit code) is identical to the old serial runner.
#
# Prereq: ./scripts/build/bootstrap.sh  (-> plewc).
set -e
cd "$(dirname "$0")/../.."

LC="${LLVM_CONFIG:-llvm-config}"
command -v "$LC" >/dev/null 2>&1 || {
    [ -x /opt/homebrew/opt/llvm/bin/llvm-config ] && LC=/opt/homebrew/opt/llvm/bin/llvm-config
}
PLEWC="${PLEWC:-./bin/plewc}"
[ -x "$PLEWC" ] || { echo "run ./scripts/build/bootstrap.sh first" >&2; exit 1; }

# One runtime object per invocation, using the same clang/default O0 as links.
RUNTIME_DIR=$(mktemp -d "${TMPDIR:-/tmp}/plew-test-runtime.XXXXXX")
trap 'rm -rf "$RUNTIME_DIR"' EXIT
trap 'exit 129' HUP
trap 'exit 130' INT
trap 'exit 143' TERM
RT="$RUNTIME_DIR/runtime.c"
python3 ./scripts/support/watch-command.py -- "$PLEWC" --runtime > "$RT"
python3 ./scripts/support/watch-command.py -- clang -w -c "$RT" -o "$RUNTIME_DIR/runtime.o"

JOBS="${PLEW_TEST_JOBS:-$(sysctl -n hw.ncpu 2>/dev/null || nproc 2>/dev/null || echo 4)}"
PLEW_RT="$RUNTIME_DIR/runtime.o"
PLEW_LD="$("$LC" --ldflags)"
export PLEWC PLEW_RT PLEW_LD JOBS

# --- suite hygiene: every companion file must pair with a .pw and vice versa.
#     A rename/delete that leaves an orphan .out (or a .pw without its golden)
#     would otherwise silently drop that test from coverage — the runners skip
#     unpaired files without a word. ---
hygiene=""
for f in tests/fixtures/run/*.out tests/fixtures/run/*.in tests/fixtures/run/*.c tests/fixtures/run/*.ll.expect tests/fixtures/run/*.out.exact; do
    [ -f "$f" ] || continue
    case "$f" in
        *.out.exact) pw="${f%.out.exact}.pw" ;;
        *.ll.expect) pw="${f%.ll.expect}.pw" ;;
        *) pw="${f%.*}.pw" ;;
    esac
    [ -f "$pw" ] || hygiene="$hygiene orphan:$f"
done
for pw in tests/fixtures/run/*.pw; do
    [ -f "${pw%.pw}.out" ] || hygiene="$hygiene no-golden:$pw"
done
for f in tests/fixtures/panic/*.panic; do
    [ -f "$f" ] || continue
    [ -f "${f%.panic}.pw" ] || hygiene="$hygiene orphan:$f"
done
for pw in tests/fixtures/panic/*.pw; do
    [ -f "${pw%.pw}.panic" ] || hygiene="$hygiene no-golden:$pw"
done

# Verify that execution failures cannot pass a golden-output comparison.
python3 ./tests/tooling/test-runner-exit-status.py
python3 -B ./tests/tooling/test-normal-dispatch.py

# --- run/ : compile, link, run, compare stdout to the golden .out ---
run_results=$(sh ./tests/harness/case-phase.sh run)
pass=$(printf '%s\n' "$run_results" | grep -c '^PASS' || true)
fail=0; failed=""
for n in $hygiene; do
    fail=$((fail + 1)); failed="$failed $n"
done
for n in $(printf '%s\n' "$run_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done
skip=0

# Architecture, diagnostic, and intrinsic contracts retained by the test inventory.
for gate in \
    tests/compiler/architecture/test-generic-method-canonical-body.sh \
    tests/compiler/architecture/test-loader-no-value-parser-fallback.sh \
    tests/tooling/test-measure-self-compile-input-fingerprint.sh \
    tests/compiler/architecture/test-mid-capture-cell-ownership.sh \
    tests/compiler/codegen/test-mid-core-string-intrinsics.sh \
    tests/compiler/codegen/test-mid-ffi-intrinsics.sh \
    tests/compiler/architecture/test-semantic-closure-body-descriptor.sh \
    tests/compiler/architecture/test-syntax-direct-extern-builder.sh \
    tests/compiler/architecture/test-syntax-direct-impl-builder.sh \
    tests/tooling/test-trace-phase-progress.sh; do
    if sh "./$gate"; then
        :
    else
        fail=$((fail + 1)); failed="$failed $gate"
    fi
done

# Checked arithmetic and failure atomicity use bounded native allocation controls.
if python3 -B ./tests/compiler/codegen/test-buffer-capacity.py --compiler "$PLEWC" --llvm-config "$LC"; then
    :
else
    fail=$((fail + 1)); failed="$failed buffer-capacity"
fi

# Keep phase tracing composable with both coverage modes used for self-hosting.
if python3 -B ./tests/tooling/test-standalone-build.py; then
    :
else
    fail=$((fail + 1)); failed="$failed standalone-build"
fi

if python3 -B ./tests/tooling/test-direct-object.py --compiler "$PLEWC" --llvm-config "$LC"; then
    :
else
    fail=$((fail + 1)); failed="$failed direct-object"
fi

if LLVM_CONFIG="$LC" python3 -B ./tests/compiler/codegen/test-orc-native.py; then
    :
else
    fail=$((fail + 1)); failed="$failed orc-native"
fi

if python3 -B ./tests/tooling/test-check-command.py --compiler "$PLEWC"; then
    echo "PASS check-command"
else
    fail=$((fail + 1)); failed="$failed check-command"
fi

if python3 -B ./tests/tooling/test-match-diagnostics.py --compiler "$PLEWC"; then
    echo "PASS match-diagnostics"
else
    fail=$((fail + 1)); failed="$failed match-diagnostics"
fi

if python3 -B ./tests/tooling/test-unreachable-diagnostics.py --compiler "$PLEWC"; then
    echo "PASS unreachable-diagnostics"
else
    fail=$((fail + 1)); failed="$failed unreachable-diagnostics"
fi

if sh ./tests/tooling/test-cli-options.sh; then
    :
else
    fail=$((fail + 1)); failed="$failed cli-options"
fi

if PLEWC="$PLEWC" python3 -B ./tests/tooling/test-lazy-cli.py; then
    :
else
    fail=$((fail + 1)); failed="$failed lazy-cli"
fi

if sh ./tests/tooling/test-self-host-measurement.sh; then
    :
else
    fail=$((fail + 1)); failed="$failed self-host-measurement"
fi

if sh ./tests/compiler/architecture/test-final-call-evaluation-plan.sh; then
    :
else
    fail=$((fail + 1)); failed="$failed final-call-evaluation-plan"
fi

if sh ./tests/compiler/architecture/test-call-template-scalar-storage.sh; then
    :
else
    fail=$((fail + 1)); failed="$failed call-template-scalar-storage"
fi

# Call results consume the type of their frozen semantic call site.

# Inferred storage uses the frozen result, including scoped match payloads.

# Static view values must retain their type facet through Mid.

# Inherited fields retain their newtype declaration identity.

# Inherited calls use shared, demand-driven typed boundaries.
if sh ./tests/compiler/codegen/test-mid-newtype-adapters.sh; then
    :
else
    fail=$((fail + 1)); failed="$failed mid-newtype-adapters"
fi

# Loop patterns lower to ordinary owned elements and field bindings.

# Raw external symbols and bundled runtime targets retain distinct identities.

# Reference cell control preserves borrowed inputs and owned results.

# OS entropy has a declaration-owned closed runtime target.
if sh ./tests/compiler/codegen/test-mid-entropy.sh; then
    :
else
    fail=$((fail + 1)); failed="$failed mid-entropy"
fi

# Self field layout is selected without rewriting its nominal parameter type.

# A construction retains its nominal owner beside unrelated lexical binders.

# Synthetic deinitializers retain the declared receiver TypeTerm.

# Unit results must remain distinct from missing call-result type facts.

# Lifetime output alone must not pass through a legacy caller unnoticed.

# Heap-copy ownership tests must exercise Mid rather than legacy lowering.

# A receiverless call still owns a canonical `None` receiver row. The row is
# not an operand and must not become a synthetic move during verification.

# Read-only receivers accept constants under the same operand contract as
# ordinary borrowed arguments, without granting a writable or movable place.

# An `inout self` call must carry the writable receiver place through
# canonical Mid, not fall back to the AST emitter because its ABI is by
# pointer.

# Indexing a temporary's field keeps its owner in the ordinary Mid scope.

# A free call receiving an `inout` struct field must retain that precise
# writable place through Mid's call terminator, including from return position.

# A receiver reached through field then index projections must preserve that
# exact writable place. The surrounding factory-heavy main is intentionally
# outside this gate; only the isolated mutating helper is the Mid boundary.

if sh ./tests/compiler/codegen/test-mid-strong-cell.sh; then
    :
else
    fail=$((fail + 1)); failed="$failed mid-strong-cell"
fi

if sh ./tests/compiler/codegen/test-mid-reference-read.sh; then
    :
else
    fail=$((fail + 1)); failed="$failed mid-reference-read"
fi

if sh ./tests/compiler/codegen/test-mid-reference-write.sh; then
    :
else
    fail=$((fail + 1)); failed="$failed mid-reference-write"
fi

# Conversion runtime tests must not silently exercise a legacy boundary.

# A direct struct field store is physical Mid Place storage, not an index
# access/writeback. Keep its ownership drop/store path out of legacy lowering.

# Moving a unique value into a freshly constructed aggregate is an ordinary
# Mid ownership transfer, never a reason to fall back to legacy lowering.

# Global places are declaration-target addresses, not legacy seeded locals.
# Keep reads, mutable replacement, and global initializer provenance on the
# Mid migration gate once every consumer can interpret that root directly.

# Global initializers are executable source bodies.  They must use the same
# frozen Mid/call facts as functions rather than merely allowing functions to
# read a legacy-initialized global address.

# Mid must retain the semantic reason when an assignment target is not a
# physical place. This gate is source-structural while fresh candidates cannot
# yet collect the resulting coverage rows.
if python3 -B ./tests/compiler/architecture/test-frontend-input-boundary.py; then
    :
else
    fail=$((fail + 1)); failed="$failed frontend-input-boundary"
fi

if sh ./tests/compiler/architecture/test-mid-assign-diagnostics.sh; then
    :
else
    fail=$((fail + 1)); failed="$failed mid-assign-diagnostics"
fi
if sh ./tests/compiler/architecture/test-mid-operand-diagnostics.sh; then
    :
else
    fail=$((fail + 1)); failed="$failed mid-operand-diagnostics"
fi

# Entry and ordinary functions must both consume the frozen canonical body.
# This guards the architectural one-way boundary independently of fixture
# execution, which is temporarily unavailable for fresh WIP candidates.
if sh ./tests/compiler/codegen/test-mid-canonical-production.sh; then
    :
else
    fail=$((fail + 1)); failed="$failed mid-canonical-production"
fi

# Runtime output cannot reveal dead cleanup loads in unoptimized LLVM.
if python3 ./tests/compiler/codegen/test-mid-trivial-drop.py; then
    :
else
    fail=$((fail + 1)); failed="$failed mid-trivial-drop"
fi

# The compiler parser must not hide the old value-AST → freeze path behind the
# immutable syntax arena.  This is a structural complement to the runtime
# SyntaxFile accessor corpus.
if sh ./tests/compiler/architecture/test-syntax-direct-builder.sh; then
    :
else
    fail=$((fail + 1)); failed="$failed syntax-direct-builder"
fi

# Macro-facing value APIs are adapters over the same direct SyntaxFile parser;
# this prevents a second recursive-descent parser from surviving behind a
# compatible TopItemAst / ExprAst result.
if sh ./tests/compiler/architecture/test-syntax-value-materializer.sh; then
    :
else
    fail=$((fail + 1)); failed="$failed syntax-value-materializer"
fi

# The macro value parser is a public explicit boundary, not an ambient normal
# compiler dependency.  Keep its endpoints out of normal compiler imports so
# self-hosted generic codegen cannot root their bodies accidentally.
if sh ./tests/compiler/architecture/test-normal-compiler-no-macro-parser-root.sh; then
    :
else
    fail=$((fail + 1)); failed="$failed normal-compiler-no-macro-parser-root"
fi

# Frozen conversion facts must stay canonical all the way through LLVM
# lowering; a draft proof thaw here would reintroduce the migration bridge.
if sh ./tests/compiler/architecture/test-mid-canonical-conversion.sh; then
    :
else
    fail=$((fail + 1)); failed="$failed mid-canonical-conversion"
fi

# --- Mid migration coverage: `--emit-mid-coverage` is observational, while
if python3 ./tests/compiler/codegen/test-existential-mid-bodies.py; then
    :
else
    fail=$((fail + 1)); failed="$failed existential-mid-bodies"
fi

if python3 ./tests/compiler/codegen/test-final-await-facts.py; then
    :
else
    fail=$((fail + 1)); failed="$failed final-await-facts"
fi

if python3 ./tests/compiler/architecture/test-final-enum-ownership.py; then
    :
else
    fail=$((fail + 1)); failed="$failed final-enum-ownership"
fi

if python3 ./tests/compiler/codegen/test-bounds-lowering.py; then
    :
else
    fail=$((fail + 1)); failed="$failed bounds-lowering"
fi

if python3 ./tests/compiler/codegen/test-expose.py; then
    :
else
    fail=$((fail + 1)); failed="$failed expose"
fi

if python3 ./tests/compiler/codegen/test-value-abi.py; then
    :
else
    fail=$((fail + 1)); failed="$failed value-abi"
fi

if python3 ./tests/compiler/codegen/test-closure-environment-mid.py; then
    :
else
    fail=$((fail + 1)); failed="$failed closure-environment-mid"
fi

# `--require-mid` is the fail-closed gate over exactly the same frozen body
# instances.  This deliberately does not pin a permanent legacy fallback: as
# the corpus reaches zero coverage the expected gate result changes from 1 to
# 0, but disagreement or unstructured output is always a failure.
mid_coverage_results=$(python3 ./tests/compiler/codegen/test-mid-coverage.py || echo "FAIL mid-coverage")
mcpass=$(printf '%s\n' "$mid_coverage_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$mid_coverage_results" | sed -n 's/^FAIL //p'); do
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
    source="tests/fixtures/run/mid_borrowed_read_receiver_cfg_lowering.pw"
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
panic_results=$(sh ./tests/harness/case-phase.sh panic)
ppass=$(printf '%s\n' "$panic_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$panic_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

# --- reject/ : spec-invalid code the FRONT-END must reject with a DIAGNOSTIC
#     (clean nonzero exit). The shared frontend (incl. the backend-independent
#     acceptance pass verifyProgram) rejects these. A compiler death by signal
#     (>= 128, e.g. its own panic/abort) is a crash, not a rejection — FAIL. ---
reject_results=$(sh ./tests/harness/case-phase.sh reject)
rpass=$(printf '%s\n' "$reject_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$reject_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

# --- part/ : multi-file modules (each subdir's Main.pw stitches siblings via
#     `part`). Compile the root, run, compare to Main.out. ---
part_results=$(sh ./tests/harness/case-phase.sh part)
qpass=$(printf '%s\n' "$part_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$part_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

# --- partreject/ : multi-file modules whose Main.pw the FRONT-END must reject —
#     cross-module rules that need real loaded sibling modules (e.g. a circular
#     import, which a single file cannot express). ---
pr_results=$(sh ./tests/harness/case-phase.sh partreject)
prpass=$(printf '%s\n' "$pr_results" | grep -c '^PASS' || true)
for n in $(printf '%s\n' "$pr_results" | sed -n 's/^FAIL //p'); do
    fail=$((fail + 1)); failed="$failed $n"
done

echo "----"
echo "plewc: run=$pass  midcoverage=$mcpass  midborrowedread=$mbrrpass  panic=$ppass  reject=$rpass  part=$qpass  partreject=$prpass  skip=$skip  fail=$fail"
[ -n "$failed" ] && echo "failing:$failed"
[ "$fail" -eq 0 ]
