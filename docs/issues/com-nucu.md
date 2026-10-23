---
id: com-nucu
status: in_progress
deps: []
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, verification]
---
# Close partial-input projected member enumeration before source admission

## Boundary

Phase 3C / C2. **Bounded investigation of one query boundary.** Parent criteria: 3, 4, 8.
This is a bounded child of [met-6e6k](met-6e6k.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Codegen/Check/Bounds.pw`; `src/Codegen/Check/CallConstraints.pw`; `src/Codegen/Mono/Call.pw`.

Trace projectedMemberResolution positionalArgsOpen probes through queryViewedTraitConstraint to selected requirement admission. Enumerate only the distinct positional trait instances for one receiver/member, then track the chosen full instance and proof. Use one-instance, two-distinct-input-instance, duplicate-path and associated-output mismatch contrasts.

## Exit and Evidence

Publish the exact enumeration/selection/filter ordering and current controls. If the weak Existence result is being used as SourceAdmission, create a mandatory bounded query/result handoff repair with exact entry/result/control sites and make the area and G1 depend on it. This investigation closes classification, not an unperformed repair. Preserve source precedence and ambiguity; do not merge different input instances, choose discovery order, or introduce an unsupported projection/opening feature.

Existing starting controls: `associated_projection_constraint_identity`, `source_selected_witness_owner_evidence`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.
