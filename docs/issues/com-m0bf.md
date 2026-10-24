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

Each hit is tied to one of the four entry families, a canonical producer or a legitimate construction-only representation, exact fallback consumers and current controls. No unclassified source nominal hit remains. For each real gap create a paired producer-plus-reader repair child with exact API/fixtures and make it mandatory; do not delete all spelling fallbacks at once. This inventory closes classification, not unperformed repairs.

Existing starting controls: `mid_type_recipe_instances`, `type_term_closedness`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.

## Producer and Reader Inventory

Inspected production code at **c056e658** (documentation checkpoint e6ef8918).
The finite four-family inventory below classifies every direct TypeRef append
and named-recovery adapter reachable from the listed entries. Rebuild/view/
substitution helpers preserve existing identity; they are not new spelling
producers. Classification is not the completion of the paired repairs.

| Entry family / producer | Representation and status | Paired reads / disposition |
| --- | --- | --- |
| Named source construction: `Expr::inferMakeInstance` | Preserves selected existing TypeRef or stamps the selected nominal declaration before recording. | Semantic aggregate/expression -> body grounding -> Mid aggregate. Already canonical; no replacement lookup. |
| Array construction: `Expr::arrayRefOfElem` | Retains full element and canonical Lang Array identity where available. `typedIrRefOfInfo`'s name-only element recovery remains distinct. | Published expression/aggregate and generic arguments; canonical main path preserved, legacy adapter assigned nqjd. |
| Source TypeInfo adapters: `TypeRecovery::typeInfoOfName`; `Expr::typedIrRefOfInfo`; `FreeFn::tyRefOfInfo`/`findOrAddTypeRef` | Primitive/unknown compatibility descriptions are legitimate during construction. An ordinary nominal recovered only via global firstBareTypeNamed or a new name-only append lacks owner/binder authority. | `recordSemanticExprInfo`, body type recovery, grounding and final signature completeness; mandatory repair nqjd. No global name-id stamping. |
| Body signatures: `Expr::semanticCallableReturnTerm` | Existing lowered return terms retain identity. Unit is a structural empty record. Async omitted return creates an unstamped Promise[Unit] after declaration publication. | CallTemplate result, body signatures and final descriptor grounding; mandatory nqjd. `Call::groundedSelectedCalleeReturn` also has a retTy=0 to simpleTypeRef adapter assigned to nqjd (keep genuine omitted Unit distinct from a missing annotated return). Promise name-collision source control currently passes, so no source-level failure is claimed from this observation alone. |
| Associated type qualifier: `Record::concreteTypeQualifierTerm` | Direct append after `typeDeclIdentityAt`, with conditional hasDecl. The resolved branch is canonical; the missing branch must remain construction-only or be rejected before saving a selected receiver. | `methodReceiverTerm`, `directReceiverTemplateForExpr`, Check/Call and ExprType. nqjd must explicitly verify/seal the missing branch rather than classify every qualifier as already canonical. |
| Associated function inference: `ExprType::associatedReceiverFromArguments`, `groundFinalMethodSignatureTerm` | Existing recvTy, signature terms and simultaneous explicit environment preserve identity. `groundFinalMethodReturn`/Parameter's missing-ref path and boundMethodRetInfo still accept a name-only receiver. | Saved signature and selected call term; missing complete term/lexical binder recovery is nqjd, registered receiver/key migration is 6paa; saved associated parameter context selection is fyxe. boundMethodRetInfo can represent a lexical ParamId, so do not stamp it as a same-spelled nominal type. Keep the correct full-term lane. |
| Associated literal context: `Literal::checkAssocArgsLitCtxFromExpected` via `checkLitSpanCtx` | No direct nominal append. A competing name lookup/inferFnArgs plus positional ctx.args -> f.typeParams map remains; callers exist in Record, Generic and Verify. It cannot be classified as a universally preselection-only adapter. | Full selected parameter context and literal checking -> saved source call -> final call; mandatory fyxe. Do not replace one missing-owner term with another lookup in a final reader. |
| Registered receiver: `Call::canonicalBodyReceiverRef`, `selectedCallableSubstitution`; fallback `Record::parametricSelfRef` | Missing explicit receiver is reconstructed by simpleTypeRef even when Func.recvTy is complete; selectedCallableSubstitution similarly reconstructs its receiver instead of preserving the declaration term. ParametricSelfRef's main recvTy lane is correct; fallback rebuilds type parameters without ParamId and the nominal head without owner. | internBodyInstance -> body signature / final callable / Mid lookup. Internal diagnostic confirms identity loss and mixed known/unknown key equivalence; mandatory 6paa. |
| Body/signature Self bridges: `Ground::assocItemRef`, `setSelfItemEnv`, `setSelfItemEnvForBody` | simpleTypeRef still rebuilds a receiver when recvInstRef is absent. `collectDeclarationTypes` can take this lane even when f.recvTy exists. | Declaration signature collection and Call final body environment, then recorded/body types. Assigned to 6paa together with parametricSelfRef and canonicalBodyReceiverRef; preserve the valid retained Item/proof environment. |
| Chain-generated registration: `Call::chainStageResultRef`, `registerChainSiteInsts` | Existing head rebuild retains identity. Missing continuation ref appends a naked nominal name; Optional[V/U] registrations also omit owner. | scanType, chain result/rewritten call facts, worklist registration -> final descriptors; mandatory nqjd. |
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
