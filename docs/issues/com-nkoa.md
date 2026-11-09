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

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Outside: optional optimization**.

More precise effect summaries/interprocedural borrowing is optional. Required effect closure, conservative unknown targets and current access safety remain included.

## Physical Guaranteed-Value ABI Observation

[Source and Swift comparison](../../../evidence/performance-regression-history/value-self-abi.md)
and [probe artifacts](../../../evidence/performance-regression-history/value-self-abi-probe.json)
record a finite current observation: selected guaranteed Borrow removes call-edge
ARC acquisition, but copyable aggregate self is still lowered as an aggregate
value through the common byval ABI. A32-array/256-byte read-only recursive
probe retains whole-self transfers after the standard LLVM pipeline and clangO2.
Swift6.2.3 -O forwards a stable self address for the corresponding UInt8/UInt
probe, even with method inlining disabled. No throughput ratio or compiler-wide
contribution is established.

Any future guaranteed indirect ABI must retain required evaluation snapshots,
source-place stability, escape/async acquisition and consistency across all
callable entries. Distinguish language borrow from internal guaranteed value
passing. Do not simply remove byval or infer unknown effects as absent. This
observation refines this optional investigation; it changes no adopted ABI,
priority, dependencies or existing-feature acceptance requirement.
