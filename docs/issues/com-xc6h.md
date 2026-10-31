---
id: com-xc6h
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:35:24Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Close required mutable services for checked Mid value evaluation

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/mid-builder-consumer-services.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-mid-builder-consumer-services.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of audit closure; implementation admission is assigned below; no product repair was performed by the audit.

## Guarantee and Scope
common recursive evaluator を same-session body owner の制御された front にし、literal decode cache、type-view registration/interner、canonical closure provider、saved descriptor/recipe reads と diagnostic/trace を個別許可する。 occurrence-local call/aggregate cache、Unit versus divergence、actual call reached versus input termination、child order/snapshots、parent cache restore、await Promise owner/suspend、Try selected error recipe/return home、view/cast boundaries と Copy/Move を維持。

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- mid-builder-primitive-source-operand-inputs: ['midOperandForSourceExpr']
- mid-builder-call-value-cache-and-materialization-inputs: ['midCallValueForSite', 'materializeMidCallValue']
- mid-builder-aggregate-value-occurrence-cache-inputs: ['materializeMidAggregateValue']
- mid-builder-ordered-aggregate-child-evaluation-inputs: ['buildMidAggregateEvaluation']
- mid-builder-short-circuit-evaluation-inputs: ['materializeMidShortCircuit']
- mid-builder-await-owned-input-and-suspend-inputs: ['materializeMidAwait']
- mid-builder-try-decomposition-and-error-edge-inputs: ['materializeMidTry']
- mid-builder-checked-expression-value-router-inputs: ['midValueOperandForSourceExpr']
- mid-builder-evaluation-snapshot-and-ambient-place-inputs: ['midEvaluatedValue']

## Actions and Completion
Change the actual consumer and provider interfaces to scoped closed services, preserving every named mutable effect and all actual source/fixture callers. Independently verify that no raw Comp reader/writer/unwrap/callback escape retains unrelated authority. Coordinate shared services once rather than duplicate implementations. pure readonly 化や sourceFacts-only 化をしない。source decision を再実行せず、selected recipes/proofs/body origins をそのまま後段へ渡す。 各 exact fact の列挙済み typed production/fixture consumers と、変更対象 API の全 actual source consumers。固定 callsite 件数や代表例だけを完全一覧とは扱わない。

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other compiler domains, source meaning/algorithm changes, all product edits/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Adopted Implementation Intake

[com-ptko](com-ptko.md) classifies the exact confirmed scope as required existing-feature phase3 conformance. Required admission owner(s): met-6e6k, com-fuo8; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-mid-and-lowering.json) retains all main/mixed roles and normative grounds. The common checked-expression evaluator consumes saved types/recipes/completion through ordered aggregate, call, short-circuit, await and Try lowering. Preserve exact value snapshots, scope/cache restore and source owner while bounding literal/interner/canonical provider services.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
