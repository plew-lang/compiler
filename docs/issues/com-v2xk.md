---
id: com-v2xk
status: closed
deps: [com-qehq]
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-ia09
tags: [frontend, verification]
---
# Verify requirement clauses and inherited receivers reach the real callee environment

## Boundary

Phase 3B / B3. **Bounded closure verification.** Parent criteria: 3, 4, 8.
This is a bounded child of [met-ia09](met-ia09.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Codegen/Check/Bounds.pw`; `src/Codegen/Mono/Call.pw`; `src/Codegen/Mono/InterfaceEvidence.pw`; `src/Ir/InstanceConstraints.pw`.

Use B0 inherited/provided and static requirement rows. Reconcile instantiateRequirementCallConstraints, requirementCallConstraintEvidence/selectedMemberConstraintEvidence and environmentWithCallableConstraints with the retained requirement-to-implementation plan and method ParamId map. Follow both declaration and final worklists through inherited logical Self to physical body Self.

## Exit and Evidence

A finite clause-ID/ParamId/receiver map covers ordinary requirement, provided, two-layer inherited receiver and Self in trait arguments. Existing positive/corrupt/missing/foreign/replaced proof controls execute actual callee/Mid where applicable. No positional zipping, Declaration catch-all or ambient receiver lookup repairs a missing mapping. Dynamic proof admissibility itself belongs to B4.

Existing starting controls: `retained_provided_body_constraints`, `interface_boxing_conditions`, `existential_newtype_condition_witness`, `retained_associated_constraint_evidence`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.

## Closure Reconciliation

Source at a0e04c49 retains the following finite identity maps. B3 changes only
an additional binder-renaming regression fixture; it does not add another
proof producer or a declaration-mode fallback.

| Edge | Saved identity and interpreter | Final consumer |
| --- | --- | --- |
| Public requirement to implementation | Check/Bounds conformance method preparation publishes RequirementBoundEvidence with original clause ID and ConformanceMethodEvidence with implementation function, method ParamId alpha map and each implementation bound's derivation | instantiateRequirementCallConstraints validates selected implementation/conformance, reinterprets original public clause with selected logical Self and saved method map, then derives each original implementation bound by ID |
| Provided body | selectedMemberConstraintEvidence validates exact placement and semanticBodyOwner; instantiateSelectedCallConstraints replays saved source operands/conditions | environmentWithCallableConstraints binds the original body's declaration indices; bodyInstanceEnvironment retains placement proof and withLexicalSelfBinding |
| Declaration and execution requests | checkStaticMemberObligation and enqueueSelectedCallee share selectedCallConstraintEvidence and callable constraint admission | appendPreparedCallConstraintInstance and enqueuePreparedFinalBody consume the admitted environment; signature checking and body interning share it |
| Inherited logical/physical Self | inheritedBodyEnvironment requires exact immediate newtype edge and admitted source conditions, matches each original DeclarationBoundRef.Function and replays its proof for physical Self | both worklists recurse through the same interpreter; executable adapter's CallResolution targets the original body and Mid/LLVM consume its prepared signature |
| Boxing | selectExistentialMember retains the exact requirement-to-implementation plan; existentialImplementationEnvironment uses the same admission | final concrete body/adapters retain implementation bound identities; dynamic universal admissibility remains B4 |

Reordered/weaker bounds, requirement/implementation binder alpha-renaming,
provided/associated/supertrait clauses, two-layer inheritance and Self in trait
arguments have scoped controls. interface_boxing_conditions also exercises
missing/foreign/replaced plan/proof rejection and actual prepared Mid targets.
The final-candidate whole-suite gates remain G2a/G2b.

Fresh execution at test revision 262bc8bc passed: 20 native golden controls and
12 expected rejects, no internal diagnostics, session68530 exit zero.
Carrier/production source are unchanged from the successful B2 build, verified
against its saved input fingerprints. Evidence is
`meta/evidence/existing-feature-conformance/source-owner-facts/phase3b-callee-environments.json`.
Independent completion review passed. The new fixture's first attempt placed a `where`
clause on a separate line unsupported by the parser; that never-green fixture
was corrected without changing compiler behavior or existing expected outputs.

## Independent Completion Review

`/root/b3_completion_review` independently reviewed source/test revision
262bc8bc and the recorded reconciliation through 7e3f95f0. Verdict: complete
within B3, with no blocking finding or task-plan omission. The reviewer confirmed
original requirement/implementation clause identities, method ParamId alpha map,
provided placement/source separation, shared admission in both worklists,
two-layer inherited physical Self, and existing corruption/Mid controls.
No extra production correction was required. B4 universal admission, C6 general
descriptors and G2a/G2b final gates are not certified by this review.
