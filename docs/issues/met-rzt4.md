---
id: met-rzt4
status: open
deps: [com-d57o, com-vrvl, com-auvx]
links: []
created: 2026-10-13T01:40:08Z
type: epic
priority: 2
assignee: Koji Murata
parent: met-si6j
tags: [frontend, jit, diagnostics]
---
# Recheck historical parser recovery and compiler-session JIT stalls

## Bounded Execution and Gate Ownership

This is an area epic, not one executable multi-week task. Its current bounded
work and real prerequisites are tk dependencies under the
[parent policy](met-si6j.md#bounded-task-policy):

- [F2](com-d57o.md): finite historical parser observations.
- [F3](com-vrvl.md): current isolated normal-CLI session progress disposition.

Close this area's exact existing contract after required children/repairs and
their scoped fresh verification. The final frozen candidate normal/gen/deps/full
sanitizer/fixed-point/performance obligation is explicitly owned by
[G2a](com-p5um.md)/[G2b](com-9l3b.md) and cannot be waived when this
area closes. Historical checkpoint gates are not current-candidate certification.
Earlier current/next/WIP observations refer to their named revisions; the bounded
children reconcile what actually remains before any repair. No new meaning or
unsupported feature is authorized by this allocation.

[F1](com-4bib.md) separately owns requested-body mode parity, and
[F4](com-s248.md) owns six historical/risk dispositions. They are direct
parent tasks, not missing acceptance work silently added to this parser/CLI area.

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
The candidate was built at 2154af1b. Its four exact CLI controls still hit the
unchanged silence deadline; None alone did not solve the observation problem.
An embedding diagnostic using the same executeProgram/runtime/preparation path,
with only the existing tracePhases option enabled, completes all four exact
fixtures with golden output at frozen 2154af1b (370.302 / 444.301 / 427.047 /
561.319 seconds). The same Plew host object relinked with the previous default
native policy also completes compiler_session_demand with golden output.
Those diagnostic runs overlapped, so their elapsed times are not a controlled
performance comparison. Native ORC/lazy controls pass normally and with LLVM22
ASan/LSan; this does not instrument every generated JIT instruction.

[Traced controls](https://github.com/plew-lang/meta/blob/main/evidence/existing-feature-conformance/source-owner-facts/session-traced-jit.json),
[default-policy control](https://github.com/plew-lang/meta/blob/main/evidence/existing-feature-conformance/source-owner-facts/session-traced-default-jit.json),
and [native controls](https://github.com/plew-lang/meta/blob/main/evidence/existing-feature-conformance/source-owner-facts/jit-codegen-native-controls.json)
record the exact scope. All process handles are recovered. This establishes
bounded successful current diagnostic executions, not normal CLI completion
under its no-progress watchdog or a universal historical-cause claim. Keep the
remaining CLI observability/materialization-latency question explicit; do not
mislabel active compilation as a demonstrated deadlock or weaken the watchdog.
