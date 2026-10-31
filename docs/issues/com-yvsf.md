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



## Scoped Test Audit Intake com-ti5b

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-001-033.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 9.

Row9: Exactly the immutable original row findings/qualifiers and receiving task current-feature subset; retain all originals and per-finding corrections. Verify actual compiler/generated A-E sanitizer IR eligibility and access instrumentation before relying on standard ASan/LSan results. Preserve access-free definitions and distinguish nested JIT/runtime/native scope. Required admission: com-9l3b.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
