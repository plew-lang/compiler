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


