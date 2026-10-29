---
id: com-r2sw
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T17:48:46Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Remove Arena receivers from pure IR hash and proof-tag helpers

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/ir-stores-and-values.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-ir-stores-and-values.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
All five pure helper APIs and their actual source/fixture consumers, including external Comp-method uses of finalAggregateHash, use explicit scalar/key inputs without Arena or Comp receiver. Preserve key/hash mapping, seven bound tag domains, decoder prevalidation, caller sentinels and overflow behavior. Count helpers separately from call expressions.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- ir-final-call-publication-and-payload-index: ['Arena.finalCalleeHash(bodyId, siteKey)', 'Arena.finalAggregateHash(bodyId, exprId)']
- ir-static-conformance-proof-serialization: ['Arena.declarationBoundKind(source)', 'Arena.declarationBoundIndex(source)', 'Arena.thawDeclarationBound(kind,index)']

## Actions and Completion
Narrow the actual APIs and all actual source/fixture consumers, preserving required data/effects and removing competing broad signatures.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Hash/tag format or semantics, whole Arena decomposition, proof selection and unrelated publication APIs.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

