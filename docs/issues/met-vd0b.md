---
id: met-vd0b
status: closed
deps: []
links: []
created: 2026-11-10T16:16:17Z
type: task
priority: 2
assignee: Koji Murata
tags: [backend, tooling, performance]
---
# Separate LLVM detailed trace producer and supervision costs


## Finite investigation contract

Using one frozen raw LLVM module and one diagnostic native worker, compare
three sequential configurations: detailed trace off, trace generated/written to
/dev/null, and trace generated through the normal compact trace supervisor.
Native CPU apple-m1, machine O2, both normal IR pipelines, verification and
preserves-all completion observer are identical. Every mode retains actual
pass-completion progress and the unchanged60-second watchdog. No fake heartbeat
or deadline relaxation. If a silent IR stage exceeds the limit, record the failed
run before refining instrumentation; do not count it as a successful sample.

Scenarios/deliverables:
- One exploratory run per mode with stage/worker wall time, child user/system
  CPU time, actual commands/exits, output hashes and observer completion counts.
- Verify both IR stages and machine stage complete, equal object bytes (or
  explicitly account for differences), and frozen-input receipts including
  diagnostic worker, raw IR, toolchain and supervisor.
- Off→null estimates detailed-trace producer plus null-write overhead; null→pipe
  estimates output-path/supervisor costs, not pure formatting or parser cost.
  Same observer avoids the previous pipeline mismatch but has unisolated cost.
- Record order/one-run/thermal limits; do not infer total standard-build savings
  or change normal defaults, source, seed, main or adopted carrier.
- Independent neutral review reconciles recipe, assertions and evidence. No
  artificial RED, full-suite/sanitizer/bootstrap or compiler adoption claim.

## Outcome

Investigated. Same-worker supervised wall is off225.811s, null459.035s,
pipe460.249s. Producer plus null-write path adds233.224s, of which machine/object
stage accounts for221.046s; child system CPU rises from1.948s to201.194s.
Null→pipe wall is only+1.214s on these one-run samples, but combined child CPU
rises about23.289s, so downstream work is not zero. All3 objects are byte-identical
(SHA9d772888…),315616 legacy observer completions agree, both IR stages and machine
stage complete. Tiny controls and both frozen-input gates pass with exit0.

[Recipe, exact results and limitations](../../../evidence/llvm-trace-cost/README.md).
The opportunity is eliminating per-pass detail generation/writing while retaining
lightweight real progress. Storage compaction alone cannot do that. Added common
observers also appear in detailed trace, so this difference is not a production
build speedup or a subtractable amount from the previous400s build. Observer
cost, fixed-order/thermal effects and pure formatting/syscall/parser costs are
not isolated. IR stages use boundaries here, not complete per-pass progress.
No production settings/source, main/seed/carrier were changed.

Closure reason: investigated. Independent neutral review rechecked all input/log
receipts,6 object outputs, stage timings/counts and statuses; no confirmed contract
violation or required unresolved check remains. The review supports the bounded
attribution and explicitly retains the nonzero downstream CPU and scope limits.
[Final review](../../../evidence/llvm-trace-cost/final-review.json).
