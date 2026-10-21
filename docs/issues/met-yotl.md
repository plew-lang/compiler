---
id: met-yotl
status: in_progress
deps: []
links: []
created: 2026-10-21T11:49:40Z
type: task
priority: 1
assignee: Koji Murata
tags: [design, generics]
---
# Specify recursive capability summaries and bounded discharge

## Active Discussion

R1: [Recursive Capability Summaries](../design/proposals/recursive-capability-summaries.md).
R2: [Bounded Capability Reasoning](../design/proposals/bounded-capability-reasoning.md).
R1's finite structural component and the shared decision authority are adopted;
the source-acceptance fragment and expanding-projection limits remain pending
user judgment. The meta
[progress document](../../../agents/compiler-design-progress.md#再レビュー指摘の具体化)
owns current work order; this issue retains the joint completion boundary.

## Problem and Evidence

Design-only review [met-ukm5](met-ukm5.md), findings R1/R2. Inputs: design
`1d83231e`, spec `16f2f139`. No implementation failure or performance result is
claimed. [Types](../design/types-and-evidence.md#capability-and-conditional-selection-contracts)
assigns nominal summaries and conditional proofs to their producers, but calls
their reasoning "adopted bounded" without defining the supported fragment,
recursive solution or common discharge result.

For `List[T]` owning T and another `List[T]`, the structural equation is
`Copy(List[T]) = Copy(T) AND Copy(List[T])`. The intended copyable result for
copyable T requires an explicit recursive solution, not Active-as-false or an
unfinished result published as success. Recursive nominal values are legal under
spec05. Recursion through changing associated-type projections may not close over
the same finite set of type terms; it is a distinct termination question.

Conditional call/via/deinit families also need a shared minimum capability/
equality fragment for overlap and coverage, with retained evidence and distinct
unknown/resource-limit outcomes. Merely requiring one authority does not specify
what that authority can decide.

## Completion Boundary

- Define finite summary representation and the selected solution/publication rule
  for nominal ownership SCCs. A recursive graph/schema is a valid alternative to
  flattening every condition into a Boolean expression over parameters.
- Preserve copyable-handle stops without confusing copyability, sendability and
  destruction dependencies. Honor declared element capability ranges.
- Explain which changing type arguments/projections close under saved summaries,
  what remains deferred, and how nontermination/resource limits are diagnosed.
- Define the minimum supported atoms/operations, canonical equality/projection
  inputs, and common outcomes/proof retention for disjointness and coverage.
  Ordinary calls, via and conditional deinit consume this same decision contract.
- Specify ordinary recursive List, mutual recursion, handle/phantom controls,
  projection growth, all-variant capability, and conditional-family controls.
  Keep arbitrary trait satisfiability and a universal solver outside the goal.
- Update the owning Types contract and its Generics consumers; obtain independent
  review of termination, soundness and source acceptance boundaries.

Existing semantics can determine the ordinary SCC solution internally. Any new
source restriction, rounding an uncertain capability to unique/copyable, or new
public annotation requires user judgment first. This task adopts none of them.

This is a design prerequisite for [met-b2la](met-b2la.md)'s capability feature,
not a requirement to implement that whole feature inside [met-si6j](met-si6j.md).

## Partial Internal Resolution and Pending Source Judgment

The [structural summary/shared decision contract](../design/types-and-evidence.md#structural-recursion-and-shared-capability-decisions)
now chooses the least fixed point of may-be-unique for closed finite structural
components, with private provisional state, complete symbolic publication and
explicit instance substitutions. Recursive summary graphs do not make ordinary
conformance-proof DAGs cyclic. A shared relation supplies call/via/deinit proof
outcomes without taking over their complete applicability rules.

The semantics reviewer independently confirmed this finite internal rule follows
existing all-field/all-variant ownership and adds no source restriction. No field
rescan, runtime classifier or Active-as-success shortcut was adopted.

A user question remains open: adopt a specified finite capability/equality
fragment as the basic accepted domain and explicitly report requests that cannot
close finitely as analysis limits. The user requested concrete examples before
deciding; the [proposal](../design/proposals/bounded-capability-reasoning.md#acceptance-examples-and-limits-for-user-review)
now distinguishes basic supported families/recursive summaries, established
associated identity, actual typing/overlap errors, and limited or unsupported
required proof. Neither the acceptance boundary nor a fallback reclassification
is adopted. R1/R2 remain open even though internal shared ownership is settled.
No source/implementation execution, formal general termination proof or performance
result is claimed.
