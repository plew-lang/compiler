---
id: com-h4dh
status: open
deps: []
links: []
created: 2026-10-13T01:03:13Z
type: task
priority: 4
assignee: Koji Murata
tags: [generics, mid]
---
# Investigate analysis sharing after generic instantiation

Optional reuse of analysis across concrete BodyInstances. Prove equality of concrete type, ownership and access contracts, not merely a shared parametric template. This is distinct from sharing immutable parametric bodies.

Design: [Pass contracts](../design/passes-and-optimization.md), [ownership and lifetimes](../design/ownership-and-access.md), and [verification](../design/verification.md).

Evidence scope: migrated from meta agents/optimization-candidates.md at meta revision ca56d9b6. These are retained investigation candidates, not newly reproduced defects or adopted implementations. Implementation requires renewed source inspection and applicable correctness/performance gates.

## Acceptance Criteria

Identify complete dependency keys and invalidation boundaries, compare independent analysis results, and measure savings on representative instances.

