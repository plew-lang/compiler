---
id: com-f18l
status: open
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
