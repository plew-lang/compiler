---
id: com-q6xg
status: open
deps: []
links: []
created: 2026-11-13T22:29:06Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, mid, diagnostics]
---
# Reject unsupported explicit conversions during source checking


## Confirmed source acceptance gap

The same input passes whole-source check on both `e85e5325` and `3bf7023e`
but fails lazy execution with “internal error: program Mid preparation failed”.
The emission-only native path also fails inside Mid.

```plew
use @Std/Io only { print }
struct Slot[T] { val item: T }
fn main() {
    val converted = true as Slot[I64]
    print(converted.item)
}
```

There is no `From[Bool]` conformance for the target. See [spec/12](../../../spec/spec/03-expressions/12-operators.md)
and the [conversion handoff](../design/frontend-handoffs.md#6-conversion-and-existential-handoffs).
Source Record admits the target type and can select a factory, but the remaining
cast path proceeds to Mid without a validated conversion decision. Mid then
tests the grounded types for a primitive conversion or newtype retag and fails.
Check also succeeds for `original as Slot[I64]` with a same-type operand,
where both JIT and native fail during Mid preparation. Establish the supported
identity behavior from the spec before assigning that case an oracle.

## Completion

- Add a rejecting source fixture for the missing conversion. Check, reached JIT
  and native emission must all reject it with a source-anchored conversion
  diagnostic, with no internal diagnostic.
- Preserve admitted numeric, explicit `From`, and exact newtype retag controls
  through check, JIT and linked native. Add a generic case that retains a
  declared conversion witness through instantiation.
- Keep conversion selection with source checking and pass the selected
  conversion and endpoint facts to Mid. Target type admission is handled by
  [com-3jtd](com-3jtd.md); coordinate with the broader
  [conversion-evidence audit](com-loyb.md).
- Verify the source-to-Mid boundary and obtain independent completion review.
