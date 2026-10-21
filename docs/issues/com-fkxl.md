---
id: com-fkxl
status: open
deps: []
links: []
created: 2026-10-21T15:16:01Z
type: task
priority: 1
assignee: Koji Murata
parent: met-c58b
tags: [design, verification]
---
# Close initialization planning over existing managed execution

## Existing-Feature Conformance Scope

Part of [com-604k](com-604k.md); scoped from [met-c58b](met-c58b.md). This is planned implementation/verification, not a completed fix. Reuses static audit [com-nsxb](com-nsxb.md), compiler `f89857b1` (runtime source unchanged from its `78bd9691` audit input), spec `1e0c4d0` and Syntax `00f740e1`. No compiler/probe/sanitizer/performance execution in this classification.

Existing global/associated initializer forms, selected calls/defaults/conversions, invoked closures and dynamic witnesses already supported, current async continuations, known existing exposed callback dependencies, and implicit copy/drop/deinit. Future workers, new public callbacks and arbitrary foreign-thread/runtime startup are excluded.

## Producer to Final Consumer and Removal

Saved selected operations and complete execution-effect summaries -> initializer dependency/provenance graph -> SCC/cycle rejection and prerequisite-ready one-time startup -> current AOT/JIT. Replace direct-AST-only dependency guesses; closure construction is distinct from invocation. Semantic/effect summaries must be closed before startup, while machine bodies can stay lazy. Unknown current dynamic targets cannot mean empty effects.

## Completion and Verification

Direct/indirect/single-root cycles, declaration order reversal, dependencies through blocks/defaults/invoked closures/drop and supported async, clean independent initializers and AOT/JIT agreement. Refine existing effect producers with their owners; do not add hidden global waits or force a new worker service to finish this current-subset task.

Close with exact revision/scope, final-consumer evidence, removed competing paths and applicable correctness/performance gates. Preserve matching-input baseline evidence; the approved formal self-compilation target is below 7 seconds. This task does not close the mixed/new-feature parent automatically.
