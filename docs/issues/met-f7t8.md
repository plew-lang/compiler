---
id: met-f7t8
status: closed
deps: []
links: []
created: 2026-11-24T04:39:14Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-ucze
tags: [frontend, generics, verification]
---
# Prefer lexical type binders over same-named module callables

A module free function named T changes a lexical generic receiver T.make() from accepted to no-matching-method. Removing only fn T() {} restores check0 and ORC output1. Existing name-lookup section3 and generics lexical binder identity require the declared type binder and its Maker evidence; this is an evidenced receiver binding defect, not a new language rule. resolveIdent currently tries firstVisibleFuncByName before isTypeParamOf. Own only lexical function/method/nominal type binder versus same-named module callable. Preserve actual local closure/value precedence, ordinary global function calls outside that binder, namespace/member visibility, selected target0 and bound dispatch. Do not redesign general namespaces, overload ranking, unsupported features or add type inference. Actual decision must be made by the binding producer and consumed consistently. Related completed com-r88j is a precedent, not an automatically reopened guarantee. com-tr3a owns normal recorded-binding reader migration; met-eqw2 owns non-value declaration admission and must not freeze this wrong qualifier classification. Evidence: meta/evidence/rejection-domains/diagnostic-domain-implementation/phase3-lexical-type-binder-receiver.json.

## Acceptance Criteria

TDD with exact paired sources and check/AOT/ORC; record source/carrier hashes and intentional RED. Cover function/method/nominal binders, no-conflict control, genuine local closure shadowing and normal global callable, actual classifier category/target0 and selected bound call where applicable. Fix the source binding authority, not a T spelling special case or later method fallback. Preserve query/error/cache/owner lifetimes; inspect cost of extra binder lookups and avoid unnecessary bind-array reconstruction. Fresh candidate targeted controls, independent neutral review and explicit parent whole/formal gates. No Source promotion by message or fake successful fact.


## TDD and source review checkpoint

Exact initial pair and final combined matrix red-v3 prove conflict3mode refusal versus no-conflict3mode success/ORC1,1,1,1,19,42. Matrix covers function/method/nominal binders, closure use of outer binder, true local closure T priority and normal global T(). Initial matrix v1 included unsupported explicit generic call syntax and is not product RED. API red-v1 compiles/links then aborts at wrong lexical binder classification; API green-v1 on modifiedsource returns ok/empty stderr with immutable input. It checks module callable target0 and all three binding classifier adapters.

Product change moves isTypeParamOf after lexical values/before module callables, with no name-specific branch or later method rescue. The same helper reads its original FuncBindRange instead of reconstructing a temporary Array; comparison/interner order preserved. Independent source review finds no must-fix. Final fresh CLI/native/affected controls and integration review pending; last formal7.329846 is not a measurement of this source.

## Finite acceptance

Resolved at12b1e680. Fresh standardbuild052506 exits0 with unchanged inputs and195 source equality. Fresh matrix6 modes all succeed; conflict/control ORC both match1,1,1,1,19,42. Fresh API native exits0/ok/empty stderr; independent reviewer checked all217 actual input hashes. Related operator48 and opaque24 CLI controls remain successful. typing_obligation_plan_review certifies the finite binding priority repair with no mandatory gap. The producer preserves true value priority and global target0, and the temporary Bind Array reconstruction is removed without changing interner/comparison behavior. Normal whole, formal fixed point/performance and parent-area acceptance remain open; no main/seed/regular-bin promotion. The earlier7.329846 formal source is not this revision. com-tr3a retains full normal binding reader migration; met-eqw2 resumes after this prerequisite.
