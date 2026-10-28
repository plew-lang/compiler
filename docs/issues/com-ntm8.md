---
id: com-ntm8
status: open
deps: []
links: []
created: 2026-10-27T19:08:00Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, diagnostics, verification]
---
# Strengthen scoped frontend rejection reasons and arity path controls

## Contract and Evidence

Scoped review F2 lists nine no-reason negatives; F3 generic_arity_construction also contains invalid annotation, so annotation rejection could mask construction handling; F4 test-check-command unused-type-error/global-conflict compare same generic errors across modes without intended reasons.

Contract: tests/README.md Test validity and coverage review and docs/design/verification.md. Scoped evidence: [F2,F3,F4](../../../evidence/test-audit/scoped-reviews/review-frontend.json); controlled driver observations and runtime controls reside alongside it. Audit did not modify compiler, fixtures, expectations or runners.

## Scope and Completion

For exactly F2 nine inputs, F3 construction/annotation pair and F4 two generated cases, verify original intent and isolate intended source rule with meaningful reason and neighboring positives. Preserve driver check/build agreement and no-execution checks. Separate shared classification com-fsuq; no arbitrary rewrite of every absent .err or new unsupported feature.

Repair requires task-start TDD, fixed candidate/input identity, relevant actual consumer checks, scoped independent review and applicable gates. This is a separately owned follow-up, not a child or dependency of com-jno0 or its audits. No phase-three certification implied.

## Explicit Part/Identity Control Extension

The later part outcome audit independently read four additional rejection
controls that have no diagnostic companion:

- `tests/fixtures/partreject/trait_view_unimported/Main.pw`
- `tests/fixtures/partreject/trait_owner_required_identity/Main.pw`
- `tests/fixtures/partreject/phantomdep/Main.pw`
- `tests/fixtures/reject/trait_subject_cycle_generic_edge_reuse.pw`

Include these exact four reason assertions alongside the original nine, not
the entire absent-.err corpus. They must distinguish missing explicit selector
binding, the actually selected trait's missing requirement, missing direct
dependency, and exact-instance cycle respectively. `phantomdep` also has legacy
manifest setup; com-7u8z must resolve the relevant canonical schema before using
that setup as a diagnostic oracle. A manifest parse/version failure is not its
intended rejection. Original intent and companion positive controls are recorded
in meta/evidence/test-audit/scoped-reviews/part-tail-0087.json. These were source
reads, not observed current-candidate reasons. Shared exit/internal-failure
classification remains com-fsuq, and audit repair remains separate.

## Explicit Part-Diamond Reason Control

Source-admission batch0003 independently reads exactly `tests/fixtures/partreject/partdiamond/{Main,A,B,C}.pw` as the paired root/part control. Main imports print but calls `print(1)` without a numeric type context and has no Main.err. The loader currently rejects the repeated part parent first; if that check regresses, forward-only numeric inference can still reject the bare literal, so generic rejection is insufficient evidence of diamond detection. Isolate the diamond reason and keep the single-parent positive. This adds one exact control to the existing finite diagnostic work, not the unread partreject corpus. No fixture was run or repaired.

## Explicit Two Visibility-Reason Controls

Batch0005 adds exactly `tests/fixtures/partreject/crossmoduleprivate/{Main,Pub,Priv}.pw` and `tests/fixtures/partreject/crossmoduleprivateglobal/{Main,Gl}.pw`. Both Main files use `print(value: ...)` while the selected Std print has an unlabeled parameter. Neither has Main.err. Even if visibility protection regresses, unrelated outer-call label rejection can still satisfy the generic rejection worker. Recover and preserve the original cross-module private callable/global isolation, isolate intended diagnostics, and use valid outer contexts with reachable public positives. No actual candidate or controlled execution is claimed. This exact five-file extension is separate from common failure classification and the unread no-reason corpus.

## Explicit Two Part-Structure Masking Controls

Batch0006 adds exactly partreject/partmissing/Main.pw and partreject/partcrossmodule/{Main,Other,Shared}.pw. partmissing has bare print(1) without numeric context, so rejection can persist if missing-part discovery is incorrectly skipped. partcrossmodule's Shared impl Z is also unbound in Other's module if shared membership is incorrectly allowed. Both lack Main.err. Isolate missing input and unique part membership reasons while preserving valid neighbor controls.

partfreefn was also read, but removing its intended part-only-impl restriction leaves a well-typed I64 triple. Missing diagnostic text alone is not a demonstrated competing-failure setup. Its reason coverage is optional, not a newly required fixture repair or a duplicate of shared com-fsuq classification.

## Explicit Arithmetic Rejection Setup

Batch0008 adds exactly tests/fixtures/reject/arith_no_trait.pw. It intends Add-unimplemented rejection for Pt, but has no .err and also writes malformed postfix `print(c.x~)` without importing print. Even if the Add check is missing, syntax/name failure can still pass the generic rejection predicate. Recover the original arithmetic-trait purpose, remove unrelated failure from the eventual scoped test and distinguish a valid Add-conforming control. Missing memberwise factory is not a defect here: same-module default construction is legal. No compiler/test modification occurred in audit.

## Explicit Chain Diagnostic-Anchor Regression

Batch0010 adds exactly tests/fixtures/reject/chain_value_type_mismatch.pw. Original path-fixed3d5bd4ec introduced it to ensure the synthetic optional-chain error points to the real ?.n token. The worker has no .err/reason/location assertion, so it cannot detect that original anchor regression. Moreover `use @Std/Core` binds namespace Core, not bare Chain used in its impl, and root Some(v=...) differs from the adopted payload label. Missing trait binding or label setup can reject before the intended continuation check.

Preserve the real source-offset assertion and intended failure class through an explicitly valid setup. Canonical inference of the output carrier is a separate finite question; do not guess a mismatch diagnostic from current lowering or freeze a guessed language rule to repair the test. met-2wca owns label migration; the new carrier question is separately named by the batch report. No arbitrary all-no-.err rewrite or compiler/fixture repair in audit.

## Explicit Nonassociative Comparison Detection

Batch0011 adds exactly tests/fixtures/reject/cmp_non_associative.pw. Its I64 a==b==c has no diagnostic companion: if the parser incorrectly groups left-associatively, the intermediate Bool is still compared to I64 and can fail for a different reason. Thus exit1 alone does not detect the intended nonassociative syntax rule. Preserve original d4a7a247 intent with a discriminating parser reason or a well-typed Bool chain contrast and valid explicitly parenthesized control. No observed compiler regression is claimed; shared crash classification remains com-fsuq.

## Explicit Two Empty-Match Rejection Controls

Batch0013 adds reject/empty_match_bool.pw and empty_match_unit.pw. Original ca23b3dd protects the rule that inhabited Bool/unit cannot have exhaustive zero-arm matches. Both instead return match value {} and have no .err: if coverage wrongly accepts zero arms, the match is classified source-diverging and its use as a return value can still reject. Isolate coverage from forbidden source-divergence value use with statement/branch context or a precise coverage reason; retain a genuinely empty enum elimination positive and rejected empty-enum direct value-use contrast. No observed candidate defect or new Never/type rule is claimed.

## Explicit Floating, Named-Value and Field-Anchor Controls

Batch0015 adds exactly reject/float_remainder.pw, fn_value_sig_binding.pw and field_typo_read.pw/.err. float_remainder uses two unsuffixed decimal literals inside generic print, so an erroneous floating % implementation can still leave ambiguous F32/F64 inference and satisfy exit1. Preserve original63b9b302 no-float-remainder intent using typed operands/context and valid integer/float-arithmetic contrasts.

fn_value_sig_binding originated5503b46f as function-signature incompatibility, but current comment instead protects named declarations not being values. The input still also mismatches I64 and String function signatures, so generic rejection cannot isolate that newer non-value rule. Recover both purposes and reuse existing named_fn_value_{untyped,field,arg,return} negatives plus the explicit fn_value closure-wrapper positive. They already isolate the non-value boundary; this root alone has weak discrimination, not a confirmed suite-wide coverage hole. Treat its reason/comment precision or deletion as optional after checking old signature coverage, avoiding redundant new tests.

field_typo_read originated3d5bd4ec to anchor .typo at the actual source token. Its specific message companion detects missing-field reason but not location, and no separate selected consumer was found by script/checker search. Retain message and add an actual path/line/token anchor assertion through the standard compiler diagnostics path; do not equate generic rejection with source-span verification. This exact three-root extension does not rewrite all missing companions, public FFI rules or unread span tests.

## Explicit Foreign-Declaration Label Boundary

Batch0015 also adds exactly reject/ffi_extern_c_label.pw. It intends to reject C declarations lacking explicit ~: suppression, but main invokes those labeled a:/b: parameters positionally. If declaration admission incorrectly permits labels while preserving them, ordinary call-label mismatch still yields exit1 and masks the declaration-boundary defect. Original72b7df2e requires explicit suppression rather than silently stripping labels. Isolate declaration rejection or require its exact reason, preserving a valid explicitly suppressed C declaration/call and ordinary labeled wrapper contrast. No blanket FFI change or actual compiler failure is claimed.

## Explicit Generic Factory Call-Syntax Context

Batch0017 reads exactly reject/generic_factory_requires_construction.pw/.err. The declared generic build body incorrectly calls a factory as T.make rather than JSX, and the companion pins that specific reason. Main also uses build[Value](), a retained unimplemented explicit free-call type-argument form documented by com-uutc. Preserve the intended body/call-kind rejection independently of that unsupported caller syntax, using the normal unused generic-body checking contract or another supported caller context. Do not require implementing the unrelated explicit-call feature just to isolate this regression, or credit its generic unsupported-form diagnostic as the specific factory reason. No current candidate was executed and no wrong-error PASS is proved by the companion.

## Explicit Source-Transfer and Newtype Declaration Controls

Batch0018 adds reject/give_result_before_return.pw: original e607bd5b checks give-result Array[String] versus [1I64], but a following return is now independently forbidden by the adopted source-transfer rule. Isolate block-result typing from that already-invalid suffix; preserve separate source-after-give rejection. No current candidate failure is claimed.

The read reject/give_unreachable_name.pw originated a73b1528 to catch an unknown name in an unreachable suffix. Since any code after give is now forbidden, it no longer discriminates unreachable-name checking. Its valid rejection can be retained/reclassified or removed as redundant after checking explicit source-transfer controls; this is optional purpose precision, not a demand for diagnostic recovery after the first error.

Batch0018 also adds reject/impl_on_newtype.pw. Original b27eeae5 intended the prohibition on user impls for newtypes. Main calls print without importing ordinary Std/Io, so an unrelated missing-name rejection can mask loss of the impl gate under adopted lookup. Preserve the declaration-only ban and valid inherited-method/as contrast using an isolated reason/input; do not make newtype methods user-definable or infer a language exception from current acceptance. These are exactly three inspected roots, not all give/newtype tests.

## Explicit Inline-Constraint Reason Isolation

Batch0019 adds reject/inline_trait_constraint.pw. Its original f81f8480 selected adding diff intended to catch silently discarded inline [T: Show] constraints. Show is undeclared/unimported and no .err is required: a different regression accepting inline constraints normally can still fail on Show lookup. Isolate the forbidden syntax with a valid local/imported trait or an appropriate diagnostic assertion, while retaining the original silent-drop regression intent. No blanket requirement for every missing .err is implied.

## Explicit Match Identity and Duplicate-Field Isolation

Batch0020 adds reject/match_unknown_variant.pw and match_pattern_dup_field.pw. The former constructs current Some(v=...), so an adopted-label error can reject even if unknown variant Other is accepted; keep the unknown-variant oracle distinct during met-2wca migration. The latter repeats field a and omits b: current checkDestructureComplete separately rejects duplicates and then missing fields. Removing duplicate detection alone still rejects for missing b. Preserve the original8978934c exactly-once regression, using a duplicate-specific assertion or a form covering all real fields as well as duplicating one. This does not require every pattern error to be independently diagnosed after the first failure.

## Explicit Type-View Rejection Isolation

Batch0021 adds reject/multiple_trait_type_view.pw. It writes both an illegal Sample#A#B annotation and the same illegal sample#A#B value. Current checkTypeViewSources and checkResolvedViewValid enforce these through separate type/value readers; losing the type-only gate can still reject at the RHS. Preserve the single-trait selector contract with a genuinely type-only input or type-specific diagnostic. The existing multiple_trait_value_view is the separate value-only contrast. This is a selected finite detection gap, not a reproduced compiler bug or a general demand for duplicated tests.

## Explicit Or-Pattern Legacy Setup Reclassification

Batch0022 adds reject/or_pattern_bind_mismatch.pw for optional purpose/setup disposition. Legacy enum payload braces can reject before the intended unequal-binding names. The same batch's canonical or_pattern_binding_names.pw/.err already isolates that rule with typed constant body and specific diagnostic. Recover original a4ef7a08 intent before retaining/migrating/reclassifying/removing the redundant old root; do not require another duplicate mandatory test or treat the stale brace form as adopted.

## Explicit Equality and Floating-Range Reason Isolation

Batch0023 adds reject/payload_enum_eq.pw and range_float_iterator.pw. The first originally2428a6fa guarded payload-enum equality without Eq, but unimported ordinary print can still reject if the Eq gate regresses. The second originally5303254e guarded the absence of Step on floating types, but both floating endpoints lack type context and its bare for value refers to no existing mutable binding (spec11:209); these failures can mask Step/Iterable admission. Establish explicit floating endpoint type and a legitimate loop binding while preserving the non-Step rejection, paired with range.contains and integer iteration contrasts.

The supplemental run/range_iterator_values.pw/.out has five bare for value loops with no prior mutable value binding. Preserve its six output lines, signed traversal, singleton maximum, repeated exhausted next and empty-range termination with valid new/previously mutable loop bindings. This exact positive setup pair belongs to the same finite iterator-oracle repair, not an all-for migration or a new language rule. No fixture was run or edited by the audit.

## Explicit Publication Visibility and Source-Anchor Checks

Batch0024 adds reject/selected_call_constraints_publication_private.pw/.err. Its outer publishPreparedCallConstraints and nested admitSelectedCallConstraints are independently private and share the same expected method-private text. Publishing only the outer method can still pass via inner rejection. Isolate publication using an external helper parameter of the already-public AdmittedCallConstraints type, without exposing its factory or skipping real admission. The inner admission gate has its own existing exact negative.

Also add record_lit_destructure_bad_field.pw and ref_arrow_missing_field.pw/.err to the finite source-anchor scope. Original108951ff and3d5bd4ec moved diagnostic provenance from interned names to actual bind/field tokens; current workers observe no location (first status-only, second message-only). Preserve the selected field/bind location contracts through a meaningful assertion or existing diagnostic checker; reference syntax migration remains met-op15.

return_unreachable_type.pw now violates the source-after-return rule before its old dead-type purpose. This is optional purpose reclassification/retention/deletion after original intent, like give_unreachable_name; do not require continued diagnostics after decisive forbidden suffix rejection.

## Explicit Generic-Payload Label Masking and Unknown-Pattern Purpose

Batch0027 adds exactly reject/tc_generic_arg_mismatch.pw and tc_generic_payload_value.pw. Both use Some(v=...) while adopted Optional declares value. Status-only rejection can survive a lost generic-instance/payload-type gate through unrelated wrong-label rejection. Original6541be59/cf3e07e4 intent is generic argument identity versus expected payload substitution, respectively. Isolate both under coherent met-2wca migration with positive grounded payload controls.

struct_pattern_type_mismatch.pw uses undeclared P, but original539c37a8 deliberately covers unknown/nonstruct pattern crash-to-clean rejection. Keep that original guarantee; a known-struct/wrong-subject contrast or precise reason is optional coverage, not a newly proved mandatory mask merely because P is absent.

## Explicit Optional-Try Rejection and Dead-Operator Purposes

Batch0030 adds exactly reject/try_on_optional.pw. Some(v=...) can reject for an unrelated adopted payload-label failure if the intended Result-only try gate regresses; preserve actual Optional versus Result early-return semantics through met-2wca migration and selected reason.

The exact type_operator_reject_dead_{block_59,if_68,match_77}.pw and type_operator_return_dead_invalid_add.pw originally799bc300 check bad operators after a transfer. Adopted spec11 now forbids every such source suffix. Reclassify/retain/delete their optional old purpose without demanding additional operator diagnostics after the decisive transfer error. Live-invalid operator control stays meaningful.

The fully read supplemental run/source_operator_literal_context.pw/.out has two bare for operation loops without an existing mutable binding (spec11). Preserve closed first-source operator selection, contextual operands, refusal to repair missing frozen selection and comparison Bool projection through valid loop bindings. This is one exact positive setup pair, not an all-for migration; no fixture was executed or edited.

## Explicit Enum-Deinit Rejection and Unique-Return Control

Batch0031 adds exactly reject/unique_enum_deinit.pw. It intends to reject explicit enum deinit but its Cell struct also contains a forbidden struct-body deinit (spec03); with status-only expectation, losing enum rejection can still pass on unrelated placement error. Preserve enum-specific rejection with an admitted payload declaration under met-2t3l migration.

Supplemental run/unique_move.pw/.out also returns the existing local f bare from makeFile and describes implicit move. spec03 requires explicit ownership mode and has no located local-return exception; spec04 return completion does not grant it. Preserve the four ownership/output events through adopted explicit transfer and coherent deinit migration rather than certifying this old positive as source-clean. This is one exact control, not all unique return bodies or an added implicit-move rule.

## Explicit Local-Type Visibility and Missing-Give Isolation

Batch0033 adds exactly reject/use_type_without_import_localval.pw. Its initializer is the undeclared identifier none, not <Optional.None />. If the Tok local-annotation visibility gate regresses, unknown none can still keep this status-only negative passing. Preserve local annotation visibility with an admitted Optional empty initializer and selected reason. Tok and kindCode exist in the pinned Syntax source, so this is not absence of the external declaration; the parameter/newtype sibling negatives have no located independent setup mask.

Also add value_if_no_give.pw and value_match_no_give.pw for their intended missing-give reason isolation. Both contain unsuffixed discarded integer expressions without a local type; source Literal/Record walks retain a no-context numeric failure independently of the give requirement. Originalcebb4528 explicitly describes this alternative error. Keep distinct if-branch and match-block coverage through a typed/suffixed payload or selected diagnostic, preserving no implicit tail value. This is static detection analysis, not an executed checker mutation or a demand for extra diagnostics after decisive rejection.

## Explicit Four Array and Associated-Name Loop Controls

Batch0036 adds exactly run/{array_literal_inferred_element,array_literal_unannotated_let,array_method_result_chain,assoc_type_name_collision}.pw/.out. Each uses a bare for binding without an existing mutable target. spec11 requires val/mut val for a new binding; bare spelling assigns an already mutable binding. Preserve grounded generic/enum array inference, module-level arrays, source-recorded local array type, whole array call-result chaining and associated-name lexical identity through admitted loop setup. This is four exact positive controls under the existing finite loop-oracle scope, not an all-for migration or new inference/iteration rule.

## Explicit Associated-Body and Signature-Authority Loop Controls

Batch0037 adds exactly run/{associated_copy_body_environment,associated_literal_signature_authority}.pw/.out. Their bare for previous/mode names have no existing mutable binding. Preserve A/B placement body identity, selected-proof receiver rejection and physical self-signature checks, plus unselected/complete/incomplete/wrong-callee/no-reconstruction signature cases, through adopted val/mut val loop declarations. Each root has separate source-admission and internal-output obligations; migration scope counts roots once and does not certify current execution.

## Explicit Receiver-Identity Loop Setup

Batch0038 adds exactly run/body_receiver_declaration_identity.pw/.out. Bare for offset/byte have no earlier mutable targets. Preserve same-spelled cross-module declaration rejection, supplied/default receiver body identity, missing/foreign receiver and signature failures, and nested resolved-view provenance under valid val/mut val loop setup. The two source/result obligations share one root; no codegen execution or blanket internal test rewrite is claimed.

## Explicit Callable-Form Source Identity Loop Setup

Batch0039 adds exactly run/callable_form_source_identity.pw/.out. Bare for index/candidate do not declare new bindings and have no earlier mutable targets. Preserve authored implementation identity across normalized default callable forms, foreign declaration/conformance/type-argument/receiver rejection and duplicate source-conformance checks with valid explicit loop declarations. Outcome and admission are separate obligations, not two migration roots.

## Explicit Chain and Closure Loop Setup

Batch0040 adds exactly run/{chain_source_type_identity,closure_array_for_arc,closure_descriptor_identity}.pw/.out. The first has bare for name/site/conversion and the latter roots bare f/body, all without earlier mutable targets. Preserve chain owner/projection/foreign-body identity, closure-element call/ARC source purpose and descriptor/body-environment negative controls using explicit val/mut val new bindings. Source-only descriptor/ARC outcomes are not newly credited.

## Explicit Session and Proof Loop Setup

Batch0041 adds exactly run/{compiler_session_body_requests,compiler_session_mid_requests,conformance_proof_demands,conformance_proof_outputs}.pw/.out. Their bare loops (3,1,1,3 sites respectively) have no earlier mutable target. Preserve selected body/declaration request, prepared Mid reuse, explicit proof source paths and output/premise query controls using val/mut val declarations. No all-session rewrite or additional outcome credit follows from this source setup intake.

## Explicit Conversion Codec Loop Setup

Batch0042 adds exactly run/conversion_proof_freeze_roundtrip.pw/.out. Bare for payload has no previous mutable target. Use an explicit binding declaration while preserving nested argumentProofs/payloads, nonempty pool prefix and repeated freeze/thaw comparisons. Printed describe omits argumentProofs but existing recursive comparator assertions do check them; do not replace this with a presumed missing oracle.

## Explicit Effect Graph and Default Template Loop Setup

Batch0043 adds exactly run/{declaration_effect_demand,default_argument_call_templates}.pw/.out. Bare for node and two for capacity sites have no earlier mutable target. Preserve root graph dedup/reachability and owner-scoped default completion, protocol pending and colliding call keys using explicit new bindings.

## Explicit Final Direct Constraint Loop Setup

Batch0044 adds exactly run/direct_call_constraint_instantiation.pw/.out. Bare for template has no previous mutable binding. Preserve prepared snapshot immutability, final-body evidence retention, child condition proof forwarding and missing/bodyless checks using an explicit binding declaration.

## Explicit Dynamic Descriptor Clone Loop Setup

Batch0045 adds exactly run/dynamic_closure_descriptor_identity.pw/.out. Bare term/recipe/result/proof/index/row/other loops have no earlier mutable targets. Preserve valid full-instance clone and exact target-only mutations/cross-instance rejection using explicit loop declarations; no observed role is assigned here.

## Explicit Factory Source Identity Loop Setup

Batch0046 adds exactly run/factory_source_declaration_identity.pw/.out. Bare for name over direct/block/branch has no prior mutable target. Preserve exact selected factory counts, declaration identity/backfill, explicit receiver retention and foreign same-name rejection using explicit loop binding.

## Explicit Final Closure Demand Loop Setup

Batch0047 adds exactly run/final_closure_demand.pw/.out. Bare for bodyId has no earlier mutable target, unlike its two valid for val callIndex loops. Preserve closure signature-before-body, generic captured type, later descriptor request and context/idempotence using explicit binding.

## Explicit Iteration Source Bindings

Batch0048 adds exactly run/{for_call_ref_array,for_iter_return_arc,for_range_bound_temp_arc,forwarded_source_admission}.pw/.out. Bare c, three t loops, i and tail have no prior mutable target; use explicit val/mut val new binding preserving fresh iterable cleanup, early return/break/full walk, call-result range bound lifetime and forwarded source ambiguity cases. The valid for val/pattern cases elsewhere are not rewritten.

## Explicit Five Missing-Entry Competing Failures

The immutable frontend-missing-main-correction record adds exactly reject/{default_arg_await,default_arg_await_match_expr,field_default_await,field_default_await_match_expr,try_from_no_matching_arg}.pw. These were primary obligations in batches0012/0015/0030, not new coverage credits. Each lacks main and .err. If the intended default-suspension or From source-type gate is lost, normal CLI whole-program LLVM lowering independently returns Failure for missing main and exits1; the status-only reject worker still accepts that unrelated failure. The normal path is Compiler.compileSource -> prepareCheckedProgram -> lowerPreparedLlvm(Whole) -> Backend missing-main Failure -> Compiler exit1, not the distinct ORC registerProgramRoots path.

Preserve direct and nested parameter/field default no-suspend rules and MyErr:From[I32] versus String error identity. Isolate each intended reason with admitted entry setup and/or a discriminating diagnostic and positive contrast in the eventual repair. Default later()->Promise[I64] agrees with current sleep; no unrelated Promise return mismatch is asserted. main-bearing try_error_type is useful neighboring coverage but does not discharge this exact masking setup. Earlier optional/unproved normal-emission judgments are superseded by the immutable correction; original reports/receipts and all primary totals remain unchanged. This is a source-backed competing-failure argument, not an executed compiler regression or audit-time fixture repair.

## Explicit Empty Generic Array Loop Binding

Batch0049 adds exactly run/generic_empty_array_arg.pw/.out: bare for x has no prior mutable target. Preserve sum seed and contextual Array[T] intent using an admitted new binding, after separately settling com-pxja sibling inference and com-s922 numeric context.

## Explicit Implicit-Call and Enum-Owner Loop Bindings

Batch0052 adds exactly run/{implicit_call_constraint_handoff,inferred_enum_argument_source_owner}.pw/.out. Bare template/index loop variables do not have earlier mutable targets. Preserve bodyless callable evidence and enum construction source-owner assertions with admitted val/mut val new bindings. The enum conversion loop can legitimately contain zero rows; central preparation/facts success remains the finite oracle, not a newly required nonempty count.

## Explicit Interface and Enumeration Loop Bindings

Batch0053 adds exactly run/{interface_boxing_conditions,interface_final_evidence,interface_nominal_hidden_readiness,interface_source_scope,iter_enumerate,iter_enumerate_i32,late_nominal_missing_identity}.pw/.out. Bare resolution/member/index/source/template/first/second/p/configured loop variables have no prior mutable target as appropriate per input; preserve nonempty final evidence, condition binding/adapter/table checks, enumerate record and missing-identity controls with admitted explicit new bindings. Do not rewrite already valid val loops.

## Explicit Nominal, Request and Relevance Loop Bindings

Batch0054 adds exactly run/{late_nominal_type_identity,lexical_body_requests,loop_arc,member_obligation_relevance_worklist}.pw/.out: six bare sites name/completedOwner/attempt/r and two relevance name loops lack prior mutable targets. Preserve normal/break/continue ownership purpose and source-owner/graph queries using adopted new bindings. Existing val/destructuring loops remain.

## Explicit Ambient Snapshot Loop Binding

Batch0055 adds exactly run/mid_ambient_effect_snapshot.pw/.out: bare for term has no earlier mutable target. Preserve partial request snapshot versus later body/destruction-index separation, unknown effect conservatism and known pure/effected controls with adopted explicit new binding.

## Explicit Mid Lattice and Declaration Loop Bindings

Batch0057 adds exactly run/{mid_dataflow_states,mid_declaration_ownership}.pw/.out: five lattice-loop sites and two variant/marker sites have no prior mutable target. Retain finite lattice/product controls and declaration ownership cases through explicit adopted new binding.

## Explicit Mid Global Access Dependency Loop Binding

Batch0058 adds exactly run/mid_global_access_demand.pw/.out: bare for body in partial.requiredBodies has no earlier mutable target. Preserve finite demand/readiness closure while adopting explicit new binding.

## Explicit Mid Instance Request Enumeration Binding

Batch0059 adds exactly run/mid_instance_demand.pw/.out: bare for body enumerates compiler.mid.bodies without earlier mutable target. Preserve selected-only body request, signature readiness and stable repeated failure under explicit adopted new binding.

## Explicit Mid Structural Traversal Loop Bindings

Batch0061 adds exactly run/mid_structural_traversal.pw/.out. Three for tag sites at17/27/34 lack earlier mutable targets; preserve duplicate successors, pool-relative captures/aggregate children, repeated operands and phase classifications with explicit new binding. Initial reviewer four-site locator count corrected to three before producer.

## Explicit Mid Recipe Wrong-Site Loop Binding

Batch0062 adds exactly run/mid_type_recipe_instances.pw/.out: bare for wrongSite lacks earlier mutable target. Preserve wrong owner/slot call-site rejection, knownUnit versus forged/missing result and instance separation with explicit new binding.

## Explicit Prepared Body Block and Shape Loop Bindings

Batch0065 adds exactly run/{prepared_call_expression_source,prepared_value_block_source_owner,projected_destruction_shape}.pw/.out. Six sites bare body/block/global/field/child/term have no earlier mutable target. Adopt explicit new val/mut val binding while preserving all-body preparation, block source isolation and shape query no-body/layout side effects. No unread loop corpus transfer.

## Explicit Custom and Control Range Loop Bindings

Batch0066 adds exactly run/{range_custom_step_arc,range_for_control}.pw/.out, six sites1+5 lacking prior mutable target. Existing range_iterator_values exact0023 pair with five loops is reused, not a third new root. Preserve range bound evaluation, closed maxima/empty ranges, continue/break/return and custom heap Step progression through explicit new bindings.

## Explicit Retained Requirement Clause Loop Binding

Batch0067 adds exactly run/retained_requirement_body_constraints.pw/.out. for source in plan.requirements meets existing immutable parameter source:String, not a prior mutable destination; explicit for val source introduces intended shadow binding. Preserve four source cases/public counts2/1/0/1, missing derivation/public evidence refusals, immutable plans and clause storage. One exact site, no new inference rule.
