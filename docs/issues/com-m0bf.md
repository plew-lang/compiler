---
id: com-m0bf
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
# Classify remaining unstamped nominal producers and paired legacy readers

## Boundary

Phase 3C / C3. **Bounded producer inventory.** Parent criteria: 1, 2, 3, 8.
This is a bounded child of [met-6e6k](met-6e6k.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Codegen/Resolve/Expr.pw`; `src/Codegen/Resolve/ExprType.pw`; `src/Codegen/Resolve/TypeRecovery.pw`; `src/Codegen/Check/Literal.pw`; `src/Codegen/Mono/Call.pw`; `src/Ir/Types.pw`.

Enumerate production constructors lacking declaration identity on the paths from source named construction, body signatures, associated-function inference and registered body receiver terms. Pair each with its consumers in tyRefIsGround, grounded type reads, sameBodyRuntimeRef and final descriptor validation. Distinguish source nominal terms from legitimate builtin/rigid/construction placeholders.

## Exit and Evidence

Each hit is tied to one of the four entry families, a canonical producer or a legitimate construction-only representation, exact fallback consumers and current controls. No unclassified source nominal hit remains. For each real gap create a paired producer-plus-reader repair child with exact API/fixtures and make it mandatory; do not delete all spelling fallbacks at once. This inventory closes classification, not unperformed repairs.

Existing starting controls: `mid_type_recipe_instances`, `type_term_closedness`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.
