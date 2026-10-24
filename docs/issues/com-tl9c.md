---
id: com-tl9c
status: in_progress
deps: []
links: []
created: 2026-10-24T14:01:36Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-gnj9
tags: [frontend, mid, ownership, verification]
---
# Save source control transfer targets and consume them in Mid


## Boundary and Evidence

Required E4 paired repair, parent criteria2/3/5/6/8. About1–2 active human
days, independently reviewed by /root/associated_context_completion_review,
with gap identification from /root/body_receiver_completion_review.

At production771150e1 / contracts6e119a73, body-checking sections2/4/7 and
checked-body-storage completion handoff require saved explicit target identities.
SemanticExpressionCompletion stores owner+relative flow only. Mid Return reads
returnPlace, Give reads blockResult, break/continue choose currentLoop stack.
Existing positive executions are correct, but that is not evidence of the
adopted source target contract. Do not rewrite the design to certify this gap.

## Entry and Action

- Ir/Frontend/SourceFacts: owner-local statement SourceTransferFact side pool,
  tagged Function/Block/Loop target identity, private writer, immutable prepared
  lookup and required successful-publication validation. Do not enlarge every
  expression summary or change pure relative SourceCompletion composition.
- Record::recordParametricFunction, closure entry and recordBlockContents/Stmt:
  choose target once under explicit enclosing region state. Canonical source
  owner includes Closure(expression), globals and provided-body aliases; do not
  confuse synthetic closure body keys with function declaration indices.
  Preserve statement/value-block boundaries, while-condition loop barriers,
  closure isolation and failure/branch-state restoration.
- Mid block/while/for lowering: map saved source block/loop identity to active
  result home/CFG edges/cleanup scope. Source blocks need not map one-to-one to
  physical scopes. Return/Give/loop-exit consumers require prepared transfer and
  its exact owner/session/kind plus active enclosing target. Remove nearest-stack
  target selection as semantic authority; missing/foreign/sibling targets reject.
- Preserve existing source diagnostics for invalid break/continue/give/return.
  Do not publish absent targets or replace source errors with internal errors.
  Preserve statically valid analyzed-unreachable transfers and operand-first
  exits: if an operand exits first, do not emit the outer transfer.
- Diverging calls and empty match have no enclosing target; implicit Unit
  fallthrough is not a new explicit transfer. No syntax, Never, LLVM, general
  lifetime/rollback, ownership redesign or unsupported feature expansion.

## Exit

Producer -> owner-local success publication -> immutable target lookup -> actual
Mid edge/cleanup -> strict executable verification/LLVM is closed in one task.
Nested block/if/match give, nested loop break/continue, return across block/loop
and closure-local return preserve destinations and cleanup order.

Reuse give_exits_block, block_loop_completion, standalone_block_control/lifetime,
block_abandoned_result, conditional_move_continuations and while_condition_local_loops.
Keep outside-loop, while-condition and break_in_closure rejection. Add focused
internal missing/foreign/kind/same-owner sibling/nonenclosing mapping controls at
the actual reader without exposing a private payload writer merely for tests.

Fresh sourcecheck and native/cleanup controls, applicable ASan E registration,
formal fixed point/median below7s and independent completion review are required.
Full final candidate gates remain G2. Any newly necessary semantics or unbounded
repair gets its own independently reviewed scope before widening this task.
