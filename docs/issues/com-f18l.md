---
id: com-f18l
status: in_progress
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
