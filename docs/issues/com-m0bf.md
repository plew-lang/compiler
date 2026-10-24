---
id: com-m0bf
status: closed
deps: []
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, verification]
---
# Classify remaining unstamped nominal producers and paired legacy readers

## Boundary

Phase 3C / C3. **Bounded producer inventory.** Parent criteria: 1, 2, 3, 8.
This is a bounded child of [met-6e6k](met-6e6k.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Codegen/Resolve/Expr.pw`; `src/Codegen/Resolve/ExprType.pw`; `src/Codegen/Resolve/TypeRecovery.pw`; `src/Codegen/Check/Literal.pw`; `src/Codegen/Mono/Call.pw`; `src/Ir/Types.pw`.

Enumerate production constructors lacking declaration identity on the paths from source named construction, body signatures, associated-function inference and registered body receiver terms. Pair each with its consumers in tyRefIsGround, grounded type reads, sameBodyRuntimeRef and final descriptor validation. Distinguish source nominal terms from legitimate builtin/rigid/construction placeholders.

## Exit and Evidence

Each hit is tied to one of the four entry families, a canonical producer or a legitimate construction-only representation, exact fallback consumers and current controls. The custom-factory source/context lane below is assigned to com-uruz; independent allocation reconfirmation is complete. For each real gap create a paired producer-plus-reader repair child with exact API/fixtures and make it mandatory; do not delete all spelling fallbacks at once. This inventory closes classification, not unperformed repairs.

Existing starting controls: `mid_type_recipe_instances`, `type_term_closedness`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.

## Producer and Reader Inventory

Inspected production code at **c056e658** (documentation checkpoint e6ef8918).
The inventory below records the inspected entries; its original completeness
claim was reopened after the Buffer and pre-rewrite Chain omissions below.
The added rows assign both producers explicitly. Rebuild/view/
substitution helpers preserve existing identity; they are not new spelling
producers. Classification is not the completion of the paired repairs.

| Entry family / producer | Representation and status | Paired reads / disposition |
| --- | --- | --- |
| Named memberwise source construction: `Expr::inferMakeInstance` | Preserves selected existing TypeRef or stamps the selected nominal declaration before recording. This does not classify custom-factory preparation/rewriting. | Semantic aggregate/expression -> body grounding -> Mid aggregate. The custom-factory lane below is a separate required finding. |
| Custom-factory source/context receiver: `Global::resolveConstructionContext`, `prepareFactoryConstruction`, named-factory/cast rewrite, `SyntheticCallSite.receiverTerm` | Current String options controls save an unowned `Options` receiver before body finalization. Trace the first loss in supplied context versus raw receiver construction; do not assume only the simpleTypeRef fallback is responsible. | Saved CallTemplate.receiverTypeTerm/signature -> declaration/executable worklists -> body environment/signature -> Mid/LLVM. Mandatory [com-uruz](com-uruz.md); classification reconfirmation covers this separate producer boundary. |
| Array construction: `Expr::arrayRefOfElem` | Retains full element and canonical Lang Array identity where available. `typedIrRefOfInfo`'s name-only element recovery remains distinct. | Published expression/aggregate and generic arguments; canonical main path preserved, legacy adapter assigned nqjd. |
| Source TypeInfo adapters: `TypeRecovery::typeInfoOfName`; `Expr::typedIrRefOfInfo`; `FreeFn::tyRefOfInfo`/`findOrAddTypeRef` | Primitive/unknown compatibility descriptions are legitimate during construction. An ordinary nominal recovered only via global firstBareTypeNamed or a new name-only append lacks owner/binder authority. | `recordSemanticExprInfo`, body type recovery, grounding and final signature completeness; mandatory repair nqjd. No global name-id stamping. |
| Body signatures: `Expr::semanticCallableReturnTerm` | Existing lowered return terms retain identity. Unit is a structural empty record. Async omitted return creates an unstamped Promise[Unit] after declaration publication. | CallTemplate result, body signatures and final descriptor grounding; mandatory nqjd. `Call::groundedSelectedCalleeReturn` also has a retTy=0 to simpleTypeRef adapter assigned to nqjd (keep genuine omitted Unit distinct from a missing annotated return). Promise name-collision source control currently passes, so no source-level failure is claimed from this observation alone. |
| Associated type qualifier: `Record::concreteTypeQualifierTerm` | Direct append after `typeDeclIdentityAt`, with conditional hasDecl. The resolved branch is canonical; the missing branch must remain construction-only or be rejected before saving a selected receiver. | `methodReceiverTerm`, `directReceiverTemplateForExpr`, Check/Call and ExprType. nqjd must explicitly verify/seal the missing branch rather than classify every qualifier as already canonical. |
| Associated function inference: `ExprType::associatedReceiverFromArguments`, `groundFinalMethodSignatureTerm` | Existing recvTy, signature terms and simultaneous explicit environment preserve identity. `groundFinalMethodReturn`/Parameter's missing-ref path and boundMethodRetInfo still accept a name-only receiver. | Saved signature and selected call term; missing complete term/lexical binder recovery is nqjd, registered receiver/key migration is 6paa; saved associated parameter context selection is fyxe. boundMethodRetInfo can represent a lexical ParamId, so do not stamp it as a same-spelled nominal type. Keep the correct full-term lane. |
| Associated literal context: `Literal::checkAssocArgsLitCtxFromExpected` via `checkLitSpanCtx` | No direct nominal append. A competing name lookup/inferFnArgs plus positional ctx.args -> f.typeParams map remains; callers exist in Record, Generic and Verify. It cannot be classified as a universally preselection-only adapter. | Full selected parameter context and literal checking -> saved source call -> final call; mandatory fyxe. Do not replace one missing-owner term with another lookup in a final reader. |
| Registered receiver: `Call::canonicalBodyReceiverRef`, `selectedCallableSubstitution`; fallback `Record::parametricSelfRef` | Missing explicit receiver is reconstructed by simpleTypeRef even when Func.recvTy is complete; selectedCallableSubstitution similarly reconstructs its receiver instead of preserving the declaration term. ParametricSelfRef's main recvTy lane is correct; fallback rebuilds type parameters without ParamId and the nominal head without owner. | internBodyInstance -> body signature / final callable / Mid lookup. Internal diagnostic confirms identity loss and mixed known/unknown key equivalence; mandatory 6paa. |
| Body/signature Self bridges: `Ground::assocItemRef`, `setSelfItemEnv`, `setSelfItemEnvForBody` | simpleTypeRef still rebuilds a receiver when recvInstRef is absent. `collectDeclarationTypes` can take this lane even when f.recvTy exists. | Declaration signature collection and Call final body environment, then recorded/body types. Assigned to 6paa together with parametricSelfRef and canonicalBodyReceiverRef; preserve the valid retained Item/proof environment. |
| Chain-generated registration: `Call::chainStageResultRef`, `registerChainSiteInsts` | Existing head rebuild retains identity. Missing continuation ref appends a naked nominal name; Optional[V/U] registrations also omit owner. | scanType, chain result/rewritten call facts, worklist registration -> final descriptors; mandatory nqjd. |
| Pre-rewrite chain source result: `Locals::optChainResultRef` via `ExprType::constructExprTypeWithChainHole`, captured by `Record::recordExpr(OptChain)` | Rebuilds Optional[U] and a missing continuation ref without owner, then records that nonzero result before rewrite and expected-result/conversion checking. Later canonical ChainSite production cannot repair this earlier commitment. | Saved semantic result/conversion -> generated MatchExpr / ChainSite -> both worklists -> final Mid/LLVM; mandatory [com-i62n](com-i62n.md). Separate from nqjd's listed late registration changes, qbwg's Buffer construction and 6paa's registered body keys. |
| Dual-stage synthetic construction: `Lower/Types::synthBufferNew`, called by `Lower/String::beginStringInterpolation` and `Record::synthEmptyDict` | Early construction records fixed Core-module provenance for ordinary declaration resolution. The same helper appends an unowned Buffer[elemRef] after publication for Dictionary's keys/values/hashes/buckets. That late branch is not covered by the one-time declaration batch. | SyntheticCallSite.receiverTerm -> complete signature -> both worklists -> body environment/key/signature -> final callee -> Mid/LLVM; mandatory [com-qbwg](com-qbwg.md). This new producer entry is separate from nqjd's reviewed bounded closure and 6paa's body-key migration. |
| Rigid/structural helpers | chainValueArgIndex creates declaration-owned ParamId leaves; semanticSourceResultTerm creates Unit; closureFnTypeRef creates a function structure; reserveTypeSentinel reserves absence. Primitive literal contexts are explicit builtin atoms. | Legitimate non-nominal/construction representations. Do not invent nominal declarations or infer binders from matching printed names. |
| Rebuild/publication helpers: `Frontend::pushType`, `Arena::registerType`, `finishTypeDeclarationResolution`; Ground rebuild/view helpers | pushType interns names and preserves supplied identity; registerType synchronizes rows/terms. The one-time declaration batch resolves source-site rows; it cannot stamp later appends or act as mutable post-publication repair. | Scalar/owning rows, typeIsClosed, grounding and runtime signature readers. D4 remains the separate publication audit; nqjd/6paa must supply late identity at production. |

The paired legacy readers are explicit: `Mono/Resolve::tyRefIsGround` uses
whole-program isTypeParamName only for unstamped terms; `Mono/Ground` retains
bare-name substitution/equality bridges in groundTermInEnvironment,
groundTermForBody, typeTermSameHead and typeTermRefSameHead; `Mono/Call::sameBodyRuntimeRef` compares
names when either side lacks owner; descriptor completeness currently checks
closedness and cannot restore lost nominal identity. These are not permission
to delete all fallbacks before migrating their producers. nqjd supplies late
source/synthetic terms, fyxe closes the associated context authority, and 6paa
closes registered receivers and the corresponding final-key fallback. Their
actual dependencies, area/G1 admission and D4 prerequisite are retained in tk.

### Evidence and Limits

Fresh candidate6 at c056e658 passes `mid_type_recipe_instances` and
`type_term_closedness` natively (controls-1, native2, no exclusions, input hashes
unchanged). The additional Promise/type-parameter-name source probe passes
source check with a preexisting warning; it does not establish all identity
properties. The internal boundary diagnostic supplies a Func with a complete
nominal recvTy, requests its canonical body receiver without an explicit instance,
and observes **1 / 0 / 1 / 1**: known identity present, synthesized identity absent,
and key equality with each of two different nominal owner IDs. This isolates the
producer/key boundary; it is not a demonstrated user-program miscompile or a
complete malformed-descriptor test. Raw probe and hashes accompany the receipt.

These planned repair descendants implement this inventory's required disposition;
closing C3 certifies classification only, never those source changes. No source,
syntax, ownership or inference specification change is proposed. The final parent
requires all mandatory repairs plus its remaining audits and G2 gates.

### Independent Completion Review

`/root/nominal_inventory_completion_review` reviewed b700300e, production c056e658,
the inventory receipt and the subsequent documentation corrections read-only.
Final verdict: **classification complete; no remaining blocking findings**.
The corrections replace the mistaken construction function name with
inferMakeInstance and explicitly allocate concreteTypeQualifierTerm, the Ground
Self/Item bridges, groundedSelectedCalleeReturn and selectedCallableSubstitution.
Missing-term/binder recovery (nqjd) remains separate from selected associated
argument-context authority (fyxe). The three finite repairs and area/G1/D3/D4
dependencies were accepted, including the reopened selection area.

The review certifies this inventory and allocation, not any repair or final gate.
If nqjd requires a broad TypeInfo-caller redesign rather than these paired
producer migrations, follow the bounded-task policy instead of silently widening
it. The planned three repairs remain open until their own evidence/review closes.

## Scope Stop: Unassigned Late Synthetic Buffer Producer

At production **39c3e27f**, fresh phase3c-body-receivers-5
(SHA239e64e562ce4aceae76f222c5e2ec082eabc3b0f9f7f9915e44a01fd45972a3)
passes full compiler-source checking and all four module native controls. The
focused suite stops after its first success: associated_literal_signature_authority
fails compiling Core Buffer.new. The trace records actual Buffer[U64] decl0,
expected Buffer[U64] from selected Buffer declaration **53232**. This is not a surface
test error or a license to relax nominal equality.

The source is Lower/Types::synthBufferNew: its raw Buffer term is valid before
declaration facet resolution, but the same helper is called by
Record::elaborateDictionaryValues -> synthEmptyDict after that publication.
The late term flows through SyntheticCallSite.receiverTerm, saved signature,
both call worklists and final body admission without an owner. The C3 inventory
did not assign this early/late dual-use producer. Independent scope review by
/root/body_receiver_completion_review classifies this as a C3 task-disposition
omission, outside the implicitly permitted extra repair of registered body keys.

The user explicitly requires stopping when task omissions/errors are found.
No Buffer producer code fix or owner-recovery fallback has been added. The user
approved task addition: [com-qbwg](com-qbwg.md) now owns the finite early/late
producer repair, its native/internal controls and final-consumer trace. Required
tk dependencies connect it to fyxe, 6paa, the type-consumer area, D4 and G1.
C3 classification reconciliation is reviewed below; it does not depend on the
repair's implementation. fyxe and 6paa remain
in_progress, not completed. Task registration resolves the planning-approval
stop; it does not turn the retained failed fixture into passing evidence.

Durable receipt: meta evidence/existing-feature-conformance/source-owner-facts/
phase3c-receiver-producer-scope-stop.json. Raw failed focused-5 and
signature-trace-5 plus successful part-focused-5 remain under
compiler/tmp/phase3c-body-receivers. No current formal performance or full G2 gate
is claimed; the earlier **6.827440s** checkpoint remains distinct.

## Reclassification Outcome

Independent read-only review by /root/body_receiver_completion_review at
**4685fe20** compared the added inventory/repair disposition with production
39c3e27f. It confirmed all five callers: early beginStringInterpolation and
late synthEmptyDict keys/values/hashes/buckets. The Core provenance, saved
SyntheticCallSite receiver and complete signature, both worklists, body
environment/key/signature, final callee and Mid/LLVM reads are assigned to
mandatory com-qbwg with no remaining blocking classification finding.
**Classification and task allocation complete.** Existing bounded nqjd evidence
is retained; com-qbwg implementation, fyxe/6paa completion and final G2 gates
remain outstanding. This closes the inventory only, not the failed control.

## Scope Stop: Unassigned Pre-rewrite Optional-chain Producer

At **ce98f5f4** (production a2eda3bd), fresh
plewc-phase3c-synthetic-buffer-1 passes compiler-source checking, module native4
and the first **19** focused native cases, including both new Buffer controls
and associated_literal_signature_authority. The next case, optional_chain,
fails source checking with "source value does not satisfy the required
conversion"; remaining native22 and reject11 are unexecuted, not successful.
The focused and module input maps remain unchanged. On the identical source,
pre-Buffer fresh5 also fails and nqjd's fixed8e0f0329 succeeds. The Buffer
producer change is not the origin of this regression.

Independent read-only review by /root/body_receiver_completion_review finds
another missing C3 producer: Record::recordExpr(OptChain)'s pre-rewrite capture
calls ExprType::constructExprTypeWithChainHole -> Locals::optChainResultRef.
That helper rebuilds Optional[U] and a missing continuation ref with raw TypeRef
appends, then recordSemanticExprInfo saves the nonzero unowned term before
expected-result/conversion checking. The later chainStageResultRef and
registerChainSiteInsts paths assigned to nqjd cannot repair that earlier saved
source meaning. This is not an unused construction term or the registered body
key repair assigned to 6paa.

The review classifies this as a producer-allocation omission, outside qbwg and
6paa's finite repairs. C3 is reopened; no code change to optChainResultRef, type
equality relaxation or implicit scope extension has been made. nqjd's listed
producer changes and their historical scoped evidence stay valid, but they do
not certify this unassigned pre-rewrite source path. qbwg/fyxe/6paa stay
in_progress. User task-omission stop condition applies.

The user approved task addition: [com-i62n](com-i62n.md) now owns the pre-rewrite
chain source producer and paired saved-fact/conversion/rewritten-call readers,
including fresh scoped validation and independent completion review. Required
tk dependencies connect it to qbwg/fyxe/6paa closure, met-6e6k and G1. It depends
only on C3 classification, not on those repairs closing first. C3's added row
records this disposition; classification re-review is distinct from the new
task's unperformed implementation. The planning approval wait is resolved.

Durable receipt: meta evidence/existing-feature-conformance/source-owner-facts/
phase3c-synthetic-buffer-partial.json. Raw results stay under
compiler/tmp/phase3c-synthetic-buffer. Current formal performance/full G2 gates
have not run. This is another inventory stop, not phase-three completion.

### Optional-chain Reclassification Outcome

Independent read-only review by /root/body_receiver_completion_review inspected
the task-addition diff on **7af9781f** against the previously traced source path.
It confirms that the added inventory row and mandatory com-i62n own pre-rewrite
source-result production/storage, conversion/rewrite and final consumption;
nqjd/qbwg/6paa/C4/C5 retain distinct responsibilities. All targets/edges exist,
are acyclic, and block qbwg/fyxe/6paa, met-6e6k and G1 appropriately; D4's
existing prerequisites reach the new repair transitively.
**Classification and task allocation complete, no blocking findings.** C3
closes this reconciliation only. The new repair remains open, qbwg/fyxe/6paa
remain in_progress, and their actual implementation/control/review exits plus
final G2 gates remain required. No source/test/verification relaxation was made.


## Scope Stop: Unassigned Custom-factory Source Receiver

At production **7aeda7d5**, fixture checkpoint **38b33f37**, fresh2 SHA
**10adc2ca3603d4d4d2ad1842ef6854ceee16d853bd3e24fbf107f8e2c9f01a65**,
the standard build, full compiler source check and module native4 pass.
focused-3 passes native44 before a new internal fixture's absent diagnostic
anchor crashes. That internal fixture is corrected without weakening its missing
dependency checks. The closure tail passes the strengthened chain/projection,
receiver-dependency and Dictionary controls, then string_interpolation fails:
`body receiver does not match its selected declaration`, Options.factory at line5.
Remaining native7 and reject15 are unexecuted. No full scoped completion follows.

The read-only probe loads that exact source through normal File dependencies,
prepares main, and reads the saved Direct templates for callee0. Both already
contain receiver term14 with hasDecl=false, siteOffset=0, nameStart=533 and
assocNameLen=0. The final body check reports actual owner0 against selected
Options owner84. Thus the loss precedes BodyInstanceEnvironment and is not a
failure of 6paa's canonical key reader. Global's custom-factory preparation and
rewrite retain a separate synthetic receiver path; the old inferMakeInstance
inventory row did not cover it. For contextual `</>`, supplied `ty=context` can
also be incomplete. The exact first-loss branch is not yet proved and must not
be guessed from a raw fallback's mere existence.

Independent /root/body_receiver_completion_review confirms **task omission / new
source producer boundary**, not an assigned finalizer repair. C3 is reopened.
i62n/qbwg/fyxe/6paa remain in_progress; their valid partial controls remain evidence,
but no task is certified complete. Stop implementation under the bounded-task
policy before silently expanding any of them.

### Approved Finite Allocation

The user approved task correction after the independent source-producer review.
[com-uruz](com-uruz.md) owns first-loss tracing at the supplied context/custom-
factory construction boundary, complete receiver production, synthetic rewrite,
saved signature, both worklists and final consumption, with paired raw authority
removal and focused controls. Its concrete actions/exit are the single task plan.
It depends only on this classification; i62n/qbwg/fyxe/6paa, met-6e6k and G1
require it. D4 remains transitively blocked. No independent broader conformance
or body-key redesign has been silently included. nqjd's bounded closure remains.

Independent allocation review confirms the finite repair, distinct responsibilities,
all existing dependency targets, acyclic graph and D4 transitive prerequisite.
**C3 classification is complete; com-uruz implementation remains open.**
The evidence in meta
`evidence/existing-feature-conformance/source-owner-facts/phase3c-chain-factory-scope-stop.json`
remains a historical failure/probe receipt, not proof of the new repair. No
implementation or new execution validation is part of this task registration.


### Custom-factory Reclassification Outcome

Independent /root/body_receiver_completion_review reviewed the concrete task
registration against compiler base **072ece07**, including source evidence,
entry/first-loss investigation, producer-to-final-consumer exit, controls,
responsibility split and all dependency edges. Verdict: **appropriate task
allocation; classification complete; no blocking findings**. The new task has
only the classification prerequisite, and the interrupted repairs/area/G1 require
it without a cycle. This closes classification only; no implementation success,
fresh execution, final repair review or G2 gate is inferred. The four existing
repairs remain in_progress and the new repair remains open.
