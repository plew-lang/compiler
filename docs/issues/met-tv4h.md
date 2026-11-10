---
id: met-tv4h
status: in_progress
deps: []
links: []
created: 2026-11-10T22:51:00Z
type: task
priority: 2
assignee: Koji Murata
tags: [backend, tooling, performance]
---
# Separate native LLVM progress events from verbose pass logging


## Contract and finite scope

Separate cheap progress from verbose LLVM logging in the native object consumer
and its embedded CLI/standalone worker. --trace-phases requests bounded real-work
checkpoints; PLEW_LLVM_TRACE=1 plus that request opts into detailed LLVM logging.
Keep native CPU/PIC/machine optimization, both shared IR pipelines, pre/post
verification, sanitizer placement, error/output preservation and watchdog/child
collection unchanged. No language semantics, seed/carrier promotion/main merge.
External opt/clang text-IR/bootstrap paths retain their existing detailed tracing
and are outside this native-object improvement; do not weaken their monitoring.

Design: new-PM afterPass/afterInvalidated callbacks, with default manager setup
matching LLVMRunPasses; legacy observational preserves-all/no-change function and
non-immutable module checkpoints. Never retain borrowed IR or grant semantic
permissions. Capture original pass kind before add() (it can delete the pass).
Checkpoint counters are not exact original LLVM pass execution counts: skipped
or redundant original passes can still be followed by an observational checkpoint.
No timer heartbeat. A single silent long pass still triggers the60-second limit.

Scenarios/closure:
- RED on original worker: trace must report IR/shared, O2 and codegen checkpoints
  without per-pass debug text. Quiet remains quiet; verbose opt-in retains both
  debug streams; env alone does not override a quiet request. Modes agree on
  tiny emitted objects; invalid inputs preserve prior output and diagnostics.
- Native worker tests on LLVM20 and22, including sanitizer-marked module output,
  actual progress/exit and output-error paths. Existing watchdog timeout,
  repeated-event, cancellation/reaping and diagnostics tests stay green.
- Existing direct-object tests use new checkpoint expectations, retain explicit
  verbose controls, and exercise reference/direct AOT fixture outputs. No change
  to language goldens. LLVM raw/compiler object comparison and current-source
  build/smoke confirm pipeline/consumer behavior beyond synthetic shape checks.
- Measure real standard build using a freshly linked candidate with this native
  implementation; distinguish first build with old carrier from measured build.
  Preserve candidate/raw/object identities, input receipts and time/log summaries.
- Synchronize native API/design/test/operational docs and independently review
  implementation plus measured candidate. No full-suite/ASan/full-fixed-point
  or adoption certification inferred from scoped gates.

## Implementation checkpoint

Original worker RED is recorded in meta tmp/llvm-progress/red-gate: the new
no-detail assertion fails on actual default trace output. LLVM20/22 native mode,
object identity, invalid-parser/output diagnostics and sanitizer-symbol controls
are GREEN in green-gate. The changed default-trace assertion in direct-object
uses PLEW_LLVM_TRACE=0 explicitly (independent review caught ambient env leakage).
prepare-gate also passes reference/native five-fixture executions, fresh embedded
candidate direct-object controls, repeated in-process requests/verbose init, and
source/native input invariance. Original LLVM verifier/target/layout rejection
controls are executed, not inferred from parser rejection. Forty supervisor/unit
checks pass with existing timeout/cancellation/reaping/diagnostic assertions.
Measured standard build and final independent candidate review remain required.
