---
id: com-kp0h
status: open
deps: []
links: []
created: 2026-10-27T19:08:00Z
type: bug
priority: 1
assignee: Koji Murata
tags: [driver, tooling, verification]
---
# Reject incomplete normal-suite dispatch results

## Contract and Evidence

Production run phase exits 0 with expected=1 pass=0 fail=0 when controlled xargs exits 1 before returning any case. Extracted unchanged phase and production progress helpers; not a full suite execution.

Contract: tests/README.md Test validity and coverage review and docs/design/verification.md. Scoped evidence: [driver-review-1](../../../evidence/test-audit/scoped-reviews/review-driver.json); controlled driver observations and runtime controls reside alongside it. Audit did not modify compiler, fixtures, expectations or runners.

## Scope and Completion

Preserve dispatcher status and reconcile expected versus returned case identities/counts for run/panic/reject/part/partreject. Test zero results, one missing result, worker interruption and complete positive/failing cases through the standard adapter. No fixture omission, timeout extension or summary-only workaround.

Repair requires task-start TDD, fixed candidate/input identity, relevant actual consumer checks, scoped independent review and applicable gates. This is a separately owned follow-up, not a child or dependency of com-jno0 or its audits. No phase-three certification implied.


