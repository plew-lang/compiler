---
id: com-j3pp
status: open
deps: []
links: []
created: 2026-10-21T15:16:01Z
type: task
priority: 2
assignee: Koji Murata
parent: com-b1ro
tags: [design, verification]
---
# Audit ownership of currently admitted closure environments

## Existing-Feature Conformance Scope

Part of [com-604k](com-604k.md); scoped from [com-b1ro](com-b1ro.md). This is planned implementation/verification, not a completed fix. Reuses static audit [com-nsxb](com-nsxb.md), compiler `f89857b1` (runtime source unchanged from its `78bd9691` audit input), spec `1e0c4d0` and Syntax `00f740e1`. No compiler/probe/sanitizer/performance execution in this classification.

Copyable capture shapes already admitted by checkedCaptureCell, shared mutable cells, ordinary nested-body preparation where currently accepted, and their descriptors/copy/drop/borrow effects. Explicitly rejected generic-struct/function-typed captures, unique move capture and a new one-shot closure model are excluded, not prohibited by new language rules.

## Producer to Final Consumer and Removal

Saved lexical/capture facts -> existing environment allocation and descriptors -> common call/access handling -> environment/cell retain/drop and final destruction on AOT/JIT. Source closure-body publication is owned by the checked-facts work; this unit checks runtime owners and final uses, not another body-checking authority.

## Completion and Verification

Admitted scalar/String/Array/nominal captures, shared cells and alias mutation, copied/escaped handles, final release order and failure cleanup. Reject controls keep known unsupported shapes loud. Do not assume all enum/struct shapes are missing or promise their exhaustive implementation from one passing fixture.

Close with exact revision/scope, final-consumer evidence, removed competing paths and applicable correctness/performance gates. Preserve matching-input baseline evidence; the approved formal self-compilation target is below 7 seconds. This task does not close the mixed/new-feature parent automatically.
