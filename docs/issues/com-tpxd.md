---
id: com-tpxd
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:40:58Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Close source constraint plan and scoped dependency input services

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/constraints-and-declaration-obligation-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-constraints-and-declaration-obligation-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
For only the exact unresolved APIs/components listed by these rows, map every direct/delegated reader, writer, retained callback/owner, query-local guard, same-session/type/binder/proof/source identity, cache/interner effect, diagnostic and success/error restoration. Close the named dependency edges without requiring all compiler algorithms; then independently decide justified versus excess, or retain a smaller finite question with explicit owner.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-retained-source-call-constraint-plan-admission: ['inout fn checkSelectedCallConstraintPlan(template: CallTemplate, expected: Array[TraitBound], plan: SelectedCallConstraints) -> Result[(), CompileDiagnostic] {']
- codegen-source-call-constraint-first-publication: ['inout fn prepareCallTemplateConstraints(templateIndex: U64) -> Result[(), CompileDiagnostic] {']
- codegen-recorded-call-constraint-and-root-proof-admission: ['inout fn checkRecordedCallConstraintEvidence(templateIndex: U64) -> Result[(), CompileDiagnostic] {', 'inout fn checkCallTemplateEvidence(template: CallTemplate) -> Result[(), CompileDiagnostic] {']
- codegen-deferred-call-and-conversion-lexical-dependency-checks: ['inout fn checkDeferredCallDependency(template: CallTemplate) -> Result[(), CompileDiagnostic] {', 'inout fn declarationConversionDependency(conversion: ValueConversionProof, scope: DeclarationTypeScope, offset: U64) -> Result[Bool, CompileDiagnostic] {']
- codegen-declaration-constraint-and-associated-assumption-dependencies: ['inout fn declarationConstraintDependency(constraint: TraitConstraint, scope: DeclarationTypeScope, offset: U64) -> Result[Bool, CompileDiagnostic] {', 'inout fn declarationAssumptionDependency(source: DeclarationBoundRef, prerequisiteDependent: Bool, bound: TraitBound, scope: DeclarationTypeScope, offset: U64) -> Result[Bool, CompileDiagnostic] {']
- codegen-declaration-assumption-scope-admission-front: ['inout fn admitDeclarationAssumptionScope(source: DeclarationBoundRef, scope: DeclarationTypeScope, offset: U64) -> Result[Bool, CompileDiagnostic] {']
- codegen-prepared-declaration-request-dedup-and-publication: ['inout fn appendPreparedCallConstraintInstance(function: U64, arguments: Array[U64], receiver: U64, environment: InstanceEnvironment, depth: U64, requests: inout Array[CallConstraintInstance], heads: inout Dictionary[U64, U64], relevant: Array[Bool]) -> Result[DeclarationObligationState, CompileDiagnostic] {']
- codegen-declaration-proof-support-and-witness-dependency-analysis: requireDeclarationProofSupport only
- codegen-scoped-assumption-prerequisite-and-authority-analysis: ['inout fn scopedAssumptionDependencies(source: DeclarationBoundRef, scope: DeclarationTypeScope, offset: U64) -> Result[DeclarationProofDependencies, CompileDiagnostic] {', 'inout fn scopedAssociatedPrerequisite(index: U64, scope: DeclarationTypeScope, offset: U64) -> Result[DeclarationProofDependencies, CompileDiagnostic] {']
- codegen-static-proof-scoped-dependency-dispatch: ['inout fn scopedProofDependencies(proof: StaticConformanceProof, scope: DeclarationTypeScope, offset: U64) -> Result[DeclarationProofDependencies, CompileDiagnostic] {']

## Actions and Completion
For confirmed scope change actual signatures and all actual consumers with TDD/refactor controls and independent structural review. For unresolved scope deliver a finite read/write/identity/error closure and supported verdict, assigning repair owners without claiming implementation GREEN.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other domains, language acceptance/solver/algorithm redesign, broad new verification requirements, product edits/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

