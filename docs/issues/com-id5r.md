---
id: com-id5r
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:26:08Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow numeric source span and diagnostic location inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/lowering-and-structural-leaf-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-lowering-and-structural-leaf-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Exact numeric/byte classifiers, arrayElemRef, location/diagnostic navigation and receiver-free fnAnchor only. Keep source-file offsets/AST fallback/sentinels/line mapping, current integer spelling/ranges and immutable pools. arrayElemNameForRef grounding excluded.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-primitive-numeric-span-and-range-queries: Primitive/name/numeric span queries of Emit.pw family
- codegen-array-element-name-navigation: arrayElemRef only; arrayElemNameForRef remains unresolved component
- codegen-source-location-and-diagnostic-queries: lineOf/diagnosticAt/fnAnchor/exprOffset and exact family helpers

## Actions and Completion
Narrow the actual APIs and all actual source/fixture consumers, preserving required data/effects and removing competing broad signatures.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other APIs, changed source acceptance/algorithms/ABI, unsupported feature work, product repair/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

