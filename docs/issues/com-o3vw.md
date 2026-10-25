---
id: com-o3vw
status: in_progress
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

## Confirmed Producer

Fresh56fc7954 reproduces the unchanged fixture with trace-codegen:
`expected=U64 inferred=U64 expr=16 position=index unresolved=false`.
The failure is the unsuffixed index0, before the assignment RHS. Source Record's
structural Array/Buffer branch constructed its U64 expectation via simpleTypeRef,
losing ambient declaration identity; tcCheckArrayIndex correctly reads the
canonical lang U64. The actual source field expectation is not the cause.
Repair this one contextual producer with langTypeRefAt and keep strict head/type
identity and final compatibility unchanged. Preserve the original42/99 fixture,
and contrast unsuffixed structural keys, generic/nested/read/write uses, an
explicit I32 key and an explicit I64 value for an I32 field. Raw before trace:
compiler/tmp/phase3-indexed-reference/before.stderr.
