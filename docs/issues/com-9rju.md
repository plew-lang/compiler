---
id: com-9rju
status: open
deps: []
links: []
created: 2026-10-27T22:18:20Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Reconcile the nested match-pattern rejection oracle

Source-only batch0021 audit at compiler9665094d/spec5bd65a5: exact tests/fixtures/reject/nested_pattern.pw comments assert a blanket single-level match pattern prohibition. Original807fbd05 adding diff intentionally guarded that historical parser limitation. Adopted spec03 explicitly describes nested assignment destructuring, while spec11 has no located blanket match prohibition. Current fixture also writes struct Point(...) instead of the documented Point {...} form and print(0) without numeric context. Its exit1-only runner cannot establish the claimed general prohibition. com-uutc retains nested destructuring as an uninspected combination, not a resolved semantic oracle.

Bounded investigation: recover that one root's original grammar/coverage purpose; compare adopted enum payload, struct/record and assignment patterns, using the corrected nested struct spelling and typed output against one-level bind-then-match and known malformed syntax. Trace current Syntax lowering, pattern representation, source check and final binding consumer only as needed to classify supported behavior versus missing implementation versus unresolved source meaning. Do not turn current rejection into a language prohibition. Preserve actual field binding/whole-field coverage and unreachable-arm checking. If existing authoritative rules do not settle acceptance, request the source decision before repair.

Deliverable: explicit canonical oracle or finite unresolved question, required test disposition and concrete repair owner if needed, with independent review. This separate follow-up is not a child/prerequisite of test audit; no compiler/test/expectation/runner repair, real compiler execution or feature completion is claimed. Unread audit obligations remain with com-e713. Evidence: meta/evidence/test-audit/scoped-reviews/frontend-batch-0021.json and independent receipt (pending reconciliation).


## Scoped Test Audit Intake com-2kze

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-034-066.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 47.

Row47: Do not assume supported or future solely from rejection. Finite investigation can yield evidenced unsupported disposition; unresolved classification must block affected pattern admission until then. com-9rju must determine the exact nested match-pattern source-admission path and saved binding/pattern facts using canonical syntax and typed controls. Historical single-level parser limit, Point(...) and print(0) setup cannot establish adopted nested-match prohibition. Required admission: met-acfl.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
