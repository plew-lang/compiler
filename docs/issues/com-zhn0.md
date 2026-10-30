---
id: com-zhn0
status: closed
deps: []
links: [com-mmk9]
created: 2026-10-29T18:53:37Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Determine public API coordinator global type query closure

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-query-and-module-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-query-and-module-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
checkGlobalSurfaceInModule→inferLetTypeとcheckExportEntrySurface/checkPublicApiClosureの経路に限定し、whole semantic coordinatorの必要入力とclosed signature leafの境界を明確にする。 explicit apiRoot/namespace/reexport/source offsets/PublicSurfaceIndex lifetime、pending global type inference、inCollection array/layout registration、whole cur frame/cache/proof/interner effects、runtime global initializer非実行を保存。正当なcoordinator候補をleafのdirect readだけでC/Jにしない。

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-public-nominal-and-global-value-signature-adapters: ['checkGlobalSurfaceInModule']
- codegen-export-entry-routing-and-public-category-dispatch: ['checkExportEntrySurface']
- codegen-whole-public-api-closure-request: ['checkPublicApiClosure']

## Actions and Completion
For confirmed scopes change exact actual signatures and all actual consumers, retain necessary mutable service effects, remove raw Comp/unwrap/callback escapes and verify with TDD/refactor controls plus independent review. For unresolved scopes deliver exact direct/delegated closure and supported verdict/finite followups. exact factのtyped source/fixture contextsを起点に、当該affected APIsの全actual consumers。高fanoutの代表例を固定callsite件数や完全一覧にしない。

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other domains, source/algorithm/ABI changes, optional passive payload shrinking, product repair/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


 ## Input Investigation Outcome

 The original required input/delegate-authority questions are answered, not merely
 assigned elsewhere. [Exact answer](../../../evidence/compiler-api-audit/resolutions/source-admission-descriptor-inputs.json)
 and [independent review](../../../evidence/compiler-api-audit/review-resolution-source-admission-descriptor-inputs.json)
 record the complete named scope, necessary inputs/effects, actual caller contexts,
 source identity and supported C conclusion. Required input questions remaining
 in this scope: none. Product repairs remain unimplemented and unverified.

 Repair ownership: [com-aaia](com-aaia.md), [com-8yzi](com-8yzi.md), [com-s696](com-s696.md), [com-3y0f](com-3y0f.md), [com-ecm1](com-ecm1.md), [com-zpo1](com-zpo1.md), [com-v8mk](com-v8mk.md), [com-cwq1](com-cwq1.md), [com-sezm](com-sezm.md). These repair issues are not evidence of the conclusion; the linked
 source closure and independent review are. This closes only this finite
 investigation, not com-mmk9 or any product implementation milestone.
