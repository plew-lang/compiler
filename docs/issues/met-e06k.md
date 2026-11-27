---
id: met-e06k
status: open
deps: []
links: []
created: 2026-11-27T21:57:49Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-3q2n
tags: [frontend, verification]
---
# Restore calls through function-valued record fields

## Contract and confirmed evidence

[spec02](../../../spec/spec/01-basics/02-basic-types.md) record fields and
[spec04](../../../spec/spec/01-basics/04-functions.md) first-class closure values
allow an unambiguous function-valued record field to be called. A record's lack
of methods does not prohibit calling a stored closure. Follow the dynamic-call
contract in [frontend handoffs](../design/frontend-handoffs.md).

Fixed carrier149aacd25456 rejects this existing language input at bundle.transform
with `no matching method for this argument list` (line5):

```plew
use @Std/Io only { print }
fn main() {
    val transform: fn(value: Bool) -> Bool = fn(value) { return value }
    val bundle = (transform: transform, number: 7I64)
    if bundle.transform(value: true) { print(bundle.number) }
}
```

The same form occurs in the current Source snapshot's ExpectedResult probe,
but the reduced input has not yet been run on a fresh current candidate. Keep
that distinction. The cause is not yet established: do not assume a particular
lookup-order fix from the message alone. The fixed-carrier reproduction is at
meta/tmp/phase3-associated-execution/record-field-probe/Main.pw. This surfaced
while auditing met-wxn1; inherited projection/expected-result inference is not
required to reproduce it.

## Finite actions and guarantee

Trace record field type/value retrieval into the shared dynamic-call producer,
retained receiver/field/signature, per-instance descriptor, Mid and LLVM. Repair
the responsible mechanism and remove any competing method/free-name recovery
for this already selected value. Do not solve it only in a later verifier.

TDD and controls: direct record field call; extracting that field to a local and
calling it; existing nominal struct function field; both relevant labels and
wrong label/type refusals; selected field/receiver/signature identity; check,
actual native AOT stdout and ORC output on the same source. Runtime must print7.
Source refusal must not be replaced by a compiler crash or unresolved final fact.

Exclude new unique/linear closure semantics, same-name callable-field/method
precedence changes, and a runtime/ABI redesign. If those become necessary,
stop and request the language/design judgment rather than guessing.

## Completion and assignment

C6/com-3q2n owns dynamic descriptor closure; this bounded repair blocks that
area and therefore met-6e6k -> com-61jt/G1 -> phase3 admission. It is independent
of met-wxn1, whose expected-result test may use the local-extraction control.
Keep the original failing direct-field input here. Do not certify this repair
from met-wxn1's success. Independent neutral review accepted legality, finite
scope and explicit area/G1 ownership. Fresh RED/GREEN, affected-mode execution,
obsolete-path removal, appropriate cost check and final independent review are
required before closure. Normal/final aggregate gates retain their owners.


