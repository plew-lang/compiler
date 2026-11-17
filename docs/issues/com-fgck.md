---
id: com-fgck
status: closed
deps: []
links: []
created: 2026-11-17T10:47:30Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-bvc8
tags: [frontend, generics, mid]
---
# Publish provided body parameter types for Mid instantiation


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

## Root Cause and Repair

The diagnostic compiler printed the exact term requested by Mid. In body
read, term 4235 was the prepared source-body parameter, a viewed
Self.Item. The closed ABI parameter was term 5322. The selected inner call
result already had a separate closed result. The prior signature publication
mapped placement-declaration rows but omitted the prepared lexical parameter
rows unless the receiver itself used the dependent nominal path.

The same body finalization boundary now publishes the selected signature
against its prepared source-body parameter slots for authored provided
placements too. It checks the slot count before pairing. This uses the
existing owner and closed type map; Mid's lookup and proof rules do not change.

The new nested regression prints 42 in JIT and native execution. The
bare nested control, five neighboring JIT controls and missing-premise
diagnostic passed. The exact source with the final shape guard passes
compiler check. Independent review and optimized verification are pending.

## Optimized Verification

The exact c899e248 candidate reached the second-generation fixed point in
20261117T105250-self-host-e0dde1 with unchanged inputs and identical LLVM,
runtime and successor binaries. The stage-three median was 7.468379 seconds.
A six-pair same-source comparison against fd53521e produced identical LLVM
throughout, with medians of 7.309119 and 7.298201 seconds respectively.

The optimized fd53521e carrier reproduced the Mid preparation error on
the committed nested fixture. The exact c899e248 candidate matched its
expected output and the five related fixture outputs in JIT. Both
missing-premise cases kept their expected diagnostics. Independent review
of c899e248 confirmed the prepared owner and slot shape agree with the
selected ABI mapping and found no blocking defect in this body handoff.
