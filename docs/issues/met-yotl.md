---
id: met-yotl
status: closed
deps: []
links: []
created: 2026-10-21T11:49:40Z
type: task
priority: 1
assignee: Koji Murata
tags: [design, generics]
---
# Specify recursive capability summaries and bounded discharge

## Adopted Contracts and Scope

[Structural capability summaries](../design/types-and-evidence.md#structural-recursion-and-shared-capability-decisions)
own nominal ownership equations, their finite-component solution and publication.
[Bounded capability reasoning](../design/types-and-evidence.md#bounded-capability-reasoning-and-analysis-limit)
owns the minimum predicate/equality fragment, common proof requests and one fixed
semantic expansion-depth limit. [Spec06](../../../spec/spec/02-type-system/06-generics.md#能力条件付き候補と重複判定)
permits an explicit analysis-limit rejection even when a request might eventually
terminate. No proof or detector of infinity is required.

The user approved simple fixed limits after reviewing concrete examples and
Rust/Swift's treatment of finite expensive work. This does not add a public
limit-override API or a language-level numeric constant. L is selected as an
implementation constant with capability implementation controls; no particular
value or measured performance is claimed by this design task.

## Original Review Gap

Design-only review [met-ukm5](met-ukm5.md), R1/R2, compared design `1d83231e`
with spec `16f2f139`. Nominal summaries and conditional proofs had owners, but
recursive solution/publication, the shared minimum proof fragment and stopping
behavior were not concrete enough to prevent competing local implementations.
For List, `Copy(List[T]) = Copy(T) AND Copy(List[T])` did not alone choose a
solution. Changing associated subjects raised a separate expansion question.
No implementation crash, source reproduction or performance regression was
established by that review.

## Resolution and Rationale

- Closed finite ownership components use least-fixed-point may-be-unique,
  equivalently greatest-fixed-point copyability. Provisional component state is
  private; a completed symbolic summary is not unfinished proof success.
- Shared handles stop referent copy-prohibition propagation under their ownership
  contract, without stopping sendability/destruction analysis. All variants,
  private owned fields and declared parameter ranges remain relevant.
- Canonical capability atoms, constants, finite Boolean combinations and retained
  identity/associated-binding equations feed one relation for call/via/deinit
  disjointness and coverage. Saved derivations go to final consumers; source names
  are not searched again. Proof of Boolean coverage does not replace the remaining
  call contract or manufacture deinit presence.
- One fixed expansion-depth L stops growing required proof chains, including finite
  deep requests. No infinity proof, separate rule-count/size/time budgets, guessed
  capability or overflow-as-false result is introduced. Finite SCC solving remains
  distinct from repeatedly descending through a self edge. This simple depth
  limit does not promise a bound on all branching work.
- Limit diagnostics retain the request/source and distinguish exhausted analysis,
  unsupported/unproved relations and actual contradiction/overlap. Caches and
  wrappers preserve depth assumptions rather than resetting or erasing them.

The finite internal solution and shared authority were independently reviewed
before the cutoff policy was adopted. Final policy-diff review is recorded below.
The two temporary comparisons are incorporated into the owning chapter; their
full examples and research remain recoverable in Git instead of competing with
that adopted contract.

## Reference-Language Evidence

Research on 2026-10-21 confirmed both languages use cutoffs without first proving
nontermination, and finite work can exceed them. [Rust limits](https://doc.rust-lang.org/reference/attributes/limits.html)
provide the practical depth precedent; [new-solver caching](https://rustc-dev-guide.rust-lang.org/solve/caching.html)
shows why available-depth assumptions matter. [Swift's designer account](https://forums.swift.org/t/the-requirement-machine-a-new-generics-implementation-based-on-term-rewriting/55601)
explains bounded completion; its [current limit fields](https://github.com/swiftlang/swift/blob/main/include/swift/Basic/LangOptions.h)
and [completion checks](https://github.com/swiftlang/swift/blob/main/lib/AST/RequirementMachine/KnuthBendix.cpp)
show several implementation budgets. Plew initially chooses the simpler single
limit rather than copying all those controls or either general trait solver.
Upstream settings are not Plew defaults or source guarantees.

## Completion Boundary and Remaining Implementation

The owning contracts specify the recursive solution, proof fragment, shared
inputs/outcomes, substitution/publication, cutoff, failure, rationale and controls.
Design verification includes complementary families; Pair/List and mutual
recursion; phantom/shared-handle behavior; associated-binding equality; actual
missing coverage/overlap; a changing projection chain; and cold/warm proof reuse.
No compiler execution, general termination proof, sanitizer or timing result is
claimed. The numeric constant, physical condition representation and tests belong
to [met-b2la](met-b2la.md), which must close source-to-copy/drop implementation.
This design task does not complete [met-si6j](met-si6j.md) or enlarge its scope.

## Final Policy Review

The semantics reviewer found no blocking issue in the final contract: one L,
finite requests stopping at its limit, no infinity detector or extra budgets,
ordinary SCC handling kept separate, no cache/wrapper reset escape, and no new
source predicate syntax or general trait negation. Spec wording was narrowed to
normalization needed for capability analysis, avoiding an unrelated all-type-work
limit. This closes R1/R2 at the design scope after the user's cutoff decision,
not the numeric implementation or language-feature implementation.
