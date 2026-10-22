---
id: met-ucze
status: in_progress
deps: []
links: []
created: 2026-10-13T01:40:08Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, generics, verification]
---
# Unify source member selection without downstream reselection

The historical 2983c47f review found Resolve/Preparation trying Record(false), Generic, Declaration and Record(true), with Record/Generic staticMemberResolution paths and different bound/trait candidate inputs. This was a structural read-only finding, not a newly reproduced current miscompile. Recheck the cumulative candidate before deciding which paths remain.

Make one source construction/selection owner authoritative and preserve the selected declaration, requirement, lexical owner and evidence through publication and final consumption. A shared selector repeatedly run by downstream readers is not completion. Preserve candidate order, visibility, labels, full signature, ownership and bounds; do not make a candidate-exists predicate final acceptance. Distinguish constructing a first concrete witness for a source-selected abstract requirement from selecting an already fixed witness again.

Acceptance: trace ordinary, generic-bound, provided, trait-subject, operator and implicit calls; remove competing source selectors/fallback accept paths, retain ambiguity/reject controls, and record remaining paths and removal conditions. The storage restart gate of met-si6j applies.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Included repair**.

Current written, generic-bound, provided, operator and implicit-call selection. Eliminate competing source selectors while preserving source-selected abstract requirements and legitimate first concrete witness formation. Sequence after the owner-reader core; this is implementation order, not a fabricated dependency on every other frontend ticket.

## Next Closed Increment: Source Operations

Rechecked at production `85aa9a96`, while com-kp3y is finishing its gates.
The owner-local expression/header/binding/completion component does not yet own
`Comp.callTemplates`, `callTemplateIndexSlots`, `callTemplateSourceOwners` or
`selectedCallConstraints`. Preserve their existing site keys and final descriptor
identity while migrating their semantic rows through the same owner boundary.
Coordinate with met-acfl and met-ia09; do not call storage alone completion.

The construction frontier is Resolve/Record's direct/static/dynamic/operator/
protocol producers and the type queries they call. Preparation currently visits
Record(false), Generic, Declaration and Record(true). Generic's symbolic method
checks can consume a recorded template, but several branches still call
staticMemberResolution or bound/member-existence queries again. ExprType also
constructs method results when no completed expression fact is available.
The migration must identify permitted tentative inference separately from an
already committed source choice; routing all repeated selections through the
same algorithm is insufficient.

Close one source-operation contract from construction to consumers:

- Give the source checker one operation-construction boundary. Private candidate
  probes may refine permitted unknowns; only the admitted candidate commits its
  declaration/requirement, receiver/evaluation sources, complete signature,
  substitution, result recipe, conversion and evidence. Preserve explicit
  uncomputed/no-static-selection/selected states where applicable.
- Generic/declaration compatibility reads the committed operation instead of
  selecting another member. Remove redundant construction walks only after
  their distinct checks have real owning producers/readers; do not simply omit
  Generic or Declaration diagnostics to obtain a single walk.
- Store successful operation and constraint rows in the owner payload, retaining
  immutable shared argument/type/proof ranges as session IDs. Any remaining
  global navigation index contains identities, not a second semantic store.
  Body/call-site readers reject missing/foreign/unprepared facts and cannot
  snapshot every owner's calls.
- Instantiate those saved operations and exact declaration-bound evidence into
  the callee environment and real Mid/final call consumers. The existing
  InstanceEnvironment.constraints and final CallSiteKey identities are inputs
  to preserve, not new mechanisms to recreate. Legitimate first concrete witness
  formation stays within the source-selected requirement.

Additional physical boundary to resolve: closeProgramCallTemplates currently
rewrites CallTemplate.mayHaveStorageArguments after source preparation. This is
an auxiliary access-demand classification, not permission to mutate a sealed
operation. Compute its source-stable part before sealing or give later analysis
its own result. The public requireCallTemplateStorage writer has no production
caller in this revision; audit tests/references and remove or place it under the
actual analysis authority instead of retaining an unrestricted payload writer.
`tests/compiler/mid/DeclarationLocalAccess.pw` does use it to force an eager
reference analysis beside the demand-filtered analysis. Preserve that comparison,
including equal diagnostics and absence of executable-body/destructor discovery;
move the eager root selection to the analysis request rather than mutating the
source payload or deleting the negative control.

Verify direct, requirement/provided, dynamic, operator and implicit calls through
actual callee bodies, with positive and wrong/missing owner/site/clause/proof
controls, AOT/JIT/gen and removal of competing decisions. Include a matching-source
old/new cost comparison whenever the new increment appears slower; fix easy
extra copies/searches rather than relying only on the seven-second ceiling.

## Storage Summary Publication Increment

First remove the remaining post-success template rewrite before moving operation
rows into owner payloads. `mayHaveStorageArguments` is a conservative source-stable
summary of the selected signature and operand passing forms. Compute it at the
private successful lexical/global preparation tail, including nested closure
rows, after default/selection/obligation closure and before source publication.
Whole-program closure and Mid analysis only read the result. Preserve the
conservative true default for unknown forms and subsequent sites once an owner
is already known to require access analysis.

Remove requireCallTemplateStorage entirely. DeclarationLocalAccess's existing
eager comparison must request eager analysis explicitly instead of mutating source
calls; preserve diagnostic equivalence, demand-versus-eager body counts and absence
of executable/destructor discovery. New controls check precision immediately after
a lazy function/global request, post-success writer rejection and stability across
whole-program closure. This bounded publication repair does not complete source
operation storage/selection/evidence migration.

## Source Selection Construction Increment (WIP)

After the storage-summary repair, construct function operation rows in the first
Record walk, disable call construction for Generic/Declaration compatibility, and
remove the second Record walk. Keep default-generator restriction and result
validation at the same construction boundary; do not lose checks that were gated
on the old false/true pass flag. Source-call closure still checks complete selected
Direct/Static signatures, labels, ownership modes, substitutions, operand/conversion
plans and admitted bounds/evidence.

Generic method validation reads the selected declaration for qualifier category
and retains its existing contextual argument checks. Remove its independent
staticMemberResolution, boundProvidesMethod and traitProvidesMember call paths.
The old traitProvidesMember/boundProvidesMethod candidate-exists helpers are
removed. Their internal owner-identity control now uses the retained source-type
query, preserving positive/private visibility and wrong-owner rejection. Operators/iteration and
Verify's concrete method queries still require their own saved-operation reader
migration. Removing a walk alone is not completion of this task.

New generic_call_selected_authority poisons only the method's diagnostic AST name
after construction while retaining its CallSiteKey: compatibility must use the
selected requirement, add no operation, and reject a deliberately missing saved
selection. Ordinary/generic/provided/default/closure/global AOT/JIT/gen and full
signature rejection controls remain required. Fresh builds and whole compiler-source checks now succeed at `699a9c59`;
normal verification of the preceding 0793cf02 snapshot is independent.

## Construction-Order Findings and Validation Boundary

Enabling the first operation-construction walk exposes dependencies on the old
second walk. Repair the owning producer rather than restore a global repair walk:

- An untyped numeric receiver such as `0 - typedValue` obtains only its permitted
  integer literal context before selection. A typed receiver's selected signature
  still owns Rhs context; heterogeneous operators are not forced homogeneous.
  Retain source result projections, particularly Ord's Ordering -> Bool.
- The second nominal-field visit must use the same constructionFieldContext as
  the first. Diagnostic inspection of SourceFacts.setState found a spurious
  conversion from SourceBodyState to Optional's unbound `T@39`; the completed
  expression still had SourceBodyState. Do not treat omitted declaration binders
  as rigid lexical context.
- Synthetic nominal Make nodes may have a selected name and no annotation term.
  Resolve that nominal term before field context and aggregate publication. The
  existing generation directiveargs control exposed the missing aggregate in its
  synthesized main; no gen-specific bypass or fabricated aggregate is introduced.
- A conversion requested while its source term is zero is an explicit builder
  dependency (pendingSource), not failed final evidence. Complete it from the
  recorded expression fact after default/type refinement and before call closure
  and owner publication. Never re-infer source syntax in the final reader. Both
  evidence admission and Mono reject pending requests; post-outcome conversion
  construction is rejected. Known incompatible evidence remains rejected.

New controls: generic_call_selected_authority, source_operator_literal_context,
inferred_enum_argument_source_owner and pending_source_conversion_completion.
The pending-request control and unchanged declaration_conversion_closure reject
control pass when current compiler source is compiled into the fixture with the
stable storage-publication carrier. This source-probe evidence is distinct from
testing the fresh compiler executable.

The `95bd11cb` fresh compiler source check passed. Its AOT slice passed the three
initial new controls plus retained call-result/substitution/proof/private-provided
controls before stopping on operator_literal_nested's stale zero-source conversion.
Its generation gate passed 23 positives and five rejects, failing directiveargs.
The pending/nominal fixes pass fresh compiler source checking, fifteen AOT
controls and the full generation gate (24 positives / five rejects) at 699a9c59.
The 8cd5172f row-refinement follow-up also passes fresh whole-source checking,
eight AOT controls and eight existing rejects, including identity/boxing
conversion completion. Formal fixed-point/performance validation is in progress. Full operation storage, callee-evidence and remaining
Verify/operator/iteration selector migration are still open.


## Concrete Compatibility Consumer Increment (WIP)

Verify's method and source-qualified method cases consume the exact CallSiteKey
selection. Direct calls use the recorded callee, type arguments and proof to form
the parameter environment; StaticMethod reads the retained requirement/provided
declaration; existential calls read the retained requirement slot. A missing or
unfinished selection is an error, never a reason to retry resolveWrittenMethod
or resolveExtMethodFinal. Receiver ownership/place/inout-overlap checks share the
selected Func contract. Public visibility applies to concrete/provided callable
declarations; a trait requirement is not reinterpreted as a private free method.
The transient callee cache is only populated from the saved direct selection.

Global initializers also construct calls before Verify, removing their second
Record pass. Record passes its already computed static resolution to unresolved
method recording instead of repeating the same candidate query. This is still a
construction boundary, not final owner-local operation/evidence storage.

verify_call_selected_authority preserves the selected direct identity under a
diagnostic-name edit for ordinary, source-qualified and associated calls. Removing
the saved selection must fail. It also requests a method-bearing global. The
current-source AOT probe passes, as does source checking by the stable prior
compiler; fresh compiler execution remains pending. Operators/iteration, global
legacy entry points, operation storage and callee evidence remain to close.


## Source Owner / Compatibility Closure Follow-up (WIP)

The first-construction checkpoint's full normal gate found four failures: the
internal source_diagnostic_owner_requests assumption that an annotated return
produces no conversion rows; a constructor's known binding conflict being reduced
to unresolved inference (wrong diagnostic); and two private provided-method calls
accepted through trait/supertrait bounds. Preserve the external reject fixtures.

Source member selection filters provided candidates by authored visibility,
including inherited bound paths. Static provided-template construction also
checks that authority at the actual use site; requirement signatures remain
public interface operations. A definite constructor TypeArgumentMatch.Conflict
is a type mismatch, not an unresolved inference hole.

Declaration registration discovers global types but no longer runs a competing
global verifier or closes global operations. Each initializer request constructs
its selected calls before compatibility, completes defaults/conversions and
checks evidence/diagnostics before source success. Whole checking and startup
already request initializers. Keep legacy generation entry points separate and
audit them, rather than permit a missing-operation lookup fallback in Verify.

The diagnostic-owner control now uses a statement-only invalid unary expression,
so no destination conversion is incidental to its diagnostic-retention test.
The global call-constraint fault-injection control explicitly constructs its
owner's plan before corrupting it. Neither change removes rejection, owner
independence, cursor restoration or evidence checks. Current-source AOT controls
for operator selection, diagnostic retention, global constraint evidence and
concrete selected methods pass. Fresh binary and full gates remain pending.


## Operator Compatibility Reader (WIP)

Generic and concrete unary/binary compatibility consume the retained Operator
selection and parameter types under its saved receiver/proof. Logical operators
remain Bool control flow. Primitive range/type restrictions remain separate from
availability. Remove Verify's independent witness search and Generic's
bound-name/candidate search; missing operation state is never reconstructed.
The source_operator_literal_context control now removes a saved selection after
successful construction and requires compatibility to reject it.

A source identity's span is not authored visibility provenance: synthetic keys
use a serial and zero originStart. Concrete verification derives visibility from the lexical source owner's
authored module (through its retained parent/header), while diagnostic offsets
and CallSiteKey remain separate. Neither a diagnostic-name edit nor a synthetic
serial-only key may change namespace authority. A cross-module private-factory control is being added.

The optimized current-source diagnostic driver accepts the entire compiler
source and preserves the constructor-conflict and two private-member rejects.
The same driver linked at O0 exhausts the default stack on the deep whole-source
probe (recursive frame approximately 522 KB); the regular optimizer/link pipeline
succeeds. This diagnostic driver is not a fresh compiler executable or a formal
performance result. Fresh build, target execution and gates remain pending.


## Next Source-operation Boundary

Finish iteration compatibility from the retained iterator/next operations and
result recipe, including record-pattern binders. Keep Core protocol identity,
associated Item constraints and existential restrictions at the owning source
selection boundary; removing a later query cannot erase its distinct checks.
Audit staticOperatorTemplateResolution/checkSymbolicMethodArgs and lexical Self/
parameter predicates: closure keys are operation owners, while assumptions come
from the retained lexical root. Do not collapse a closure's CallSiteKey to that
root to obtain its bounds. Existing generic_closure_lexical_bound and its wrong-
lexical-bound reject remain controls; add operator/type-qualifier cases if the
remaining raw function-count guards are reproduced as failures.

Then move operation/constraint semantic rows into the owner payload and carry
exact callee evidence through final consumers. The just-validated compatibility
readers do not complete physical storage, callee evidence or phase three.


## Lexical Environment and Operator Surface Repair

The operation owner of a closure remains its own body/site identity. Binder,
Self and assumption queries project through the retained lexical function;
function-count guards must not discard a closure's generic environment. Positive
operator and type-qualifier cases and a wrong instance-qualified call exercise
this distinction. The qualifier fixture supplies an unused typed witness to infer
the outer generic argument; it does not require unrelated explicit generic-call
syntax support.

The selected operator has two boundaries: its logical source receiver, retaining
views, and its implementation's lexical parameter representation. Compatibility
uses the retained receiver term for Self; final call elaboration owns the selected
implementation boundary. Do not globally erase views or relax value compatibility.
A Pending operation is still rejected at source closure, using the shared operator
category diagnostic rather than another lookup. Constructor constraint conflicts
are decisive at construction and preserve the existing inference/type-mismatch
diagnostic categories. No reject expectation is weakened.

The frozen ff9a8a1c full suite failed in three positive view cases and two reject
diagnostics. The following build/slice must establish these repairs independently;
the formal 5.932379-second checkpoint remains evidence for ff9a8a1c only. This
repair does not close iteration selection or owner-local operation storage.


## Iteration Source Contract Increment (WIP)

Record now selects canonical Core protocol owners even for concrete receivers.
The pre-repair carrier accepted both a structural next-only cursor and a
structural iterator-only collection; dedicated reject controls retain these
failures. Generic/Verify read the selected next result through its exact slot
and the saved Optional carrier identity. For-field access receives the actual
Item, including a nested array; the old independent iterable Item helpers are
removed. The provisional registration walk may query private protocol context
without publishing operation/recipe success; the successful owner commits it.

The first fresh build passed 19 AOT golden outputs and 15 rejection outcomes,
including generic closure iteration, projected/inherited/existential protocols,
array-valued Items, typed bindings and destructuring. An operator-bound diagnostic
still failed because sourceSelectedCallBounds omitted Operator/Protocol entirely;
its eventual declaration worklist reconstructed the constraint at a library span.
The follow-up gives these selected signatures the same source constraint
construction as written methods. It must pass a fresh build and the existing
nested_array_noeq control; the earlier attribution change alone did not fix it.

Physical operation/constraint storage and exact callee evidence remain open.
These source compatibility repairs are not phase-three completion.


## Next Physical Storage Unit

Keep one session navigation row per CallSiteKey containing only its source owner
and dense local operation identity. Move the CallTemplate and selected-constraint
state into SourceBodyData, using the existing private active/inactive builder and
immutable successful-owner reader. Shared argument/type/operand/view pools remain
append-only session ranges; they are not a second per-owner semantic store.
Publication must keep the current admitted-constraint capability and writer
closure. Replacing the global arrays with owner-aware getters while retaining a
second semantic copy is not completion.

Migrate exact-site, signature/result, declaration-worklist, Mono and Mid readers;
retain original site/clause/constraint identities. Production whole-session scans
iterate navigation rows and acquire the referenced owner data, rather than
snapshotting every owner's templates. Diagnostic test snapshots may materialize
an explicit inspection copy. Keep owner/session/missing/failure controls, stable
retained readers, Comp branching and publication cost measurements. Do not
reintroduce a full SourceBodyData by-value read for one operation row.

After storage is closed, complete exact callee evidence and replace remaining
Declaration evidence reconstruction with the saved selected-call evidence.
Legitimate first concrete witness formation for an abstract requirement remains
separate from selecting source syntax again. This plan refines the adopted
checked-body-storage design without changing language semantics or runtime ABI.


## Owner Operation Storage Implementation (WIP)

SourceBodyData owns SourceOperationRow (CallTemplate plus construction/prepared
constraint state). The session callTemplateLocations stores only CallSiteKey,
SemanticCompletionOwner and dense local index. Argument/type/operand/view pools
remain append-only session ranges. The former global callTemplates,
callTemplateSourceOwners and selectedCallConstraints semantic stores are removed.
All source, declaration, Mono and Mid callers now read owner rows; rebuilding an
index uses identity metadata only. Production callTemplateSnapshot scanning is
removed; the explicit snapshot remains a diagnostic/test inspection copy.

PreparedSemanticFacts exposes a bounded local operation reader over the retained
immutable payload. Construction mutation checks owner closure and exact site;
constraint publication still consumes the admitted value before source success.
Readonly operation queries do not require a mutable compiler merely to read an
immutable artifact. Verify Comp forks and failed-owner isolation rather than
sharing a mutable Ref across copies.

The source-imported controls pass publication, retained reader stability, foreign
session rejection, Comp builder branching, global constraint corruption, selected
call authority and iteration authority. A diagnostic-continuation control exposed
a previously overbroad global default-completion walk: a lazy global request must
complete only its own retained call indices. That repair passes the original
failure/retry/unrelated-global/cursor expectations unchanged. Origin fallback
navigation also compares navigation keys before opening a payload; failed
unrelated owners have no semantic rows to inspect.

These controls compile current algorithms through /Frontend with the previous
fixed carrier. A fresh compiler, formal cost and full current-candidate gates are
still required. Exact callee evidence transfer is the next semantic increment;
physical storage alone does not certify it or phase-three completion.


## Operation Read Cost Repair (WIP)

The first owner-local storage candidate reached a second-generation fixed point
but regressed to a formal median 7.624807 seconds. The same frozen source measured
5.909264 versus 7.607760 seconds, with identical LLVM on every run. Sampling and
optimized IR identify nontrivial readonly Comp getters retaining a complete Comp
value argument (gm3135 callTemplateAt), rather than only the operation inputs.
The immutable conversion of SourceFactDirectory state/isActive/inactiveBuilder
also changed existing hot construction queries.

Construction/read adapters and actual Mid declaration-access callers use in-place
session queries. The first narrowed candidate restores a second-generation fixed
point at 6.655382 seconds; its matching-source comparison improves 7.665639 to
6.760961 seconds with identical LLVM. Fresh source check and 30 AOT/17 rejection
controls pass. The next bounded repair removes the transient multi-table query
projection and reads through the existing SourceFactDirectory in place instead.
No second owner-state lookup implementation remains. Cache reuse still checks
both session and owner; template reads still check the exact CallSiteKey.

Retained PreparedSemanticFacts remains the immutable final reader. Source owner
operations and constraint states use parallel dense columns under the same local
ID; reading one template cannot copy and destroy its unrelated constraint state.
Their writer and publication boundary remains joint and owner-local. No ARC,
validation, visibility or semantic check is suppressed. The directory simplification
has passed whole-source checking; its fresh carrier, matching-source performance
and complete affected gates remain required. Performance and scoped evidence live
in meta/evidence/existing-feature-conformance/source-owner-facts.

## Conditional Protocol Failure Diagnostics (WIP)

The 2899ddad full normal gate completes all 1433 run cases and reports four
rejection-diagnostic mismatches, with unchanged inputs. Three internal privacy
fixtures still address the removed global constraint/owner storage. They now
exercise PreparedCallConstraints's private plan/factory and private navigation
locations, preserving actual construction/read boundaries and their original
privacy assertions.

The external unused_for_float_range remains rejected, but a generic missing
protocol message hides its original closed Step-bound failure. Preserve its
expectation. At the failed source-selection boundary only, diagnose a structurally
matching canonical Iterable/Iterator conformance whose closed substitution fails
its declared conditions. The same matcher and condition-evidence query supply the
cause; candidate presence never permits acceptance or a prepared-owner read.
Abstract underconstrained receivers still use the protocol diagnostic. Protocol selection now establishes canonical trait applicability before selecting
its requirement. It no longer accepts a same-shaped implementation and waits for
its bounds to fail after it has hidden an available Iterator. Concrete and abstract
receivers retain the same Requirement/proof contract; selected concrete evidence
closes associated result projections under an explicit receiver environment.
Valid Iterator fallback is resolved before the error path; an unavailable
conditional Iterable cannot hide an available Iterator. Add a non-range conditional protocol
rejection and that positive fallback control. No source type spelling is special.
Fresh diagnostics/execution and full gates remain required.

The first fresh diagnostic slice exposed three failures: the error-only helper
was not reached when a structurally selected implementation later failed its
conditions, and that early choice also hid valid Iterator fallback. The initial
requirement-only experiment exposed missing name IDs and concrete associated
result normalization; both are fixed at construction. A current-source imported
frontend probe now accepts the fallback control. Fresh complete slice, canonical
selection/corruption controls, matching-source cost and full gates remain required.
