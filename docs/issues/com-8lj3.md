---
id: com-8lj3
status: open
deps: [com-kphi]
links: []
created: 2026-11-15T11:49:39Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, mid, generics, verification]
---
# Prepare ordinary local storage from checked Mid

Replace source-scan preparation of storage descriptors for ordinary function local initializations with requests derived from checked parametric Mid. See [inventory](com-1a6q.md), [Mid contract](../design/mid.md) and [finalization contract](../design/frontend-handoffs.md#8-implicit-calls-and-reachability).

## Design

Carry the checked binding origin, selected conversion occurrence and initializer type dependency to the pre-Access request. Order prior call result, concrete local type and conversion, then subsequent local uses by dependency, independently of physical block order. Publish the descriptor once per body and storage occurrence. Preserve evidence replay, type/layout and destruction registration, diagnostic order and necessary descriptor-only work. Switch the migrated path and remove its legacy descriptor producer. Keep globals, closures, assignments, generated bodies, adapters and unrelated scanner migration outside this task.

## Acceptance Criteria

Trace checked binding and conversion production through both AOT and lazy preparation to actual Mid instantiation and execution. Exercise annotated and inferred locals, prior and subsequent calls, shadowing, two distinct generic instances, non-continuing initialization and missing/foreign facts. Verify preserved global, closure, generated and adapter paths. Compare fixed-input LLVM/runtime, scan counts and timing, document the result and obtain independent review. The standard fixed-point and seven-second checks belong to com-p5um.

