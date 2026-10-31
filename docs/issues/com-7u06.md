---
id: com-7u06
status: open
deps: []
links: []
created: 2026-10-21T15:16:01Z
type: task
priority: 2
assignee: Koji Murata
parent: com-tn1m
tags: [design, verification]
---
# Close common Mid ownership and lifetime for admitted scalar async

## Existing-Feature Conformance Scope

Part of [com-604k](com-604k.md); scoped from [com-tn1m](com-tn1m.md). This is planned implementation/verification, not a completed fix. Reuses static audit [com-nsxb](com-nsxb.md), compiler `f89857b1` (runtime source unchanged from its `78bd9691` audit input), spec `1e0c4d0` and Syntax `00f740e1`. No compiler/probe/sanitizer/performance execution in this classification.

Currently admitted async functions and scalar Promise results, ordinary and move inputs, frame/suspension/resume/completion, ready-await immediate continuation, scheduled timer/waiter ownership and single completion. Explicit borrow/inout restrictions remain. Method/generic async, composite or unique results, worker/I/O polling extensions and cancellation APIs are excluded.

## Producer to Final Consumer and Removal

Saved source signature -> common Mid activation-input acquisition/transfer plan -> access/drop and frame liveness -> shared AOT/JIT runtime -> LLVM frame slots and terminal release. Move semantic ownership acquisition out of backend-only decisions, preserving +0 ordinary caller ABI and exactly one acquisition. Backend retains physical frame placement only; publication must precede any synchronous completion.

## Completion and Verification

Ready and pending awaits, completion during entry, dropping a user handle while pending, timer/waiter lifetime, copy/move input cleanup and rejected explicit borrows. Establish the exact existing timer contract; do not claim wall-clock/OS readiness from the virtual-clock lane. Trace actual producers/consumers before labeling any missing guard a runtime bug.

Close with exact revision/scope, final-consumer evidence, removed competing paths and applicable correctness/performance gates. Preserve matching-input baseline evidence; the approved formal self-compilation target is below 7 seconds. This task does not close the mixed/new-feature parent automatically.

## Scoped Test Audit Intake com-5azh

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-067-098.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 84.

Row84: Preserve ready-await inline and timer virtual-clock limits; no unconditional yield. Composite/unique results, method/generic async/cancellation/worker/I/O family excluded; explicit borrow/inout refusal and logical/public signatures remain. Existing scalar async activation input acquire/transfer, common Mid access/drop/frame liveness and final AOT/JIT release require current owner com-7u06.19 named runtime contexts are not its completion. Required admission: com-an0b, com-604k.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
