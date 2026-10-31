---
id: com-euq7
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:53:36Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow owner diagnostic / formatter inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-query-and-module-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-query-and-module-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of audit closure; implementation admission is assigned below; no product repair was performed by the audit.

## Guarantee and Scope
owned CompileDiagnostic値、explicit operator/source spans、immutable AST/type/byte formatting readers、currentSourceOwner resolver/sessionとfirst-failure latch store、tcLog/trace policyへ限定する。 source/module/path/line/offset/severity/message、ownerごとfirst failure、tcLog false immediate Err / true continuationと後段拒否、printingを行うcallerとpure formatterの区別を保存。

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-type-diagnostic-continuation-and-owner-failure-latch: ['continueTypeDiagnostic', 'checkSourceDiagnosticFailures', 'checkDiagnosticContinuationFailures']
- codegen-unresolved-operator-location-diagnostic: ['unresolvedSourceOperatorDiagnostic']
- codegen-typecheck-diagnostic-spelling-and-expression-shape: ['tcFieldPos', 'tcExprKind', 'tcRefName']

## Actions and Completion
For confirmed scopes change exact actual signatures and all actual consumers, retain necessary mutable service effects, remove raw Comp/unwrap/callback escapes and verify with TDD/refactor controls plus independent review. For unresolved scopes deliver exact direct/delegated closure and supported verdict/finite followups. exact factのtyped source/fixture contextsを起点に、当該affected APIsの全actual consumers。高fanoutの代表例を固定callsite件数や完全一覧にしない。

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other domains, source/algorithm/ABI changes, optional passive payload shrinking, product repair/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Adopted Implementation Intake

[com-3z5o](com-3z5o.md) classifies the exact confirmed scope as required existing-feature phase3 conformance. Required admission owner(s): met-acfl, met-k7ks; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-source-queries.json) retains all main/mixed roles and normative grounds. Type diagnostic continuation has an owner-specific first-failure latch that prevents successful source publication; formatting and message/span projections are diagnostic subsets. Preserve tcLog false immediate Err versus continued-check eventual rejection, without diagnostic relookup or arbitrary writer authority.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
