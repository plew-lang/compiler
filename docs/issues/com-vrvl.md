---
id: com-vrvl
status: in_progress
deps: []
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-rzt4
tags: [frontend, verification]
---
# Isolate normal CLI InternalSession progress before changing JIT policy

## Boundary

Phase 3F / F3. **Bounded isolated investigation.** Parent criteria: 7, 9.
This is a bounded child of [met-rzt4](met-rzt4.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/CompilerExecution.pw`; `src/CheckedProgram.pw`; `native/compiler_execution.cpp`; `native/llvm_backend.cpp`; `scripts/support/process_watch.py`.

Recheck the four retained compiler_session demand/finalization/initializers/registry inputs on the current saved candidate through the normal CLI, separately from other heavy work. Keep the 60-second no-progress rule. Compare existing traced-embedding evidence only as a scope contrast; identify the exact source preparation/materialization/CLI progress boundary if normal execution still stops.

## Exit and Evidence

Each of four cases has normal CLI exit/output and actual progress evidence, or a precise stopping phase plus one bounded repair child naming the real progress source/consumer. Classify active LLVM work versus deadlock using evidence. Do not merely tune JIT optimization, extend timeouts, emit heartbeats or treat old 2154af1b observations as a current reproduction. An unknown repair is not promised as a few-day implementation.

Existing starting controls: `compiler_session_demand`, `compiler_session_finalization`, `compiler_session_initializers`, `compiler_session_registry`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.

## Prepared Current Progress Boundary (Not Reproduced)

Read-only tracing at36680385 finds tracePhases defaults false in normal
Compiler.runProgram/executeProgram and the fixtures' inner CompilerSession.open.
prepare_body -> lowerBody is synchronous; diagnostic draining occurs afterward.
Native source callback/module admission/ORC materialization have no ordinary
progress publisher. This identifies possible silent intervals, not a new current
60-second reproduction or proven deadlock. If reproduced, connect actual source
worklist/pass progress to its consumer; do not add heartbeats or extend deadlines.

The task's exact four inputs remain demand/finalization/initializers/registry.
The older session-traced-jit.json fourth case is mid_requests, so that historical
success does not certify registry. No current normal-CLI execution was started
during this preparation.
