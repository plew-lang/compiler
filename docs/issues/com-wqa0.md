---
id: com-wqa0
status: open
deps: [com-qb05, com-17yh, com-v2xk, com-4kti, com-fyxe]
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-acfl
tags: [frontend, verification]
---
# Close operation and constraint API write authority after semantic selection

## Boundary

Phase 3D / D3. **Bounded API/removal verification.** Parent criteria: 2, 3, 8.
This is a bounded child of [met-acfl](met-acfl.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Frontend.pw`; `src/Codegen/Resolve/Record.pw`; `src/Ir/InstanceConstraints.pw`; `src/Codegen/Check/Bounds.pw`; `src/Codegen/Mono/Call.pw`.

After [com-4kti](com-4kti.md) closes its shared generic/projected candidate
selection repair, use its revised source-selection/constraint-publication map
together with the finalized B1/B2/B3 maps. Enumerate operation/constraint constructors, navigation and sealed readers. Verify private owner payload mutation is possible only while Building and auxiliary storage-demand analysis cannot rewrite committed operations. Follow each saved operation/constraint range to admitted callee and final use.

## Exit and Evidence

Operation/constraint API table and privacy/post-outcome/foreign-owner controls close the remaining public writer boundary. Confirm source-local immutable range backing, no second semantic navigation store and no removed storage-summary rewrite. Preserve declaration construction queries and independent access-analysis results; no test-only writer exposure.

Existing starting controls: `source_operation_owner_storage`, `source_call_storage_publication`, `call_template_seal`, `source_call_constraint_evidence`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.
