---
id: com-gyup
status: open
deps: []
links: []
created: 2026-10-13T01:09:56Z
type: task
priority: 1
assignee: Koji Murata
tags: [frontend, ownership, verification]
---
# Reassess continuation-specific move-state joins

Retained R10-O1 / D5 investigation from the block-expression review. At source a8934f06 / compiler bb2e80e0, the frontend merged move state from exiting short-circuit RHS and condition-chain paths into the normal continuation, rejecting programs without a double consumption. The same branch expressed as an if control succeeded. This is historical evidence, not a fresh reproduction on the current implementation or retained candidate.

[Historical reproductions and results](../../../evidence/block-expression-tenth-review/README.md#r10-o1--p2短絡評価で脱出する経路のmove状態が正常経路へ混入する) and [paused remediation design](../../../agents/typechecking-design-review.md) retain inputs, detailed diagnosis and D5. The current [completion contract](../design/body-checking.md#4-blocks-branches-patterns-and-completion) rejects wholly source-diverging expressions in operand positions: the original `flag && { consume(...); return }` is therefore not automatically a valid positive fixture under the adopted specification. Reassess fixture intent and find specification-valid controls rather than restoring obsolete acceptance.

The required [ownership contract](../design/ownership-and-access.md) joins only paths reaching the same continuation. Carry normal/give/break/continue destinations explicitly; condition clauses need success/failure inputs and loops need backedge/exit state. Merely discarding RHS state can miss a move reaching a loop exit. Static checks of unreachable code remain required, without merging that state into executable continuations. Source completion and analytical reachability have distinct owners and cannot be guessed independently by syntax-specific move handlers.

This investigation belongs to the paused type-checking remediation, not authorization to resume implementation during design consolidation. R10-T1 and R10-T2 have separately recorded scoped fixes in [remediation evidence](../../../evidence/typechecking-remediation/README.md); that does not close D5 or the whole type-checking redesign.

## Acceptance Criteria

Audit current producer-to-final-consumer flow against the adopted specification. Build specification-valid positive controls and loop-exit use-after-move rejects, preserving diagnostic/static checking. Close with actual revision/scope and targeted results; either demonstrate that the contract already holds or repair the common transfer/join owner and remove superseded paths. Complete the applicable paused-work gates before claiming implementation integration.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Included bounded verification**.

Current specification-valid continuation joins: normal/give/return/break/continue destinations, loop exits and live versus checked-dead paths. Reassess old short-circuit tests against approved value-position rejection. No new value-bearing break or loop syntax.
