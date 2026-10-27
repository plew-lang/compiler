---
id: com-mt7l
status: open
deps: []
links: []
created: 2026-10-27T19:08:00Z
type: bug
priority: 2
assignee: Koji Murata
tags: [driver, tooling, verification]
---
# Require part and generation golden files before comparing output

## Contract and Evidence

Unchanged part worker passes when Main.out is missing and app stdout empty; unchanged generation compare block also passes without App.out. Six controlled observations preserve stderr cat errors.

Contract: tests/README.md Test validity and coverage review and docs/design/verification.md. Scoped evidence: [driver-review-2](../../../evidence/test-audit/scoped-reviews/review-driver.json); controlled driver observations and runtime controls reside alongside it. Audit did not modify compiler, fixtures, expectations or runners.

## Scope and Completion

Reject missing/unreadable required part/gen goldens regardless of output. Preserve real empty goldens, exactness/newline policy and valid nonempty comparisons. Fail at owning hygiene/consumer boundary, not by changing fixtures or swallowing IO errors.

Repair requires task-start TDD, fixed candidate/input identity, relevant actual consumer checks, scoped independent review and applicable gates. This is a separately owned follow-up, not a child or dependency of com-jno0 or its audits. No phase-three certification implied.


