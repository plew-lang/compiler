---
id: com-ge01
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:35:24Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow Mid saved-fact admission and transfer reader inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/mid-builder-consumer-services.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-mid-builder-consumer-services.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of audit closure; implementation admission is assigned below; no product repair was performed by the audit.

## Guarantee and Scope
session/source owner resolver、strong PreparedSemanticFacts、exact source call-head/aggregate/closure/transfer lookup、source-offset diagnostic、acquisition counter、type/view normalization interner を操作別 front にする。raw source builder/publication writer は渡さない。 missing/failed/foreign-owner/session、Function/Closure/Global identity、default None と explicit target、statement kind/owner/source offset、Pending recipe、provided/default/synthetic call origin、strong payload lifetime、normalization/cache mutation を維持。 operation-reader hint/lifecycle/fallback と exact location key/panic semantics も維持する。

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- mid-builder-sealed-expression-type-reader-inputs: ['midSourceSemanticTerm', 'midSourceSemanticType']
- mid-builder-recorded-loop-exit-inputs: ['buildMidLoopExit']
- mid-builder-source-state-construction-and-owner-admission: ['prepareMidSourceState', 'admitSource', 'midSourceStateAdmitted', 'midSourceStatementAdmitted']
- mid-builder-loop-target-stack-and-source-transfer-reader: ['midSourceTransfer']
- mid-builder-recorded-identifier-to-place-input: ['midPlaceForRecordedIdent']
- mid-builder-sealed-aggregate-closure-and-capture-readers: ['midSemanticAggregateForSourceBody', 'midSemanticClosureForSourceBody']

## Actions and Completion
Change the actual consumer and provider interfaces to scoped closed services, preserving every named mutable effect and all actual source/fixture callers. Independently verify that no raw Comp reader/writer/unwrap/callback escape retains unrelated authority. Coordinate shared services once rather than duplicate implementations. 既存 reader service 内部が同じ owner/session storage を使うことは正当。Comp を丸ごと public field に入れただけの wrapper は解消に数えない。 各 exact fact の列挙済み typed production/fixture consumers と、変更対象 API の全 actual source consumers。固定 callsite 件数や代表例だけを完全一覧とは扱わない。

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other compiler domains, source meaning/algorithm changes, all product edits/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Adopted Implementation Intake

[com-ptko](com-ptko.md) classifies the exact confirmed scope as required existing-feature phase3 conformance. Required admission owner(s): met-acfl, com-fuo8; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-mid-and-lowering.json) retains all main/mixed roles and normative grounds. Successful owner admission and sealed type/call/aggregate/closure/transfer readers are the publication-to-final-reader boundary. Preserve strong prepared facts, exact source/session/owner, missing/failed distinctions and measured acquisitions; no raw writer or AST reinference may escape.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
