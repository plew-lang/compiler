---
id: com-lm8j
status: open
deps: []
links: []
created: 2026-10-27T20:14:26Z
type: chore
priority: 3
assignee: Koji Murata
tags: [verification, tooling]
---
# Align inspected fixture descriptions with current execution contracts

## Finite Documentation Correction

Selected source-audit descriptions assert mechanisms no longer owned by their current tests. Correct only the named comments/claim boundaries while retaining input behavior and meaningful assertions:

- run/assoc_val.pw: stored eager associated value, not a zeroarg function reevaluated per access; original fee81cae explains historical intent. Constants/read/composition output remains valid, not a startup-effect test.
- run/array_enum_payload_function_copy.pw: non-main call remains useful; no retired separate direct-LLVM path is claimed when bodies all require Mid.
- run/ambient_core.pw: fixed language-item names/syntax operations are ambient, not all of Core.
- run/any_box_value_semantics.pw, any_basic.pw, any_generic_param.pw, any_array_covariant_erasure.pw: logical value independence, not mandatory immediate deep copies or fixed8/16-byte physical layouts.
- run/any_for_iterator.pw: iterator() produces the protocol iterator copy; do not assert original binding state from loop output alone.
- part/trait_owner_reexport_generic/Main.pw: current signature has no associated projection; part/trait_owner_reexport_type is the separate concrete projection control.
- part/reexport/Barrel.pw: pub use supplies the local binding as well as forwarding; the consumer does not observe local binding in this fixture.

## Completion and Limits

Use spec/design as authority, preserve original limited regression purposes and links to separate stronger controls. Accurate descriptions of a deliberately tested internal representation need not be erased; remove only false current-path claims and wording that promotes an incidental mechanism to a semantic requirement. Actual fixture comment edits belong to repair after audit, no requirement to add every stronger interaction or rewrite outputs. any_array_covariant_erasure admission migration remains com-vp0o; coordinate rather than retain contradicted commentary. Do not add broad startup/ARC requirements to this chore. Verify comment-only diff/unchanged executable inputs, references and independent review; no fabricated TDD RED for prose. Evidence run-head-0087.json, part-tail-0087.json, runtime-batch-0088.json and runtime-batch-0089.json under meta/evidence/test-audit/scoped-reviews. This issue is separate from audit completion.


## Explicit Dictionary Rejection Comment

Batch0007 additionally reads exactly tests/fixtures/reject/any_dict_covariant_no_repack.pw and its .err. Rejection remains correct under generic invariance. The comment instead grants Array/generic-enum covariance and justifies Dictionary exclusion by historical fixed layouts/absent backend repacking. Align that one description with the adopted invariant source rule, preserving the useful direct per-insert boxing contrast and intended rejection; do not change semantics or golden just to retain a former physical explanation.

## Explicit Imported-Overload Tier Wording

Batch0005 also read exactly tests/fixtures/partreject/imported_overload_ambiguity/Main.pw and its .err. Its two numeric overloads legitimately make the unsuffixed literal ambiguous, but the comment calls a directly imported module a resolution tier. Canonical spec15 combines visible public candidate sets without source-origin priority. Keep the ambiguity assertion and describe that set rather than preserving an obsolete origin-tier model. No test behavior is changed in this audit.

## Explicit Generic Description Precision

Batch0017 adds optional description-only cleanup for exactly reject/generic_field_on_typeparam.pw (traits do support field requirements; this particular T has no bound granting field access) and generic_recv_arg_width.pw (comment says U32 but actual typed argument is I32). Preserve both valid rejections and executable inputs. These are not missing trait-field capability or numeric-conversion feature requests.

## Explicit Generic Capability Wording

Batch0018 adds optional comment precision for reject/generic_unique_arg.pw: the ordinary Box[T] parameter is copyable-only and correctly rejects File, but the comment's blanket claim that all generics are copyable-only is superseded by explicit unique/allowunique capability declarations. Preserve the useful ordinary-[T] negative and Ref-handle contrast without turning the old implementation limit into a new specification prohibition.

## Explicit Match/Method Historical Backend Comments

Batch0020 adds only reject/match_unknown_field.pw and method_value.pw as optional comment precision. Historical emitted-C/clang descriptions explain original failures but are not the current LLVM mechanism or oracle. Preserve unknown-field/method-nonvalue rejection. No source repair or new semantic requirement is implied.

## Explicit Generic Overload Rule Comments

Batch0022 adds reject/overload_generic_concrete.pw and overload_generic_nonoverlap_cycle.pw/.err as optional comment precision. The former is invalid because T and I32 can coincide, not because every generic/concrete pair is forbidden. The latter requires a discriminator at an individual argument position; its comment claiming cross-position joint unification must keep the declarations distinct contradicts the adopted rule and reject oracle. Preserve those rejections; no general solver or inference expansion is implied.

## Explicit Range/Provided-Method Control Comments

Batch0023 adds supplemental run/range_value.pw/.out and provided_method_valid.pw/.out only for optional comment precision. arr.count() is U64, despite an I64 comment; total returns first() rather than combining both requirements, while the golden3/4 is correct. Preserve the actual output and purpose instead of inventing a missing sum assertion. No primary source-admission/outcome credit is added.

## Explicit All-Diverging Match Negative Comments

Batch0025 adds exactly reject/source_divergent_mid_value_match_all_diverge_{choose,throughAggregate,throughCall}.pw and their .err contexts as optional comment precision. Historical comments describe producing a match result type or emitting Mid around wholly diverging value use, while current spec11 and these specific rejection oracles forbid such value use. Preserve those negatives and the partial-divergence normal control; do not reintroduce a bottom coercion or claim these compile-reject tests exercise runtime cleanup/CFG emission.

## Explicit Dictionary-Key Negative Comment

Batch0027 adds reject/tc_dict_key_type.pw for optional comment precision. Its .at desugaring, skipped generic-argument checking and exclusive TypeRef-checker explanation describe a retired mechanism. Preserve Dictionary[String,I64] versus I64 key rejection through canonical Index selection; do not weaken that valid negative or require a broad comment rewrite.

## Explicit Eager Cycle Purpose Comment

Batch0029 adds reject/trait_subject_cycle_generic_active_view.pw as optional purpose/comment reclassification. Bare A→B plus bundle E B→A is already rejected eagerly at declaration consistency, before the generic view body matters (spec09). Preserve the rejection but do not credit it as evidence that the generic body was visited. Neighboring source-set-only cycle tests supply the distinct late view obligation; no duplicate mandatory fixture or first-error recovery rule is required.

## Explicit Try Primitive Conversion Comment

Batch0030 adds reject/try_error_type.pw for optional comment precision. The valid rejection is absence of From[String] on the I64 target, not absence of all from factories merely because I64 is primitive. Preserve the same error-type conversion negative and avoid introducing a primitive-only exception.

## Explicit String Unary Negative Comment

Batch0031 adds reject/unary_neg_string.pw for optional explanation precision. This source has no applicable Neg witness, but being a standard primitive does not in general prohibit providing external-type operator conformance inside an explicitly selected named extension (spec09). Preserve the valid bare String unary rejection; do not infer a universal extension prohibition from the current witness set.

## Explicit Existential Value-Copy Comment

Batch0034 adds run/any_box_value_semantics.pw/.out for optional comment precision. Its required guarantee is that mutation of the original Array field does not change the boxed value; eager deep-copy at boxing is not required by CoW/value semantics. Preserve outputs1/99 while describing semantic independence without making a physical allocation strategy the oracle. This admission audit does not claim fresh execution or verify every existential copy/drop path.

## Explicit Ordinary-Function Enum-Copy Comment

Batch0035 adds run/array_enum_payload_function_copy.pw/.out for optional pipeline-description precision. Its ordinary function argument/append/enum-payload regression remains useful, but its comment describes ordinary LLVM lowering versus Mid as competing function paths. The adopted backend consumes canonical Mid for ordinary functions too. Preserve the non-main ownership/source path without claiming an AST backend or duplicating an obsolete pipeline authority. This source-admission audit does not newly certify its runtime/memory outcome.

## Explicit Same-Named Assignment Identity Comment

Batch0036 adds run/assign_same_named_type.pw/.out for optional explanation precision. Its same declaration and same complete Optional/Result instances should reassign, but the comment same head name implies same id is not the general identity rule. Nominal owner and all type arguments remain part of identity. Preserve the exact contextual reassignment regression without endorsing head-only type compatibility.

## Explicit Buffer, Foreign-Identifier and Cast Comments

Batch0039 adds run/{buffer_floor,buffer_index,c_reserved_idents,cast}.pw/.out for optional purpose/comment precision. Ordinary Array/Buffer representation and Index semantics are owned by canonical design, so historical ptr/i64 or not-an-index-witness comments must not mandate a competing semantic path. C-reserved identifiers remain valid Plew names, independent of a retired generated-C backend. Cast is total/infallible, not necessarily lossless, and some signedness changes such as this root U16→I32 are total. Preserve all valid sources/results; no new cast rule, source-specific lowering or memory proof is introduced.

## Explicit Closure Capture and Temporary-Lifetime Comments

Batch0041 adds run/{closure_shadow_capture,closure_temp_arg_arc}.pw/.out for optional explanation precision. Capture identity is lexical independently of the retired generated-C suffix mechanism, and the first shadowed x is actually mut. Call-argument temporary retention ends at the called closure completion before the outer expression resumes (spec03:113), not generally at outer statement end. Keep source/ownership regressions; this admission audit does not certify output discrimination of cleanup timing or add unread outcome work to this comment task.

## Optional Dictionary Lowering Comment Precision

Batch0044 records optional comment precision only for run/{dict_compound_assign,dict_str_value,dictionary_subscript}.pw/.out. Literal-key compound assignment is valid; shorthand d[k]=d[k]OPv must not imply reevaluating a nonliteral place/key. Old at/insert lowering descriptions are not authored calls in these fixtures; use selected Index/IndexSet contracts when refreshing prose. No mandatory new behavior test or source change follows from this comment-only observation.

## Optional Enum Migration Comment Precision

Batch0045 adds optional prose-only run/enum_record_form.pw/.out. Its custom Opt.Some(v:T) source is valid, but old brace-form accepted-during-migration comment is not the adopted record-variant syntax contract. Refresh commentary without renaming authored custom v or requiring new behavior coverage.

## Optional Factory and View Resolution Comments

Batch0046 adds optional prose-only run/{factory_gate_valid,extension_overload_view}.pw/.out. Module-private factory is usable from same-module free functions, not only anonymous impl; view overload meaning is decided/retained before backend consumption, not repaired from local spelling there. Current test inputs are legitimate, comments not source rules.

## Optional Conversion and Callable Completion Comments

Batch0048 adds optional prose-only run/{from_conversion,function_completion_type_identity}.pw/.out. Numeric as uses primitive From factories too; they are not exempt from that adopted contract. Diverge surface is connected, so the completion identity test should describe its finite metadata guarantee without future-only surface wording. Synthetic () name is not a new source Unit representation requirement; current typed source/results stay unchanged.

## Optional Generic-Free Function Mode Comment

Batch0050 adds optional prose-only run/generic_free_fn.pw/.out: qualify eagerly checked bodies by check/build versus demanded run behavior. Its declared Getter bound and concrete outputs remain meaningful; no mandatory eager-run test or new source failure is asserted.

## Optional Transitive Generic Mode Wording

Batch0051 adds optional prose-only run/generic_transitive.pw/.out: eager abstract bound checking describes check/build, while run may defer unneeded source bodies. Preserve outer-to-inner declared Getter proof forwarding and outputs; no mandatory eager-run execution is introduced.

## Optional Hash Seed Contract Wording

Batch0052 adds optional prose-only run/hash_siphasher.pw/.out. Current SipHasher.new uses per-process random key, so fixedseed wording should state equal-input same-process behavior. Selected differing key samples are useful regressions, not a universal no-collision contract. Do not freeze magic digest values or change current golden based only on cross-process key variability.

## Optional Iterator Terminal and Binder Explanations

Batch0053 adds optional prose-only run/{iter_adapter_terminal,iter_fold_adapter,iter_terminals}.pw/.out. Adapter fold and terminal support is exercised by neighboring roots, so old future-gap wording is stale. Method-owned and receiver binders use distinct identities rather than last-name-match shadowing. any/all short-circuit per current public API instead of necessarily exhausting iterator; retain current finite result checks and avoid inventing a new exhaustive-consumption requirement.

## Optional String Identity and Temporary Ownership Wording

Batch0054 adds optional prose-only run/{let_infer_string,make_literal_arg_arc}.pw/.out. Arbitrary source String spelling is not semantic type authority; use resolved ambient declaration/recorded term description. A call-owned temporary ends retention at its target call completion, not generally full statement end; preserve legitimate result ownership and separate IndexSet evaluation. Current goldens do not assert wrong deinit timing or prove ASan was executed by this audit.

## Optional Receiver and Entry-Path Descriptions

Batch0055 adds optional prose-only run/{methods,mid_access_inout_argument_cfg_lowering,mid_access_nested_argument_cfg_lowering,mid_access_nested_return_cfg_lowering,mid_access_receiver_cfg_lowering}.pw/.out, plus already-read supplemental pub_get_field.pw/.out. Plain fn self is a read borrow, not a by-value snapshot; four main-legacy comments predate verified-Mid-only entry path. Supplemental pub(get)/private access is module-scoped, not restricted to anonymous impl. Preserve existing finite source/output/IR purposes; do not claim module-wide mid marker proves one body or require new modes just for prose.

## Optional Mid Lifetime and Legacy-Path Descriptions

Batch0057 adds optional prose-only run/{mid_conditional_unique_move_cfg_lowering,mid_default_enum_owner_return,mid_default_field_fallback,mid_direct_call_cfg_lowering,mid_enum_aggregate_construction}.pw/.out and IR companions where present. Four comments retain obsolete AST/legacy body staging; current main and ordinary functions require verified Mid. conditional_unique_move describes retained ownership as lasting to enclosing scope, but actual accessibility-cliff cleanup is at the join, immediately followed by scope exit here. Preserve meaningful exactly-once behavior without treating this stdout as proof of scope extension; no mandatory new mode or code repair solely for wording.

## Optional Mid Buffer and Aggregate Entry Descriptions

Batch0056 adds optional prose-only run/{mid_body_build_return_error_match,mid_buffer_append_cfg_lowering,mid_buffer_clear_cfg_lowering,mid_buffer_eq_cfg_lowering,mid_buffer_remove_last_cfg_lowering,mid_buffer_reserve_cfg_lowering,mid_buffer_set_cfg_lowering}.pw/.out and registered IR companions. Six legacy/main/body comments predate verified-Mid-only ordinary/helper/entry emission. clear capacity equality describes current implementation rather than unspecified adopted clear capacity; truncate equality analogous current observation, not a new source ban. Preserve finite assertions and source purposes, no mandatory new mode solely for wording.

## Optional Mid Free Function and Field Replacement Descriptions

Batch0058 adds optional prose-only run/{mid_field_overwrite,mid_free_function_copy_return_cfg_lowering,mid_free_function_direct_call_cfg_lowering,mid_free_function_move_return_cfg_lowering,mid_free_function_parameter_cfg_lowering,mid_free_function_return_cfg_lowering}.pw/.out and registered IR companions. Five global-anchor/main-legacy claims and field-overwrite legacy-emitter staging predate verified-Mid-only entry/helper emission. A module-wide mid marker does not itself locate one helper. Keep finite call/parameter/result/field purposes; no runtime/compiler change or mandatory new matrix solely for prose.

## Optional Mid Local Loop and Receiver Descriptions

Batch0059 adds optional prose-only run/{mid_local_assign_cfg_lowering,mid_loop_exit_cfg_lowering,mid_method_call_cfg_lowering,mid_method_receiver_field_cfg_lowering}.pw/.out and registered IR companions. Legacy main/callee subset assumptions and by-value-self wording predate shared verified Mid and read borrowing. Preserve local/loop/receiver projection purposes; module-wide marker is not a unique helper proof and no new execution matrix is imposed solely for prose.

## Optional Mid Wide Operand and Operator Legacy Descriptions

Batch0060 adds optional prose-only run/{mid_operand_build_error_propagation,mid_operator_call_cfg_lowering}.pw/.out/.ll.expect. Producer-outside-minimal-Mid/main-legacy assumptions are obsolete under shared verified Mid. Operand golden correctly distinguishes UnsupportedCall42 from None0; do not assign the distinct batch0056 identical-arm detector defect to this input. Preserve typed operator and wide-tail enum semantics, no mandatory new modes solely for comments.

## Optional Mid Short Circuit Legacy Description

Batch0061 adds optional prose-only run/mid_short_circuit_cfg_lowering.pw/.out: global anchor does not keep main legacy under verified-Mid-only entry. Preserve short-circuit effect/loop/argument/negation outputs, no mandatory new coverage matrix solely for wording.

## Optional Mid While Legacy Description

Batch0062 adds optional prose-only run/mid_while_cfg_lowering.pw/.out/.ll.expect: global anchor no longer keeps main on legacy lowering, and module-wide mid marker does not uniquely locate loopNoop. Preserve while backedge/fallthrough purpose without introducing mandatory new modes solely for wording.

## Optional Nested Newtype and Ambient Description Precision

Batch0063 optional prose-only run/{nested_aggregate_owner_return,no_import_main,newtype_string_inherit,newtype_struct_inherit}.pw/.out. Mandatory verified Mid supersedes legacy while comment; Lang transitively uses Core; bytes() is method not field; trait mark does not also prove separate inherent method. No new matrix, source or golden change required solely for wording.

## Optional Overload Selector and Direct Finalizer Description

Batch0064 optional prose-only run/{overload,p2_finalizer_direct_call}.pw/.out. Selector is name+labels, argument types distinguish its overloads; finalizer no longer flows through legacy emitter. Empty outputs do not mandate an extra outcome matrix solely to correct wording.

## Optional Array Receiver and Primitive Format Description

Batch0065 adds optional prose-only run/{prelude_array,print_format}.pw/.out. Receiver get/set resolution needs no method import but these are not ambient free names; selected I8/U8/I32/I64/U64+Bool sample is not all integer widths. Existing provided_method_valid0023 (total returns first) and pub_get_field0055 (module-private versus impl-only) exact comments reused, no duplicate intake or mandatory new width/mode matrix.

## Optional Shared-Reference and Enum Pattern Descriptions

Batch0067 optional prose-only run/{ref_arc_deinit,ref_arrow_method,ref_scalar_literal,rename_bind}.pw/.out. peek comment mentions nonexistent make/returned Ref; read-only Ref dereference is not MutableRef-only, scalar whole-pointee access is not an adopted unsupported rule, enum rename/discard uses parentheses not braces. No extra runtime assertions required solely for wording. Repeated Holder publication separately stays met-4slo finite question, not a proven duplicate custom body.

## Optional Runtime Smoke and Self-Resolution Descriptions

Batch0068 optional prose-only run/{runtime_intrinsic_process_smoke,self_param_conformance,self_param_conformance_enum,self_return}.pw/.out. Smoke calls bundled Process.argCount rather than ordinary lookalike extern; numeric/entropy identity tests separately cover ordinary symbols. Self typing/grounding belongs before final backend consumption, rather than historical backend cursor. No extra runtime matrix solely for wording.

## Optional Shadowing Backend Description

Batch0069 optional prose-only run/shadowing.pw/.out: same-block rebindings must retain lexical identity through the current Mid/LLVM pipeline, not generated C. Preserve scalar/type/Array binding behavior; no new mode matrix solely for wording.

## Optional Path-Root and Witness Evidence Headers

Batch0071 optional prose-only run/{source_path_root_owner_evidence,source_selected_witness_owner_evidence}.pw/.out: copied box-target header is broader than actual all-any-P subject/binder/root/witness compatibility contrasts. Actual current-path births778263f8/ba295008 differ from --follow box ancestor38d7121c. Preserve meaningful evidence predicates, without inventing a new target-mismatch matrix solely for wording.

## Optional String Byte API Descriptions

Batch0072 optional prose-only run/{string_bytes_count,string_methods}.pw/.out. Clarify bytes() returns a logical CoW Array rather than a borrowed Slice, and avoid suggesting public backing-field access. Preserve source/outputs; no required new runtime matrix or API expansion solely for wording.

## Optional Direct Syntax Mechanism Claim Precision

Batch0073 optional prose-only run/{syntax_direct_entry_cast,syntax_file_direct_top_level_forms}.pw/.out. Goldens show Cast/U64 shape or selected13members/top-level kinds/mode fields; they do not alone prove every grammar form or absence of an internal value-AST/freezer bridge. Shared pinned Syntax entry and registered source architecture gates are separate evidence. Preserve fixtures/goldens and useful direct-shape regression; no mandatory new matrix or renaming merely because historical filenames contain freeze.

## Lowered Call and Method Header Precision

Batch0075 optionally reconciles run/syntax_lower_method_exprs.pw and supplemental syntax_lower_call_expr.pw headers: argument-context selection/lookup is not asserted by their Lower-only receiver/name/label/expression metadata outputs. Preserve all fixtures/goldens; neither current argument-context selection correctness nor a new mandatory matrix is certified. The supplemental free-call source/out was fully read in0074 and rechecked unchanged here; only method primary roles receive0075 credit.

## Temporary Lifetime and Trait Namespace Comment Precision

Batch0076 optionally updates exactly run/temp_stmt_end_deinit.pw header: call-owned temporary ends at call completion, not a blanket every-temporary statement-end rule. Its next-statement output does not discriminate the two timings. Also qualify run/trait_assoc_fn.pw old Hash.derive analogy: it exercises ordinary trait-associated namespace calls, not adopted macrointerface generation. Preserve fixtures/goldens; no new mandatory lifetime or macro matrix.

## Checked Conversion and Selected Witness Header Precision

Batch0078 optionally qualifies exactly run/{try_from_generic_convert,tryfrom_float_unsigned,tryfrom_narrowing}.pw headers. Selection belongs to checker/prepared/mono facts, not backend convert-or-not name matching. Obsolete convert(from:) fragments should describe checked(source:) API without changing assertions. float unsigned selected negative is -1.0: current Core source<0 gate differs from adopted integer-part range wording for unselected (-1,0), so do not call all negative floats a proven universal source rule or claim that unselected boundary was audited. No new mandatory conversion matrix or automatic golden rewrite.

## Trait Declaration Identity and Source Wrapper Header Precision

Batch0077 optionally qualifies exactly run/{trait_name_collision,trait_name_collision_provided,trait_source_select}.pw. Lexical declaration ownership/full trait instance, not merely requirement shape or name+arity, separates local trait spellings and canonical operator identities. srcTraitId/findExtMethod remain actual current names; the shared wrapper must preserve semantic source kind/owner, so do not call these removed APIs. Retain inputs/goldens, not a new mandatory matrix.

## Type Arena and Unique Ownership Header Precision

Batch0079 optionally qualifies exactly run/{type_arena_push,u64_literal,unique_ref,unique_reassign}.pw. pushType tested plain/helper/Box/binder shapes do not establish universal one-row allocation when projection receiver publication may precede the main row. U64 uses LLVM backend, not emitted-C ULL. unique_ref old blanket unique-generic prohibition is obsolete under adopted capability work. unique_reassign observes old release before next statement, not RHS-acquisition/commit/drop order by itself; do not infer a new assignment rule. Preserve fixtures/goldens and finite purpose; no mandatory new matrix.

## Weak Reference Cycle and Safety Claim Precision

Batch0081 optionally qualifies exactly run/weakref_arc.pw: early prose says Child-before-Parent, while later explanation/current golden70→80 is Parent-before-Child after selected949e7b4 change. Normal deinit markers observe selected owner release/count/order; they do not alone prove absence of all UAF/leaks or fixed RC decrement implementation. Historical ASan-clean comment is not fresh execution. Preserve fixture/golden and weak ownership purpose, with separate sanitizer boundaries; no mandatory new safety matrix.

## Collection Safety and Value Receiver Header Precision

Batch0080 optionally qualifies exactly run/{user_collection,value_branch_receiver}.pw. Historical ASan/leaked-safe and concrete RC/commit mechanism prose is not fresh verification or proved by functional stdout. Current checked source facts and retained selection own branch-result receiver type/dispatch; backend re-solving is historical, not adopted authority. Preserve all output/assertion purposes without a new mandatory lifecycle/dispatch matrix.

## Generated Provider Comment Precision

Batch0001 remaining gen optionally qualifies directiveargs/directivealias project comments (App/Left/Right): public configured factories do not require every field public. enumeqtag module-0 collision and structdictkey old backend Eq/layout prose describe history/implementation, not adopted restrictions or fresh architecture proof. Preserve current consumer-root Hasher binding and current valid provider lanes; no new mandatory coverage matrix.

## Buffer Observable Guarantees and Mechanism Prose

Batch0091 optionally qualifies exactly run/{buffer_cow_field,buffer_insert,buffer_nested,buffer_removal,buffer_string,buffer_struct_field}.pw/.out. Preserve values, sizes, alias independence and actually owned lifetime purposes. Normal stdout is not proof of all retain/drop counts, leaked/freed memory, exact header/growth/memmove mechanisms or a fresh ASan result. A returned removeLast String is owned by caller, so buffer_string prose must not imply immediate destruction of the returned element. Existing0039 buffer_floor/buffer_index/c_reserved_idents descriptions are exact reuse, not three further intakes. Literal-element retirement detection is separately mandatory com-4vr8; do not reduce that repair to wording.

## Async Teardown Source and Completion Responsibilities

Batch0090 optionally qualifies exactly run/async_arc_teardown.pw/.out. Its header attributes all source-local release to final resolve, while the current MidAsync completion tail runs after source Drop and only releases its activation Promise/frame responsibility. Preserve the four output lines and copied String/temporary/named Promise lifetime purpose. Normal stdout is not a fresh LSan result or exact retain-count proof; do not remove a legitimate memory-check goal or substitute prose for detection. No new mandatory case matrix or production repair in this audit.

## Closure Parameter Cleanup Description

Batch0092 optionally qualifies exactly run/closure_param_borrow_arc.pw/.out. Lengths15/5/3 after repeated closure parameter/fallthrough calls preserve the value/retention regression, but do not count exact +0/per-activation retain/unwind operations or prove all memory safety. Align any mechanism prose with current source-owned call/environment cleanup rather than deleting legitimate historical context. cast is existing0039 exact reuse. closure_array_for_arc two-word historical payload context and two concrete release markers are retained: the preliminary universal-layout concern was withdrawn, with no new intake or mandatory matrix.

## CoW Observable Independence and Historical Gateways

Batch0094 optionally qualifies exactly run/{cow_construct_share,cow_enum_share_mut,cow_gw_elem_field_array,cow_string_elem}.pw/.out. Preserve independent values and genuine heap-backed String coverage. Outputs do not require physical RC sharing instead of eager copying or prove fresh ASan cleanliness; old consumeIntoOwned/placePtrOfWrite/sole-gateway wording must not designate a competing current authority after canonical Mid ownership. Keep accurate finite historical internal context rather than erasing every mechanism description. dict_compound_assign is existing0044 exact reuse. No mandatory universal cost/safety matrix or audit-time source repair.

## Compound Place Mechanism and Construction Examples

Batch0093 optionally qualifies exactly run/{compound_assign_place_once,construct_field_literal}.pw/.out. Preserve one evaluation of the side-effecting place key and contextual record/Dictionary field values. A retired named-Lower implementation explanation must not become a second current authority; Unit is not an actual selected field example in construct_field_literal and needs no mandatory new test solely to satisfy prose. closure_shadow_capture and closure_temp_arg_arc are existing exact descriptions, not two new intakes; the latter lifetime detector gap is independently mandatory under met-6zp3.

## Floating Print and Compound Assignment Descriptions

Batch0097 optionally qualifies exactly run/{float_compound_assign,float_literal}.pw/.out: the old local-kind explanation is historical, and current generic Io.print constructs String through Format rather than directly calling plew_print_f64 for those expressions. Preserve the finite numeric results and genuine historical context; no numerical representation redesign or added universal precision matrix is required. from_conversion is existing0048 exact prose reuse; float_f32 physical-double comment is already within com-s922 finite source/precision qualification. Audit makes no fixture/compiler repair or execution.

## Division Helper Description

Batch0095 optionally qualifies exactly run/div_mod.pw/.out: historical plew_div/plew_mod names no longer designate the current checked LLVM width-helper path. Preserve selected signed truncation/remainder outputs and true historical purpose; no numerical redesign. dict_str_value/dictionary_subscript/enum_record_form are prior0044/0045 exact prose reuse. No audit-time source repair or execution.

## Generic Enum Result and Dispatch Descriptions

Batch0099 optionally qualifies exactly run/{generic_enum_array,generic_enum_dispatch}.pw/.out. Preserve genuine historical8/16byte stride failures and inline enum argument purposes. Old exprLlvmType/llvmArgTypeRef or backend resolver explanations are historical rather than current semantic selection authorities; prepared result readers consume saved facts rather than construction-time grounding. generic_free_fn is prior exact prose reuse; checking is command/demand-sensitive, not proved eager by the output. Preserve current finite values, no source repair, numerical redesign or all-mechanism comment sweep.

## Mutual Generic Body Description

Batch0100 optionally qualifies exactly run/generic_mutual_recursion_body_instances.pw/.out: left/right are two distinct generic declarations, each body shared across its own I64/String instances. The header singular shared-AST wording should not imply both declarations have one body identity. Preserve mutual recursion/instance outputs7/tea; no added test or compiler repair. generic_transitive/hash_siphasher reuse existing exact command-sensitive checking/process-seed descriptions, without demanding collision freedom for all hash seeds.

## Generic Associated Call and Inference Examples

Batch0098 optionally qualifies exactly run/{generic_assoc_fn,generic_ctor_infer}.pw/.out. Pair.of/Box.make/dup are associated functions rather than multi-parameter factories; the inference header Map example is actually Pair[U64,U64] in source. Preserve six transitive associated-call and four top-down/multi-parameter inference outputs. The separate generic publication identity question stays with com-owb3. No source repair, added universal matrix or erasure of legitimate old representation failure context.

## Grounded Method-Result Description

Batch0103 optionally qualifies exactly run/method_result_bind.pw/.out. The original22d54d8e exprResultRef helper explanation is legitimate history but no longer a current semantic authority; preserve unannotated grounded Optional method-result binding, Some extraction and missing-key fallback2/99. This is one optional comment pair, without new tests or runtime repair. methods and four Access main-legacy descriptions reuse Batch0055 scope; old staging explains the original regression without claiming current alternate emission.

## Iterator Prefix and Loop Cleanup Descriptions

Batch0102 optionally qualifies exactly run/{iter_take_skip,loop_arc,loop_shortcircuit_elem_arc}.pw/.out. Preserve the original lazy prefix/skip and loop/conditional temporary cleanup purposes and finite values. adapterCallResultInst, drainStmtTemps and backend loop-frame explanations are historical rather than current semantic authorities; no new ASan execution is established by an ASan-clean comment. iter_terminals/let_infer_string/make_literal_arg_arc reuse earlier exact descriptions. Do not erase genuine prior validation history, add a broad mechanism sweep or require new runtime cases solely for prose.
