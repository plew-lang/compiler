---
id: met-qs57
status: closed
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

## Outcome

Resolved by 6a876323 (scalar destruction query),318e6be0 (saved call context),
f53ac39d (owner-local expression index),499c0d7f (dedicated publication control).
Standard build20261024T174941-build-da3780 exit0/frozen inputs; fresh c37f338fbf0be63af9c57ec8688142da05e9110019541845b4297c8759273363 passes
all sourcecheck and22 native/4 reject controls. Same-source serial alternating
3 runs each: old6.931619/6.904798/6.926046; new6.611139/6.606803/6.605769s.
Median6.926046→6.606803s, all LLVM44f54532b2fe6fac647186a10b35654c42e1e9d09e4aa9614c30e5aa22179203.
Meta evidence/performance-six-seconds/source-query-index.json owns hashes,
receipts and individual results. b2 independent reviewer rechecked ten references,
240/239/5933 input fingerprints and all six compressed LLVM outputs and accepts
this bounded task. Formal <6s/fixed point and whole correctness admission remain
open on parent. met-v1jg owns the next measured navigation-copy/division slice.
