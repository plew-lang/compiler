---
id: met-wxn1
status: in_progress
deps: [met-4dxy, met-y2ec, met-k93s]
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

## Body result handoff checkpoint

Fresh f9aba36f CLI matrix passed12/39 with immutable inputs. Child's identity
return rejected in generic checking; Parent passed check but failed Mid
preparation. They are distinct unclosed consumers, not evidence of completion.
A native regression proved semanticBodyReturnContext retained Child while its
parameter reader published Parent. lexicalBodySignatureType now shares the
exact admitted slot reader for parameters and results. Body recording, generic
checking and verification propagate reader failure and use its logical result;
async explicit Promise unwrap occurs once there and forwarding remains wrapped.
Record reuses one result read for its origin and published body signature.

Meta body-result-checkpoint.json retains target RED, GREEN and20-profile GREEN
with input hashes. Independent finite review found no required correction in
this slice. It did not certify CLI/AOT/ORC, performance or task completion.
Raw/closure/forwarding were source-inspected, not newly executed.
The try consumer is covered by the checkpoint below.

## Free callable signature checkpoint

The fresh result-handoff candidate removed Child's generic return mismatch but
still passed12/39: free call selection and argument contexts grounded raw Child
parameter slots before the result handoff. A frozen diagnostic snapshot proved
the failure preceded context/result entry. Source call selection now receives
its explicit callable ID and reads admitted lexical parameter patterns through
the common matcher. Inference receives these patterns explicitly; diagnostic
origin is not semantic authority. Completed argument contexts read
SourceParameters and results read SourceResult, grounding the saved declaring
terms under the same map. Provided calls retain the strict existing proof and
missing-signature gate; unregistered Raw declarations retain their adapter.

Meta free-call-signature-checkpoint.json retains target RED and final native-v8
20-profile GREEN, including actual caller recording/Source obligations and Bool
argument rejection by spec12 rather than projection lookup failure. Independent
finite source review checked explicit-ID ownership, partial inference, provided
gates and DiagnosticCandidate fallback. No new member/name selection is added.
Method Raw adapters and pre-admission ranking remain unaudited. Final fresh
CLI/AOT/ORC, performance and all task gates are still required.

## Try logical-result checkpoint

recordTryExpression now reads semanticBodyReturnContext rather than the raw
declared result. A Result[I64,T#Child.Output] operand and identical function
result previously fabricated a spec13 From-conversion failure. The regression
now records one try fact with equal source/target errors and passes Source typing
obligations. Meta try-result-checkpoint.json retains RED and final native-v2
20-profile GREEN with input invariance. Independent finite review found no
required correction: Result detection, error extraction and From selection are
unchanged, and ordinary logical-result handling is shared rather than duplicated.
This does not certify remaining method/closure producers or fresh AOT/ORC.

## Method signature checkpoint

A corresponding registered generic method reproduced the same missing-binding
failure. Method ranking's six consumers now pass their exact callable ID and
use admitted lexical patterns; the obsolete f-only rank adapter is removed.
Source method inference receives an explicit parameter vector (shape-checked),
without deriving authority from diagnostic origin. Both ordinary and provided
selected calls publish AdmittedParameters; provided proof/missing-signature
gates and unregistered Direct fallback remain. Method operand contexts compute
one complete environment outside the loop rather than rebuilding it per operand.

Meta method-signature-checkpoint.json records target RED and final native-v3
20-profile GREEN: method Source recording/obligations, wrong Bool argument
spec12 rejection, and an initially untyped closure argument whose expected type
comes from a later typed operand. Independent finite source review found no
required correction. The old e001910a fresh candidate (free-call slice only)
still passed12/39; latest all-mode results and performance remain outstanding.
Raw helper/early-admission auditing is not complete.

## Checked body-slot publication checkpoint

The real CheckedProgram.check→prepareCheckedProgram bridge exposed Parent's Mid
MissingTypeResolution: publication only rebased provided/dependent receiver
parameter slots, not every checked body's semantic slots or logical result.
scanFinalBodyInstance now publishes the selected signature for every ordinary
body (excluding bodyless declarations and explicit ABI adapters), against the
prepared source receiver/parameters/result. Owner and slot-count checks remain;
Mid still only substitutes and consumes published facts, never chooses evidence.
The common contract is explicit in frontend-handoffs section9.

Meta body-slot-publication-checkpoint.json retains target RED, three-case full
preparation GREEN and the collected16-case gate. All11 positive whole-check and
executable preparations pass, including changed arity/arguments, closure,
provided method and unused parameter. Three negative controls reject correctly;
AmbiguousChild and EqualOutputs still fail the required diagnostic assertion
(Missing instead of Ambiguous), assigned to planned met-2yhf. No assertion was
weakened. The component20 profiles also pass, input-invariant. Independent finite
review found no required correction in body-slot publication.

The CLI matrix now adds closure/provided/unused and a separate empty-main tool
control. --native-backend links/runs accepted AOT outputs rather than counting IR
emission as execution. The old aefa2b90 control executes its empty AOT/ORC program;
projection programs remain RED until a fresh mapping candidate is built. Full
AOT/ORC, remaining reader audit and cost gates remain open.

## Remaining implementation and verification sequence

1. Recover the running formal fixed-point/cost result for source8bec5272, then
   reuse the existing57-row real check/AOT/ORC matrix with that final candidate
   and run gen. Keep the six wrong Missing refusal rows assigned to met-2yhf;
   do not weaken or silently delete them. A successful native API is not this gate.
2. Close the small evidence gaps identified by independent contract-first audit:
   registered signature admission in Open/Complete/Failed states plus unregistered
   Raw; a static Requirement call through a concrete witness to inherited output;
   and inherited FactoryError through factory body/try/final signature. Reuse
   existing evidence first, add only the missing finite controls. Compare ordinary
   static/provided expected-result reads where their distinct adapters are used.
3. Record the bounded source call-chain audit: registered Source is read through
   its receipt, an unmigrated Raw/synthetic declaration alone may return None,
   and admitted body slots publish saved Parent before Mid. Late assocBindingFor
   may read an exact concrete owner/arguments/member proof; it cannot choose a
   different member or replace a missing Source receipt. Check fallback Param.ty/
   retTy only in these chains, rather than removing every raw field read.
4. Reconcile these gates with the existing short/lexical/head/body/recursive
   evidence and obtain independent task review. Then met-2yhf consumes the saved
   outcomes for owned refusals; parent met-o5z0 retains whole-gate certification.

The independent remaining-scope audit found no additional confirmed defect.
It did not request a producer-by-mode Cartesian product, new language features,
all malformed Raw Comp states or the unrelated C6 closure-field fix. The five
unjoined boundaries above, rather than another whole compiler audit, are the
remaining finite acceptance work.

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

## Expected-result inference and substitution boundary

Direct contextual-result completion reads the admitted declaration pattern.
Known substitutions are proposal-local rigid boundaries keyed by original pattern
nodes; unknown binders alone remain inference variables. Projection boundaries
apply the known map once and close the saved declaring projection. The common
matcher does not re-enter replacement children, even when recursive caller and
callee ParamIds coincide. Empty-map callers retain their existing match classes.
The final result/occurrence/selector comes from the admitted signature reader,
never from the expected type. Explicit views on known parameters are retained.

Argument contexts, final parameter checks and result publication consume those
already-interpreted reader terms. They close remaining projections separately;
they do not apply the callee binder map a second time. This preserves concrete
associated outputs as well as caller-owned recursive terms.

Meta rigid-result-boundary-checkpoint.json retains actual Direct API RED/GREEN,
known concrete/recursive/cross-binder/mismatch controls, final result assertions,
Source recursive inference/typed-closure controls and the component21 gate.
Generic associated-output expectation is assembled by canonical record labels;
initial positional-field probe failures were test errors, not compiler RED.
Independent source and final fixture review found no required correction in this
finite slice, and directly checked all three final result JSONs. Broader gates
remain separate.

The pre-rigidity CLI candidate passes51 of57 actual check/native-AOT/ORC rows.
Only the two wrong Missing refusals remain in that candidate, owned by met-2yhf.
The current Source root18 aggregate also preserves those two failures rather
than weakening them. Fresh current-source CLI, gen, same-source formal cost and
parent gates remain required. No task, whole-green, carrier or stage3 completion
is claimed here.

## Remaining consumer and cost checkpoint

See meta `remaining-consumer-checkpoint.json` for frozen inputs and actual
results. Real Open-window admission and Complete/Failed/unregistered readers
pass; no production admission gate was weakened. Optional absent rigid-boundary
maps avoid constructing empty Dictionaries; the component21 gate passes and an
independent limited source review found no semantic violation.

Canonical parameter patterns now also flow through static provided environment,
final method result and unselected call parameter environment construction.
FactoryError uses its own admitted source slot for the lexical body Result.
These corrections alone do not close the remaining whole-check failures.
Parent-projection controls distinguish inherited lookup failures from an existing
provided expected-result inference failure. Static contextual-result proposal
and final publication are being moved from raw terms to the shared reader;
latest native static-result-reader-v17 remains pending at this checkpoint.

The vector-reuse-only candidate built successfully. Six alternating same-source
samples retain identical LLVM; old/new medians are 8.124098/8.102937s. This is not
a material recovery claim. Formal latest 8bec5272 is 8.073688s at G3 fixed point,
above 7.5s. The task remains in progress; neither candidate nor completion is
adopted. Further functional and cost work is required.

Actual frame-preserved diagnostic stacks identify two remaining raw readers.
Final method argument verification passed original Param.ty directly to grounding;
it now takes selected callee identity and uses the same admitted parameter reader
as source-call closure, preserving labels and inout validation. The ordinary
static expected-result fixture changes from refusal to success (v19).

Provided placement candidates retained canonical lexicalOwnerFnId but the lexical
reader queried the copy's signature map. The reader now uses semanticBodyOwner,
validates original slot identity and reads the symbolic source recipe before the
candidate receiver substitution. Direct placement-reader RED/GREEN asserts that
raw Child stays authored while the copy publishes Parent; the copy itself has no
independent receipt. v20 removes the late Child lookup. Provided Parent/Child
controls both still fail expected-result inference; FactoryError caller and the
separate met-2yhf refusals remain. Independent limited source review found no
guard weakening. This checkpoint does not close the task.

Generic recorded direct-call argument checking had the same raw Param.ty read.
It now consumes selectedDirectParameterSignature/sourceCallArgumentType once per
call; v24 resolves FactoryError Parent/Child caller cases. Component22, including
the new direct placement-reader test, passes. Provided expected-result patterns
retain method binders until shared rigid-boundary matching; v27 passes every
normal whole-check fixture while preserving the two met-2yhf diagnostic failures.

Completion remains unproven: receiver/impl substitutions already inserted into a
provided pattern may contain caller-owned method ParamIds in recursive calls.
Review identifies this possible loss of original-node boundaries. A dedicated
recursive Source fixture is being checked before finalizing that representation.
The isolated canonical-readers build uses an earlier frozen source, not these
later Generic/provided changes; do not confuse it with a final candidate.

## Performance recovery priority

Normal implementation is suspended until the self-host median is at most 7.5s.
The frozen current-source candidate reached a generation-2 fixed point in
`20261128T041820-self-host-1997cd`; samples are 8.760432, 8.216416 and
8.293744s, median 8.293744s. This candidate-start diagnostic is not promotion
of the adopted carrier. Evidence: meta
`evidence/rejection-domains/diagnostic-domain-implementation/projection-members/performance-recovery/`.
The closed-term early-return experiment built successfully, but alternating
three pairs gave 8.171744s before versus 8.212380s after, all LLVM outputs equal.
It is not adopted. Source review additionally found malformed unknown-closedness
input and raw view normalization risks.

Authorized CPU sample (2–5s interval) and exact frozen-symbol mapping are in
meta scratch `tmp/performance-recovery-current/cpu-profile-authorized` and
`symbols.json`; baseline profile input and source are fixed. Declaration
completion and Mid construction appear in that interval; this is not a
whole-run attribution or exact percentage claim.

The lazy parametric-receiver experiment also showed no material recovery
(8.095831s before / 8.114948s after) and is not adopted.

On the same latest source, adopted149aac and the current candidate give
7.437584s and 8.048875s respectively (three alternating pairs). The major
phase difference is function/declaration checking before declaration Mid
construction. Removing only receiver-term IDs in generated method symbol
names yields zero differing LLVM lines for the first pair, not raw equality.

Recipe-header optimization0863e52b changes TypeRef materialization to the
existing TypeTerm reader without removing admission, slot or proof checks.
Build20261128T050405-build-284e87 passed. Warm alternating pairs give
8.117768s / 8.069929s, all LLVM equal and inputs unchanged. Independent review
plus native admission controls and 24 associated/selection/reader profiles
pass. Detailed evidence is under the meta performance-recovery directory.
The source-level recipe contract excludes direct Raw Arena projections lacking
a stored receiver; normal Comp.pushType producers normalize that representation.

The 7.5s cap remains unmet, ordinary implementation remains suspended, and no
hard-to-repair judgment has been made. Diagnostic O0 checking counts241858 reader entries and38060 distinct specified
structural keys; see meta performance-recovery/signature-read-counts.json. Counts
do not establish a complete cache key or a speedup.

An isolated structural-only success memo passed key/CoW/session controls but did
not improve warm runtime (8.149641 -> 8.179752 seconds); it is not adopted.
Diagnostic counters: 241809 eligible reads, 203765 hits, maximum bucket size2.

A narrower scope-presence Bool query and identity receiver shortcut preserve the
original validation fallback. Baseline targeted counter RED, candidate GREEN;
presence controls and all24 component profiles pass with unchanged inputs.
Independent review found no mandatory correction. Warm alternating three-pair
medians 8.079642 -> 8.012548 seconds, all six LLVM hashes identical. The limited
improvement is adopted; formal <=7.5 recovery remains unmet. Ordinary type
checking work stays suspended. Next investigate residual declaration-checking
cost, without adopting the result memo or promoting bin/seed.

Complete SourceParameters vector forwarding passed build/native24/source review
but warm medians 8.025435 -> 8.077316 seconds showed no gain (LLVM identical).
Not adopted. Next isolate temporary memo administration for nonrecursive leaf
recipes; preserve every proof, environment and malformed-input boundary.

Authored leaf memo administration: preserve complete interpretation but omit
final memo entries for leaves with no children/sourceRecipe/projection/views.
Build and native24 passed; independent source review found no mandatory issue.
Warm medians 8.072792 -> 8.011871 seconds, all LLVM identical. Limited adoption;
not formal recovery. Next count reader modes by declaration phases, retaining
all checks. No method/result work or carrier/seed promotion is resumed.

## Performance recovery stop boundary

Ordinary met-y2ec/Source work remains suspended until formal <=7.5s recovery.
The header/scope/leaf changes yield only limited improvements. Closed grounding,
lazy receiver preparation, structural result memo, vector forwarding and
identity-write experiments did not demonstrate sufficient recovery.

Latest finite old/current same-target coarse-phase diagnostic: instrumented
wall medians7.519873/8.091147s. Added exclusive Record0.250s, Generic0.001s,
Verify0.132s, Rest0.060s, outside0.129s. All receiver-number-normalized LLVM
equal, inputs unchanged. Separate inclusive retained-signature reads~0.356s
include mandatory first reads and observer effects; do not sum them with phase
deltas or treat them as entirely removable. No formal recovery is claimed.

Engineering judgment, independently reviewed: no currently identified local
repair supports <=7.5 recovery; broader multi-phase investigation/repair is
needed before resuming. This is not proof that a large change is technically
inevitable, nor evidence selecting a cache architecture. All handles collected.

On explicitly authorized resumption, attribute added signature interpretation,
construction receipt and fixed-replacement work within Record/Verify/Rest, and
explain outside-phase cost. Separate necessary semantics from recalculation.
If transfer of checked results is justified, preserve exact selection revision,
readiness, source owner/scope/session, environment/proof and fact lifetime across
consumers. Do not silently use scalar diagnostic keys as reuse authority.

Source-reviewed small opportunities remain unproven recovery candidates: empty
argument signature reads in Verify/Generic (12347/62); duplicate projection
presence queries in callableParameterPatterns; repeated construction-head
occurrence/use extraction. Preserve admission and current-expression checks;
do not try them sequentially without measured contribution.

Evidence and final independent assessment: meta projection-members/
performance-recovery/{declaration-phase-*,recovery-decision-review.md}.
Pending feature work is preserved as WIP, not completed or promoted.
