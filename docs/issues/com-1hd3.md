---
id: com-1hd3
status: in_progress
deps: []
links: []
created: 2026-11-09T08:54:16Z
type: task
priority: 1
assignee: Koji Murata
parent: com-amjl
tags: [frontend, generics, verification]
---
# Connect retained free signatures to call and body descriptors

## Guarantee and Finite Work

Registered free-function annotations must reach selected-call ABI types and BodySignature through exact saved parameter/result slots and the original constraints-bearing InstanceEnvironment. readAdmittedSignatureRoot currently has no production caller; groundedSelectedCalleeReturn/ParameterTypes and recordFinalCallableSignature independently ground declaration terms.

Implement one shared signature-consumption endpoint, consume it at actual call/body publication, preserve body-type result recording/layout scans, and remove the competing source re-query for this registered free path. A missing admitted slot/recipe/proof is Err, never a fallback. Keep synthetic/default helpers and non-free signatures explicitly separate. Preserve async Promise versus logical body result and explicit/omitted Unit without re-substituting caller replacements or proof outputs.

## Required Scenarios

- Sync generic/nested projection parameter and result, repeated identical terms at different slots, actual final-call/BodySignature agreement and native value.
- Missing/foreign proof, constraints, owner/slot and wrong output reject even when a conformance remains searchable; valid recovery restores request state.
- Async annotated/omitted result, explicit/omitted Unit, default-argument helper and no-view free function remain valid in their existing representations.
- Both lowering adapters and check/AOT/lazy consumers use the same retained endpoint; supported gen applicability is recorded, not assumed.

## Verification and Completion

Follow the parent [contract and closure rules](com-amjl.md#contract-and-closure) and task-start TDD. Confirm the actual old-candidate RED for new behavior, preserve valid controls, then build a fresh candidate and test the real source-to-final-consumer path. Pure refactors use existing GREEN. Record exact inputs/carrier, diagnostic origin, meaningful assertions, applicable modes, removed competing authorities and independent neutral review. Do not close from a table/check/helper-only result. Existing unsupported surfaces must retain their actual diagnostic and be recorded, not silently counted as acceptance.

No new specification or general solver/SCC/unique/opening feature, API-wide authority extraction, main/seed promotion or whole-suite/ASan certification is included. Shared API names alone do not create whole-task prerequisites. Whole-program fixed-point/performance/full-suite gates remain with met-si6j; parent closure still requires the complete original guarantee map.

## Current Finite Implementation and Evidence

[Saved RED/GREEN, fresh controls and limits](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-free-signature-consumers.json)
record the old-source call-parameter/result/body consumers recovering absent
constraints (three targeted native REDs), followed by the shared private retained
signature endpoint. Registered free signatures require admission even when empty;
non-free/synthetic declarations stay on their separate existing path. Actual body
publication reads saved slots before type caches, records type-result mappings
and scans layouts. Async logical result extraction preserves the existing Promise
shape; supported default/Unit behavior is unchanged.

Build20261109T092204-build-8c4823 passes. Its saved candidate passes final12 internal
cases and56 existing signature/recipe/bound/async controls, with invariant inputs.
The new public program passes check, AOT/native and lazy, as does its old-candidate
baseline. Internal finalCalls requires seven actual signature forms and compares
call/body parameter/result types, saved type-result mappings and async payloads.
The independent review accepts source responsibilities, build/public results and
final12, including exact current179source/candidate correspondence. Preservation56 and its raw/input reconciliation are also accepted; final aggregate and mode reconciliation remain pending.

The late legacy adapter control uses direct primitive projection after manual
lowering; the ordinary Syntax/public paths retain nested Box coverage. Its former
nominal Box setup omitted the loader's already-sealed identity phase and is not a
product RED. wrongOutput also has witness Self/bind inconsistency, so no output-only
isolation is claimed. missingProof is an existing node referencing an absent clause;
the trusted store's rejection of a Missing node is not consumer coverage. Initial
unsupported aggregate/generic async test setups were corrected within existing
limits, not treated as regressions or newly supported features.

Formal self-host20261109T094105-self-host-d01361 reached generation3 fixed point,
median7.999618s. Balanced same-source formal candidates (five each) measured old
6.937475s/new7.906643s; this is a confirmed regression, not repair difficulty.
An additional primitive/nominal/nested saved-reader allocation control has a real
native RED (stable-red2: unchanged children allocate a new type). The common
semantic child fold is being changed to preserve an unchanged node after comparing
all canonical child IDs; proof/occurrence checks remain in the reader. Build20261109T100329-build-eeb617 passed; independent review accepted the fold and
recommended preserving the old out-of-range-ref rejection. That explicit guard
is included in passed build20261109T100909-build-632602. The retained
[regression/fold evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-free-signature-identity-fold.json) distinguishes both source snapshots. The final identity candidate passes fresh13 (including stableChildren), existing56,
public check/AOT/lazy plus the refusal control. Old and new candidates both compile
and execute the existing helperboundary generator; its real free helper returns
identical expected generated source. Formal recovery run20261109T101928-self-host-f3b5ef
is active; final performance and independent closure reconciliation remain pending.
This child remains in_progress. No full-suite/ASan or parent/goal closure is claimed.
