---
id: com-947r
status: in_progress
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



## Current final-candidate acceptance

W2 and W3 are independently closed; W4 is in progress. Final fixed-point source is fd8987e5; docs-only follow-up0d18fbf8 changes no product source. Formal median8.139814 seconds is not performance recovery. Six matched pairs are W1b7.879058/final7.919201 seconds; whole RSS medians2301845504/2316312576 bytes. Final retained-boundary native medians140.283ms/30.796ms, actual CLI1.758170/1.292705 seconds. The independent cost/scope review supports conditional adoption, subject to the reviewed memory-safety gates. E original85 plus UAF control/direct-object, generated C38/D50 and native callback/execution/session ASan/LSan are running. Do not claim standard full ASan or full normal GREEN.

[Final candidate evidence](../../../evidence/performance-regression-history/value-passing-implementation/w4-measurement/final-candidate/checkpoint.json) and [independent W2/W3 completion review](../../../evidence/performance-regression-history/value-passing-implementation/w4-measurement/final-candidate/w2-w3-completion-review.json) retain exact scope, candidate/input reconciliation, executed assertions and limits. Baseline failures remain explicit under their original owners; they are not passing coverage. W4 safety/adoption, com-ffar completion, main/seed/carrier promotion and original com-1hd3 recovery are separate and unrecognized by this closure.
