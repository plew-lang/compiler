---
id: met-wxn1
status: in_progress
deps: [met-4dxy]
links: []
created: 2026-11-27T15:58:48Z
type: task
priority: 1
assignee: Koji Murata
parent: met-o5z0
tags: [frontend, generics, diagnostics, verification]
---
# Retain inherited associated selections through source and instantiation

## Contract and scope

Implement spec08 and [associated-member selection](../design/types-and-evidence.md#associated-member-selection).
Parent met-o5z0 retains the whole producer-to-final-consumer guarantee. Query
unit met-4dxy is closed. This task is not complete from fields or native service
success alone. No main/seed/carrier promotion or new source semantics.

Use the common query for TypeAst/SyntaxType short/explicit projections and lexical
associated names. Remove traitOwnerHasAssocId prefilters and competing
chooseShortProjectionSource/lowerLexicalAssociatedType decisions. Preserve original
declaration scope, ProjectionBoundState readiness and demand timing; do not
prepare unrelated clauses or reinterpret missing headers as empty namespaces.

Keep the authored selector, exact occurrence/argument recipes and original Child
view proof separate from the actual declaring Parent instance/member/derivation.
T:Parent never justifies T#Child.Output. Changed parent arity, same-name modules,
alias visibility and original use positions must survive. Equal output types do
not merge different declaring instances. Candidate dedup does not prove path
uniqueness or discharge incoming conformance obligations.

## Publication boundary

The immutable authored annotation/recipe can retain Child before admission.
Admission owns a receipt combining the retained selection, its source premises,
original view proof and declaring-instance evidence. All published declaration,
abstract-body, call and concrete-instantiation types use the saved declaring
Parent projection, even while symbolic. Build new semantic terms at this reader;
do not mutate an interned authored term or reselect names downstream.

This follows the existing distinction between authored signatures/recipes and
admitted type readers. Rewriting lowering's term to Parent would unnecessarily
move Child source children into a foreign structural graph. The former new test
that inspected raw Param.ty was never a required contract: InheritedSelectionMain
now checks lexicalBodyParameterType, retaining Child as the source annotation.
Its admitted-publication RED is authoritative; no output requirement is removed.

## Implementation and evidence checkpoint

Meta evidence: rejection-domains/diagnostic-domain-implementation/projection-members/.
The original fixed149aac language matrix is39 cases/27 target mismatches;
preserve it for final fresh AOT/check/ORC comparison. Native internal-reader
success is not that final comparison and does not close this task.

The query draft passes by PType token to a write-once exact occurrence/recipe
binding, retaining session/site/scope/term identity, explicit authored selector,
argument recipes and exact equation source-clause IDs. Source prerequisites
prepare subject/recipe once before RHS, respect original frame/binder and
readiness, and qualify dependencies by receiver plus known equations. Irrelevant
Failed/Lowering clauses do not poison an unrelated query.

Proof comparison preserves normalization context and source roots/trait-subject
branches. Root-local folding composes with saved equations under a finite bound.
Equivalent root premises contribute only compatible outputs; different owners
and complete instances do not merge. Saved graph edges use source owner plus
declaration ordinal. Compact replay checks every incoming clause, retaining
separate original root and declaring proof authority rather than enumerating
all root-to-leaf paths. Exact source-clause mapping includes Function,
RawRequirement, Implementation and conformance source/declaration range ownership.

Source signature admission verifies equation authority, root and derived proof
scope support before writing AdmittedAssociatedSelection. It keeps root proofs,
declaring identity/proof, exact scoped premise refs and normalization context.
Guarded retrieval checks the original binding/session/identity; duplicate writes,
foreign sessions, absent scoped premises and unrelated scope reject. Source
re-review identified and verified the root scope-support gate. The gate-removal
mutation fails its assertion; it is not historical RED. [Admission evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/projection-members/admission-checkpoint.json) retains those exact results.

Abstract parameter slots now use the same constructor recipe reader as concrete
slots. The reader verifies the authored Child view, then consumes the saved
Parent instance/arguments/proof without name selection. Concrete and
AssociatedBinding contexts replay saved equations and proofs together through
the existing service; declaration reads allow symbolic results. Original source
annotations remain unchanged. Direct members reuse already-read identical proof
when owner and interpreted arguments also match; inherited proofs remain distinct.
A saved Unique without its admission receipt cannot silently take the old path.

[Reader evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/projection-members/reader-checkpoint.json) retains abstract-publication and concrete
normalization RED/GREEN evidence. Final native-v16 passes sixteen profiles with
input invariance and zero compile/runtime/link/native status. It includes changed
parent arity, nested equation substitution, concrete conformance binding output,
nested Array construction, alias without direct Parent import, weak/strong
premise orders and missing-receipt refusal. Independent source/design re-review
found no required defect in these slices. Broader trait-provided body contexts, closure/synthetic
producer environments and final consumers still require the checks below.
No formal performance, whole-green, carrier promotion or B closure is claimed.

## Source-selection clause identity checkpoint

SourceSelection reads ordinary callable signatures as well as trait-provided
bodies. Clause identity storage is therefore common to all registered authored
function signatures, with parent=0 an empty range. AuthoredSignatureClause
retains own/inherited order and exact scope/row/clause checks. Extern signature
registration receives its original authored scope and records exact source IDs;
Raw scope=0 retains no invented identity. Value/Syntax extern producers bind the
scope once at registration. Range metadata is obtained once, not per bound.

The ordinary generic SourceSelection RED (foreign where premise) now succeeds.
Finite mode tests cover symbolic Parent with changed arity, Requirement reads
using a validated concrete Child witness and actual U32 output, own+parent method
conditions, empty where, and both extern producers. SourceSelection/projection
reader API names express their common role instead of suggesting provided-only
ownership. Independent implementation and naming/design re-review found no
required correction in these slices. Final native-v18 passes seventeen profiles
with unchanged inputs and zero setup/native statuses. Meta
source-clause-checkpoint.json owns exact results and exclusions. This does not
certify closure/synthetic producers or final execution/performance gates.

## Next implementation sequence

1. Audit remaining producer/receiver environments against the receipt checkpoint;
   retain source scope and exact roots/equations across nested/provided/associated
   binding uses. Do not infer all-mode closure from the finite native profiles.
2. Connect abstract and concrete admitted readers (AuthoredTypes, source/body
   facts, call/generic instantiation, Mono/Resolve and witness output access).
   Read saved identity/arguments/derivation under explicit environments. Concrete
   witness output access is legitimate; fresh member-name/source selection is not.
3. Move remaining short/lexical adapters to the same query, remove replaced
   paths, and close all source-to-final-consumer scenarios below. Keep original
   recipes/proofs distinct from generated Parent semantic children.

## Completion and limits

Run qualified/short/lexical, parent substitution and changed arity, diamond
incoming obligations, ambiguous/equal-output cases, local/imported same-name
traits, aliases without direct Parent import, missing Child view proof, unused
body timing and legacy adapter controls. Verify admitted symbolic Parent and
actual generic AOT/ORC output use the same saved selection. Audit direct Param.ty
and assocBindingFor readers for late selection. Do not stop at invariants.

Independent final review, focused fresh/regression/gen gates and same-source
cost assessment are required. Parent met-o5z0 reconciles children; com-yeua owns
aggregate formal/whole comparison. The adopted149aac baseline remains7.380636s
and3314/248fail, not green. Missing/Ambiguous owned refusal/cache/lifetime is
met-2yhf, not silently implemented or certified here. No all-source/global or
stage3 completion is implied by the finite native suite.
