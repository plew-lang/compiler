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


