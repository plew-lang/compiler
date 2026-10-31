---
id: com-0huw
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:53:36Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow loaded module / declaration / visibility metadata inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-query-and-module-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-query-and-module-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of audit closure; implementation admission is assigned below; no product repair was performed by the audit.

## Guarantee and Scope
admitted Modules provenance/ranges/import/public/qualified origins、Arena/Declsのnominal/callable/signature readers、source bytes、spelling internerとsource diagnosticをbounded module-query frontへ束ねる。local DFS/output arraysはcaller-owned。 root/part/package/Lang/source identity、alias/reexport/qualified binding、公私/namespace/synthesized policy、no missing-result permanent cache、declaration dedup/order/sentinels、no type proof/body request、readonly grantとmutable internerの差を保存。

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-loaded-source-offset-module-membership: ['moduleOf']
- codegen-statement-principal-source-offset-and-entry-method-query: ['stmtPrincipalOffset', 'methodInEntryModule']
- codegen-lang-ambient-nominal-and-forwarded-name-query: ['isAmbientInLang']
- codegen-source-offset-loaded-membership-query: ['offsetIsLoaded']
- codegen-module-direct-and-barrel-edge-membership: ['hasImportEdge', 'importsBarrelForwarding']
- codegen-free-callable-public-surface-collection: ['appendFreeFunctionSurface']
- codegen-visible-free-function-candidate-surface: ['visibleFreeFunctions']
- codegen-first-free-function-global-and-visible-name-queries: ['firstFuncByName', 'firstVisibleFuncByName']
- codegen-inaccessible-label-match-diagnostic-query: ['labelMatchOnlyInvisible']
- codegen-first-method-declared-result-name-query: ['firstMethodRetType']
- codegen-view-source-set-insertion-and-required-trait-source: ['appendViewSource', 'appendRequiredTraitSource']
- codegen-view-set-callable-source-membership: ['viewSetHasTrait', 'callableMatchesAnyExtension', 'callableMatchesAnyTrait']
- codegen-extension-and-view-only-method-name-existence: ['extMethodNameExists', 'viewOnlyMethodExists']
- codegen-associated-receiver-nominal-declaration-compatibility: ['receiverDeclarationMatches', 'receiverDeclarationHasOwner']
- codegen-type-name-and-associated-function-presence: ['isTypeName', 'typeHasAssocFn']
- codegen-associated-value-source-line-recognition: ['funcDeclLineHasAssocVal', 'typeHasAssocVal']
- codegen-canonical-lang-result-enum-identity-query: ['resultEnumIndex']
- codegen-module-origin-surface-and-use-binding-query: ['moduleBindingFromOrigin', 'moduleBindingFromSurface', 'moduleBindingAt', 'sameModuleBinding']
- codegen-import-surface-declaration-identity-fallback-query: ['importedDeclIdentityFromSurface']
- codegen-export-import-and-defining-module-membership: ['isExportedName', 'isExportedFromModule', 'isImportedInto', 'defModuleVisible']
- codegen-import-public-surface-and-collision-admission: ['importOriginHasOnlyFunctions', 'checkImports']
- codegen-call-spelling-visibility-walk-and-intercept-name-query: ['checkUseVisibility', 'checkExpressionVisibility', 'isAmbientInterceptedName']
- codegen-type-name-visibility-alias-and-global-existence: ['typeDeclVisibleFrom', 'typeDeclExistsGlobally', 'realTypeNameInModule', 'checkTypeName']
- codegen-package-root-and-type-definition-module-queries: ['typeDeclModuleMissing', 'packageRootModuleOf', 'isPackageRootModule', 'typeDefinitionModule']
- codegen-nominal-declaration-identity-in-module-surface-and-use: ['missingDeclIdentity', 'typeDeclIdentityInModule', 'typeDeclIdentityFromSurface', 'typeDeclIdentityAt']
- codegen-declaration-identity-to-name-and-name-predicate: ['typeDeclName', 'declIdentityHasName']
- codegen-export-entry-routing-and-public-category-dispatch: ['surfaceCanExportDeclModule', 'exportEntrySurfaceModule']
- codegen-import-graph-cycle-state-and-path-diagnostics: ['dfsImportCycle', 'importModulePath', 'importCycleMessage', 'detectImportCycles']
- codegen-lexical-name-and-module-namespace-query: ['lexicalNameBound', 'namespaceExprModule']

## Actions and Completion
For confirmed scopes change exact actual signatures and all actual consumers, retain necessary mutable service effects, remove raw Comp/unwrap/callback escapes and verify with TDD/refactor controls plus independent review. For unresolved scopes deliver exact direct/delegated closure and supported verdict/finite followups. exact factのtyped source/fixture contextsを起点に、当該affected APIsの全actual consumers。高fanoutの代表例を固定callsite件数や完全一覧にしない。

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other domains, source/algorithm/ABI changes, optional passive payload shrinking, product repair/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Adopted Implementation Intake

[com-3z5o](com-3z5o.md) classifies the exact confirmed scope as required existing-feature phase3 conformance. Required admission owner(s): met-ucze, met-ia09, com-604k; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-source-queries.json) retains all main/mixed roles and normative grounds. Module/public/import/alias/namespace provenance and candidate/type visibility queries feed ordinary source binding and applicability; import-cycle and loaded-source subroles additionally belong to input admission. Retain exact module/part/package/Lang identities, local traversal output and actual interner/diagnostic services, without proof/body execution authority.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
