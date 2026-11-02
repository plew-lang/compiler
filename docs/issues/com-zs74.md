---
id: com-zs74
status: open
deps: []
links: []
created: 2026-11-02T21:30:20Z
type: bug
priority: 2
assignee: Koji Murata
tags: [backend, verification]
---
# Consume retained physical call preparation during LLVM emission

## Contract and audit evidence

Follow the existing diagnostics, verification and owning stage contracts. Origin: [com-6lza](com-6lza.md), [finite assignment evidence](../../../evidence/compiler-failure-audit/correction-owner-candidates.json), unit `PHYSICAL-PREFLIGHT-ONCE`. Audit findings are source-backed unless the referenced evidence explicitly records executed controls; no product repair or GREEN is implied.

## Ownership and finding

Required emitters rerun call preflight after prepareCanonicalMidForLlvm approved body. Retain and consume exact physical call result instead, preserving current instruction semantics and failure contract.

Finding references: LLVM-CALL-PREFLIGHT-REEXECUTION.

## Covered source boundary

- Backend/Llvm/Mid2607/2721-2733 prepare
- Mid1111/1219/1316/1483/1722 emitters and B053 dispatch

## Guarantees and scenarios

- Count actual required preflight on prepared path; emit consumes stored body/call decision with exact session/snapshot provenance.
- Unsupported/missing/child Err no AST fallback or failed success; representative valid direct/closure/interface/Buffer call outputs unchanged.

## Excluded

- No measured regression asserted, general optimization, new opcode or whole malformed table validation.

## Completion

Inspect the pinned finding and current owner preconditions before implementation. Establish meaningful RED for the exact defect and preserved positive/boundary controls, then repair producer through final consumer and remove competing interpretation. Verify all returned exits/publication obligations in scope, run affected gates, obtain independent review, and record revisions/results. Do not close from added checks or audit assignment. No mass panic conversion, surviving-host recovery, changed public CLI code/format or unspecified syntax policy is authorized by this ticket; request any required decision before adoption.

Admission connections will be recorded after exact dependency/cycle review; creation alone does not complete audit intake.

