---
id: com-2suv
status: open
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
