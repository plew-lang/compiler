---
id: met-vd0b
status: in_progress
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
