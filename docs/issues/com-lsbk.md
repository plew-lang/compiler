---
id: com-lsbk
status: open
deps: []
links: []
created: 2026-10-13T01:03:13Z
type: task
priority: 4
assignee: Koji Murata
tags: [backend, ownership]
---
# Investigate aggregate argument reduction across delegation

Optional backend optimization. Aggregate value arguments remain after the shared SCC-local pipeline and argpromotion. Distinguish necessary snapshots from redundant machine copies; examine inlining and argument reduction order and final machine-code loads/stores. No compiler-type-name or aggregate-size exceptions. Existing scoped evidence: meta evidence/typechecking-remediation/call-bound-admission/final-call-backend-code-size.json; it is not proof of current whole-program prevalence.

Design: [Pass contracts](../design/passes-and-optimization.md), [ownership and lifetimes](../design/ownership-and-access.md), and [verification](../design/verification.md).

Evidence scope: migrated from meta agents/optimization-candidates.md at meta revision ca56d9b6. These are retained investigation candidates, not newly reproduced defects or adopted implementations. Implementation requires renewed source inspection and applicable correctness/performance gates.

## Acceptance Criteria

Compare the same input with a fixed compiler/toolchain and inspect actual load/store changes while preserving snapshot, alias and ownership contracts.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Outside: optional optimization**.

Aggregate argument reduction is optional; current admitted ABI/ownership must remain valid.
