---
id: met-g53w
status: open
deps: [com-qlnc]
links: [com-y8l4]
created: 2026-10-25T12:03:16Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-ucze
tags: [frontend, generics, verification]
---
# Unify overload declaration admission using fixed argument types

## Confirmed Contract and Evidence

P2 finding from independent review of com-ra96/com-zy6r/com-y8l4.
This is a newly recorded ordinary/trait inconsistency, not a regression in that
repair. The currently written spec/07 requires matching generic arity and
positions, while spec/08 gives trait requirements the ordinary rules. The user
has now selected a reviewed replacement rule; [com-qlnc](com-qlnc.md) must first
update the canonical specification and design. Do not implement the superseded
plan of imposing the old generic-shape restriction on trait requirements.

```plew
trait Picker {
    fn pick[T](value: I64, other: T)
    fn pick(value: Bool, other: Bool)
}
fn main() {}
```

Old candidate bin/plewc-dynamic-argument-admission SHA256
23f7d582501b394f3390fbd9e2ebd577cc9892cf6c7de4d5129b70ae5f14b583
and WIP bin/plewc-overload-identity-wip SHA256
b0f8cccb49deb0dc3fb271c62b1e044f8a4201b3f0216f6958987ddd6a9429a5
both accept this unused requirement group with --check exit0 (contrary to the
currently written rule; acceptance is intended under the selected replacement).
The equivalent ordinary free declarations both reject with the spec/07
same-type-argument-count/generic-positions diagnostic. A trait group with
matching generic shapes, differing concrete first arguments and alpha-renamed
method binders accepts on both. Six bounded --check commands; no application
or invalid dispatch was executed. Full sources, exact commands/hashes/results
are retained in meta/evidence/existing-feature-conformance/source-owner-facts/
overload-identity-checkpoint.json; raw scratch is meta/tmp/
phase3-overload-identity-repair/generic-shape/results.json.

## Design Boundary and Required Finite End State

After com-qlnc closes, implement its canonical pairwise concrete-discriminator
contract through one source declaration-admission relation shared by ordinary
callables and trait requirements. Preserve semantic type/binder identity,
default-omitted forms and the existing selector/origin/capability boundaries.
Remove the old blanket sameGenericShape restriction and any replaced independent
admission authority; simply deleting that check is insufficient because the
current overlap relation can prove non-overlap between dependent type patterns.

Reject invalid groups before successful declaration/source publication even
when unused. Preserve selected identity/evidence through generic and existential
consumers, without trait-only inference, late source reselection or weaker full
argument checks. Trace successful admission and failure to actual retained use.

Cover different generic counts/positions, pairwise groups, dependent-only
rejection, aliases/Self/projections, defaults, ordinary/trait consistency,
explicit type arguments and ambiguous calls. Perform affected execution modes
and independent finite completion review. Final G1/G2a/G2b/G3 remain required;
no threshold, verifier or test weakening is authorized by this contract update.

This is distinct from com-y8l4's canonical duplicate-signature identity and is
linked for coordination, not imposed as an invented sequencing dependency.
The source-selection area met-ucze and G1 require this separate repair.

## Current Planning Boundary

The documentation prerequisite is open; this implementation task is blocked on
it. The current user request is task creation, not documentation implementation
or a compiler restart. Existing return-owner/dynamic-argument closures remain
valid in their scopes. The three overload repairs are still check-only WIP;
this shared declaration-admission repair has not been implemented.

## Review of the Selected Contract Change

The user selected the reviewed concrete-argument rule and requested a dedicated
spec/design prerequisite. This section preserves its review, **not a claim that
the canonical documents or implementation already satisfy it**. The required
repair is now unification under that rule, rather than extending the old ban.

Three independent reviewers examined specification consistency, call ambiguity
and soundness, and source-to-consumer architecture. All recommend adoption;
none found a fundamental obstacle or a further major semantic decision needed.
This was a static design review; no compiler/test execution was performed.

Recommended wording for ordinary type-overload declaration admission:

> For every pair of callable forms with the same selector in the same
> declaration-conflict domain, at least one corresponding argument position must
> have two semantically distinct types, neither depending on unresolved type
> parameters. Generic arity and parameter usage at other positions need not match.

Required clarifications:

- A selector is the name plus ordered argument labels. Different selectors are
  separate operations; this type-overload condition does not compare them.
- The discriminator is pairwise. Three declarations may distinguish each pair
  at different positions; no one position need discriminate the whole group.
- Compare normalized semantic type identity. Array[I64] is independent of type
  parameters; Array[T] is not. Include receiver/impl/trait binders, abstract Self
  and unresolved associated projections in the dependency check. Concrete Self
  or a projection already resolved by retained equalities may normalize to a
  fixed type. Do not search new general trait constraints to invent a discriminator.
- Different names for the same type do not discriminate. Conversely, distinct
  nominal types remain distinct even if their representation is identical.
- Apply the condition to default-omitted callable forms. For example,
  f(kind: I64 = 0I64, value: Bool) and
  f(kind: String = "", value: Bool) collide on f(value:).
- Declaration admission does not prove every call unique. Unsuffixed literals,
  contextual literals and closures, existential injection, and sendability
  guarantee erasure can leave more than one applicable candidate. Preserve the
  existing ambiguity error, forward contextual-inference rules, and source
  selection boundary; do not invent priority or retry another candidate after
  selected generic inference/constraints fail.
- Generic argument count and general where bounds are not new discriminators.
  Keep the separate adopted capability-conditioned candidate contract, receiver
  domains, import-origin rules, and trait-provided-member coexistence/preferences.

Implementation consequence: removing sameGenericShape alone does not implement
the proposed contract. callableFormsMayOverlap can establish structural
non-overlap between dependent patterns such as Array[T] and Box[U], but neither
argument is a fixed discriminator under this conservative proposal. Ordinary
functions, methods, associated functions, factories and trait requirements need
the same explicit declaration-admission relation, including default forms.
Retain selected declaration/requirement identity and its own binder environment
through generic/existential consumers; do not add a trait-only approximation.

The com-qlnc prerequisite synchronizes spec/07, linked factory/operator
explanations and name-lookup/generics contracts. This repair covers different generic
counts/positions, pairwise three-candidate groups, dependent-only rejection,
labels, defaults, Self/projections, explicit type arguments and ambiguous calls;
then verify retained selections through native/JIT/generic/any execution.
The existing WIP check-only evidence does not satisfy those completion conditions.
