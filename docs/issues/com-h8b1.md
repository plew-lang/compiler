---
id: com-h8b1
status: open
deps: [com-9hny]
links: []
created: 2026-11-09T17:11:02Z
type: task
priority: 2
assignee: Koji Murata
parent: com-uiri
tags: [ownership, backend, mid]
---
# Connect guaranteed home transport through all entry consumers

## Guarantee and Scope

Freeze an inventory of actual common-helper call sites, then migrate caller and callee binding coherently across normal, method/default, synthetic, closure/witness, external adapters, async and demanded JIT entries. Split this unit by coherent migration boundary before coding when needed. No direct-only rollout. Preserve conservative snapshots, ownership, async frame acquisition and external ABI.

Canonical proposal: [com-rv7l](com-rv7l.md#investigation-result-and-recommended-design). Parent [com-uiri](com-uiri.md) retains end-to-end prototype and no-go/return responsibilities. This task does not change source language semantics or authorize main/seed promotion.

## Execution and Completion

Enumerate finite assertions and real producer/consumer inventory before editing; use task-start TDD and independent neutral review at each reviewable increment. Structural RED must identify the missing handoff/protocol rather than unrelated fixture failure. Record actual execution and retained snapshots as separate evidence. Each required obligation above must be reconciled; deferred implementation cannot count as completion. Measure metadata/preparation cost at W2/W4 even when this unit does not claim speedup.


