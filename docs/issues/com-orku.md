---
id: com-orku
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T17:53:14Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Determine canonical instance application semantic service inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/mid-domain-services-and-values.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-mid-domain-services-and-values.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
only unresolved components in Instantiate.pw rows, not Mid builders or whole compiler type checker

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- mid-instantiation-rvalue-statement-dispatch-and-failure-trace: ['instantiateCanonicalStatement.locals', 'traceMidInstantiationRvalue']
- mid-instantiation-noncall-control-and-remapped-protocol-branches: ['instantiateCanonicalNonCallTerminator', 'instantiateCanonicalNonCallTerminatorRemapped']
- mid-instantiation-selected-call-resolution-target-and-receiver: ['instantiateCanonicalCallTarget']
- mid-instantiation-grounded-local-row-publication: ['appendCanonicalInstantiatedLocals']
- mid-instantiation-public-selected-call-materialization: ['materializeCanonicalMidCall']
- mid-instantiation-selected-signature-and-passing-readers: ['midSignatureArgumentMatches']
- mid-instantiation-explicit-type-term-and-recipe-grounding: ['instantiateMidTerm', 'instantiateMidType']
- mid-instantiation-canonical-place-operand-and-closed-rvalue-cloning: ['instantiateCanonicalPlace', 'instantiateCanonicalOperand', 'instantiateCanonicalClosedRvalue']
- mid-instantiation-storage-and-return-boundary-application: ['traceMidReturnBoundary']
- mid-instantiation-selected-aggregate-application: ['instantiateCanonicalAggregate']
- mid-instantiation-view-newtype-and-numeric-cast-adaptation: ['instantiateCanonicalViewBoundary', 'instantiateCanonicalCastBoundary']
- mid-instantiation-selected-enum-match-and-destructure: ['midFinalMatchShapeMatches', 'midFinalMatchPayloadMatches']
- mid-instantiation-selected-for-and-try-values: ['instantiateCanonicalForRvalue', 'instantiateCanonicalTryRvalue']
- mid-instantiation-closure-signature-and-capture-application: ['instantiateCanonicalMakeClosure']

## Actions and Completion
per service complete writer/reader/identity/error map and finite callers; source origin/session/body environment and interner/final cache effects preserved; no erased source-owner or raw-Comp wrapper counted as narrowing

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other compiler APIs/algorithms, source semantics, product repair/execution and speculative performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

