---
id: met-hw4n
status: open
deps: []
links: []
created: 2026-11-28T10:31:20Z
type: task
priority: 2
assignee: Koji Murata
parent: met-si6j
tags: [performance, frontend]
---
# Measure immediate final-callee registry rereads after publication

Finite investigation of prepareSelectedCalleeDescriptor -> completeStaticBodyCallee -> bodyCalleeResultRef and enqueueSelectedCallee -> bodyCalleeIndex. Registries already use hash indexes; do not label them linear searches. Measure exact same-key rereads and their cost before deciding whether publication should return an opaque resolution identity to immediate consumers. Coordinate written-call guarantees in com-qb05; do not duplicate its source selection work or com-xc6h builder API repair.

## Acceptance Criteria

Map publication and immediate reads, including reentry/table changes/owner and interface evidence; count the exact chain and demonstrate meaningful cost. Retain all required checks. If useful, specify scoped identity handoff and create bounded repair; if insignificant, close with rejection evidence. No cache architecture assumption, no generic callee/context reuse, no claimed timing from partial CPU windows.

