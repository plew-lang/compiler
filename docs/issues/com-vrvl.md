---
id: com-vrvl
status: closed
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

## Fresh Isolated Outcome

Candidate09dac934/source1f442206 ran the exact demand/finalization/initializers/registry inputs independently via normal CLI `--run SOURCE`. All four exit124 at about61 seconds from the unchanged60-second no-progress watchdog; no normal golden output is claimed. Inputs remain unchanged. One native sample per case at25seconds observed active SourceBodyGenerator, native Plew prepare callback and ORC module/compilation work; this is evidence of work at that instant, not proof that the entire interval progressed or that no later deadlock exists.

The precise observation gap is normal run's default tracePhases=false and synchronous requested body/ORC preparation without a watched work-unit publisher. Required finite repair com-auvx names the actual producers and process_watch consumer, prohibiting heartbeat/deadline/JIT-policy substitutes. F3's bounded investigation exit allows this precise phase plus required child; met-rzt4/G1 remain open until repair and fresh success. The first never-successful scratch runner wrongly passed a trace flag in the source position; normal-1 is retained as setup failure, normal-2 uses correct unchanged CLI arguments. This is unrelated to application semantic failure.

Durable evidence: meta/evidence/existing-feature-conformance/source-owner-facts/phase3f-session-cli-investigation.json. Independent c2_classification_review matched all receipt references,251 inputs/carrier and4 stdout/stderr hashes, observed samples and mandatory successor dependencies; accepted bounded investigation completion. New progress alone will not certify the four cases; com-auvx must obtain actual outcomes or assign any newly precise mandatory repair.
