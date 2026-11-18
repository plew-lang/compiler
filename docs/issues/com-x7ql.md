---
id: com-x7ql
status: closed
deps: [com-j8k0, com-ew3i]
links: []
created: 2026-11-18T15:24:06Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, mid, ownership, verification]
---
# Preserve outer unique bindings across nested shadowing


## Contract and completion

Implement the binding-scope rules in [com-j8k0](com-j8k0.md). Have frontend
select the exact replaced binding and its scope once. Pass a binding-end
identity to Mid only when the declaration replaces a binding in the same
scope. Keep verifier state consistent with Mid; neither Mid nor LLVM should
reconstruct the decision from name spelling. Preserve RHS access, temporary
cleanup and already-consumed behavior.

Prove RED and GREEN independently of the bare-block change using an existing
statement scope. Cover old and new same-scope values with observable exactly-once
destruction, RHS move, nested shadowing with an outer read, nested shadowing with
an actual move, and borrow controls across real drop versus temporary hiding.
Exercise ordinary and relevant pattern/condition binding scopes. Check native
and ORC output with ownership sanitizer controls, then obtain independent review.

After [com-ew3i](com-ew3i.md) enables bare statement blocks, replace
`unique_shadow_cliff_use.pw` with a success fixture that retains the original
bare block and proves inner value 2, outer value 1, and their destruction order.
Keep a distinct same-scope early-destruction control.

## Ordinary declaration checkpoint

The standalone-block candidate `cb79a227` refuses both the original bare
block and the equivalent if statement for a moved outer owner. This
checkpoint records the current lexical scope's first local during Record
and publishes an existing binding-end identity only for a replacement
in that scope. Verify consumes that recorded identity after the RHS; Mid
already consumes it for EndBinding. Lowered guard continuations retain
their surrounding lexical scope for ordinary declarations.

The converted success fixture now passes check, AOT native and ORC with
exact output `2, 102, 1, 101`, including both destruction points. Existing
same-scope/drop controls and the standalone block control still pass in
ORC. A supplementary ordinary if pattern preserves the enclosing owner.
An ordinary redeclaration after a successful Bool guard still drops the
old value before the following print.

Remaining RED: for an outer unique `f`, a successful
`guard Optional.Some(v: val f) = opt { return }` binds a same-scope copyable
`f`. The current candidate prints the new value before destroying the
old owner. Finish binding-end publication and consumption at guard
pattern acquisition, including its ownership/borrow and failure controls.
The task stays open for that and independent closure verification.

## Closure evidence

Compiler `60beea23` records committed guard replacements by source binding
identity. Verify updates ownership only along the successful continuation,
and Mid ends the same owners after the condition's temporaries are released.
The selected-pattern lowering seals the condition evaluation range before
creating independent payload bindings. Match arms keep their existing lifetime.

The guard fixture failed against the standalone-block candidate and passes
check, ORC, native and LLVM 22 ASan/LSan with exact destruction order. It
covers reverse old-owner order, short-circuit failure retaining old owners,
and discarded and retained reference payloads. Both ordinary shadowing
fixtures pass the same modes. An actual nested move still refuses a subsequent
read in check, ORC and AOT. The nested shadow fixture preserves a pending
borrow across temporary hiding; its existing RHS-move control still passes.
Independent re-review confirmed the former counterexample, initial mismatch,
late failure, and if/while condition cleanup with no remaining blocker.
