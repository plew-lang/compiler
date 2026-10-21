---
id: com-f8bw
status: open
deps: [com-legt]
links: []
created: 2026-10-21T15:16:01Z
type: task
priority: 2
assignee: Koji Murata
parent: com-qzpm
tags: [design, verification]
---
# Correct existing sendable type checks without enabling workers

## Existing-Feature Conformance Scope

Part of [com-604k](com-604k.md); scoped from [com-qzpm](com-qzpm.md). This is planned implementation/verification, not a completed fix. Reuses static audit [com-nsxb](com-nsxb.md), compiler `f89857b1` (runtime source unchanged from its `78bd9691` audit input), spec `1e0c4d0` and Syntax `00f740e1`. No compiler/probe/sanitizer/performance execution in this classification.

Already admitted sendable type annotations/binders and ordinary structural checks, especially Ref/WeakRef nonsendability and propagation through existing containers/nominals. Spawn, sendable closure literals still unsupported by Syntax, worker effect closure, atomic RC and new transport APIs are excluded.

## Producer to Final Consumer and Removal

Infer/Type and Infer/Check consume Infer/Sendability.typeRefIsSendable; current Ref/WeakRef recursively inherit their payload result, contrary to their nonsendable contract. Use exact standard identities from the reference-identity work. Trace current query inputs, recursive failure and diagnostics; a depth exhaustion must not be presented as a proved capability. The unique-capability SCC/Boolean solver is a separate absent family.

## Completion and Verification

Supported generic/annotation checks with scalars, arrays/structs/enums containing Ref or WeakRef, unrelated same-named types, mutable-reference controls and nested/recursive query termination. Preserve explicit unsupported worker rejection. Close current predicate/result evidence without claiming safe cross-thread execution exists.

Close with exact revision/scope, final-consumer evidence, removed competing paths and applicable correctness/performance gates. Preserve matching-input baseline evidence; the approved formal self-compilation target is below 7 seconds. This task does not close the mixed/new-feature parent automatically.
