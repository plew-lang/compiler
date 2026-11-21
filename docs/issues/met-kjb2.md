---
id: met-kjb2
status: closed
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

## Outcome

Implemented9e491708. Real LLVM20normal and LLVM22ASan/LSan pass with unchanged
native assertion ASTs. Four actual-entry tool-double controls and13shared monitor
controls pass. The same standard observer accepts the real native local gate
with unchanged inputs; a70.70second build control with260progress events also
passes with the idle deadline unchanged. Independent review found no must-fix
and accepts this finite task. Whole normal suite/com-9l3b/phase3 remain open.

The silent process was implicit dsymutil after both TU compilation and linking.
Objects retain-g; explicit object linking avoids that unnecessary packaging.
The reason dsymutil itself waited is not established and is not required by
this native ORC diagnostic. Query/summary-save I/O receipt endpoints predate
this repair and are outside its compile/link/run guarantee; never accept a
standalone old summary without the successful process/input result.

[Canonical evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-native-orc-build-monitor.json).
