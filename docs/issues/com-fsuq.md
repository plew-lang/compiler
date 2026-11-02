---
id: com-fsuq
status: in_progress
deps: []
links: []
created: 2026-10-27T18:40:48Z
type: bug
priority: 1
assignee: Koji Murata
tags: [verification, tooling]
---
# Reject non-source failures in negative-test result classification

Prevent normal reject/partreject workers, the finite expose cases and ASan B checker cases below from reporting PASS for non-source compiler failures.

Confirmed audit evidence: evidence/test-audit/rejection-classification.json (meta) executes the actual worker bodies extracted from tests/harness/test.sh, with production supervisors and fixed compiler doubles. Without .err, silent exit 1 and a plewc internal-error diagnostic plus exit 1 both publish PASS for both phases. With a reason companion, unrelated text fails in the measured controls. No real compiler miscompile/rejection or individual wrong expectation is claimed.

Guarantee: a negative source test passes only for the intended class of compiler rejection; signals, timeout, silent non-source failures and internal failures must not be counted as success. Preserve valid source rejection, diagnostic substring checks, expected program panic semantics, worker aggregation/progress and source inputs.

Before changing code, independently inspect diagnostic/runner contracts and history. Add controlled-double RED cases that exercise the production worker, with/without companions, proper diagnostics, no diagnostic, internal failure, ordinary wrong exit and signal. Avoid an independent copy of worker classification. Find the responsible shared classification boundary rather than weakening expectations or filtering the offending inputs. If internal failure cannot be reliably distinguished by the available result contract, document the required diagnostic/exit boundary and seek an unresolved design decision instead of assuming a regex is sound.

Excluded: adding .err to all 427 cases, correcting each fixture expectation, compiler semantics changes, suite reduction, weakening sanitizer/watchdog checks, or claims about every other runner phase. Only the named expose and ASan B checker extensions below are additionally owned; other phase audits remain with com-e713/com-5zvv.

Acceptance: discriminating RED/GREEN controls plus affected production worker/runner checks; independent review of actual failure paths and source-result contract. Repair execution is separate from audit work; this issue has no dependency on audit closure and does not become an audit completion prerequisite.

Found by com-ouh2; source baseline tests/harness/test.sh SHA is in the evidence snapshot.


## Finite Expose Checker Extension

Batch0124 independently reads tests/compiler/codegen/test-expose.py in full. Its three negative branches require only nonzero status and the expected diagnostic substring: six shared expose_* rejection fixtures, four generated external ABI collisions and eight generated managed parameter/result cases. A result with exact intended diagnostic followed by signal(-6), or wrong ordinary status2, satisfies each conjunction. The six fixtures also have standard reject coverage; the generated twelve do not pass that worker. This is a concrete source-result classification gap, not a reproduced compiler crash or merely a missing diagnostic reason. Meta runtime-batch-0124.json and its review retain the source-backed counterexample.

Extend the shared classification investigation only to these18 negative invocations. Preserve all specific reason assertions, successful C/Plew/O0/O2/Clang ABI controls, optional ASan scope and callback/aggregate ABI exclusions. Distinguish clean intended source rejection from diagnostic-then-crash/wrong status/timeout; do not require a full C ABI matrix, treat an unrelated panic-template failure as expected ABI refusal, or tighten statuses by weakening diagnostics. Recover original intent and use controlled RED/GREEN on the actual checker path, then independently review. Current managed-return legacy panic setup is a separate source-lane migration qualification. No repair or actual compiler/program execution occurred during this audit.

## ASan B Failure-Domain Extension

Batch0130 separately audits the checker contract of tests/harness/asan-compile-corpus.sh B reject invocations and the actual diagnostic/supervisor channel. Status1 plus ^plewc: error: and no ASan report also accepts an internal Error1 as RAN. Actual ed4a4f9 introduced expected status/diagnostics and successful-completion counts; c72b1b6 tightened trace-only rejection without separating internal failure. Own this failure-domain boundary explicitly, preserving valid source rejection, compiler instrumentation, all-input counts and existing statuses. Do not add per-fixture .err matching, require a source-oracle redesign, weaken sanitizers or assume another regex can distinguish domains absent a sound channel. No current compiler memory defect or actual B execution was reproduced. Batch0123 remains instrumentation-envelope evidence only; it neither certifies source reasons nor previously owned this checker extension.

## Scoped Test Audit Intake com-5azh

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-067-098.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 89.

Row89: Preserve reasons/ABI positives/supervision/instrumentation/status. ASan B not source-oracle proof. No per-fixture err/all-runner scope or invented regex channel; unresolved failure channel needs explicit disposition. Actual normal reject/partreject, registered expose18 (6shared+4ABI+8managed) and standard ASan B source-rejection domains need sound failure classification. Internal/silent/wrong-status/diagnostic-then-signal must not become PASS; current scalar/pointer expose admission also affected. Required admission: com-9l3b, com-2o4w.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.


## Task-Start Scenarios

Inspect the original diagnostic, CLI and supervisor contracts/history before
changing classification. Exercise actual normal reject/partreject workers with
and without reason companions; all three expose negative invocation families;
and the actual ASan B corpus classifier. Controlled compilers cover successful
source rejection, accepted input, silent exit1, internal failure, wrong ordinary
status, diagnostic-then-signal, and timeout/supervisor failure. Retain intended
reason checks, valid acceptance controls, progress/aggregation, and sanitizer
rejection. Distinguish read/setup errors from the intended RED.

The test doubles isolate failure classification and do not certify source
semantics, compiler instrumentation or whole-suite success. If presentation has
already erased the failure domain, preserve evidence and request the required
result/diagnostic boundary decision rather than inventing a text heuristic.


## Investigation Checkpoint and Required Decision

At product baseline b3bfa3ea, the unregistered task-start checker
`tests/tooling/test-rejection-domains.py` exercises80 controlled cases through
actual production classifiers:32 false successes,48 preserved contrasts and0
unrecognized terminals/setup failures. The [RED](../../../evidence/rejection-domains/red.json)
and [independent channel review](../../../evidence/rejection-domains/channel-review.json)
retain source identity, direct outcomes, history and limits. The reviewer
independently reproduced the same results. Production classifiers and compiler
source have not changed; this task remains in_progress.

The missing boundary is structural. `Diag::CompileDiagnostic` holds only
severity/location/message. `PreparedProgram::programPreparationDiagnostic` and
`DeclarationProgram::declarationProgramDiagnostic` erase typed causes, while
`CompilerDiagnostics::reportProgramPreparationError` and Compiler CLI failures
report them with exit1. Even `DeclarationAccessError.Frontend` can contain
missing-function/closure invariant failures. Neither its variant name nor a
rendered prefix/location/substring proves source rejection. Supervisors retain
signal/timeout/status but cannot recover that erased domain.

Decision requested, not adopted:

1. Recommended: retain explicit failure kinds from producer to CLI; give source
   rejection exit1 and non-source failures a distinct ordinary status. Keep
   detailed causes internally, reason companions and existing sanitizer/supervisor
   protections. Do not infer kinds from wording or default unclassified errors
   to source rejection. Exact non-source codes need a documented mapping.
2. Alternative: retain the same explicit failure kinds but publish a structured
   terminal result channel and preserve broad exit compatibility. This adds an
   output/protocol surface and input/output handling to the consumers; no general
   diagnostic serialization is currently adopted.

Both require a producer-to-CLI transport decision rather than another negative
regex. [Rust's driver result adapter](https://doc.rust-lang.org/stable/nightly-rustc/rustc_driver_impl/fn.catch_with_exit_code.html)
is a reference for mapping returned failure to exit status; its exact status
policy is not automatically Plew's contract.

Before final repair certification, inventory all producers/conversions/terminal
adapters feeding these named consumers; do not tag all existing Frontend errors
as source. Complete actual runner integration and relevant positive/panic/ABI
controls. The current124/125 controls do not test real watchdog/error cleanup;
reuse those supervision controls or add them if the integration changes. Add an
isolated wrong-source-reason contrast when implementing the shared classifier.
These are remaining obligations of this task, not completed product guarantees.


## Decision-Independent Boundary Preparation

The [producer/conversion/terminal map](../../../evidence/rejection-domains/producer-boundaries.json)
records nine inspected boundary groups and all18 literal `CompileDiagnostic`
construction sites at the pinned inputs. It also indexes986 syntactic
`diagnosticAt` occurrences across81 files without claiming that their semantic
failure kinds have been classified. Direct construction includes input IO,
unsupported operations, coverage and ABI invariants, warnings and ordinary
source diagnostics; the shared constructor does not provide their distinction.
Legacy terminal helpers have only definitions/unused imports in the current
source scan; live CLI exits and retained failure services still need the chosen
transport. Object/JIT/callback neighbors are impact boundaries, not permission to
change application exit or callback ABI incidentally. Product repair and the
user's result-channel decision remain outstanding.
