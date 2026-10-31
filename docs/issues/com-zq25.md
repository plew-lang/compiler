---
id: com-zq25
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:00:03Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow grounded ownership shape and deinitializer metadata inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-control-ownership-generation.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-control-ownership-generation.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
arcClassOfRef/structOwnDeinitFi only; preserve type/record/nominal identity, spelling intern effects, source diagnostics and sentinel results. No runtime ARC or layout publication redesign.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-grounded-ownership-class-query: arcClassOfRef
- codegen-deinitializer-declaration-query: structOwnDeinitFi

## Actions and Completion
Narrow the actual APIs and all actual source/fixture consumers, preserving required data/effects and removing competing broad signatures.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Language/source acceptance changes, runtime algorithms, whole compiler redesign, product execution/repair/performance in this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Adopted Implementation Intake

[com-vr57](com-vr57.md) classifies the exact confirmed scope as required existing-feature phase4 conformance. Required admission owner(s): com-h61e; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-frontend-services.json) retains all main/mixed roles and normative grounds. Existing grounded ownership class and deinitializer metadata queries are downstream ownership/layout input services; preserve nominal/record identity, spelling effects, diagnostics and sentinels without runtime ARC redesign.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
