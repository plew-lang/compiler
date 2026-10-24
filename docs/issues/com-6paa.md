---
id: com-6paa
status: in_progress
deps: [com-m0bf, com-nqjd, com-fyxe, com-qbwg, com-i62n]
links: []
created: 2026-10-24T02:29:50Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, verification]
---
# Preserve declared receiver identity through final body keys

## Boundary and Entry

Planned paired repair from [C3 inventory](com-m0bf.md#producer-and-reader-inventory),
parent criteria 2, 3, 8. This owns registered body receiver production and its
paired key/closedness readers, after other late nominal producers are migrated.

Entry: `Mono/Call::canonicalBodyReceiverRef`, `selectedCallableSubstitution`,
`internBodyInstance`,
`sameBodyRuntimeRef`, `finalStaticCalleeIsComplete`;
`Resolve/Record::parametricSelfRef`; `Mono/FreeFn::registerMethodInst`;
`Mono/Resolve::tyRefIsGround`; `Mono/Ground::assocItemRef`, `setSelfItemEnv`, `setSelfItemEnvForBody`,
`collectDeclarationTypes`, `groundTermInEnvironment`, `groundTermForBody`,
`typeTermSameHead`, `typeTermRefSameHead` and paired legacy bare-name substitutions.

## Finite Actions

1. Migrate declaration and final-body Self environment construction together
   (`collectDeclarationTypes` must not pass through an unowned receiver merely
   because recvInstRef is zero). Retain selected associated Item evidence.
   Use the selected function's complete declared receiver and explicit
   instantiation environment when no instance receiver was supplied, including
   selectedCallableSubstitution rather than recreating f.recvTy from its name. Preserve
   ParamId and nominal owner while removing only the caller's outer views and
   reapplying the selected declaration's own view. Trait-subject/provided copies
   must use retained evidence, not pretend that a trait name is a concrete type.
2. Carry that receiver through body interning, stored signatures, final callee
   descriptors and Mid/backend instance lookup. A supplied receiver and the
   equivalent receiver obtained from the declaration must canonicalize to one
   key; unrelated same-spelled declarations must remain distinct.
3. After nqjd producer closure, retire the paired spelling/whole-program
   parameter-name fallbacks for published semantic nominal types. Keep valid
   primitive/structural/rigid terms explicit. Do not remove every legacy helper
   indiscriminately or merge same-layout distinct owners. No new body-key format
   or runtime ABI is required.

## Exit and Controls

The C3 internal diagnostic currently prints known.hasDecl=1, canonical.hasDecl=0,
then matches the unstamped receiver against two distinct nominal owners (1,1).
Turn it into a regression with proper registered declarations and assert
complete receiver/owner, same-owner key reuse and distinct-owner key separation.
Cover source alias/same-name modules, ordinary/generic/associated/extension and
provided receivers, explicit/synthesized receiver input, and final signature
missing/foreign identity controls. Reuse `mid_type_recipe_instances`,
`mid_unique_type_identity` and existing source owner/static signature controls.
Fresh scoped native/reject controls, exact removal/consumer locations, pinned
inputs and independent completion review required; final gates stay in G2.

## Paired Self-construction Observation

While preparing com-fyxe controls with fixed candidate
8e0f0329887a5386a6a1bdda84328217e64da57ee083a7bc514b35cb6df6a7cf,
`impl[A, B] Pair[B, A] { assoc fn made(first: B, second: A) -> Self {
return <Self first=first second=second /> } }` was rejected as having no
memberwise factory, even after an explicit `impl[A, B] Pair[A, B] { factory }`.
The same body using `<Pair[B, A] first=first second=second />` proceeds to the
actual associated literal-context error. Recheck this against the existing
parametricSelfRef/registered receiver identity repair; it is a recorded boundary
observation, not proof of a new language rule. fyxe keeps the explicit receiver
construction so its context controls isolate the selected signature.

### Registered Self Alias Regression

The permanent part fixture body_receiver_alias_identity preserves the initial
Self-returning associated_literal_owner_context input. Fresh6 (14153136,
SHA6087bdc59fc8bb7dcfc0da488154fd835ae77ed6207fdfbeee779364dc10e4b1)
selects distinct left/right callees361/362 and seals complete receivers/binders,
but finalizes the left Self result with carrier-decl=0 versus source-decl=100685.
Raw receipt: tmp/phase3c-associated-context/part-focused-3 and owner-trace-6.stderr.
This is the planned canonicalBodyReceiverRef/selectedCallableSubstitution/body
signature boundary, not a new selection or inference issue. fyxe's new fixture
uses an explicit Pair[B,A] return to isolate associated parameter context. This
Self variant remains a required native success control for this task.

### Receiver Producer Increment

The first implementation increment consumes parametricSelfRef and saved callable
ParamId arguments for missing concrete receivers. canonicalBodyReceiverRef retains
the complete declaration term; selectedCallableSubstitution no longer uses head
spelling or a result hint to replace it. bodyInstanceEnvironment grounds the
receiver from its explicit callable substitution before key normalization.
Declaration signature collection, verification and setSelfItemEnvForBody use
complete receiver terms. The paired Self/Item adapters now take receiver terms
only; no missing-term simpleTypeRef fallback remains there. parametricSelfRef's
ordinary legacy whole-program head/positional binder reconstruction is removed.
The registered-declaration regression checks owner retention, default/supplied
key reuse and homonymous-owner separation. Legacy equality/substitution reader
retirement and fresh verification remain pending within this task.

### Paired Legacy Reader Retirement

After owner-preserving nominal producers, groundTermInEnvironment no longer
binds unstamped terms by parameter spelling. The whole-program isTypeParamName
query and the obsolete instArgCollidesParamName rejection are removed; ParamId
and registered term closedness own those decisions. typeTermSameHead and its
scalar counterpart reject known/missing nominal identity mismatches. Canonical
body receivers use the ordinary complete type equality instead of a parallel
head/args comparator that erased nested facets. Outer views are normalized once
at the receiver producer; nested views and structural/function children survive.
Fresh target checks and final reader negative controls remain required.

### Fixed Primitive Producer Pairing

Fresh9c4f2d77 builds successfully but exposes expected/inferred Bool identity
inconsistency in Lang's Dictionary loop condition. Strict nominal equality is
retained. The paired semantic fixed-builtin sites now use langTypeRefAt:
Check/Match boolean coverage, Infer/Check logical operands and U64 index,
Verify/Func condition, Resolve/Expr static comparison result,
Resolve/TypeRecovery boolean coverage, Record synthetic Dictionary U64 buffers,
and Mono/Ownership I64 discriminant. Minimal clients keep the existing primitive
atom floor. Unresolved Lower constructors and arbitrary TypeInfo adapters are
not generalized by this correction. Independent scope review classifies it as
the planned Action3 primitive-preserving producer/reader migration.

### Receiver and Body Signature Admission

Independent review identified that a caller-supplied receiver or same-function
foreign BodyInstance could bypass the repaired producer. The common
bodyReceiverMatchesDeclaration validates the selected declaration's receiver
pattern under explicit bindings, allowing only the existing one-way newtype
inheritance boundary. bodyInstanceEnvironment rejects receiver/argument conflicts
and foreign or missing nominal ownership. finalCallBodyEnvironmentMatches checks
selected function, canonical receiver and exact callable arguments against the
retained body environment; completeStaticBodyCallee consumes it before reading
the signature and finalStaticCalleeIsComplete shares the check. Bodyless calls
validate their explicit declaration environment without selecting a new proof.
The registered-owner regression includes wrong/missing receiver, swapped body,
prepared foreign signature and bodyless-descriptor controls. Fresh verification
and reviewer follow-up remain pending.

### Semantic View Identity and Signature Receiver

Independent follow-up requires nested resolved trait-owner views to distinguish
keys even when their compatibility surface IDs coincide. Scalar normalized view
source readers now serve both ordinary view projection and common ref-based
identity. The dead owning typeTermSameHead mirror has no production caller and
is removed. typeTermRefSameHead compares semantic source sets, not redundant
viewExtId/viewIds mirrors. The registered-owner regression adds two registered
homonymous trait owners below Wrapper[Element], key separation and outer-view
normalization reuse.

The prepared BodySignature's receiver is also compared with its selected body
environment by one shared check. Associated-only callables keep the existing
receiverType=0 contract. New controls forge a ready same-body signature with a
foreign or missing receiver and require rejection. Fresh2286dbe6 sourcecheck
passes; its native module control reaches a receiver/declaration inconsistency
in Array.overBuffer. A trace-only diagnostic records pattern/expected/actual
receivers to identify that producer; no accepted comparison is weakened.

### Completed Signature Receiver at Finalization

Freshb4f0d160's trace isolates Array.overBuffer: saved source signature is
Array[U8], but selectDirectTemplateCall grounds the evaluation recipe's bare
Array term, dropping the completed receiverTypeTerm. The finalizer now receives
that saved complete signature term explicitly, grounding it in the caller body
environment for selected callable/body identity. The receiver recipe continues
to own evaluation and dependency provenance. No result/name reconstruction or
receiver inference is reintroduced. The old owning head comparison's remaining
internal client mid_nominal_alias_identity is migrated to the scalar ref reader;
its same-owner alias intent is unchanged.

### Receiver Dependency Remains Mandatory

The independent review of fc183c6b accepts saved signature authority but requires
PriorCallResult/PriorProtocolResult (including views) to keep their exact body/site
dependency checks. groundSelectedDirectReceiver separates the two: Term/opaque
construction recipes use a completed saved term; Prior recipes must resolve their
existing dependency and agree with the saved term, even when that term is present.
Missing dependency, wrong-result site, cross-body and view/protocol variants are
covered by direct_receiver_signature_dependency. No AST order alone proves the
prior operation completed. Freshfc183c6b already passes full compiler sourcecheck
and all four part controls (explicit result, Self result and namespace controls).

## Completion Hold: Unassigned Producer

The fresh39c3e27f module controls4 and compiler-source check pass, but the
mandatory internal authority fixture fails on an ownerless late Buffer[U64].
Independent review identifies an unassigned C3 producer, not another body-key
repair. The approved task addition assigns it to mandatory prerequisite
[com-qbwg](com-qbwg.md); keep this task in_progress until that repair and this
task's own required fresh controls and completion review pass.
The canonical finding, trace, receipt and classification reconciliation are in
[C3 scope reconciliation](com-m0bf.md#scope-stop-unassigned-late-synthetic-buffer-producer).

The Buffer checkpoint ce98f5f4 fresh62a36bc4 passes its first19 native controls
and module4, but optional_chain now exposes a separate, unassigned pre-rewrite
source producer. It also fails with pre-Buffer fresh5 on identical source.
The [current C3 stop](com-m0bf.md#scope-stop-unassigned-pre-rewrite-optional-chain-producer)
owns the finding/proposed disposition. Keep this task in_progress; do not weaken
type identity or absorb another producer into the registered body-key repair.
The approved [com-i62n](com-i62n.md) is now its explicit required prerequisite;
this task retains its own fresh control and independent completion review exit.
