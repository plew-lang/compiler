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



## Scoped Test Audit Intake com-ti5b

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-001-033.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 1.

Row1: Exactly the immutable original row findings/qualifiers and receiving task current-feature subset; retain all originals and per-finding corrections. Preserve actual normal dispatcher results/status/case identity before accepting normal run/panic/reject/part evidence. This validator repair precedes affected gate reliance, not all source investigations. Required admission: com-9l3b.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
