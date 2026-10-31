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



## Scoped Test Audit Intake com-ti5b

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-001-033.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 2.

Row2: Exactly the immutable original row findings/qualifiers and receiving task current-feature subset; retain all originals and per-finding corrections. Required part/gen goldens must be readable before comparing output; empty valid goldens remain valid. Apply at actual normal/gen admission without changing fixtures to mask IO failure. Required admission: com-9l3b, met-8b8w.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.

## Scoped Test Audit Intake com-5azh

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-067-098.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 95.

Row95: Preserve original snapshots and accepted correction, one repair count. Not kp0h terminal-result closure/tfxc selector/every output oracle; no duplicate reopening or individual fixture absence claim. met-py42 stays closed duplicate; actual com-mt7l owns part Main.out and gen App.out missing/unreadable required-file read failure with valid present-empty comparisons. Normal/gen adapters must propagate failure. Required admission: com-9l3b.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
