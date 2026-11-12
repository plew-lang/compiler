---
id: com-fur3
status: open
deps: []
links: []
created: 2026-11-12T21:36:22Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-amjl
tags: [frontend, generics, verification]
---
# Preserve trait views in concrete associated-output equality


## Contract and Reproduction

The [type and evidence contract](../design/types-and-evidence.md) retains
view sources in semantic type identity and compares associated-output
predicates on the selected conformance. The [view specification](../../../spec/spec/02-type-system/09-extensions.md)
defines a trait view as an invariant refinement of the receiver type.

```plew
use @Std/Io only { print }

trait Preferred {}
trait Holder { type Item }
struct Worker {}
impl Worker as Preferred {}
struct Box[T] {}
impl[T] Box[T] as Holder where T: Preferred { type Item = T#Preferred }

fn accept[T, U](marker: T, value: U) -> I64 where T: Preferred, U: Holder[Item=T#Preferred] {
    return 42I64
}
fn main() { print(accept(marker: <Worker />, value: <Box[Worker] />)) }
```

Fixed baseline `34a254d6` and candidate `c51623ca` both reject the
identical viewed associated output with an unsatisfied where constraint.
Replacing both `T#Preferred` occurrences with `T` prints 42 on
`1919348b`. This has no supertraits, associated-output forwarding,
or condition inside the callee. It was isolated during independent
review of [com-80t4](com-80t4.md), whose symbolic projected-subject
regression is separate.

## Scope and Completion

- Find the first producer or consumer that loses or compares the wrong
  view in the selected concrete witness output or the required predicate.
  Follow the exact view identity and substitution through call admission
  to final execution. Preserve the saved selection and remove any
  competing derivation responsible for the mismatch.
- Exercise check, JIT and native for the matching viewed and bare cases.
  Reject mismatched views, viewed vs bare, and an unsatisfied view
  conformance. Keep existing type-view and associated-output controls.
- Record the source-to-consumer evidence, fixed-candidate RED, result and
  independent review. This is a repair of existing invariant view
  equality, with no inheritance, syntax or solver expansion.
