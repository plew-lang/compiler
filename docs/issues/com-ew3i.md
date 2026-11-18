---
id: com-ew3i
status: open
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
