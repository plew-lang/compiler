---
id: com-i86w
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:35:24Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow Mid metadata and trace helper inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/mid-builder-consumer-services.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-mid-builder-consumer-services.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
nominal ownership/type structural relation、published discriminant scalar、template argument/operand pools、Array shape reader と trace sink を必要 query ごとに許可。pure key equality は値 API、trace は explicit scalar/context にする。 same-session type/decl/view labels/proof identity、fixed tag ABI/sentinels、trace text/enabled behavior、argument defaults/bounds、no-production helper inventory を維持。

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- mid-builder-adapter-place-and-mode-values: ['midAdapterPlace']
- mid-builder-nominal-value-ownership-queries: ['midTermIsUnique', 'midAggregateHasUniqueValue']
- mid-builder-direct-array-and-unsupported-shape-queries: ['midDirectArrayIndexExpr']
- mid-builder-unique-return-operand-adapter: ['midReturnOperand']
- mid-builder-pattern-tag-and-trace-inputs: ['traceMidUnsupportedMatch']
- mid-builder-pattern-continuation-and-discriminant-input: ['buildMidPatternContinuation', 'midDiscriminantType']
- mid-builder-call-value-cache-and-materialization-inputs: ['midCallValueForSite', 'materializeMidCallValue']
- mid-builder-template-argument-range-readers: ['midTemplateArguments']
- mid-builder-call-and-receiver-shape-queries: ['midExprIsCall', 'midExprIsShortCircuit']

## Actions and Completion
Change the actual consumer and provider interfaces to scoped closed services, preserving every named mutable effect and all actual source/fixture callers. Independently verify that no raw Comp reader/writer/unwrap/callback escape retains unrelated authority. Coordinate shared services once rather than duplicate implementations. readonly whole Comp の指摘は writer grant と区別。same-domain readonly Arena/Decls/MidBuildState owner 自体を誤りとしない。52 の materializer/46 continuation は対応 evaluator followup に分ける。 各 exact fact の列挙済み typed production/fixture consumers と、変更対象 API の全 actual source consumers。固定 callsite 件数や代表例だけを完全一覧とは扱わない。

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other compiler domains, source meaning/algorithm changes, all product edits/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

