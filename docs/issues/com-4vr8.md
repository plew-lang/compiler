---
id: com-4vr8
status: open
deps: []
links: []
created: 2026-10-27T20:14:26Z
type: bug
priority: 2
assignee: Koji Murata
tags: [runtime, ownership, verification]
---
# Exercise owned String retirement in the array mutation regression

## Evidence

Exact tests/fixtures/run/array_string_set_pop.pw, source baseline9665094d. All old/new elements are direct String literals. Backend/Llvm/StringOps.pw::genLlvmStr emits module-static rawbuf with immortal RC sentinel, and Arrays.pw::valueArc preserves that lifetime. Consequently this source cannot substantiate its claimed detection of misbalanced retired String release; ordinary outer-array CoW values are still meaningfully checked. Original cb7443daa77f8bb38e91e6ba3cce477c9e522b10 explicitly targeted old-value retirement with a second owner. This is a confirmed assertion-path gap, not a reproduced compiler memory fault.

## Guarantee and Controls

Keep the current value/size/second-owner observations and add actually managed heap-backed old/new String elements through set and discarded removeLast, including repeated replacements. Confirm selected candidate really allocates the tested String buffers; constant-folded/interned output cannot stand in for a releasable owner. Demonstrate missing-release versus excessive-release discrimination with appropriate sanitizer/leak or owner-lifecycle controls, and correct results on the real path. Do not weaken normal runner, claim normal stdout alone proves memory safety, or edit generated LLVM as a fix.

Existing buffer_capacity_cow uses dynamic Strings only through append/reserve/insertAt, so it is a useful contrast but not the set/removeLast path. Preserve its scope; do not silently reopen closed com-p10m or transfer into broad com-zgk9. Relevant real instrumentation must be confirmed rather than inferred from an ASan option. No full collection rewrite, new API or unrelated leak cleanup. TDD, fixed inputs/candidate and independent review required. Evidence runtime-batch-0089.json and selected String emitter paths; audit performed no program/sanitizer execution or repair.


## Buffer Field and Removal Paths

Batch0091 adds exactly run/{buffer_cow_field,buffer_removal}.pw/.out. Actual adding6a681faf/bda1e917 targeted field-place CoW and owned String retirement/removal respectively. Their stored String elements are all direct immortal literals, so omitted/excessive per-element retain/drop cannot substantiate the intended retirement/safety detection. Ordinary logical CoW, sizes, removal order and returned values remain useful. Include genuinely releasable old/new elements and discriminating ownership/instrumentation controls for field set/removeLast and removeAt/swapRemove/truncate/clear, without changing their value guarantees or inferring a current compiler fault. Existing buffer_capacity_cow dynamically constructs its elements after e1024192; buffer_string has dynamic concatenation, nested buffers are owned heap objects, so these are contrasts rather than the same gap. No repair or ASan invocation performed in audit.

## Dictionary Dense Removal

Batch0095 adds exactly run/dict_remove_str.pw/.out. Original a31f5659 and current source expressly target String key/value dense-swap retain followed by tail drop. All tested keys and values are direct immortal literals, so omitting a String retain before tail retirement does not free the backing; current survivor/count outputs and even real C ASan could miss that targeted ownership fault. Preserve survivor lookup, absent-key/count and complete removal observations. Add genuinely releasable key/value backings and selected-path lifecycle/instrumentation discrimination for this exact Dictionary dense removal, not just textual claims or a whole collection rewrite. Existing dynamic Strings in for_struct_destructure_arc/cow_string_elem and Dictionary MutableRef overwrite contrasts exercise different ownership paths. No current compiler memory fault reproduced and no audit-time test/compiler/expectation/runner repair or sanitizer execution.

## Discarded Place Versus Owned Result

Batch0095 additionally adds exactly run/discarded_result_arc.pw/.out after a parent-origin post-initial question and independent validation. Original bb92b015 explicitly requires a discarded place read not to release its named owner. Current keep=label(5) holds an immortal literal, so wrongly dropping that place owner can still leave the same pos/done output and no freed backing. Use a genuinely releasable keep and direct-result counterpart to distinguish borrowed place disposal from owned temporary cleanup; verify the selected candidate actually allocates the observed owner. Existing concat and tagged-construction results already carry managed storage and retain their valid cleanup/LSan purpose. This is a narrow assertion-path gap, not wholesale test invalidity or a requirement for all call forms. No current compiler defect reproduced, actual instrumentation run or source repair.

## Saved Custom Index Key

Batch0101 adds exactly run/index_evaluation_custom_key.pw/.out. Original40ae40d6, ownership design153–158/188 and the focused index guide target saved evaluated keys including owned fields. Key.name is always an immortal literal; omitting its saved retain before adjust replaces the original key can preserve every key/getter/setter/updated-target output and evade even actual app ASan. Preserve current once/order/first-target observations and add genuinely releasable owned String backing across this exact freeze/replacement/writeback path, confirming managed storage and discriminating selected lifetime/instrumentation. iter_enumerate_heap is a managed-storage contrast on a different path. ASan E only compiles this source under an instrumented compiler; C executes generated code but discards stdout; normal and the focused diagnostic compare output. No current compiler memory fault, actual sanitizer run, source repair or broad key matrix is claimed.

## Physical String Field Retirement

Batch0106 adds exactly run/mid_field_overwrite.pw/.out. Actual05e13de explicitly targets physical field String old-owner release, nested replacement and RHS completion before retirement. Every old/new String and replacement() result is a direct immortal literal; omitted/excess finite release can preserve all six outputs. This is a static assertion-path gap, not a reproduced compiler memory fault. Preserve value/nested/RHS-print/counter observations and reconcile the ownership purpose with releasable backings and discriminating lifecycle/instrumentation evidence. Existing static_view_value_arc provides a managed-shaped ordinary field replacement/alias contrast; mid_reference_write and other field/Ref controls are complementary. Reuse them where their real path and selected candidate allocation satisfy the purpose; do not claim all managed field coverage is absent or require a new case for every helper/projection. No tests, compiler, runner or sanitizer execution were changed/performed.

## Temporary Indexed String Result

Batch0107 adds exactly run/mid_index_rvalue_field.pw/.out. Actual1b7efeb0 explicitly targets evaluating Items temporary before key once each and owning the String element after temporary/Array cleanup. Its sole kept element is an immortal literal, so omitting the returned element retain can preserve10/20/kept and leave no freed String backing for application ASan to detect. Preserve order/value checks and exercise this exact temporary-index-result ownership with releasable storage and discriminating lifecycle/instrumentation evidence; selected candidate allocation must be verified. Existing cow_string_elem and mid_return_bytes_cow are useful managed contrasts on different owner paths, not proof this literal fixture detects a missing retain. No claim of current compiler fault, broad missing coverage, all-call matrix, repair or actual execution.

## Returned Matched String Payload

Batch0108 adds exactly run/mid_match_owned_payload.pw/.out after an independent initial observation and parent-prompted finite reassessment. Actual c99ca7d2 explicitly requires a returned Copy to survive scrutinee cleanup. Current pattern bindings are independent copies; preserve that semantics rather than requiring original borrowed lowering. Both yes/none backings are immortal literals, so missing managed-String acquisition can preserve the two outputs. The old fifteen-line checker only excluded legacy build:match and was retired by fc8bf4a2; current structural ownership checks do not assert this generated result lifetime. Preserve branch/value observations and reconcile the exact ownership purpose with a releasable payload and discriminating lifecycle/instrumentation or precise structural evidence, confirming actual candidate allocation. Existing managed aggregate/Ref matches and Array[U8] TOML payload returns are complementary and may be reused where the path matches; do not infer absence of all managed match coverage. Existing Some-label migration is separate. No current compiler memory fault reproduced, all-type/mode matrix required, production repair or real execution performed.

## String Snapshot Before Sibling Effects

Batch0110 adds exactly run/mid_value_evaluation_order.pw/.out. Actual585e865f/6e01cdc2 require earlier String/global/parameter/Snapshot value copies to survive later sibling replacement. All before/after backings are direct immortal literals, so a missing saved String acquisition can preserve all six outputs despite retiring the original owner. Scalar1/1/1 snapshots still discriminate stale rereads. Reconcile this exact lifetime purpose with genuinely releasable backing and selected lifecycle/instrumentation evidence; confirm actual allocation and reuse matching existing controls. cow_string_elem and value_snapshot_callback offer useful managed String/Array contrasts on other owner paths; neither automatically certifies this saved String-before-sibling-retirement detector. No current compiler fault reproduced, all-call matrix required, source/runner repair or actual execution performed.

## Viewed String Receiver Source Ownership

Batch0111 adds exactly run/operator_receiver_view_ownership.pw/.out. Actual3d5a52ca explicitly requires ARC source copies to remain valid across viewed operations and introduces the receiver adapter temporary/cleanup. Named hello and temporary fresh are immortal String literals, so missing source-owner acquisition can preserve all four outputs without freed backing. Managed concatenated return values alone do not detect acquisition of that source owner. Preserve lexical view selection, repeated named/original reads and temporary result; reconcile lifetime detection with releasable source storage and selected lifecycle/instrumentation evidence, verifying candidate allocation. Existing static_view_value_arc is a useful managed-shaped aggregate-view contrast, not automatic evidence for this direct String receiver adapter. No current compiler defect reproduced, broad view/method/operator matrix required, test/compiler/runner repair or real execution performed.

## String Field Copied From Replaced Pointee

Batch0114 adds exactly run/ref_arrow_field_bind_arc.pw/.out. Actual292d2d56 explicitly targets independent ownership of both Array and String field buffers after replacing the sole pointee owner. Array storage remains a useful managed lifetime detector; nm and replacement names are immortal literals, so String-specific acquisition omission can preserve3/pointee/other and leave no freed String backing. Preserve Array/replacement/value checks and reconcile the String subcase with releasable source storage and selected lifecycle/instrumentation or precise structural evidence, confirming allocation. Current reference-place materialization supplies Copy through final valueArc/StringLike; cow_string_elem and static_view_value_arc are managed-shaped contrasts on other paths and may be reused where evidence matches. No current compiler fault reproduced, all-Ref/field/type/helper matrix required, source repair or real execution performed.

## User Collection Element Ownership

Batch0121 adds exactly run/user_collection.pw/.out. Actual4d029d42 and6b1a7c5e explicitly target String acquisition, retirement, peek/pop ownership and CoW through user-authored Stack methods over Buffer. All stored elements are immortal literals; display concatenations never enter the collection. Missing/excessive element acquisition or release can retain all six outputs without freed String backing, even with application instrumentation. Preserve scalar/count/order/CoW observations and reconcile this exact wrapper path with releasable elements plus discriminating lifecycle/instrumentation or matching precise structural evidence, verifying selected candidate allocation. Existing buffer_string uses managed item-N elements on the direct Buffer path and is a useful complement, not proof every Stack instantiation detects ownership loss. Existing public Buffer construction and generic publication qualifications remain separate. No current compiler memory defect reproduced, all-collection matrix required, production repair or real execution performed.
