---
id: met-o5z0
status: in_progress
deps: [met-ldvd, met-oxch, met-4dxy, met-wxn1, met-2yhf]
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

## Bounded implementation units

A. Common associated-member query. Introduce one missing/unique/ambiguous semantic
result over explicit receiver/member/complete-root instances and the admitted
equality context. Follow declaration/header supertrait edges with simultaneous
substitution, retain actual declaring instance and derivation, deduplicate exact
member/instance candidates, and keep bounded-analysis/malformed/unready answers
separate from Missing. Use existing Raw admission/native cases for meaningful
RED and test new result fields as the service is introduced. This unit certifies
the service, not source publication or product completion.

B. Source publication through final consumption. Connect legacy TypeAst and
SyntaxType short/explicit adapters and lexical inherited names to A. Remove
traitOwnerHasAssocId prefilters that discard a Child root before traversal and
competing chooseShortProjectionSource/lowerLexicalAssociatedType selection.
Use declaration/lexical headers without interpreting unfinished graph data as
absence; preserve ProjectionBoundState readiness and original scope. Publish the
actual declaring instance, root selector, edge derivation and recipe provenance;
handle changed parent arity and derived argument recipes. Require the authored
Child view's proof independently: normalization to Parent must not accept a call
with only T:Parent. AuthoredTypes admission and Mono Resolve consume the retained
selection; assocBindingFor/associatedOutputTermInProof may read the selected
witness output, but must not become fresh member-name/source resolution.
Guarantees include actual generic instantiation and final AOT/ORC behavior, not
just a saved field or invariant checker.

C. Owned refusal/result lifetime and final finite certification. Consume A/B's
same Missing/Ambiguous outcome in SourceTypeUseAdmission/ProjectionMembers rather
than the old declaration-local Boolean. Retain occurrence/root/frontier/query
identity once, preserve the real authored location and Raw compatibility type:/
ref: views, and carry failure through SourceFacts, owned/eager/session/cache/
drain/terminal consumers. Preserve downstream missing-conformance/binding
producers separately. Verify foreign/forged/moved/failed-builder/malformed/limit
boundaries, lazy body timing, successful controls and no failed success cache.
Parent met-o5z0 then reconciles all guarantees, normal regressions, gen, current
performance and independent review without claiming com-yeua/stage3/main green.

A precedes B; B precedes C. All three block this parent. Initial implementation
map: Lower/Decl chooseShortProjectionSource and unique*Source; Lower/
ProjectionBounds cachedValue/cachedSyntaxProjectionSource early membership
filters; Lower/Types lowerLexicalAssociatedType plus both lowering adapters;
Lower/TypeRecipes inherited/view argument recipes; Check/AuthoredTypes saved
view/projection evidence; Mono/Resolve exact selected associated output; and
ProjectionMembers/SourceTypeUseAdmission/SourceFacts failure consumers. The
query's returned actual owner must not erase the authored Child's view obligation.

## Adopted units and review

- query: [met-4dxy](met-4dxy.md)
- publication: [met-wxn1](met-wxn1.md)
- failure: [met-2yhf](met-2yhf.md)

Neutral split review found no mandatory correction: A->B->C covers the adopted
contract without narrowing it. B is the largest unit but intentionally closes
producer through final consumption; a further split must preserve that owner
guarantee. The query input explicitly includes admitted source scope and selected
view/equality context. Existing assocBindingFor is a current proof reacquisition
site to audit, not a completion exception.
