---
id: met-quvh
status: in_progress
deps: []
links: []
created: 2026-11-20T22:37:10Z
type: task
priority: 1
assignee: Koji Murata
parent: com-8uik
tags: [diagnostics, performance, verification]
---
# Batch phase trace writes while preserving progress events

Bounded performance followthrough: phase tracing currently emits prefix, label, punctuation and each decimal digit through separate stderr writes. Preserve all event identities, order, count, numeric values, immediate per-event visibility, disabled-trace silence and compiler output. Batch each complete event into one eprint. Excludes trace sampling/frequency changes, formal measurement definitions, watchdog weakening and global runtime I/O changes. Baseline identical final carrier comparison: plain6.898061s/trace-pipe7.002378s/trace-file7.348953s; diagnostic only, all LLVM identical. First freeze behavior with exact native trace controls, then change helpers and compare exact candidate. Evidence follows meta array-context plan.

## Acceptance Criteria

Native baseline and changed candidate: disabled trace silent; enabled labels including empty, zero, multi-digit and U64 max exact; stride hit/miss and disabled stride preserved. Full-source trace events and LLVM unchanged for same source; retained watchdog works. Same-source alternating timing, standard build and applicable controls. Independent review; do not claim 7s goal from diagnostic timing.


## Validation increment

Baseline native PhaseTrace exact stdout/stderr passed; changed final candidate also passes. Initial helper rename missed calls from module parts and failed compilation; traceU64 was retained for these callers. Standard isolated build20261120T223935-build-870d50 passes. Same frozen source alternating3 pairs with the existing formal one-compile wrapper: before6.982657s / after6.975036s medians; all6 LLVM identical. All15175 phase event bytes/order/count identical. Full stderr differs only in two carrier-relative standard-library warning paths. This is diagnostic timing, not a demonstrated speedup or formal7s success. Independent source review found no must-fix; bounded String concatenation allocation tradeoff retained for measurement. Canonical meta array-context evidence contains exact hashes/rows. Final formal performance and task closure remain open.
