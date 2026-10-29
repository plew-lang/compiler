---
id: com-debo
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T17:44:50Z
type: task
priority: 2
assignee: Koji Murata
tags: [backend, verification]
---
# Narrow backend metadata and registered-slot query inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/build-binding-and-root-leaves.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-build-binding-and-root-leaves.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md); independent of com-jno0/phase 3. Audit has not performed repairs.

## Guarantee and Scope
Narrow only isAsyncFn, refIsAny, isUnsignedName, typeArgsEq and genFnSlotForBody. Flag/spelling/type-identity queries must not receive whole mutable Comp; registered-body lookup must not receive mutable LlvmCtx with module/builder/queues. Use explicit flag/type metadata or immutable spelling bytes, a limited structural type-equality reader, and registered body identity array respectively. Definition-only queries remain in scope; absence of current production callers is not grounds for inventing use or silently deleting public APIs.

## Actions and Completion
Enumerate actual source/fixture consumers. Preserve async/type flags, bounds/miss sentinels, unsigned-name matching and full typeRefEq semantics (head, children, labels, view/binder/nominal identity and failure/panic rules), not merely U64 equality. Preserve genFnK ordering/count. Narrow real signatures and remove competing broad alternatives; a wrapper retaining whole Comp/LlvmCtx is not sufficient. Apply TDD/refactor rules, independent structural/behavioral review and gates appropriate to the future change.

## Excluded
llvmTargetComponent (already explicit), physical lowering/ABI/LLVM algorithms, source semantics and performance work.

