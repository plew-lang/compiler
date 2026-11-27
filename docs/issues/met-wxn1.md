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
chooseShortProjectionSource and independent inherited-lexical selection decisions.
A directly declared lexical associated binder is a declaration reference, not an
inherited query; retain that distinction through admission. Preserve original
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

## Short-selection checkpoint

Both Syntax and Value short projection adapters now pass one prepared common
query result explicitly into occurrence capture. Search roots and equation-only
context are separate. A contributing representation root retains the original
source argument recipes without changing the declaring-member decision or
removing other roots/edges. Capture checks session, scope, site and receiver;
normalization may justify a receiver distinct from a root's authored subject.
The old short source chooser and unused spelling-based subject prefilters are
removed. Lexical selection remains a separate migration obligation: its declaring
term representation must not be confused with the short adapter's root recipe.

The native short profile covers inherited/combined roots, recursive unrelated
bounds, equal-output ambiguity, wrong receivers, unavailable-header Limit,
receiver equations, separate real source occurrences and the legacy Value AST.
The site-guard-removal mutation fails the crossing assertion; this is mutation
evidence, not a historical RED. Final results and exact input hashes are linked
from the meta projection-members evidence index. These internal gates do not
prove fresh AOT/ORC execution or performance.

## Lexical migration boundary

Independent source/design review confirms that lexical lowering must return the
term and its prepared query together. Keep an explicit representation kind:
short source recipes describe the contributing root; lexical recipes describe
the declaring candidate while preserving the original Child/Self roots and
arguments separately. Capture validates this mapping instead of inferring it
from a coincidentally equal term. Missing may continue lexical name lookup;
Ambiguous, unavailable preparation and Limit must propagate.

The migration includes direct TypeAst/SyntaxType annotations, nested projection
receiver recipes and construction heads. Expr.Make currently retains argument
occurrences but only a U64 for its head. Move source construction heads to an
explicit term/provenance result and retain that occurrence through body admission
and factory rewrite. Synthetic Optional/Result wrapper creation is nominal
construction, not ambient lexical lookup. A factory rewrite with an existing
writtenTerm transfers its saved provenance; an unfinished-declaration fallback
must not silently start another lexical selection. These are existing
source-to-final-consumer obligations, not a new language feature or a reason to
close the task after fixing annotation callers alone.

Lexical unavailable-header RED is confirmed: compile/runtime/link succeed,
native aborts because missing preparation becomes successful absence. A direct
unconditional common-query trial fixes that case but rejects the existing
parameterized source profile with Limit. Header preparation enters Child lexical
scope, lowers Parent[I64], then publishes Child's header; the I64 nominal name
must not become a demand for an unfinished inherited namespace. The trial is not
adopted. Resolve that producer dependency explicitly before the handoff migration;
do not restore silent missing-header behavior or add a per-name exception.
Meta lexical-checkpoint.json retains frozen input hashes and exact outcomes.

Namespace-only preparation is now implemented for Syntax and Value producers,
including per-entry setup and a parent-count/owner consistency check at completed
header registration. Lexical lookup uses namespace filtering then the common
instance query; its old BFS/comparison helpers are removed. The original eighteen
native profiles pass in lexical-namespace-green-v3, including an added Value AST
Parent[I64] case. The unavailable-namespace internal control now removes both
namespace and header information; a valid namespace snapshot is not missing data.

Local lexical declaration binders now have an explicit Declaration variant,
separate from Query. Exact owner/member declaration offset, Self and lexical
arguments pass through direct/nested recipes into occurrence binding. Admission
requires independently justified complete-instance evidence, matching lexical
Self scope and authorized normalization/proof dependencies. The admitted reader
rejects missing binder admission and uses the saved identity/proof. Generic
heritage checking now receives its exact lexical argument environment.

The formerly failing LexicalHeaderSelectionMain succeeds for own-member heritage
references, including generic traits. Source and Value AST controls retain the
Declaration variant rather than fabricating Unique graphs. Negative controls
cover wrong declaration identity, Self, argument arity, same-arity foreign
arguments and foreign Self admission scope. Requirement reading preserves the
admitted symbolic owner/arguments. An independently observed missing final
redeclaration check is repaired at completed Source trait validation, after
cycle checks and before nominal admission. Its accepted-input RED is retained.
Meta declaration-binding-checkpoint.json owns the final results and review.

The inherited lexical annotation and nested-receiver handoff now carries the
prepared result and original Root argument recipes explicitly. Capture rejects
missing preparation instead of querying again. Root/Declaring representation is
retained and checked during capture and retrieval; the redundant authoredRoot
API argument is removed. Root recipes are checked by arity and exact term,
including Root arguments1 versus declaring arguments0. The missing-handoff RED,
wrong-representation refusal and nineteen-profile result are retained in meta
lexical-handoff-checkpoint.json. This completes these finite annotation/receiver
slices, not this task. Construction head formation and body proof replay are now under validation
below; their terminal gates remain required. No all-mode or performance
completion follows from native tests.

## Construction head checkpoint

Value/Syntax Make heads now produce a whole-head PType/occurrence with original
argument recipes and retained lexical declaration/query data. The head is kept
on AuthoredConstruction and transferred by authorized rewrite; Make's separate
typearg-slot admission is removed. Synthetic nominal wrappers no longer perform
lexical lookup. Projection/view heads are admitted once into owner-local body
facts, and generated factory type receivers consume that admitted term rather
than resolving the head spelling as a value. Missing written heads and unrelated
receiver proofs reject. Source frontiers track only valid head/snapshot identity
across Make/Method, retain current child-edge checks, and collect rewritten Method
heads. Mono replays saved proof with an explicit body environment and checks its
receiver/aggregate instance; missing executable head/proof is an internal failure.

Native coverage includes the original missing-occurrence RED and the discovered
factory-type-receiver-as-value failure, ordinary and named factory body admission,
direct generic and inherited heads, context-only and partial nominal heads,
head arguments containing projections, concrete Wrap[I64] recipe interpretation,
Raw replacement, wrong receiver, missing written/executable heads and rewrite
frontier/child-path controls. The meta construction-head checkpoint records exact
results. Fresh CLI execution, AOT/ORC, full producer audit and performance are
still required; this is not final construction/task certification.

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
