---
id: com-nqjd
status: open
deps: [com-m0bf]
links: []
created: 2026-10-24T02:29:50Z
type: task
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, verification]
---
# Stamp late nominal source and synthetic type producers

## Boundary and Entry

Planned paired repair from [C3 inventory](com-m0bf.md#producer-and-reader-inventory),
not a new language feature. Parent criteria 1, 2, 3, 8. C3 classifies;
this task implements its late source/synthetic nominal producer boundary.

Entry: `Resolve/Expr::typedIrRefOfInfo`, `semanticCallableReturnTerm`,
`arrayRefOfElem`; `Resolve/TypeRecovery::typeInfoOfName`;
`Mono/FreeFn::tyRefOfInfo`/`findOrAddTypeRef`;
`Mono/Call::chainStageResultRef`/`registerChainSiteInsts`.
Normal named constructions already preserve the selected declaration through
`contextualNominalMakeRef`; do not replace that working path with name lookup.

## Finite Actions

1. Distinguish source nominal recovery from primitive/structural construction.
   A source nominal append after declaration publication must receive the already
   selected owner/complete term or resolve once in its explicit source domain at
   its producer. Use existing declaration APIs; do not globally stamp pushType
   rows by spelling or mutate a published declaration facet. A bare-name cache
   cannot select among unrelated declarations or bind a lexical ParamId.
2. Preserve the canonical bundled Promise identity for async implicit Unit,
   and Optional/continuation identities for Chain-generated registration.
   Complete terms from child expressions stay complete through nested arrays,
   aliases and generic instances; do not rebuild them from a TypeInfo head.
3. Pair each migrated producer with its actual semantic fact, signature/scan and
   descriptor reads. Reject missing source identity at publication rather than
   reconstructing it downstream. Retire only the paired recovery calls; remaining
   registered-body key recovery belongs to com-6paa. Primitive leaves, Unit,
   function/record structures and rigid ParamId/projection terms need no invented
   nominal declaration.

## Exit and Controls

Exact migrated/removal sites and producer -> fact -> explicit environment ->
final read recorded. Add positive alias/same-spelling declaration, nested array,
async implicit Unit and Chain continuation cases plus missing/wrong-owner
internal controls. Preserve already committed arguments and existing source
order/inference limits. Reuse `async_implicit_promise`, `mid_type_recipe_instances`,
`type_term_closedness`, namespace construction/identity and Chain controls.
A source passing now does not excuse an unstamped published nominal term.
Fresh source check/scoped native and rejection controls, pinned hashes and an
independent completion review are required. Global final gates remain G2.
General type-checker/ABI/inference redesign is outside this bounded task.
