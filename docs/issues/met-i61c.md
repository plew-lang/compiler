---
id: met-i61c
status: open
deps: []
links: []
created: 2026-11-28T12:50:36Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [performance, mid, verification]
---
# Measure and avoid empty drop-flag dataflow work

Investigate verifyCanonicalMidFlagInitialization on the current frozen selfcompile. The verifier builds and propagates per-block flag vectors even when the local flag domain is empty. Count empty-domain requests and relevant statement visits before deciding. If material, use the general proof that an empty flag domain with no flag operations needs no flag fixed point; preserve malformed-input and invalid flag-operation diagnostics, including reachable versus unreachable behavior. Keep canonical shape checks and all non-flag verification.

## Acceptance Criteria

Record measured applicability and cost evidence. TDD empty domain, valid nonempty flags, uninitialized/invalid flag operations, unreachable operations and malformed targets; preserve diagnostics and output. No compiler-specific exemption and no bypass based only on missing local flags. Compare uninstrumented same-source LLVM/time and resources; independent review before completion. Distinguish gain from noise; do not claim sub-7 success from this bounded task alone.

