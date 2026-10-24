---
id: com-2suv
status: in_progress
deps: [com-f0mq]
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: com-fuo8
tags: [frontend, verification]
---
# Verify block branch and short-circuit completion use one result authority

## Boundary

Phase 3E / E1. **Bounded semantic closure verification.** Parent criteria: 1, 2, 5, 6, 8.
This is a bounded child of [com-fuo8](com-fuo8.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/SourceCompletion.pw`; `src/Codegen/Resolve/Record.pw`; `src/Codegen/Check/Return.pw`.

Trace completionThen/Choice/Block/Loop and recordBlockContents for block/if/match/short-circuit. Check normal value joins, expected-type completion and exact give/return/break/continue targets using the committed owner facts. Do not infer type from unreachable give or the last AST statement.

## Exit and Evidence

A four-expression table identifies source producer and saved result/exit facts. Direct/wrapped scalar/array/closure and mixed normal/non-normal controls agree under the same available context. Incompatible expectations reject without rewriting committed types. No parallel last-statement/type reinference decides the migrated result.

Existing starting controls: `prepared_value_block_source_owner`, `give_exits_block`, `match_expr_diverge`, `block_branch_divergence`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.

## Four-expression Reconciliation

Initial audit at `ee736b1a` / runtime `9b4652a3`; the final repair and
functional scope are recorded below.

| Expression | Source producer / saved authority | Final consumer |
|---|---|---|
| Standalone block / sequence | `recordValueBlock` calls shared `recordBlockContents`, recording the directly belonging give in lexical scope and composing `completionThen` / `completionBlock`. It stores owner-local `SourceValueBlockFact` and the expression term/completion. | Mid reads admitted expression terms/recipes and `facts.valueBlock`, creates the result place and routes give through the block epilogue. Mono's executable scan requires the saved owner completion. |
| if / condition chain | `recordExpr` checks conditions then visits branch value blocks in source order, retaining existing context for later normal results. `completionChoice` preserves normal and abrupt edges separately. | Mid's value-region CFG joins normally completing branches into one result place; nonnormal branches retain exits and an all-nonnormal join is Unreachable. |
| match | The source recorder saves the selected scrutinee/pattern/arm bindings and records each arm through the same `recordValueBlock` boundary. A bare arm is a source block with the corresponding result/exit contract. | Mid's saved semantic match and value-region lowering preserve the selected patterns and normal result; no arm's lexical binding/type is rediscovered by a final reader. |
| short-circuit Bool | Both operands are source-checked as values. Shared completion composes LHS with RHS/skip choice, independently for source typing and execution reachability. | `materializeMidShortCircuit` uses the saved Bool result and builds distinct RHS/skip CFG edges. Runtime non-evaluation does not authorize a source-nonvalue operand. |

`blockGiveExpr` remains a construction-time structural query for the one direct
give and permitted context holes; no actual Mid/Mono/LLVM type decision uses it.
Completed Mono scans use `checkedSemanticExprCompletion` / saved statements for
body instances; syntax completion is limited to bodyless construction walks.
The loop source/execution distinction is preserved, with diagnostics in E2 and
full exit cleanup auditing in E4.

## Required Repair and Functional Evidence

Independent review found and reproduced repeated-context source type rewriting
for direct/block scalar/empty Array. The decisive4-mode panic134 and separate
setup failures are retained in meta `phase3e-context-authority-before.json`.
Ordinary source miscompilation is not established. Required child
[com-f0mq](com-f0mq.md) implements a shared initial-context/binding commitment
policy at production `63372a7c`; contract `fbab88b5`. The marker is owner-local
builder progress only; source type and final-consumer authority remain the
existing saved facts. Requested expectations still drive normal compatibility
and saved conversion evidence.

Controls `1b3e0520` cover both recontext entries across4modes, initial commitment
through the expected-result entry, pre/postcommit Comp forks, provisional
Array[Square] first-context completion versus binding commitment, and actual
saved ArrayRepack admission. Standard build `20261024T112642-build-b6309c`, fresh
whole compiler sourcecheck, native33/reject20 all succeed with frozen inputs.
Meta `phase3e-result-authority.json` retains exact cases/hash/receipts; carrier
`bin/plewc-phase3e-context-1` SHA256
`31bae1a929a8bb8a4c7b223ecf72e05458a9577ae208b36957b2cb632954c7bc`.
Sessions83521/34954/58874 reached exit0.

Formal self-host and independent final admission remain pending. This is not
E2 diagnostic closure, E3 callable closure, E4 cleanup closure or G2 full gates.
