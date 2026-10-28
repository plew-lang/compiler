---
id: com-owb3
status: open
deps: []
links: []
created: 2026-10-27T19:56:08Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, generics, verification]
---
# Reconcile generic factory fixture binders with explicit impl declarations

## Finite Investigation and Repair Boundary

Audit source baseline9665094d/spec5bd65a5. Exact scopes: part/namespace_type_generic/Models.pw (`pub impl Box[T] { factory }`, T has no explicit impl binder), run/aggregate_infer_recorded_fields.pw (`pub impl Measurement { factory }`) and run/any_generic_param.pw (`pub impl Wrapper { factory }`). spec06 impl parameters require introduction by impl[...] and distinguish binders from type uses. First shape has an undeclared T and is a confirmed explicit-binder migration candidate. The two bare-owner publication markers are not automatically the same invalid shape: determine whether a specified shorthand exists before changing them; consult spec05/07 and original intent.

Source-only evidence in part-batch-0086.json/run-head-0087.json under meta/evidence/test-audit/scoped-reviews. Original c0b5b54b intended qualified Box[I64] identity/output41, not implicit binder syntax. Preserve the numeric/identity regression; never bless syntax because current compiler accepts it.

## Deliverables and Guarantees

Derive each admission ruling from canonical rules, preserving default memberwise factory publication and correct lexical ParamIds. If the bare-owner shorthand lacks a decided meaning, obtain a surface decision instead of inferring a new rule. Migrate confirmed stale fixture syntax and add actual positive/reject controls distinguishing explicit binder, unbound T, concrete Box[I64] and any accepted bare publication form. Ensure actual registration and final factory call consume the same binder identity; no special-case fixture handling.

## Completion

Rulings for all selected forms and exact extended roots, preserved original coverage, finite owned implementation gap if found, relevant RED/GREEN and independent review. Not a whole-corpus generic rewrite. The rest of source-admission audit remains its original work.


## Paired Rejection Setup

`tests/fixtures/partreject/namespace_type_argument/Models.pw` repeats the undeclared `Box[T]` form. Read its Main.pw/Main.err and preserve the intended rejection of type arguments on a namespace; setup migration must not silently replace that reason with an unbound-binder rejection. This exact auxiliary scope accompanies the Box positive, not an audit of all partreject inputs.

## Explicit Three-Root Same-Form Intake Extension

Batch0089 adds bare generic-owner factory markers in exactly
`tests/fixtures/run/array_generic_field.pw` (Holder),
`tests/fixtures/run/array_literal_inferred_element.pw` (Box), and
`tests/fixtures/run/associated_callable_invocation.pw` (Projected). Apply the
same eventual bare-publication ruling, without conflating them with the
undeclared Box[T] binder. Preserve their respective generic field, inferred
array element and associated callable result/control coverage. The rule is
undecided; no fixture change is authorized merely by current parser behavior.

## Explicit Variant-Argument Rejection Setup

The source-admission audit also reads exactly `tests/fixtures/partreject/namespace_variant_argument/{Main.pw,Models.pw,Main.err}`. Models repeats the same undeclared `pub impl Box[T]` binder. Main intends to reject `<Models.Choice.Some[I64] value=41I64 />`, with the specific reason that only the constructed type accepts type arguments. Preserve that reason while migrating the unrelated Box setup; unbound-T failure is not a substitute. This is one supplementary control, not a newly audited primary plan unit or the unread partreject corpus.

## Explicit Paired Literal-Range Bare-Publication Context

Batch0007 reads `tests/fixtures/reject/aggregate_infer_literal_range.pw` and its .err. It repeats the bare generic `pub impl Measurement { factory }` of the already named run positive. Include this exact negative when deciding any bare-owner publication shorthand, preserving the intended 256-versus-U8 range reason and com-pxja's separate forward sibling-inference question. This is not the confirmed unbound Box[T] form or an extra source rule.

## Explicit Associated-Receiver Negative Context

Batch0008 adds exactly tests/fixtures/reject/assoc_disjoint_receiver_ambiguous.pw. The bare generic `pub impl Box { factory }` has the same unresolved publication meaning as the existing bare-owner representatives. Preserve its actual source requirement: Box.tag() cannot select Box[I64] versus Box[String] by declaration order without receiver type information. Missing .err alone is optional diagnostic coverage, not another proved masking bug; do not conflate a declaration-setup question with permission to resolve that ambiguous call.

## Explicit Four Standalone Rejection Setups

Batch0011 adds exactly tests/fixtures/reject/{closure_capture_generic_inst,concrete_conformance_does_not_match_other_instance,concrete_conformance_trait_view_mismatch,concrete_supertrait_does_not_cover_other_instance}.pw. Each has the unresolved bare generic pub impl Box { factory } publication marker, not an undeclared Box[T] binder. Include them in the same eventual source ruling while preserving distinct captured generic representation, concrete conformance instance, explicit trait-view and supertrait coverage. Capture of generic structures is an explicitly current unsupported lane, not an adopted prohibition or a request to implement it in audit. No other unread bare-owner roots are transferred.

## Explicit Three Named-Extension Negative Setups

Batch0014 adds exactly reject/{extension_conformance_generic_overlap,extension_conformance_only_view_generic_mismatch,extension_generic_concrete_receiver_overlap}.pw. Their pub impl Box {factory} markers repeat the unresolved bare generic publication form. Apply the same canonical shorthand/binder ruling while retaining same-extension overlapping conformance, inapplicable concrete receiver view and generic/concrete member receiver overlap as separate rejection purposes. These are not newly proved undeclared-T defects or all unread extension tests.

## Explicit Generic Field-Default Control

Batch0015 additionally reads run/field_defaults_generic.pw/.out, whose pub impl Box {factory} is the same unresolved bare-publication shape. Include exactly this pair in the existing source ruling, preserving concrete default field substitution, fresh array and override results5/99/0/1/2. This is supplemental control scope only, not a newly completed primary admission/outcome or an automatic invalid-binder diagnosis.

## Explicit Generic Constructor Constraint Contexts

Batch0016 adds exactly reject/generic_constructor_nested_conflict.pw/.err and the fully read supplemental run/{generic_ctor_infer,generic_ctor_bottomup,generic_constructor_nested_constraints}.pw/.out. Rows, Box, Pair and Nested use the same unresolved bare-owner publication markers. Apply the eventual canonical ruling while preserving repeated-field conflict, top-down expected instance, bottom-up ground element types and nested/generic field constraints as distinct source guarantees. Qualified control reads do not complete their unread primary admission/outcome units or certify a hidden default numeric type.

## Explicit Generic Receiver and Method-Where Controls

Batch0017 adds the fully read supplemental run/generic_recv_arg_valid.pw/.out and generic_method_where.pw/.out. Both contain bare generic pub impl Box {factory} markers. Apply the same eventual publication ruling while preserving grounded I64/String receiver argument acceptance and actual Bar conformance discharge; these positive controls do not justify the unresolved shorthand by current output. Exact supplemental scope only, not new primary credit.

## Explicit Generic Index-Call Supplemental Control

Batch0017 adds run/generic_index_call_template.pw/.out, whose bare pub impl Shelf {factory} has the same unresolved generic publication shape. Preserve actual selected Index[U64].Output=T substitution and final subscript use through generic shelf with String/I64 results. No new primary audit credit or implicit structural Index conformance is claimed.

## Explicit Receiver-Overlap Negative Setup

Batch0022 adds reject/overload_generic_concrete_receiver_overlap.pw, whose pub impl Box { factory } is the same unresolved generic memberwise-publication shape. Preserve the definite Box[T]/Box[I64] receiver-domain overlap rejection while resolving this setup; do not infer bare publication legality from current acceptance or call its rejection a confirmed competing failure while that source rule remains unsettled. This is one exact root, not every generic overload declaration.

## Explicit Shared-Pointee Method Control Setup

Batch0024 adds run/ref_arrow_method.pw/.out, whose Box[T] generic has a bare pub impl Box { factory } marker. Preserve shared Counter mutation/destruction and grounded Box[I32].get result through the same unresolved publication decision. Adopted projection/deinit migration stays met-op15/met-2t3l; this exact control is not certified source-clean or newly credited as a primary outcome/admission.

## Explicit Struct-Pattern and Generic-Payload Controls

Batch0027 adds supplemental run/{struct_destructure_stmt,struct_pattern,generic_enum_payload_context}.pw/.out. Each uses the same unresolved bare generic pub impl Box { factory } publication marker. Preserve statement punning/rename/assignment/discard and grounded generic fields, struct match payload/value results, and contextual Optional/Box literal inference through the eventual canonical publication ruling. The last pair also has current Some(v=...) producers/patterns, owned by met-2wca. These are qualified source controls, not adopted-clean proofs or completed primary outcome/admission units.

## Explicit Try-From Generic Argument Control

Batch0030 adds supplemental run/try_from_generic_arg_match.pw/.out. Its pub impl Box {factory} repeats the unresolved bare generic publication shape. Preserve correctly matched Box[String] From factory conversion and error55 alongside the mismatch negative through the eventual canonical publication ruling; no adopted shorthand is inferred from historical acceptance.

## Explicit Unused Generic Capture Negative

Batch0032 adds exactly reject/unused_closure_capture_generic_inst.pw/.err. Its bare pub impl Box {factory} repeats the unresolved generic publication shape. Preserve declaration-time diagnosis of the currently unsupported generic-struct capture shape in the unused body and its specific capture diagnostic through the eventual canonical publication ruling. com-b1ro owns that unsupported environment shape; neither fixture name nor historical rejection creates an adopted type-kind capture ban.

## Explicit Nested ARC and Array-Element Admission Contexts

Batch0035 adds exactly run/{arc_nested_generic_box,arg_convention_guaranteed_arc,array_compound_elem}.pw/.out. Their pub impl Box {factory} markers repeat the unresolved bare generic publication form. Preserve grounded nested Box instances with String/shared-cell payloads, guaranteed argument versus stored/returned owners, and generic compound array elements through the eventual publication ruling. Reference/deinit/API qualifications remain their existing owners; no undeclared Box[T] binder error or allARC certification is inferred.

## Explicit Associated-Storage Layout Admission Context

Batch0037 adds exactly run/associated_storage_layout.pw/.out. Projected[T] and Wrapper[T] have bare generic-owner publication markers, repeating the unresolved shorthand. Preserve concrete and projected fields, generic receiver grounding, enum payload/value copies, newtype storage and I64/String outputs through the eventual common ruling. Holder is nongeneric and not part of this publication question. No layout/codegen outcome is newly certified by this admission role.

## Explicit Associated Body-Signature Context

Batch0038 adds exactly run/body_signature_associated_types.pw/.out. Bare pub impl Shelf {factory} repeats the unresolved generic publication form. Preserve exact Index[U64].Output as both parameter and result under distinct Shelf[I64]/Shelf[String] body environments through the common eventual publication ruling. No unique/generic ABI feature or new structural Index conformance is required by this source-admission question.

## Explicit Generic Array-Return Inference Control

Batch0039 fully reads supplemental run/generic_array_ret_infer.pw/.out. Bare pub impl Box {factory} repeats the unresolved generic publication shorthand. Preserve caller/callee binder substitution, full Array result and nested idArr/firstOf/wrapAll value types through the eventual common ruling. It is a qualified control only, with no new primary admission/outcome credit or default numeric inference.

## Explicit Chain and Closure-Field Publication Contexts

Batch0040 adds exactly run/{chain_generic,closure_field}.pw/.out. BoxG/Pair and Apply bare generic-owner factory publication repeat the unresolved shorthand. Preserve generic Chain value substitution and grounded function-valued receiver field calls through the eventual shared ruling. This does not authorize arbitrary open F invocation without a function-type declaration or silently resolve Optional labels/loop setup.

## Explicit Self-Projection Conformance Context

Batch0041 adds exactly run/conformance_self_projection.pw/.out. Bare pub impl Box {factory} repeats the unresolved generic-owner publication shorthand. Preserve Self as the complete Box[T] trait positional input and T as the associated output across I64/String generic read calls through the common eventual ruling. This is not undeclared Box[T] or permission to infer bounds from concrete instances.

## Explicit Generic Method Ordering Control

Batch0043 adds only supplementary run/default_eval_order_generic_method.pw/.out: bare pub impl Box factory repeats the unresolved generic publication shorthand. Preserve middle omission and explicit-first evaluation purpose when reconciling source. No primary obligation credit or blanket Box[T] undeclared binder rewrite.

## Explicit Dynamic Transform and Existential Wrapper Publication

Batch0045 adds exactly run/{dynamic_call_template_generic_instances,existential_payload}.pw/.out. Bare pub impl Transform/Wrapper factory repeat unresolved generic publication shorthand; keep generic closure signature and existential payload intents separate from this finite source question.

## Explicit Unit-Indexed Factory Publication

Batch0046 adds exactly run/factory_receiver_identity.pw/.out. Bare pub impl Dist factory repeats unresolved generic publication shorthand. Preserve full destination Dist[Feet] versus Dist[Yards] identity and common Dist[Meters] input; do not change into an assumed undeclared Box[T]-binder error.

## Explicit Field and Pattern-Bound Generic Publication

Batch0047 adds exactly run/{field_init_place_arc,final_callable_receiver_pattern_bound}.pw/.out. Bare pub impl Box/Packed factory repeats unresolved shorthand; field_defaults_generic is already exact owned and reused. Preserve field ownership and Packed[Array[T]] binder identity, not an assumed explicit undeclared-binder fix.

## Explicit Generic Array Field Publication and Missing Binder

Batch0048 adds exactly run/{generic_array_box_field,generic_array_compound_field,generic_array_field,generic_array_field_deinit}.pw/.out. First three have bare generic pub impl Box/Holder, Entry/Map, or Box factory markers, held for existing shorthand ruling. Last instead explicitly names Container[T] without declaring impl[T], a confirmed undeclared binder shape: migrate that distinct setup while retaining nested Array/ref/deinit copy purpose. Do not treat all four as the same ambiguous source form.

## Explicit Generic Binding, Constructor and Enum Publication

Batch0049 adds exactly run/{generic_array_field_instance_isolation,generic_assoc_fn,generic_associated_bound_grounding,generic_box_ref_payload_arc,generic_constructor_value_shape,generic_enum_array,generic_enum_chain_match_print}.pw/.out with bare generic pub impl markers; generic_array_ret_infer/generic_constructor_nested_constraints/generic_ctor_bottomup/generic_ctor_infer reuse existing exact intakes. Preserve nominal declaration/impl binder separation, nested Array/constructor shape, associated witness grounding and Optional chain layout. Do not declare bare shorthand an explicit unbound T defect.

## Explicit Generic Result Binder and Method Publication

Batch0050 adds exactly run/{generic_if_result_instance_isolation,generic_inst_param_fn,generic_match_result_payload_term,generic_method_struct,generic_method_transitive_hash}.pw/.out; enum_payload_context/index_call_template/method_where reuse existing generic-prefixed exact intakes. generic_if_result_instance_isolation and generic_match_result_payload_term explicitly write pub impl Box[T] without impl[T], confirmed missing binder. generic_inst_param_fn/generic_method_struct/generic_method_transitive_hash use bare Box/Hasher1 publication, kept as existing unresolved shorthand question. Preserve if/match semantic producer, nominal parameter/method return and nested transitive Hash purposes without conflating the forms.

## Explicit Generic Struct and Global Publication

Batch0051 adds exactly run/{generic_struct,generic_struct_fn,generic_struct_local_drop_arc,generic_struct_multi,global_generic_init}.pw/.out; generic_recv_arg_valid reuses its earlier exact intake. Preserve multiple nominal fields, nongeneric function parameters/results, local/shared generic payload ownership and global generic rooting. These bare pub impl Box/Pair markers remain the existing shorthand ruling, not explicitly undeclared T.

## Explicit Generic Iterable Publication

Batch0053 adds exactly run/iter_generic.pw/.out with bare pub impl BoxIter/Box factory markers. Preserve generic Array[T] storage, Item=T next/result and Iterable.Iter substitution while settling the existing shorthand question. No explicit undeclared-T or structural conformance exception is inferred.

## Explicit Mid Associated Item Publication

Batch0055 adds exactly run/mid_associated_item_identity.pw/.out. Bare pub impl Box factory repeats existing unresolved shorthand, not explicit undeclared T. Preserve trait Item versus method Item lexical binder independence and concrete Array results through the eventual canonical ruling.

## Explicit Mid Global Initializer Publication

Batch0058 adds exactly run/mid_global_init_cfg_lowering.pw/.out. Bare pub impl Box factory repeats existing finite unresolved generic publication form, not explicit undeclared T. Preserve earlier-root dependency, generic initializer call and storage type evidence through canonical reconciliation.

## Explicit Patterned Receiver Factory Publication

Batch0060 adds exactly run/mid_receiver_pattern_layout.pw/.out: bare pub impl Packed factory repeats existing unresolved generic publication, separate from impl[T] Packed[Array[T]] valid binder. Preserve selected receiver pattern substitution, bound and field layout through canonical ruling; no bare shorthand invented.
