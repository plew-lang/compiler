---
id: com-vh0x
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:53:36Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow canonical metadata/type-construction leaf inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-query-and-module-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-query-and-module-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of audit closure; implementation admission is assigned below; no product repair was performed by the audit.

## Guarantee and Scope
同session canonical type/child/label/view/nominal/binder/instance-key readersとexplicit value inputs。必要箇所だけtype/name/keyword interner・canonical publisher・body-derived type-result writer・diagnosticを許可し、sourceFacts publication/lexical cursor/Mono/Mid全writerを露出しない。 ParamId/nominal/projection/view/labelsのidentity、simultaneous replacement、default fields/sentinels/empty vectors、type pools/index/summaries、current type/name/keyword cache mutationを保存。recordLayout queryはalias/module/import provenanceとinternerも必要。

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-explicit-type-environment-substitution: ['groundTermInEnvironment']
- codegen-body-type-grounding-result-cache-publication: ['recordBodyTypeTermResult']
- codegen-type-and-record-child-reconstruction: ['rebuildTypeTerm', 'rebuildRecordTypeTerm']
- codegen-typeref-compatibility-child-and-label-navigation: ['typeTermChildCount', 'typeTermChildRef', 'typeTermChildLabel', 'typeTermIdentityChildLabel']
- codegen-canonical-term-child-and-projection-navigation: ['typeTermRefChildCount', 'typeTermRefProjectionReceiver', 'typeTermRefChildRef']
- codegen-canonical-child-identity-label-and-view-set-navigation: ['typeTermRefIdentityChildLabel', 'sameTypeTermViewIds']
- codegen-canonical-type-head-identity-comparison: ['typeTermRefSameHead']
- codegen-associated-projection-carrier-reconstruction: ['rebuildProjectionTerm']
- codegen-readable-record-type-key-production: ['recordTypeKeyFromRef']
- codegen-semantic-record-layout-matching-and-query: ['recordLayoutMatches', 'recordStructIndex']
- codegen-instantiated-type-depth-query-and-limit: ['tyRefDepth', 'checkInstDepth']
- codegen-simple-type-spelling-to-term-registration: ['simpleTypeRef']
- codegen-generation-derived-type-argument-filter: ['refArgNamesADeriveTarget']
- codegen-primitive-integer-type-ref-predicates: ['tcIsUnsignedInt', 'tcIsPrimInt']
- codegen-trait-argument-label-projections: ['positionalTraitArgs', 'traitAssocArgNames', 'traitAssocArgValues']
- codegen-compatibility-shape-and-result-predicates: ['sameCompatibilityViewSet', 'isConcreteType', 'isCompatibilityBuiltin', 'argWidensToAny', 'genericStructHeadId', 'typeCompatibilityResult']
- codegen-function-field-and-declared-return-typeinfo-projection: ['declaredRetInfo']
- codegen-receiver-match-to-callable-binder-argument-projection: ['receiverCallableArguments']
- codegen-selected-signature-binder-order-projection: ['signatureTypeArguments']
- codegen-type-argument-nonzero-completeness-query: ['fnArgsAllResolved']
- codegen-trait-requirement-declaration-owned-self-substitution: ['groundTraitRequirementType']
- codegen-generic-callable-and-receiver-parameter-queries: ['isGenericFreeFn', 'recvParamCount']
- codegen-type-spelling-and-closure-signature-construction: ['findOrAddTypeRef', 'closureFnTypeRef', 'tyRefOfInfo']
- codegen-argument-view-term-adapter: ['argViewRef']
- codegen-function-instance-membership: ['fnInstExists']
- codegen-associated-result-type-argument-fill: ['groundAssocFromResult']

## Actions and Completion
For confirmed scopes change exact actual signatures and all actual consumers, retain necessary mutable service effects, remove raw Comp/unwrap/callback escapes and verify with TDD/refactor controls plus independent review. For unresolved scopes deliver exact direct/delegated closure and supported verdict/finite followups. exact factのtyped source/fixture contextsを起点に、当該affected APIsの全actual consumers。高fanoutの代表例を固定callsite件数や完全一覧にしない。

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other domains, source/algorithm/ABI changes, optional passive payload shrinking, product repair/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Adopted Implementation Intake

[com-3z5o](com-3z5o.md) classifies the exact confirmed scope as required existing-feature phase3 conformance. Required admission owner(s): met-6e6k, met-ia09, met-acfl; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-source-queries.json) retains all main/mixed roles and normative grounds. Canonical type reconstruction, substitution, result-cache publication and compatibility/signature projections consume exact nominal/ParamId/view/label identity. Keep actual per-entry interner/type/name/proof/diagnostic writes and no raw source-fact/cursor/Mono/Mid authority.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
