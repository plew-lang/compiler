---
id: met-op15
status: open
deps: []
links: []
created: 2026-10-21T11:05:50Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, ownership, runtime]
---
# Migrate standard references, weak restoration and dereference syntax


## Current Source Inspection

Compiler `ea5f751a8343febe8dfecfa3e88e48ccebdefb27`, spec
`16f2f13970dbe2789214b2206c48af3df21b68c8`, pinned Syntax
`00f740e1178e5b992cfdd30ddaa5a0612ce27b43`. Static source inspection only;
no compiler execution, regression reproduction or performance result is claimed.

## Contract and Observed Gap

Spec03 adopts FrozenRef, shared MutexRef, unique nonsendable Guard, standard `.*`
projection and WeakRef[R] restoration to its exact strong handle R.
[Ownership](../design/ownership-and-access.md#standard-reference-projection-handoff),
[ABI](../design/representation-and-abi.md#typed-operations-and-weak-restoration) and
[Standard Library](../design/standard-library.md) own the internal handoffs.

[Core](../../std/Core.pw) currently defines Ref[T]/MutableRef[T]/WeakRef[T]/
WeakMutableRef[T], with upgrade returning Ref[T] or MutableRef[T] from the two
separate weak wrappers. The new FrozenRef/MutexRef/Guard/Weakable declarations
and their typed integration are absent from the checked standard-library source.
Pinned Syntax and [Lower/Expr](../../src/Codegen/Lower/Expr.pw) implement Arrow/
ArrowMethod (`->`) and internal Deref, rather than the adopted source `.*`.
Internal Deref is therefore not proof of source syntax support.

## Completion Boundary

Migrate construction/conversion, ordinary visibility and exact standard-declaration
registration together with semantic place formation, final writeback, typed weak
restoration, ABI and runtime operations. Guard retain protects cell lifetime;
access protection must also prevent early unlock and destruction/move of an owner
during its final projected use. Preserve existing Ref usage while migrating its
public API; do not add public lifetimes, arbitrary raw reference construction or
a generic user-defined projection trait. Unique-generic support is tracked in
[met-b2la](met-b2la.md); transport/atomic work remains [com-qzpm](com-qzpm.md).

## Trusted Identity Consumer Recheck

Detailed audit [com-nsxb](com-nsxb.md), compiler `78bd9691`, found
Mono/Helpers.pw isRefInst/isMutableRefInst/isStrongRefInst/isWeakRefInst still
classify a one-argument term by head spelling. The adopted standard-reference
handoff requires exact registered declaration identity. Carry that authority into
the new projection/weak operations instead of retaining a name-only classifier.
Existing owner-qualified runtimeIntrinsicDeclaration is a separate useful lane;
it is not proof these type predicates are already declaration qualified.
No same-named-user-type runtime miscompile was reproduced by this audit.
