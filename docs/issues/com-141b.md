---
id: com-141b
status: open
deps: []
links: []
created: 2026-10-27T19:08:00Z
type: task
priority: 2
assignee: Koji Murata
tags: [backend, ownership, verification]
---
# Detect premature array release metadata reads in the IR checker

## Contract and Evidence

Production test-array-release-count.py passes synthetic IR with an extra entry-path pw_buffer_count because it only inspects arrrel.free blocks. Current backend count is final-owner-only; this is missing detection, not evidenced compiler regression.

Contract: tests/README.md Test validity and coverage review and docs/design/verification.md. Scoped evidence: [RT-01](../../../evidence/test-audit/scoped-reviews/review-runtime.json); controlled driver observations and runtime controls reside alongside it. Audit did not modify compiler, fixtures, expectations or runners.

## Scope and Completion

Verify the original optimization contract; reject premature/shared/nonfinal count reads while requiring exactly one count in each necessary final-owner cascade. Preserve legitimate unrelated buffer-count operations. Add valid CFG and bad-before-branch/selective controls; use actual checker and representative emitted IR without rewriting LLVM as a product fix.

Repair requires task-start TDD, fixed candidate/input identity, relevant actual consumer checks, scoped independent review and applicable gates. This is a separately owned follow-up, not a child or dependency of com-jno0 or its audits. No phase-three certification implied.



## Scoped Test Audit Intake com-ti5b

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-001-033.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 6.

Row6: Exactly the immutable original row findings/qualifiers and receiving task current-feature subset; retain all originals and per-finding corrections. Premature/shared/nonfinal Array release count reads require a real target/CFG-aware structural detector at backend acceptance, preserving legitimate unrelated count operations and exactly-needed final cascades. Required admission: com-h61e, com-9l3b.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
