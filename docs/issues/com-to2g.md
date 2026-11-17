---
id: com-to2g
status: open
deps: []
links: [com-jbau]
created: 2026-11-17T12:41:19Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, ownership, verification]
---
# Require stable shared-cell identity for static inout rejection


## Contract and Reproduction

Spec/03 requires evaluation of each shared place once, with the selected
cell held across argument evaluation and the call. Distinct evaluated cells
are valid. Only an established static overlap may fail at compilation;
otherwise Access compares the evaluated cells. Follow
[Ownership and Access](../design/ownership-and-access.md).

The c41653f1 fixed candidate rejects both check and JIT for a valid
three-argument call: the first and last arguments are `inout current->value`
and the middle argument replaces mutable global `current` with a new cell.
The first selected cell remains pinned, the second refers to the replacement.
The intended outputs are 1 and 2. Current Verify/Ops.classifyInoutPair
claims static overlap from `exprSyntaxEq` on those shared places.
A readable exact reproducer is saved with the execution evidence in meta.

## Required Change and Verification

Establish stable cell identity and overlapping projection from legitimate
retained source facts before rejecting. Preserve static rejection for
definite conflicts, the value-place rules, mixed/disjoint success, and
runtime failure on actual unproven aliases before any conflicting effect.
Make the producer and Access consumer agree on any uncertain case so the
check reads already evaluated, pinned cells exactly once. Avoid a separate
syntax-equality authority. Cover the mutable rebinding contrast, an immutable
same-cell negative, truly dynamic same/different cells, shared container
granularity and source-to-Access lifetime. Verify check, AOT and lazy modes,
actual diagnostics or call effects, independent review and normal gates.

This repair does not add general alias inference or change the test audit
owned by com-jbau. com-yeua must not classify unproved shared conflicts as
source errors while this repair is open.
