---
id: met-2qbc
status: open
deps: []
links: []
created: 2026-11-06T02:36:55Z
type: task
priority: 3
assignee: Koji Murata
parent: com-qnyl
tags: [backend, runtime, design]
---
# Specify managed and unique value eligibility at exposed C boundaries

Bound the future C ownership/representation decision for exposed Buffer[T], Ref[T], String and Array[T] parameters and results. Current scalar/pointer support and repr(c) aggregate classification do not define managed retain/release, unique transfer, C-visible layout or return ownership. Inspect those eight shapes and the shared imported/exposed ABI boundary; propose eligibility, conversions and lifetime ownership, seek approval for public semantics, then assign finite implementation tasks. Until that decision and implementation, retain precise Limit refusal with intended reason and normal status; never accept by pointer-shaped private layout. No promise that every managed type becomes directly exposable; no new source restriction or required phase-three implementation. Reuse com-042v aggregate layout and com-0oxy callback work without duplication.

## Acceptance Criteria

Each of the four families in parameter/result position has explicit design grounds and a disposition: approved interoperable form with bounded implementation owner, or justified refusal/wrapper alternative. Record source-to-C and C-to-source ownership, copy/move, cleanup/failure and representative positive/refusal controls. Independent review; proposal work is distinct from product support. No source semantics changed without user decision.

