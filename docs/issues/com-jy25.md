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


