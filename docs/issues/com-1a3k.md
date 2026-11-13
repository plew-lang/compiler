---
id: com-1a3k
status: closed
deps: []
links: []
created: 2026-11-09T08:54:17Z
type: task
priority: 1
assignee: Koji Murata
parent: com-amjl
tags: [frontend, generics, verification]
---
# Repair authorized projection fixtures while preserving their graph oracles

## Guarantee and Finite Work

Repair only the two previously user-authorized success setups: inherited_projection_identity.pw and trait_subject_cycle_parameterized_projection_distinct_allowed.pw. Inspect introducing intent/com-x95z evidence first. A whole-source success fixture may not require an unpromised Parent[String] or unconstrained T#Projection.

Retain exact graph/equality assertions at the correct internal boundary when valid source cannot express the structural setup, with a valid source companion. Do not weaken assertions, delete coverage, introduce conditional trait-to-trait where support, or repurpose projection-growth/binder rejection tests into unrelated missing-bound tests.

## Required Scenarios

- Diamond equality, foreign receiver distinction, missing symbolic query, Conflict versus known Unit and no-body-discovery assertions stay executed.
- Distinct parameterized projections do not manufacture a cycle; preserve original structural comparison and valid whole-source admission.
- Growth/binder rejection controls still reach the structural graph oracle; separately assert source admission diagnostics/order if setup changes.
- Fresh targeted native/check/lazy as applicable, expected-result provenance and independent review of test intent and sensitivity.

## Verification and Completion

Follow the parent [contract and closure rules](com-amjl.md#contract-and-closure) and task-start TDD. Confirm the actual old-candidate RED for new behavior, preserve valid controls, then build a fresh candidate and test the real source-to-final-consumer path. Pure refactors use existing GREEN. Record exact inputs/carrier, diagnostic origin, meaningful assertions, applicable modes, removed competing authorities and independent neutral review. Do not close from a table/check/helper-only result. Existing unsupported surfaces must retain their actual diagnostic and be recorded, not silently counted as acceptance.

No new specification or general solver/SCC/unique/opening feature, API-wide authority extraction, main/seed promotion or whole-suite/ASan certification is included. Shared API names alone do not create whole-task prerequisites. Whole-program fixed-point/performance/full-suite gates remain with met-si6j; parent closure still requires the complete original guarantee map.

## Outcome

The [inherited-signature checkpoint](com-30u1.md#inherited-signature-equation-checkpoint)
records the original declaration failure and the repaired setup. The missing
instance remains a raw comparison, alongside the diamond equalities, foreign
receiver, Conflict, known Unit and empty executable worklist assertions.

The parameterized cycle fixture now forms all three projections from explicit
conformances. Its original symbolic edge shapes remain in the native
`TraitCycleCanonicalIdentity` probe. Different positional arguments pass;
the same arguments close a cycle even when independently lowered on distinct
binders. This pair detects both dropped positional children and equality by
arena identity.

Verified on development carrier `83b5baf2956f` from build
`20261113T131109-build-325dd4`. Both corrected source fixtures pass
check, JIT and linked native with their existing golden output. The two
new graph scenarios and existing same/distinct controls pass native with
exact output and empty stderr. Projection growth, binder duplication and
the exact-cycle contrast reject with exit 1 and their existing structural
diagnostics in check and JIT. The baselined compiler's acceptance of
unpromised impl target projections remains tracked by [com-3jtd](com-3jtd.md).

Independent review against `5cd03791` confirmed the source setups and
unchanged diagnostic producers. The review identified that the paired
graph tests initially reused the same binder and terms. Re-review
confirmed that independently allocated terms and distinct binders now
exercise semantic positional identity; the updated pair was rerun.
