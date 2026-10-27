---
id: com-ntm8
status: open
deps: []
links: []
created: 2026-10-27T19:08:00Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, diagnostics, verification]
---
# Strengthen scoped frontend rejection reasons and arity path controls

## Contract and Evidence

Scoped review F2 lists nine no-reason negatives; F3 generic_arity_construction also contains invalid annotation, so annotation rejection could mask construction handling; F4 test-check-command unused-type-error/global-conflict compare same generic errors across modes without intended reasons.

Contract: tests/README.md Test validity and coverage review and docs/design/verification.md. Scoped evidence: [F2,F3,F4](../../../evidence/test-audit/scoped-reviews/review-frontend.json); controlled driver observations and runtime controls reside alongside it. Audit did not modify compiler, fixtures, expectations or runners.

## Scope and Completion

For exactly F2 nine inputs, F3 construction/annotation pair and F4 two generated cases, verify original intent and isolate intended source rule with meaningful reason and neighboring positives. Preserve driver check/build agreement and no-execution checks. Separate shared classification com-fsuq; no arbitrary rewrite of every absent .err or new unsupported feature.

Repair requires task-start TDD, fixed candidate/input identity, relevant actual consumer checks, scoped independent review and applicable gates. This is a separately owned follow-up, not a child or dependency of com-jno0 or its audits. No phase-three certification implied.


