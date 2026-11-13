---
id: com-fur3
status: in_progress
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

## Reverification after the associated RHS migration

The original viewed case still rejects on `c51623ca` and `9fe88cf2`.
It passes on `27421b95` and on `17e89289` (`3b570dd7`). The
[associated binding migration](com-zzf3.md) covers the intervening
transition from the raw binding term to the admitted authored recipe.
The current predicate comparator reads the selected witness's output
and compares it through `typeRefEq`, retaining the exact view attached
by recipe replay. The precise first passing intermediate revision is
unverified.

The matching viewed and matching bare fixtures each print `42` in JIT
and native and pass check on `17e89289`. Both directions of viewed versus
bare, two different trait views, and missing `Preferred` conformance
reject with the expected where-clause diagnostic. The fixed baseline
rejects the new viewed positive fixture. This checkpoint adds only
regression coverage; independent review remains pending.

## Witness substitution for conditional predicates

Independent review traced the original loss to `groundWitnessTypeTerm`.
Its zero-positional-argument branch replaced a parameter with the saved
binder term without preserving the original view. The direct call was
already repaired by using the admitted binding recipe. The same loss
remained when grounding the expected predicate of a conditional impl and
the immediate RHS of a retained projection equation.

`associated_output_conditional_trait_view` rejects on `17e89289`
and succeeds on `ee7bfebf`. Witness substitution now preserves the
authored view on both the ParamId and positional binder replacements.
The matching same-owner instance control also succeeds; changing only
the trait's positional argument is rejected. Six check/JIT/native
controls and six rejection controls passed. Build
`20261113T020149-build-840df8` passed, with same-source medians
6.896634 s and 6.898719 s and identical LLVM in all eight runs.

An isolated native probe reads the admitted parameter
`Box[Worker]#Holder.Item` and inspects the equation transported by
the recipe. Both revisions return `Worker#Preferred` as the normalized
parameter. With the `db463c14` witness substitution, the saved equation
has bare `Worker` and fails the exact type check. With `3f09a219`, both
the parameter and the saved immediate RHS are `Worker#Preferred`.
