---
id: met-4dxy
status: in_progress
deps: [met-oxch]
links: []
created: 2026-11-27T15:58:48Z
type: task
priority: 1
assignee: Koji Murata
parent: met-o5z0
tags: [frontend, generics, diagnostics, verification]
---
# Build the common inherited associated-member query

Contract: spec08 inherited associated-member uniqueness and docs/design/types-and-evidence.md#associated-member-selection. Read parent met-o5z0 before work. No new source semantics or main/seed/carrier promotion. Preserve candidate identity separately from conformance evidence paths. TDD and independent final review are required; parent certification remains separate.

Own the canonical semantic query over explicit receiver/member/complete root instances and admitted source scope/selected view/equality context. Reuse declaration/lexical headers and explicit substitution services; do not infer missing ancestry from an unready header or use ambient cur as a substitute for the query environment. Return Missing/Unique/Ambiguous with actual declaring instance/member and compact inheritance/substitution derivation. Malformed/foreign/unready inputs and bounded-analysis limits remain distinct from Missing. Preserve all conformance-path obligations independently of name-candidate deduplication.

Connect the coherent Raw compatibility validation surface or native service consumer so this is an exercised service, not unused scaffolding. Keep Raw non-Source. The normal Source adapters/publication are still unfinished in the next child; do not certify language acceptance from this query unit.

Cover direct and inherited members, multiple roots, parent parameter substitution and changed arity, exact same-instance diamond deduplication, different declarations/instances including equal output types, same-spelled binders/module owners, bounded recursion and incomplete input. Use existing Raw/admission controls for actual RED, not missing-new-API setup failure. New result-shape checks can be GREEN as the API is introduced. Confirm one decision owner and no repeated traversal at the consuming Raw boundary. Avoid eagerly enumerating all inheritance paths or scanning/rebuilding the complete compiler catalogue per query.



## Query shape before implementation

Use explicit subject/member/site, search roots:Array[TraitBound], and a
separate equationContext:Array[TraitBound], not an ambient cursor or external
Source permission. The receiver/selected view is explicit in the query terms. Declaration/header readers and explicit traitConstraintInShape
substitution provide parent bounds. Source/view/equality context is represented by the query receiver, selected roots
and available equations; do not add equation premises to the search roots or
pass an unused source object.

Retain a compact graph of bound nodes and declared supertrait edges, with root
references and candidate references to actual declaring nodes/member declarations.
Deduplicate candidate identity separately from graph bound/equation contexts;
keep incoming edges, rather than enumerating every diamond path or discarding
alternative conformance derivations. Bound normalizations use exact binder and
semantic type identity. Unknown/malformed storage or unfinished headers are
errors, never an empty namespace. Reuse the existing128 inherited-instance limit
as Limit, not Source or a claim of infinite recursion.

The initial native compatibility RED is associated-member-query-raw-red-v1:
valid graph declarations load successfully, direct Root succeeds, but Diamond's
inherited Output is rejected by the current public type: helper. This is a real
Raw namespace defect, not a missing-new-API setup failure. Rich outcome/graph
assertions follow once the new service exists. Source publication remains B.

API pre-review required the explicit equationContext separation. For
Child[A]:Parent[A]+Parent[I64], the independent premise T:P[Item=I64] makes
T#Child[T#P.Item].Output unique. Roots alone cannot represent that equality;
adding P to roots would incorrectly widen a qualified lookup (especially when
P also declares Output). Add native controls with/without that premise and
with an unrelated Output in the equation-only scope. Preserve conflict/limit
handling rather than guessing equality or silently treating an unavailable
operand as no edge. availableTraitBoundShape alone is not a readiness proof;
check supertraitOperandAvailable and actual reached storage before expansion.
Canonical input preconditions remain explicit: this is not a complete validator
for every arbitrary corrupted Comp/arena, whose separate owner is met-wuzv.
