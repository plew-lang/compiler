---
id: com-5wze
status: closed
deps: []
links: [com-30u1]
created: 2026-11-12T20:22:54Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-amjl
tags: [frontend, generics, verification]
---
# Resolve projected arguments when admitting concrete supertraits

[Spec08](../../../spec/spec/02-type-system/08-traits.md#トレイトの継承supertrait)
and [Types and Evidence](../design/types-and-evidence.md#4-substitution-and-projection)
require the exact instantiated supertrait constraint. The affected producer
is prepareConformanceSupertraits in src/Codegen/Check/Bounds.pw.

The following input is rejected on 5c1b2723 and 65210d55 at the Middle impl:
`supertrait not satisfied: this type must also conform to the trait's supertrait`.

```plew
trait Marker { type Type }
trait Parent[T] {}
trait Middle: Marker + Parent[Self#Marker.Type] {}
struct Worker {}
impl Worker as Marker { type Type = I64 }
impl Worker as Parent[I64] {}
impl Worker as Middle {}
fn main() {}
```

Adding `Marker[Type=I64]` to Middle's declaration makes the input check.
The concrete Marker impl already supplies that output in the rejected
input. There are no callable requirements, so the rejection precedes
signature recipes, existential adaptation and call selection. The
verified evidence localizes the failing producer; whether it loses
normalization or selects a wrong query environment remains to be traced.

## Acceptance Criteria

Admit the concrete parent by the selected Marker witness and retain the
normalization and exact Parent instance for replay. Verify order
independence of the listed supertrait edges and of the impl declarations,
a competing Parent[Bool], and rejection when only the wrong parent
instance is available or the Marker prerequisite is absent. Verify the original no-method RED
and an inherited associated-signature consumer through check/JIT/native.
Inspect the producer and final replay for fresh conformance selection.
No new syntax or general solver redesign. Independent review is required.


## Retained parent admission and replay

The producer substitutes each authored clause in its conformance environment,
records the projection proofs using source admission, selects the exact
normalized parent, and publishes the source slot, original terms, equations,
and frozen parent proof together. Each clause uses the same declared
environment independently of list and impl order. The replay reader checks
the source slot and shape, grounds the saved terms, replays saved equations
and proofs, and compares the exact resulting parent. A concrete signature
whose authored positional recipe already evaluates the projection uses that
retained parent's instance for comparison.

On `fefa4c07`, `concrete_supertrait_projected_argument` and the signature
case reject at parent admission. Intermediate `9204154a` admits the bare
signature but rejects its fully qualified equivalent when its child recipe
already produces I64. Candidate `072faa8a` passes both. The public signature
fixture exercises generic replay, both supertrait orders, a reverse-ordered
impl, and a competing Parent[Bool], printing 42 and 43.

Standard build `20261112T220246-build-ce999e` and generation
`20261112T220623-gen-df42e7` passed. Ten public check/JIT/native controls,
six targeted rejections, and the internal retained-supertrait check/native
control passed. The internal fixture preserves its write-once, exact
witness and missing/foreign edge assertions under the updated row API.
Same-source medians were 6.810221 s and 6.813270 s, with identical LLVM
across eight runs.

Independent review of `072faa8a` confirmed the stored source slot,
normalization and exact parent proof reach replay without new selection.
Additional checks covered ambiguous Marker witness paths and JIT with
nested projections, conditional impls and a generic receiver. The reviewer
isolated an associated-binding RHS defect that also reproduces without
a positional supertrait argument on the old candidate. Its existing
repair owner is [com-zzf3](com-zzf3.md).
