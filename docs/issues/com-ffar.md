---
id: com-ffar
status: closed
deps: [com-uiri]
links: []
created: 2026-11-09T14:53:00Z
type: task
priority: 2
assignee: Koji Murata
tags: [ownership, backend, mid]
---
# Integrate and validate the selected value-passing optimization

## Entry Condition and Guarantee

Use the [com-rv7l design and entry matrix](com-rv7l.md#investigation-result-and-recommended-design)
and the actual com-uiri decision, not the broad com-nkoa effect-precision scope.
All changed common-helper users, adapter-supplied parameter bindings, indirect
calls and requested JIT definitions must agree on the deterministic physical
signature protocol. Caller-specific inability to reuse storage selects a
snapshot, never a different unannounced callee ABI.

Proceed only after the design approval and positive prototype decision. Update this ticket to the exact accepted lane and entry scope before implementation. A completed prototype ticket alone is not adoption permission.

Integrate the selected private physical ABI through its common descriptor/classification owner, call emission, declaration/definition, callee binding and every affected adapter/publication consumer. Remove competing lane decisions. Retain conservative snapshots where required; no arbitrary aggregate-size threshold or compiler-specific ARC suppression. Synchronize adopted design contracts; source language meaning remains unchanged.

## Coverage and Completion

Reconcile every scenario/entry from the design matrix with executed meaningful assertions and structural evidence, including aliases/later evaluation, ownership/destruction, escape/async, generic/default, closure/witness and lazy/JIT paths as applicable. Any unaffected/unsupported entry must demonstrably retain an internally consistent protocol, not be silently counted as passing coverage.

Complete targeted TDD, fresh build, affected normal/generated/dependency tests, applicable ASan/LSan and formal self-host fixed-point/performance gates on the final frozen candidate under existing rules. Review caller/callee attributes, ownership acquisition, temporary storage and final machine-code effect. Compare old/new on identical source separately from formal timing; report actual benefit and residual cost rather than assuming recovery. Independent neutral review and synchronized contracts/evidence are required. Main/seed promotion remains a separate authorized operation.

## Return to Interrupted Work

The final scenario reconciliation includes the prototype's raw unoptimized and
optimized ABI execution controls, and optional Mid-transform enabled/disabled
controls where applicable, rerun for the final candidate.

After the optimization is accepted or explicitly rejected/deferred, follow [com-1hd3 interruption procedure](com-1hd3.md#interruption-checkpoint-and-return-procedure), re-establish its exact candidate/source and rerun affected checks/performance with changed inputs accounted for. Its original signature-consumption guarantees and performance acceptance remain open until separately reconciled. This task is not a new correctness prerequisite for every phase-three child.

## Exclusions

No general interprocedural effect-summary expansion, new borrow/lifetime feature or blanket API reshaping. If design/prototype discovers a necessary new meaning or heavy architecture choice, stop for the existing user decision procedure. No promise of a particular speedup before measurement.


## Current Execution Authorization

The user selected completion of this task as the thread goal on 2026-11-10,
with Swift as reference, neutral review of small increments, no source semantics
changes, and consultation on any uncertain judgment. This authorizes execution
of the concrete com-rv7l recommendation and its prerequisite prototype. Final
integration remains gated on the prototype's positive evidence-based decision;
it does not authorize assuming that result, bypassing tests or main/seed promotion.
The prerequisite epic now owns its reviewed, dependent implementation units.

## Accepted Integration Scope and Outcome

The positive [W4 decision](com-947r.md#final-candidate-decision) adopts copyable
aggregate Borrow lanes as guaranteed-indirect typed byref homes, independently
of caller-specific reuse. The common descriptor and typed Value/Home protocol
cover body, closure, witness, glue, async acquisition, external-C adapters,
SourceEntry/main/initializer, requested/publication and lazy execution consumers.
Verified local immutable/evaluation-temporary/static-field homes can forward;
unsupported or unproved roots snapshot under the same ABI. Exact entry/lane
proofs forward incoming homes. Competing per-entry classifications were removed.
There is no arbitrary aggregate-size cutoff, new source feature or special ARC
suppression. Semantic Copy/drop and async acquisition remain independently
verified. Adopted contracts are synchronized in representation-and-abi,
ownership-and-access and passes-and-optimization.

[Final evidence](../../../evidence/performance-regression-history/value-passing-implementation/w4-measurement/final-candidate/checkpoint.json)
retains the guarantee reconciliation, RED/GREEN/structure controls, finite
normal/gen/deps/ASan/LSan scope, actual CLI/JIT paths, formal generation3 fixed
point and balanced same-source comparisons. Independent reviews distinguish
applicable passing coverage from baseline failures and optional future work.
The retained-boundary benchmark improves; self-compilation does not measurably
improve (7.879058/7.919201 seconds matched, formal median8.139814 seconds).
The optimization is accepted for its demonstrated bounded benefit and measured
costs, not as a repair of the interrupted signature task's performance regression.

Main, seed and adopted carrier remain unchanged. Full normal and standard full
ASan are not certified. Original failure owners and com-1hd3 remain open. Next
work returns through its documented changed-input validation/performance
procedure; old signature checkpoints cannot certify the changed ABI candidate.

## Closure

Closed as resolved after the independent
[final integration reconciliation](../../../evidence/performance-regression-history/value-passing-implementation/w4-measurement/final-candidate/final-integration-closure-review.json).
Product fd8987e5 and adopted design758af159 are the accepted boundary; no required
in-scope correction or execution remains. Main/seed/adopted-carrier promotion,
full-suite GREEN and original com-1hd3 recovery are not certified.
