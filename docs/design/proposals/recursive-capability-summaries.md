# Recursive Capability Summaries

**Status: Under discussion.** Review finding R1; tracked by
[met-yotl](../../issues/met-yotl.md). No solution is adopted by this proposal.
Work order and current progress live in the meta
[design progress document](../../../../agents/compiler-design-progress.md#再レビュー指摘の具体化).

## Question and Existing Constraints

How does nominal finalization publish a complete copyability summary for recursive
owned values, without unfolding indefinitely or publishing an active computation
as success? The owning contract is
[Types and Evidence](../types-and-evidence.md#capability-and-conditional-selection-contracts).
The [recursive-value specification](../../../../spec/spec/02-type-system/05-structs-enums.md#再帰的な値型)
permits recursive value types; the
[autounique specification](../../../../spec/spec/02-type-system/06-generics.md#autounique)
requires all owned fields/variants to determine capability, including whether an
autounique declaration varies over its admitted argument range.

Preserve these already adopted constraints:

- Shared handle copyability does not inherit a unique referent's copy prohibition.
  Sendability and destruction are separate properties with different dependencies.
- Instantiation consumes the saved summary and explicit substitution. It does not
  scan fields to invent a different capability decision.
- Active, failed, deferred and completed results remain distinct. A computation
  limit cannot become permission to copy or omit destruction.
- Physical boxing/layout does not decide logical ownership. Empty variants,
  private fields and phantom arguments must retain their specified effects.

## Cases That Must Be Distinguished

| Case | Required design answer |
|---|---|
| `List[T]` owns T and another `List[T]` | Solve `C = Copy(T) AND C`; choose the solution matching finite value-copy semantics |
| Mutually recursive nominal declarations | Identify the ownership component and publish only a completed component result |
| A field is `Ref[T]` or another admitted copyable handle | Stop copy-prohibition propagation at the handle, without stopping other analyses |
| Recursive arguments change but reduce under known summaries | Reuse finite summaries instead of rejecting all syntactically changing arguments |
| Recursion follows `T.Next.Next...` through associated types | Define finite representation, discharge/deferral and termination behavior separately from same-node recursion |

These are design controls, not executed Plew tests or newly adopted source rules.

## Candidate Approaches

1. Solve finite structural ownership components with greatest-fixed-point
   copyability, equivalently least-fixed-point may-be-unique where the equations
   are monotone complements. Keep provisional results private until convergence.
2. Retain a finite recursive summary graph/schema and discharge it through the
   shared capability relation. This can avoid requiring every recursive condition
   to flatten into a Boolean formula over declared parameters.
3. Fully expand type arguments/projections before saving a result. This is useful
   only with a demonstrated termination boundary; naive expansion cannot be the
   general solution.

The initial direction to investigate is a finite structural solution with reusable
summary references, rather than a general coinductive trait solver. The approaches
may be combined; no storage format or algorithm is selected here.

## Decisions to Close

- What are the graph nodes/edges and the exact solution for ordinary nominal
  recursion? Which facts are available while constructing a component?
- What is a complete symbolic summary, and what is its substitution/publication
  contract? What must [bounded reasoning](bounded-capability-reasoning.md) consume?
- Which changing arguments/projections close finitely under declared summaries?
  Which justified obligations can remain deferred, and which request needs a
  resource-limit diagnostic rather than a source-typing rejection?
- How are always-copyable/always-unique declarations classified over their full
  admitted domain without enumerating observed concrete uses?
- What inputs and cache keys preserve binder, projection and conformance identity,
  and what bounds traversal, repeated work and memory?

Ordinary structural recursion can be settled as internal realization of adopted
meaning. A new source restriction, public annotation or capability reclassification
requires user judgment. Do not claim a restriction is necessary before checking
the finite-summary alternative and distinguishing source checking from execution
resource limits.

## Comparison and Completion

[Rust coinduction](https://rustc-dev-guide.rust-lang.org/solve/coinduction.html)
uses recursive List/Send to explain cyclic proofs; it is a reference for choosing
and publishing a recursive result, not permission to generalize coinduction to
every Plew proof. [Swift SE-0427](https://github.com/swiftlang/swift-evolution/blob/main/proposals/0427-noncopyable-generics.md#recursive-copyable)
separately discusses growing associated-type Copyable requirements. Neither
comparison determines Plew's acceptance policy.

Completion requires an explicit finite contract and limits, the cases above traced
from producer through substitution and copy/drop consumers, rationale and cost,
and independent review. Incorporate the accepted result into Types and Evidence
and link its Generics/ownership consumers. Synchronize spec only if meaning changes;
then retire this active proposal after retaining necessary rationale. Closing this
design work does not complete [the capability implementation](../../issues/met-b2la.md).
