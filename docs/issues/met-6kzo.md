---
id: met-6kzo
status: open
deps: []
links: []
created: 2026-10-21T11:49:40Z
type: task
priority: 2
assignee: Koji Murata
tags: [design, mid, ownership]
---
# Close the async input ownership handoff

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
required. The +0 public entry with explicit activation acquisition is a natural
recommendation; changing all internal entries to consuming ABI is an alternative
whose callers/adapters would need the same finalized contract. Neither is adopted
by this issue. Independent review must check acquisition and cleanup together.

[com-tn1m](com-tn1m.md) owns implementation/payload coverage. Closing this design
task alone does not close that implementation investigation.
