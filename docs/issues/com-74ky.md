---
id: com-74ky
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T19:03:37Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow source value pools cache and indices inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-expression-and-recording-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-expression-and-recording-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Recipe/synthetic/cache/range/argument/typearg/operand/view/local index value storage; keep synchronized columns, sentinels and matching pool lifetime. Replace real full Comp grants at all actual named API callers with the closed domain reader/writer proposed per row. Keep coherent stores/topology together and retain all legitimate side effects, identity/lifetime/default/error/invariant behavior.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-semantic-type-recipe-value-store: ['pushSemanticTypeRecipe', 'semanticTypeRecipeTerm']
- codegen-expression-legacy-type-cache-slot-allocation: ['ensureExprTySlot', 'buildExprTyTable']
- codegen-selected-callee-cache-tag-and-write-adapters: ['recordResolvedMethodCallee', 'calleeCacheEntry']
- codegen-recorded-call-template-type-argument-range-admission: ['checkCallTemplateTypeArguments']
- codegen-source-call-template-argument-range-admission: ['checkCallTemplateArguments']
- codegen-synthetic-call-origin-table-publication-and-read: ['recordSyntheticCallSite', 'syntheticCallSiteIndex']
- codegen-call-template-location-and-lexical-chain-index-rebuild: ['rebuildCallTemplateIndex', 'ensureCallTemplateIndex']
- codegen-first-lexical-call-template-chain-reader: ['firstLexicalCallTemplate']
- codegen-call-template-argument-and-type-pool-publication: ['publishCallTemplateArguments', 'publishCallTemplateTypeArgs']
- codegen-call-template-type-and-argument-pool-copy-readers: ['callTemplateTypeArgs', 'callTemplateArguments']
- codegen-call-template-operand-and-view-pool-adapters: ['publishCallTemplateOperands', 'publishCallTemplateViews', 'callTemplateViews']
- codegen-index-call-argument-construction: ['indexCallArgs']

## Actions and Completion
Change the actual APIs and every actual source/fixture consumer to the named closed services. Remove competing broad grants and raw Comp/unwrap/callback escapes. Preserve all listed direct/delegated effects, source/session/owner identity, ordering/defaults and error/restore/lifetime behavior with task-start TDD/refactor controls and independent structural review; run appropriate repair validation. A new interface proposal alone is not repair completion.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other API components/domains, passive record field decomposition, language acceptance/algorithm/performance/ABI changes or whole compiler correctness/GREEN. No product repair/execution occurs within the originating audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

