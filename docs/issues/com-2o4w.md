---
id: com-2o4w
status: open
deps: [com-6u0t, com-fsuq]
links: []
created: 2026-10-21T15:16:01Z
type: task
priority: 2
assignee: Koji Murata
parent: com-042v
tags: [design, verification]
---
# Verify admitted scalar and pointer C boundary handoffs

## Existing-Feature Conformance Scope

Part of [com-604k](com-604k.md); scoped from [com-042v](com-042v.md). This is planned implementation/verification, not a completed fix. Reuses static audit [com-nsxb](com-nsxb.md), compiler `f89857b1` (runtime source unchanged from its `78bd9691` audit input), spec `1e0c4d0` and Syntax `00f740e1`. No compiler/probe/sanitizer/performance execution in this classification.

Current host scalar/pointer extern calls, exposed free functions and existing compiler callbacks with their present signatures. repr(c), aggregate ABI classifiers, arbitrary anonymous C callbacks, new targets, foreign-thread attachment and reusable embedding are excluded.

## Producer to Final Consumer and Removal

Selected source declaration/signature -> common CAbi scalar/integer/F32/inout classification -> imported/exposed LLVM entry -> native call/return/writeback and resource ownership. Preserve private ValueAbi separation, exact source type identity despite pointer representation, registry IDs and one-shot code/context lifetime. Unsupported aggregates must not silently enter the scalar lane.

## Completion and Verification

Two-way C controls on the current host for permitted widths/signs, Float, pointer, inout writeback, exposed names and labels, signature mismatches and unsupported boundary rejection; compare AOT/JIT entry failure/lifetime. Aggregate-layout absence remains in the parent and does not become an asserted supported feature.

Close with exact revision/scope, final-consumer evidence, removed competing paths and applicable correctness/performance gates. Preserve matching-input baseline evidence; the approved formal self-compilation target is below 7 seconds. This task does not close the mixed/new-feature parent automatically.

## Scoped Audit Intake com-71gu

The [scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-llvm-physical.json) assigns exact required input-authority repair subsets to this admission contract: com-6u0t. Their real prerequisites block this scope until the finite repairs and applicable independent controls pass. Preserve every source/physical/diagnostic role identified there; a primary assignment does not erase another required consumer. This is adopted assignment, not repaired product or area re-admission.

## Test Admission Intake com-5azh

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-067-098.json) installs required finite repair/investigation prerequisites at this actual admission: com-fsuq (row89). Retain each row qualifier and secondary domain. Validators must be repaired before relying on their affected result; source/expectation questions close with the corresponding area. Manual tools, unsupported shapes and optional scopes do not become unrelated standard-gate prerequisites. Assignment is not product repair or area completion.
