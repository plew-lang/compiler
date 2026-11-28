---
id: met-k93s
status: open
deps: []
links: []
created: 2026-11-28T00:58:13Z
type: task
priority: 1
assignee: Koji Murata
parent: met-wxn1
tags: [frontend, generics, verification]
---
# Investigate nominal Self in generic projection signatures and bounds

## Question and boundary

Resolve the declaration-scope failure for ordinary generic nominal Self in an
associated projection or explicit bound. This is a required bounded follow-up
of met-wxn1, discovered while isolating met-y2ec. Do not widen call-pattern
matching to conceal declaration admission failures.

The independent input family in meta
`tmp/phase3-forward-frontier/mixed-setup-followups-v47/results.json` uses a fixed
v45 native compiler (hash recorded), fresh complete input copies and invariant
input hashes. All variants retain the separate met-2yhf diagnostic failures;
only the additional target failure is relevant here.

Starting source is RecursiveMixedProjection.pw with `Wrap[R] as Parent` and
`type Item = R`. Replacing only `Wrap[R]#Parent.Item` with `Self#Parent.Item`
inside the method signature refuses at the declaration with "trait view requires
a conformance". Adding `where Self: Parent` instead refuses with "unresolved
declaration type has no lexical parameter dependency". The explicit Wrap[R]
version passes with the call-pattern repair. Do not count these earlier failures
as inference RED for met-y2ec.

## Required actions and completion

Check spec Self/trait-view/bound rules and trace its saved declaration receiver,
source recipe, proof and dependency scope. Compare nongeneric Self, generic
Self, explicit Wrap[R], projection and explicit-bound cases. Establish whether
Self was left as a legacy unbound name or the wrong declaration environment was
used; do not weaken dependency validation or special-case this spelling at a
late consumer. For a confirmed existing-contract defect, produce a minimal RED
and repair from source admission through use, or create a finite mandatory repair
child before closing this investigation. A necessary specification decision
requires user judgement. Preserve the evidence and independent review; a note
that further investigation is needed is not completion.
