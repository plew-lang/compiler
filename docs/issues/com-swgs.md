---
id: com-swgs
status: closed
deps: [com-ksl8, com-9t8k, com-5d2q, met-qs57, met-v1jg, met-7a8u, met-ycyn, com-qxzc, com-yyqd]
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

## Outcome: Resolved Within the Performance Boundary

Formal run20261024T192558-self-host-689981 reached generation2 fixed point,
with all three timings6.349646/5.871513/5.899920s and median5.899920s.
LLVM/runtime and both successors match; frozen inputs and standalone timing
conditions held. Saved measured compiler bin/plewc-perf-type-pools-fixed has
SHA6ddf8f7503274af6a0f474cbf02fae9451d8140b942d1c85777d861917bc32d1.
Winning final implementation a1ed4c14/58e5888f passes affected native26/panic2/
reject8 controls; the measured compiler itself passes sourcecheck and the
applicable positive fixtures in the full normal suite.

Whole normal20261024T193137-test-625275 completed exit1:2744pass/12fail/0skip,
inputs unchanged. All twelve failures reproduce with original pre-performance
baseline090240dd on the same latest source/std/fixtures; five runtime-failure
LLVM pairs are byte-identical and runtime hashes match. Ten finite repair or
fixture-maintenance tasks are explicit prerequisites of G2b com-9l3b. They do
not become hidden repairs inside this completed performance goal.

Normal is still red. ASan/LSan is unexecuted because normal prerequisites are
unmet; gen/deps, G2, phase3, main, seed and adopted carrier are not certified or
promoted. No test/verifier/ownership rule was weakened. Main integration is
not authorized by this limited completion.

Durable records: meta/evidence/performance-six-seconds/type-pools-formal-self-host.json,
type-pool-queries.json and type-pools-milestone.json. Independent b2 final review
verified29 nested path/hash references, normal stdout/stderr, all five failed
runtime LLVM pairs, all twelve failure names and the ten G2b dependencies, and
accepted this limited parent completion with no material gap. All nine scoped
performance prerequisites are closed. Further existing-feature conformance
continues at3F/F1 com-4bib and the final G2 gates.
