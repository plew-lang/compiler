---
id: com-t4gm
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:40:58Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow conversion navigation clause-index and proof-support inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/constraints-and-declaration-obligation-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-constraints-and-declaration-obligation-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Only recordGlobalConversionOwner/sourceDeclarationCallBoundIndices/requireDeclarationProofSupport/checkConversionProofBoundary/callConstraintIsRelevant/callConstraintSubstitutionState/selectedCallHasDeferredConstraints/declarationTypeScope; preserve readonly canonical equality/closedness, same-session owner/location/prepared strong reader and actual hint/cache/measurement effects, lexical owner/binders, bounded conversion map writes, bound index ordering/duplicates, all actual sentinels/Deferred/error behavior and diagnostic provenance. Neighboring full evidence admission, grounding and dependency recursion is outside confirmed scope.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-global-conversion-owner-navigation-publication: recordGlobalConversionOwner
- codegen-conversion-endpoint-boundary-validation: checkConversionProofBoundary only; checkConversionProofAtBoundary remains unresolved
- codegen-declaration-obligation-relevance-and-substitution-gates: callConstraintIsRelevant/callConstraintSubstitutionState
- codegen-selected-source-constraint-deferredness-query: selectedCallHasDeferredConstraints
- codegen-lexical-declaration-type-scope-construction: declarationTypeScope
- codegen-source-signature-clause-term-and-identity-projection: sourceDeclarationCallBoundIndices only
- codegen-declaration-proof-support-and-witness-dependency-analysis: requireDeclarationProofSupport only

## Actions and Completion
For confirmed scope change actual signatures and all actual consumers with TDD/refactor controls and independent structural review. For unresolved scope deliver a finite read/write/identity/error closure and supported verdict, assigning repair owners without claiming implementation GREEN.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other domains, language acceptance/solver/algorithm redesign, broad new verification requirements, product edits/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

