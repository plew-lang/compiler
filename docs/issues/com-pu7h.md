---
id: com-pu7h
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:00:03Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Determine legacy ownership and sendability grounding service inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-control-ownership-generation.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-control-ownership-generation.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
The four unresolved families only: close groundTypeRef/resolveTy and actual nominal/field/projection/environment/cache/layout/interner/diagnostic dependencies from their fixed callers; characterize success and error restoration/retained visited state before choosing a service. This finite input investigation is not a new solver or correctness proof.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-field-ownership-type-grounding-inputs: arcFieldTy
- codegen-recursive-release-requirement-query: arcNeedsRelease/arcRefNeedsRelease
- codegen-structural-sendability-query-and-budget: typeRefIsSendable/typeRefIsNonsendable/typeRefIsSendableDepth
- codegen-sendability-field-instantiation-frame: fieldsAreSendable/groundFieldSendabilityType

## Actions and Completion
Narrow the actual APIs and all actual source/fixture consumers, preserving required data/effects and removing competing broad signatures.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Language/source acceptance changes, runtime algorithms, whole compiler redesign, product execution/repair/performance in this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

