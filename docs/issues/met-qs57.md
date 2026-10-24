---
id: met-qs57
status: in_progress
deps: [com-5d2q]
links: []
created: 2026-10-24T17:43:34Z
type: task
priority: 1
assignee: Koji Murata
parent: com-swgs
tags: [performance, frontend]
---
# Reuse selected call metadata and index owner-local expression identities


## Boundary

Remove repeated reads without changing saved source meaning or admission:
1. Pass the already acquired CallTemplate expected result/type-argument range
   from resolveBodyCallee to Direct/Dynamic selection and grounding.
2. Pass scalar destruction classification to the private DeclarationAccess
   helper instead of copying the entire Comp. Preserve short circuit/order.
3. Index SourceBodyData expressions with existing expressionIds plus row+1
   sparse slots. Exact key comparison and <=75% occupancy preserve key zero,
   collisions, missing rows, replacement and reconstruction after tentative
   rows are discarded. Other tables and owner/session/outcome isolation stay
   unchanged. No full-arena direct array or shared semantic cache.

Independent scope reviewer b2 accepts these finite changes, measured together
but split into revertible commits. Preserve lookup/growth/replacement/missing,
active/inactive/published and retained/forked owner controls; selected-call
Direct/Dynamic/generic/provided/default controls; destruction closed/deferred/
recipe/Unit and nested global-access controls. Add no test-only public APIs.
Build fresh once, run full source check and affected functional controls,
compare old/new serially on the identical source and emitted LLVM/runtime.
A faster helper is not a whole self-compilation claim. The parent remains open
until formal fixed point, below6s and required correctness admission.
