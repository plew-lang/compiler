---
id: com-zowv
status: open
deps: []
links: []
created: 2026-10-13T01:03:13Z
type: task
priority: 4
assignee: Koji Murata
tags: [mid, ownership]
---
# Investigate general CFG copy propagation

General CFG copy propagation is an optional proposal, not an incomplete mandatory pass. Prove definitions for each use, alias/snapshot preservation, and destruction timing. Equality of type names, layouts, or drop implementations is not semantic type equality. Dominance alone does not justify repeatedly consuming a value defined outside a loop: each consuming execution needs a fresh definition. Propagating a source place must account for intervening writes, borrows, captures and aliases.

Design: [Pass contracts](../design/passes-and-optimization.md), [ownership and lifetimes](../design/ownership-and-access.md), and [verification](../design/verification.md).

Evidence scope: migrated from meta agents/optimization-candidates.md at meta revision ca56d9b6. These are retained investigation candidates, not newly reproduced defects or adopted implementations. Implementation requires renewed source inspection and applicable correctness/performance gates.

## Acceptance Criteria

Establish a bounded legal subset with enabled/disabled behavior comparisons, malformed-input controls, structural effect checks, and analysis/snapshot cost measurements. Preserve complete-expression temporaries, named binding ends, guaranteed by-value ownership, and ReturnBoundary provenance.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Outside: optional optimization**.

General CFG copy propagation is optional. Correctness of transformations already enabled is included under Mid/ownership verification.
