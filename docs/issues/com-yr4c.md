---
id: com-yr4c
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:40:58Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Close retained conversion and proof admission input services

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/constraints-and-declaration-obligation-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-constraints-and-declaration-obligation-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
For only the exact unresolved APIs/components listed by these rows, map every direct/delegated reader, writer, retained callback/owner, query-local guard, same-session/type/binder/proof/source identity, cache/interner effect, diagnostic and success/error restoration. Close the named dependency edges without requiring all compiler algorithms; then independently decide justified versus excess, or retain a smaller finite question with explicit owner.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-pending-source-conversion-completion: ['inout fn completePendingSourceConversion(index: U64) -> Result[(), CompileDiagnostic] {', 'inout fn completeSourceConversions(owner: SemanticCompletionOwner) -> Result[(), CompileDiagnostic] {']
- codegen-declaration-conversion-evidence-admission: ['inout fn checkDeclarationConversionEvidence(conversion: DeclarationConversion) -> Result[(), CompileDiagnostic] {']
- codegen-conversion-endpoint-boundary-validation: checkConversionProofBoundary only; checkConversionProofAtBoundary remains unresolved
- codegen-retained-conversion-proof-recursive-validation: ['inout fn checkConversionProofEvidence(proof: ValueConversionProof, offset: U64) -> Result[(), CompileDiagnostic] {']
- codegen-static-conformance-proof-integrity-admission: ['inout fn checkStaticProofEvidence(proof: StaticConformanceProof, offset: U64) -> Result[(), CompileDiagnostic] {']
- codegen-retained-static-path-predecessor-validation: ['inout fn checkStaticPathEvidence(edges: Array[WitnessMatch], root: TraitBound, offset: U64) -> Result[(), CompileDiagnostic] {']
- codegen-selected-witness-condition-plan-admission: ['inout fn checkWitnessConditionEvidence(witness: WitnessMatch, offset: U64) -> Result[(), CompileDiagnostic] {']
- codegen-selected-projection-normalization-evidence-admission: ['inout fn checkProjectionNormalizations(normalizations: Array[ProjectionNormalizationStep], offset: U64) -> Result[(), CompileDiagnostic] {']
- codegen-saved-projection-and-constraint-normalization-replay: ['inout fn replayProjectionNormalizations(ref: U64, normalizations: Array[ProjectionNormalizationStep], offset: U64, active: Array[U64] = []) -> Result[U64, CompileDiagnostic] {', 'inout fn replayConstraintNormalizations(constraint: TraitConstraint, normalizations: Array[ProjectionNormalizationStep], offset: U64) -> Result[TraitConstraint, CompileDiagnostic] {']
- codegen-condition-child-clause-proof-validation: ['inout fn checkWitnessConditionChildren(witness: WitnessMatch, proofs: Array[U64], normalizations: Array[ProjectionNormalizationStep], offset: U64) -> Result[(), CompileDiagnostic] {']

## Actions and Completion
For confirmed scope change actual signatures and all actual consumers with TDD/refactor controls and independent structural review. For unresolved scope deliver a finite read/write/identity/error closure and supported verdict, assigning repair owners without claiming implementation GREEN.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other domains, language acceptance/solver/algorithm redesign, broad new verification requirements, product edits/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

