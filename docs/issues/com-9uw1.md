---
id: com-9uw1
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:40:58Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Close selected callable constraint and iteration evidence input services

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/constraints-and-declaration-obligation-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-constraints-and-declaration-obligation-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
For only the exact unresolved APIs/components listed by these rows, map every direct/delegated reader, writer, retained callback/owner, query-local guard, same-session/type/binder/proof/source identity, cache/interner effect, diagnostic and success/error restoration. Close the named dependency edges without requiring all compiler algorithms; then independently decide justified versus excess, or retain a smaller finite question with explicit owner.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-callable-bound-explicit-instance-grounding: ['inout fn groundCallableBound(bound: TraitBound, environment: InstanceEnvironment, selfRef: U64, itemRef: U64) -> Result[TraitBound, CompileDiagnostic] {', 'inout fn groundCallableSignatureBounds(fnIdx: U64, environment: InstanceEnvironment) -> Result[Array[TraitBound], CompileDiagnostic] {']
- codegen-selected-callable-signature-bound-admission: ['inout fn checkSelectedCallableBounds(fnIdx: U64, environment: InstanceEnvironment, assumptions: Array[DeclarationBoundRef] = []) -> Result[(), CompileDiagnostic] {']
- codegen-requirement-call-constraint-derivation-replay: ['inout fn instantiateRequirementCallConstraints(fnIdx: U64, environment: InstanceEnvironment, planIndex: U64, bounds: Array[TraitBound], proofs: Array[StaticConformanceProof]) -> Result[CallableConstraintEvidence, CompileDiagnostic] {']
- codegen-recorded-callable-constraint-signature-check: ['inout fn checkCallableConstraintEvidence(fnIdx: U64, environment: InstanceEnvironment, evidence: CallableConstraintEvidence) -> Result[(), CompileDiagnostic] {']
- codegen-callable-instance-prepared-constraint-environment: ['inout fn environmentWithCallableConstraints(fnIdx: U64, environment: InstanceEnvironment, evidence: CallableConstraintEvidence) -> Result[InstanceEnvironment, CompileDiagnostic] {']
- codegen-source-selected-result-recipe-and-closed-receiver-projection: ['inout fn sourceSelectedCallResult(siteKey: CallSiteKey) -> U64 {', 'inout fn closedSelectedCallResult(siteKey: CallSiteKey) -> Result[U64, CompileDiagnostic] {', 'inout fn closedProtocolReceiver(receiver: CallTemplateReceiver) -> Result[U64, CompileDiagnostic] {']
- codegen-closed-iteration-protocol-selected-evidence-validation: ['inout fn checkClosedIterationProtocols() -> Result[(), CompileDiagnostic] {', 'inout fn checkClosedIterationProtocol(templateIndex: U64) -> Result[(), CompileDiagnostic] {']
- codegen-recorded-call-constraint-body-and-whole-declaration-entries: ['inout fn checkRecordedBodyCallConstraints(owner: U64) -> Result[(), CompileDiagnostic] {', 'inout fn checkRecordedCallTemplateBound(templateIndex: U64) -> Result[(), CompileDiagnostic] {', 'inout fn checkRecordedCallTemplateBounds() -> Result[(), CompileDiagnostic] {']
- codegen-method-receiver-directional-instance-environment: ['inout fn methodReceiverEnvironment(f: Func, instRef: U64) -> Result[WitnessMatch, CompileDiagnostic] {']

## Actions and Completion
For confirmed scope change actual signatures and all actual consumers with TDD/refactor controls and independent structural review. For unresolved scope deliver a finite read/write/identity/error closure and supported verdict, assigning repair owners without claiming implementation GREEN.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other domains, language acceptance/solver/algorithm redesign, broad new verification requirements, product edits/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

