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
If more examples are requested, explain accepted complementary families,
associated-binding identity, and growing projection chains before changing spec.

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
