---
id: com-nkoa
status: open
deps: []
links: []
created: 2026-10-13T01:03:13Z
type: task
priority: 4
assignee: Koji Murata
tags: [ownership, runtime, mid]
---
# Investigate effect precision and interprocedural borrowing

Optional effect-summary precision and interprocedural borrowing. Account for dynamic targets and read/write paths; unknown effects are not pure. Single-thread execution or immutable bindings do not exclude callback, shared-identity or await-mediated changes.

Design: [Pass contracts](../design/passes-and-optimization.md), [ownership and lifetimes](../design/ownership-and-access.md), and [verification](../design/verification.md).

Evidence scope: migrated from meta agents/optimization-candidates.md at meta revision ca56d9b6. These are retained investigation candidates, not newly reproduced defects or adopted implementations. Implementation requires renewed source inspection and applicable correctness/performance gates.

## Acceptance Criteria

Define the proof that permits each removed check/copy, retain effect closure/publication validity, compare behavior and verification with optimization disabled, and measure total cost.

