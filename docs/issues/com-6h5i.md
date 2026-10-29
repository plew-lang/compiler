---
id: com-6h5i
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:13:53Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow program preparation diagnostic converter inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-owner-and-preparation-services.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-owner-and-preparation-services.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Only programPreparationDiagnostic and its immediate diagnostic projections; use the already assigned declaration/Mid diagnostic narrowing owners where their actual signatures are prerequisites. Preserve body/source/error/trace provenance; no source preparation/exit/printing final error.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- prepared-program-error-diagnostic-adapter: programPreparationDiagnostic

## Actions and Completion
Narrow the actual APIs and all actual source/fixture consumers, preserving required data/effects and removing competing broad signatures.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Language/algorithm/ABI/runtime changes, full compiler redesign, product edits/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

