---
id: com-tl9c
status: closed
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
formal fixed point and independent completion review are required. The user
removed below7s as this bounded completion exit on 2026-10-25; the actual
measured time is retained below.
Full final candidate gates remain G2. Any newly necessary semantics or unbounded
repair gets its own independently reviewed scope before widening this task.

## Implemented Boundary and Verification

Production dea2b38d adds owner-local SourceTransferFact(Function/Block/Loop),
private statement publication and immutable prepared lookup. Record chooses
identity under explicit block/loop/condition-barrier/closure contexts; Mid maps
the saved identity to the actual active result/CFG/cleanup destination. The old
nearest-loop authority and parallel loop arrays are removed. SemanticTry keeps
its existing owner/returnTerm for implicit Err returns; it needs no duplicate
direct-statement transfer row. Global return acceptance is unchanged.

Fixture d4749a85 source_transfer_targets checks real successful publication,
exact nested/sibling/closure identity and actual Mid missing/sibling mapping
rejection. Standard build20261024T142604-build-a5eb16, fresh sourcecheck and
native50/panic4/reject36 pass. The already registered sanitizer ownership inputs
cover the changed cleanup paths; this internal contract fixture adds no separate
runtime ownership path requiring another manifest entry.

36680385 removes only duplicate target-key lookup and eager successful-give
diagnostic offsets. Private registration retains all prior owner/kind/target
checks without rewriting existing rows. Measured successor090240dd513a530998c9025c43323f3243fc3206653e1aee1af657ed7503ddad
passes all-source checking and affected native20/panic4/reject36. Independent
review /root/body_receiver_completion_review verifies19 receipt references,
303 current focused inputs, all5929 formal inputs and saved successor identity.
The earlier90-case scope differs only in the two refined production files.

Both formal runs reach generation2 fixed point with unchanged inputs and exit0.
Initial20261024T143250-self-host-7c1dbf median7.267095s; refined
20261024T144321-self-host-f35ef5 median7.072914s (7.546383/7.072914/7.023181).
The original below7s exit was not met. Alternating identical-source old E3/new E4
medians7.071088/7.064008, identical LLVM, do not establish an E4-specific slowdown.
No further clear low-cost removal within this boundary was found; broader common
Mid performance investigation is needed, not weaker target validation. This is
not a claim that improvement is inherently impossible. The independent reviewer
recognized functional completion and the original performance stop. The revised
completion decision is recorded below; no G2/main/seed/carrier promotion follows.

Durable records: meta evidence/existing-feature-conformance/source-owner-facts/
phase3e-transfer-targets.json, phase3e-transfer-targets-initial-self-host.json,
phase3e-transfer-targets-cost-self-host.json and
phase3e-transfer-targets-same-source.json. All sessions are recovered.

## Completion Under the User-Approved Exit

On 2026-10-25 the user explicitly accepted completing 3E without satisfying
below7s. Only that bounded performance exit is removed; median **7.072914s**
and both original unmet performance records remain unchanged.

/root/body_receiver_completion_review reconciled the full E1–E4 contracts and
confirmed no other unfinished exit for this repair/E4. Existing functional and
fixed-point artifact admission remains applicable: production36680385, refined
60 controls,303 current focused inputs,5929 formal inputs and measured compiler
090240dd513a530998c9025c43323f3243fc3206653e1aee1af657ed7503ddad.
No production input changed and no extra execution is required for this
documentation-only admission. The repair is complete under the revised exit.
Final frozen-candidate gates and whole phase-three completion remain separate.
