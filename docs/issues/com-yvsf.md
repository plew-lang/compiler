---
id: com-yvsf
status: open
deps: []
links: []
created: 2026-10-27T19:08:00Z
type: task
priority: 2
assignee: Koji Murata
tags: [backend, runtime, tooling, verification]
---
# Validate sanitizer eligibility on actual standard gate IR paths

## Contract and Evidence

Standard A-E invoke instrumentation but do not independently check actual Plew-produced IR eligibility/access checks. E intentional UAF is hand-authored sanitize_address, so its success alone cannot detect missing compiler --asan eligibility. Source-backed detection gap, not current broken instrumentation.

Contract: tests/README.md Test validity and coverage review and docs/design/verification.md. Scoped evidence: [RT-04](../../../evidence/test-audit/scoped-reviews/review-runtime.json); controlled driver observations and runtime controls reside alongside it. Audit did not modify compiler, fixtures, expectations or runners.

## Scope and Completion

Use bounded actual producer IR controls for compiler A/B/E and generated C/D, including no-op/missing-eligibility variants and clean counterparts. Avoid asserting access instrumentation for access-free definitions. Distinguish native bridge, runtime helpers and nested JIT scope. Preserve all gate members and LLVM compatibility, no sanitizer weakening.

Repair requires task-start TDD, fixed candidate/input identity, relevant actual consumer checks, scoped independent review and applicable gates. This is a separately owned follow-up, not a child or dependency of com-jno0 or its audits. No phase-three certification implied.


