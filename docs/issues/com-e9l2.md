---
id: com-e9l2
status: in_progress
deps: [com-qehq]
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, verification]
---
# Verify saved result recipes and projection identity at final reads

## Boundary

Phase 3C / C4. **Bounded closure verification.** Parent criteria: 2, 3, 8.
This is a bounded child of [met-6e6k](met-6e6k.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Codegen/Check/Obligations.pw`; `src/Codegen/Check/Bounds.pw`; `src/Codegen/Mono/Call.pw`; `src/Mid/Build.pw`.

Inventory the actual result-recipe variants in Ir, then trace Term/prior-call/project/optional-payload equivalents through sourceCallArgumentType, sourceSelectedCallResult and final type grounding. Keep source owner, callSite/slot and instance environment distinct; do not map recipe IDs onto type IDs or term zero onto Unit.

## Exit and Evidence

Every current recipe variant has its producer and final reader plus matching/wrong call-site, cross-instance, missing fact and genuine Unit/no-value controls. Retain the already repaired PriorCallResult.siteKey check. Repair only an identified variant boundary or link a blocking bounded repair; no new inference in final readers.

Existing starting controls: `source_call_result_site_authority`, `mid_type_recipe_instances`, `prepared_body_expression_owner`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.
