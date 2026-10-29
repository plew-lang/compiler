---
id: com-m4kt
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T17:53:14Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow published Mid type and contract-readiness services

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/mid-domain-services-and-values.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-mid-domain-services-and-values.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Types.pw three families + Verify.pw existing ownership/conversion readiness only

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- mid-published-type-comparison-and-view-normalization: ['midViewTypesMatch', 'midRetagTypesMatch', 'midTypesEqual']
- mid-place-and-operand-published-type-validation: ['midPlaceTypeIsValid', 'midOperandTypesAreValid']
- mid-operation-conversion-and-call-type-validation: ['midConversionTypesMatch', 'midRvalueTypesMatch', 'canonicalMidStatementTypesMatch', 'canonicalMidTerminatorTypesMatch']
- mid-verifier-frozen-copy-and-conversion-contract-readiness: ['canonicalMidCopyContractError', 'canonicalMidOwnershipContractIsReady', 'canonicalMidConversionContractsAreReady']

## Actions and Completion
isolate type identity/view normalization+name interner/final layout memo/frozen call-proof readers/trace; raw Comp not retained by new views; preserve no-reselection and missing-contract failure behavior; compare final target cache/type identity before/after

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other compiler APIs/algorithms, source semantics, product repair/execution and speculative performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

