---
id: com-rb1s
status: open
deps: []
links: []
created: 2026-10-27T19:08:00Z
type: task
priority: 2
assignee: Koji Murata
tags: [backend, verification]
---
# Check zero-sized indirect value ABI lanes in regression assertions

## Contract and Evidence

Exact empty-type regex in test-value-abi.py catches direct %Empty parameter but misses ptr byval(%Empty). Isolated expression control only, not full checker or real compiler run.

Contract: tests/README.md Test validity and coverage review and docs/design/verification.md. Scoped evidence: [RT-03](../../../evidence/test-audit/scoped-reviews/review-runtime.json); controlled driver observations and runtime controls reside alongside it. Audit did not modify compiler, fixtures, expectations or runners.

## Scope and Completion

Ground omitted zero-sized value lane contract in private ABI design and original fixture. Add indirect/direct and caller/callee omission controls while allowing legitimate borrow/inout pointers. Keep native semantic output and existing aggregate argument assertions; no physical ABI redesign.

Repair requires task-start TDD, fixed candidate/input identity, relevant actual consumer checks, scoped independent review and applicable gates. This is a separately owned follow-up, not a child or dependency of com-jno0 or its audits. No phase-three certification implied.



## Scoped Test Audit Intake com-ti5b

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-001-033.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 7.

Row7: Exactly the immutable original row findings/qualifiers and receiving task current-feature subset; retain all originals and per-finding corrections. Zero-sized direct/indirect ABI omission must be checked at real caller/callee lanes; retain legitimate borrow/inout pointers and native semantic controls, not a physical ABI redesign. This is the private Plew Value ABI; the scalar/pointer-only C boundary is not the receiving contract. Required admission: com-h61e, com-9l3b.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
