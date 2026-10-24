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

## Source and Consumer Reconciliation

Static audit at production `041b451e` (test-only extension `85e9b190`) found no
new implementation defect in this finite scope. The source/execution channels
are retained as separate compositional facts, not re-inferred in final readers.

| Contract | Producer / saved fact | Consumer / diagnostic |
|---|---|---|
| Direct return/give/break/continue, diverging call, empty exhaustive match | `completionTransfer` and expression/statement composition retain abrupt edges. `completionBlock` consumes only the directly belonging give. | `recordBlockContents` errors at a successor when `flow.source.normal()` is false; an enclosing block/loop consumes only its own exit. |
| Analytical loop noncontinuation | `completionLoop` preserves source normal continuation independently of execution return/diverge/no continuation. | The same statement walk emits `warnUnreachableStatement` once, then still records/type-checks successors. A later explicit transfer still makes its successor an error. |
| Source-nonvalue in a required value position | `requireExpressionCompletionValue` uses the saved/constructed source channel, regardless of expected type or runtime branch skipping. | Assignment/argument/operator/give/return value gates reject; a normal branch can still supply a mixed expression's value. |
| Analytical dead-code verification | Checked statements retain completion/binding facts even without an execution edge. | `verifyBlock` checks statements while keeping non-executing ownership state out of actual continuation joins. Mono/Mid read admitted completion facts at their existing instance/value-region/loop boundaries. |
| Warning demand/lifetime | `prepareLexicalBody` requests the body; successful/failed owner states retain their outcome; `takeDiagnostics` drains pending warnings. | No dormant-body preparation solely for diagnostics. Existing reported-statement identity suppresses repeated warnings without weakening source errors. |

New internal `source_completion_diagnostics` uses the public File/SourceAccess
request pipeline: dormant warning body, unrelated successful request, one
Warning severity/message, retained source/execution/binding facts, repeat without
duplicate emission, type error after a loop with failed facts/retry retained,
and explicit return successor error inside a warned region. It does not execute
an infinite loop or expose a private API. Native12/reject22 are running under
watch-command with fresh `bin/plewc-phase3e-context-4`; runtime source remains
unchanged from the E1 fixed-point/performance checkpoint. No E3/E4/G2 admission
follows from this verification plan.
