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
