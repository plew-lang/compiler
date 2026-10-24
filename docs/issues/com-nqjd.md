---
id: com-nqjd
status: closed
deps: [com-m0bf]
links: []
created: 2026-10-24T02:29:50Z
type: task
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, verification]
---
# Stamp late nominal source and synthetic type producers

Scope clarification: this closed task's listed production/reader changes and
historical controls remain valid. It does not certify every Chain source
producer: the unassigned pre-rewrite Locals::optChainResultRef path is now a
[C3 scope stop](com-m0bf.md#scope-stop-unassigned-pre-rewrite-optional-chain-producer).
Its disposition must be reconciled before claiming Chain-family/parent closure;
it is not silently added to this completed finite task. The approved separate
repair is [com-i62n](com-i62n.md).

## Boundary and Entry

Planned paired repair from [C3 inventory](com-m0bf.md#producer-and-reader-inventory),
not a new language feature. Parent criteria 1, 2, 3, 8. C3 classifies;
this task implements its late source/synthetic nominal producer boundary.

Entry: `Resolve/Expr::typedIrRefOfInfo`, `semanticCallableReturnTerm`,
`arrayRefOfElem`; `Resolve/Record::concreteTypeQualifierTerm`;
`Resolve/TypeRecovery::typeInfoOfName`;
`Mono/FreeFn::tyRefOfInfo`/`findOrAddTypeRef`;
`Resolve/ExprType::groundFinalMethodReturn`, `groundFinalMethodParameter`,
`boundMethodRetInfo`; `Mono/Call::groundedSelectedCalleeReturn`,
`chainStageResultRef`/`registerChainSiteInsts`.
Normal named constructions already preserve the selected declaration through
`inferMakeInstance`; do not replace that working path with name lookup.

## Finite Actions

1. Distinguish source nominal recovery from primitive/structural construction.
   A source nominal append after declaration publication must receive the already
   selected owner/complete term or resolve once in its explicit source domain at
   its producer. Use existing declaration APIs; do not globally stamp pushType
   rows by spelling or mutate a published declaration facet. A bare-name cache
   cannot select among unrelated declarations or bind a lexical ParamId.
   Include concreteTypeQualifierTerm: its resolved declaration branch is valid;
   its missing-identity branch may not publish a nominal receiver. Distinguish
   explicit primitive qualifiers from unresolved/foreign nominal names.
2. Preserve the canonical bundled Promise identity for async implicit Unit,
   and Optional/continuation identities for Chain-generated registration.
   Complete terms from child expressions stay complete through nested arrays,
   aliases and generic instances; do not rebuild them from a TypeInfo head.
3. Pair each migrated producer with its actual semantic fact, signature/scan and
   descriptor reads. Reject missing source identity at publication rather than
   reconstructing it downstream. Retire only the paired recovery calls; remaining
   registered-body key recovery belongs to com-6paa. Primitive leaves, Unit,
   function/record structures and rigid ParamId/projection terms need no invented
   nominal declaration.
   This task owns missing complete receiver/return term and lexical ParamId
   recovery, including ExprType adapters and groundedSelectedCalleeReturn. It
   must not attach a nominal owner to boundMethodRetInfo's lexical parameter.
   A missing annotated result is distinct from genuine omitted Unit. fyxe owns
   selecting/reading associated argument context, not these term constructors.

## Exit and Controls

Exact migrated/removal sites and producer -> fact -> explicit environment ->
final read recorded. Add positive alias/same-spelling declaration, nested array,
async implicit Unit and Chain continuation cases plus missing/wrong-owner
internal controls. Preserve already committed arguments and existing source
order/inference limits. Reuse `async_implicit_promise`, `mid_type_recipe_instances`,
`type_term_closedness`, namespace construction/identity and Chain controls.
A source passing now does not excuse an unstamped published nominal term.
Fresh source check/scoped native and rejection controls, pinned hashes and an
independent completion review are required. Global final gates remain G2.
General type-checker/ABI/inference redesign is outside this bounded task.

## Implementation and Reader Closure

Production is f95134ca. This closes the bounded producer boundary; the registered
receiver/body key and associated context readers remain com-6paa and com-fyxe.

| Producer | Saved authority and explicit environment | Final consumption |
|---|---|---|
| Decl::declaredTypeRef / langTypeRefAt, FreeFn::findOrAddTypeRef | Real nominal owner and full arity; canonical spelling is only a shape projection. Bare cache validates all facets and is keyed by resolved owner. Source adapters resolve in the source occurrence's module; synthetic carriers use the fixed Lang surface. | TypeRef/TypeTerm owner reaches expression facts, source signatures and instance type arguments. No global first-name nominal/ParamId reconstruction. |
| Record literal / sourceArrayTypeRef, ExprType index | Saved literal carries its fixed Lang owner; Array keeps the complete child term. Missing String/Array fails before publication. typedIrRefOfInfo no longer uses name-keyed arrayElems to invent a child. | Saved owner/body expression -> body type grounding -> final aggregate/index facts -> Mid operands and LLVM type use. Nested arrays of Leaf and an unrelated same-name lexical binder execute in the source control; distinct nominal owners are covered separately by the registered-owner and namespace controls. |
| semanticCallableReturnTerm | Implicit async returns Promise[structural Unit] with exact Lang owner; admission validates a missing carrier before call constraints. Omitted ordinary Unit remains an ordinary structural source value and an erased completed ABI result slot. | Declaration worklist callConstraintSubstitutionState/appendCallConstraintInstance and executable prepareFinalBodyRequest/scanFinalBodyInstance consume saved templates in explicit environments; groundedSelectedCalleeReturn is the selected bodyless signature reader. |
| ExprType bound/provided results | One staticMemberCallResultType/staticProvidedCallEnvironment retains the selected requirement/provided proof and receiver. groundFinalMethodReturn/Parameter defer a missing complete receiver; missing annotated results and qualifiers are not rewritten from spelling. | Recorded call result/signature -> source constraint checking -> explicit body signature/final call. Old first-bound/supertrait return-name traversal and traitMemberRetInfo/boundRetInfoOf are removed. |
| Chain continuation / Optional | chainStageResultRef preserves the full continuation term and rebuilds the original carrier with unchanged semantic facets; registerChainSiteInsts selects canonical Optional. | Same saved rewritten call and instance registration paths; no raw nominal append for a missing continuation. Existing optional/generic/multiparam/projected chains remain decisive controls. |

The unchanged terminal handoff is BodySignature -> completeStaticBodyCallee ->
CallResolution parameter/result terms -> Mid::instantiateCanonicalMidBody and
instantiateMidType -> Backend/Llvm/Mid preflight/emission. Mid reads body-specific
type results and final call signatures; it neither evaluates source recipes nor
performs another nominal lookup. arcFieldTy now requires the declared field term
rather than guessing an owner from the field's text.

Internal declaration clients now explicitly supply their minimal Promise/Lang
fixture. The existential async client uses SourceResource modules so ordinary
WorkerValue remains outside Lang. bare_type_registration keeps the original raw
index-order test directly through the arena index. New never-green fixture syntax
and minimal-environment mistakes were corrected without changing expected
language behavior. late_nominal_type_identity separates alias spelling
normalization from actual same-spelling owners: two registered StructDefs belong
to different registered module ranges, and complete terms must retain distinct
owners despite equal name IDs. Repeated queries must reuse each owner's term.

## Scoped Verification

Fresh candidate phase3c-late-nominal-2 is built by the standard immutable-input
build 20261024T031013-build-0d0187, exit 0, and checks the full compiler source
successfully. SHA256 b27d410681ba36e068609cb57b88e728564a45e738e5b3b0bf7cc4564933745e.
Target receipts cover normal 26, reject 9 (no internal diagnostics) and three
real-module alias/namespace native cases. The first five unchanged successes
from late-focused-7 and the remaining 21 plus rejects from late-focused-8 are
reconciled by exact applicable input hashes; only the intervening existential
fixture changed. Every run held its inputs fixed. Failed preparatory runs are
not success evidence. The meta evidence phase3c-late-nominal.json retains the
build receipt, source-check hashes, per-case input hashes and actual results.

The first static review found five production blockers: actual Record literals,
ref-less Array name reconstruction, missing ambient String/Array/Promise,
nominal kind/arity, and incomplete first-cache facet/stability handling. The
f95134ca rereview confirms those repairs and no further production blocker;
its same-spelling evidence concern is addressed by the registered-module and
fresh namespace controls. Independent final closure review by late_nominal_completion_review confirms the finite boundary complete with no blocking findings. It independently verified raw receipts, every applicable input hash, candidate hash, the same-name registered-owner regression, the repaired producer/removal sites and both-worklist/Mid/LLVM handoff. Two nonblocking trace-wording corrections are incorporated above. The formal checkpoint 20261024T032622-self-host-3988ef subsequently completed at generation 2, median 6.827440 seconds (7.446359 / 6.827440 / 6.777643), exit 0 with unchanged inputs. The meta evidence phase3c-late-nominal-self-host.json preserves its exact measured compiler hash and receipt. The scoped task is complete; final G2 all-suite gates and the parent remain open.
