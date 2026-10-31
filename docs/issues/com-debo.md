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


## Adopted Implementation Intake

[com-k35g](com-k35g.md) classifies this exact confirmed scope as required existing-feature phase4 conformance. Required admission owner(s): com-h61e; actual tk prerequisites retain the open repair.

[Scoped intake outcome](../../../evidence/existing-feature-conformance/audit-intake/api-session-and-inputs.json) preserves every main/mixed role and the normative reason. Existing finalized flag/type queries and registered-body slot lookup must not receive unrelated mutable/native capabilities. Definition-only APIs retain finite signature/consumer scope, not a new feature.

The original audit-time independence does not waive this implementation admission. Keep the original finite guarantee, caller/delegate/control and excluded optional scopes. This is assignment only, not product repair/GREEN.
