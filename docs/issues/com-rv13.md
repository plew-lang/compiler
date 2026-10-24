---
id: com-rv13
status: in_progress
deps: []
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: com-kp3y
tags: [frontend, verification]
---
# Reconcile owner payload publication and core final-reader closure

## Boundary

Phase 3D / D1. **Bounded closure verification of implemented storage.** Parent criteria: 2, 3, 8.
This is a bounded child of [com-kp3y](com-kp3y.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Frontend.pw`; `src/Codegen/Resolve/Record.pw`; `src/Mid/Build.pw`; `src/Codegen/Mono/Call.pw`.

Audit only header, expression, binding, completion, aggregate, try and pattern payload APIs: construction writer -> success/failure publication -> PreparedSemanticFacts -> actual Mid/Mono reader. Reuse owner-local Ref-backed storage; confirm removed all-owner tables/snapshots and distinguish required absence from a non-applicable optional fact.

## Exit and Evidence

A seven-family API table identifies writer privacy/state checks and final readers. Retained-reader, fork, missing/foreign owner/session, stable failure and post-success/post-failure writes have applicable controls. Every old writer/table/fallback in this component is removed or explicitly construction-only. Do not repeat the existing storage migration; local gaps require exact paired repair children.

Existing starting controls: `source_owner_payload_stability`, `source_builder_branch_isolation`, `prepared_aggregate_source_owner`, `prepared_try_source_owner`, `prepared_match_source_owner`, `source_fact_directory_private`, `source_prepared_payload_private`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.
