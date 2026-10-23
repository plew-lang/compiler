---
id: met-ucze
status: in_progress
deps: [com-qehq, com-qb05, com-17yh]
links: []
created: 2026-10-13T01:40:08Z
type: epic
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, generics, verification]
---
# Unify source member selection without downstream reselection

## Contract

One source construction/selection owner commits the declaration or requirement,
lexical owner, receiver/evaluation inputs, full signature, substitution, result
recipe, conversions and evidence. Candidate probes may refine permitted unknowns;
Generic, Verify, Mono and final readers consume the committed result rather than
selecting another member. Shared lookup called repeatedly is not one authority.
Preserve source order, visibility, labels, ownership, bounds and ambiguity.
First concrete evidence for an already selected abstract requirement is legitimate
instantiation, not permission to choose a different source path.

Design: [Body Checking](../design/body-checking.md),
[Lookup](../design/name-lookup.md), [Frontend Handoffs](../design/frontend-handoffs.md).

## Current Boundary

Owner-local operation/constraint payloads, navigation-only indexes, saved static/
dynamic/operator/protocol templates and recorded-signature readers are implemented
increments. Static protocol operations retain selected requirements; the old
ProtocolSelection.Direct alternative and post-success storage-summary rewrite
were removed. Canonical iteration requirements and lexical provided-body ownership
remain semantic obligations. None of this certifies all remaining paths without
the child closure records below.

Auxiliary storage/access-demand analysis must not mutate a published source
operation. Keep its independent result and eager/demand access-analysis contrasts.
Pending source conversions finish before successful owner publication; final
readers cannot turn missing selection/evidence into presence-only acceptance.
Keep method/operator/protocol result projections and the same source provenance.

## Executable Work

- [B0](com-qehq.md): reconcile the eight actual paths and select residuals.
- [B1](com-qb05.md): ordinary/method/factory saved-selection closure.
- [B2](com-17yh.md): operator/protocol/iteration/try selected requirements.
- [B3](com-v2xk.md) under met-ia09 owns exact callee condition environments;
  [D3](com-wqa0.md) owns the final operation/constraint API write boundary.

Close this area after its required children/repairs and scoped fresh controls,
with producer/final-reader/removal locations per path. Retain matching successful
evidence from the [source-owner index](https://github.com/plew-lang/meta/blob/main/evidence/existing-feature-conformance/source-owner-facts/README.md).
The old sequential WIP/next/gate paragraphs are Git history, not current work.
Whole-candidate gates remain required by [G2a](com-p5um.md)/[G2b](com-9l3b.md)
before the parent closes; area closure alone is not release/seed readiness.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), [com-esri](com-esri.md): **Included repair** on existing
written/generic-bound/provided/operator/implicit calls. No new opening, unique
generics or protocol surface is introduced by this work.

## Current Eight-Path Reconciliation

[B0](com-qehq.md) inspected compiler **4c78bb38**, whose source and fixtures
still match **09e5a277**. The inventory is static; subsequent
[B1 closure](com-qb05.md#outcome) at **2d7e4d2f** adds fresh written-call
verification and removes the two competing signature decisions. B2–B4 and
other named boundaries remain independent required work. The receipt pins
inspected source and control hashes in
[the B0 evidence record](https://github.com/plew-lang/meta/blob/main/evidence/existing-feature-conformance/source-owner-facts/phase3b-call-path-inventory.json).
Function names below are navigation anchors; the receipt pins the exact input.

All eight rows use owner-local operations reached through `CallSiteKey` and
`callTemplateLocations`. `Check/CallConstraints.pw::callTemplateAt` reads the
owner payload; the session index is navigation. `Resolve/Expr.pw` closes source
selection through `checkCallTemplateSelection` and
`Check/Obligations.pw::prepareCallTemplateConstraints`; prepared constraint
plans are read through `preparedCallConstraints`. These are separate facts:
template presence is not source success, and source success is not a prepared
concrete callee.

The common static instance tail in `Mono/Call.pw` is
`selectedCallConstraintEvidence` → `enqueueSelectedCallee` →
`enqueueFinalBody` / `environmentWithCallableConstraints` →
`completeStaticBodyCallee`. The latter consumes a prepared `BodySignature`
(or the explicitly selected bodyless declaration environment), checks argument
conversions and source/carrier result projections, then publishes the final
`CallResolution`. `finalStaticCalleeIsComplete` is a downstream completeness
check, not a replacement for source signature/constraint admission.

| Path | Source producer and saved selection/result | Instance and final consumer | Replaced decision, current control, and remaining disposition |
|---|---|---|---|
| Ordinary free call | `Resolve/Record.pw::recordFreeCallExpression` selects with `resolvedCallee`, supplies selected parameter context, then `recordParametricFreeCall` / `Resolve/Expr.pw::recordSemanticExprCall` saves `Direct(callee, typeArgs, proofId, arguments)`, `SemanticExprType`, expected result and result recipe. `Generic.pw::checkRecordedDirectCallArguments` reads the selected declaration/substitution. | `Mono/Call.pw::resolveBodyCallee` → `selectDirectTemplateCall` grounds the saved source result and type arguments under `bodyEnvironment`; the common static tail supplies the real body and final descriptor. `Mid/Build.pw::buildMidCallEvaluation` preserves saved argument evaluation order; `Mid/Instantiate.pw::instantiateCanonicalCallTarget` maps the saved site to its final resolution; `Backend/Llvm/Mid.pw::midCanonicalEmitDirectCall` emits that target. | Mono no longer opens `Expr.Call` to choose a name. **At the pinned B0 input a competing source decision remained (now resolved by B1):** `Verify/Expr.pw::verifyExpr` calls `Verify/Call.pw::checkCallArgCategories`, which enumerates `visibleFreeFunctions` and checks a sole nongeneric candidate, skipping generic/overloaded sets. [B1](com-qb05.md) owns removing this path and proving selected-signature validation remains complete. Controls: `prepared_call_expression_source`, `source_call_constraint_evidence`, `source_call_proof_evidence`, `call_template_seal`; their presence does not prove this remaining path correct. |
| Method / explicit view | `recordExpr` Method/ExtMethod arms supply receiver/view and selected argument context, then `recordParametricMethodCall` saves a `Direct` declaration with the full method/impl substitution or `StaticMethod` with selected requirement/provided proof. `recordUnresolvedMethodTemplate` admits a justified static or dynamic target, rather than accepting candidate presence. `verifyRecordedMethodCall` and `checkSymbolicMethodArgs` read the selected target. | `resolveBodyCallee` dispatches Direct to `selectDirectTemplateCall`, StaticMethod to `selectStaticMethodTemplateCall`; the latter grounds the selected proof and finds the implementation of that exact requirement. The common static tail and the same Mid/direct LLVM readers consume it. | Name/view queries in Record construct the source selection; a first concrete witness for its retained requirement is instance work. Missing final templates are errors in `resolveBodyCallee`. [B1](com-qb05.md) still owns wrong label/type/receiver-passing and missing-template controls; [B3](com-v2xk.md) owns proof/clause/ParamId environment closure. Controls: `source_call_proof_boundary`, `source_call_proof_evidence`, `prepared_call_expression_source`. No blanket method closure is claimed. |
| Factory / default forwarding | `Resolve/Global.pw::prepareFactoryConstruction` chooses an anonymous factory or a canonical factory requirement and rewrites it to a method-shaped call with `SyntheticCallKind.Factory`; Record then uses the method selection boundary above. `Defaults.pw::recordDefaultArgumentCall` records an ordinary selected generator `Direct` call, retaining its lexical receiver/proof and distinct evaluation site. Pure memberwise/enum aggregates stay `SemanticAggregate` construction, not an imaginary callee. | Factory calls use Direct/StaticMethod grounding and the common static tail; `buildMidCallEvaluation` retains explicit-argument evaluation order followed by generated defaults, while the final resolution identifies the actual factory/generator body. Aggregate construction instead uses `preparedBodyAggregate` and Mid aggregate materialization. | No factory-name lookup is needed in final Mid/LLVM. Source rewriting and generation of selected default sites are legitimate construction, not downstream reselection. [B1](com-qb05.md) owns factory overload/label/type/ownership closure; [B3](com-v2xk.md) owns a provided/default generator's retained evidence; [D2](com-vkw3.md) owns its lexical source domain. Controls: `default_argument_call_templates`, `generic_constructor_field_width`, `call_template_seal`. The template fixture alone does not test all runtime default ordering. |
| Operator | `Resolve/Expr.pw::recordOperatorTemplate` saves operands, selected Direct/Static/Primitive `OperatorSelection`, source result and permitted operand context. `checkCallTemplateSelection` and source obligations validate the same operation; logical `&&`/`||` are completion/control-flow operations, not this callable family. | `Mono/Call.pw::recordBodyOperatorCallee` grounds operand sources and the saved selection, then uses the common static tail for callable operators. `BoolNot` / `OrderingTest` retain the source result projection. Mid instantiation maps the site to the final resolution; `Backend/Llvm/Mid.pw::midProjectCallResult` applies the saved projection after the carrier call. | Mono reads the selected operation rather than rerunning operator-name selection. **Residual proof/control:** `recordBodyOperatorCallee` still synthesizes Bool for an absent saved ordering result, and has additional zero-result fallbacks. [B2](com-17yh.md), coordinated with [C4](com-e9l2.md), must distinguish permitted construction-only absence from a missing mandatory result and remove migrated recovery where required. Controls: `generic_closure_operator_bound`, `source_call_proof_boundary`, operator projection fixtures. This inventory does not call every fallback a reproduced bug. |
| Protocol / iteration | `Record.pw` For arm calls `Resolve/Expr.pw::recordProtocolCallTemplate` with canonical Core Iterable/Iterator requirements. Slot 1 is iterator (or explicit Identity fallback); slot 2 is next with `PriorProtocolResult(1)`. The saved operation retains Static/Existential/Identity selection and result; `recordForItemTypeRecipe` / `sourceForItemTerm` retain the selected next payload. | `Mono/Call.pw::scanStmtInsts` consumes `protocolTemplateForCurrentBody`, `groundedProtocolTemplateReceiver`, `selectedProtocolTemplateCall`; selected static calls enter the common tail. `Mid/Build.pw::buildMidFor` uses the saved iterator/next/item recipes and protocol slots; `instantiateCanonicalCallTarget` maps slots to final resolutions. Direct or existential LLVM emission consumes them. | `ProtocolSelection.Direct` is absent from the enum and its source/consumer branches. Identity means the selected Iterator receiver itself; it does not admit arbitrary same-named structural `next`. [B2](com-17yh.md) owns confirming conditional applicability, exact canonical requirements, bounds and Item/result projections. Controls: `generic_closure_iteration_bound`, `source_operation_owner_storage`, existing structural-next and ambiguity rejects. |
| Try | `Resolve/Expr.pw::recordTryExpression` saves `SemanticTry` (Result declaration/variant identities, operand/return/success/error terms). Unequal errors select the canonical Core From requirement as a StaticMethod template at slot 1 with its proof and source error argument. Equal errors require no conversion call. | `Mono/Call.pw::registerTryConversion` reads `preparedBodyTry`, grounds its saved terms and slot-1 selection, and saves `FinalTryResolution.errorConversionResolution`. `Mid/Build.pw::materializeMidTry` consumes the decomposition; `instantiateCanonicalCallTarget` resolves the TryConversion target through that final receipt; LLVM emits the already selected conversion. | Missing decomposition/template/final conversion is an error. There is no final `from` factory search from Result spelling. [B2](com-17yh.md) owns same-error, differing-error, missing/wrong From evidence and final cleanup/result contrasts. Control: `prepared_try_source_owner`; static/corrupt evidence controls also exercise the common admission boundary, not the entire try execution. |
| Inherited / provided adapter | `recordParametricMethodCall` retains trait-subject Requirement/Provided proof rather than an incidental copied concrete witness; Direct stores its selected proof too. `Resolve/Expr.pw::recordStaticMethodTemplate` preserves the source method substitution/result. Public requirement clauses and retained implementation entailment remain separately identified. | `selectStaticMethodTemplateCall`, `selectedMemberConstraintEvidence` / `requirementCallConstraintEvidence`, `Check/Bounds.pw::instantiateRequirementCallConstraints` and `environmentWithCallableConstraints` feed the real callee. `Mono/Newtype.pw::inheritedBodyEnvironment` interprets logical versus physical Self; `finalizeNewtypeAdapter` publishes a generated final call to the original body. `Mid/Build.pw::buildMidBodyForInstance` consumes both signatures/that edge; LLVM emits the final descriptor. | This is same-declaration realization, not overload lookup. `selectDirectTemplateCall` still has a missing-provided-proof completion via `providedBodyProof`; [B3](com-v2xk.md) must prove its admitted domain or close the missing producer fact, not certify it from the comment. B3 owns clause IDs, method ParamId map, two-layer Self and both worklists. Controls: `retained_provided_body_constraints`, `retained_associated_constraint_evidence`, `existential_newtype_condition_witness`. |
| Dynamic / interface | `Record.pw::recordDynamicLocalCall` saves binding identity and function term; `recordDynamicMethodCall` saves a field index/function term or existential trait/requirement slot. `Resolve/Expr.pw::recordDynamicCallTemplate` retains arguments and interface root; source admission validates the selected callable signature/evidence. | `Mono/Call.pw::selectDynamicTemplateCall` grounds the retained target, and `recordSelectedBodyCallee` publishes its dynamic signature/conversions. `Mono/InterfaceEvidence.pw::instantiateInterfaceCall` and `checkFinalInterfaceEvidence` interpret retained roots; boxing/witness finalization consumes the admitted member plan. The same Mid saved-site lookup feeds `Backend/Llvm/Mid.pw::midCanonicalEmitClosureCall` / `midCanonicalEmitExistentialCall`. | No late local/field/name lookup replaces the saved dynamic target. [B4](com-yojf.md) owns universal versus concrete proof admission (hidden nominal arguments, conditional/associated/supertrait roots); [B3](com-v2xk.md) owns executable witness environments; [C6](com-3q2n.md) owns complete descriptor dependency closure. Controls: `dynamic_call_template_generic_instances`, `interface_declared_guarantees`, `interface_final_evidence`, `interface_boxing_conditions`. These do not establish stronger universal nominal proof by themselves. |

### Reconciled Removal and Verification Boundary

The old blanket claims about a second Record pass, a final written-call AST
selector and `ProtocolSelection.Direct` are not outstanding rewrite requests:
the inspected current paths already record once and materialize saved selections.
`resolveBodyCallee` rejects a missing written selection, and the inspected final
Mid/LLVM call consumers use saved site/resolution IDs. Do not reimplement those
already migrated parts.

At the pinned B0 input, the free-call Verify rescan was live code rather than
an obsolete checkpoint.
It was the concrete B1 change, now removed with scoped evidence in
[B1](com-qb05.md#outcome), together with the Dictionary label type override. The result and provided-proof fallbacks above
are named closure questions for B2/C4 and B3, respectively, not source-correctness
claims. Operation writer sealing belongs to [D3](com-wqa0.md), and universal
interface admission remains B4. Each residual has an existing mandatory owner;
this inventory needs no anonymous new repair bucket.

No compiler/test/performance process was run for B0. The prior f67c8fce normal
suite is historical coverage of the starting controls, not fresh evidence for
09e5a277 or a source-to-final proof. B1–B4 retain their fresh positive/reject/
corruption and final-consumer requirements, and G2a/G2b retain all final gates.
