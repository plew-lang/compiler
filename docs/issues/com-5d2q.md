---
id: com-5d2q
status: closed
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

## Outcome

Investigation completed. Diagnostic commit a43cf64f was fully reverted by
462073ec. All three production source hashes equal the pre-instrumentation
snapshot; default bin/plewc was restored to production bf6de4f19011e75b764bc63a7e52b0f2c79573d664828d1483fa4a9087849258.
Meta evidence/performance-six-seconds/mid-cost-attribution.json retains twelve
hashed raw references, CPU totals, clock calibration and uninstrumented profile.
Flags cost about 0.054s; term intervals include substantial clock overhead, so
neither is a measured one-second improvement opportunity. Source-call metadata
navigation and whole-Comp argument snapshots are next bounded candidates in
met-qs57. CPU categories are inclusive and cannot be added blindly.
Independent b2 reviewer recomputed all seven totals, term count, twelve hashes,
source restoration and binary identity; no completion blocker. This closes the
diagnostic investigation, not the below-six-second parent goal.
