# Recursive Capability Summaries

**Status: Partly settled; source acceptance pending.** Review finding R1; tracked by
[met-yotl](../../issues/met-yotl.md). The finite structural rule is adopted in
[Types and Evidence](../types-and-evidence.md#structural-recursion-and-shared-capability-decisions);
this active document retains the unsettled expanding-projection boundary.
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

The finite structural solution with reusable summary references has been adopted
and independently reviewed. General trait coinduction and naive expansion were
not selected. Its exact physical packing remains an implementation choice; this
does not settle acceptance of unbounded changing projections.

## Pending Source-Acceptance Decision

The user requested concrete examples before setting the basic accepted fragment
and the outcome for requests that do not close finitely. Recommendation: retain the
finite capability/equality fragment and explicit analysis-limit diagnostics,
without silently classifying an uncertain type or rejecting ordinary recursive
List/mutual recursion. This recommendation is **not adopted**. The
[acceptance examples](bounded-capability-reasoning.md#acceptance-examples-and-limits-for-user-review)
separate supported cases, genuine typing errors and unresolved/limited analysis.

### Changing Projection Example

```plew
allowunique trait Link {
    allowunique type Next: Link
}

autounique enum Chain[allowunique T] where T: Link {
    End
    Step(value: T, rest: Chain[T#Link.Next])
}
```

This is a design example, not an executed acceptance test. Its ownership relation
may follow a different associated subject at each step. Equalities that return to
an earlier subject can close a finite component; known nominal summaries may also
collapse syntactically changing subjects. A complementary source candidate family
can use the whole subject's capability symbolically without expanding every child.
Do not classify this declaration as automatically illegal or automatically beyond
all possible finite reasoning.

Distinguish same-component recursion from a declaration such as an allowunique
Link with an allowunique Next associated type, and an owned Chain whose recursive
child is Chain[T#Link.Next]. Repeated discovery can introduce predicates for T,
T.Next, T.Next.Next and so on. A finite schema may describe the relation without
making every useful source query decidable. The open decision concerns admission
and diagnostics for such requests, not permission to guess their answer.

For the distinction between proving nontermination and enforcing a finite budget,
see the [Rust/Swift limit research](bounded-capability-reasoning.md#reference-language-treatment-of-analysis-limits).
The proposed cutoff can stop finite-but-expensive requests too. It does not need
to establish that a projection sequence is actually infinite, and it does not
change the adopted finite structural-component solution.

## Remaining Decisions to Close

The finite component's solution, private provisional state, complete symbolic
publication, binder/summary identity and instance-reader rules are already in
Types and Evidence. Do not reopen them as unspecified merely because this
proposal remains active. The remaining questions are:

- Which changing arguments/projections close finitely under the supported summary
  normalizations, and what acceptance/diagnostic policy applies otherwise?
- How does the approved minimum fragment handle full-domain autounique
  classification when a recursive symbolic relation cannot be reduced far enough?
- Which justified conditions remain residual obligations, and which admission
  requires proof immediately? Coordinate that distinction with R2.
- What source-facing controls distinguish a genuine typing rejection from the
  agreed analysis limit, independently of observed concrete uses?

Ordinary finite structural recursion is settled as internal realization of adopted
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
