---
id: com-hd9n
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:53:37Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow source operation read / construction / publication fronts

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-query-and-module-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-query-and-module-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of audit closure; implementation admission is assigned below; no product repair was performed by the audit.

## Guarantee and Scope
session/owner/location/key index、cached strong reader hint、SourceFactDirectory lifecycle whole ownerとそのactive/inactive builders/maps/state、owner-local operation/constraint/recipe writer、lexical/global index publisherを必要operationのfrontで扱う。 Building/Prepared/failed/succeeded distinctions、private Admitted exact plan、phase/key/range guards・panic/false/absence、activation-before-local-reject、source parent/root/global identity、Ref lifetime、pool/default mayHaveStorageArguments と Optional resultExpression を保存。rawComp/unwrap/Comp callback付きwrapperは不可。

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-saved-operator-template-and-parameter-queries: ['recordedSourceOperator']
- codegen-source-operation-constraint-state-readers: ['selectedCallConstraintPlan', 'preparedCallConstraints', 'sourceOperationConstraints']
- codegen-source-operation-constraint-construction-writer: ['recordBuildingCallConstraints', 'storeBuildingOperationConstraints']
- codegen-call-constraint-admission-and-publication: ['publishPreparedCallConstraints']
- codegen-session-call-navigation-and-inspection: ['callTemplateIndex', 'callTemplateCount', 'callTemplateAt', 'callTemplateHeadAt', 'callTemplateSnapshot', 'callTemplateOperandCount', 'callTemplateOperandAt', 'nextLexicalCallTemplate', 'globalCallTemplates', 'lexicalBodyPreparationCount', 'globalInitializerPreparationCount']
- codegen-call-template-construction-replacement: ['replaceBuildingCallTemplate', 'replaceSourceCallTemplate']
- codegen-call-template-owner-index-and-append-adapters: ['registerCallTemplateLexicalRoot', 'appendSourceCallTemplate', 'recordGlobalCallTemplateOwner', 'indexLexicalCallTemplate']

## Actions and Completion
For confirmed scopes change exact actual signatures and all actual consumers, retain necessary mutable service effects, remove raw Comp/unwrap/callback escapes and verify with TDD/refactor controls plus independent review. For unresolved scopes deliver exact direct/delegated closure and supported verdict/finite followups. exact factのtyped source/fixture contextsを起点に、当該affected APIsの全actual consumers。高fanoutの代表例を固定callsite件数や完全一覧にしない。

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other domains, source/algorithm/ABI changes, optional passive payload shrinking, product repair/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Adopted Implementation Intake

[com-3z5o](com-3z5o.md) classifies the exact confirmed scope as required existing-feature phase3 conformance. Required admission owner(s): met-acfl, met-ia09, met-ucze; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-source-queries.json) retains all main/mixed roles and normative grounds. Call constraints, templates and lexical/global indexes are owner-affine construction/publication and sealed reader boundaries. Retain Building/Prepared/failed/succeeded, exact phase/range/lifetime and active/inactive stores, without raw compiler/unwrap/callback escape.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
