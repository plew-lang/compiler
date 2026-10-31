---
id: com-pshx
status: open
deps: []
links: []
created: 2026-10-27T19:08:00Z
type: task
priority: 2
assignee: Koji Murata
tags: [mid, backend, verification]
---
# Reconcile module-wide Mid literals with their intended emission contracts

## Contract and Evidence

All 66 .ll.expect companions were read by scoped reviewer; 52 use generic mid:/mid./mid2:. Exact grep accepts unrelated body marker while intended target lacks Mid lowering. This is literal-presence evidence only, not all runtime fixtures invalid.

Contract: tests/README.md Test validity and coverage review and docs/design/verification.md. Scoped evidence: [RT-02](../../../evidence/test-audit/scoped-reviews/review-runtime.json); controlled driver observations and runtime controls reside alongside it. Audit did not modify compiler, fixtures, expectations or runners.

## Scope and Completion

For the fixed 66-companion set, recover original migration/mechanism intent and identify which claims need per-target/canonical emitted-body identity. Retain goldens and distinct ownership paths. Use unrelated-marker controls for target-specific claims; do not mechanically delete identical strings or require arbitrary LLVM spelling as language semantics.

Repair requires task-start TDD, fixed candidate/input identity, relevant actual consumer checks, scoped independent review and applicable gates. This is a separately owned follow-up, not a child or dependency of com-jno0 or its audits. No phase-three certification implied.



## Scoped Test Audit Intake com-ti5b

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-001-033.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 8.

Row8: Exactly the immutable original row findings/qualifiers and receiving task current-feature subset; retain all originals and per-finding corrections. The exact66 Mid companions need original mechanism/target attribution and unrelated-marker controls before claiming emitted-body coverage. Preserve valid output and distinct ownership paths; generic text presence is not a semantic or per-target proof. Required admission: com-an0b, com-h61e, com-9l3b.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
