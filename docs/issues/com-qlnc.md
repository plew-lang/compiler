---
id: com-qlnc
status: closed
deps: []
links: []
created: 2026-10-25T14:02:11Z
type: task
priority: 1
assignee: Koji Murata
parent: met-ucze
tags: [frontend, generics, documentation]
---

# Specify bounded structural disjointness and shared overload admission

## Selected Direction and Dependency

Specification/design prerequisite for [met-g53w](met-g53w.md). The user selected
bounded structural reasoning after the fixed-type-only rule rejected the public
Optional.unwrapOr API. Keep its eager/lazy names and signatures; do not rename
the lazy operation to unwrapOrElse to accommodate the implementation.

For ordinary type overloads in the same conflict domain and selector, establish
a distinguishing argument position for each pair of common callable forms.
That position may use ordinary type structure and already established type
equalities to prove the two parameter types different for all allowed receiver
substitutions. Closed concrete types remain a simple sufficient case, not the
only permitted discriminator. Different ordered labels are different selectors.
General where/trait satisfiability, candidate priority and specialization are
not introduced. Document this refinement before changing the implementation.

## Required Examples and Binder Identity

The receiver environment is common to the compared methods. Its parameters are
shared symbolic types, even while checking a generic body; treating them as fixed
for one invocation does not prove distinctness for every possible receiver.
Method-owned parameters belong to each declaration separately and are fresh
relative to those of another candidate. Neither spelling nor declaration-list
position establishes that two binders are the same.

| Parameter types | Required outcome and reason |
| --- | --- |
| I64 vs Bool | Distinguishable concrete types. |
| Array[I64] vs Array[Bool] | Distinguishable complete nominal arguments. |
| Receiver T vs I64 | Not a guaranteed discriminator: T can be I64. |
| Receiver A vs receiver B | Not guaranteed: A and B can coincide. |
| Receiver T vs fn() -> the same T | Distinguishable: equality would require a cyclic structural substitution. Preserve Optional.unwrapOr. |
| Array[T] vs Box[U] | Distinguishable nominal constructors, without solving bounds. |
| Array[T] vs Array[I64] | Not guaranteed: T can be I64. |
| Candidate-owned T vs fn() -> other candidate-owned U | Can coincide with T = fn() -> I64 and U = I64; reject without another discriminator. |

A finite occurs check detects a variable inside its own proposed replacement;
it does not require infinite expansion or a general proof of nontermination.
Recursive nominal structs/enums retain their declared identity; do not unfold
fields or equate a nominal recursive type with a structural function type.
An unresolved associated projection is unknown unless retained equalities
normalize it. Unproved disjointness and proved overlap must remain distinct,
even when both require rejection under the conservative acceptance policy.

## Architectural Problem and Finite Work

The original ordinary/trait mismatch exposed fragmented admission authority:
registration had an extra generic-shape predicate outside the shared overlap
helper, while trait checking called only the helper. Specify one owner of the
complete decision, not parallel entry-specific predicates kept in sync.

1. Revise spec07's fixed-type-only wording from cc13283 to this bounded structural
   criterion. Reconcile functions/defaults, factories/memberwise factories,
   generics, trait requirements and operators, including Optional's explicit
   eager/lazy specification. Audit standard public overloads against the rule;
   do not repeat the prior review's omission of the nil-coalescing API.
2. Define the proof inputs: canonical type/declaration identities, shared
   receiver substitutions, separate lexical method binders, known equalities,
   callable omission forms and existing receiver/origin/capability domains.
   Keep generic arity/usage free to differ. Explain why method-owned T and U are
   not one variable and why receiver-owned T is shared across candidates.
3. State the bounded structural operations and their limits: compare nominal,
   function and other ordinary type structure, maintain consistent substitutions
   and perform occurs checks; use retained normalization evidence. Do not solve
   arbitrary trait bounds, assume unknown projections distinct, or fall back to
   eventual concrete instantiation to rescue a source ambiguity. Preserve the
   existing fixed analysis-limit policy and distinguish AnalysisLimit/unknown
   from a proof. Retain the earlier requirement of a distinguishing position:
   refine how that position is proved, rather than accepting solely because of
   interactions between multiple individually non-distinguishing positions.
4. Apply the same rule to common default-omitted forms and pairwise candidate
   comparisons. Keep declaration admission separate from call ambiguity caused
   by literals/conversions, forward inference and selected-candidate constraint
   validation; do not invent ranking or retry a failed candidate.
5. Update name-lookup, generics and frontend-handoffs to define the common
   authority's complete inputs/result, every supported declaration entry,
   successful-admission boundary and removal of independent predicates.
   Free functions, methods, associated functions, factories and requirements
   must follow one rule. Entry-specific traversal/diagnostics and genuine
   domain/origin/capability contracts remain explicit.
6. Reconcile met-g53w's acceptance cases and WIP fixture classifications with the
   final documents. Record revisions, check links/contradictory claims and obtain
   independent completion review before closing this prerequisite.

## Completion and Exclusions

Canonical spec/design agree on the examples, proof scope, binder identities,
unknown/limit outcomes and decision ownership. In particular, unwrapOr remains
valid while receiver T/I64 and A/B are not declared distinct merely because
receiver parameters are not method-owned. Preserve pairwise/default rules,
selected identity/environment through final consumers and the requirement to
remove independent acceptance authorities. A helper-sharing instruction alone
is insufficient.

This is a documentation task, not overload implementation, test expectation
maintenance, a build or performance gate. Keep it open until the real documents
and independent review are complete; the present request only updates tasks.

## Evidence and Superseded Checkpoint

Spec cc13283 / compiler design220a3f56 adopted an overly restrictive fixed-type
criterion; independent review inspected six spec and three design diffs but
missed its conflict with the documented eager/lazy unwrapOr API. The probe in
meta/evidence/existing-feature-conformance/source-owner-facts/
overload-admission-stopped.json shows old23f7 accepting an empty application
and strict WIP508b rejecting it at std/Lang.pw:88. That review does not establish
completion for the structural contract above. The task remains reopened; the
former fixed-only plan and API-rename recommendation are superseded.

Reference for the finite occurs-check mechanism:
[Rust InferCtxt documentation](https://doc.rust-lang.org/stable/nightly-rustc/rustc_trait_selection/infer/struct.InferCtxt.html).
This supports the mechanism, not adoption of Rust's overload/language rules.

## Revised Documentation Outcome

Resolved at spec5bd65a5 and the accompanying three-chapter compiler design
update. The six spec chapters now permit bounded per-position structural
distinction, explicitly share receiver binders and separate method-owned ones,
retain default/origin/capability boundaries, and preserve Optional.unwrapOr's
public eager/lazy overloads. Unknown projections, occurs checks, nominal
recursion and analysis limits have explicit contracts.

Independent overload_rule_semantics_review and overload_rule_architecture_review
both accepted the actual six-spec/three-design diff. This time both checked the
real standard Optional API and related Result/collection/format surfaces;
the semantic review also checked nominal recursion against the occurs argument.
The architectural review's nonblocking generic-shape wording was replaced with
binder-domain wording. No blocking omission remained. Targeted stale-contract
search and diff whitespace checks passed. This is documentation acceptance,
not success of the strict WIP or completion of met-g53w/phase three.
