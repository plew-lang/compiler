---
id: com-v9ua
status: open
deps: []
links: []
created: 2026-10-28T01:49:32Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Reconcile custom Not witness source controls


## Finite Question and Evidence

Static audit batch0064 at compiler9665094d/spec5bd65a5 reads exactly
run/operator_unary.pw/.out. Its Money Neg branch is independently useful and
ordinary. Its Switch implements canonical Not with Output=Switch and calls
(!s).on. Spec12's general operator-trait rules (63/201) and its Bool-only Not
wording (195/405) do not clearly settle this custom witness. Independent
history read found both statements already in initial spec59bf8d20, and actual
fixture origin7b69f75b deliberately exercises custom unary dispatch; a24db4e9
moves it to canonical Core Not. Current acceptance/golden alone is not an
adopted permission or reproduced compiler defect.

## Deliverable and Guarantees

Recover canonical operator-domain intent and reconcile this one source oracle.
If records do not decide, obtain a focused surface judgment before repairing
source/spec. Do not silently ban user witnesses, relax Bool meaning, or preserve
old behavior as authority. Preserve Money Neg and the custom unary-dispatch
purpose in the eventual authorized form, with meaningful positive/refusal
contrasts and independent review after repair.

Supplemental controls read: run/{unary_operator_distinct_output,
final_callable_unary_primitive}.pw/.out and reject/{operator_unary_trait_identity,
tc_not_nonbool,tc_bitnot_bool}.pw. I32 without a Not conformance does not decide
whether a user-defined Not is allowed. The distinct-output control's custom
BitNot also requires care with spec405's integer wording; it is a finite related
contract contrast, not permission to widen to all unary operators or unread tests.
No new primary credit or missing-control claim for these supplemental reads.

Meta evidence/test-audit/scoped-reviews/frontend-batch-0064.json and independent
receipt own the static audit. No compiler/source/expected-output/runner changes
or actual compiler/native/ASan execution. Subsequent repair is outside the audit;
this task does not block completing the assigned audit obligations.

## Scoped Test Audit Intake com-2kze

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-034-066.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 64.

Row64: Preserve Money Neg/Bool Not and I32-without-Not rejection; BitNot integer wording related finite contrast. No new user witness permission, ban or source change until grounded. com-v9ua must reconcile spec12 general Not witness with Bool-only wording before selected unary operation and result type admission. Current custom Switch/BitNot acceptance and origin intent are insufficient. Required admission: met-ucze, met-6e6k.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
