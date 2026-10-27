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


