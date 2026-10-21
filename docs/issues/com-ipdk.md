---
id: com-ipdk
status: open
deps: []
links: []
created: 2026-10-13T01:03:13Z
type: task
priority: 4
assignee: Koji Murata
tags: [mid, runtime, ownership]
---
# Investigate sparse async liveness analysis

Optional sparse/worklist analysis for large async bodies. No measurement currently establishes a self-compiler speed benefit. Preserve saved-variable sets, borrow-owner dependencies and post-resumption Drop obligations.

Design: [Pass contracts](../design/passes-and-optimization.md), [ownership and lifetimes](../design/ownership-and-access.md), and [verification](../design/verification.md).

Evidence scope: migrated from meta agents/optimization-candidates.md at meta revision ca56d9b6. These are retained investigation candidates, not newly reproduced defects or adopted implementations. Implementation requires renewed source inspection and applicable correctness/performance gates.

## Acceptance Criteria

Compare dense and proposed analyses on large async inputs, demonstrate identical required frame ownership/liveness, and report compile-time and storage cost.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Outside: optional optimization**.

Sparse liveness is an optional algorithm; current frame live roots and release correctness remain required.
