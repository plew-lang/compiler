---
id: com-uk6c
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T17:48:45Z
type: task
priority: 2
assignee: Koji Murata
tags: [generics, frontend, verification]
---
# Narrow positional pattern-matcher type and binder inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/frontend-services-and-values.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-frontend-services-and-values.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
typeRefListPatternMatches/traitInstanceArgsMatchと共通unifyPatterns必要closure。local binds以外を書けず、binder/view/occurs/type children全読取と既存defaultsを保持。

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- frontend-positional-pattern-list-matching-adapters: ['typeRefListPatternMatches', 'traitInstanceArgsMatch']

## Actions and Completion
対象APIと全typed consumersで必要入力/indirect grantを照合し、source/session/diagnostic/cache/restoreを失わない境界案を独立レビューする。修正時のTDD/構造検証は別task。

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other compiler APIs/algorithms, source acceptance changes, product repair/performance claims within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

