---
id: com-0vbn
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T19:03:36Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow source owner and occurrence navigation inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-expression-and-recording-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-expression-and-recording-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Current/recording owner, exact provided lexical owner and function/closure/global keys; written/synthetic/protocol origins; stored head/template/closure-result queries with exact session/owner/reader hint. Replace real full Comp grants at all actual named API callers with the closed domain reader/writer proposed per row. Keep coherent stores/topology together and retain all legitimate side effects, identity/lifetime/default/error/invariant behavior.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-current-lexical-source-owner-navigation: ['currentSourceOwner']
- codegen-lexical-function-or-closure-declared-result-term-query: ['declaredBodyReturnTerm']
- codegen-synthetic-selected-forwarder-type-argument-reader: ['syntheticSelectedTypeArguments']
- codegen-construction-expression-presence-and-unit-state-queries: ['hasSemanticExprTypeFact', 'recordedExpressionHasUnitResult']
- codegen-construction-expression-term-projection: ['semanticExprTerm']
- codegen-lexical-call-template-closure-state-query: ['callTemplatesClosedForBody']
- codegen-source-call-template-owner-key-normalization: ['callTemplateOwner']
- codegen-provided-copy-semantic-body-owner-reader: ['semanticBodyOwner']
- codegen-written-source-call-site-key-construction: ['sourceCallSiteKey']
- codegen-template-expression-protocol-key-and-origin-comparators: ['templateCallSiteKey', 'templateProtocolSiteKey', 'sameCallSiteKey', 'sameCallSiteOrigin']
- codegen-source-recording-owner-authority-adapter: ['sourceRecordingOwner']
- codegen-current-body-template-origin-fallback-reader: ['callTemplateForCurrentBody']
- codegen-exact-lexical-body-template-and-head-readers: ['callTemplateForSourceBody', 'callTemplateHeadForSourceBody']
- codegen-semantic-expression-typeinfo-compatibility-reader: ['semanticExprTypeInfo']
- codegen-synthetic-receiver-term-fallback-reader: ['syntheticCallReceiverTerm']
- codegen-selected-for-item-payload-and-recipe-reader: ['forItemPayload', 'sourceForItemTerm']
- codegen-recorded-call-selection-presence-reader: ['recordedCallIsSelected']

## Actions and Completion
Change the actual APIs and every actual source/fixture consumer to the named closed services. Remove competing broad grants and raw Comp/unwrap/callback escapes. Preserve all listed direct/delegated effects, source/session/owner identity, ordering/defaults and error/restore/lifetime behavior with task-start TDD/refactor controls and independent structural review; run appropriate repair validation. A new interface proposal alone is not repair completion.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other API components/domains, passive record field decomposition, language acceptance/algorithm/performance/ABI changes or whole compiler correctness/GREEN. No product repair/execution occurs within the originating audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

