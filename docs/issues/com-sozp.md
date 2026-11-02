---
id: com-sozp
status: open
deps: []
links: []
created: 2026-11-02T21:30:20Z
type: bug
priority: 2
assignee: Koji Murata
tags: [diagnostics, verification]
---
# Reject failed Mid rewrites and forbidden executable terminators at their stage

## Contract and audit evidence

Follow the existing diagnostics, verification and owning stage contracts. Origin: [com-6lza](com-6lza.md), [finite assignment evidence](../../../evidence/compiler-failure-audit/correction-owner-candidates.json), unit `MID-STAGE-ADMISSION`. Audit findings are source-backed unless the referenced evidence explicitly records executed controls; no product repair or GREEN is implied.

## Ownership and finding

B060 false/None+body0 can form intermediate Ok; B062 direct executable verifier accepts minimal raw Open. Correct returned failure and stage validation without assuming ordinary source or full pipeline false success.

Finding references: MID-INSTANTIATION-EMPTY-HANDLE-NONE-ERROR, MID-EXECUTABLE-OPEN-TERMINATOR-ADMISSION.

## Covered source boundary

- Instantiate1380/1388-1390/1406 and Statement700-736
- Prepare45-50/access1011-1012
- Verify814-1089/Types205-247/Structure60-67 Open stage predicate

## Guarantees and scenarios

- Deliberate unsupported statement/noncall false with otherwise valid raw fixture gives typed failure, never successful0 handle.
- Minimal one-block zero-local Open rejected by executable verifier; contrast Return Unit/Abort/Unreachable and explicitly intended earlier stage policy.
- Valid Prepare stage order/tokens unchanged; failed raw artifact is validator refusal, not new panic.

## Excluded

- No arbitrary mutable Comp resilience, normal-source miscompile claim or new executable opcodes.

## Completion

Inspect the pinned finding and current owner preconditions before implementation. Establish meaningful RED for the exact defect and preserved positive/boundary controls, then repair producer through final consumer and remove competing interpretation. Verify all returned exits/publication obligations in scope, run affected gates, obtain independent review, and record revisions/results. Do not close from added checks or audit assignment. No mass panic conversion, surviving-host recovery, changed public CLI code/format or unspecified syntax policy is authorized by this ticket; request any required decision before adoption.

Admission connections will be recorded after exact dependency/cycle review; creation alone does not complete audit intake.

