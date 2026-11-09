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

Compiler **f65fa24e** connects saved free signature slots to actual selected-call
and body signatures before caches or ambient grounding can confer authority.
Non-free/synthetic declarations keep their separate path. Actual publication
retains type-result mappings and layout scans; async Promise/body results and
omitted/explicit Unit retain their existing representation.

[Original consumer RED/GREEN](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-free-signature-consumers.json),
[unchanged-child identity fold](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-free-signature-identity-fold.json)
and [signature-wide reader](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-free-signature-batch.json)
retain exact sources, candidates, scenarios and mode limits. The reader validates
one original declaration/environment, then interprets all requested slots with
one recipe-ID memo. Every slot still checks its authored occurrence and saved
proof; equal semantic terms do not confer authority. Empty slots also require
the exact environment. This added refusal has an actual old-source native RED,
followed by rejection and valid recovery in the final13 controls.

Build20261109T111958-build-a2b67a passed. Fresh13 internal,58 preservation,
public check/AOT/lazy and refusal, plus old/new actual helperboundary generator
execution and exact generated source passed. Independent review reconciled all
seven raw result hashes, input deltas,179source/build/candidate identities,
assertions and source responsibilities. A manual legacy adapter uses a primitive
projection; ordinary/public paths retain nested Box coverage. The wrongOutput
control also has witness Self/bind inconsistency, so output-only isolation is not
claimed. Unsupported generic/aggregate async setups are not passing coverage.

## Performance Stop and Resume Boundary

The final formal run **20261109T113003-self-host-195aa0** reaches generation2
fixed point. Samples8.307254/7.743194/7.720560s give median **7.743194s**.
Balanced final formal candidates on the same current source (five each) measure
old7.038477s/new7.716668s; all ten LLVM outputs match. The earlier exact restored
checkpoint is [preserved](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-free-signature-restored-checkpoint.json).
The diagnostic comparison does not replace the formal median.

The shared identity fold only partially recovered the introduced regression.
Three grounder-side trials were [discarded with exact patches](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-free-signature-discarded-trials.json).
Signature-wide batching measured7.846359s/7.810533s in the same development
pipeline (five each), insufficient recovery. Source/profile observations suggest
machine-code/inlining changes in an existing substitution hot path, but neither
the complete cause nor an unavoidable design cost is established.

Independent review found no clearly low-effort additional repair that preserves
evidence. The next investigation must correlate generated machine code with
actual call frequency, array/proof processing and reader work. Apply the user's
performance stop condition: median exceeds7s and recovery now needs investigation
beyond the tested local repairs. Do not resume a sibling to bypass this failure.

[Final fixed-point, matched timing and fresh candidate controls](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-free-signature-batch-final.json)
record the final candidate. This child remains in_progress; parent/goal, full
suites/ASan/G2 and main/seed/adopted-carrier promotion remain uncertified.
