---
id: met-tv4h
status: closed
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

## Outcome and closure

Resolved for the scoped native object path in95dab522. The standard measured
build20261110T230220-build-873ce3 completes in246.570621s versus the prior
same-source compact-retention build400.307606s (one run each, different times).
Build helpers match; carrier/native differ. The compiler object SHA cb3f46eec…
exactly matches the previous normal object, and final fresh candidate raw LLVM
and runtime agree. Its same-source warm/three-pair control is old7.935486s versus
new7.900756s with8 identical LLVM outputs; no significant speed gain is claimed.

Full compiler-scale IR/shared, O2 and codegen progress is observed through real
callbacks/checkpoints, with47/28/111 intermediate lines and no LLVM detail rows.
All scoped GREEN/prepare/build/final/throughput gates preserve immutable inputs.
The final candidate is bin/plewc-light-progress-built-20261111, SHA
9cd0658f7b5d165cff06fa23d07c56ffbb704aaf92379fbd7a122f09b8020df6.

[Decisive evidence and operating limits](../../../evidence/native-llvm-progress/README.md).
[Independent final review](../../../evidence/native-llvm-progress/final-review.json)
accepts this scope; its only confirmed test-environment issue was fixed and
exercised under the formerly failing ambient env. Source/observation lifetime,
pipeline preservation, verifier/failure paths, repeated request state, watchdog
controls, fresh candidate and measurements are independently reconciled.

This is not full-suite, sanitizer-runtime/LSan, distribution, formal new fixed
point, main/seed or adopted-carrier certification. External text-IR LLVM tools
keep their prior monitoring. A single silent long operation can still time out.
No heartbeat/deadline relaxation or language-semantic workaround was introduced.
