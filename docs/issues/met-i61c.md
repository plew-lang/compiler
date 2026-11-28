---
id: met-i61c
status: in_progress
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

## Current evidence and finite scenarios

Measured current fixed target: 26,973 flag checks, all with empty domains; 620,262 empty per-block vectors and 4,764,427 statement visits, zero flag operations. Counter diagnostic is LLVM22/O0, not a timing claim. New fixture mid_drop_flag_empty_domain is GREEN before and after: empty success, reachable invalid Set/ConditionalDrop, unreachable invalid Set, malformed edge, nonempty initialized flag and uninitialized ConditionalDrop. Existing mid_drop_flag_initialization covers joins/backedges. Independent source/test review found no required correction; native build and real timing remain pending.

After diagnostic: all 26,973 checks use the fast path; vectors 620,262→0 and fixed-point visits 4,764,427→0, replaced by 1,244,929 presence checks. Native controls are GREEN with unchanged inputs; next optimized snapshot is tmp/performance-empty-flags/compiler. Standard suite for met-b775 holds the validation lock, so next build is queued rather than launched concurrently.

Optimized build20261128T135355-build-9c8a85 and own-source smoke succeeded. Five fixed-source pairs:8.036734→7.962734 seconds, paired median−0.048299 seconds,4/5 faster,10LLVM equal, inputs unchanged. RSS effectively unchanged. Independent review supports finite retention without general-rate or formal sub-7 claims. Keep open until the final combined whole-suite gate; the interrupted c55 suite is not a completed gate.
