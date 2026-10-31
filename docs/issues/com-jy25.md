---
id: com-jy25
status: open
deps: []
links: []
created: 2026-10-27T19:08:00Z
type: task
priority: 2
assignee: Koji Murata
tags: [tooling, verification]
---
# Resolve stale alternating phase progress in nested worker supervision

## Contract and Evidence

Production process_watch.run controlled .2s idle probe: repeated a times out124, alternating a/b for .64s exits0 with 16 events, no new phase/counter. Outer run_gate tests reject interleaved old phases. Exact nested progress policy needs adjudication; legitimate repeated LLVM work must remain progress.

Contract: tests/README.md Test validity and coverage review and docs/design/verification.md. Scoped evidence: [driver-review-7](../../../evidence/test-audit/scoped-reviews/review-driver.json); controlled driver observations and runtime controls reside alongside it. Audit did not modify compiler, fixtures, expectations or runners.

## Scope and Completion

Trace producer events through process_watch and outer run_gate. Decide stale phase handling from agents/codex-execution contract, distinguish phase reentry with real new work, add nested alternating-old-phase/real counter/LLVM progress and cleanup controls. No deadline relaxation or heartbeat acceptance; seek judgment only if existing contract cannot settle semantics.

Repair requires task-start TDD, fixed candidate/input identity, relevant actual consumer checks, scoped independent review and applicable gates. This is a separately owned follow-up, not a child or dependency of com-jno0 or its audits. No phase-three certification implied.



## Observational Measurement Progress Consumer

Batch0132 adds scripts/diagnostics/measure-self-compile.sh record_line as a distinct finite consumer reached by test-measure-self-compile-input-fingerprint.sh and test-measure-self-compile-sampling.py. Every [trace-phase] line, even an identical stale line, resets last_progress and increments event_count. This conflicts with agents/codex-execution.md semantic-progress contract (source-backed; no real 60second stall executed). Reconcile duplicate/stale phase against actual advancing phase/counter and completion while retaining logs, exact exit, sampler draining/reaping and the unchanged60second deadline. Existing process_watch/outer run_gate controls remain complementary, not proof of this consumer; no all-watchdog matrix or compiler trace-policy change.

## Scoped Test Audit Intake com-ti5b

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-001-033.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 12.

Row12: Exactly the immutable original row findings/qualifiers and receiving task current-feature subset; retain all originals and per-finding corrections. Nested worker/measurement progress consumers must distinguish stale phase alternation from actual advancing counters/LLVM work before relying on supervised gates. Preserve60second deadline and cleanup, not a heartbeat exception. Required admission: com-p5um, com-9l3b.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
