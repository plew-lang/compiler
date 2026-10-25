---
id: com-auvx
status: open
deps: []
links: []
created: 2026-10-25T00:50:48Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-rzt4
tags: [driver, verification, frontend]
---
# Publish real lazy preparation and ORC materialization progress to watched CLI runs


## Boundary and Exit

Finite observability repair required by F3/com-vrvl. On fresh09dac934/source1f442206, all four exact normal CLI `--run` CompilerSession fixtures stop at unchanged60-second no-progress watchdog (exit124), with frozen inputs. One3-second native sample starting25seconds into each case shows active SourceBodyGenerator/plew_compiler_prepare_body work and ORC module/native compilation. This is not success and not a proof against later deadlock; no completed body/pass progress reaches the watcher in these quiet CLI runs.

Producer boundary: Compiler.runProgram→CompilerExecution.executeProgram defaults FrontendOptions.tracePhases=false; CompilerCallbacks.prepare_body synchronously prepares and lowers a requested body; native SourceBodyGenerator::generate consumes/submits its module; ORC materialization completes actual work. Consumer: scripts/support/process_watch.py's unchanged semantic-progress deadline and standard validation event aggregation. Reuse the existing phase/worklist observation contract, connect genuine newly completed/source/pass units and identity to an opt-in watched/diagnostic run, and propagate observation into requested preparation. Do not expose compiler internals as language behavior or make ordinary application stderr noisy. Preserve one runtime and JIT preparation semantics.

A trace/progress option or internal observer adapter is routine diagnostic plumbing, not permission to tune JIT optimization, alter body request boundaries, extend deadlines or emit time-based/liveness heartbeats. Test that completed new units advance the observer and repeated unchanged state does not, and that an actually stuck unit still stops within60seconds. Rerun all four original normal CLI inputs with current candidate and actual progress enabled through the supported diagnostic path; record exit/output or a newly precise bounded failure rather than claiming timeout suppression as completion. Preserve no-argument normal CLI behavior and target the same source. Add focused ordinary run/compiler-session controls and whole sourcecheck; independent review required.

F3 receipt: meta/evidence/existing-feature-conformance/source-owner-facts/phase3f-session-cli-investigation.json; raw compiler/tmp/phase3f-session-cli/normal-2. Existing traced embedding-host evidence is separate and cannot certify these CLI cases. G1 and driver area must depend on this repair; full G2 remains required.
