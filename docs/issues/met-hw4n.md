---
id: met-hw4n
status: closed
deps: []
links: []
created: 2026-11-28T10:31:20Z
type: task
priority: 2
assignee: Koji Murata
parent: met-si6j
tags: [performance, frontend]
---
# Measure immediate final-callee registry rereads after publication

Finite investigation of prepareSelectedCalleeDescriptor -> completeStaticBodyCallee -> bodyCalleeResultRef and enqueueSelectedCallee -> bodyCalleeIndex. Registries already use hash indexes; do not label them linear searches. Measure exact same-key rereads and their cost before deciding whether publication should return an opaque resolution identity to immediate consumers. Coordinate written-call guarantees in com-qb05; do not duplicate its source selection work or com-xc6h builder API repair.

## Acceptance Criteria

Map publication and immediate reads, including reentry/table changes/owner and interface evidence; count the exact chain and demonstrate meaningful cost. Retain all required checks. If useful, specify scoped identity handoff and create bounded repair; if insignificant, close with rejection evidence. No cache architecture assumption, no generic callee/context reuse, no claimed timing from partial CPU windows.

## Investigation plan

Use a private optimized LLVM20 diagnostic compiler based on4ac60a9c. Preserve every result and interface-evidence check. Count all bodyCalleeIndex calls and time exactly the post-completeStatic bodyCalleeResultRef and post-prepare enqueue bodyCalleeIndex paths with clock_gettime_nsec_np(CLOCK_MONOTONIC=6), confirmed in the installed SDK header. Compare caller body plus all six CallSiteKey fields with the template; distinguish misses and nested/unexpected keys. The latest static publication marker is only an observation, not a proof granting descriptor reuse; scanType and tracing/enqueue operations may intervene and append to tables. Timed paths include required checks, diagnostic overhead and possible nested work, so use them conservatively when rejecting an insignificant opportunity, never as an asserted production gain. Verify compiler-output equality, fixed inputs and runtime library before interpreting. First private build failed only because C ABI parameters require label suppression; corrected diagnostic signature, not a product RED. No product repair is included without measured justification.

## Investigation outcome

Not selected as a performance repair for this fixed selfcompile. Three optimized LLVM20 diagnostic runs preserve inputs, runtime and exact uninstrumented LLVM. Each:332550 total bodyCalleeIndex calls;92369 reads on each scoped chain, matching body+all six key fields, missing/unexpected0. Observed combined time is about20ms including required checks/diagnostic overhead, with microsecond quantization and possible nested overlap. It is not a strict production saving bound and does not establish safe token handoff. Latest-row/count markers do not prove the target publication lifetime. Other traffic/inputs remain outside the result. Independent registry_measurement_review supports investigation closure; no product repair or whole-suite claim. Evidence: meta projection-members/performance-recovery/registry-rereads/. Retained private source/binary/one hardlinked output are needed only through remaining profile comparison, then retire; versioned patch/results/provenance suffice for reproduction.
