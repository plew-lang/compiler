---
id: met-30q7
status: open
deps: []
links: []
created: 2026-10-27T20:57:28Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, generics, verification]
---
# Reconcile the single existential generic-call rejection with implicit opening


## Exact Oracle Conflict

Source-only audit at compiler9665094d/spec5bd65a5: `tests/fixtures/reject/any_is_not_static_bound_proof.pw` and .err assert rejection of one `any Marker` passed to needsStaticProof[T](value:T) where T:Marker, returning I64. Spec08 implicit opening explicitly admits one hidden Self for such a generic trait-bound call. This does not mean any Marker itself automatically conforms to Marker. The root currently tests the absence of a newly adopted opening facility; its expected rejection is not the adopted source-language oracle.

## Finite Disposition and Completion

Recover original hidden-Self/static-evidence intent; preserve `any_is_not_static_trait_evidence` with two independently boxed arguments sharing required T as a legitimate reject, plus no-bound generic boxing and invariant nested-container contrasts. Classify the one-box case as adopted-positive versus current-unimplemented-lane explicitly and assign any needed normative test/migration work without making an entire new opening implementation an audit prerequisite. Do not implement arbitrary any self-conformance, dynamic same-type rescue, container opening, overload reselection or new ownership features.

Check actual source-selection/witness/open-bridge ownership if implementing later; met-ia09 explicitly excludes general opening and is not reopened or silently expanded. General capability met-b2la and historical com-uutc are not blanket dependencies of this finite expectation disposition. Close with canonical source oracle, preserved contrasts and concrete follow-up. Audit executes and changes no compiler/tests/expectations; later repair uses TDD/scoped review. Evidence: meta/evidence/test-audit/scoped-reviews/frontend-batch-0007.json.
