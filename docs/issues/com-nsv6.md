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
