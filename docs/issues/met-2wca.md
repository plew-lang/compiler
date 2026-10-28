---
id: met-2wca
status: open
deps: []
links: []
created: 2026-10-27T20:42:00Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Plan adopted Optional payload labels for selected regressions


## Contract and Finite Scope

Source-only admission audit at compiler9665094d/spec5bd65a5: `tests/fixtures/part/namespace_chain_identity/{Main,First,Second,Noise}.pw` protects nominal Chain identity, permuted binder positions, equal concrete arguments and empty behavior. First/Second.chain construct Optional.Some using `v=`; spec05 declares Some(value:T). Current std/Lang57-60 defines Some(v:T), and Core's Optional Chain implementation527-531 constructs v=. The Chain requirement names themselves match the adopted contract. This fixture has current-public-API grounds, not fully adopted payload-label admission.

## Deliverables

Recover the original Chain identity regression and enumerate exactly this root's Optional producers plus the defining Lang Some declaration and Core Optional Chain producer. Plan the label handoff from canonical declaration through construction/pattern/member checks and the compiler's structural Optional consumer, keeping the four existing results and nominal/binder/empty controls. Distinguish payload-label migration from autounique/allowunique capability work (met-b2la); do not silently extend that epic or require its whole implementation just to classify this existing copyable case. Check correctly labeled construction, wrong-label rejection and corresponding Some/None decomposition under a coherent fixed Std input.

## Completion

An explicit bounded migration/disposition with concrete owned repair if needed, preserving the current regression and adopted public signature. This audit neither changes source/Std/expectations nor adopts an alias label or new rule. Unread Optional/Result fixture obligations remain in the audit; this is not an all-Std rewrite. Evidence: meta/evidence/test-audit/scoped-reviews/frontend-part-0003.json and its independent review.

## Explicit Three Array-Negative Producers

Batch0008 adds exactly tests/fixtures/reject/array_forward_context_block_conflict.pw, array_forward_context_explicit_conflict.pw, and array_forward_context_none_first.pw, with their .err companions. All root-authored Some constructors use current `v=` rather than adopted `value=`. The first two must fail for incompatible I64/U64 element context, not merely wrong label yielding a generic type-mismatch message. The third must preserve the leading unbound None forward-inference rejection; its later Some label still needs a coherent public-API migration.

Include these exact three roots with the existing namespace_chain_identity root, not every unread Optional/Result fixture. Preserve direct/block equivalence, explicit type mismatch and no later-element backward inference. No new label alias, capability feature prerequisite or source/expectation change is adopted by audit.

## Explicit Two Chain-Negative Producers

Batch0010 adds exactly tests/fixtures/reject/chain_missing_factory.pw with .err and chain_value_type_mismatch.pw (no companion). Both explicitly construct Optional.Some(v=...) against the current Std signature. Preserve missing empty() conformance versus continuation Value/result mismatch and the original source-anchor purpose as separate reasons; migrating labels is not proof those checks ran. The selected scope is now the original part Chain root plus five standalone negative roots, not the entire Optional corpus.

## Explicit Supplemental Coalescing Control

Batch0011 also reads run/try_coalesce.pw and .out as a positive for removed ?? versus current unwrapOr and try behavior. Its Some(v=5) is the same current/adopted payload-label difference. Include this exact pair in the finite label migration, preserving six outputs, successful/error propagation and eager/lazy fallback contrasts; no all-Optional corpus intake or new primary audit count.

## Explicit Enum-Destructure Supplemental Producer

Batch0013 adds exactly run/enum_payload_destructure.pw/.out. Its current Some(v=7I64) must migrate coherently to the adopted value label without dropping full/discard/bare-tag pattern coverage or changing 30/10/99 outputs. It is one supplemental pair, not an all-enum rewrite or a newly audited primary admission/outcome.

## Explicit Generic Associated-Self Supplemental Producer

Batch0016 adds run/generic_associated_self.pw/.out: two Some(v=value) constructors and the Some(v:val result) pattern use current payload label v instead of adopted value. Preserve generic/associated Self substitution through Optional[T], immediate unwrap and pattern extraction with 42/heap/42/heap outputs. This exact pair is not an all-Optional rewrite or a completed primary admission/outcome obligation.

## Explicit Generic Enum-Payload Type Negative

Batch0017 adds exactly reject/generic_enum_payload_wrong_type.pw. It intends Bool versus grounded I64 payload rejection but currently writes Some(v=true), against adopted Some(value:T). Preserve the payload-type reason through a coherent label migration; wrong-label rejection alone is not that type check. This is one named standalone negative, not an all-enum/Optional migration or a new primary credit for earlier controls.

## Explicit Generic Enum-Inference Supplemental Producer

Batch0017 adds run/generic_enum_field_inference.pw/.out. Root Some(v=...) constructors and v: payload patterns use current labels. Preserve inferred enum payload type/layout, forward context through block/match/array, owned String payload and all twelve outputs under the adopted value label. Panic fallback migration is com-bfvd's separately explicit exact root; no primary admission/outcome count is added.

## Explicit Guard Supplemental Producer

Batch0018 adds run/guard_stmt.pw/.out: three Some(v=...) constructors use the current label rather than adopted value. Preserve failure-branch return, successful binding escape, combined condition and all seven output lines under a coherent migration. Positional pattern binding is a separate contract, not automatically a mislabeled constructor. No execution or primary admission/outcome credit is added.

## Explicit Unknown-Variant Negative

Batch0020 adds reject/match_unknown_variant.pw. Some(v=...) construction and the v punned payload pattern use the current Optional label; reconcile both with adopted value while preserving the unknown Other variant rejection, not merely rejecting on label setup. com-ntm8 owns the selected reason-isolation requirement. This exact root is not an all-pattern migration intake.

## Explicit Optional-Chain Negatives and Receiver-Identity Control

Batch0022 adds reject/optchain_chain_incomplete.pw/.err and optchain_chain_not_nominal.pw/.err: their Optional.Some(v=...) producers use current rather than adopted labels. Preserve whole Chain requirements versus nominal-proof absence and their specific diagnostics. Custom MyOpt.Has(v:T) is its author's field label and must not be mechanically renamed. Supplemental run/overload_receiver_structural_identity.pw/.out uses <.Some v=5I64>; migrate that exact constructor while retaining nine overload/receiver/record/eager-lazy outputs. No unread Optional roots or primary admission/outcome credits are added.

## Explicit Generic Type-Checker Negatives and Context Control

Batch0027 adds exactly reject/tc_generic_arg_mismatch.pw, tc_generic_payload_value.pw and supplemental run/generic_enum_payload_context.pw/.out. Some(v=...) and v patterns require coherent adopted value-label migration. Preserve different Optional generic arguments, expected I64 payload checking and contextual integer typing in let/return/generic field positions with5/7/9 outputs. Wrong-label rejection must not mask the selected negative purposes (com-ntm8). Bare generic factory publication is com-owb3, not automatically an invalid binder.

## Explicit Trait-Method Result-Context Control

Batch0028 adds exactly supplemental run/trait_method_result_context.pw/.out. absent uses Optional.Some(v: _) against adopted value label; migrate that exact pattern coherently while preserving expected-result inference through required/provided/default generic members, block/if wrappers, associated output record members and bound discharge. Optional.None needs no payload-label change. This pair is a qualified control, not completed primary admission/outcome or a request to change inference semantics.

## Explicit Shared-Witness Optional and Protocol Negatives

Batch0029 adds exactly reject/trait_subject_chain_conflict_{existential_enum,protocol,protocol_bound}.pw/.err. Their Some(v=...) producers differ from adopted value. Preserve ambiguity inside shared witness bodies through generic erasure and direct/generic iteration protocol calls; the specific ambiguity companions must not pass on wrong-label rejection. The enum whole-container conversion has its separate com-vp0o setup disposition. No implicit label alias or new primary positive credit is adopted.

## Explicit Optional-Try Negative and Mapping Controls

Batch0030 adds exactly reject/try_on_optional.pw and supplemental run/{iter_map_retype,iter_for_map}.pw/.out. Their Some(v=...) producers need coherent adopted value-label migration. Preserve Result-only try rejection and generic Iterator map output-type retyping (five Bool outputs versus three mapped I64 outputs). com-ntm8 owns selected rejection isolation; no unread mapper corpus or new primary admission/outcome credit is included.

## Explicit Ambient and Existential Admission Producers

Batch0034 adds exactly run/{ambient_core,any_direct_optional_match,any_for_generic_iterable,any_for_iterable,any_for_iterator,any_heap_self_member_return,any_iterator}.pw/.out. Some(v=...) constructors and explicitly named v patterns differ from adopted value; positional payload patterns and None do not need mechanical renaming. Preserve ambient language vocabulary, legal bound Iterator/Iterable dispatch and explicit iteration binding semantics. Nominal Optional/Array[Self] result calls in two roots remain com-vp0o, so label migration alone does not certify those source admissions. This is seven exact roots, not the existential corpus.

## Explicit Optional Existential and Sendability Admission Producers

Batch0035 adds exactly run/{any_optional_covariant_erasure,any_optional_self_member_return,any_sendable_erasure,any_single_letter_trait_optional_self}.pw/.out. Some(v=...) producers and named v patterns differ from adopted value. Preserve direct existential guarantee erasure, direct Self dispatch and legal element/variant boxing contrasts under coherent label migration. All four roots already have separate forbidden container/nominal Self-result behavior in com-vp0o, so fixing labels alone does not certify admission. No new covariance or sendability-container lift is adopted.

## Explicit Forward Array and Reassignment Admission Producers

Batch0036 adds exactly run/{array_forward_element_context,assign_same_named_type}.pw/.out. Some(v=...) and named v patterns use current rather than adopted value payload label. Preserve already-grounded first-element context into later None, wrapped/branch/match/empty child arrays and contextual generic reassignment. The former root is already exact com-bfvd panic setup scope; coherent label migration alone does not establish all adopted source admission. No later-sibling backward inference is adopted.

## Explicit Synthetic Callable-Form Selection Producer

Batch0039 adds exactly run/callable_form_source_identity.pw/.out. The replacement helper constructs Optional.Some(v=declaration), against adopted value label. Preserve exact selected-declaration/conformance/type-argument mutation controls through coherent label migration; fixing the label alone does not settle the separate loop and ordinary-panic setup qualifications.

## Explicit Chain Producers and Named-Pattern Clarification

Batch0040 adds exactly run/{chain_generic,chain_trait,chain_wrapped_results}.pw/.out. Std Optional.Some(v=...) must migrate coherently to value. In chain_generic, Some(val v) is named-field punning for v:val v under spec11, so retain the binding name v by writing Some(value:val v), rather than exempting it as a positional payload pattern. Custom Loaded.Loaded(v:T)/Loaded(val v) remains its own correct field v and must not be renamed.

The same clarification applies to already exact owned run/{ambient_core,any_iterator,guard_stmt}.pw/.out and reject/match_unknown_variant.pw: each has Optional.Some(val v). Spec05 named fields and spec11 punning do not provide a separate positional-pattern exception. Older audit0018/0034 language calling these positional is corrected by a retained evidence amendment; original records/hashes stay intact. All four roots were already qualified for coherent label migration, so no primary count or adopted admission classification changes.

## Explicit Conditional Binding and Session Optional Patterns

Batch0041 adds exactly run/{cond_chain_bool_first,cond_chain_multibind,compiler_session_initializers,compiler_session_mid_requests,compiler_session_registry}.pw/.out. Some(v=...) producers and v: patterns use current Optional labels instead of adopted value. Preserve left-to-right condition binding scope/short-circuit, missing initializer/body lookup, prepared Mid reuse and session weak-handle lookup through coherent migration. Typed weak/reference API changes are independently met-op15. No ordinary Result labels or authored custom enum fields are mechanically renamed.

## Explicit Core Optional Producer

Batch0042 adds exactly run/core_lib.pw/.out. Some(v=7) uses the current Std API instead of adopted value label. Preserve predicates/unwrap and Result cases through coherent Optional producer migration; no blanket custom-v-field or Result rename.

## Explicit Declaration Index and Default Optional Patterns

Batch0043 adds exactly run/{declaration_identity_index,default_argument_bindings,default_argument_call_templates,default_body_demand}.pw/.out. Optional.Some(v:) patterns require adopted value label; retain authored local names and custom Explicit(argumentIndex)/Default(generator) fields unchanged.

## Explicit Default Projection and Dictionary Optional Punning

Batch0044 adds exactly run/{default_generator_shared_owner,dict_get,dict_str_value}.pw/.out. Some(val v) is named v-field punning, not positional payload matching. Migrate to Some(value:val v), retaining lexical generator projection, safe dictionary lookup/fallback and String results. Do not change custom field v of unrelated types.

## Explicit Dynamic and Existential Optional Labels

Batch0045 adds exactly run/{dynamic_closure_descriptor_identity,enum_generic_inst_payload,existential_declaration_plan,existential_payload,existential_rebox_evidence}.pw/.out. Current Optional.Some(v=...)/v: patterns and Some(val v) punning migrate to adopted value while local binding names remain. Already exact enum_payload_destructure is reused. Custom Tree.Leaf(v), Holder.Wrap(v), Opt.Some(v) are unrelated authored fields and stay v.

## Explicit Fallible Factory Optional Labels

Batch0046 adds exactly run/{factory_fallible,factory_requirement_fallible}.pw/.out. Optional Some(v=...)/v: patterns migrate adopted value label while custom Pct.v and Result.Ok(value)/Err(error) fields stay. Preserve optional/result success/failure and generic requirement behavior.

## Explicit Final Call Argument Store Optional Producer

Batch0047 adds exactly run/final_call_store_publication.pw/.out. Optional.Some(v=inputs) used by final argument publication needs adopted value label; preserve row-owned ranges, duplicate write rejection and snapshot isolation.

## Explicit Iteration Recipe Optional Pattern

Batch0048 adds exactly run/for_type_recipe_index.pw/.out. Optional.Some(v:_) patterns migrate to adopted value label, preserving absent/no fabricated recipe and copy-isolated high-ID checks.

## Explicit Generic Provided Members and Enum Payload Labels

Batch0049 adds exactly run/{generic_bound_provided_collect,generic_bound_provided_member,generic_enum_array,generic_enum_chain_match_print,generic_enum_ctor_arg}.pw/.out; generic_associated_self reuses existing exact intake. Migrate Some(v=...), v: and named valv punning coherently to adopted value while retaining provided Iterator proof and direct/array/chain enum payload contexts. Local custom v fields remain unchanged.

## Explicit Generic Enum Direct, Loop and Multi-Instance Labels

Batch0050 adds exactly run/{generic_enum_loop_constant_print,generic_enum_loop_i64_constant_print,generic_enum_match_print,generic_enum_multi_instance_print,generic_enum_multi_instance_print_annotated,generic_enum_string_match_print,generic_enum_two_match_print}.pw/.out; generic_enum_field_inference/generic_enum_payload_context reuse earlier exact intakes. Preserve direct/annotated/unannotated numeric/String arrays, loops, sequential matches and payload extraction; constant-body loop roots test admission/tag paths, not payload value output. User Maybe.v and Either.value/error are legitimate local names, not migration targets.

## Explicit Global Owner Optional Patterns

Batch0051 adds exactly run/{global_address_identity,global_call_constraint_evidence,global_initializer_requests}.pw/.out. Adopt coherent Optional.Some value label for sealed address, cursor and global request result patterns/construction; preserve negative absent/nonpublished owner facts.

## Explicit Guard, Newtype and Minimal-Std Optional Shapes

Batch0052 adds exactly run/{guard_completion_expression,i64_newtype_self,if_let,implicit_call_constraint_handoff}.pw/.out; guard_stmt already exact via earlier audit/correction. Guard/newtype/if-let constructors/patterns migrate coherently to Some(value:T). implicit_call_constraint_handoff embeds minimal plew:std/Lang.pw Optional(v:T), a standard API substitute needing coherent shape, not an arbitrary local custom enum v rename or all generic-capability implementation. Preserve retained implicit Add/Iterator evidence, not merely host source admission.

## Explicit Iterator Adapter and Interface Optional Shapes

Batch0053 adds exactly run/{interface_final_evidence,iter_adapter_terminal,iter_chain,iter_chain3,iter_chain_mapmap,iter_chain_multiline,iter_collect,iter_custom,iter_enumerate,iter_enumerate_heap,iter_enumerate_i32,iter_first_reduce,iter_fold_adapter,iter_fold_string_acc,iter_for_bare,iter_for_filter,iter_generic,iter_take_skip,iter_terminals}.pw/.out; iter_for_map/iter_map_retype reuse earlier exact supplemental intakes. Migrate StdSome v constructors, explicit v patterns and valv named punning coherently, retaining map/filter/take/skip/collect/fold/first/reduce/enumerate generic result and interface constraint evidence contexts. Local record value field remains unchanged.

## Explicit Match-Scrutinee Optional Shapes

Batch0054 adds exactly run/{match_expr_scrutinee_temp_arc,match_subexpr_scrutinee_arc}.pw/.out. Migrate StdSome v producer/pattern labels coherently, preserving selected held payload lifetime versus unretained scrutinee destruction and match-before-parent-call order. Custom Opt.v and ResultFile.file are not migration targets.

## Explicit Method Result and Mid Repack Optional Labels

Batch0055 adds exactly run/{method_result_bind,mid_ambient_effect_snapshot,mid_any_nested_optional_call_repack,mid_any_optional_array_call_repack,mid_any_optional_call_repack}.pw/.out. Some(val v) in method_result_bind is named v-field punning (spec11:136), not a positional exception. Coherently migrate standard constructors/patterns for Dictionary result, effect snapshot and nested Optional payloads; whole-container conversion source mismatch remains separately com-vp0o.

## Explicit Mid Generic Optional Construction

Batch0058 adds exactly run/mid_generic_enum_aggregate_construction.pw/.out/.ll.expect: standard Some v construction and pattern migrate coherently to value, retaining generic T grounding and selected enum/variant identity; unrelated custom payload names remain unchanged.

## Explicit Mid Global and Match Optional Labels

Batch0059 adds exactly run/{mid_global_storage_conversion,mid_match_owned_payload,mid_match_rvalue_scrutinee}.pw/.out. Standard Some v constructor/pattern labels migrate coherently to value, preserving local binding names and Some/None result behavior; nominal whole-container conversion separately com-vp0o.

## Explicit Mid Owned Optional and Readonly Weak Labels

Batch0060 adds exactly run/{mid_owned_conversion_boundaries,mid_owned_enum_call_copy,mid_owned_enum_copy,mid_readonly_weak_cell}.pw/.out. Coherently migrate standard Some v construction/patterns to value, preserving local names, None controls and weak live/dead transitions; nominal covariance and exact weak-handle API migration remain separate owners.

## Explicit Mid Optional Storage Payload Labels

Batch0061 adds exactly run/mid_storage_optional_conversion.pw/.out. Coherently migrate standard Some v construction and patterns to value while preserving local names/None controls; whole nominal covariance remains independently com-vp0o.

## Explicit Mid Value Context and Module Lookup Optional Labels

Batch0062 adds exactly run/{mid_value_block_context,module_source_attributes}.pw/.out. Standard Some constructors/patterns migrate v to value. The raw registered Optional(v) carrier inside mid_type_recipe_instances is deliberately synthetic and is excluded: its explicit owner/payload recipe test is not a Std declaration migration.

## Explicit Nested Enum and Newtype Boundary Optional Labels

Batch0063 adds exactly run/{nested_generic_enum,newtype_adapter_boundary}.pw/.out. Standard Some constructor/pattern v migrates to value, preserving inner versus outer generic instance identity and inherited Self adapter behavior. Array[Self]/Optional[Self] adaptation is explicitly allowed at spec10 newtype inheritance boundary; this is not generic nominal covariance.

## Explicit Chain and Unsigned Optional Label Controls

Batch0064 adds exactly run/{optchain_generic_method,optchain_multiparam_chain,optchain_place_arc,optchain_projected_result,optchain_propagate,optchain_propagate_ref,optional_chain,optional_unsigned_elem}.pw/.out, eight new pairs. Existing overload_receiver_structural_identity pair already exact Batch0022 is reused, not ninth new root. Standard Some v migrates to value; custom Slot.Full(v) and Cell.v remain. Preserve parametric/projection/multiparam/short-circuit/shared-handle and unsigned element purposes.

## Explicit Prepared Owner and Minimal Std Optional Labels

Batch0065 adds exactly run/{prepared_aggregate_source_owner,prepared_binding_source_owner,prepared_body_expression_owner,prepared_call_expression_source,prepared_match_source_owner,protocol_selected_result_authority}.pw/.out. First five host roots use standard Some v producers/patterns; protocol_selected_result_authority supplies parsed plew:std/Lang Optional(v), like existing0052 Std replacement. Both require adopted value label reconciliation. This differs from manually registered raw0062 custom carrier; do not rewrite arbitrary custom payload names. Preserve owner/global target/closure and exact Iterator selected result identity.

## Explicit Range and Recursive Record Optional Labels

Batch0066 adds exactly run/{range_custom_step_arc,rec_boxed_inout,rec_mutual,rec_struct_optional,rec_value_semantics,record_generic_method_arg,record_in_optional,record_nested_depth2}.pw/.out. Standard Some v producers/patterns migrate to adopted value; custom List/Tree fields and Cell.v remain. Preserve custom Step continuation, recursive CoW independence, grounded record method/payload and depth-two type identity.

## Explicit Recursive Instances and Shared Optional Labels

Batch0067 adds exactly run/{recursive_generic,recursive_generic_multi_instance,ref_arc_deinit}.pw/.out. Standard Some v producers/patterns migrate to value while custom Tree.Leaf(v)/Ping.v stay unchanged; preserve multiple recursive generic instances and shared Optional ownership timing.

## Explicit Inherited Iterator and Global Completion Optional Labels

Batch0068 adds exactly run/{self_inherited_iterator_runtime,semantic_checked_completion}.pw/.out. Std Some v in iterator result and globalInitializerTarget handle migrates to value, preserving selected iteration and refusal of unowned/completed global operation appends.

## Explicit Source Range and Operation Optional Labels

Batch0070 adds exactly run/{source_file_ranges,source_iteration_authority,source_operation_head_projection}.pw/.out. Some v patterns in reader/file handles and the supplied minimal canonical Lang Some(v:T) declaration migrate to adopted value label; the supplied standard resource is not an unrelated custom nominal enum. Preserve multi-file identity, selected next-result authority and scalar operation-head field correspondence.

## Explicit Typing Owner Completion Optional Label

Batch0071 adds exactly run/source_typing_owner_requests.pw/.out: the current completion-result Some(v:...) reader uses adopted standard payload label value instead. Preserve request-local failure, cursor restoration, retry counts and deferred closure preparation distinctions.

## Explicit Generic Field and Supertrait Optional Labels

Batch0072 adds exactly run/{struct_generic_inst_field,struct_generic_inst_field_mutate,supertrait_projection_witness}.pw/.out. Migrate standard Some v constructor/pattern labels to value while preserving nested nominal field substitution, mutation/None and selected inherited projection. User-defined Box.v and other custom payload names are unchanged.

## Explicit Lowered For Type-Use Optional Reader

Batch0074 adds exactly run/syntax_lower_for_type_uses.pw/.out. Host blockTypeUses reader pattern Some(v:uses) migrates to adopted standard value label, preserving record-pattern and typed-loop rebuilt-body type-use retention. User-defined Choice.Some in aggregate lowering is not this standard label. No exact type-use content/count or full semantic admission is claimed from two >0 outputs.

## Explicit Temporary Scrutinee Optional Labels

Batch0076 adds exactly run/{temp_match_scrutinee_deinit,temp_optchain_deinit}.pw/.out. Standard Some v construction/pattern labels migrate to value; Cell.v and Result value/error labels stay. Preserve temporary lifetime, scrutinee/optchain single evaluation and alias lifetime oracle without changing expected output during this audit.

## Explicit Weak Upgrade and While Binding Optional Labels

Batch0081 adds exactly run/{weakref_arc,weakref_dance_deferred,weakref_match_temp,weakref_upgrade_match,while_let}.pw/.out. Migrate standard Some producers/named v patterns and while_let Some(val v) punning to explicit value label while retaining local v and custom Cell.v/Node.x/Counter.n fields. Preserve alive/dead upgraded owner, deferred last strong release, direct temporary match and per-iteration condition binding purposes; reference/deinit API migration is separately owned.

## Explicit Unused Generic Optional Constructor Label

Batch0080 adds exactly run/unused_generic_enum_context.pw/.out. Standard Optional.Some v producer migrates to value, preserving unused generic T under explicit Optional[T] context and whole-target declaration checking. Empty stdout is deliberate source checking, not lazy-run body-demand or runtime payload proof.
