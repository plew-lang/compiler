---
id: com-x95z
status: open
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
