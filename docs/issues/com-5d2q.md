---
id: com-5d2q
status: in_progress
deps: [com-9t8k]
links: []
created: 2026-10-24T17:27:48Z
type: task
priority: 1
assignee: Koji Murata
parent: com-swgs
tags: [performance, mid, verification]
---
# Measure CPU time inside common Mid preparation passes

## Diagnostic Boundary

Temporarily wrap common Mid Verify/FlagInitialization/Instantiate/appendLocals/
instantiateMidTerm/Drop functions with libc clock CPU timing. Aggregate per-term
cost inside each canonical instantiation; no per-term printing. All original
functions and results execute, no checker/proof/ownership condition is bypassed.
Use a separate signed diagnostic commit, standard build, saved diagnostic-only
carrier and watched compiler-source execution. Preserve raw records and source
hashes; revert the complete instrumentation commit after execution and verify
production source is byte-identical to its pre-instrumentation snapshot.

Timing and instrumentation overhead are diagnostic, not a formal self-compilation
value. Inclusive nesting is explicit: Flag belongs to Verify, term/local times
belong to Instantiate. Select the next finite local optimization from measured
pass costs. The user goal below6s is not reached by completing this measurement.
Independent reviewer accepts this separated diagnostic protocol.
