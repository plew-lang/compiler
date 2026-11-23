---
id: met-ajht
status: open
deps: [met-tsa3, met-ia2q]
links: []
created: 2026-11-23T17:18:10Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-ucze
tags: [frontend, generics, verification]
---
# Resolve inherited existential protocol evidence through final dispatch

## Existing-contract gap and finite questions

The adopted1b22eb22 accepts direct any Index[U64, Output=I64] indexing and
generic T:TaggedIndex where TaggedIndex inherits Index, but rejects indexing an
any TaggedIndex value with a missing Index implementation diagnostic. The executed
source and check/ORC baseline are retained in
[durable inherited_existential_followup record](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-canonical-protocol-demand.json)
and scratch dynamic-protocol-inherited-baseline.json. The source is:

```plew
trait TaggedIndex: Index[U64, Output=I64] {}
// Shelf explicitly implements both Index[U64] and TaggedIndex.
val shelf: any TaggedIndex = <Shelf item=11I64 />
print(shelf[0U64])
```

Spec08 supertraits and existential public requirements, spec12 Index, and design
body-checking/frontend-handoffs own the contract. Investigate retained parent
requirement identity, inherited associated bindings, source applicability,
existential slot selection and final witness realization. Do not treat a bare
same-name member as proof or implement a second selector in LLVM. Distinguish
an existing missing semantic handoff from a genuinely unspecified case; seek
surface decisions only if the canonical documents do not determine behavior.

## Guarantees, limits and completion

Freeze a complete minimal fixture and RED on the adopted carrier, preserving
check/ORC actual output and failure classification. Contrast direct anyIndex,
generic inheritedIndex, explicit parent member call, unrelated same-name trait,
and a different Index key/result binding. Repair the retained source evidence
and its actual final consumer if the existing contract determines acceptance;
otherwise deliver a precise decision request. Preserve ordinary calls and
nominal conformance, evaluation/ownership and witness identity. New existential
features or a global trait redesign are excluded. Independent review must verify
source-to-final-use controls and any removed competing query. Final adoption
requires the applicable phase-three fixed-point/performance/normal gates.

This is separate from met-tsa3's repair of accepting ineligible dynamic targets.
The pre-existing unsupported inherited existential is not silently credited as
fixed or removed from the phase-three area. Wait for the currently validated
met-tsa3/met-ia2q boundary; do not alter frozen validation inputs.



## Independent task/contract review

Reviewer typing_obligation_plan_review confirms this existing-contract scope:
spec08 explicitly admits supertrait assumptions for existential calls, while
spec12 requires the canonical Index instance. This concrete key/result example
has no forbidden nonreceiver Self input. The task is distinct from com-qomc
(newtype conditional boxing evidence) and com-v2xk (requirement/callee environment
mapping); cross-link any shared repair rather than assigning it twice.

Retain the parent trait instance and U64/Output=I64 bindings with the selected
slot/witness, never infer eligibility from the Index spelling. Cover an explicit
supertrait, a diamond reaching the same requirement, and incompatible bindings
or genuinely ambiguous paths. Do not silently treat trait-to-trait `impl P as Q`
as equivalent to explicit supertrait inheritance: spec08 keeps its existential
ambiguity rule. Acceptance must reach actual ORC output, not check alone.
This is task/contract review only; implementation and validation are still open.
