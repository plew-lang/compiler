---
id: com-qb05
status: open
deps: [com-qehq]
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-ucze
tags: [frontend, verification]
---
# Verify written static calls consume one saved source selection

## Boundary

Phase 3B / B1. **Bounded closure verification; repair only an identified local gap.** Parent criteria: 3, 4, 8.
This is a bounded child of [met-ucze](met-ucze.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Codegen/Resolve/Record.pw`; `src/Codegen/Check/Generic.pw`; `src/Codegen/Verify/Call.pw`; `src/Codegen/Mono/Call.pw`; `src/Backend/Llvm/CallBasic.pw`.

Use B0 ordinary/method/factory rows. Trace recordParametricMethodCall and direct/static templates through selectDirectTemplateCall/selectStaticMethodTemplateCall, completeStaticBodyCallee and finalStaticCalleeIsComplete. Inspect Generic/Verify only at the corresponding recorded-call readers. Reconcile labels, full signature, argument/receiver passing, bounds and result projection; do not repeat overload lookup after commitment.

## Exit and Evidence

For each of the three rows record final consumer and removed/legitimate query sites, plus positive and wrong label/type/ownership/bound controls. Any required-fact hole or repeated selection is repaired in its exact producer/reader pair and a fresh control, or blocks this task via a specific repair child. Already correct rows close by source/removal evidence and matching scoped tests, not a fabricated rewrite.

Existing starting controls: `prepared_call_expression_source`, `source_call_proof_evidence`, `call_template_seal`, `generic_constructor_field_width`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.
