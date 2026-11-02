---
id: com-k3mn
status: open
deps: []
links: []
created: 2026-11-02T21:30:20Z
type: bug
priority: 2
assignee: Koji Murata
tags: [backend, verification]
---
# Preflight global initializer bodies before beginning LLVM emission

## Contract and audit evidence

Follow the existing diagnostics, verification and owning stage contracts. Origin: [com-6lza](com-6lza.md), [finite assignment evidence](../../../evidence/compiler-failure-audit/correction-owner-candidates.json), unit `GLOBAL-PREFLIGHT-ORDER`. Audit findings are source-backed unless the referenced evidence explicitly records executed controls; no product repair or GREEN is implied.

## Ownership and finding

Entry begins function body before global initializer Mid preflight, unlike main. Final Failure disposal does not satisfy prepared-input before emission contract.

Finding references: GLOBAL-INITIALIZER-PREFLIGHT-ORDER.

## Covered source boundary

- Backend/Entry67/83-97 versus156-172
- Locals48-55 beginFnBody
- Backend lower global initializer caller Failure

## Guarantees and scenarios

- Preflight failure leaves no body emission begun; successful initializer output unchanged.
- Empty/normal/missing prepared global body and main positive order; final failed module never published.

## Excluded

- No startup sort/effect closure redesign or asserted normal-source misordering.

## Completion

Inspect the pinned finding and current owner preconditions before implementation. Establish meaningful RED for the exact defect and preserved positive/boundary controls, then repair producer through final consumer and remove competing interpretation. Verify all returned exits/publication obligations in scope, run affected gates, obtain independent review, and record revisions/results. Do not close from added checks or audit assignment. No mass panic conversion, surviving-host recovery, changed public CLI code/format or unspecified syntax policy is authorized by this ticket; request any required decision before adoption.

Actual accepted admission connections are recorded in [dependency adoption](../../../evidence/compiler-failure-audit/dependency-adoption.json), after scope/cycle review. Product repair and gates remain outstanding.
