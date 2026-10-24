---
id: com-0ssn
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
# Verify explicit transfer errors remain distinct from loop reachability warnings

## Boundary

Phase 3E / E2. **Bounded diagnostic/flow verification.** Parent criteria: 2, 5, 6, 8.
This is a bounded child of [com-fuo8](com-fuo8.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/SourceCompletion.pw`; `src/Codegen/Check/Return.pw`; `src/Codegen/Resolve/Record.pw`.

Audit requireExpressionCompletionValue/warnUnreachableStatement and sequential statement recording for return/give/break/continue/diverge calls/empty match versus analytical loop non-continuation. Use existing while/for forms where loop expression syntax is absent; keep static checking of analytical dead code separate from execution ownership joins.

## Exit and Evidence

Fix a finite source/warning/error table: value use of a source-nonvalue rejects; explicit-transfer successors error; analytically noncontinuing-loop successors warn and are still type checked; give after an analytical loop retains source value semantics. Preserve exact exit nesting and do not add Never, new loop syntax or value-bearing break.

Existing starting controls: `block_loop_completion`, `standalone_block_return`, `block_interpolation_divergence`, `block_unary_divergence`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.
