---
id: met-6kzo
status: closed
deps: []
links: []
created: 2026-10-21T11:49:40Z
type: task
priority: 2
assignee: Koji Murata
tags: [design, mid, ownership]
---
# Close the async input ownership handoff

## Adopted Contract

[Async Activation Inputs](../design/ownership-and-access.md#async-activation-inputs)
owns the accepted internal design, rationale, alternatives and controls. The
temporary comparison was incorporated and retired. The meta
[progress document](../../../agents/compiler-design-progress.md#再レビュー指摘の具体化)
owns work order; this issue records design resolution, not implementation support.

## Problem and Evidence

Design-only review [met-ukm5](met-ukm5.md), R3; design `1d83231e`, spec
`16f2f139`. This is a handoff omission, not a reproduced UAF or a contradiction
in async source semantics.

[Call materialization](../design/mid-entry-audit.md#evaluation-homes-and-call-materialization)
uses caller-guaranteed +0 ordinary inputs; [ownership](../design/ownership-and-access.md)
does not destroy guaranteed parameters as local owners. Meanwhile
[Frontend Handoffs](../design/frontend-handoffs.md#8-implicit-calls-and-reachability)
requires async entry to own accepted inputs, and
[async lowering](../design/mid-entry-audit.md#async-and-machine-boundaries)
stores entry-to-resume arguments in the frame. The general
[stored-value rule](../design/representation-and-abi.md#stored-values-and-ownership-glue)
requires acquisition when an independent owner is stored, so the desired meaning
is already derivable. What remains unspecified is the producer connecting that
acquisition/transfer to the logical body's initial ownership state and Mid cleanup.

A temporary String passed to an async function may outlive the entry call after
suspension. Saving descriptor bytes alone cannot establish that ownership; a
backend-only retain/drop invention would violate Mid's cleanup authority.

## Completion Boundary

Define one public-entry-to-activation contract in the Mid/ownership home and link
the ABI/runtime consumers to it. Before caller guarantees expire, copyable input/
copy-self/environment requirements acquire independent ownership; unique Move
inputs transfer ownership. Assign producer responsibility and connect the resulting
owners to logical-body entry, normal exits and exactly-once cleanup. Cover first
resume completing synchronously as well as suspension, without conflating source
cleanup with Promise/frame bookkeeping or inventing cancellation semantics.

No new public API, source lifetime rule, second runtime or general coroutine IR is
required. The adopted +0 entry with explicit activation acquisition preserves the
existing call contract. A distinct consuming internal ABI was not selected because
it would expand the consumers to synchronize without a demonstrated benefit here.
Independent review checked acquisition and cleanup together.

[com-tn1m](com-tn1m.md) owns implementation/payload coverage. Closing this design
task alone does not close that implementation investigation.

## Resolution: Design Handoff Closed

Read-only review of the documentation delta against spec03/06/07/14 found the
decision derivable from existing ownership semantics. Common Mid construction
creates the checked input plan; instantiation grounds it; acquisition/transfer
feeds logical initial ownership, Drop and independent verification. LLVM handles
storage and runtime handles separate scheduling/Promise/frame obligations.
Direct and mechanical forwarding entries share one activation boundary.

Temporary input, copy-self, unique Move, environment, generic/indirect entry and
immediate-versus-suspended completion controls are specified in the owning chapter.
No source rule, lifetime extension, cancellation or backend-only cleanup was added.
The execution reviewer found no blocking design problem. No compiler execution,
performance or sanitizer evidence is claimed. Implementation remains com-tn1m.
