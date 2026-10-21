---
id: com-t0kz
status: open
deps: []
links: []
created: 2026-10-13T01:03:13Z
type: task
priority: 4
assignee: Koji Murata
tags: [tooling, verification]
---
# Investigate caching sanitizer preparation

Optional preparation cache, not cached test outcomes. The key must include source, dependencies, runtime, toolchain, flags, target/SDK and pipeline. Every required target execution/check remains mandatory.

Design: [Pass contracts](../design/passes-and-optimization.md), [ownership and lifetimes](../design/ownership-and-access.md), and [verification](../design/verification.md).

Evidence scope: migrated from meta agents/optimization-candidates.md at meta revision ca56d9b6. These are retained investigation candidates, not newly reproduced defects or adopted implementations. Implementation requires renewed source inspection and applicable correctness/performance gates.

## Acceptance Criteria

Specify content identity, invalidation and corruption handling, demonstrate cache-hit/miss equivalence and input recording, and measure benefit without skipping sanitizer coverage.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Outside: optional optimization**.

Caching sanitizer preparation is optional; complete instrumentation/coverage and standard gates remain required.
