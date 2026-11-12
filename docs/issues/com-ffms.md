---
id: com-ffms
status: in_progress
deps: []
links: []
created: 2026-11-12T10:23:29Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-amjl
tags: [frontend, generics, diagnostics, verification]
---
# Reject unresolved trait names in where clauses

## Guarantee and Finite Work

Resolve ordinary where clauses on prepared free functions, implementations
and their members under the original declaration and admitted module scope.
An unknown name or a binding of the wrong kind
cannot become a usable bound or pass source admission because no member/body
happens to use it. Preserve canonical known owners, open positional bounds,
qualified imports, exact argument handling, and the distinction between
source rejection, malformed internal input and analysis limit. Use the
ordinary declaration-bound resolver; projection candidate filtering has a
separate role.

The prepared right-hand side must be a trait head, including its optional
arguments and associated-output predicates. A projection, a view or an
existential type is not a trait head. Raw requirement/extern signature
admission and its frame lifecycle remain with [com-30u1](com-30u1.md).
Associated-type and supertrait declarations keep their existing readers.

Contracts: [generics and where clauses](../../../spec/spec/02-type-system/06-generics.md#where-句)
and [source evidence admission](../design/types-and-evidence.md#5-conformance-evidence).

## Executed Evidence

Using `--check` on an unused `fn unused[T](value:T) where T:Unknown {}`,
a bounded inherent impl (with or without an unused method), and a bounded
conformance, all with empty `main`:

- Fixed `5606588a` rejects the free function with `unknown view source` and
  accepts the three impls.
- Fixed `378d4f6e` rejects all four with `unknown view source`; this comes
  from eager view-source lookup during ordinary clause preparation.
- Impl-publication candidates `790c0f4b` and `da939fd0` accept all four after removing that
  dependency. Acceptance of the free function is a regression; impl
  acceptance is pre-existing in the older baseline.

The minimal impl controls use `struct Box[T] { val item:T }`, then either
`impl[T] Box[T] where T:Unknown {}` or
`impl[T] Box[T] as Marker where T:Unknown {}` with `trait Marker {}`.

## Required Scenarios and Completion

Reject unused free-function, inherent/member and conformance clauses in the
correct source domain at the original trait use. Preserve valid qualified
aliases and zero/open/exact positional bounds. Exercise SyntaxFile and value
AST adapters, include empty/unused declarations and an applicable condition,
and show that successful checks never publish an unresolved owner. Verify the
normal source paths and keep scope restoration and Limit behavior. Follow
task-start TDD and independent completion review. Excludes broader callable
publication and view-formation migration.

This fix is a prerequisite of [com-erlx](com-erlx.md).
