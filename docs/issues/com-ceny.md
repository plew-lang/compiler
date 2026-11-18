---
id: com-ceny
status: closed
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

## Structural RED and implementation boundary

Run `PLEWC=/absolute/candidate python3 -B tests/compiler/codegen/test-async-forwarding-activation.py`.
The candidate for `9c0e4cf8` emits three frame allocation calls for the
standalone fixture. The expected two belong to async main and the selected
target. The same test counts Promise creation separately. This is a
pre-optimization check, independent of LLVM inlining.

Lower's `lowerViaBody` is shared by explicit delegation and generated
callable-form witnesses. The execution distinction must follow the generated
body through lexical and concrete owners, separately from the callable's
public async signature. The forwarding body evaluates its existing selected
call and required defaults synchronously, and returns the target's Promise
directly. Copyable receiver and ordinary inputs keep the caller's guarantee
until the delegated entry acquires them. Move inputs are forwarded once.
Mid ownership and access checking remain responsible for the forwarding body,
including any synchronous effects in defaults. The LLVM body route must read
the same execution classification as Mid. It must not infer forwarding from
an await/call sequence in an authored async body.

## Implementation and independent review

Lower marks the generated body and returns the selected call expression
itself. Source and Mid use synchronous ownership for the adapter. Mono
freezes the forwarding kind and the body result in the completed signature.
Both AOT and ORC use that signature to route the body through ordinary
ABI emission, which verifies the return against the public Promise term.
The actual target still uses the async entry descriptor. The authored
delegation check uses the same selected call expression.

RED at `9c0e4cf8`: three frame and Promise allocations where two were
expected. On the final candidate, five mechanical cases (ordinary via,
suspended with a default, moved receiver, generated callable form and
implicit Unit) emitted two allocations for each routine in AOT. A
diagnostic-only snapshot printed emitted ORC body-module IR immediately
before publication and confirmed the same counts. The authored
await-forwarding control kept three allocations in both paths. All six
ORC outputs matched exactly. Thirteen check/native controls and both
async structural checks passed. The suspended copy/default and unique
move fixtures passed focused LLVM 22 ASan/LSan, with exact stdout.

Independent review inspected the selected call and direct Promise return,
the acquisition and drop sites, lexical and final effect edges, and the
frozen signature's publication and consumers. A supplemental ORC probe
matched baseline and candidate evaluation order for explicit arguments,
two defaults and a moved unique ordinary argument, with one deinit after
suspension. Full-suite and phase-level performance gates remain separate.
