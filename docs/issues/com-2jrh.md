---
id: com-2jrh
status: open
deps: []
links: []
created: 2026-10-13T01:03:13Z
type: task
priority: 4
assignee: Koji Murata
tags: [mid, ownership]
---
# Investigate sharing cleanup CFG paths

Optional sharing of generated cleanup paths. Distinct drop ownership states, flags, conditional access checks, and cleanup ordering must survive CFG sharing. Similar emitted instruction text does not prove equivalent obligations.

Design: [Pass contracts](../design/passes-and-optimization.md), [ownership and lifetimes](../design/ownership-and-access.md), and [verification](../design/verification.md).

Evidence scope: migrated from meta agents/optimization-candidates.md at meta revision ca56d9b6. These are retained investigation candidates, not newly reproduced defects or adopted implementations. Implementation requires renewed source inspection and applicable correctness/performance gates.

## Acceptance Criteria

Specify an equivalence condition and test conditional moves, flags, destruction order and exceptional/terminal exits applicable to the changed paths.
