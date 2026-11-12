---
id: com-5wze
status: open
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

