---
id: met-6vbn
status: in_progress
deps: []
links: []
created: 2026-11-19T07:59:51Z
type: task
priority: 1
assignee: Koji Murata
parent: com-p5um
tags: [frontend, performance, verification]
---
# Index generic layout candidates by sealed nominal declaration


## Contract and measured boundary

[Call-site counts](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-type-equality-call-sites.json)
attribute 5,590,875 of 9,093,179 type-equality comparisons to `scanType`'s
whole generic-layout registry scan (`Codegen/Mono/Ground.pw:1435`). Counts
include recursive comparisons attributed to their external origin. Instrumented
output equals the fixed formal LLVM; diagnostic wall time is not performance.
A per-type simple-head index was separately rejected because whole time did
not improve. Do not repeat that design or add a large pair-result cache.

The endpoint is registry-owned, conservative candidate navigation. The existing
complete `typeRefEq` remains the only semantic equality decision. Preserve exact
reference confirmations, registration order, gen skip, depth refusal, recursive
field discovery and all success/failure behavior. No solver, new type identity,
ARC suppression, weakened verifier or changed source semantics.

## Intended actions and owner boundary

- Inspect the existing Arena/MonoWork same-universe construction precondition;
  resolve index lifetime/fork validity before implementation. Do not casually
  add a global nonce or treat arbitrary foreign raw TypeIDs as valid inputs.
- MonoWork owns its ordered layout rows, private nominal buckets and unindexed
  fallback candidates. Arena remains the type/declaration authority; no reverse
  dependency from Arena to MonoWork.
- Before declaration publication, use the original scan. After successful
  publication, derive the index once from actual retained layout rows and
  immutable Arena facets; later append updates rows and navigation together.
- A sealed `hasNominalIdentity()` declaration offset is only a necessary filter.
  Query its bucket plus unindexed candidates in original index order. Unsupported
  input heads use the old full scan. Every candidate still uses full equality.
- Read with a cursor/range, without per-query candidate array reconstruction.
  Readonly Arena input must not create repeated whole-state copies/retains.

## Guarantees and controls

This is an optimization/refactor: use meaningful existing behavioral GREEN,
not a fabricated source RED. Demonstrate the baseline excessive comparison work
and reduced candidate counts independently of whole-time improvement.

Cover same declaration/different children, same name/different declaration,
same declaration/different spelling, views, projection/record/legacy fallback,
keyed/unindexed mixtures and first match order, pre-freeze registration then
facet updates/publication, failed publication, late append and whole-state CoW
fork. Preserve gen skip, depth errors and recursively discovered field layouts.
Inspect raw public construction and existing same-Arena preconditions rather
than claiming bounds alone seals a cache. Check actual source-to-final-layout
consumers and remove the replaced full-scan path only for the proven subset.

## Completion and exclusions

After independent source/controls review, compare old/new compilers on identical
fixed source, alternate runs and retain all samples and output hashes. Adopt
only demonstrated useful whole-time behavior; otherwise reject the prototype
with evidence and leave the 7-second gate open. Final official fixed point and
all phase-three gates remain in the parent workflow. No carrier/seed/main
promotion here. No full compiler registry sealing or unrelated diagnostics work.

Plan review: `diagnostic_report_performance_review` supports registry prefiltering
and the finite controls above. The existing same-Arena raw construction precondition is retained: foreign
MonoWork/Arena transplantation is not newly supported or detected by bounds.
Independent follow-up review confirms a new global identity mechanism is not
required. Same-scope old append must invalidate the derived index, new indexed
append must synchronize it, and whole-state forks must update independently. Current standard suite input is
frozen; prototypes must use isolated snapshots until it completes.

## Opaque head projection and caller evidence

The first isolated Arena-argument prototype passed finite native controls, but
optimized IR of its query caller still allocates/loads the entire Arena before
mutating MonoWork. A readonly callee signature alone did not prove cheap caller
transport. Do not adopt that ABI or claim it removes whole-state copies.

The revised prototype makes Arena construct an opaque scalar GenericLayoutHead
(ref/publication/optional nominal owner). MonoWork query/append take only this
projection; append uses its embedded ref. A private Comp phase coordinator
projects existing refs once before batch index construction. Preparation checks
original generation, count, every ref and publication before any publication;
failed preparation retains the original full scan. Ready queries allocate no
head array. These are navigation hints, not new type identity or source proof.
Same-Arena/producing-registry preconditions remain explicit. Cursor scalars hold
no arrays and must continue only in their originating MonoWork. Native controls
cover unsealed hints, bad batch order/generation, recovery and declaration0.
The public MonoWork factory preserves its existing ten labels/defaults while
keeping the required private index out of its construction signature.
