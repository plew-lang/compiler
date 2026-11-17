---
id: com-f18l
status: closed
deps: []
links: [com-j2i7]
created: 2026-11-17T10:39:00Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-bvc8
tags: [frontend, generics, verification]
---
# Forward the instantiated output selector with a selected result


## Reproduced boundary

The optimized fd53521e compiler accepts and executes the following provided
method case, printing 42. A diagnostic fd53521e rebuild emitted LLVM and
traced one exact saved match and one instance mismatch at
matchRecordedAuthoredTraitSelector: the mismatching saved selector and result
selector have the same canonical head, but distinct positional terms after
substituting K with Bool. The recorded result selection can therefore miss
the retained authored choice and leave the structural fallback to resolve it.

```plew
use @Std/Io only { print }
trait Mark[K] { fn number() -> I64 }
struct Value {}
impl Value as Mark[Bool] { fn number() -> I64 { return 42I64 } }
trait Source[K] { type Item: Mark[K] }
pub impl[K] Source[K] {
    fn forward(value: Item#Mark[K]) -> Item#Mark[K] { return value }
}
struct Provider {}
pub impl Provider { factory }
impl Provider as Source[Bool] { type Item = Value }
fn main() {
    val value = <Value />#Mark[Bool]
    print(<Provider />.forward(value: value).number())
}
```

## Guarantee and completion

The reader that consumes the retained output-view witness and instantiates
the authored result owns the instantiated selector. Pass that selected
instance to lexical expression recording and candidate collection along with
its result type, or use an existing equivalent retained result handoff.
Do not recover authority by matching only the owner/arity on inferred result
types, re-infer the environment or reselect conformance.

Show RED/GREEN at the consumer, not only stdout: the generic returned
Mark[Bool] must use the saved concrete selector. Include distinct actual
instances and a case whose result merely acquires a view from a caller,
so that a same-head view cannot manufacture source evidence. Cover the
literal-argument and no-premise controls, optimized verification and
independent review. Preserve representation and unrelated candidate lookup.

## Implemented Handoff

The authored recipe reader returns the output selector only after replaying
its retained proof. The retained callable result hands the selected
instantiated selector to lexical call recording, which checks the exact view
is present on the recorded result. No owner/arity recovery or new
conformance lookup is used.

The compiler source passes check. A separate diagnostic rebuild using the
fixed-point carrier observed publication from the already-read output
selector and consumption by candidate collection in the reduced repro.
The two-instance native compiler input produced two publications and matched
42/17 in JIT. A generic identity call returning its caller's Mark[Bool] view
still prints 42, with no publication of an authored output selector.
Instrumentation exists only in scratch. Independent review and optimized
verification remain pending.

## Static Provided Call Follow-up

The independent d4456ebb review identified two readers that consumed only
the result type: static provided calls and expected-result completion.
Both now publish the selected result through the same recorder as direct
calls. A traced nested provided call observed static signature result
selection, exact recording and subsequent candidate collection.

The nested program still fails in Mid after the verified selection. The
failure and its unviewed control are assigned to com-fgck, a separate
required dependency of com-bvc8. This trace demonstrates lexical selection,
not successful Mid execution. Optimized verification remains pending.

## Optimized Verification

The fixed-point c899e248 candidate matched the expected JIT output for
the generic selector, nested static call, parameterized view and
extension-backed view fixtures. Both missing-premise diagnostics remained
correct. Read-only review confirmed recording verifies the exact selector
on the instantiated receiver. A nominal provided-method result with a
missing explicit type argument resolved from its expected result and ran
on both candidates. The independent review's projected expected-result
completion coverage concern remains open: the attempted Item#Mark[K]
fixture was rejected in both candidates during generic body checking,
before it could establish that the selector was published on that path.

## Completed Result Selection

An associated-type equality on a generic receiver grounds Item to Value
before result matching. The expected Value#Mark[Bool] supplies the
method binder without inverting an unresolved projection. The regression
also exercises the same completion with a concrete receiver. Diagnostic
runs on c899e248 reached both late-completion branches and found an exact
selector in the signature; the Direct consumer dropped it. The same
candidate reached static completion for an authored nominal Box[K]#Mark[K]
result but returned no selector from its recipe.

The retained recipe reader now emits an authored outer selector after
reading its saved proof for nominal results too. Projection-receiver
selectors stay separate from selectors on the projection result. Direct
and static completion use the same reader and publisher. Direct recording
places the initial origin before completion so earlier facts cannot
overwrite the completed selector. No new conformance search is involved.
The independent diff review confirmed exact receiver matching and that
call recipe and authored extension origin routes are preserved.

The two permanent fixtures cover the associated static and direct routes
and the nominal static route. A diagnostic candidate printed their
expected outputs, reached all three completions, and supplied their
retained selectors. The existing nested, generic, and extension-backed
JIT fixtures also passed. Formal verification of the new revision is
pending.

## Closure Evidence

On cceb9631 the diagnostic candidate read the selector back from the
initializer expression against the completed result term and matched the
selector's authored source position in all three late-completion cases.
Typed binding annotations can independently supply the later method
candidate; the readback is the assertion for the completion handoff.
The existing unannotated forwarded-result case covers consumption at
candidate collection. Independent review confirmed the distinction.

The optimized fixed-point candidate matched all eight scoped JIT outputs,
both missing-premise diagnostics, and native outputs for both new fixtures.
Isolated self-host 20261117T112124-self-host-9c1635 reached its second-generation
fixed point with unchanged inputs and a 7.500079-second median. A six-pair
comparison on cceb9631 source gave medians 7.354675 seconds before and
7.364672 seconds after, with identical LLVM in all trials. The phase-wide
performance target remains with com-p5um.
