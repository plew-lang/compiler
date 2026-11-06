---
id: com-fsuq
status: in_progress
deps: [com-6lza, com-yeua]
links: []
created: 2026-10-27T18:40:48Z
type: bug
priority: 1
assignee: Koji Murata
tags: [verification, tooling]
---
# Reject non-source failures in negative-test result classification

Require Source for normal reject/partreject, ASan B source cases and the ten source-invalid/conflicting-ABI expose controls. Require precise Limit for the eight managed-ABI capability controls. No lane may pass an unrelated failure, signal, timeout or sanitizer error.

Confirmed audit evidence: evidence/test-audit/rejection-classification.json (meta) executes the actual worker bodies extracted from tests/harness/test.sh, with production supervisors and fixed compiler doubles. Without .err, silent exit 1 and a plewc internal-error diagnostic plus exit 1 both publish PASS for both phases. With a reason companion, unrelated text fails in the measured controls. No real compiler miscompile/rejection or individual wrong expectation is claimed.

Guarantee: a negative source test passes only for the intended class of compiler rejection; signals, timeout, silent non-source failures and internal failures must not be counted as success. Preserve valid source rejection, diagnostic substring checks, expected program panic semantics, worker aggregation/progress and source inputs.

Before changing code, independently inspect diagnostic/runner contracts and history. Add controlled-double RED cases that exercise the production worker, with/without companions, proper diagnostics, no diagnostic, internal failure, ordinary wrong exit and signal. Avoid an independent copy of worker classification. Find the responsible shared classification boundary rather than weakening expectations or filtering the offending inputs. If internal failure cannot be reliably distinguished by the available result contract, document the required diagnostic/exit boundary and seek an unresolved design decision instead of assuming a regex is sound.

Excluded: adding .err to all 427 cases, correcting each fixture expectation, compiler semantics changes, suite reduction, weakening sanitizer/watchdog checks, or claims about every other runner phase. Only the named expose and ASan B checker extensions below are additionally owned; other phase audits remain with com-e713/com-5zvv.

Acceptance: discriminating RED/GREEN controls plus affected production worker/runner checks; independent review of actual failure paths and source-result contract. Repair execution is separate from the completed com-jno0 API/test audits and does not become their completion prerequisite. The distinct failure-policy investigation com-6lza is now an explicit prerequisite for this repair.

Found by com-ouh2; source baseline tests/harness/test.sh SHA is in the evidence snapshot.


## Finite Expose Checker Extension

Batch0124 independently reads tests/compiler/codegen/test-expose.py in full. Its three negative branches require only nonzero status and the expected diagnostic substring: six shared expose_* rejection fixtures, four generated external ABI collisions and eight generated managed parameter/result cases. A result with exact intended diagnostic followed by signal(-6), or wrong ordinary status2, satisfies each conjunction. The six fixtures also have standard reject coverage; the generated twelve do not pass that worker. This is a concrete source-result classification gap, not a reproduced compiler crash or merely a missing diagnostic reason. Meta runtime-batch-0124.json and its review retain the source-backed counterexample.

Extend the shared classification investigation only to these18 negative invocations. Preserve all specific reason assertions, successful C/Plew/O0/O2/Clang ABI controls, optional ASan scope and callback/aggregate ABI exclusions. Distinguish the intended Source rejection or precisely scoped Limit refusal from diagnostic-then-crash/wrong status/timeout; do not require a full C ABI matrix, treat an unrelated panic-template failure as expected ABI refusal, or tighten statuses by weakening diagnostics. Recover original intent and use controlled RED/GREEN on the actual checker path, then independently review. Current managed-return legacy panic setup is a separate source-lane migration qualification. No repair or actual compiler/program execution occurred during this audit.

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

The earlier CLI transport alternatives are not adopted. Following the user's
request, first complete the separate compiler-wide failure/panic audit
[com-6lza](com-6lza.md). It must assess lower-layer API tests, typed failure
retention and genuine invariant violations before choosing any public CLI
change. Neither distinct exit codes nor a structured output protocol is a
prerequisite by assumption. Source/IO/unsupported failures and validators of
malformed input must not be converted to panic merely by message matching.

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
change application exit or callback ABI incidentally. Product repair remains
outstanding; the failure-policy decision now follows com-6lza rather than an
isolated CLI-only choice.


## Audit Dependency and Resumption

com-6lza is a prerequisite investigation, not a parent or completion waiver.
Preserve this task's finite normal/expose/ASan B scope and existing RED. Once the
audit fixes the failure-policy boundary, attach the relevant finite producer/
transport repairs as actual prerequisites and complete these consumers' own
RED/GREEN, affected runner controls and independent completion review. Audit
completion or creation of follow-ups does not repair the32 false successes.

## Failure Audit Intake com-6lza

- `NEGATIVE-SOURCE-CONSUMERS`: semantic-rejection-consumers normal/expose/ASan B, existing80controls/32false-success. Current exact contract owns normal reject/partreject,18 expose negative calls and ASan B classifier. Sound producer channel must precede classifier repair; existing task expressly requires decision if unavailable.

Exact source scopes, controls and exclusions: [finite evidence](../../../evidence/compiler-failure-audit/correction-owner-candidates.json). Actual accepted admission edges: [dependency adoption](../../../evidence/compiler-failure-audit/dependency-adoption.json). Preserve this task's existing finite scope; audit intake is not repair, GREEN or permission to adopt unresolved panic/CLI policy.

## Authorized ABI Refusal Distinction

The user authorized checking the eight managed expose inputs against actual
backend support, correcting their tests, and recording future support. Preserve
all18 cases: six source-exposure restrictions and four conflicting external ABI
cases require Source; the eight Buffer[I64]/Ref[I64]/String/Array[I64] parameter
and result cases require precise Limit, normal exit1, intended ABI reason and
no sanitizer/supervisor failure. Ordinary reject/partreject and ASan B source
lanes remain Source-only. Do not accept arbitrary non-source failures or tag an
implementation restriction as a language prohibition. No skip or deletion.

The source-owned boolean support query first obtains checked final destruction;
its failed contract/ABI queries propagate their original domain, while its
explicit supported-subset false result produces Limit. Preserve supported scalar,
pointer, narrow integer/F32 and native O0/O2 controls. Controlled doubles must
cover Source/Limit cross-substitution, wrong reason, status/signal/timeout,
sanitizer and missing/malformed channel. The original 80 RED and subsequent88
controls remain historical evidence, not proof of this amended contract.

[met-2qbc](met-2qbc.md) owns future managed/unique C exposure eligibility and
ownership decisions, separately from repr(c) aggregate layout com-042v. Future
support is not a new prerequisite for phase three. Precise refusal and preserving
existing positive ABI behavior remain required here. The previous WIP channel
checkpoint is retained in meta; these tasks remain in_progress and unclosed.

## Scoped Exposure Classification Verification

The [approved finite correction](../../../evidence/rejection-domains/diagnostic-domain-implementation/managed-abi-correction.json)
records meaningful fixed-candidate RED, new build20261106T024018-build-0778a6
with unchanged inputs, actual Source10/Limit8 and C/Plew/Clang/O0/O2 positives,
96 controlled domain/status/reason contrasts and CLI regression7. Independent
managed_expose_refusal_review accepts this finite correction, including exact
old/new eight inputs and producer preconditions. No skip/deletion or new ABI
support. met-2qbc remains future work. This is not completion of this task:
remaining producer/classifier integration, runner controls and applicable gates
plus independent whole-task review still apply.
