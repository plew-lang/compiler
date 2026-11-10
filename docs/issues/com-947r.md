---
id: com-947r
status: closed
deps: [com-h8b1]
links: []
created: 2026-11-09T17:11:02Z
type: task
priority: 2
assignee: Koji Murata
parent: com-uiri
tags: [ownership, backend, mid]
---
# Measure and review the complete value-passing prototype

## Guarantee and Scope

Reconcile the finite scenario/entry matrix, raw/optimized and optional-transform controls; inspect final native transfer reduction separately from ARC. Balanced same-input candidate comparisons, probe runtime, plan builds/preparation/code size and formal fixed-point gates. Independent neutral correctness/performance review yields explicit go/no-go; no-go reverts experimental product changes and follows com-1hd3 return procedure.

Canonical proposal: [com-rv7l](com-rv7l.md#investigation-result-and-recommended-design). Parent [com-uiri](com-uiri.md) retains end-to-end prototype and no-go/return responsibilities. This task does not change source language semantics or authorize main/seed promotion.

## Execution and Completion

Enumerate finite assertions and real producer/consumer inventory before editing; use task-start TDD and independent neutral review at each reviewable increment. Structural RED must identify the missing handoff/protocol rather than unrelated fixture failure. Record actual execution and retained snapshots as separate evidence. Each required obligation above must be reconciled; deferred implementation cannot count as completion. Measure metadata/preparation cost at W2/W4 even when this unit does not claim speedup.



## Final-Candidate Decision

The independently reviewed prototype decision is **GO**, not a claim of original
self-compile performance recovery. Product source is fd8987e5; subsequent changes
are documentation/task records only. Final candidate
`bin/plewc-guaranteed-fixed-point-20261110` has SHA256
`f92a897e32b316664b3b1a43d7014059604cbd6e86e5f884c729ae9e7d3596f7`.

Formal run20261110T111312-self-host-e0c7c3 passed with generation3
LLVM/runtime/binary fixed point and median8.139814 seconds. Six balanced
same-source pairs measure W1b7.879058/final7.919201 seconds (+0.51%); no
self-compile improvement is established. Whole-process RSS medians are
2301845504/2316312576 bytes (+0.63%), binary size +6.49%.
The retained native boundary reduces a 512-byte copy to stable-home forwarding:
140.283ms/30.796ms in the isolated native workload, and actual CLI demand-run
1.758170/1.292705 seconds. Whole-module optimization erases that boundary and
provides no benefit evidence. Preparation body timers are28.914ms and final
receipt validation0.748ms, excluding caller transport and isolated heap costs.

Final CLI72, unsupported-mode12, all12 entry/control groups, view raw/optimized24,
standard dependency and generation25positive/5reject gates passed. Reviewed
scoped safety passed: original raw-compiler E85 including self-compile, actual
UAF detection control, standard direct-object, generated-program C38 with LSan,
all D50 panic cases and native callback/execution/session ASan/LSan. Panic aborts
are not leak-success evidence; JIT instructions themselves are not instrumented.
This is not standard full ASan or full normal GREEN. Full normal761 failures
are retained with old/new baseline reproduction and explicit original repair
owners; two obsolete structural guards were repaired and individually passed.

The independent W2/W3 guarantee reconciliation and W4 correctness/cost/safety
review accept the finite scope with no remaining mandatory implementation gap.
Conservative snapshots for unproved globals, index/dereference/cell/boxed homes
remain valid, not optimized coverage. Original com-1hd3 recovery, whole-suite
integration and main/seed/adopted-carrier promotion remain separate.

[Final candidate evidence](../../../evidence/performance-regression-history/value-passing-implementation/w4-measurement/final-candidate/checkpoint.json),
[W2/W3 review](../../../evidence/performance-regression-history/value-passing-implementation/w4-measurement/final-candidate/w2-w3-completion-review.json) and
[W4 GO review](../../../evidence/performance-regression-history/value-passing-implementation/w4-measurement/final-candidate/final-adoption-review.json)
retain actual assertions, input reconciliation, residual failures and limits.

## Closure

Closed as resolved after the independent
[final integration reconciliation](../../../evidence/performance-regression-history/value-passing-implementation/w4-measurement/final-candidate/final-integration-closure-review.json).
Product fd8987e5 and adopted design758af159 are the accepted boundary; no required
in-scope correction or execution remains. Main/seed/adopted-carrier promotion,
full-suite GREEN and original com-1hd3 recovery are not certified.
