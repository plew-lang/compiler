---
id: com-ffar
status: open
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

