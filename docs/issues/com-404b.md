---
id: com-404b
status: in_progress
deps: []
links: [com-mmk9]
created: 2026-10-29T18:53:37Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Determine source value / compatibility query closure

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-query-and-module-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-query-and-module-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
tcCheckValue/operator/field expected checksとinferType/normalizedValueType/typeCompatibility/recursive records/nominal headsのnamed query closureを、source/current body owner・substitution/proof/literal-context単位で閉じる。 typeOf/exprType cache、keyword/name/type/record-layout/proof/sendability/existential services、tcLog/trace/error latch、Unresolved/Err/Compatible差、temporary cursorとfailure prefixes。複雑なservicesをopaque wholeComp wrapperで隠しただけでは解消しない。

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-value-type-check-against-explicit-expected-term: ['tcCheckValue']
- codegen-saved-operator-template-and-parameter-queries: ['sourceOperatorParameter']
- codegen-binary-operator-selected-argument-validation: ['tcCheckBinop']
- codegen-unary-legality-selected-parameter-and-diagnostic-adapters: ['tcUnaryReject', 'tcCheckUnary', 'tcCheckPrimitiveUnary']
- codegen-array-and-dictionary-index-expected-type-check: ['tcCheckArrayIndex']
- codegen-contextual-make-field-type-validation: ['tcCheckMakeFields', 'tcCheckFieldsUnder']
- codegen-expression-source-type-query: ['inferType']
- codegen-value-type-normalization-and-compatibility-predicate: ['typesCompatible', 'normalizedValueType']
- codegen-value-type-compatibility-dispatch: ['typeCompatibility']
- codegen-record-field-type-compatibility: ['recordTypeCompatibility']
- codegen-nominal-head-and-child-type-compatibility: ['namedTypeCompatibility: whole Comp / normalization and recursive query closure']
- codegen-function-field-and-declared-return-typeinfo-projection: ['closureFieldRetInfo']

## Actions and Completion
For confirmed scopes change exact actual signatures and all actual consumers, retain necessary mutable service effects, remove raw Comp/unwrap/callback escapes and verify with TDD/refactor controls plus independent review. For unresolved scopes deliver exact direct/delegated closure and supported verdict/finite followups. exact factのtyped source/fixture contextsを起点に、当該affected APIsの全actual consumers。高fanoutの代表例を固定callsite件数や完全一覧にしない。

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other domains, source/algorithm/ABI changes, optional passive payload shrinking, product repair/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

