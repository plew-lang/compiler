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

## Retained provisional audit scope

Track loop expression and value-bearing break connection to shared Syntax and internal IR separately from completion classification. The retained note reports these forms unconnected and uses while true for infinite-iteration probes; while true success does not prove loop syntax implementation. Preserve the specification distinction between source divergence and analytical non-continuation.

Evidence scope: retained from meta agents/provisional.md at c539d7b96615a5c59c0165b0a5e3df90ec1f8dac; grammar-specific items additionally come from agents/grammar.md at that revision. These notes mix historical reproduction and uninspected combinations. No current compiler run or exhaustive implementation audit was performed during migration. Recheck current source and minimal run/reject inputs before claiming a defect; close resolved investigations with evidence rather than weakening the specification.
