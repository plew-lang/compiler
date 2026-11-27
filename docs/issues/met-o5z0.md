---
id: met-o5z0
status: in_progress
deps: [met-ldvd, met-oxch]
links: []
created: 2026-11-27T13:29:11Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-yeua
tags: [frontend, diagnostics, verification]
---
# Carry resolved associated-member outcomes through type-use admission

## Contract and scope

Implement the adopted associated-member selection contract in spec08 and
[types and evidence](../design/types-and-evidence.md#associated-member-selection).
T.Item searches available constraints; T#Child[Args].Item searches that selected
instance and its inherited instances. Both use the same missing/unique/ambiguous
judgment, substituted declaring-instance/member identity and candidate deduplication.
A child need not directly declare the member. View/conformance evidence remains
required independently; matching concrete output types do not merge candidates.

Retain the actual declaring instance and inheritance/substitution derivation
through source publication and final consumers. Namespace selection is not a
membership test against only the child's declaration-local assocTypes range.
TraitDef.assocTypes is declaration-local, not a flattened inherited namespace.
Remove competing short/explicit projection decisions and late name reselection.

The existing WIP transports a missing direct-member refusal using common
SourceTypeUseFailureEvidence. Reuse that occurrence/root/frontier/path ownership
and original positions, but consume the complete resolver outcome before
publishing or classifying a refusal. Raw compatibility stays non-Source. Do not
replay resolution to classify; do not infer authority from text, IDs or a cursor.

## Covered scenarios and completion

TDD covers unqualified/qualified/direct/inherited roots, local/imported same-name
traits, generic parent substitutions, identical diamonds, distinct declaring
members/instances (including equal concrete outputs), missing and ambiguous
members, and the selected parent form that disambiguates. Follow successful
identity and justified evidence through instantiation and final execution.

Preserve declaration checks versus demanded/unrequested body timing, actual
occurrence positions, public Raw type: and ref: entry points, malformed/unresolved
Raw input handling, forged/foreign/query-changed refusals, failure retry/cache/
drain, owned eager/whole/session consumers and no success-cache insertion on failure.
Do not merge independent conformance evidence paths while deduplicating names.

Downstream missing conformance/binding refusals in Codegen/Mono/Resolve
(extern_signature_unrelated_conformance and extern_signature_wrong_trait_instance)
are distinct producers despite matching text; preserve their current domain.
No blanket Raw Comp validation, main/seed/bin promotion or all associated-type
failure migration is included.

Independent plan/final review and focused fresh/regression/gen gates are required.
Parent com-yeua owns aggregate formal/whole comparison at its bounded integration
gate. Baseline149aacd25456 is3314/248fail, not green. Split further implementation
units before coding if the common resolver/retained-consumer scope needs them.

## Evidence and current implementation gap

Meta evidence/rejection-domains/diagnostic-domain-implementation/projection-members/
retains fixed149aac RED48 (14legal/deferred,34Unclassified target refusals),
WIP dc6c0974 fresh48/48, existing controls15/15, gen, native/session boundaries,
and original alias-location RED/GREEN. These certify only the prior finite WIP;
they do not prove the newly adopted inherited-resolution contract.

The Child spelling in Inherited.pw is now a required legal control, not a correct
rejection oracle. InheritedParent.pw is its already-working declaring-parent
counterpart. The saved149aac carrier and248fail whole baseline remain adopted.
No completion or WIP carrier promotion is claimed.
