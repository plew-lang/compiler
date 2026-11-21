---
id: met-kjb2
status: in_progress
deps: []
links: []
created: 2026-11-21T10:48:20Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [tooling, verification, backend]
---
# Connect native ORC build progress to normal validation

The native ORC test hides build output and uses a total 60-second subprocess timeout. Normal run 20261121T092032-test-b7974b stalled after its 1817 run fixtures. Diagnose the silent stage and connect genuine progress through existing monitoring without weakening the no-progress deadline or correctness assertions.

## Contract and boundary

Use the existing trace-command/process_watch supervisor and the standard
normal gate's worker/progress channel. The producer is native C++ compilation;
the consumer is the outer validation deadline. Diagnose actual compiler,
optimizer and linker stages before selecting progress flags. A completed
build is not evidence that an earlier silent interval was observable.

## Guarantees and scenarios

- A valid compile exceeding a total60seconds while making genuine progress
  continues; actual inactivity still stops after60seconds.
- Real compiler/optimizer progress reaches both the retained log and the
  outer worker channel. Heartbeats/PID liveness do not advance the deadline.
- Compile error, signal, cancellation and stall remain failures; children
  are collected and no success receipt survives a failed build/run.
- Existing native ORC layout, publication, ownership, diagnostic and empty
  stdout assertions remain intact, in normal LLVM20 and LLVM22ASan/LSan.
- Keep diagnostic bytes in artifacts and compact the model-facing output.

## Completion

Record meaningful RED for the missing build-progress transport, repair the
owning test harness, verify monitor edge controls plus the actual native ORC
normal and ASan runs, and obtain independent review. Confirm the standard
normal gate consumes the same progress path. Whole-corpus compiler failures
remain their existing owners; this task does not certify the whole suite green.

## Excluded and dependency

No language/backend/runtime semantics, new monitoring framework, reduced tests,
heartbeat, timeout extension, or blanket log streaming. Parentmet-si6j;
com-9l3b depends on this task for the final normal/sanitizer gate. The current
com-yeua normal retry also consumes the repaired harness.

Evidence begins at meta run20261121T092032-test-b7974b and its unchanged-input
stalled result, with the native build log empty. Reuse existing shared monitor
edge controls, adding only this missing harness integration scenario.
