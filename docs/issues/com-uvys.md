---
id: com-uvys
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:26:08Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow pending derive and module declaration metadata inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/lowering-and-structural-leaf-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-lowering-and-structural-leaf-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Exact drainDerives/enumIndexByName/markImport/recordExport/recordExportFrom; remove unused markImport segment operands, preserve queue drain, module/source public identity and alias/interner/import/export effects. Do not redesign visibility or macro execution.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- parser-semantic-derive-pending-drain: drainDerives
- parser-unused-enum-name-index-query: enumIndexByName
- parser-module-import-and-public-name-registration: markImport/recordExport/recordExportFrom; markImport segStart/segLen unused

## Actions and Completion
Narrow the actual APIs and all actual source/fixture consumers, preserving required data/effects and removing competing broad signatures.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other APIs, changed source acceptance/algorithms/ABI, unsupported feature work, product repair/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Adopted Implementation Intake

[com-ptko](com-ptko.md) classifies the exact confirmed scope as required existing-feature phase4 conformance. Required admission owner(s): com-604k; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-mid-and-lowering.json) retains all main/mixed roles and normative grounds. Parser derive draining and existing module public/import registration are input identity and pending-work boundaries. Remove unused operands and unrelated compiler authority while preserving module/root identity, source lineage and queue/interner effects; no visibility policy change.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
