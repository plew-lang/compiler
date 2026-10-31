---
id: com-nsv6
status: open
deps: []
links: []
created: 2026-10-27T23:09:22Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, generics, verification]
---
# Clarify associated-type bounds when naming existential types


## Finite Question and Grounds

Source-only audit9665094d/spec5bd65a5. Exact positive input
run/any_formation_unused_constraints.pw/.out names any Iterable[Item=I64,Iter=T]
without a T:Iterator bound, and Iter=I64 in another unused parameter. Standard
Iterable declares Iter:Iterator[Item=Item] (spec11/Core220-223). No value is boxed,
method invoked or protocol executed; the empty golden only observes acceptance.

spec08 requires complete positional/associated bindings and permits unavailable
members, including Self inputs or unsatisfied method where conditions, without
banning existential formation. This does not expressly establish whether the
associated binding itself may violate its declared associated-type bound.
Do not extrapolate the method rule, infer validity from current success, or
assert a compiler defect without settling this distinction.

## Deliverables and Completion

Recover originalcdc84749 purpose; derive the adopted well-formedness contract
for merely naming/retaining an existential versus injecting a concrete witness
and invoking its members. Compare exactly reject/any_for_unbound_cursor and
any_associated_bound_mismatch plus its generic counterpart (already reviewed as
finite contrasts), valid concrete and generic Iter bounds, and absent concrete
witness versus contradictory associated output guarantees. Determine the source
oracle from existing decisions or obtain a focused surface judgment if still
open. Preserve declaration-only versus demanded-protocol checks and assign any
finite spec/test/compiler correction; do not change source in this audit.

Evidence: meta/evidence/test-audit/scoped-reviews/frontend-batch-0034.json and
its independent receipt. No actual compiler, program, sanitizer or performance
run. This is an independent finite investigation, not an audit-completion
prerequisite, source choice, repaired API or phase3 certification.

## Scoped Test Audit Intake com-2kze

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-034-066.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 53.

Row53: Keep missing premise, valid bound, contradictory guarantee and absent concrete witness distinct. No general opening implementation or new rule selected; finite unknown blocks affected formation/type admission. com-nsv6 investigates unused any Iterable associated binding T/I64 against Iter:Iterator declaration requirements. Naming/formation consistency is not established by method-unavailability or absence of invocation. Required admission: met-ia09, met-6e6k.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
