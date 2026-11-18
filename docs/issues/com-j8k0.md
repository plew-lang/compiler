---
id: com-j8k0
status: closed
deps: []
links: []
created: 2026-11-18T15:24:06Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, ownership]
---
# Specify standalone blocks and scope-aware unique shadowing


## Contract and completion

Update [control flow](../../../spec/spec/03-expressions/11-control-flow.md)
and [values and ownership](../../../spec/spec/01-basics/03-values.md), and
reconcile the matching name lookup, ownership, frontend handoff and Mid
contracts wherever they describe these boundaries.

- A statement position can evaluate an expression and discard its result,
  including a call, a literal or a block with a directly belonging `give`.
  A standalone block creates a lexical scope and can also continue normally
  without a `give`. A block whose result is required must produce it with
  `give` on normal paths. The last expression never supplies it implicitly.
  A `give` targets its own value region. Preserve existing explicit transfers,
  divergence rules, and the distinction between source completion and
  reachability inferred by analysis. Discarded-result warnings are out of scope.
- A same-scope declaration replaces the previous binding after RHS evaluation
  and temporary cleanup. End its old unique ownership at commit if it is still
  owned. A nested declaration only hides an enclosing binding for that scope;
  it creates no drop edge or borrow conflict for the enclosing owner. Ordinary
  move, branch joins, explicit end and scope cleanup still apply. Use the actual
  binding scope for pattern and condition bindings.

Check that examples and cleanup/borrow terminology agree across the affected
documents. Record the independent review before closure. This task delivers
the source and compiler contracts; implementation belongs to
[com-ew3i](com-ew3i.md) and [com-x7ql](com-x7ql.md).

## Independent closure review

Spec revision `c895765` and the corresponding compiler design update
synchronize block result use, destination-specific transfers, binding
scope and destruction. The independent reviewer identified unconditional
fall-through wording, stale function/give wording, conflation of expected
type and result use, missing pattern-scope detail, and an ambiguous numeric
example. Follow-up review confirmed each correction and the new anchor.
This closes the documentation contract; the implementation and runtime
controls belong to com-ew3i and com-x7ql.
