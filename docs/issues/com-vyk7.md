---
id: com-vyk7
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T17:53:14Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow saved-operation scanning inputs for declaration effects

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/mid-domain-services-and-values.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-mid-domain-services-and-values.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
State.scanBody and source-bound saved-call access in checkDeclarationBodyAccess; State.body/close/public orchestration excluded

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- mid-declaration-effect-body-and-selected-operation-collection: ['DeclarationAccessState.scanBody']
- mid-declaration-local-call-access-entry-and-storage-filter: ['checkDeclarationBodyAccess']

## Actions and Completion
same-session owner-bound saved operation reader/failure state and canonical/closedness views; preserve cached reader owner key/fallback/missing-row panic; no source reconstruction or ambient cursor source selection

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other compiler APIs/algorithms, source semantics, product repair/execution and speculative performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Component Input Investigation Answer

[Exact answer](../../../evidence/compiler-api-audit/resolutions/declaration-access-inputs.json)
and [independent review](../../../evidence/compiler-api-audit/review-resolution-declaration-access-inputs.json)
answer the original checkDeclarationBodyAccess input-authority question, including
saved operation identity, lifecycle fallback, required reads and error behavior.
The main and other component classifications remain unchanged. Product repair in
this issue remains open and unimplemented; this answer neither closes this issue
nor completes com-mmk9. Preserve the required contract and failure distinctions
when replacing the broad API boundary.
