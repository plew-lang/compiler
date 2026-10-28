---
id: com-bfvd
status: open
deps: []
links: []
created: 2026-10-27T19:19:55Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, runtime, verification]
---
# Reconcile ordinary panic function admission in selected regression fixtures

## Contract, Evidence and Scope

spec 11-control-flow requires explicit use of ordinary @Std/Core diverge fn panic(message~:String). Six panic fixtures (diverging_call, diverging_callable_storage, diverging_field_invocation, diverging_local_invocation, match_expr_panic_arm, span_equality_identical_out_of_bounds) use no Core panic import, some with legacy panic statement form. Existing runtime intent is sound; source does not certify current-spec admission. Pinned current implementation still admits legacy forms; no candidate execution. Existing com-8j0w mentions panic/exit integration generally but does not explicitly own this migration.

Bounded follow-up: recover original six test purposes; trace public Std/Core panic declaration, parser keyword/statement path, ordinary name/import lookup and divergence callable result handling. Produce a concrete migration/repair with finite required consumers and source controls before editing fixtures; do not merely add imports or change statements before the ordinary-function API exists. Preserve abort/no-unwind behavior and direct/local/field/generic/associated-value invocation coverage. Distinguish current supported subset from adopted surface. No new general effect/lifetime feature, no all-Std migration. TDD and independent review for any later implementation; audit itself only assigns this work.

Scoped evidence: meta/evidence/test-audit/scoped-reviews/runtime-batch-0084.json and batch-0084-disposition.json (test/source baseline 9665094d). This is a separate finite follow-up, not a child/prerequisite of the audit epic or a claim repairs passed.



## Additional Same-Contract Evidence

The exact seven internal-panic-outcome audit adds only the span fixture to the
representative root-input scope above; its fallback has a legacy panic statement.
Imported Frontend/Ir/SourceFiles invariant guards and positive controls also use
legacy panic. Inventory their affected migration handoffs when planning the
ordinary-function boundary; do not rewrite them anonymously inside this audit or
claim that changing six root fixtures alone implements the public API. This
remains bounded admission/migration investigation, not an all-compiler rewrite.
The original first-five review remains exact historical evidence; the extension
is recorded explicitly here rather than silently changing that report.

## Explicit Seventh Representative Root

Batch0088 adds `tests/fixtures/run/any_sendable_erasure.pw`: both unused failure
arms use the legacy panic statement. Keep this positive-path context when
inventorying ordinary imported panic admission; it is not a claim those branches
ran or trapped. Its nominal-Self/container conversion reconciliation is com-vp0o,
not part of implementing panic. Seven representative roots do not constitute an
all-source migration inventory; imported guards still require the bounded
handoff investigation above.

## Explicit Eighth Representative Root

Batch0089 adds `tests/fixtures/run/array_forward_element_context.pw`: three
positive-control fallback calls use panic without importing the ordinary Core
function. Preserve array forward context, generic String payload and nested
empty-array checks; no failure branch was executed by this audit. This expands
only the named representative input set, not the complete compiler migration.

## Explicit Ninth Representative Root

Batch0009 adds exactly tests/fixtures/reject/associated_literal_context_unknown.pw and its .err context. Holder[T].empty's unused body calls panic without explicitly importing the ordinary Core function; the intended negative is absent generic receiver/result context at Holder.empty(). Preserve that inference rejection and its specific diagnostic, rather than allowing ordinary panic name/surface migration to replace it. No failure arm or compiler was executed. This extends only one representative root, not an all-compiler migration or an audit of other unread associated calls.

## Explicit Two Divergence-Declaration Negatives

Batch0012 adds exactly reject/diverging_async_modifier.pw and reject/diverging_call_following_statement.pw with the latter .err. The first combines async/diverge illegally but also calls panic without explicit use; the second has legacy panic statement syntax inside a diverge function before testing forbidden following code at its call site. Preserve the modifier and source-transfer diagnostic purposes through ordinary imported panic migration. Specific following-statement .err prevents unrelated missing-panic rejection from being credited. Current legacy admission is not proof of adopted source validity. These extend only the representative set; compiler guards and all unread fixtures are not silently transferred.

## Explicit Five Divergence-Value Negatives and Three Storage/Flow Controls

Batch0013 adds exactly reject/{diverging_call_value,diverging_closure_contract_erasure,diverging_closure_contract_strengthening,diverging_dynamic_call_value,diverging_spawn_modifier}.pw with their existing companions. Four use legacy panic statement syntax; spawn uses panic() without importing it. Preserve direct/dynamic invocation value prohibition, strict normal/diverge closure contracts and forbidden spawn/diverge combination through ordinary panic migration. Specific .err predicates remain distinct from unrelated setup rejection.

The fully read supplemental run/{diverging_call_flow,diverging_callable_declarations,diverging_callable_storage}.pw/.out add three bounded contexts using the same legacy/unimported panic forms. Preserve branch result42, uncalled divergence declarations and stored/copied/projected callable values; they are source/oracle controls, not evidence their abort branches executed. run/diverging_loop_invocation_boundary is a separate panic-free control, not a migration input. The finite representative set is19 roots after these exact eight additions; neither unread source nor all compiler internal guards are silently transferred.

## Explicit Four Memberwise-Collision Negatives

Batch0015 adds exactly reject/factory_memberwise_{collision,default_collision,empty_collision,generic_collision}.pw and their .err companions. All custom factory bodies call panic() without the adopted ordinary Core import. Preserve full/default/empty/generic collision declaration rejection and its specific anonymous-factory-overlap diagnostic under a coherent panic migration. A body/name error cannot replace the required companion. The representative set is23 roots after these exact four additions; no compiler/test/expectation change or execution occurred in audit.

## Explicit Generic Enum-Inference Fallback Control

Batch0017 adds the supplemental run/generic_enum_field_inference.pw/.out, whose two unexecuted failure arms call panic without importing the ordinary Core function. Preserve successful array/String payload inference and fallback diagnostics without pretending those arms executed. Optional payload labels are owned by met-2wca. This adds one representative root (24 total at this intake), not all generic-enum fixtures or actual abort-path coverage.

## Explicit Source-Transfer Mapping Control

Batch0018 adds exactly run/source_transfer_targets.pw/.out as a supplemental internal control. Its invariant-failure branches call panic without the adopted ordinary Core import. Preserve source return/give/break/continue owner identity, wrong-session/kind rejection and the final Mid consumer mapping; this source-only read neither executes those arms nor certifies the complete internal service API. This extends the representative set to25 named roots, not all source guards.

## Explicit Import-Provenance Supplemental Control

Batch0019 adds run/import_origin_provenance.pw/.out. Internal provenance-table assertions use legacy unimported panic statements. Preserve original/local module identity, independent copy tables, re-export distinctions and first-binding retention through ordinary panic migration; no failure branch was executed. This is the26th named representative root, not a claim to have inventoried every internal guard or audited its complete primary service contract.

## Explicit Mid Source-Owner Supplemental Control

Batch0020 adds run/mid_source_owner_admission.pw/.out. Its invariant-failure arms use panic without the ordinary Core import. Preserve valid prepared source acceptance, wrong-owner statements/facts, absent admission and foreign-session rejection through coherent panic migration. This27th representative root is a qualified supplemental read; it neither ran the failure branches nor certifies all Mid/source fact APIs.

## Explicit Return-Path Supplemental Control

Batch0021 adds run/return_paths.pw/.out. The C arm of classify uses a legacy unimported panic statement. Preserve source-return coverage for exhaustive match, if/else and the noncompleting while form, all five normal outputs and abort behavior under ordinary imported panic migration. This28th representative root is a supplemental source read, not proof the panic arm ran or a complete control-flow API audit.

## Explicit Diverging Operator-Witness Negative

Batch0022 adds reject/operator_diverging_witness.pw/.err. Its assoc diverge fn Neg witness uses a legacy unimported panic statement. Preserve normal-versus-diverge requirement contract mismatch and the specific incomplete-conformance diagnostic under ordinary panic migration. This29th representative input is not evidence the operator was invoked; no new conformance exception or primary control execution is claimed.

## Explicit Call-Storage Publication Supplemental Control

Batch0024 adds run/source_call_storage_publication.pw/.out. Its invariant guards call panic without the ordinary Core import. Preserve final storage-demand summaries, immutable publication/reopen rejection and closure stability through coherent panic migration. This30th representative root is a supplemental source/oracle read, not execution of failure branches or certification of the full call-fact service.

## Explicit Closure-Publication Supplemental Control

Batch0025 adds run/source_closure_publication.pw/.out. Its invariant-failure arms call panic without the ordinary Core import. Preserve construction-versus-preparation state, failed-owner nonpublication, immutable completed closure facts and final Mid canonical-consumer checks under coherent panic migration. This31st representative root is a qualified supplemental read, not executed invariant-failure coverage or certification of every closure/source service. source_call_storage_publication was already the exact30th root in batch0024 and is reused by unchanged source identity.

## Explicit Source-Typing and Value-Region Supplemental Controls

Batch0026 adds exactly run/source_typing_context_closure.pw/.out and source_value_region_production.pw/.out. Their invariant guards call panic without the ordinary Core import. Preserve typed empty arrays/generic closure results/comparison context, and saved give-produced region terms versus expectation-only missing values, distinct source/execution completion and stable failed-owner nonpublication. These add two representative roots (32/33), not an all-internal migration inventory. No branch was executed or primary service outcome certified by the audit.

## Explicit Required-Field Negative and Supertrait-Proof Control

Batch0027 adds exactly reject/struct_required_array_field.pw/.err and supplemental run/declaration_supertrait_proof.pw/.out. Both use legacy unimported ordinary panic. Preserve the missing required Array field reason in the first; preserve inherited/conferred path owners, distinct trait instances, freeze/thaw proof equality and absence of execution preparation/destruction in the second. These are representative roots34/35, not executed guards, full source-service certification or an all-internal migration.

## Explicit Type-Declaration and Operator-Source Controls

Batch0030 adds exactly supplemental run/{type_declaration_publication,type_term_closedness,source_operator_literal_context}.pw/.out, whose guards use ordinary panic without its explicit Core import. Preserve atomic declaration publication/failure isolation, later-writer closure and Arena branch independence; recursive type closedness including unknown future children and snapshot stability; closed source operator selection and refusal to repair removed selections. These are representative roots36/37/38 only, not executed guards or complete source-service certification. The operator control also needs its exact loop-binding setup disposition in com-ntm8.

## Explicit Unused Required-Field Negative

Batch0033 adds exactly reject/unused_struct_required_array_field.pw/.err. Its unused guard uses legacy unimported ordinary panic. Preserve whole-target checking of the missing required Array field and its specific diagnostic under coherent panic migration; unrelated panic rejection is not a passing substitute. This is representative root39, not all unused source bodies or actual guard execution.

## Explicit Access-Index and Binder-Identity Roots

Batch0034 adds exactly run/{access_candidate_index,active_type_parameter_identity}.pw/.out. Their guards use legacy unimported ordinary panic. Preserve independent first-match/role-specific access-index oracle, holes/max IDs, late registration/copy isolation, explicit nested provenance and ParamId-based active/foreign/zero binder discrimination. These two roots have both admission and observed-behavior plan units; count each root once in migration (representatives40/41), and do not claim guard execution or allAPI correctness from static inspection.

## Explicit Projection and Bare-Type Internal Guards

Batch0037 adds exactly run/{associated_projection_constraint_identity,bare_type_name_index,bare_type_registration}.pw/.out. Unimported legacy panic guards qualify adopted source admission, while the internal assertions still distinguish associated owner/arguments/receiver and legacy bare-name first-match, append, copy and parallel-row publication. These are representative roots42–44, not a complete guard inventory. The last root has only its outcome obligation in this batch; its separate unread admission is not transferred or counted here. No failing guard was executed.

## Explicit Binder and Body-Instance Internal Guards

Batch0038 adds exactly run/{binder_type_term,body_instance_index}.pw/.out as representative roots45–46. Their unimported legacy panic guards need the same ordinary-function admission reconciliation, while preserving lexical binder/view/structural distinctions and body environment/proof/order/copy-key invariants. The already named bare_type_registration root42–44 intake from0037 is reused for its separate admission role here, not a new representative root. No guard was executed.

## Explicit Call and Callable Internal Guards

Batch0039 adds exactly run/{call_closure_owner_boundary,call_template_result_arguments,call_type_argument_constraints,callable_form_source_identity,callable_method_selection,callable_name_index,callable_signature_demand}.pw/.out as representative roots47–53. Unimported legacy panic guards qualify source admission; preserve owner/frontier separation, transactional type inference, authored selection/provenance, ordered candidate/copy behavior and signature-without-body preparation. Embedded text missing() in callable_signature_demand is a deliberate later body-demand rejection, distinct from the outer source panic migration. No guard or compiler was executed.

## Explicit Chain, Checked-Program and Closure Guards

Batch0040 adds exactly run/{chain_source_type_identity,checked_division_widths,checked_program_boundary,closure_completion_contract,closure_descriptor_identity,closure_enum_owned,closure_instance_environment}.pw/.out as representative roots54–60. Ordinary panic import/surface migration preserves independent contract checks. Source-only width, checked-program, descriptor and enum inputs do not newly certify their output/IR/native behavior; internal outcome credit is only the three exact assigned roles. No guard or compiler was run.

## Explicit Session and Conformance-Proof Guards

Batch0041 adds exactly run/{compiler_session_body_requests,compiler_session_demand,compiler_session_finalization,compiler_session_initializers,compiler_session_mid_requests,compiler_session_registry,conformance_proof_demands,conformance_proof_outputs}.pw/.out as representative roots61–68. Reconcile ordinary panic admission while preserving selected request/failure/snapshot/initializer/registry source purposes and exact proof-demand/output assertions. Session roots are source-only roles here; no additional session runtime/outcome or complete lazy-execution result is certified.

## Explicit Declaration Evidence and Capture Guards

Batch0042 adds exactly run/{declaration_associated_evidence,declaration_body_demand,declaration_bound_proof,declaration_capture_facts}.pw/.out as representative roots69–72. Reconcile unimported ordinary panic admission without weakening projection prerequisite/interning/stack cleanup, per-owner request/cache/local-access errors, bound ownership/codec corruption or declaration capture-mode assertions. Capture has only its observed-behavior role here; body-demand only source-admission. No guard was executed.

## Explicit Declaration Obligation and Default Guards

Batch0043 adds exactly run/{declaration_codegen_limit_boundary,declaration_conversion_closure,declaration_conversion_evidence,declaration_effect_demand,declaration_identity_index,declaration_identity_precedence,declaration_method_receiver_proof,declaration_obligation_scope,declaration_obligation_states,declaration_program_boundary,declaration_trait_assumptions,default_argument_call_templates,default_body_demand}.pw/.out as representative roots73–85. Reconcile ordinary panic admission while retaining exact conversion/binder/receiver/state/default/cache/effect guard purposes. Reuse declaration_supertrait_proof representative35 and declaration_capture_facts representative72, not two more roots. Internal synthetic malformed rows and embedded invalid input are deliberate probes; no guard was executed.

## Explicit Default Environment and Direct Evidence Guards

Batch0044 adds exactly run/{default_generator_environment,default_generator_source_publication,direct_call_constraint_instantiation}.pw/.out as representative roots86–88. Reconcile ordinary panic admission while retaining lexical module/Self/proof transport, independently published default facts, retained call/conditional/bodyless constraint evidence and missing-proof failures. The three already exact diverging_call_flow/diverging_callable_declarations/diverging_callable_storage roots are reused, not new representatives. Source-only default publication gains no observed-role credit.

## Explicit Dynamic Descriptor and Existential Guards

Batch0045 adds exactly run/{dynamic_closure_descriptor_identity,empty_call_constraint_plan,enum_name_index,existential_callable_result,existential_declaration_plan,existential_implementation_evidence,existential_rebox_evidence}.pw/.out as representative roots89–95. Ordinary panic admission migration preserves independent identity/index/empty-plan/Promise signature/selected witness and proof reuse checks. Dynamic descriptor role is source-only; internally historical existential plan/rebox expectations require separate com-vp0o reconciliation, not mere panic repair.

## Explicit Retag, Symbolic Result and Factory Guards

Batch0046 adds exactly run/{existential_retag_proof,existential_symbolic_result,factory_requirement_fallible,factory_source_declaration_identity}.pw/.out as representative roots96–99. Reconcile ordinary panic while preserving forged retag negative checks, ambient-substitution noninterference, fallible requirement branches and exact factory nominal/foreign-owner assertions. Retag and requirement roots source-only here; no new unassigned outcome certification.

## Explicit Final Call, Body and Publication Guards

Batch0047 adds exactly run/{final_body_demand,final_call_requires_record,final_call_signature_readiness,final_call_store_publication,final_closure_demand,final_dependency_demand,final_for_index,final_witness_demand,finalization_publication}.pw/.out as representative roots100–108. Ordinary panic migration preserves independent missing-record/signature/publication, lazy request/context/terminal-failure and body/stmt index invariants; await index already uses imported assert and is not a panic intake. No guard executed.

## Explicit Iteration, Source Admission and Function Index Guards

Batch0048 adds exactly run/{for_type_recipe_index,forwarded_source_admission,frontend_body_demand,function_bound_arena,function_name_index}.pw/.out as representative roots109–113. Ordinary panic migration preserves first-write immutable recipe/index, concrete source forwarding admission, partial body-request caching and function-bound/candidate order/copy checks. FunctionBoundArena is only source role here; no new outcome or blanket all guards claim.

## Explicit Selected Generic Call Authority Guard

Batch0049 adds exactly run/generic_call_selected_authority.pw/.out as representative root114. Preserve selected source declaration, stable semantic site despite AST name poisoning, no reconstruction after Pending and no extra operation recording. This building-owner test is not a successful owner closure/global publication proof.

## Explicit Lexical Inference Legacy Panic Statements

Batch0050 adds exactly run/generic_inference_lexical_term.pw/.out as representative root115. Its panic message statement form is part of the same adopted ordinary diverge-function migration, not source-clean merely because no ordinary call name is written. Preserve lexical ParamId versus concrete body-environment isolation and pending suffixed literal declaration type; no inference implementation defect or executed failure arm is asserted.

## Explicit Global Owner and Grounding Guard Sources

Batch0051 adds exactly run/{global_address_identity,global_call_constraint_evidence,global_closure_call_constraints,global_initializer_requests,ground_environment_views}.pw/.out as representative roots116–120. Four roots use ordinary panic calls without explicit import; ground_environment_views uses legacy panic statements, also within the same ordinary diverge-function migration. Preserve sealed global identity, independent source requests/closure call evidence, cached failure and simultaneous substitution assertions; not merely an import edit before API support.

## Explicit Ground, Import and Projection Guard Sources

Batch0052 adds exactly run/{ground_nominal_identity,implicit_call_constraint_handoff,import_origin_provenance,inference_literal_record_authority,inherited_projection_identity}.pw/.out as representative roots121–125. Legacy panic statements and unimported ordinary panic calls both require adopted ordinary diverge-function boundary; preserve nominal identity, implicit selected-call evidence, import provenance, Record literal authority and projection equality guards. Statement syntax is not an exemption or import-only edit.

## Explicit Interface and Missing-Nominal Guard Sources

Batch0053 adds exactly run/{interface_boxing_conditions,interface_declared_guarantees,interface_final_evidence,interface_nominal_hidden_readiness,interface_source_scope,late_nominal_missing_identity}.pw/.out as representative roots126–131. Adopt ordinary imported diverge panic while preserving exact interface declared guarantees, scoped hidden subjects, final evidence/boxing and no-fabricated ambient identity assertions. Source-only boxing/final tests are not newly counted internal outcome roles.

## Explicit Nominal Request, Match and Relevance Guards

Batch0054 adds exactly run/{late_nominal_type_identity,lexical_body_requests,match_expr_diverge,member_obligation_relevance_worklist}.pw/.out as representative roots132–135. Ordinary calls need explicit Core import; match_expr_diverge legacy panic statements also require ordinary function migration. Preserve nominal ambient identity, failed/successful source request caching, branch divergence and graph relevance/error-order contracts, not an all-guard rewrite.
