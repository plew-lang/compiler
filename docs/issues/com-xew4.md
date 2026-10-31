---
id: com-xew4
status: open
deps: []
links: []
created: 2026-10-27T19:08:00Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, runtime, verification]
---
# Reconcile constant arithmetic overflow rejection tests with panic semantics

## Contract and Evidence

reject/generic_body_const_range, lit_const_overflow, lit_typed_const_overflow each require rejection for 200+100 in U8 although both leaves fit. spec 02-basic-types integer overflow panics, optimization preserves execution and cannot promote runtime errors. Existing panic/overflow_add observes equivalent variable operands. Source-confirmed oracle conflict, no candidate execution.

Contract: tests/README.md Test validity and coverage review and docs/design/verification.md. Scoped evidence: [F1](../../../evidence/test-audit/scoped-reviews/review-frontend.json); controlled driver observations and runtime controls reside alongside it. Audit did not modify compiler, fixtures, expectations or runners.

## Scope and Completion

Check original creation intent (including 484b4a3f and pre-layout history): prevent silent wrap and preserve generic-body coverage. Reconcile all three expectations and current checkConstantIntegerRange implementation with spec, retaining out-of-range literal rejection, unexecuted branch, side-effect order and generic/non-generic panic controls. Do not infer validity from current compiler output or mechanically move tests before checking the mandatory-analysis distinction. Scope only these constant-result checks.

Repair requires task-start TDD, fixed candidate/input identity, relevant actual consumer checks, scoped independent review and applicable gates. This is a separately owned follow-up, not a child or dependency of com-jno0 or its audits. No phase-three certification implied.



## Explicit Heterogeneous Operator-RHS Overflow

Batch0022 adds reject/operator_hetero_nested_range.pw/.err as the fourth exact arithmetic-result oracle. Original7d064ca2 guarded witness Rhs=I8 contextual typing and silent truncation of100*3. Both literals fit I8; multiplication overflow is adopted runtime panic, unlike operator_hetero_rhs_range's single out-of-range literal200. Preserve selected Rhs/Output independence and overflow behavior when reconciling the compile-reject oracle. This is the same finite result-overflow issue, not a new operator typing rule.

## Scoped Test Audit Intake com-ti5b

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-001-033.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 4.

Row4: Exactly the immutable original row findings/qualifiers and receiving task current-feature subset; retain all originals and per-finding corrections. Constant arithmetic-result overflow oracle needs canonical source typing versus runtime panic reconciliation. Keep literal range rejection and generic/Rhs context, finite original intent and side-effect controls; no semantic rule chosen here. Required admission: met-6e6k.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
