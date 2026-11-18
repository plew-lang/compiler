---
id: com-ew3i
status: in_progress
deps: [com-j8k0]
links: []
created: 2026-11-18T15:24:06Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, mid, verification]
---
# Accept standalone blocks in discarded-result position


## Contract and completion

Implement the block rules in [com-j8k0](com-j8k0.md) from syntax and Lower
through source completion and Mid. Carry result use and lexical scope to
consumers; reuse the existing statement/value block processing and
destination-based transfer rules. Preserve the expression interpretation when
surrounding syntax requires a value. Do not synthesize a `give`, an implicit
tail value or a discarded-result warning.

Confirm RED with an existing pinned carrier. Cover standalone effects without
`give`, an explicit `give` whose result is discarded, literal/call expression
statements, necessary and missing block results, nested give ownership and
return/break/continue propagation. Include scope cleanup on normal and early exit,
check/native/ORC parity and independent review. The combined unique shadowing
fixture is owned by [com-x7ql](com-x7ql.md).

## Baseline checkpoint

With the fixed diagnostic carrier for `9aef2eaa`, a standalone
`{ print(1I64) }` followed by `print(2I64)` is refused for missing give
in check and demanded ORC. Adding a directly owned `give 3I64` produces
exactly 1 then 2 in ORC. Moving the original no-give block into an I64
initializer still correctly refuses in both modes. The first case is RED;
the latter two are behavior controls. The current source checker reaches
`recordExpr(needsValue: false)` from ExprStmt but unconditionally calls
`recordValueBlock` for Expr.Block. Mid currently asks for a value operand
on this same path. Close the result-use handoff through these consumers.
