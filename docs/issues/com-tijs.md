---
id: com-tijs
status: open
deps: []
links: []
created: 2026-10-13T00:55:05Z
type: task
priority: 1
assignee: Koji Murata
tags: [frontend, mid, diagnostics, verification]
---
# Complete explicit-divergence and source-completion migration

Adopted divergence/value-use/following-code semantics are in the specification, but the retained type-checking implementation migration and existing-test synchronization are incomplete. Centralize classification and sequential/branch composition instead of recognizing terminal syntax independently in each checker/lowerer. Source completion and diagnostic cause differ from analytical CFG non-continuation.

The paused remediation candidate and validation evidence remain in the meta worklog, not in this issue. This issue does not authorize restarting implementation before its unresolved checked-body storage/reader design is decided. The former divergence memo identified standalone_block_return.pw and old unreachable-warning fixtures for intent/spec-impact reassessment; do not silently keep the old meaning or change unrelated test purposes.

## Design

[Decision and rejected alternatives](../design/decisions/divergence.md); [shared value-region checking](../design/body-checking.md#4-blocks-branches-patterns-and-completion); [diagnostic responsibility](../design/diagnostics.md). The spec is the semantic authority. Preserve diverging function types through normal type/evidence readers, without Never/Unit fallback or ordinary-function promotion.

## Acceptance Criteria

Close producer, saved completion/targets/callable contracts, instance readers, Mid flow/cleanup, LLVM and JIT consumers; remove old last-statement and name/AST-based competing decisions. Cover direct value rejection, typed normal wrappers, branch divergence, empty match, nested exits, both function-type conversion rejections, function values through generic/field/associated types, capture/access, sendable preservation and async/FFI restrictions. Explicit-transfer following code errors; analytically unreachable loop successors warn and remain statically checked, including give/type errors, without reachable ownership joins. Reassess affected old tests against original intent and adopted spec. Complete applicable gates and synchronize design; do not claim completion from added checks alone.

