---
id: met-xb46
status: in_progress
deps: []
links: []
created: 2026-11-10T15:51:41Z
type: task
priority: 2
assignee: Koji Murata
tags: [backend, tooling, performance]
---
# Compare lower machine-code optimization tiers for development compiler builds


## Finite investigation contract

Compare machine-code O1 and O0 against the retained host O2 object from
met-1hnl. Keep both normal IR pipelines, native CPU apple-m1, verification,
runtime and production native backend identical. Select the lower machine
level only after IR optimization. Diagnostic observer passes are unchanged.
No production defaults, seed, adopted carrier or main integration are in scope.

Questions/scenarios:
- Measure each lower-tier object worker, stages, object/binary size and link.
  The O2 build timing is the previous single-run reference, not a fresh median.
- Link all three objects with the same runtime and native support archive.
- Warm each resulting compiler and alternate five source-to-LLVM trials per
  tier on the same compiler source; require byte-identical raw LLVM and runtime.
- Compare a small valid and invalid source on all three candidate compilers;
  preserve expected stdout/exit/diagnostics, and exercise AOT/lazy execution.
- Retain input hashes, actual exits and independent neutral review. Report any
  untested scope; no full-suite, sanitizer, fixed-point or promotion claim.

This is a configuration experiment, not a bug repair; no artificial RED.
If a lower tier is useful, production-mode selection is a subsequent decision.
