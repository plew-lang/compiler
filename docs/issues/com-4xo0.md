---
id: com-4xo0
status: open
deps: []
links: []
created: 2026-11-02T21:30:20Z
type: bug
priority: 2
assignee: Koji Murata
tags: [diagnostics, verification]
---
# Restore nested LLVM helper context on every returned error

## Contract and audit evidence

Follow the existing diagnostics, verification and owning stage contracts. Origin: [com-6lza](com-6lza.md), [finite assignment evidence](../../../evidence/compiler-failure-audit/correction-owner-candidates.json), unit `LLVM-TEMP-CONTEXT`. Audit findings are source-backed unless the referenced evidence explicitly records executed controls; no product repair or GREEN is implied.

## Ownership and finding

B048 confirms saved insertion block/curFn/ambientPermit success-only restoration in Any and Ambient helpers; a discarded fresh module is different from the nested API temporary-state contract.

Finding references: LLVM-HELPER-ERROR-EMISSION-CONTEXT-RESTORATION.

## Covered source boundary

- Backend/Llvm/Any.buildAnyCopyThunk/buildAnyDropThunk102-153
- Backend/Llvm/Ambient.midAmbientBeginCall/midCanonicalEmitCall96-175
- outer Backend returned Failure disposal contrast

## Guarantees and scenarios

- Controlled nested retain/drop/place/runtime declaration Err restores prior insertion/function/permit and original diagnostic.
- Recursive vtable reservation and ordinary nested helpers preserve valid physical cache prefix; outer failed module disposed without publication.

## Excluded

- No compiler live runtime lock unwinding, rollback of canonical declarations or arbitrary failed raw LLVM reuse guarantee.

## Completion

Inspect the pinned finding and current owner preconditions before implementation. Establish meaningful RED for the exact defect and preserved positive/boundary controls, then repair producer through final consumer and remove competing interpretation. Verify all returned exits/publication obligations in scope, run affected gates, obtain independent review, and record revisions/results. Do not close from added checks or audit assignment. No mass panic conversion, surviving-host recovery, changed public CLI code/format or unspecified syntax policy is authorized by this ticket; request any required decision before adoption.

Admission connections will be recorded after exact dependency/cycle review; creation alone does not complete audit intake.

