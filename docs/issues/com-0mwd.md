---
id: com-0mwd
status: open
deps: []
links: []
created: 2026-10-13T01:03:13Z
type: task
priority: 4
assignee: Koji Murata
tags: [mid, ownership, backend]
---
# Investigate direct construction into result storage

Optional destination integration. Prove alias and lifetime constraints before constructing directly into the final result; retain the logical ReturnBoundary and source-site provenance. Allocation elimination alone is not permission to change destruction order.

Design: [Pass contracts](../design/passes-and-optimization.md), [ownership and lifetimes](../design/ownership-and-access.md), and [verification](../design/verification.md).

Evidence scope: migrated from meta agents/optimization-candidates.md at meta revision ca56d9b6. These are retained investigation candidates, not newly reproduced defects or adopted implementations. Implementation requires renewed source inspection and applicable correctness/performance gates.

## Acceptance Criteria

Define legal cases and fallback, prove producer-to-final-consumer result/ownership equivalence, and measure whether analysis plus rewriting pays.
