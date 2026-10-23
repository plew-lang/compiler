---
id: com-3q2n
status: open
deps: []
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, verification]
---
# Verify closure and dynamic descriptors retain semantic dependencies

## Boundary

Phase 3C / C6. **Bounded closure verification.** Parent criteria: 2, 3, 8.
This is a bounded child of [met-6e6k](met-6e6k.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Codegen/Mono/Call.pw`; `src/Codegen/Mono/InterfaceEvidence.pw`; `src/Backend/Llvm/Closures.pw`; `src/Backend/Llvm/GenericAny.pw`; `src/Ir.pw`.

For closure and dynamic/interface descriptors, trace source result/parameter/receiver terms and dependencies into per-instance descriptor publication, Mid signature preparation and LLVM preflight. Check that phantom/nominal/view information is not erased because payload layouts happen to match. Use the existing interface capability; proof admissibility belongs to B4.

## Exit and Evidence

Each of the two descriptor families has exact publication/reader functions and missing/foreign/instance/proof-replacement plus equal-ABI-distinct-semantics controls. Separate declaration dependency scope from demanded runtime reachability. Close actual descriptor gaps end to end; do not redesign runtime capture/drop or add a new ABI.

Existing starting controls: `dynamic_call_template_generic_instances`, `interface_final_evidence`, `closure_enum_owned`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.
