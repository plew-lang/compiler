---
id: met-rzt4
status: open
deps: []
links: []
created: 2026-10-13T01:40:08Z
type: task
priority: 2
assignee: Koji Murata
parent: met-si6j
tags: [frontend, jit, diagnostics]
---
# Recheck historical parser recovery and compiler-session JIT stalls

Retained independent investigation from type-checking remediation. Historical reserved-identifier/match/trait recovery could stall until the 60-second watchdog; a compiler InternalSession JIT execution aborted after the selected-body/final-call authority migration. Neither is established as a current-tree defect by the documentation migration.

Recheck exact historical inputs/revisions and watchdog output in [migration evidence](https://github.com/plew-lang/meta/blob/main/evidence/typechecking-remediation/design-migration.md) and the [final-call-authority record](https://github.com/plew-lang/meta/blob/main/evidence/typechecking-remediation/final-call-authority/README.md) (compiler 1a2ed6b6); separate parser recovery/progress from JIT dependency/abort ownership. Do not infer the _memcpy issue (com-8w4c) is the same failure.

Acceptance: minimal current controls, bounded termination or actionable error, failure-state propagation, and specific implementation/evidence if still reproducible. Do not weaken watchdogs or turn unfinished investigations into source restrictions. Route discovered responsibility changes to separate tickets if necessary.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Included bounded verification**.

Current bounded parser recovery for the retained malformed input and the distinct InternalSession JIT abort. Use exact old inputs/revisions, current error/exit controls and stage evidence. Keep the libcall issue separate. Do not weaken watchdogs or introduce unsupported syntax to restore old acceptance.

## Bounded Current Recheck and Materialization Observation (WIP)

5e1dd64b, measured compiler SHA256
007423150e3c3624740dd9d5ff83a04de3d5c4ce4b396683d5bd06616fbd7f4e:
representative match/trait name declarations terminate, and malformed use of
those names returns a positioned parse error. The retained historical ledger
names the spellings but does not retain its exact original scratch source; do
not claim an exact-input replay or general keyword-validity certification.
The ordinary-name control also terminates. No parser change was needed for these
bounded current controls.

The exact compiler_session_demand fixture still hits the unchanged 60-second
no-progress deadline in CLI JIT, with no application output. Two samples on a
repeat show active host compiler body preparation at 20 seconds and LLVM ORC
IRCompileLayer / greedy register allocation at 45 seconds, not a stationary
mutex wait. The full normal gate with eight workers was also active; this does
not establish an isolated elapsed-time comparison or prove the entire historical
failure class has one cause. Do not classify active, unreported compilation as
a proven deadlock.

Candidate repair: explicitly request CodeGenOptLevel::None from the host
JITTargetMachineBuilder. LLJIT otherwise uses its default machine-code optimizer
on raw source IR. Materialization latency is the development JIT's responsibility;
the shared runtime, checking, body preparation and AOT optimization remain common
or unchanged. Validate the four retained InternalSession fixtures and native ORC
controls; keep the 60-second watchdog and exact output/failure checks. If a long
phase remains, expose real phase progress rather than periodic heartbeat success.
This candidate is not yet built or claimed to close the task.
