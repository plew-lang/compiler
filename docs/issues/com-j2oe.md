---
id: com-j2oe
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:53:37Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow unused query adapter values

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-query-and-module-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-query-and-module-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
boundMethodRetInfo.tpStart/tpLen、firstVisibleFuncByName.useMod、labelMatchOnlyInvisible.useMod、resolveAssocForResolvedReceiver.useOffset、registerCallInst.nameStart/nameLen/argsを対象signatureと全actual source/fixture consumersから除く。 other query/Comp argumentsはこのfindingだけでは縮めない。nameStartのregistered provenance、selected descriptors/body identity、interner/cache/cursor/registry/evidence/collection effects、default routesをそのまま保存。

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-bound-method-result-signature-query: ['boundMethodRetInfo: tpStart, tpLen only']
- codegen-first-free-function-global-and-visible-name-queries: ['firstFuncByName', 'firstVisibleFuncByName']
- codegen-inaccessible-label-match-diagnostic-query: ['labelMatchOnlyInvisible']
- codegen-concrete-receiver-final-associated-query: ['resolveAssocForResolvedReceiver: useOffset only']
- codegen-selected-final-call-instance-demand: ['registerCallInst: nameStart, nameLen, args only']

## Actions and Completion
For confirmed scopes change exact actual signatures and all actual consumers, retain necessary mutable service effects, remove raw Comp/unwrap/callback escapes and verify with TDD/refactor controls plus independent review. For unresolved scopes deliver exact direct/delegated closure and supported verdict/finite followups. exact factのtyped source/fixture contextsを起点に、当該affected APIsの全actual consumers。高fanoutの代表例を固定callsite件数や完全一覧にしない。

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other domains, source/algorithm/ABI changes, optional passive payload shrinking, product repair/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

