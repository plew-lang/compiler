---
id: com-v2xk
status: open
deps: [com-qehq]
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-ia09
tags: [frontend, verification]
---
# Verify requirement clauses and inherited receivers reach the real callee environment

## Boundary

Phase 3B / B3. **Bounded closure verification.** Parent criteria: 3, 4, 8.
This is a bounded child of [met-ia09](met-ia09.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Codegen/Check/Bounds.pw`; `src/Codegen/Mono/Call.pw`; `src/Codegen/Mono/InterfaceEvidence.pw`; `src/Ir/InstanceConstraints.pw`.

Use B0 inherited/provided and static requirement rows. Reconcile instantiateRequirementCallConstraints, requirementCallConstraintEvidence/selectedMemberConstraintEvidence and environmentWithCallableConstraints with the retained requirement-to-implementation plan and method ParamId map. Follow both declaration and final worklists through inherited logical Self to physical body Self.

## Exit and Evidence

A finite clause-ID/ParamId/receiver map covers ordinary requirement, provided, two-layer inherited receiver and Self in trait arguments. Existing positive/corrupt/missing/foreign/replaced proof controls execute actual callee/Mid where applicable. No positional zipping, Declaration catch-all or ambient receiver lookup repairs a missing mapping. Dynamic proof admissibility itself belongs to B4.

Existing starting controls: `retained_provided_body_constraints`, `interface_boxing_conditions`, `existential_newtype_condition_witness`, `retained_associated_constraint_evidence`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.
