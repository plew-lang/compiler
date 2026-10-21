# Bounded Capability Reasoning

**Status: Source-acceptance decision pending.** Review finding R2; tracked with R1 by
[met-yotl](../../issues/met-yotl.md). This document owns the active R2 comparison,
not the adopted contract or work status. See the
[progress document](../../../../agents/compiler-design-progress.md#再レビュー指摘の具体化).

## Question and Existing Constraints

What minimum capability/equality reasoning do ordinary calls, via and conditional
deinit share, and what does each consumer receive? The owner is
[Types and Evidence](../types-and-evidence.md#capability-and-conditional-selection-contracts);
[Generics](../generics.md#capability-discharge-and-witness-admission) consumes saved
conditions and derivations. The
[specification](../../../../spec/spec/02-type-system/06-generics.md#能力条件付き候補と重複判定)
admits only provably disjoint families within limited reasoning, distinguishes
overlap from unproved disjointness, and does not require arbitrary trait solving.

Keep source-selected candidates, a common call contract and their proof together.
No later name search, candidate priority fallback, unknown-as-false conversion or
different solver per consumer is permitted. R1 supplies recursive capability
summaries; this document must not define another ownership derivation.

The [shared relation's ownership, inputs and outcome distinctions](../types-and-evidence.md#structural-recursion-and-shared-capability-decisions)
are now adopted and independently reviewed. The minimum accepted fragment below
is still a proposal: the user explicitly requires confirmation for decisions
affecting source acceptance, even when the internal recommendation is strong.

## Pending User Question

The pending question asks whether to adopt finite combinations of copyable/unique
conditions and established type equalities as the basic acceptance domain, with
explicit analysis-limit diagnostics for requests that do not close finitely.
Ordinary recursive List/mutual recursion must not be rejected merely because they
are recursive; no uncertain capability is rounded to copyable or unique. Await a
reply before treating this minimum domain or limit outcome as an adopted rule.
The user requested concrete acceptance examples and limits before deciding.
The examples below explain the proposal; no source-acceptance policy is approved.

## Acceptance Examples and Limits for User Review

These examples describe the proposed source contract, not results from running
the present compiler. Passing this proof boundary does not waive label, mode,
type, visibility or ownership checks at the rest of the call boundary.

### A. Complementary Copyable and Unique Branches

```plew
fn consume[T](value: T) {}
fn consume[unique T](value: move T) {}

fn forward[allowunique T](value: move T) {
    consume(value: move value)
}
```

The candidates cover Copy(T) and Unique(T): exactly one applies for every admitted
T. The allowunique mode adaptation is already specified. This basic family must
be supported; choosing between these two recorded branches is not another name
search during instantiation.

### B. Several Owned Parameters and Recursive Nominal Values

```plew
autounique struct Pair[allowunique A, allowunique B] {
    val a: A
    val b: B
}

autounique enum List[allowunique T] {
    Nil
    Cons(value: T, rest: List[T])
}
```

The saved summaries are Copy(Pair[A,B]) = Copy(A) AND Copy(B), and
Copy(List[T]) = Copy(T). List's self edge does not create another independent
capability atom on each traversal. Mutual recursion closing over a finite
structural component follows the same rule. No prohibition of ordinary lists,
trees, recursive types or generic combinations is proposed.

For two independent capabilities, complementary groups may cover both-copyable
versus at-least-one-unique, or three disjoint cases: A unique; A copyable and B
unique; both copyable. All these are finite propositional obligations. Source
call-contract compatibility remains a separate requirement.

### C. Associated Types with Established Identity

A term such as T#Link.Next is not rejected merely because it is a projection.
Its declared capability can be represented by an atom. If retained conformance
evidence already establishes T#Link.Next = U, use the same capability condition
as U. Do not require the user to duplicate that equality or distinguish spellings.
Do not equate unrelated projections without such evidence.

A complementary family can sometimes be proved even while its subject capability
remains abstract: for one fixed term S, Copy(S) OR Unique(S) covers its admitted
two-class domain. Such a proof need not expand every field of S first. Concrete
copy/drop preparation still must discharge S's executable capability through its
saved summary and instance evidence; source family proof is not that discharge.

### D. Ordinary Typing or Overlap Errors

| Request | Reason for rejection, not an analysis limit |
|---|---|
| An allowunique caller relies on only a copyable branch | The unique part of its admitted domain is uncovered |
| One branch requires A copyable, another requires B copyable, with both otherwise unconstrained | The both-copyable case overlaps; no priority chooses a winner |
| Copy(T) is used to assume Copy(T#Link.Next), while Next is allowunique | The bound does not give that implication; Next may be unique even when T is copyable |

A general solver cannot justify a false implication. Adding an actual required
bound or changing the family may fix these errors; raising a resource limit will
not. If a purported counterexample depends on ignored summary/equality relations,
it is not a proved overlap: preserve the separate unproved result.

### E. A Request That Does Not Close Under Supported Normalization

See the [changing-projection example](recursive-capability-summaries.md#changing-projection-example).
An owned recursive relation may depend on Copy(T), Copy(T.Next),
Copy(T.Next.Next), and further terms. A fixed-point rule over the same finite
nodes does not by itself answer this expanding request. It may still close using
a finite schema, known summaries or equalities; those cases should be supported
when their proof is available. The declaration alone is not automatically an
analysis-limit error.

The proposed stopping rule applies only when a proof required by the current
admission request cannot close in the supported reasoning, or consumes its
deterministic work/depth allowance. Do not guess a capability, label the source
mathematically invalid, or treat absence of proof as proven overlap. An unknown
compiler-specific numeric limit is not being approved by these examples.

Increasing a resource allowance may help a finite but expensive request; an
unbounded expansion may require a different finite proof/summary or a simpler
declaration/bound. Arbitrary trait satisfiability, inferred infinite chains of
requirements and "a valid program must always terminate analysis" are outside
the proposed guarantee. A source check succeeding also does not promise that
build/run can generate endlessly many distinct concrete code instances.

The decision requested is whether this finite, evidence-based basic fragment and
explicit limit outcome are the intended boundary. It is not a request to outlaw
all projections, accept arbitrary Boolean syntax in source, or approve a general
trait solver. Exact internal representation and implementation budgets come after
that acceptance-policy decision.

## Candidate Minimum Fragment

Investigate the following as a proposal, not an adopted acceptance boundary:

- Capability atoms on canonical semantic terms and justified projections, with
  allowed ranges supplied by binder/trait/associated-type declarations.
- Constants and finite Boolean combinations needed by saved nominal summaries
  and complementary copyable/unique families. Negating a capability condition
  must not become arbitrary negation-as-failure for unresolved trait obligations.
- Equality normalization justified by exact terms and retained associated bindings,
  preserving conformance provenance; no unrestricted search for convenient aliases.
- A shared overlap/coverage interface whose context includes the admitted domain,
  selected candidate identities and evidence environment.

For domain D and candidate conditions F_i, pairwise overlap asks whether
`D AND F_i AND F_j` is satisfiable; coverage asks whether
`D AND NOT(F_1 OR ... OR F_n)` is impossible. These describe proof obligations,
not a mandate to use SAT or enumerate every capability assignment.

## Alternatives and Questions

| Alternative | Benefit | Risk/question |
|---|---|---|
| Small canonical Boolean forms with bounded simplification | Transparent common cases and diagnostic explanations | Must specify supported cases independently of incidental simplifier success |
| Decision graph or another bounded shared procedure | May reuse conditions and avoid expanded formulas | Identity, limits and integration with recursive summaries need a concrete cost account |
| Separate ad hoc checks for each call/via/deinit path | Locally easy to add | Recreates competing decision authorities; unsuitable endpoint |

Close these questions before adoption:

1. Which atoms, normalizations and Boolean operations must succeed in the minimum
   fragment? Where is a recursive summary reference allowed?
2. Which saved equality/projection evidence permits atom identity, and what remains
   distinct even when physical types or terminal witnesses coincide?
3. How does each approved case map to the common relation's already adopted
   proof/counterevidence, unproved, residual, resource-limit and invalid-input
   distinctions? Specify diagnostics without reintroducing separate per-consumer
   outcome systems or requiring a particular enum layout.
4. Which conclusions may be deferred under a declared bound, and which admission
   requires a proof now? A family cannot publish incomplete required coverage.
5. What proof or residual condition survives concrete substitution, and which
   consumers are forbidden from retrying broader source selection?

New restrictions on promised basic cases require user judgment. Choosing a bounded
internal procedure within the adopted contract does not by itself change source
meaning. No general satisfiability engine or new source predicate syntax is a goal.

## Controls and Completion

Compare complementary copyable/unique families; two owned parameters with
`Copy(T) AND Copy(U)`; missing/overlapping branches; identical associated bindings
versus distinct provenance; phantom/shared-handle conditions; and unsupported or
resource-limited requests. Run the same design traces through ordinary calls, via
and conditional deinit. Check common modes/labels/results/default forms separately
from condition satisfiability; Boolean coverage alone does not make a valid call.

[Swift SE-0427](https://github.com/swiftlang/swift-evolution/blob/main/proposals/0427-noncopyable-generics.md)
is a capability-range comparison, not authority for Plew's exclusive families.
[Rust canonicalization](https://rustc-dev-guide.rust-lang.org/solve/canonicalization.html)
is a reference to investigate for stable query identity, not a required solver.

Completion requires a named minimum fragment, common inputs/results and saved
evidence, explicit limits/failure behavior, matching controls across all consumers,
and review together with [R1](recursive-capability-summaries.md). Place the accepted
contract in Types and Evidence and synchronize its consumers. Retain decisions and
remove this active comparison after incorporation; implementation remains separate.
