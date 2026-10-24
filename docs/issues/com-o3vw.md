---
id: com-o3vw
status: open
deps: []
links: []
created: 2026-10-24T19:45:10Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [validation, phase3, regression]
---
# Restore literal context through an indexed reference field


## Boundary

The existing normal run fixture arrow_store_literal.pw expects42/99. Direct
r->v=42 succeeds, but ys[0]->v=99 (MutableRef[Box], Box.v:I32) rejects line13
with spec12 type mismatch. This is a valid source-use defect, not a reject
fixture or permission to add an explicit suffix/remove the expectation.

Original performance baseline090240dd, before-poolsedd0ae71 and measured6ddf8f75
all reject the same frozen source with identical diagnostic. Not introduced by
performance work. Restore expected target typing in the source producer and
retain saved decision through the consumer; do not reinfer/retag in Mid.
Keep direct/indexed field and incorrect explicit integer type contrasts.
Determine exact producer before editing; split if repair crosses another boundary.

Normal milestone20261024T193137-test-625275 remains failed. Diagnostic
compiler/tmp/perf-six-type-pools/arrow-control/summary.json; durable final
performance milestone receipt will reference it. Independent b2 classified
this separately from two internal fixture maintenance tasks. Required before
G2b green; does not block the separately scoped speed goal.
