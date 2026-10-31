---
id: com-0t9x
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T17:53:14Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow Mid leaf analysis adapter and trace inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/mid-domain-services-and-values.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-mid-domain-services-and-values.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
only affected Mid-only/predicate/trace/selected immutable reader APIs listed by rows; no semantic grounder redesign

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- mid-declaration-effect-public-analysis-entry-and-roots: ['hasMutableGlobals']
- mid-declaration-local-call-access-entry-and-storage-filter: ['declarationCallHasStorageArguments']
- mid-instantiation-rvalue-statement-dispatch-and-failure-trace: ['instantiateCanonicalStatement.locals', 'traceMidInstantiationRvalue']
- mid-instantiation-selected-call-resolution-target-and-receiver: ['instantiateCanonicalCallTarget']
- mid-instantiation-output-cfg-prefix-planning: ['canonicalBlockTargets']
- mid-instantiation-explicit-receiver-passing-and-temporary-borrow: ['canonicalBorrowOperand', 'canonicalReceiverWithPassing']
- mid-instantiation-selected-signature-and-passing-readers: ['midSignatureArgumentMatches']
- mid-instantiation-operand-rvalue-and-conversion-type-readers: ['canonicalMidOperandTypeRef', 'canonicalMidRvalueResultType', 'midConversionSourceRef', 'midConversionTargetRef']
- mid-instantiation-storage-and-return-boundary-application: ['traceMidReturnBoundary']
- mid-instantiation-selected-enum-match-and-destructure: ['midFinalMatchShapeMatches', 'midFinalMatchPayloadMatches']
- mid-build-and-instantiation-trace-presentation: ['traceMidBuildFailure', 'reportMidBuildError', 'traceMidInstantiationFailure']
- mid-verifier-cfg-target-and-writable-physical-path: ['canonicalMidWritablePhysicalPath']
- mid-canonical-async-storage-liveness-plan: ['planCanonicalMidAsyncFrame', 'usePlace', 'definePlace', 'useOperand', 'useRvalue', 'transferTerminator', 'transferStatements', 'borrowedOwners']

## Actions and Completion
typed production/fixture callers use arena/domain values/trace flag; unused Statement.locals removed; no raw Comp/CompRef reaches these leaves; preserve IDs/defaults/output/error codes and owning body pairing

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other compiler APIs/algorithms, source semantics, product repair/execution and speculative performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Adopted Implementation Intake

[com-ptko](com-ptko.md) classifies the exact confirmed scope as required existing-feature phase4 conformance. Required admission owner(s): com-an0b, met-k7ks; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-mid-and-lowering.json) retains all main/mixed roles and normative grounds. Mid-only predicates, canonical CFG/signature/operand readers, frame liveness and trace/error adaptation consume frozen inputs and caller-owned derived plans. These are existing Mid preparation and diagnostic authority contracts, not source reinference or a new semantic grounder.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
