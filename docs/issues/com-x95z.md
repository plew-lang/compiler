---
id: com-x95z
status: closed
deps: []
links: []
created: 2026-10-27T22:54:20Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, generics, verification]
---
# Clarify projection evidence in selected cycle-graph fixture declarations


## Finite Question and Grounds

Audit baseline9665094d/spec5bd65a5, source-only. Exact roots:
reject/trait_subject_cycle_projection_argument_growth.pw/.err,
reject/trait_subject_cycle_projection_binder_duplicate.pw/.err, and
run/trait_subject_cycle_parameterized_projection_distinct_allowed.pw/.out.
Their generic receivers appear in T#Projection[Args].Item without authored
Projection bounds. The separate receiver_generic_exact negative has explicit
where clauses and is not part of this question.

spec09 permits symbolic projection terms in structural cycle/growth comparison
and says missing conformers/where satisfiability must not suppress declaration
consistency. That does not by itself certify full source admission: design
Types and Evidence separates justified symbolic terms from missing evidence.
The two specific growth companions do not pass on unrelated missing-bound errors;
the positive establishes structural distinctness only until admission is grounded.
Do not invent implicit conformance, infer a language exception from current
acceptance, or misreport this as an observed compiler defect.

## Deliverables and Completion

Recover actual introducing purposes and the canonical projection well-formedness
contract for impl-head pattern terms versus ordinary body/signature projections.
Trace graph-term construction, declaration proof admission and final source
success separately. Determine whether these exact terms are justified by an
adopted implication rule or require explicit bounds. Preserve nested projection
argument traversal, binder multiplicity despite constructor shrink, and distinct
trait-instance arguments with valid finite positive/reject contrasts. Obtain a
surface judgment only if existing rules leave the source meaning open; assign any
concrete test/compiler correction without doing it inside the audit.

Evidence: meta/evidence/test-audit/scoped-reviews/frontend-batch-0029.json and its
independent receipt. Source/output/runner were not edited or executed. This is a
separate finite investigation, not a prerequisite of audit completion or a claim
phase3 is complete; unread cycle and projection obligations remain in the audit.

## Explicit Inherited Projection Signature Evidence

Batch0052 adds exactly run/inherited_projection_identity.pw/.out. Embedded Diamond inherits Parent[I64] and Parent[Bool] but declares missing()->Self#Parent[String].Item without that premise. analyzeFrontendDeclarations normal route completes declarations, so its successful unwrap is more than raw parse/registration. Recover canonical ordinary-signature projection justification separately from the valid helper unresolved/no-fabricated-equality assertion. Preserve diamond inherited equalities, foreign receiver distinction, Conflict versus known term0, and no executable body discovery. Do not assert whole oracle invalid or invent implicit Parent[String] evidence from current success; reuse the finite ordinary-signature/impl-head evidence investigation.

## Scoped Test Audit Intake com-2kze

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-034-066.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 51.

Row51: Preserve growth/binder multiplicity/parameterized distinction/equalities/conflicts and unused declaration checks. Do not invent missing proof or special source exception; receiver_generic_exact already bound and excluded. com-x95z must reconcile symbolic projection graph terms versus actual source well-formedness and inherited projection premises. Saved associated evidence and full projection type/instance admission cannot rely on structural graph comparison as proof; input declaration-cycle gate is distinct. Required admission: met-ia09, met-6e6k, com-604k.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.

## Receiving Cycle-Input Repair

[met-c1pg](met-c1pg.md) depends on this finite investigation's projection
admission conclusion and valid graph/source oracles. Distinguish structural
comparison premises from ordinary/inherited-signature proof requirements before
that repair chooses its input predicate. Do not infer that all symbolic
projections are invalid or fabricate conformance. This dependency waits for
the bounded investigation and explicit follow-up assignment, not every later
product repair it assigns. No new source decision or product completion is
implied by the dependency.

## Finite Investigation Checkpoint — Not Closed

[Findings](../../../evidence/rejection-domains/projection-admission-investigation/README.md)
record all four introducing purposes, canonical obligations, exact current
checks/native embedding and independent neutral review. Structural graph terms
and full source signature admission have distinct prerequisites; no new surface
policy is needed. Graph checking must not solve receiver conformance before
structural cycle/growth comparison. met-c1pg keeps that repair and the two
negative growth oracles.

The positive graph setup's full-source success and inherited fixture's embedded
missing Parent[String] declaration are not justified by their valid helper/
structural purposes. Current ordinary unbounded T#P.Item signatures also pass.
A separate trait-view/projection-justification repair and the two named
success-setup corrections are assigned to com-amjl. Do not introduce
conditional trait-to-trait conformance while adjusting them (com-wfq2).

The user authorized follow-up issue creation including the clarified trait-view
contract and the two source-success setup corrections. [com-amjl](com-amjl.md)
owns common trait-view evidence admission and projection/final-consumer closure;
met-ia09, met-6e6k and com-604k depend on that repair. met-c1pg stays separate and
does not wait for its product GREEN. The assignment/completion review accepts investigated closure. No compiler/fixture changes, correction GREEN or
phase-three completion is claimed. Do not repeat the investigation on resume.

## Closure: Investigated

The finite investigation and receiving assignment are complete at source
51519401 (no product change from the recorded c63ffc07 investigation).
New com-amjl and the actual area/integration dependencies retain all source and
oracle corrections; met-c1pg retains raw graph admission/identity repair.
Independent neutral projection_view_task_review accepts scope, task granularity,
all four fixture purposes and the dependency graph. Its required stale-owner/
pending-assignment corrections were applied, including the final two-line
recheck. Exact adoption, review disposition and saved revision are in
[task-adoption.json](../../../evidence/rejection-domains/projection-admission-investigation/task-adoption.json).
Reason: investigated. No compiler/test repair, GREEN, area, phase-three or
integration completion is certified by closing this finite task.
