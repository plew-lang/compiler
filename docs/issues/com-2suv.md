---
id: com-2suv
status: open
deps: [com-f0mq, com-ugee]
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: com-fuo8
tags: [frontend, verification]
---
# Verify block branch and short-circuit completion use one result authority

## Current Reopening

[com-bkqq](com-bkqq.md) reproduced [com-ugee](com-ugee.md) on exact final
candidate3c532ce1: analytical loop noncontinuation suppresses missing-give
rejection, and expected context becomes a value-region result. This contract is
reopened until the shared producer/publication/final-consumer repair and its
independent controls close. The scoped evidence below remains attached to its
named inputs; it no longer proves this area's complete current admission.
No production repair has been made. Parent criteria1/2/5/6/8 are affected.

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
saved ArrayRepack admission. Final production `041b451e` includes stable lexical
base-scope reuse and reuse of validated direct-call environment materials,
without weakening arity/owner/selection/dependency checks.

Standard build `20261024T122016-build-ac051e`, fresh whole compiler sourcecheck
and native37/reject20 all succeed with frozen inputs. Meta
`phase3e-result-authority.json` retains exact cases/hash/receipts. Formal
`20261024T122706-self-host-de3b4c` reaches generation2 fixed point with
7.463384/6.885864/6.930588s, median6.930588s below7s; exit0 and unchanged inputs.
Meta `phase3e-result-authority-self-host.json`. Saved measured WIP compiler
`bin/plewc-phase3e-result-authority-fixed`, SHA256
`3014fb6134705e2e390779f71c3c1c6c7d0f11208b81fb4d11a33777627ec5bf`.
The three preceding above-target checkpoints remain separate and do not certify
completion. No formal same-source speedup percentage is claimed.

## Outcome

Resolved and independently admitted by `/root/body_receiver_completion_review`.
The final static/functional review checked14 referenced hashes and290 focused
inputs. Formal receipt/summary/saved binary match and all5904 formal input hashes
remain current; recomputed median6.930588s. Both E1 and required childcom-f0mq
meet their finite exits. No remaining blocker in this scope.

This is not E2 diagnostic closure, E3 callable closure, E4 cleanup closure, G2
full gates, main integration, or adopted-carrier/seed promotion.
