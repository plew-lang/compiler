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

