---
id: met-ia09
status: open
deps: []
links: []
created: 2026-10-13T01:40:08Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, generics, verification]
---
# Close saved constraint evidence through callee environments and final use

Reconcile the cumulative candidate before work: historical Direct evidence transfer, presence environments, supertrait edges, receiver/TraitSubject, associated-clause evidence, requirement-to-implementation derivations and Provided Static handoff already have bounded implementations/evidence. Do not re-register their earlier next-step paragraphs as untouched work. [Migration evidence](https://github.com/plew-lang/meta/blob/main/evidence/typechecking-remediation/design-migration.md) gives revision boundaries.

Remaining closure audit: bind each callee declaration-bound identity to its saved evidence in the explicit instance environment; include those bindings in sameInstanceEnvironment, withLexicalSelfBinding and body identity. Preserve legitimate empty bindings versus missing/unprepared. Source public requirements and chosen implementation obligations are not positional arrays to zip: retain conformance, requirement clause, implementation declaration and derived proof identities. Check Function/Requirement/Conformance/MethodReceiver/TraitSelf/TraitSubject/AssociatedType roots, AssumedBound/AssumedSupertraitPath/AssumedTraitPath, conditional child proofs, projection normalization and ExistentialBox consumers. Declaration worklists (Check/Bounds iteration and Check/Obligations) and execution preparation need explicit environments; ambient Mono Cursor cannot replace them.

Presence evidence establishes neither source-path admission nor unique member dispatch. Even an unused source bound needs its unique specification-valid path; executable endpoint selection is a further distinct demand. Preserve admitted source proofs without silently privileging a caller path. Conditional WitnessConditionPlan children are not a substitute for complete supertrait derivations. Ground concrete selected evidence without repeating selection; abstract/deferred evidence remains distinct from a missing concrete binding.

Cover Written Direct, Static Requirement/Provided, operator, protocol, try conversion, root/entry, extern/bodyless and synthetic calls. Entry must consume selected body identity. Associated declaration proofs must reach projection prerequisite -> selected conformance -> original clause -> final consumer; do not merely privatize stores. Requirement derivations must handle weaker/reordered impl bounds, supertrait and conformance-where entailment.

Acceptance: producer construction/storage -> owner admission -> explicit substitution -> real callee body context/final consumers all closed; remove old lookup and reader-side source obligation reconstruction only after publisher authority is structural. Positive and missing/foreign/clause/path/replacement controls, differing evidence with same type arguments, AOT/JIT and applicable parent gates. Public storage writers are not semantic success capabilities.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Included repair**.

Current declaration-bound identity, binder/proof/environment keys and selected-call instances through real callee contexts. Preserve existing simultaneous substitution and proof keys. Coordinate the saved-source operation contract with met-ucze; no new allowunique/conditional capability solver.

## Source-selected Static Enqueue Increment (WIP)

The existing Direct/Static evidence readers are reused, not replaced by a new
constraint store. enqueueSelectedCallee now requires the retained CallTemplate;
it constructs the exact evidence from that source operation in the explicit
caller environment. Written calls, operators, protocol slots and try conversion
all use this entry. Its default Declaration evidence parameter is removed.
Protocol grounding and selection consume the same acquired template rather than
independently acquiring or interpreting its source occurrence.

Declaration worklists route static requirements/provided methods, protocol and
operator calls through the same explicit-environment reader. A shared substitution
gate distinguishes deferred/open arguments before concrete evidence instantiation.
Bodyless requests admit signature/evidence before completing without a body.
Root and synthetic declaration producers retain their separate legitimate path.
Requirement-to-implementation mapping retains the existing conformance method
plan and original clause identities; no public/implementation bound arrays are zipped.

Whole-compiler source checking succeeds with the preceding fixed carrier.
An internal source-imported control is being added for operator/protocol callee
bindings, explicit environments and malformed bodyless evidence. Fresh binary,
matching-source cost and applicable full gates remain pending. This increment does
not close dynamic descriptors, associated proof consumers or the entire issue.

Current-source imported controls pass existing requirement derivation (including
reordered/weaker/conformance bounds), provided-body bindings, Direct evidence,
selected conditional proofs and independent global owners. The new implicit-call
control reaches real operator/protocol callee environments and succeeds with an
explicit caller environment while the ambient cursor is cleared. A canonical
nominal/binder confusion exposed by this control is recorded in met-6e6k.
Additional empty-evidence replacement and provided-placement guards require the
next fresh candidate's checks; no full-gate success is claimed yet.

The fixed 2b241be3 full normal run found lexical_body_requests reading a failed
owner's unpublishable operation before testing writer rejection. Preserve that
fixture's original refusal/retry/cursor/independence checks: retain the attempted
row while Building, then use it for the post-failure rejected writer call. Do not
make failed-owner rows readable to satisfy this internal fixture.

## Dynamic Requirement Bounds: Reproduced Gap and Next Closure

Compiler 2899ddad accepts this requested body in check (exit zero):

```plew
trait Marker {}
trait Service { fn get() -> I64 where Self: Marker }
fn probe(value: any Service) -> I64 { return value.get() }
fn main() {}
```

The receiver interface does not guarantee Marker. sourceSelectedCallBounds drops
Dynamic and existential Protocol clauses, and recordDynamicCallTemplate receives
but does not retain receiverTerm. This is an existing complete-signature gap,
not permission to forbid all method bounds through existentials or treat an
existential container as conforming to its own trait.

Close it from signature construction through final dynamic use and concrete
witness preparation. Reuse the selected requirement, associated bindings and
SourceCallSignature.Trait normalization. Represent an interface's universally
quantified hidden Self with a distinct rigid binder and explicit immutable
interface-evidence provenance; do not reuse an enclosing method's lexical Self,
introduce a local inference variable, or infer equality of two erased values.
The interface guarantee is a proof-only contract. It does not expose a new source
type, enable unsupported generic opening, or change the dynamic ABI.

A shared immutable interface evidence root can justify only guarantees entailed
by that exact trait instance and its associated bindings. Caller substitution
must retain this root and ground caller-owned terms explicitly. Source admission
and the final dynamic descriptor consume the saved clauses/proofs; missing,
foreign and replaced evidence must fail rather than silently regenerate a proof.
Do not funnel a universally scoped interface guarantee into static callable
selection as though the hidden concrete witness were known.

Concrete existential witness preparation is the first-concrete boundary. Consume
the already selected boxing proof, use the retained requirement-to-implementation
plan, and pass exact implementation-bound identities into the selected body.
Separate method formation from call availability: spec/08 allows an existential
even when some members are unavailable. A member whose public preconditions are
not established cannot be invoked; a forged/missing proof for a promised member
is an error, not a non-dispatchable sentinel. No blanket new object-safety rule,
implicit downcast, runtime trait search or where-clause exemption is approved.

Required controls include the rejection above; an inherited guarantee that does
permit the call; associated-type predicates; a call inside a provided body whose
lexical Self is unrelated to the erased receiver; unavailable unused members;
and missing/foreign/clause-replacement evidence through final AOT/JIT consumers.
Do not close this task after only adding the receiver field or a source check.

Reference: Rust's item-bound satisfaction contract requires bounds when an item
is used (https://doc.rust-lang.org/reference/trait-bounds.html#bound-satisfaction).
Its dyn-compatibility restrictions (https://doc.rust-lang.org/reference/items/traits.html#dyn-compatibility)
are not imported wholesale: Plew's spec/08 explicitly separates existential
formation from member availability. The exact internal representation must retain
these adopted semantics; any newly necessary language decision still requires
user judgment.

### Internal Implementation Sequence

#### Concrete Boxing Boundary and Remaining Audit

The working increment now distinguishes source-call and interface-contract
scopes, reuses signature normalization, and interprets the latter with its exact
selected boxing witness. Both declaration and execution worklists select the
available member through the same private entry and pass Requirement evidence
through conformanceMethodPlan. Actual signature checking uses the admitted
implementation environment. A source-call root cannot authorize a contract.
Fresh controls cover unavailable unused members, actual condition-using bodies,
reordered public/implementation predicates, missing/foreign/replaced evidence,
and real session Mid preparation. Main/full gates are not implied.

An existing conformance comparison also compared an implementation's raw Self
subject/trait arguments against receiver-substituted public clauses. The
increment applies the same explicit receiver interpretation as the signature's
result, using pure substitution rather than associated-type re-selection.
Original clause identities and the contextual Self contract remain intact.
The dedicated conformance_method_self_conditions control includes Self inside
the required trait's arguments.

Give interface-contract interpretation its own explicit provenance. A contract
for a selected boxing conversion/requirement is not an invented source call,
and must not borrow a CallSiteKey or ambient caller merely to use an existing
checker. Source-call and contract scopes cannot authorize each other's rows.
Normalize public clauses with the same trait-signature machinery and query them
from the exact interface/associated guarantees and concrete target terms.
An unavailable member is distinct from an invalid derivation for an admitted
member. Do not swallow proof errors as a missing optional table slot.

The shared interpreter needs a concrete-root interpretation supplied by the
already selected boxing witness, alongside its abstract-root interpretation for
dynamic calls. Retain the associated/supertrait clause and selected conformance
workers introduced above. An abstract interface result cannot become static
Ready by changing a tag; a concrete interpretation must establish and validate
the actual selected witnesses.

Reuse the retained conformanceMethodPlan for requirement-to-implementation
transfer, including weaker/reordered implementation conditions. Pass Requirement
evidence into witness body preparation; remove its Declaration default path.
Cover unavailable-unused members, available conditional bodies, inherited and
associated guarantees, explicit source views and malformed promised evidence.
The inherited/newtype target recursion inside enqueueFinalBody still calls the
Declaration default when it changes the receiver. Audit its retained proof and
bound mapping before closure; the new concrete-boxing call's explicit evidence
alone does not prove that nested adapter boundary preserves it. Also inspect
finalExistentialIndex's source/target-only cache against differing selected proof
identity, including the early successful return on a cached conversion.

Audit universally scoped nominal predicates separately: a nominal witness with
hidden type arguments may have no interface-assumption child. The blanket
declarationWitnessDependency refusal and interfaceProofRoot-only classification
must not be assumed to cover that case. Check source admission, unavailable
member classification and both proof interpretations with real controls before
calling the universal predicate surface complete. Reuse admitted environments
between signature validation and enqueue rather than interpreting the same
requirement-to-implementation mapping twice.

If a necessary case cannot preserve its admitted evidence without a new runtime
ABI/semantic decision, reproduce it and request that judgment rather than adding
a new implicit selector or silently changing the accepted condition.

The retained interface interpretation now has an explicit declaration or body
owner and a fresh hidden binder when its condition set is nonempty. Its result
is distinct from concrete static evidence. Final dynamic call rows retain a
private immutable evidence capability, preserved by the resolution pool and
checked at publication, Mid signature materialization and LLVM preflight.
`interface_final_evidence` exercises real session Mid preparation and rejects
missing, nonexistent, foreign-body and substituted-operation capabilities. The
static adapter also rejects a universal interface assumption.

Conditional witness children, projection normalization and retained trait edges
now share that explicit interpretation context. Associated-clause dependency
admission follows its prerequisite instead of reclassifying its projected type
as an unbound source parameter. Fixed caller outputs receive first-concrete
source admission; later outputs/child conditions use the retained conformance
clause. Concrete and abstract supertrait/associated interpretation reuse the same
selected-evidence workers. Scope admission returns its dependency result so an
associated chain is not recursively admitted twice at each level.

Fresh controls cover the compound condition, nested associated normalization,
a caller-authored root combined with an interface-derived edge condition,
original source ownership refusal and real Mid preparation. This is still a
bounded increment: concrete boxing needs retained requirement-to-implementation
evidence and unavailable-member separation. Fresh focused checks do not replace
the parent fixed-point/performance and whole-suite gates.

Keep this work in the existing evidence domain rather than introducing a second
body checker or a runtime trait solver. The representation below is an internal
plan, not a new source-level opening feature or a claim of implementation.

1. **Interface root and scope.** Intern an immutable, session-local interface
   contract for an exact existential type/binding instance. Allocate its hidden
   Self through the ordinary ParamId allocator; it is rigid and distinct from
   both an inference variable and the enclosing provided body's lexical Self.
   Retain the interface bound and binder together. A declaration-proof scope can
   authorize this exact root only for the matching selected dynamic operation;
   it cannot authorize arbitrary interface roots or make any P conform to P.
   Reuse DeclarationBoundRef / existing assumption and supertrait/path evidence
   with an explicit interface-root kind rather than a parallel trait solver.
2. **Source call admission.** Dynamic and existential Protocol templates retain
   their actual receiver and interface root. Normalize the selected requirement's
   clauses with the existing SourceCallSignature.Trait machinery, substituting
   its hidden Self and exact associated bindings. Derive only from that interface
   and the caller's actual lexical premises. Seal the complete clause/proof plan
   with the owner; an absent or mismatched plan is not an empty signature.
3. **Two explicit evidence interpretations.** For a dynamic caller, substitute
   caller-owned parameters while retaining the interface's universal hidden Self
   under its exact new scope. This is capture-avoiding proof substitution, not
   static concrete-witness selection. Return a distinct interface-call evidence
   result so it cannot enter static callee enqueue as concrete evidence. For
   first-concrete boxing, substitute the already selected boxing witness for
   that same root and use the existing conformanceMethodPlan to transfer public
   clause identities into implementation-bound evidence. Do not zip public and
   implementation clauses or reconstruct them from an ambient body cursor.
4. **Concrete member availability.** A source interface can exist with unavailable
   members. First-concrete member preparation distinguishes genuinely unavailable
   ABI/conditions from a malformed or foreign promised proof. A concrete method
   whose preconditions fail is not enqueued merely because an implementation
   exists. A member admitted as callable must retain its exact successful
   evidence through body/adaptor/descriptors. Preserve both declaration-worklist
   checking and executable preparation; neither uses Declaration as a substitute
   for the retained requirement-to-implementation derivation.
5. **Final consumption and removal.** The dynamic descriptor/call reads the
   saved, caller-instantiated interface evidence and exact requirement/receiver
   boundary. Concrete witness bodies receive mapped implementation evidence.
   Required-fact deletion, another receiver/interface root, replaced clauses and
   wrong caller bindings must fail without rerunning source selection. Remove
   the Dynamic/Protocol bound-dropping branches and boxing Declaration fallback
   only as these replacement paths become connected; do not call a source-only
   rejection the completed fix.

Fresh reject controls cover unproved Self, unproved Item, implicit trait-source
preference and an enclosing unrelated Self that does have the desired trait.
Positive controls cover supertrait/associated/compound guarantees and an
unrelated enclosing Self. Missing/foreign/replacement controls reach the final
descriptor and real Mid preparation. Formation of a box with an unavailable,
unused conditional member remains a required repair target; do not merge that
pending behavior into the successful focused set.

References for representation, not imported source rules:
[Swift SE-0352](https://github.com/swiftlang/swift-evolution/blob/main/proposals/0352-implicit-open-existentials.md)
distinguishes the box from its hidden conforming type and does not equate the
underlying types of independent boxes. Plew's proof root follows that distinction
without broadening this task to generic opening or Swift's erasure conversions.
[Rust's higher-ranked checking](https://rustc-dev-guide.rust-lang.org/traits/hrtb.html)
uses fresh placeholders and checks that they do not leak into unrelated existing
parameters. The relevant lesson is scoped rigid identity and capture-avoiding
substitution; this does not introduce Rust lifetime syntax or HRTB features.

### Source Admission Versus Existence: Reproduced Additional Gap

The measured 5e1dd64b candidate accepts a fully closed call to accept[T] where
T: A when S reaches empty A through both S:C -> B -> A and S:D -> B -> A.
No member is used; check exits zero. This violates the adopted unique source-path
contract in Types and Evidence, not a new inference or trait feature.
The new source_bound_ambiguous_empty_trait control retains that input. The
positive source_bound_unique_empty_trait combines an explicit #C source with
exact duplicate authored T:A premises; duplicate representations of the same
premise are not separate declaration paths.

The existing requireUniqueWitness flag describes executable member selection:
mergeMemberWitnessProof can merge different paths with the same terminal witness.
An internal existence result and that endpoint merger cannot certify unique
source-path admission. Close this through one proof-query policy with explicit
Existence / SourceAdmission / MemberDispatch demands, shared matching/conditions
and source/view selection. Source admission deduplicates the same normalized
root and declaration path, not merely equal endpoints; distinct trait-subject
branches remain ambiguous. Caller-owned exact duplicate promises can be
canonicalized by their checked bound and path, without arbitrary root-ID priority
or a broader inference solver. Preserve explicit source views and conditional
applicability before selection; do not make a #C positive ambiguous by dropping
its selected source while collecting all paths. The first bounded query-policy increment is now implemented: explicit
ConformanceProofDemand at the core query, separate source-path versus terminal
merging, query-local duplicate-premise comparison, and explicit source preference
without erasing an unrelated unique conformance. Source call-clause admission,
protocol/operator proof construction and existential injection request source
admission. The ordinary ambiguous-empty-trait source is rejected by current
imported algorithms, and both #C/#D, an unrelated view and duplicate promises
remain accepted. Whole-source check and seven existing evidence controls plus
the new query/ordinary-frontend control pass with the old measured driver.
This is not a fresh candidate or full closure.

The next bounded increment separates query outcomes (Missing / Found / Ambiguous)
from admission diagnostics, checks output compatibility after path selection,
prioritizes exact opaque premises and makes conditional applicability require
source-valid conformance. Source proofs and boolean eligibility now share the
same explicit-demand query; ambiguity makes a conditional candidate inapplicable,
whereas malformed proof interpretation remains an error. The new internal output
control checks bare ambiguity, #C success, #D output mismatch without fallback,
conditional Wrapper eligibility and stronger versus opaque authored premises.
Fresh 2154af1b passes whole-source check, 55 AOT and 36 rejection controls, and
generation-two fixed point with formal median 6.521807 seconds. Evidence is in
meta's source-owner-facts/conformance-query-fresh.json and
conformance-query-self-host.json. These gates do not close final-consumer or
source-certificate auditing.

The raw Building constraint-plan writer is being made module-private. Its sole
producer is the complete source-signature/query constructor; admission and final
readers validate/consume that retained value. Internal corruption controls submit
bad local plans to the same admission validator without injecting them into the
real store. This closes this writer's alternate construction route, not every
raw operation/conversion producer. Preserve separate missing/foreign/clause/scope
controls and the privacy rejection through a fresh candidate before closure.

Partial-input projected member enumeration remains a presence probe: it has not
yet selected a complete positional trait instance. Do not label that probe source
admission; met-6e6k retains its exact-instance selection audit. The interface-root
and dynamic/boxing proof substitution work above is still unimplemented.

The ordinary opaque-output source control exposed another query-boundary gap:
the parsed constraint retains positionalArgsOpen even for a zero-arity trait.
An API-only exact query correctly returned Missing, while the source wrapper
skipped exact-premise priority and diagnosed a competing derived path. Normalize
that empty input against declaration arity at the common query boundary, and
exclude query openness from declaration-path root identity. Current imported
controls cover both the authored wrapper and an actual analyzeFrontend call;
new ordinary source fixtures cover ambiguous/mismatching/conditional outputs and
stronger-premise propagation to execution. Fresh verification remains required
for this last increment; do not repair the opaque fixture by changing its
expected diagnostic to the old ambiguity.

### Interface Evidence Implementation Boundary

Use a private immutable interface-evidence node pool in Frontend, referenced by
an explicit DeclarationBoundRef.Interface kind. A source node owns session,
semantic owner, exact CallSiteKey/receiver/trait instance, and a fresh rigid
hidden-Self term. The bound's subject is that hidden term, never the existential
container and never the enclosing lexical Self. Its constructor is private to
selected Dynamic/Protocol recording. DeclarationTypeScope admits that one root
only for the matching saved operation; ordinary static scopes admit none.

At an executable caller body, interpret the same source root under its explicit
BodyInstance environment, with a fresh hidden binder for that interpretation.
Retain original-root identity and caller body in the immutable interpretation;
substitute caller terms and source hidden Self together without capture. Repeated
use of the same source root/body reuses its interpretation. Independent call
sites and body instances do not acquire equal hidden types merely by sharing a
printed trait or source binder. Use existing source-fact session identity and
body/environment identities, not an unrelated new session registry.

Factor proof substitution and edge/condition/projection replay under a private
explicit scope. Concrete substitution and universal interface substitution share
that traversal and retain original declaration/clause roots; the latter permits
only its exact hidden binder after caller substitution. Keep their public result
types distinct. Universal completion cannot become StaticProofInstantiation.Ready
or enter a static callee queue. Missing promised bindings and malformed/foreign
roots remain errors; an actually open caller is not successful evidence.

The dynamic final descriptor retains the prepared interface-call evidence for
its exact source root/caller/requirement/receiver. It consumes saved obligations
without source selection. First-concrete boxing instead substitutes the already
selected concrete witness and existing conformanceMethodPlan, and distinguishes
an unavailable unused member from corrupt evidence. Connect these actual readers
and remove the old bound-dropping/Declaration fallbacks before calling this
increment complete. Private root storage alone, source rejection alone, or new
checks without those consumers are not completion.

### Source Interface Scope Increment

The source-operation constructor now retains an immutable Interface bound root
with a fresh rigid hidden Self. Dynamic and existential protocol signatures
retain all public clauses. Source proof validation checks the exact operation,
receiver, lexical owner and interface root, while distinguishing universal hidden
Self from unresolved caller parameters. The imported interface_source_scope
control succeeds with a real golden output and rejects foreign/missing roots.
Whole compiler source checking succeeds with the preceding measured carrier.

This is a WIP boundary: executable-body interpretation, shared proof substitution,
final dynamic consumption and concrete boxing evidence transfer are still open.
The existing final consumers currently ignore the new root. No full-gate or fresh
compiler claim is made for this increment.

### First-Concrete Source Admission for Unused Derived Bounds

A bounded control found a further omission: requireQ[T] where T:Q is empty,
viaP[T] where T:P forwards to it through impl P as Q, and a concrete S has
both P -> Q and R -> Q. Direct requireQ(S) rejects, while viaP(S) formerly
passed both check and AOT; adding a Q member use made it reject. The relevance
filter incorrectly limited declaration work to executable member obligations.

Relevance now includes public conditions with unresolved subjects and propagates
through callers. At their first concrete substitution, derived proofs discharge
SourceAdmission uniqueness independently of MemberDispatch. This gate preserves
the retained derivation: it never replaces it with the query result or reopens
callable selection. An exact authored Function/Requirement premise instead
consumes its already-admitted caller binding. This is not a blanket requery of
closed source operations or permission to ignore missing proof storage.

Whole source checking and the imported forwarded_source_admission control pass,
covering an ambiguous bare S, explicit S#P, and an uninstantiated generic body.
Fresh compiler checks remain pending at this increment.

### Adopted Decision: Erasure Is Not an Implicit Source Selector

User decision: any P does not implicitly select P's route to another trait Q.
The specification records this in spec/08 existential member availability and
spec/09 source paths. For hidden Self, consume explicit interface, supertrait and
associated guarantees. A trait-subject impl P as Q alone is not a universal Q
uniqueness guarantee. Caller-owned concrete/abstract terms retain their actual
explicit constraints. Do not ban existential formation merely because a member's
conditions are unavailable.

```plew
trait Q {}
trait P { fn get() -> I64 where Self: Q }
impl P as Q {}
fn probe(value: any P) -> I64 { return value.get() } // reject
```

A concrete S may also conform to R with impl R as Q. Its two Q paths remain
ambiguous after erasure; no hidden #P preference is added. P:Q can instead declare
the needed guarantee, requiring concrete conformers to satisfy that contract.
Ordinary generics keep their first-concrete source-admission gate; the universal
interface proof is not concrete StaticProofInstantiation.Ready evidence.

[Concrete programs and scoped observations](https://github.com/plew-lang/meta/blob/main/evidence/existing-feature-conformance/source-owner-facts/universal-interface-decision.json)
preserve the pre-decision check/AOT discrepancy. The source root exists, but
universal proof interpretation, final dynamic consumption and concrete boxing
transfer remain implementation work. Add rejection and retained-guarantee controls
at the actual publishers and consumers; do not close the issue at source checking.

Swift SE-0309 supports separating existential formation from member availability.
Rust's [coherence rules](https://doc.rust-lang.org/reference/items/implementations.html#trait-implementation-coherence)
reject overlapping impls rather than selecting competing paths. Plew preserves
its explicit source selectors instead of importing either language's coherence
model or introducing an implicit source choice at erasure.

### Explicit Guarantee Admission Increment

The common proof query does not extend universal interface premises through
trait-subject edges. Integrity validation also rejects a forged universal
trait-subject path or concrete witness for the rigid hidden subject. Explicit
supertraits remain available. Associated declaration promises retain their
original projection, prerequisite and clause even when Item=T normalizes the
obligation subject to caller T. The common associated-clause interpretation
recognizes that an abstract declared premise can promise a known output's bound;
concrete witnesses cannot self-authorize from a declaration schema.

Whole compiler source checking and the imported interface_declared_guarantees
control pass: implicit-path rejection, explicit supertrait, associated guarantee
with generic output, and a caller-authored bound. New sole-path/collision reject
fixtures are retained for the next fresh compiler. The relevance seed check is
folded into the existing declaration fixed-point walk, removing its extra full
call traversal. Fresh/performance and final dynamic proof transport remain open.
