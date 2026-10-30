---
id: com-a1qy
status: closed
deps: []
links: [com-mmk9]
created: 2026-10-29T18:40:58Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Close conversion expansion and declaration request input services

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/constraints-and-declaration-obligation-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-constraints-and-declaration-obligation-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
For only the exact unresolved APIs/components listed by these rows, map every direct/delegated reader, writer, retained callback/owner, query-local guard, same-session/type/binder/proof/source identity, cache/interner effect, diagnostic and success/error restoration. Close the named dependency edges without requiring all compiler algorithms; then independently decide justified versus excess, or retain a smaller finite question with explicit owner.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-array-conversion-element-boundary-projection: ['inout fn arrayConversionElementBoundary(sourceRef: U64, targetRef: U64, offset: U64) -> Result[ValueConversionBoundary, CompileDiagnostic] {']
- codegen-owner-source-conversion-evidence-validation-entry: ['inout fn checkSourceConversionEvidence(owner: SemanticCompletionOwner) -> Result[(), CompileDiagnostic] {']
- codegen-abstract-existential-witness-plan-shape-check: ['inout fn checkAbstractExistentialPlans(evidence: ExistentialBoxEvidence) -> Result[(), CompileDiagnostic] {']
- codegen-phantom-conversion-semantic-obligation-check: ['inout fn checkSemanticConversionObligations(conversion: ValueConversionProof, environment: InstanceEnvironment) -> Result[DeclarationObligationState, CompileDiagnostic] {']
- codegen-payload-conversion-declaration-obligation-expansion: ['inout fn checkConversionObligations(conversion: ValueConversionProof, environment: InstanceEnvironment, depth: U64, requests: inout Array[CallConstraintInstance], heads: inout Dictionary[U64, U64], relevant: Array[Bool]) -> Result[DeclarationObligationState, CompileDiagnostic] {']
- codegen-declaration-call-instance-admission-to-request-handoff: ['inout fn appendCallConstraintInstance(function: U64, arguments: Array[U64], receiver: U64, proof: StaticConformanceProof, constraints: CallableConstraintEvidence = <CallableConstraintEvidence.Declaration />, depth: U64, requests: inout Array[CallConstraintInstance], heads: inout Dictionary[U64, U64], relevant: Array[Bool]) -> Result[DeclarationObligationState, CompileDiagnostic] {']
- codegen-selected-static-member-instance-type-argument-mapping: ['inout fn callConstraintTypeArguments(function: Func, receiver: U64, proof: StaticConformanceProof) -> Result[Array[U64], CompileDiagnostic] {', 'inout fn staticMemberInstanceArguments(resolution: StaticMemberResolution, function: U64, receiver: U64, proof: StaticConformanceProof, methodArguments: Array[U64], environment: InstanceEnvironment) -> Result[Array[U64], CompileDiagnostic] {']
- codegen-static-member-selected-declaration-obligation: ['inout fn checkStaticMemberObligation(template: CallTemplate, resolution: StaticMemberResolution, methodArguments: Array[U64] = [], receiver: U64, environment: InstanceEnvironment, depth: U64, requests: inout Array[CallConstraintInstance], heads: inout Dictionary[U64, U64], relevant: Array[Bool]) -> Result[DeclarationObligationState, CompileDiagnostic] {']
- codegen-recorded-call-template-declaration-obligation-dispatch: ['inout fn checkCallConstraintTemplate(template: CallTemplate, environment: InstanceEnvironment, depth: U64, requests: inout Array[CallConstraintInstance], heads: inout Dictionary[U64, U64], relevant: Array[Bool]) -> Result[DeclarationObligationState, CompileDiagnostic] {']
- codegen-member-obligation-declaration-relevance-slice: ['inout fn memberObligationRelevance() -> Result[Array[Bool], CompileDiagnostic] {']

## Actions and Completion
For confirmed scope change actual signatures and all actual consumers with TDD/refactor controls and independent structural review. For unresolved scope deliver a finite read/write/identity/error closure and supported verdict, assigning repair owners without claiming implementation GREEN.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other domains, language acceptance/solver/algorithm redesign, broad new verification requirements, product edits/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Input Investigation Outcome

The original required input/delegate-authority questions are answered, not merely
assigned elsewhere. [Exact answer](../../../evidence/compiler-api-audit/resolutions/obligation-request-inputs.json)
and [independent review](../../../evidence/compiler-api-audit/review-resolution-obligation-request-inputs.json)
record the complete named scope, necessary inputs/effects, actual caller contexts,
source identity and supported C conclusion. Required input questions remaining
in this scope: none. Product repairs remain unimplemented and unverified.

Repair ownership: [com-g3ex](com-g3ex.md), [com-tn1g](com-tn1g.md), [com-odg0](com-odg0.md). These repair issues are not evidence of the conclusion; the linked
source closure and independent review are. This closes only this finite
investigation, not com-mmk9 or any product implementation milestone.
