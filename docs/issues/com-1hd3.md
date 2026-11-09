---
id: com-1hd3
status: open
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
