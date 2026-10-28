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
