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

New red controls cover unproved Self, unproved Item, and an enclosing unrelated
Self that does have the desired trait. Positive controls cover supertrait and
associated guarantees, an unrelated enclosing Self, and forming a box whose
conditional member is unused/unavailable. They are implementation targets, not
currently green gates. Add scoped missing/foreign/replacement controls at the
actual final readers before closure.

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
