---
id: com-4k31
status: open
deps: [com-9hde, com-amjl]
links: [met-c1pg, com-oir7]
created: 2026-11-06T23:54:58Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, generics, verification]
---
# Select view calls using complete trait-instance evidence

Contract: [spec09](../../../spec/spec/02-type-system/09-extensions.md) method-source selection and complete trait-instance views; [Types and Evidence](../design/types-and-evidence.md) sections2-4 and [Name Lookup](../design/name-lookup.md) section5. A selector means canonical trait owner plus every positional argument; no argument omission even with one conformance. Memberless views and associated projections are distinct. Extension sets remain separate from the single complete trait selector; unrelated base members remain visible under the existing rules.

Evidence: [executed investigation](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-view-instance-state.json), source8a2ab6c6, exact Syntax8c89204230c3d865ea95a03382c3fd213731e1de. Sixteen check inputs and five JIT/five AOT executions were independently reviewed. The carrier has experimental cycle Source annotations unrelated to selection; it is not an adopted final candidate. Initial direct-requirement declaration overlap is excluded as a view control; wrong-instance refusal is not validated by failures that also reject matching calls.

## Scope and Endpoint

Consume the shared complete selector produced by type/value lowering through common view/source admission and candidate selection into the retained call target, substitution, proof/witness and final BodyInstance/Mid/backend/JIT use. resolveViewSourceKey currently compares owner and arity without positional argument values; collecting candidates or letting ordinary argument matching happen to select11/22 is not complete-instance selection. Preserve the chosen canonical owner and positional arguments through direct, stored, generic and imported/aliased views; do not reconstruct them from a method's argument list, result expectation, spelling, ambient cursor or projection-only fields.

Coarse candidate buckets may still filter by owner/arity where appropriate, but those filters are not complete identity, conformance proof or final call selection. Do not alter declaration overlap rules merely to make the selection key more precise.

Reuse com-amjl's shared exact receiver/trait-instance justification. Missing conformance/bound must fail before successful source admission; no second view-only conformance solver or existence-as-unique proof. Preserve extension composition, nominal/newtype semantics, same-owner/bound environment, witness substitutions and the specification's unrelated-base-member visibility. Do not make fallback select a different instance in place of an explicit selection. If a candidate/fallback case is not determined by existing base-surface rules, obtain a decision rather than silently ban all unrelated members.

## Guarantees and TDD

Use saved check/JIT/AOT observations as REDs and preserved nongeneric provided-method direct/stored controls. Require positive exact P[I64]/P[Bool] calls with distinguishable bodies, not merely wrong-call rejection: currently matching calls fail too. Execute matching source through direct/stored/generic paths in check, AOT build/native and lazy run as applicable; ensure unused signature errors remain eager. Test missing bound/conformance, wrong complete instance/arity and same-spelled foreign owner without unrelated-evidence reuse. Cover multiple positional args and substitution inside nested view arguments, selected-extension sources, and import alias controls.

For instances with identical call argument shapes, first establish a setup allowed by existing declaration/overload rules (for example an applicable via/provided-method route) or use the actual lower-level selection boundary plus valid source companion. Do not reuse the excluded direct-requirement collision fixture or change overload rules just to manufacture a selection test. Record which wrong-instance outcomes are actually mandated by the existing unrelated-base-member rule; matching failures never certify rejection correctness.

## Completion and Boundaries

Close producer-to-final-call selection with exact target/output assertions, preserved nongeneric/extension controls, removal of owner/arity-only decisions and fallback reselection in affected consumers, required validation and neutral review. This task is the end-to-end acceptance owner after term/syntax prerequisites, not a field-addition or --check-only task. Parent gates/performance policy remain unchanged; no unsupported-feature workarounds, ARC exceptions, new overload semantics, full solver redesign or main/seed promotion. com-amjl retains projection evidence and its existing test repairs; com-bvc8 retains non-cycle projection head/category repair; API authority tickets remain separately required.



## Concrete Associated Extension Control

During com-9hde canonical bundle verification, fresh candidate
`bin/plewc-canonical-extension-identity` and prior candidate
`bin/plewc-extension-publication` both reject the existing
`tests/fixtures/run/extension_assoc_source_select.pw` at its
`Sample#Extra.value()` call with `no matching method for this argument list`.
This is not a newly introduced identity regression. Both candidates also
reject the associated call in the new valid two-path reexport/fragment setup
`tests/compiler/frontend/fixtures/ViewSourceOwners/FragmentAssociatedUse.pw`.
The direct compatibility final-resolver API value/associated contrast is GREEN;
that does not certify the parser's ExtView+ordinary Method path. Trace the
associated receiver/source through the common frontend owner rather than add
another consumer-specific spelling fallback. Keep the existing successful
value-call controls and the exact-instance guarantees above.

## Inherited extension call on a parameterized newtype base

The shared view inventory (com-3jtd) found that the following accepts
in check but fails in JIT and AOT while preparing a Mid body. Removing
the call leaves a type- and value-view control that runs. Replacing the
underlying and the constructor with `Box[Bool]` instead rejects the
view itself. The baseline is compiler `f0ac23c4`, candidate
`92b3cf006403`. The AOT trace reports Mid build detail 3 at fn 0.
Trace the selected extension's method and receiver into the generated
newtype adapter before changing the check or expected output.

```plew
use @Std/Io only { print }

struct Box[T] {}
extension Numbers {
    impl Box[I64] { fn number() -> I64 { return 42I64 } }
}
newtype Wrapped = Box[I64]

fn main() {
    val wrapped = <Box[I64] /> as Wrapped
    val selected: Wrapped#Numbers = wrapped#Numbers
    print(selected.number())
}
```
