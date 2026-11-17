---
id: com-fgck
status: open
deps: []
links: []
created: 2026-11-17T10:47:30Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-bvc8
tags: [frontend, generics, mid]
---
# Publish the viewed provided call result for Mid instantiation


## Reproduced failure and contract

In the com-f18l reproduction, add this method to the provided Source impl
and change main to print `<Provider />.read(value: value)`:

```plew
fn read(value: Item#Mark[K]) -> I64 {
    return self.forward(value: value).number()
}
```

The program passes source check. Native frontend/codegen and JIT fail during
Mid instantiation. The diagnostic build after the static selector handoff
records and consumes the retained inner selector at candidate collection;
codegen still reports `[mid-type] missing body=5 source=4235 substituted=5498`
and `Mid instantiate-fallback detail=18 fn=577`. The raw IDs are run-local;
the affected body is `read`. Removing the argument/result view and passing
the unviewed Value makes the same nested call execute and print 42.

Trace the selected grounded result term and its source-view-bearing template
edge into final call descriptors and the prepared Mid operand type map.
Publish the exact required type using its existing owner. Do not bypass an
unavailable map entry by re-resolving source syntax or using an unviewed term
as semantic identity. Verify native and JIT 42, the unviewed control, and
existing rejection of absent view evidence. Independently review this boundary
separately from the source selector handoff in com-f18l.
