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


