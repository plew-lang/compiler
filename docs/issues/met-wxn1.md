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

## Saved implementation and evidence

Meta evidence: rejection-domains/diagnostic-domain-implementation/projection-members/.
The fixed149aac language matrix is39 cases/27 target mismatches; preserve it for
final AOT/check/ORC comparison. Early direct-refusal successes are not B closure.

Current append-only query draft is explicitly passed by PType token to a
write-once occurrence/recipe binding. It retains session/site/scope/term identity,
authoredSource only for explicit #, authored and term argument recipes, graph
outcome and exact equationClauses parallel to context after the root prefix.
Clause IDs identify preparation sources, never Source proof. Consumer admission
must validate their session/scope/Ready bound and match actual scoped assumptions.
Never recover a source premise by equal canonical terms or an ambient cursor.

PreparedProjectionSubject caches only term/recipe before the RHS, with its own
Unlowered/Lowering/Ready/Failed state and original frame/binder/role checks.
Receiver-qualified dependency discovery uses explicit edge substitution and
known equations. Unknown-result normalization memo is reset when context grows.
Head identity lookup does not consume Failed before dependency filtering.

Native selection-native-suite.json is the finite current suite (ten profiles):
Raw graph; exact retention/write-once/foreign term/session; bare/nested Child/Self
roots; prerequisite states and unrelated-owner noninterference; real Unlowered
preparation; T/U noninterference; receiver equality and distinct V countercase;
value-AST fresh binders/frame; alias Chosen location and missing Child proof.
Source-equation records additionally check exact source-clause mapping. Source
re-reviews found no remaining defect in those slices; these are not final B gates.
The distinct-receiver control checks its semantic query, not C's unfinished text.

## Next implementation sequence

1. Preserve normalization context in conformance-path comparison:
   queryTraitPatternProof -> collectTraitProof -> sameSourceProofPath and equation
   agreement. Replay saved equations; propagate replay failure distinctly from
   false/ambiguous. Preserve authored root/trait-subject branch identity even if
   endpoints become equal. No name or conformance reselection in the comparator.
2. Build the occurrence-owned admission receipt. Bind saved equation context to
   actual source assumptions by exact clause IDs. Retain original root proof and
   declaring proof separately. Replay the saved compact graph per node/incoming
   edge with readSignatureSupertraitWitness/checkRetainedWitnessClause; merge
   with context-aware path equivalence, not by enumerating every full path or
   by name-candidate identity alone.
3. Connect abstract and concrete admitted readers (AuthoredTypes, source/body
   facts, call/generic instantiation, Mono/Resolve and witness output access).
   Read saved identity/arguments/derivation under explicit environments. Concrete
   witness output access is legitimate; fresh member-name/source selection is not.
4. Move remaining short/lexical adapters to the same query, remove replaced
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
