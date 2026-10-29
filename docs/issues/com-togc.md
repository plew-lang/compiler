---
id: com-togc
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:53:37Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Determine legacy expression/source-result query closure

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-query-and-module-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-query-and-module-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
exprTypeWithChainHole/constructExprTypeWithChainHoleの全指定segmentsとvalue-block/inferenceArgument/inferLetのsaved-versus-construction routesに限り、source/body/env/chainHoleとdomain effectsを有限表へまとめる。 same physical APIを複数independent functionsと誤認しない。pending global TYPE forcing: global Local metadata導入、whole cur/resolvingGlobalTypes両結果restore、success local replacement、outer type/proof/cache/interner/collection effectsのErr残留。generic pathsのsuccess-only restoreとruntime initializer実行との差、normal/diagnostic/no-normal categoriesを保存。

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-inference-argument-recorded-fact-and-fallback-query: ['inferenceArgumentType']
- codegen-context-free-and-diagnostic-subject-type-query: ['exprType', 'sourceSubjectTypeInfo']
- codegen-value-block-normal-result-typeinfo-query: ['valueBlockTypeInfo']
- codegen-recorded-expression-environment-typeinfo-projection: ['exprTypeWithChainHole']
- codegen-expression-construction-literal-and-local-query-segment: ['constructExprTypeWithChainHole']
- codegen-expression-construction-operator-query-segment: ['constructExprTypeWithChainHole: specified source segment only']
- codegen-expression-construction-free-call-query-segment: ['constructExprTypeWithChainHole: specified source segment only']
- codegen-expression-construction-field-query-segment: ['constructExprTypeWithChainHole: specified source segment only']
- codegen-expression-construction-make-and-array-query-segment: ['constructExprTypeWithChainHole: specified source segment only']
- codegen-expression-construction-index-query-segment: ['constructExprTypeWithChainHole: specified source segment only']
- codegen-expression-construction-view-query-segment: ['constructExprTypeWithChainHole: specified source segment only']
- codegen-expression-construction-extension-method-query-segment: ['constructExprTypeWithChainHole: specified source segment only']
- codegen-expression-construction-method-query-segment: ['constructExprTypeWithChainHole: specified source segment only']
- codegen-expression-construction-cast-and-value-control-query-segment: ['constructExprTypeWithChainHole: specified source segment only']
- codegen-expression-construction-chain-pointer-closure-and-await-query-segment: ['constructExprTypeWithChainHole: specified source segment only']
- codegen-let-inference-selected-result-and-array-collection-adapter: ['inferLetType']

## Actions and Completion
For confirmed scopes change exact actual signatures and all actual consumers, retain necessary mutable service effects, remove raw Comp/unwrap/callback escapes and verify with TDD/refactor controls plus independent review. For unresolved scopes deliver exact direct/delegated closure and supported verdict/finite followups. exact factのtyped source/fixture contextsを起点に、当該affected APIsの全actual consumers。高fanoutの代表例を固定callsite件数や完全一覧にしない。

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other domains, source/algorithm/ABI changes, optional passive payload shrinking, product repair/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

