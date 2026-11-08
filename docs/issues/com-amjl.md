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
