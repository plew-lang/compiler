---
id: com-ceny
status: open
deps: [com-atac]
links: []
created: 2026-11-18T13:58:58Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [backend, ownership, runtime, verification]
---
# Forward mechanical async calls through a single activation


## Reproduction

With the async instance entry prototype from [com-atac](com-atac.md),
the [async via fixture](../../tests/fixtures/run/async_instance_via.pw)
prints 42 in both native AOT and ORC. In its LLVM IR, `main` calls the
forwarder's Promise entry, its resume calls the target's Promise entry
and awaits it, and both entries allocate a frame and a Promise. Lower
creates the extra await in `lowerViaBody` for mechanical forwarding.
An authored async implementation that explicitly awaits a target is a
control and may create its own activation.

## Guarantee and Completion

Implement the [one-activation rule for mechanical
forwarding](../design/ownership-and-access.md#async-activation-inputs).
Use the selected final call and ordinary default/argument evaluation,
then forward into the target entry without an intermediate activation
or repeated ownership acquisition. Preserve the exact Promise result,
receiver modes, source diagnostics, argument evaluation order and
exactly-once destruction. Keep authored async bodies on the existing
state-machine path. This issue concerns generated forwarding for the
supported async subset.

Require a structural RED that counts the entry allocations along the
actual delegation path, then prove one target activation in AOT and
ORC plus behavior controls for immediate and suspended completion.
Exercise copied self and moved unique ownership, retain the authored
forwarding control, and obtain independent review.
