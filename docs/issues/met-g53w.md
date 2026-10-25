---
id: met-g53w
status: open
deps: []
links: [com-y8l4]
created: 2026-10-25T12:03:16Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-ucze
tags: [frontend, generics, verification]
---
# Enforce shared generic overload shape for trait requirement groups

## Confirmed Contract and Evidence

P2 finding from independent review of com-ra96/com-zy6r/com-y8l4.
This is a newly recorded existing violation, not a regression in that repair.
Spec/07 requires every overload in one selector to have the same generic arity
and generic parameter positions. Spec/08 gives overloaded trait requirements
ordinary selector/signature rules; there is no trait-only exception.

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
both accept this unused malformed requirement group with --check exit0.
The equivalent ordinary free declarations both reject with the spec/07
same-type-argument-count/generic-positions diagnostic. A trait group with
matching generic shapes, differing concrete first arguments and alpha-renamed
method binders accepts on both. Six bounded --check commands; no application
or invalid dispatch was executed. Full sources, exact commands/hashes/results
are retained in meta/evidence/existing-feature-conformance/source-owner-facts/
overload-identity-checkpoint.json; raw scratch is meta/tmp/
phase3-overload-identity-repair/generic-shape/results.json.

## Design Boundary and Required Finite End State

The same-selector group contract belongs to source declaration admission.
Lower/Registration.pw applies sameGenericShape before callable-form overlap;
Check/Duplicate.pw::checkDuplicateTraitReqs lacks the group-shape obligation.
Canonical type equality/overlap is necessary for duplicate checking but does not
prove that a selector group has legal generic arity/positions.

Share the existing ordinary declaration group contract with trait requirements,
retaining canonical binder/type identity and the same selector-label semantics.
Reject invalid groups before successful declaration/source publication even
when unused, keep valid same-shape concrete-type overloads and true duplicate
rejection, and preserve selected identity/evidence through existing generic and
existential consumers. Do not invent trait-only generic overload inference,
rely on a call being made, or broaden signature applicability to mask the gap.
Trace producer to successful admission/failure and actual retained consumers;
remove any replaced independent group/duplicate authority.

Add bounded valid/invalid controls for generic count and generic positions,
ordinary/trait contrasts and renamed binders, then perform affected modes and
independent finite completion review. Final G1/G2a/G2b/G3 remain separately
required. No specification change or threshold/verifier weakening is authorized.

This is distinct from com-y8l4's canonical duplicate-signature identity and is
linked for coordination, not imposed as an invented sequencing dependency.
The source-selection area met-ucze and G1 require this separate repair.

## Planning Stop

New mandatory task discovered during the resumed work. The user-requested
task-omission stop applies. Existing return-owner and dynamic-argument tasks
remain independently complete. The three overload repairs are WIP with source
check-only contrasts, not complete or area admitted; this new group-contract
repair has not been implemented. Record the task and required dependencies,
then await a user instruction to resume the updated finite work scope.

## Review of the Proposed Contract Change

The user proposed replacing the equal-generic-shape restriction with a concrete
argument discriminator and requested independent review. This section records a
reviewed proposal, **not an adopted specification or an implemented repair**.
The confirmed ordinary/trait behavior above remains evidence against the
currently written specification; adopting this proposal would change the repair
direction rather than require adding the old restriction to trait requirements.

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

If adopted, synchronize spec/07, linked factory/operator explanations, the
name-lookup/generics contracts and this task's end state. Cover different generic
counts/positions, pairwise three-candidate groups, dependent-only rejection,
labels, defaults, Self/projections, explicit type arguments and ambiguous calls;
then verify retained selections through native/JIT/generic/any execution.
The existing WIP check-only evidence does not satisfy those completion conditions.
