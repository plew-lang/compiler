---
id: com-2suv
status: in_progress
deps: []
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

Initial audit at `ee736b1a` / runtime `9b4652a3`. This map is not completion
admission while the recontextualization question below is unresolved.

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

## Open Verification Point

Initial native17/reject16 all pass with fixed carrier
`bin/plewc-phase3d-type-storage-fixed`, SHA256
`380d649e240dd71e366323a4167ac39200dc77a0993fcec4cc5cda1dd8822275`;
meta receipt `phase3e-result-authority-initial.json` retains the exact scope.
Independent review found a possible construction API path that reapplies an
I16 expectation after a scalar or empty array was already typed with I8,
including wrapped values. `value_control_context_authority` reproduces all4 direct/block scalar/empty
Array changes and subsequent compatibility acceptance (panic134). Setup parse
and private-API failures are separate from this decisive baseline; no private
reader was exposed. Ordinary source miscompilation is not established. A finite
shared-context repair is being designed before allocation.
Preserve legitimate Pending-to-known and generic result completion; explicit
types and already committed terms must not be overwritten merely by context.
