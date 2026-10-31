---
id: com-0lz8
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T17:48:45Z
type: task
priority: 2
assignee: Koji Murata
tags: [generics, frontend, verification]
---
# Narrow index category queries and call-syntax synthesis inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/frontend-services-and-values.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-frontend-services-and-values.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of audit closure; implementation admission is assigned below; no product repair was performed by the audit.

## Guarantee and Scope
isDictionaryType/isBufferType/typeHasMethodNamed/synthMethodCallのみ。interner/type metadataとkeyword memo、syntax Arg/Expr origin builderをそれぞれ保持。

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- frontend-index-recognition-and-call-synthesis: ['isDictionaryType', 'isBufferType', 'typeHasMethodNamed', 'synthMethodCall']

## Actions and Completion
対象APIと全typed consumersで必要入力/indirect grantを照合し、source/session/diagnostic/cache/restoreを失わない境界案を独立レビューする。

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other compiler APIs/algorithms, source acceptance changes, product repair/performance claims within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Adopted Implementation Intake

[com-vr57](com-vr57.md) classifies the exact confirmed scope as required existing-feature phase3 conformance. Required admission owner(s): met-ucze, met-acfl; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-frontend-services.json) retains all main/mixed roles and normative grounds. Existing method/category queries and synthesized call syntax feed source selection and retained origin; preserve keyword/type/interner and source Arg/Expr creation without unrelated compiler authority.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
