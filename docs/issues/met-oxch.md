---
id: met-oxch
status: closed
deps: []
links: []
created: 2026-11-27T13:54:21Z
type: task
priority: 1
assignee: Koji Murata
parent: met-o5z0
tags: [spec, design, generics]
---
# Specify associated projection through an inheriting trait

## Adopted contract and scope

The user adopted one uniqueness rule for T.Item and T#Child[Args].Item, with
only the search roots differing. Inherited members are eligible; identical
associated declarations in the same complete declaring instance deduplicate,
while distinct declarations or instances remain ambiguous even for equal output
types. Missing members reject. View/conformance admission remains separate.

This task publishes the language rule in spec08 and the shared selection and
retained-result contract in types-and-evidence/name-lookup. It verifies their
consistency and links through independent review. Product implementation and
executed RED/GREEN scenarios belong to parent met-o5z0 and are not completed by
this document change.

## Required document checks

- T.Output, T#Child.Output and T#Parent.Output agree for a unique inherited member.
- Different same-name members remain ambiguous; selected parent roots disambiguate.
- Parent arguments are substituted; distinct complete instances do not merge.
- A diamond reaching the same candidate does not duplicate it; conformance-path
  validity/uniqueness remains independently required.
- One resolver owns the decision, source publication retains it, and downstream
  consumers do not repeat name lookup or replace the selected origin.

Rationale: the explicit trait chooses the search roots, rather than introducing
an extra direct-declaration-only rule. The same uniqueness mechanism serves both
spellings. Implementation gaps remain at met-o5z0, not in the normative text.

## Completion

Resolved as a documentation task. Spec revision 7c8e321c091f7070070447350888cd2c778bb00e publishes
the adopted rule; design types-and-evidence Associated-Member Selection owns
the common query/result/retained-consumer contract, and name-lookup links to it.
Independent neutral review derived requirements before inspecting edits and found
no required correction or remaining source decision. It checked full instance
arguments, inherited redeclaration prohibition, view admission and the separation
of candidate deduplication from conformance-path ambiguity. Cross-repository
diff checks and changed local heading/link targets pass.

Implementation and executed acceptance coverage remain met-o5z0 obligations.
No product correctness, performance, whole-green or stage3 completion is claimed.
