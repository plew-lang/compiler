---
id: com-swgs
status: in_progress
deps: [com-ksl8, com-9t8k, com-5d2q, met-qs57, met-v1jg, met-7a8u, met-ycyn, com-qxzc]
links: []
created: 2026-10-24T17:09:12Z
type: epic
priority: 1
assignee: Koji Murata
tags: [performance, mid, verification]
---
# Reduce formal self compilation median below six seconds

## Goal and Boundary

User priority on2026-10-25: formal self-compilation median below6 seconds,
with unchanged language meaning, ownership and always-on correctness checks.
3E remains closed;3F is deferred while this explicit performance task is active.
The earlier7s stop does not prevent this newly authorized investigation.

Baseline production36680385, measured carrier
bin/plewc-phase3e-target-cost-fixed SHA090240dd513a530998c9025c43323f3243fc3206653e1aee1af657ed7503ddad,
formal20261024T144321-self-host-f35ef5: generation2 fixed point, median7.072914s.
Existing trace/samples identify shared Mid verification, instantiation and drop
work. Reuse matching-source evidence; do not call different-source timings a
measured implementation speedup.

## Execution and Exit

com-ksl8 owns the finite initial cost/selection investigation. Implement each
selected optimization in an explicitly scoped child with input validity, removed
repeated work, correctness contrasts and independent review. Keep failed
candidates and total timing, not just isolated helper speedups. No verifier
weakening, compiler-name exceptions, ARC suppression or LLVM text surgery.

Completion requires the standard formal generation fixed point and median below6s
with frozen inputs and no other builds/tests; a separately saved measured compiler
must pass affected source/IR/ownership controls. Run applicable whole correctness
gates at the resulting milestone. Keep source/carrier/std/Syntax/toolchain hashes,
per-run timings, regressions and independent admission in durable meta evidence.
No main/seed/adopted-carrier promotion is implicit.
