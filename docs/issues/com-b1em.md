---
id: com-b1em
status: open
deps: [com-kd1s]
links: []
created: 2026-11-09T17:11:02Z
type: task
priority: 2
assignee: Koji Murata
parent: com-uiri
tags: [ownership, backend, mid]
---
# Select stable evaluated homes before ownership preparation

## Guarantee and Scope

Consume W1a facts with the common root/interval/projection proof before drop/ownership verification. Preserve named-local ownership and required evaluation snapshots; omit only redundant evaluation temporaries. Cover initial self acquisition versus guaranteed self forwarding, globals/static fields, reference/accessor exclusions, callback/later argument/deinit reentry and async acquisition. Keep baseline byval ABI.

Canonical proposal: [com-rv7l](com-rv7l.md#investigation-result-and-recommended-design). Parent [com-uiri](com-uiri.md) retains end-to-end prototype and no-go/return responsibilities. This task does not change source language semantics or authorize main/seed promotion.

## Execution and Completion

Enumerate finite assertions and real producer/consumer inventory before editing; use task-start TDD and independent neutral review at each reviewable increment. Structural RED must identify the missing handoff/protocol rather than unrelated fixture failure. Record actual execution and retained snapshots as separate evidence. Each required obligation above must be reconciled; deferred implementation cannot count as completion. Measure metadata/preparation cost at W2/W4 even when this unit does not claim speedup.


