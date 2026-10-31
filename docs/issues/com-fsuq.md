---
id: com-fsuq
status: open
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
