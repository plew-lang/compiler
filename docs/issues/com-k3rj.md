---
id: com-k3rj
status: open
deps: []
links: []
created: 2026-11-02T21:30:20Z
type: bug
priority: 2
assignee: Koji Murata
tags: [frontend, ownership, verification]
---
# Restore temporary source verifier state on every returned error

## Contract and audit evidence

Follow the existing diagnostics, verification and owning stage contracts. Origin: [com-6lza](com-6lza.md), [finite assignment evidence](../../../evidence/compiler-failure-audit/correction-owner-candidates.json), unit `VERIFY-TEMP-CONTEXT`. Audit findings are source-backed unless the referenced evidence explicitly records executed controls; no product repair or GREEN is implied.

## Ownership and finding

B042/B043 confirm early Err before temporary closure/block/loop/return/local/branch restoration. Outer prepareLexicalBody fullcur/Failed guard prevents some publication but does not satisfy standalone helper all-exit contract.

Finding references: VERIFY-ERROR-TEMPORARY-CONTEXT-RESTORATION.

## Covered source boundary

- Codegen/Verify/Expr selected closure/block/ownership branch scopes
- Codegen/Verify/Stmt selected loop/pattern/assignment scopes
- verifyConditionValue all-exit positive contrast
- Resolve/Record2658/global176 Failed-owner guard

## Guarantees and scenarios

- Inject child Err inside each distinct temp scope; original error and caller cur/local/loop/return/move state restored.
- Positive nesting and source failure retention; legitimate persistent source/cache prefixes preserved; normal fresh product guard remains.

## Excluded

- No all verifier algorithm/soundness redesign, demonstrated surviving-session corruption or allcaller panic claim.

## Completion

Inspect the pinned finding and current owner preconditions before implementation. Establish meaningful RED for the exact defect and preserved positive/boundary controls, then repair producer through final consumer and remove competing interpretation. Verify all returned exits/publication obligations in scope, run affected gates, obtain independent review, and record revisions/results. Do not close from added checks or audit assignment. No mass panic conversion, surviving-host recovery, changed public CLI code/format or unspecified syntax policy is authorized by this ticket; request any required decision before adoption.

Actual accepted admission connections are recorded in [dependency adoption](../../../evidence/compiler-failure-audit/dependency-adoption.json), after scope/cycle review. Product repair and gates remain outstanding.
