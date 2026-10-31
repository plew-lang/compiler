---
id: com-nqiq
status: open
deps: []
links: []
created: 2026-10-27T19:08:00Z
type: task
priority: 2
assignee: Koji Murata
tags: [tooling, verification]
---
# Test measurement fingerprints against independent content identities

## Contract and Evidence

test-measure-self-compile-input-fingerprint.sh checks 64-hex shape and filenames, not independently expected content hashes. Constant valid-looking hash can satisfy these assertions; production hashing not shown broken.

Contract: tests/README.md Test validity and coverage review and docs/design/verification.md. Scoped evidence: [driver-review-5](../../../evidence/test-audit/scoped-reviews/review-driver.json); controlled driver observations and runtime controls reside alongside it. Audit did not modify compiler, fixtures, expectations or runners.

## Scope and Completion

Add independent expected content identities for identical input stability and changed source/manifest/lock-selected dependency. Preserve sampling assertions. Do not use helper under test as sole oracle, hash mutable scratch output, or alter measurement protocol.

Repair requires task-start TDD, fixed candidate/input identity, relevant actual consumer checks, scoped independent review and applicable gates. This is a separately owned follow-up, not a child or dependency of com-jno0 or its audits. No phase-three certification implied.



## Selected Observational Input Clarification

Batch0132 independently reconfirms the exact fingerprint checker gap. SOURCE selects the temporary src/_.pw, but measure-self-compile.sh cd selects compiler-cwd Plew.toml/Plew.lock, not the checker-created temporary package stubs. Derive expected content identities from the actual selected closure and one bounded changed-content contrast; retain sampling handshake and status/artifact checks. Source_tree64hex/name presence alone is not a content oracle. This is existing exact ownership, not a new task or demonstrated production-hashing defect.

## Scoped Test Audit Intake com-ti5b

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-001-033.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 11.

Row11: Exactly the immutable original row findings/qualifiers and receiving task current-feature subset; retain all originals and per-finding corrections. Measurement fingerprint assertions need independent actual selected input-content oracles before formal performance admission; do not alter the measurement protocol or trust helper-under-test alone. Required admission: com-p5um.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
