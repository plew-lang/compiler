---
id: com-amjl
status: in_progress
deps: [com-x95z, com-zdod]
links: [com-oir7, com-8egj, met-c1pg, com-16j0, com-0w38, com-wka4, com-9hde]
created: 2026-11-06T09:51:26Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, generics, verification]
---
# Establish trait-view evidence before admitting associated projections

Validate authored trait-view applicability under the exact lexical receiver and trait instance before source declaration success; preserve evidence through associated projection and final consumption. Repair the two com-x95z success setups without weakening their original graph/equality coverage.

## Contract and Confirmed Defect

[Spec09](../../../spec/spec/02-type-system/09-extensions.md#拡張ビューと-トレイトビューの非対称混同しやすい)
requires an existing conformance before forming a trait view: `#P` selects a
source and never creates conformance. This applies to type and value views.
[Spec08](../../../spec/spec/02-type-system/08-traits.md) makes
`T#P[Args].Item` an exact source/instance selection; `T.Item` is a shorthand only
when the lexical bounds uniquely determine that complete instance and member.
The declaration's own bounds, inherited premises or other specification-valid
evidence can justify a symbolic receiver; concrete resolution is not required.
Follow [Types and Evidence](../design/types-and-evidence.md#4-substitution-and-projection),
[source handoffs](../design/frontend-handoffs.md) and
[name lookup](../design/name-lookup.md). No new language rule is adopted.

[Investigation](../../../evidence/rejection-domains/projection-admission-investigation/README.md)
and [executed controls](../../../evidence/rejection-domains/projection-admission-investigation/cause-controls.json)
record current ordinary generic signature acceptance with no bound, unrelated
`T: Q`, and `T: P[I64]` for a requested `T#P[String].Item`. All pass the fixed
candidate. Correctly bounded input also passes; missing-member, unknown-trait
and concrete-no-conformance controls reject. The demonstrated cause is missing
generic justification, not a demonstrated unrelated-evidence leak.
Standalone `T#P` behavior and other entry paths require execution before claims.

`resolveAssocProjection` preserves ParamId receivers without querying evidence;
`checkProjectionMember` checks member existence but not receiver conformance.
Both responsibilities are individually useful, but neither establishes source
view validity. Deferral of concrete evaluation must not mean deferred proof
that a declaration is legal. Fix the common view-formation responsibility,
not an Item-specific missing-bound check or removal of symbolic deferral.

## Finite Repair and Final Consumer

Trace authored type/view construction -> lexical declaration environment ->
exact trait-view admission -> successful source publication -> associated term
and retained proof -> generic substitution/concrete output or dynamic consumer.
Include unused signatures, body annotations and value views on the supported
surface, and applicable check/build/lazy-run/gen declaration paths. Record actual
callers and applicability rather than asserting all modes share an entry.

- Establish receiver + canonical trait owner + full positional arguments under
  the originating ParamId/bound environment. Reuse the common conformance/source
  selection query; do not invent a second view-only solver or use an existence
  query as unique source admission. Preserve inherited and selected-extension
  evidence and existing ambiguity rules.
- Preserve established justification until projection/final use. Symbolic
  validity and concrete normalization remain separate. Do not recover proof from
  an unrelated ambient cursor, same-spelled binder or another trait instance.
  Retained facts/cache identity must include the necessary environment and
  source selection; remove competing unchecked source-success paths.
- A missing premise on valid authored input is a source diagnostic at the view
  selection, before member/output use; malformed raw input remains a typed
  non-Source failure under the shared input contract. Never tag arbitrary
  unresolved requests Source merely to satisfy a rejection consumer.
- Keep projection member existence, exact positional arity and short-form
  uniqueness checks. No implicit bounds, concrete witness lookup for every
  abstract declaration, or expectation inferred from current compiler success.

## Existing Test Corrections Authorized by the User

Preserve the introducing purposes documented by com-x95z:

- `tests/fixtures/run/trait_subject_cycle_parameterized_projection_distinct_allowed.pw`:
  distinct trait-instance projection arguments must not manufacture a cycle.
  Correct the whole-source success setup; if a valid source setup cannot express
  that structural case, retain it at the proper internal graph boundary and
  provide a valid source companion. Do not silently discard the comparison.
- `tests/fixtures/run/inherited_projection_identity.pw`: preserve inherited
  diamond equalities, foreign receiver distinction, symbolic missing-query
  behavior, Conflict versus known Unit term0, and no body discovery. Separate
  the internal unavailable Parent[String] query from successful admission of
  an embedded signature requiring that unavailable premise.

No conditional trait-to-trait `where` workaround is authorized (spec08,
com-wfq2). The two projection growth/binder rejection oracles remain owned by
the structural graph boundary and must not become unrelated missing-bound tests.
If stronger source admission changes their setup, preserve their exact graph
assertions and independently validate source diagnostics/order.

## Scenarios and Completion

Begin with meaningful REDs and valid GREEN controls from the saved candidate:
standalone `T#P` and projected `T#P.Item`; no bound, unrelated bound and wrong
trait instance; correct direct/inherited bound; same-spelled foreign binder or
unrelated declaration; unknown owner/member and arity; ambiguous/unique short
projection; supported selected-extension and nested type contexts; unused
signature and actual instantiated use. Test distinct semantic boundaries, not
all Cartesian combinations. Existing passing cases are controls, not defect REDs.

Complete only after source construction through final use is closed, retained
facts and alternate entry paths are structurally checked, corrected fixtures
retain meaningful assertions, and fresh targeted execution plus independent
neutral review accept the guarantees. Coordinate Source diagnostics with
com-yeua/com-fsuq without treating their whole tasks as prerequisites.
Final fixed-point/performance/full-suite gates remain G2a/G2b under met-si6j.

## Dependencies and Exclusions

com-x95z supplies the finite contract/oracle investigation and owned follow-ups,
not this product's GREEN. met-ia09 and met-6e6k must admit this repair before
closing their affected evidence/final-consumer boundaries; com-604k retains it
at integration. met-c1pg remains a separate raw graph-admission repair and does
not wait for this entire product repair: structural cycle checking does not
solve receiver applicability/where satisfiability before comparing terms.

com-oir7 owns view-check API authority narrowing. Closed investigations
com-16j0/com-8egj retain the projection/grounding input maps and their assigned
product repair owners; they did not complete those product repairs. Consult
their outcome sections and share this corrected semantic contract with the
actual affected repair owners, without duplicating their entire repairs or
adding unrelated full-task prerequisites. This task does not certify those APIs
already satisfy design.

Those existing product owners are com-p5q2/com-4vvt/com-be0m/com-4oor/com-hnm8
(com-16j0 outcome), and com-d4m2/com-9nbx/com-nei5 (com-8egj outcome). At
implementation, record which changed API is responsible for semantic evidence
admission here versus authority narrowing there; a shared API name alone is not
a new whole-task dependency or authorization to duplicate its implementation.

Excluded: new projection syntax or meaning, implicit conformance, conditional
trait-to-trait support, general solver/SCC redesign, unrelated API narrowing,
new unique/opening features, main/seed promotion, and claiming scope-wide
completion from helper comparisons alone.


## Complete-Instance View Coordination

The approved type/value view rule and executed state investigation are assigned
to com-zdod (shared complete selector terms), com-9hde (Syntax/Lower) and
com-4k31 (final call selection). This repair depends on com-zdod's term contract
and retains common exact receiver/instance source-proof admission, including
its original projection controls and authorized test corrections. com-4k31
consumes that shared proof instead of implementing another solver. No dependency
on com-4k31 or whole Syntax migration is introduced here; coordinate the shared
API with its actual producer/consumer without duplicating their task bodies.

## Complete View Reader Handoff

The earlier com-zdod review identified a legacy proofSourceIsActive reader.
Current source reads complete semantic sources and distinguishes extension kind;
do not retain the old viewIds-only observation as a current defect. This does
not establish exact-instance admission or retained proof to final consumers.

## Array Receiver Admission Increment

The com-9hde preservation probes expose an existing common source-query defect,
not an ambiguity of bracket parsing. Array TypeInfo intentionally carries an
I64 element-name adapter together with a complete Array[I64] term. The authored
value-view checker passes both to resolveViewSourceKey; its conformance filter
and extAppliesToType's extension filter compare the element-name head before
matching the structured receiver. A parenthesized extension view fails too.

[Executed diagnosis](../../../evidence/rejection-domains/diagnostic-domain-implementation/array-view-receiver-investigation.json)
retains noninstrumented rejection, successful plain indexing, scratch-only output
at the actual query boundary, and a canonical-head counterfactual. Neutral review
assigns this repair to this existing common receiver/source-admission scope;
com-79k3 remains responsible for API authority narrowing, not these algorithms.
No new whole-task dependency or language rule is introduced.

Finite guarantee: when the query has a complete receiver term, candidate head
filtering and structured matching consume that same receiver. Legacy name input
is only an adapter fallback when no term is available. This is not an Array
exception, a proof of selected-instance arguments, or completion of this task.
Cover extension, parenthesized extension, zero-argument trait and view-free array
indexing, nominal receiver preservation, and rejection of a mismatched extension
or missing trait conformance. Remove the competing element-head interpretation
from both common source-query filters; do not merely patch one verifier call.
Run fresh focused native tests and shared source-query controls, inspect the
actual consumers, and obtain neutral review of this increment before returning
to com-9hde's parser work. Task-wide retained evidence/projection/final-consumer
requirements remain open.

[Finite repair verification](../../../evidence/rejection-domains/diagnostic-domain-implementation/array-view-receiver-repair.json):
standard build `20261107T104002-build-ff7b35` passed. The common read-only arena
projection supplies the complete term's head to both filters, with a ref0-only
legacy fallback. Nine Frontend scenarios plus an actual ref0 source-query
control pass with exact golden/empty stderr. Seven old/new native programs match
goldens and three rejection controls retain their diagnostics. An additional
old-candidate RED accepts `Array[Meter]#E` for an I64 extension; the fresh candidate
rejects it, while Meter's own inherited extension remains valid. Neutral review
independently reran the final native probe and reconciled all 198 target/210
control input hashes without mismatch; no additional finite required repair.

The existing newtype-underlying extension recursion still omits the underlying
full term ref. This increment does not establish generic newtype inheritance or
repair that erasure. Full exact-instance evidence, retained source facts,
projection/final-consumer work and task-wide gates remain open; do not close this
task or infer that parser preservation alone supplies these guarantees.

## Short-form Instance Controls from Source-path Preservation

The existing complete-bound-instance requirement has concrete manual controls:
MaterializedTypePathControls mode shorthand preserves accepted short-form
admission/name/ParamId receiver only; shorthandInstance requires canonical trait
owner plus the bound I64 argument; it printed0 against golden1 before the
complete-context increment below, and now passes. A
focused raw-shape diagnostic found the written bound span rather than canonical
declaration owner and an empty positional-argument list; this is not proof of a valid
complete instance. Retain this failing control as required work, and make it GREEN before closing
this task; short-form admission alone is insufficient.

The unchanged old candidate487138f4 also rejects
fixtures/ImplTraitInstances/QualifiedShorthandInstance.pw (`where T: Types.P[I64]`)
with no unique short source, while accepting BareShorthandInstance.pw
(`where T: P[I64]`). Both belong to this task's lexical complete-instance and
short-form uniqueness contract. The com-9hde qualified explicit-path repair
does not certify or replace them. Original results live under the saved
qualified-type repair evidence; no new specification or task scope is adopted.


## Short-form Complete-bound Context Increment (WIP)

The name-only Lower context loses qualified paths and positional arguments;
owner-only dedup also collapses P[I64] and P[Bool]. New
ShortProjectionBoundInstances records seven actual failed assertions and the
preserved zero-argument success. The current complete-context implementation
passes17 native controls, including value-AST adapters, nested/two arguments,
qualified bounds, ambiguous instances, missing/open premises and legacy SigAst
with omitted optional rich bounds. MaterializedTypePathControls shorthandInstance
now succeeds; the prior37 preservation cases also succeed before the last
compatibility/dependency follow-up and must be rerun on the final source.

Replace name/span-only context with complete TypeAst/TypeId constraint nodes at
all four scope owners in both adapters. Preserve one constraint row per subject
when legacy whereTraitTypes is absent, before concatenating impl/member scopes.
Both short-projection adapters use one exact-instance uniqueness decision and
save that instance directly. The normalizer only transforms representation;
remove its name-only semantic choice and the subsequent owner/arity reselection.
Reuse private argument decoders shared with full constraint lowering, filtering
out non-member sources before recursively decoding their arguments.

Neutral WIP review identified the rich-field omission/index-shift regression
and a dependency recursion risk; both are mandatory before finite acceptance.
The first dependent test accidentally gave P its own Item, unlike the review's
Zero-plus-nonmember-P case; do not count that as the intended valid-source RED.
Keep the corrected valid dependency control, and a separate recursive query
control requiring typed Limit instead of a crash. Both adapters share a fixed
32-request depth budget, restored on error; an initial128 budget overflowed the
native unoptimized stack. This is resource exhaustion, not evidence of source
invalidity. No infinite-recursion proof or language type rule is introduced.

Remaining original task work includes semantic receiver/ParamId matching
(current boundLhsMatches helpers still compare raw forms), inherited premise
selection, common view-conformance evidence, raw-input categorization, retained
proof through final consumers, authorized old fixture repairs and applicable
gates. Legacy adapters and dependency behavior need re-review. This increment
is not task closure, final performance or final-candidate admission.


Maintained source controls now cover the finite final-use increment:
fixtures/run/associated_short_projection_complete_bound.pw passes a concrete
Value plus I64 through generic T.Item parameter/result and prints42; the old
candidate rejected before use, while the new candidate check/run succeeds.
fixtures/reject/associated_short_projection_distinct_instances.pw was wrongly
accepted by the old candidate and now rejects with the intended short-source
ambiguity in check/run. Full proof admission/task closure remains open.
Standard build20261107T204652-build-017d31 passes with unchanged inputs;
fresh candidate bin/plewc-short-projection-bound-context is WIP only.

Fresh candidate target17 and preservation37 now all pass with immutable inputs.
Neutral source/native review accepts only this finite context increment, not
common view proof or the remaining task. Formal current-source gates remain open.

## Authorized Structural-normalization Test Repair

The user authorized correcting associated_condition_normalization_structural
after reviewing its missing Parser premises. Preserve normalization inside
receiver constructors, positional trait inputs and associated output equations
with explicit T:Parser premises and executed selected-method result checks.
The repeated-projection condition moves to an automatically discovered internal
run fixture, associated_condition_normalization_chain: build nested semantic
projection receivers against valid concrete witnesses, record both ordered
normalization equations, validate their proof/receiver/output, replay to Leaf,
require the final Mark conformance and reject the intermediate Next control.
Omitting either saved equation must leave replay unresolved rather than trigger
fresh lookup. This repairs the oracle; it neither adopts chained surface syntax
nor completes common source admission. No product/spec change is authorized by
this test correction. Focused check, AOT execution and lazy-run source companion,
internal native execution and independent review are required.

[Finite verification](../../../evidence/rejection-domains/diagnostic-domain-implementation/structural-normalization-test-repair.json):
both fixtures pass check, AOT compile/link and native empty-output goldens; the
public source companion also passes lazy run. Production normal dispatcher
executes both cases successfully. Final203 inputs match before/after/current.
Neutral review required a stronger missing-equation assertion: both results now
retain a projection and equal the exact expected unresolved term. Review accepted
that repair and independently replayed both saved native binaries successfully.
The initial new internal setup lacked nominal declaration identity; its failure
is not a product RED. Full suite/ASan/common proof-admission closure remains open.

## Nested Conditional-wrapper Controls

The user requested a maintained positive/rejection pair for
Wrap[T#Parser.Output]:Mark when Wrap[U]:Mark itself requires U:Required.
Keep associated_condition_normalization_structural unchanged as its independent
concrete-Wrap control. Add associated_condition_normalization_nested for the
successful conditional path, checking both direct and generic Use method calls.
Add associated_condition_normalization_nested_missing as a rejection fixture:
both Good/Bad satisfy Parser, but only Good.Output satisfies Required. Call the
same requireUse for Good before Bad; require the missing-where diagnostic for
the Bad instance request, not malformed projection/visibility/parser failure.
Current diagnostics point to the requirement declaration rather than the Bad
callsite; these tests do not certify source-location correctness. An isolated Good
companion and direct method calls may be used as diagnostic controls. Test the
selected fixed compiler through check, lazy-run and AOT/native where applicable,
and production normal dispatch; preserve meaningful Source rejection
classification separately from legacy process exit. No compiler/spec change or
common admission completion is implied by adding these controls.

[Executed controls](../../../evidence/rejection-domains/diagnostic-domain-implementation/nested-conditional-wrapper-controls.json):
Good check/lazy/AOT/native succeeds with direct/generic method result checks;
Bad check/lazy refuses with the intended where reason. Adding only
Rejected:Required makes both modes succeed; direct Bad.use also refuses.
All209 inputs remain unchanged. Production run dispatcher passes, but reject
worker reports FAIL(classification=1): its private receipt is unclassified, not
Source. Preserve this failing test and existing com-yeua/com-fsuq responsibility;
do not weaken the oracle or call it GREEN. Neutral review accepts the additional
coverage and independently replays the positive binary; source location remains
a limitation. The existing structural fixture is byte-unchanged from31014653.

## Authored Provenance Producer Prefix (WIP)

Preserve occurrence identity independently from structural type identity before
implementing source proof admission. SourceTypeUses owns only append-only
occurrences and bracketed lexical scope tokens. Each occurrence retains its term,
original site, active token and immutable ParamId-bearing binder snapshot.
Free functions, methods, impls and signatures reserve scope before lowering in
both adapters; requirement/extern origins are distinct and requirements retain
the trait owner. Private cores return Result through a wrapper that restores
parent scope and records Lowered/Failed on all exits. Raw interning creates no
receipt. Zero token is explicitly unowned, never module authority.

This is producer-only provenance, not canonical owner binding, scope authority
or admitted conformance. Lowered means syntax lowering completed only. Existing
ref arrays/visibility consumers remain until the common receipt consumer replaces
them; no correctness claim about their ref cache follows. Unsupported declaration
origins, owner sealing and failed-ancestor authority remain non-authoritative.
Next bind tokens to real function/conformance/raw-signature owners and publish
owned premises, including inherent impl conditions and trait Self, through the
shared proof query. Do not launder raw requirement clauses as implementation
Requirement evidence or arbitrary Conformance pool authority. Then admit exact
views under an explicit lexical environment, retain proofs and migrate final
projection consumers. The existing8 source-admission REDs are still required.

Manual AuthoredTypeUseProvenance tests store bounds/snapshots, same-term distinct
occurrences, original sites in both adapters, impl/member ParamIds and parent
tokens, requirement siblings/Self/trait owner, extern separation, raw interning,
and success/failure restore. First execution assumptions about TypeRef ID equality
and replaying an already registered declaration were test setup errors, not
product REDs. The final native probe succeeds. Static independent review accepts
this finite prefix after value impl/requirement and exact-site test additions.
Task-wide admission remains pending; fresh compiler and formal
fixed-point/performance results follow below. [Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/authored-type-provenance-prefix.json).

### Producer Prefix Fresh Gates and Next Owner Boundary

Compiler c7012d7f passed standard build, fresh provenance native, short17 and preservation37 controls; all recorded inputs remained unchanged. Independent read-only reconciliation accepted those results. The same fifteen source admission probes retain eight invalid acceptances, four valid successes and three intended rejections. Formal run `20261108T000545-self-host-42d9af` reached generation-three LLVM/runtime fixed point, median 6.703740 seconds (7.383906 / 6.703740 / 6.703296). The saved candidate is `bin/plewc-authored-type-provenance-fixed-point`; no adoption or seed promotion. See the linked prefix evidence for hashes and input deltas.

Next, bind receipts to actual registration identities: free/method/extern Function IDs and their exact declared bounds; real conformance identity and owned bounds; a separate inherent-impl owner; canonical trait owner plus requirement slot for raw signatures. Carry signature scope tokens explicitly in the lowering handoff, never by searching anchors or guessing functionCount. Bind raw trait Self to the exact full trait instance; existing translated Requirement evidence is not raw source authority. Origin-specific ownership and premise checks must reject foreign/sibling/rebound/failed scopes. Then admit unused source signatures through the shared solver using rigid explicit lexical terms: the current viewed wrapper's ambient resolveTy is not sufficient. This is the existing finite repair sequence, not a new solver or an additional whole-task dependency.

### Registered Function Identity Prefix (WIP)

Both free-function and method adapters now bind their scope to the actual
registerDeclaredFunc result after owned bounds are appended. Method bounds also
use that result; the prospective index remains only for the existing witness
identity producer. SourceTypeUses preserves the optional function link across
finish and rejects duplicate, foreign-active, completed or wrong-kind binding.
The provenance internal test asserts actual registered identity in both adapters
and checks zero index and those store boundaries. Current-source check, compile,
link and native golden pass with 202 inputs unchanged; independent static review
accepts the identity-preservation prefix. See the same prefix evidence.

This is not premise admission: the shared binding helper checks function range
and store state, not arbitrary foreign function authority or failed ancestors.
Exact owner-premise validation and non-function origins remain mandatory. Fresh
candidate gates for this newer source remain pending; formal 6.703740 seconds
certifies c7012d7f, before this identity increment.

### Explicit Signature Handoff Prefix (WIP)

Both signature adapters now return LoweredSourceSignature { function, scope }.
Extern callers register that exact function then bind its returned token to the
actual registration ID. Extern binding requires completed lowering; free/method
binding still requires the active lowering scope. Failed, premature and duplicate
extern binding is rejected. Raw requirement callers retain the function without
pretending it is registered; requirement-slot binding remains next.

Independent static review accepted the structure and requested the added failed
extern store control. Current-source provenance check/compile/link/native passes
with exact spans and real extern identities in both adapters. Short17 controls
also pass after mechanical signature-return API migration, with expectations
unchanged. The same evidence holds input deltas and the finite setup correction.
No fresh compiler/formal gate for this newer source is claimed.

### Raw Requirement Identity Prefix (WIP)

registerTrait returns its actual appended index. Both trait adapters retain each
signature scope token and, after registration, bind it to that trait index and
requirement slot. The private handoff validates trait/slot range and the actual
requirement span; the store validates origin, completed lowering, canonical
trait owner and single assignment. It does not manufacture a Function owner or
reuse translated Requirement evidence for raw source authority.

Current-source check/compile/link/native passes with 202 inputs unchanged. Both
adapters verify exact sibling slots/owners/spans and absent function identity;
store tests cover unfinished, Failed, foreign owner and duplicate binding, and
unregistered raw signatures remain unbound. Independent static review accepted
this finite identity increment. Premise authority, trait Self, failed ancestors,
impl origins, common admission/proofs/consumers and fresh candidate gates remain
uncompleted. See the same prefix evidence; formal6.703740 is earlier c7012d7f.

### Registered Owner Fresh Candidate and Admission Sequence

Source 4f6505d1 passed standard build `20261108T003517-build-f606f8`. Saved
candidate `bin/plewc-authored-scope-owners` passed provenance native, short17 and
preservation37; all recorded inputs remained unchanged. The source admission15
probe still has the same eight invalid acceptances, valid4 and reject3. Formal
6.703740 remains the earlier c7012d7f result, not a performance certification of
this newer owner-binding source. Full suite and task completion remain open.

Independent design review permits closing unused free-signature admission before
remaining non-function migration. First retain explicit signature occurrence
roles/IDs: a FreeFunction token currently also owns body and default-expression
uses, which must not be eagerly admitted as unused signature work. Then make
shared query output normalization explicit: conditional associated predicates
currently reach selectedProofAssociatedTypesMatch -> typesCompatible ->
normalizedValueType -> ambient groundTypeRef/cur.checkFn. A direct rigid query
entry alone does not remove that dependency. Preserve extension/view state,
validate original owner/ParamIds and premise roots, retain only Found proofs per
receipt, and test ambient/default/body noninterference. This changes the finite
implementation order, not the scope or language contract. Non-function origins
and final proof-based consumers remain mandatory, without unchecked exemptions.

The reviewed impl follow-up uses a common source owner record with explicit
Nominal/TraitSubject receiver, actual conformance index only where registered,
full span/module, binders, clauses and extension identity. Inherent impls must
not acquire fake Func/Conform identities. Clause-pool sharing does not confer
Conformance authority; repeated AST lowering is still to be removed.

### Occurrence Demand Role Prefix (WIP)

Authored occurrences now retain Declaration, DefaultArgument, Body or Unowned.
The active role is scope-local lowering scratch; each immutable receipt snapshots
its role. Child scopes start as declarations and finishing either exit restores
the parent's frame. Shared value/syntax default lowering restores the caller role
on both Results. Actual free/method body entries set Body, then restore Declaration
for subsequent bounds. Unowned origins remain Unowned. This adds no source proof
or implicit permission to inspect a body.

AuthoredTypeUseRoles covers nested/Failed frame restoration, immutable snapshots,
invalid role changes and exact source sites for both adapters' free/method
parameter/result/default/body boundaries plus declaration where clauses. Together
with provenance, check/compile/link/native2 pass with 204 inputs unchanged.
Independent review reconciled hashes/results and replayed both natives. See the
same prefix evidence. Fresh candidate gates for this newer source remain pending.
Deinit/closure/field default and individual deferred generator/body identities
remain outside this finite producer acceptance; roles alone are not request-owner
identity. Next, use Declaration receipts for unused free signatures only, under
the reviewed explicit-normalization query contract.

## Explicit Query Premises and Declaration Readers (WIP)

[Finite evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/rigid-trait-query-environment.json)
records direct/conditional query REDs: unrelated current body substitutions
changed associated-type equality. The query now uses structural type equality
and projection closure under explicit premises, not value conversion or ambient
body normalization. Canonical declaration scopes supply premises to retained
call/conversion/static/conditional readers; interface contract admission forwards
its own premises. Actual generic-call and boxing controls exposed a missing
reader handoff during the repair; both are preserved as additions and repaired.
Fresh candidate `plewc-authored-rigid-query` passes nine query/boundary cases and
eight affected retained-evidence fixtures, with invariant inputs. Build run
`20261108T011356-build-ee83dd` passed. Independent review replayed the saved nine
native controls. Formal current-source performance is still pending.

This is not final proof-interpretation closure: unmatched associated terms can
still trigger an explicit-premise Existence query. Saved-equation-only readers
and occurrence-specific view admission/final consumption remain required here.
Original source admission's eight invalid acceptances are not repaired by this
increment. Universal interface replay's omitted premise arrays are a static
concern, not a confirmed supported-source regression: hidden nominal witnesses
are an existing rejection boundary, and the supported sibling projection is
reified earlier. Preserve the concern for the retained-proof consumer audit;
do not claim a product RED from an unsupported setup. API narrowing stays with
com-pmiz/com-oir7, and zero/missing output distinction with com-nei5.

### Next Finite Signature Handoff

Independent design review confirms unused free-signature admission can precede
all nonfunction owners, but signature slots must retain receipt identity at
lowering. Add a source-signature artifact keyed by the actual registered
function: parameter slots in actual order, explicit result slot, and the separate
Declaration receipt list. Type lowering returns the root receipt explicitly;
synthetic types have no receipt. Do not recover it by term, spelling or location.
A saved reader takes function + slot + explicit environment, validates that
slot's receipt/scope/proof, and interprets the retained proof. A later migrated
call/body consumer must not fall back to groundTermForBody's source re-query.

Nested semantic child paths also need receipt links before nested projection
consumption is certified. Root-only reader guarantees do not waive nested source
admission. Test both adapters' parameter/result order, repeated identical terms,
foreign owner/slot swaps, missing proof, scope exit, and exclusion of default/body
roles. Reuse admitted callable constraints and InstanceEnvironment for proof
instantiation. This is a concrete handoff within this task, not a new solver or
a claim that provenance alone admits the eight remaining invalid sources.

The first formal run `20261108T012121-self-host-ececa5` failed in generation2:
the new premise projector erroneously required a function for a canonical
global-initializer scope. A new `globalBoundary` addition reproduces that exact
conversion refusal; it passes after preserving the existing no-function empty
premise scope. Owner/proof dependency admission is unchanged. Local ten native
cases pass, with invariant inputs and independent static review; these do not
replace final fresh gates. Re-run `20261108T012910-self-host-f609cd` is pending.
The earlier 17-case fresh result predates this global-scope repair.

Final finite gate: `20261108T012910-self-host-f609cd` passes with gen2==gen3
LLVM/runtime; samples7.301216/6.912851/6.839355, median6.912851 seconds.
Candidate `plewc-authored-rigid-query-fixed-point` SHA
`994a1ef814bbb0b805ad67f74194a79f2d28f67f40a89a5bb13cd4b3eca217da`
passes final ten query/boundary controls plus eight existing fixtures; inputs
are invariant. Independent review reconciles all hashes/goldens, 175 source
files at048188e1, and the formal median. No main/carrier/seed promotion.
Original15 source cases on this candidate still show eight invalid acceptances,
four valid accepts and three valid rejections. This retained RED is the next
signature-admission implementation baseline, not a completed task.

### Free-Signature Admission Increment (WIP)

[Saved RED/GREEN and independent review](../../../evidence/rejection-domains/diagnostic-domain-implementation/authored-signature-admission.json)
cover explicit PType root receipts through Param and actual free-function slots,
Declaration-only occurrence lists, exact lexical-instance SourceAdmission, and
private publication only after the whole signature succeeds. The root reader
consumes the exact occurrence's retained proof with explicit substitution and
prepared callable constraints, without discovering missing source evidence.
Both free-function lowering adapters retain distinct occurrences for repeated
identical parameter/result terms. Default/body roles are excluded from this
signature admission; they remain mandatory follow-up owners.

Fresh candidate after build `20261108T022115-build-8512b9` passes the original
15 source controls (all eight erroneous acceptances now reject), 19 internal
signature controls, ten query controls and eight retained-evidence fixtures.
The three additive public fixtures pass check, lazy execution, AOT/native and
the production normal/reject dispatcher, including Source failure classification.
These are finite gates, not full suite or task completion.

Preservation testing finds one real new regression: `QualifiedTypePathEdges`
`precedingTrait` (`S#Q#P[I64].Item`) is rejected because admission mixed the
receiver's view selector with the projection's separately stored trait instance.
The remaining38 of39 preservation cases pass. Preserve the existing oracle:
spec09 distinguishes a view type from a projection, and the semantic projection
retains receiver plus its own complete trait instance. Independent review
confirms the distinction. The source repair counts only receiver selectors for
the view normal form, preserves `S#Q` in P's query, and makes the root reader
interpret receiver-view proofs before projection output. A new generic
`receiverTrait` control plus the old failing case and previous19 controls pass
locally (21 total). Build `20261108T023302-build-bd9d20` passed with
invariant inputs. Its fresh candidate passes the strengthened21 controls,
all39 preservation cases and all public companion modes/dispatchers. The
Q-only missing/P-retained control fails the isolated reader-loop-omission
mutation and succeeds unchanged with the repaired reader; independent review
reconciles both, without calling the mutation an old-product RED.

Formal run `20261108T024119-self-host-85aa7a` passes with gen2==gen3
LLVM/runtime. Samples7.306906/6.881155/6.834871 give median6.881155 seconds.
Saved candidate `plewc-authored-signature-fixed-point` SHA
`3b07b06b908b5fc06a96842c6568e5c6ab62f402b3f44bf17bf09f3733374c44`
is a WIP checkpoint, not the adopted carrier. The fixed-point candidate passes
21 internal controls and all public companion modes/dispatchers with invariant
inputs. Independent formal reconciliation verifies all6400 inputs, source
revision, actual gen2/gen3 output hashes, saved candidate and formal median.

Nested child-to-occurrence paths, production call/body consumer migration,
non-free owners, and saved-only interpretation of all frozen associated predicates
remain required. Known Unit versus missing output remains com-nei5; the root
reader is not certified for that boundary. No task closure, seed/carrier
promotion or main integration is claimed.

### Next: Explicit Nested Type Recipes

Independent implementation-design review derives the next handoff from existing
contracts: each authored root retains canonical semantic-child edges selected
while lowering both adapters. Authored nodes carry occurrence receipts; derived
structural nodes carry term, children and origin, without invented source
admission authority. Never reverse-search a receipt by term, spelling or site.

Projection children are receiver first and complete trait arguments thereafter.
Preserve source argument edges inside synthesized receivers; shorthand arguments
retain selected-bound origin. Carry recipe edges through selector normalization
and retain all original Declaration occurrences despite deduplication. Validate
edge count, target term and labels against the common semantic visitor before
publication; equality validates an already-selected edge, never chooses one.

First save/replay recipes for nominal, record, function, view and projection
children in both adapters. Then replace the root-only proof reader recursively
and migrate selected free-call parameter/result plus body-signature consumers;
remove their term-only query fallback. Caller replacements and proof-produced
outputs are derived results, not callee recipe children to substitute again.

Controls: nested siblings, repeated same-term occurrences, record order,
function parameter/result, projection receiver arguments, nested selector
arguments and shorthand bound-derived arguments; reject missing/foreign/swapped
edges and absent proofs without downstream source rediscovery. This is within
the existing task; no new spec rule or task decomposition is adopted.

`AuthoredNestedSignature.pw` is the first next-reader RED: a justified
`Box[T#Project[I64].Item]` signature, instantiated with Source whose retained
Project[I64] output is I64, must read as Box[I64]. The current root-only reader
leaves the nested output unresolved. Fixed-point candidate compiles/links the
harness successfully, then the native equality assertion alone exits134;
inputs are invariant. This is a manual internal pending-RED fixture, not a
new specification failure or an automatically green suite case. The source
recipe producer implementation is WIP; the recursive reader is not yet connected.

### Nested Recipe Producer WIP and Bound-Origin RED

[Producer controls and independent findings](../../../evidence/rejection-domains/diagnostic-domain-implementation/authored-type-recipes.json)
record the current source work: immutable recipe nodes, explicit child edges
through both PType adapters, record ordering, parallel view argument recipes,
projection receiver/arguments, and direct canonical child checks. Local21 controls
pass at the checked-prefix revision; subsequent strict missing-edge refusal and
Unit-origin linkage require fresh validation. No new candidate or performance
gate is claimed for this WIP; nested reader/production consumers remain open.

Independent review confirms a pre-existing source-bound lowering responsibility
problem exposed by recipe identity: unique*ProjectionSourceCore re-lowers the
where AST at each use. Returning those new recipes is not forwarding the original
bound occurrence. `AuthoredProjectionBoundOrigin.pw` compiles/links successfully
and fails only the intended assertion: the where argument acquires Body role
when a body uses T.Item. Its source position alone cannot restore its owner.
This is within this task's exact lexical-origin requirement, not a new spec rule.

Repair before consumer migration: reserve stable clause IDs in the original
owner context, retain original ParamIds and syntax descriptors, materialize
candidate arguments only after owner/member filtering, and complete owner clauses
in Declaration role before parameter/default/result lowering. Repeated short
uses and FuncBound publication must consume the same prepared subject/constraint/
argument recipes. Impl clauses retain impl scope and are inherited by method IDs;
member clauses remain separate. Raw requirements do not acquire function identity.
Preserve the shared32-request Limit contract, Failed diagnostic retention and
Err restoration; do not impersonate another owner by switching cur. Declaration
validation may move earlier, so compare actual diagnostic ordering.

Required additions: both adapters' repeated left/right/result/body/default;
shared impl conditions across methods and separate member conditions;
later-clause dependence, existing nonmember filtering and recursive Limit;
failed-context/depth/role restoration; legacy rich-field omission and concatenated
impl/member clause identity. The evidence record holds the detailed review.

### Free Bound Preparation Checkpoint (WIP)

[Finite evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/authored-free-bound-context.json)
records original-clause reservation and once-only Declaration preparation for
both free-function adapters. Short selection and FuncBound publication consume
the same Ready canonical source and original argument recipes. Failed requests
restore lexical state; an empty context masks stale legacy arrays. Generated
declarations run after the originating frame has been restored. Legacy name-only
subjects do not acquire fictitious source occurrences.

Fresh build `20261108T033925-build-5cad03` passes with invariant inputs.
`plewc-authored-bound-context` passes8 bound-context controls,21 signature
controls,39 preservation controls and public check/run/AOT/native/dispatcher
companions. Independent review accepts source structure and fresh8/21/public;
preservation/gen differential and fixed-point fresh results are also independently reconciled. A diagnostic-runner
key collision overwrote the no-argument result with the literal default case;
the fresh8 run uses distinct keys and retains all planned cases.

Standard gen fails26/rejects5 for both old and new candidates with byte-identical
stdout/stderr; this is not gen GREEN. Initial formal run03abe5 failed at an
Optional local inference difference in the adopted carrier. Explicit Optional[U64]
annotations in both wrappers repair carrier acceptance without changing semantics.
Formal run59de22 for a49e6524 passes at generation3 with invariant inputs:
7.472470/6.934775/6.918589 seconds, median6.934775. Saved fixed-point candidate
SHAa6954297 passes final8/21/public; independent reviews reconcile all6408
formal inputs, actual artifacts, source, median, candidate and final focused cases.
The existing nested-reader harness still compiles/links then fails only its
expected retained-output assertion (native134). This checkpoint does not close inherited impl/member clauses,
raw requirements/extern owners, recursive recipe validation, nested saved-proof
reader, production consumers, saved-only predicate interpretation or the two
original graph/equality fixture repairs. Continue those existing obligations;
no whole-task completion, main integration or seed/carrier promotion.

### Recursive Recipe Admission WIP

[REDs and independent findings](../../../evidence/rejection-domains/diagnostic-domain-implementation/authored-recipe-admission.json)
track canonical child/label/term checks, exact authored backlinks and owner/binder
validation. Derived tags alone do not establish authority: three actual REDs
require parent-constructor position checks, including before memo hits. Another
actual RED hides an inner projection in a synthetic receiver; require an authored
occurrence/proof for that inner projection. Unit mapping is valid only on the
function result edge and must retain its authored Unit source. The newly added
internal positive fixture was corrected to that real constructor position;
ordinary Box placement remains an explicit rejection case.

Legacy BoundSelection without retained original clause/binder provenance is not
admitted by this free-signature gate. The mandatory non-free/inherited-owner
migration must supply original recipes before connecting its admission path;
this restriction is not whole-producer completion. Build55ae26 and fresh14/21/8,
public modes/dispatchers and whole compiler source --check pass with invariant
inputs. Independent review reconciles the current free gate, exact case sets,
all input maps and candidate SHA27187aad. Latest-source formal performance is
unmeasured; previous6.934775 seconds certifies a49e6524 only. The fresh candidate
reconfirms the existing nested-reader RED: compile/link0 then expected native134.
Continue nested retained-proof consumption and production handoffs after this
finite gate; do not close the task from validator success.

### Recursive Free-signature Recipe Reader (WIP)

[RED/GREEN controls and independent findings](../../../evidence/rejection-domains/diagnostic-domain-implementation/authored-recursive-reader.json)
retain the reader increment. The exact slot now traverses saved canonical child
recipes with a per-signature/environment memo. Each Authored occurrence selects
its own saved complete selector; folded children instantiate that selection.
Source-constructor selectors remain separate from caller-added views. Shared
head lookup does not traverse a replacement; caller replacements and associated
outputs are not fed through the callee recipe again. Grounding retains its
previous direct Self/Item replacement behavior, guarded by an actual crash RED
and repaired control.

The first seven cases failed their intended assertions before the reader change.
The additional result/once/receiver-view/selector-argument/receiver-argument
cases are GREEN controls, not invented REDs. Final candidate passes nested14,
prior signature21, integrity14, bound8, public check/lazy/AOT/native/dispatcher,
whole compiler source check, and the two existing explicit-grounding fixtures;
all recorded inputs are invariant. Full suites, performance and whole-task
completion are not implied by these focused results.

**Next required boundary:** the reader itself does not query, but shared
`instantiateConstraintProof -> instantiateConcreteConstraintProof` still calls
`groundTermForBody` on original bound arguments/predicates, which can reach an
Existence query. Nested argument GREEN does not prove saved-only replay. Remove
that competing interpretation in the common retained-evidence frontier, preserve
exact clause/environment identity and saved normalization, and add a missing
nested-normalization control that cannot be rescued by existing conformance.
Do not add a reader-specific solver or simply skip validation. Proof-output
once-only coverage and production free-call/body signature consumers then remain
required, alongside all non-free owner migrations already listed above. This
increment and com-amjl/met-si6j remain open.

### Prepared Callable Bound Snapshots (WIP)

[Controls and retained handoff](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-callable-bound-snapshots.json)
record the common Function/Requirement reader migration. Preparation forwards
the same full expected `TraitBound` that was validated, alongside its exact
`DeclarationBoundRef` and frozen proof. An immutable publication environment
retains ParamIds/arguments, receiver and provided-proof context, without a
recursive constraints link. One row owns each source/bound/proof tuple; the
previous parallel source/proof-only publication is removed.

Consumption checks the originating environment, canonical source/function
ownership, exact clause, receiver and the complete saved proof boundary. It
returns the same frozen proof, without the former original-bound argument/
predicate preflight or receiver-repair fallback. Instance equality includes
both the originating context and saved complete obligations. Requirement
ownership remains the original implementation, not a provided placement.
Newtype's existing explicit target re-admission issues a fresh snapshot.

The initial stale-argument/receiver/proof-context controls were actual REDs;
valid and missing-set controls were already correct. Additional internal raw
snapshot cases cover owner/clause/duplicate/empty, wrong full inputs/predicates,
Deferred preservation for missing normalization, proof identity and cache
identity. The prepared-empty sentinel still has no owner/environment and cannot
authorize a clause. Raw Arena issuance is trusted internal storage, not source
admission authority; see the publication-boundary reconciliation below.
com-oir7 owns only view-check API narrowing, not blanket issuer sealing.

This removes the Function/Requirement source-bound preflight, not every query
in the shared proof graph. Conformance/Associated/Receiver paths, deeper frozen
witness normalization and predicate comparison, occurrence/owner migrations and
production source-signature consumers remain mandatory. The snapshot does not
make a fresh query into an acceptable repair for missing retained evidence.


### Retained Conformance Clause Replay (WIP)

The Conformance consumer now dispatches before caller-side original-bound
preflight. It receives only the exact declaration clause, requested subject and
selected witness. A shared interpreter substitutes the original impl clause
through that witness once and replays its retained normalization equations.
Whole-plan admission and individual clause reading share the same full proof
boundary checks, including proof-side normalization; the existing whole-plan
validation is preserved. The reader checks source range, plan substitution,
child identity, complete expected constraint and requested clause subject.
Missing equations cannot be repaired into Ready by a new conformance query.
Admission cycles are rejected and stack state is restored on every result.

[Finite evidence and independent review](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-conformance-clauses.json)
retain four actual old-source REDs (missing equations, wrong proof/subject,
and missing caller map), two existing GREEN controls, and nine final controls.
The added foreign-map/substitution/cycle controls are GREEN checks, not claimed
old-source REDs. Malformed evidence requires Err; missing normalization remains
non-Ready. All controls also perform a valid recovery read and exact-proof check.

The root/path is already admitted by the existing caller protocol; this reader
does not certify raw publication sealing or revalidate unrelated sibling clauses
on every read. Deep predicate normalization fallback, Associated/Receiver replay,
non-free declaration ownership, production signature consumers, Unit distinction
and final whole-task gates remain open. This finite handoff does not close
com-amjl or met-si6j.


The first isolated fixed-point measurement for this increment (5770c323,
run9ded4c) is 7.109542 seconds, above the7-second condition. A local follow-up
changes witness constraint grounding to accept the existing PatternBindInput;
its two callers pass their original Conformance range directly instead of
copying Bind arrays. This preserves binder identity/order and all checks. The
same-source diagnostic (three pairs with reversed order) shows identical output
but no demonstrated speedup. It is not a formal performance result. Fresh9/10/14
controls pass. The isolated formal follow-up (ae19e30b, run64fe3c) reached
generation3 fixed point, but samples7.521118/7.553853/6.958024 gave median
7.521118 seconds. The7-second gate remained unmet at that checkpoint. A same-latest-source comparison
of the pre-increment, first-increment and range-followup fixed-point compilers
produced identical LLVM in all9 runs; timing varied and does not establish a
reliable cause or an improvement. Do not label the regression unavoidable or
the copy-removal successful. Local copy removal has not restored the gate. That single unsuccessful
change does not establish that repair is difficult: the prior stop decision
is withdrawn as premature. Investigate measurement variation and dominant cost
with the7-second condition unchanged, before returning to saved predicate replay.
No task completion, main integration, seed or carrier promotion follows.


The stop was withdrawn as premature: one ineffective local change does not
establish difficult repair. A balanced same-source comparison (5 samples for
each of the3 fixed-point compilers) gives6.895844/6.882198/6.875783 seconds,
with all15 LLVM outputs equal. Old slow samples concentrate their extra time
before the first load:start event is received or between write events; these
are parent observation times and do not isolate an OS cause. They do not
establish a persistent Conformance regression.

Formal recheck67e957 reaches generation3 fixed point with the same compiler
artifact c080052..., samples7.586391/6.940820/6.898564 and median6.940820,
below7 seconds. Product source is unchanged from ae19e30b. The old failed
performance measurements remain evidence; the new formal result is not a
substitution of diagnostic timing. Resume the saved-predicate handoff described
above; no whole-task closure or carrier promotion follows.


### Saved Associated Predicate Normalization (WIP)

[Initial RED/GREEN and candidate](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-predicate-normalizations.json)
record the next finite handoff. A pure retained comparator reads selected
associated outputs, replays saved equations and checks structural equality;
it has no query or assumptions. Selection owns a recording adapter and
Conformance's producer retains required actual-output equations after Found,
before freezing its condition plan. Whole-plan/requested-clause validation
share the pure comparator. Existing callable/boxing query adapters remain
until their own saved transport migrates.

Saved replay now folds canonical type children and rebuilds through the same
term API as source recipes, including view selector arguments, before applying
an equation to a projection head. The visitor control is distinct from source
view admission. Three actual old-source REDs and one existing GREEN control
become GREEN. A subsequent mixed-predicate RED detects unnecessary equation
acquisition for an already-equal predicate; it is a structural non-interference
failure, not a demonstrated language-output error. Pure term-pair comparison
is shared by the retained matcher and recording adapter, and only mismatching
pairs acquire evidence; final whole-predicate replay still validates the result.

The final build candidate passes14 normalization controls plus2 acquisition
controls,10 preserved calls/newtype fixtures,14 existing once/binder readers plus
structural/chain fixtures,25 prior Conformance/callable snapshot controls,
public check/lazy/AOT/native/dispatcher, and the compiler's whole source check.
All inputs remain invariant. The normalization controls cover actual-only nested
and view-containing production plans, missing equations, malformed prerequisite/
receiver/trait arguments/output, reachable raw cycles versus plan admission,
symbolic equality, missing output, and recovery/proof identity/stack cleanup.
These are finite guarantees. Formal run `20261108T154849-self-host-0d7495`
reaches generation3 LLVM/runtime/compiler fixed point with6418 invariant inputs;
its median is7.029968 seconds (samples7.582913/7.029968/6.976340).
The measured fixed-point candidate passes the final16/public gates. Independent
read-only reconciliation accepted formal artifacts, source and final gates.
A balanced same-source five-run comparison gives before7.066202/after7.054865
seconds, invariant inputs and identical LLVM across all ten runs. This does not
replace the formal median or establish difficult repair; continue the required
transport work while keeping the overall performance condition open.
Whole-task obligations remain; do not call com-amjl or met-si6j closed.

### Saved Projection Prerequisite Replay (WIP)

[Finite RED/GREEN and preservation evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-projection-prerequisites.json)
records the shared prerequisite frontier. `replayConstraintProof` no longer
routes projection uses to fresh MemberDispatch queries. Projection prerequisites
and condition children use the same exact declaration-evidence reader after the
unchanged interface scope/Universal interpretation.

The internal handoff test first admits one equation in its original Function
binder domain, then replays it under an explicit prepared environment. It is not
a claim that the entire parent witness plan came from the production producer.
The corrected old-source RED has valid compile/link, a passing prepared-context
control, and only the missing-context assertion fails. The initial mismatched
source/proof setup is excluded from authoritative RED evidence. Final controls
check exact retained proof, concrete source/output, rejection without repair,
recovery and admission-stack restoration. This source change has no new formal
self-host result; previous7.029968 seconds applies only to the previous source.
Whole-task transport, performance and suite gates remain open.

**Next: selected Associated clause transport.** `checkAssociatedBounds` already
checks the impl-translated full subject/constraint, but publishes only clause and
proof. Preserve that full impl-owned bound and its normalization dependencies
(including actual child outputs) before replacing the reader. The source
`AssociatedBoundEvidence` retains the authored projection/clause/prerequisite;
the conformance-owned row retains its implementation derivation. They are not
interchangeable owners. Read the exact row from the selected prerequisite's
terminal conformance, validate original trait instance/member/clause, substitute
impl terms once, replay saved prerequisite/child equations through this shared
frontier, and check the complete subject/arguments/predicates without caller-side
`groundCallableBound` or query-capable boundary rescue. Share equation grounding
with witness replay instead of implementing another normalizer.

Remove AssociatedType's generic caller argument/predicate preflight only when
its saved transport replaces that authority. Nested projection receivers need
retained dependencies too; structural substitution alone is not proof that they
are concrete. Preserve legitimate first-concrete SourceAdmission and universal
interface restrictions. Required controls include nested/actual-output equation
loss, caller/impl binder distinction and once-only replacement, foreign owner/
trait instance/member/subject/proof/equation, missing/duplicate row, cycles,
Deferred versus concrete missing evidence, recovery and existing source usage.
The independent read-only design review accepted this boundary and distinguished
it from all-owner migration; it did not certify its implementation.


### Associated Clause Producer Snapshot (WIP)

[Saved representation and fresh validation](../../../evidence/rejection-domains/diagnostic-domain-implementation/associated-clause-snapshots.json)
record the unchanged three-control baseline, fresh77 native cases, public modes/
AOT/dispatcher and compiler source check. Build `20261108T164217-build-4f6770`
and fresh results have invariant inputs and independently reconciled current
source/test/golden/runner/candidate hashes. No new formal timing is claimed.

The conformance-owned associated row now retains the full **pre-normalization**
impl-translated `TraitBound`, original trait clause ID, selected proof and saved
normalizations. SourceAdmission still receives exactly the former subject and
constraint; recording happens only after that selection. Expected subject,
positional arguments and predicates are recorded under exact conformance
assumptions, with only mismatching actual-output terms acquired by the shared
recorder. Equations and the complete pure boundary are checked before publication.
The old proof API remains a compatibility reader of the new row; the associated
consumer is deliberately not yet migrated.

This is a representation refactor with preserved GREEN controls and snapshot
assertions, not an invented old-source RED. An attempted direct private-helper
probe failed visibility at compile time and is not evidence of a product bug.
`RetainedAssociatedClauses` covers closed, generic, nested and actual-output-only
obligations, original impl ParamIds, complete raw arguments/predicates, exact
proof identity, equation-loss rejection by the existing pure comparator and
recovery. Its nested selected child has no own condition plan but does have a
projection in its binding, explicitly preserving the next reader dependency.
The source fixture's empty/absent publication check is a local control, not a
claim that every raw issuer is sealed. Storage immutability and source-success
publication are separate guarantees; see the reconciliation below.

The next consumer increment must share equation instantiation/prerequisite
replay with witness replay. Ground source/output simultaneously once in the
selected impl environment. Pass that validated context to child bindings and
Self as well as to the expected bound; `replaySelectedWitness` currently queries
through `groundTermForBody` before processing its own plan, so merely changing
the expected-bound check is insufficient. An unconditional child (`conditions=0`)
must still consume its outer associated-row equations. Compose only the explicit
row/child contexts with their owners; do not search arena-wide equations, reapply
the caller map to replaced terms, or introduce another solver. Missing context
cannot fall back to query rescue. Existing scoped interface interpretation and
legitimate first-concrete admission remain separate.

### Shared Saved Equation Context (WIP)

[RED/GREEN and preservation evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-proof-equation-contexts.json)
tracks the shared reader required by the Associated row migration. Witness binds
and Self now cross one simultaneous substitution frontier and consume explicit
saved equations before closedness checks. Equation replay normalizes canonical
source children before interpreting its prerequisite, compares the substituted
saved output against that proof's raw output through the same context, and keeps
the immediate derivation. Inherited contexts are not substituted again. A
separate active-plan stack rejects recursive replay and is restored on every
Result path. Unconditional children retain context when later associated-output
reads still need it; raw output derivation and semantic output replay remain
separate APIs.

The original child-only missing-context REDs and the Wrapper[T] -> T equation
substitution RED are covered. Making the reader pure exposed an existing
producer dependency: authored recipes returned their child terms without their
proof equations. They now fold only canonical child contexts, transfer the exact
selected proof's output dependencies, and retain immediate projection derivations
alongside terms in the memo. The unchanged receiverArgument oracle and the new
proofOutputDependency RED both pass. No source re-query repairs absent context.

The internal viewPlanMissing mutation used to remove only an outer equation
copy. Its selected child still owns valid output equations, which the semantic
reader can now legitimately use. The positive viewChildContext preserves that
case; the negative control removes the dependency at both reachable owners and
continues to require individual and whole-plan rejection. Other malformed and
missing-proof assertions are retained. This is an internal fixture correction,
not a specification change or permission to recover missing evidence by query.

Final build `20261108T173903-build-b00e5b` and candidate
`bin/plewc-retained-recipe-proof-contexts` pass57 nested/retained controls,
17 predicate/acquisition controls,20 public native fixtures, the authored-signature
check/lazy/AOT/dispatcher controls and compiler source check with invariant inputs.
The additional public mixed-path fixture fails equally on the old producer
candidate; its invalid source-range premise is already owned by com-wfq2. This
is not an all-green public suite. Independent source and fixture reviews accept
these finite handoffs; final evidence reconciliation is recorded in the linked
artifact rather than inferred from case counts.

**Next remains the Associated row consumer.** Its integration control still
fails because the old reader does not pass the saved row equations into the
child proof. Wire the shared reader to the exact impl-owned row, validate the
original clause/owner/trait instance/full expected bound, and remove caller-bound
query grounding. Keep scoped interface interpretation and legitimate first
concrete admission. Receiver and the other previously listed producer-to-final-
consumer migrations, whole-task gates and performance remain open. No formal
self-host result applies to this source; do not reuse ce5eb536's7.029968 seconds
as its timing or infer repair difficulty from that earlier threshold crossing.

### Associated Row Reader WIP and Task-Ownership Stop

The static associated reader now consumes the exact selected impl-owned row,
substitutes its full bound/equations once and uses the shared saved-only proof
frontier. Original clause/member/trait-instance checks, table count/presence,
translation-invariant row shape, complete child boundary and requested subject
are validated. Caller-side bound re-grounding/query rescue is removed. Static
and interface entries share projection-child replay; only an explicit Universal
context permits symbolic terms. No runtime Universal path is claimed verified.

[Current WIP evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-associated-row-reader.json)
retains the prior integration RED, build `20261108T180709-build-146ca9`, fresh18
row controls, preserved57/17 controls and compiler source check. Malformed
row/source controls require Err; missingEquation alone permits nonReady. Valid
clone is an internal retained-reader setup control, not a new SourceAdmission
success. The existing21 public controls have20 native successes and the same
mixed-path failure owned by com-wfq2. Two added interface probes fail on both
old and fresh candidates before this reader, at requirement/source admission;
keep them as pending producer-to-consumer cases inside this issue, not as
Universal execution coverage or successful regression tests. Full non-free/
interface producer admission and whole-task gates remain required.

**Stop condition: task-ownership inconsistency.** Earlier sections assign raw
Arena/proof/table issuance sealing to com-oir7. That assignment is incorrect:
com-oir7's actual finite scope is `checkTypeViewSources` API authority narrowing,
as this issue itself correctly states above. com-pmiz owns selected associated
query adapters, and com-j2i7 includes proof freeze/thaw adapter narrowing; neither
establishes that the whole raw table issuer boundary has an accepted sealing
owner. Do not treat the previous cross-reference as proof of an assigned task.
The new reader trusts producer-admitted immutable rows; it does not reject every
self-consistent forged raw row. That trust boundary must not silently become a
claim that another task will seal it.

No new task/dependency or mandatory scope expansion is adopted at this stop.
First reconcile the actual design guarantee and existing task scopes: determine
whether raw issuance is intentionally trusted internal construction, a required
restricted publication boundary owned here, or separately necessary work. Then
correct the erroneous references/acceptance claims and resume implementation.
This stop is a planning-record issue, not a proven language defect or a claim
that self-compilation performance is unrepairable. No fresh formal timing,
main/seed promotion or whole-task completion is claimed.

### Publication Boundary Reconciliation

The user authorized correcting the ownership record and resuming the bounded
implementation, without automatically requiring blanket raw-factory sealing.
Reconciliation uses product source at `a3fdb140`; this is a structural inspection,
not a new execution gate or proof that all source admission is complete.

[Checked-body storage](../design/checked-body-storage.md#adopted-choice-and-decision-boundary)
requires the source-operation Building writer to be private and Prepared
publication to follow successful owner admission. It does not turn every
append-only proof/binding allocator into a source-success capability.
[com-wqa0](com-wqa0.md#operation-and-constraint-api-reconciliation) already
records this distinction; the current paths below independently confirm it.

| Boundary | Actual production path and guarantee | Responsibility |
| --- | --- | --- |
| Source-operation success | `Check/CallConstraints.pw`: private admission creates the exact `AdmittedCallConstraints`; private publication constructs `PreparedCallConstraints`. `Resolve/Preparation.pw` finishes fallible body/global checks before publishing. `Resolve/Record.pw` and `Resolve/Global.pw` record the result through `finishSourceFacts`; the private Building store rejects completed owners. | Existing com-wqa0 source-operation guarantee; new authored projection admission remains com-amjl, not waived by that closed task. |
| Callable instance binding | `Check/Bounds.pw`: `environmentWithCallableConstraints` checks Declaration/Recorded/Requirement evidence; `instantiateRequirementCallConstraints` checks exact public substitution and proof boundary before Arena binding. `Ir/InstanceConstraints.pw` appends immutable bindings and strips recursive constraints from their saved environment. `PreparedCallableConstraints` is not `PreparedCallConstraints`. | com-amjl owns saved-evidence correctness along its producer/reader paths; com-nhtx owns the exact callable/environment API narrowing. Raw allocation is not source-success authority. |
| Conformance associated rows | Sole production `publishConformanceAssociatedEvidence` caller is `Check/Bounds.pw`: SourceAdmission selection, normalization validation and complete retained-witness boundary precede publication. `Ir/DeclarationConstraints.pw` rejects a second table, including after an empty first table. | com-amjl's associated producer-to-reader guarantee, including pending interface cases. No blanket sealing dependency inferred. |
| Conformance method / supertrait rows | Sole production writers are `Check/Bounds.pw`, after requirement/implementation or supertrait checks and proof freezing. Arena method and supertrait stores reject replacement; they are not body-owner readiness. | Preserve declaration evidence guarantees; this inspection does not certify all declaration paths or broaden com-amjl into every API group. |
| Associated assumptions / witness plans | `Mono/Resolve.pw` deduplicates associated assumptions; callers are projected facts, interface assumptions and interface rebasing. Witness plans are appended in selected/replayed witness paths. These immutable records can exist during checking and are not successful source-owner receipts. | com-amjl must validate exact prerequisite, scope and retained proof at actual consumers. com-pmiz/com-j2i7 retain their finite adapter scopes; neither is assigned all raw issuance. |

Raw storage may retain an immutable prefix when a later semantic operation
fails. Such a prefix must not authorize source success or repair absent saved
evidence. Internal malformed-row tests deliberately use low-level construction;
their rejection controls do not establish that arbitrary internal callers cannot
forge a self-consistent row. Conversely, that testing facility alone is not an
observed source-language bypass or evidence that every allocator must be sealed.

The erroneous com-oir7 attributions above are corrected. No new issue or real
dependency is needed for that correction; existing required com-amjl production
admission/consumer work stays open. The previous stop is resolved for resumption,
not for task closure. Next: use the two saved failing interface probes to repair
the first failing declaration/admission owner, then verify retained rows through
their actual interface consumer. Do not count either pre-reader failure as a
reader RED, Universal execution coverage, or a completed producer-to-consumer
guarantee.

Independent read-only review `publication_boundary_reconciliation_review`
accepted this documentation increment against `a3fdb140` plus the document
diff. It independently checked checked-body storage, frontend handoffs, the
private source-operation success tail, all listed production storage callers
and the four finite API tasks. No confirmed contract violation or mandatory
extra sealing task was found. Adopted: correct the ownership record, retain the
unfinished interface producer/consumer guarantee, resume within com-amjl. This
is not execution revalidation or task/phase completion.

#### Resumed interface admission localization

[Six fixed-input check probes](../../../evidence/rejection-domains/diagnostic-domain-implementation/interface-admission-localization.json)
reuse the saved associated-row candidate against unchanged product source.
The single-condition original fails at the selected-call evidence boundary;
replacing only `value.inspect()` with `45I64` succeeds. The nested-condition
original and that replacement both fail with the lexical-dependency diagnostic,
while declaration-only versions of both inputs succeed. Thus the latter is
triggered by using the existential contract, not unconditional declaration-only
processing. The two failures must not be collapsed into a single reader defect.

Next source anchors are `Check/Obligations.pw`'s
`checkSelectedCallConstraintBoundary` / `prepareCallTemplateConstraints` and
`Check/InterfaceEvidence.pw`'s `declarationTypeDependencies`, together with
`scopedWitnessDependencies`. Trace exact authored subject/proof and scope at
these boundaries before changing them. Do not admit a normalized subject by
guessing or weaken the foreign-binder gate. These six checks are diagnostic
localization only: no product change, new direct reader RED, execution coverage
or formal timing is claimed.

#### Associated output context diagnosis

[Instrumented six-case results and rejected attempt](../../../evidence/rejection-domains/diagnostic-domain-implementation/interface-admission-output-context.json)
record the single-condition mismatch as authored `Wrapper[T].Value` versus
selected-proof `T.Child`, with the same Marker owner and an interface root.
The nested gate receives `Parent.Child` (no ParamId, one canonical receiver
child) under an InterfaceContract scope. These are unresolved projection terms,
not evidence of a foreign lexical parameter.

Passing the exact witness's retained equations to its self/binding dependency
scan alone changed neither failure. That attempted change was reverted rather
than retained without a demonstrated benefit; all temporary diagnostic prints
were removed. Both builds and six-case runs preserved their inputs. No formal
timing or native GREEN is inferred from these diagnostics.

`retained_associated_interface_nested_contract.pw` isolates contract use from
the later dynamic method call: its source is byte-identical to the executed
without-interface-call RED, and its output remains45. It is pending, not a
passing regression. Existing tests and expectations are unchanged.

Continue tracing the exact failing caller before changing dependency semantics.
In particular, `declarationAssumptionDependency` scans an associated bound's
output again in the consumer scope, while `associatedOutputTermInProof` obtains
an impl output by structural substitution of `AssocBinding.ty`. The binding
currently stores that type and its impl ParamIds but drops `PType.authoredUse`
in both lowering adapters. This belongs to the already-required non-free
occurrence/admission migration here. Preserve the binding's own provenance and
derivation through its selected proof; do not delete the output check, infer
closedness from an absent binder, or repair missing equations by caller lookup.
The source-call comparison is a separate consumer of retained equations and
must also be closed before these interface probes count as execution coverage.

#### Retained declaration dependency context increment (WIP)

[RED, scope controls, mutation sensitivity and fixed-input gates](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-declaration-dependency-context.json)
close a finite dependency-reader defect, not the outstanding public interface
admission failures. An already admitted two-step projection chain was scanned
as unresolved source syntax. Private dependency readers now compose the exact
witness's retained equations with their inherited context and pass it through
condition children, equation prerequisites and associated prerequisites. Type,
bound argument and predicate dependencies replay that context before the final
binder check. Original equation receivers/arguments/outputs and proof premises
still contribute scope dependencies. No source query repairs absent equations.
Public declaration dependency APIs keep their original signatures; the extra
context is private to the admitted traversal. Empty context skips replay.

`RetainedDeclarationDependencyContext` has an actual old-source native RED at
the targeted assertion, followed by six GREEN controls: valid chained output,
missing output equation, wrong output equation, foreign binder, valid owner
versus foreign proof scope with recovery, and a raw projection in an
unconditional child's self/binding. The child control first passes pure proof
integrity. Removing only the two parent-to-child context arguments preserves
the other five controls and fails that control with its exact targeted panic;
the mutation was reverted and six GREEN controls rerun. Missing/wrong equation
controls retain the original proof graph and verify failure followed by valid
recovery, including an empty active assumption stack.

Independent contract-first read-only review `declaration_dependency_context_review`
accepted the finite source/fixture increment and reconciled the sensitivity
result plus source restoration. Its additional scope control was adopted.
Limits: the foreign proof also exposes T in its self type, so it does not
isolate equation-output-only scope traversal; child self/binding sensitivity
is combined rather than separately certified. No broader guarantee is inferred.

Build `20261109T055354-build-fcc21d`, fresh six controls, preserved57/18/17
internal controls and whole compiler source check pass with invariant inputs.
The final public six-case localization retains its same three pre-reader
failures. Formal performance/fixed point, full suites, ASan, source-interface
execution and whole-task completion remain open. Next: trace the public
interface contract's failing dependency caller and its actual context;
retain associated binding occurrence/output derivations and source-call bound
equations at their real declaration producers instead of loosening this reader.

#### Retained abstract interface projection scope increment (WIP)

[RED, scope controls, fresh105, public execution and build](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-interface-projection-scope.json)
record a finite repair after 9b76346e. An interface's selected associated
premise can retain an equation with output zero: the associated output is
unknown, not missing. For Source.Item:Family with Item=Parent, this selected
premise owns Parent.Child even without a free lexical parameter. It cannot be
replaced with Parent's concrete Family witness to invent a known output.

Private scoped type dependency checking now returns successful scope integrity
separately from dependency flags. Exact retained abstract equations follow their
saved prerequisite under the original scope. Constructors compose child
scope results, including abstract outputs without caller dependencies. Raw
unresolved leaves still require a binder or saved derivation. The shared equation
validator verifies declared trait/member existence; zero is not scanned as an
output type. No source query repairs absent evidence, and static Universal
escape rejection remains separate.

The actual File-graph frontend native RED reproduced the old rejection before
the control fixture was expanded. Fresh six controls cover acceptance, foreign
interface scope, omitted equation, nonexistent associated member, missing
interface promise and a real method call. They check recovery and an empty
active prerequisite stack. Build 20261109T063105-build-5eac06 and whole compiler
source check pass with invariant inputs. All105 final native cases pass,
including direct/nested Universal static rejection in interface_final_evidence.
Contract-first independent review accepted the finite source change and
reconciled all179 source hashes, all105 outcomes, immutable inputs and fresh
candidate/build artifact identity.

Both nested_contract and nested_conditions now pass check, AOT/native and lazy
execution with their exact45 goldens. The simple interface_condition case still
fails source-call bound comparison and remains mandatory. The first final run
was interrupted by disk-full and is excluded; the complete retry is the accepted
record. Only completed diagnostics' regenerable LLVM files were removed to
recover space; result records, logs, sources and binaries were retained.

No whole-task acceptance, new formal timing, fixed point, full suites or ASan is
claimed. Main/seed/adopted carrier remain unchanged. Next: close the distinct
source-call bound normalization producer/consumer path without new lookup at
the reader, then resume remaining com-amjl guarantees.
