---
id: com-qzpm
status: open
deps: []
links: []
created: 2026-10-13T01:10:11Z
type: task
priority: 3
assignee: Koji Murata
tags: [ownership, runtime]
---
# Close future concurrency and atomic allocation analysis boundaries

spawn/channel and whole-program sendability/effect propagation remain implementation boundaries, not a redesign of the specified event-loop baseline. Allocation sharing determines a fixed atomic/non-atomic mode; no boundary graph-copy or dynamic promotion is adopted. Demand execution must close required sharing facts before allocation/publication. Current non-atomic helpers do not establish concurrency implementation.

Design: [runtime](../design/runtime.md). Source contracts: [modules](https://github.com/plew-lang/spec/blob/main/spec/04-execution/15-modules.md), [concurrency](https://github.com/plew-lang/spec/blob/main/spec/04-execution/14-concurrency.md), [basic types](https://github.com/plew-lang/spec/blob/main/spec/01-basics/02-basic-types.md) and [packages](https://github.com/plew-lang/spec/blob/main/spec/04-execution/17-packages.md), as applicable.

Evidence scope: migrated from meta agents/design-decisions.md at d2c317318126e994c86e4a3c1f71bfef75606fa2. No new compiler execution or full implementation audit was performed. This is retained follow-up work, not blanket evidence of defects.

## Acceptance Criteria

Audit current implementation, preserve selected protocol from semantic roots through allocations and consumers, and obtain a design decision for any newly necessary lazy/concurrent interaction instead of silently guessing confinement.
