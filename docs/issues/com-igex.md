---
id: com-igex
status: closed
deps: []
links: [com-mmk9]
created: 2026-10-29T18:40:58Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Close lexical scope and selected source signature input services

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/constraints-and-declaration-obligation-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-constraints-and-declaration-obligation-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
For only the exact unresolved APIs/components listed by these rows, map every direct/delegated reader, writer, retained callback/owner, query-local guard, same-session/type/binder/proof/source identity, cache/interner effect, diagnostic and success/error restoration. Close the named dependency edges without requiring all compiler algorithms; then independently decide justified versus excess, or retain a smaller finite question with explicit owner.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-declaration-type-bound-and-proof-dependency-fronts: ['inout fn declarationTypeDependency(ref: U64, scope: DeclarationTypeScope, offset: U64) -> Result[Bool, CompileDiagnostic] {', 'inout fn declarationBoundDependency(bound: TraitBound, scope: DeclarationTypeScope, offset: U64) -> Result[Bool, CompileDiagnostic] {', 'inout fn checkDeclarationAssumptionScope(source: DeclarationBoundRef, scope: DeclarationTypeScope, offset: U64) -> Result[(), CompileDiagnostic] {', 'inout fn declarationProofDependency(proof: StaticConformanceProof, scope: DeclarationTypeScope, offset: U64) -> Result[Bool, CompileDiagnostic] {', 'inout fn declarationStaticMemberDependency(resolution: StaticMemberResolution, scope: DeclarationTypeScope, offset: U64) -> Result[Bool, CompileDiagnostic] {']
- codegen-selected-declaration-call-proof-and-receiver-boundaries: ['inout fn checkDeclarationCallBoundary(proof: StaticConformanceProof, receiverRef: U64, traitIndex: U64, offset: U64) -> Result[(), CompileDiagnostic] {', 'inout fn checkDeclarationDirectCallBoundary(callee: U64, proof: StaticConformanceProof, receiverRef: U64, offset: U64) -> Result[(), CompileDiagnostic] {', 'inout fn checkDeclarationCallProof(proof: StaticConformanceProof, scope: DeclarationTypeScope, offset: U64) -> Result[(), CompileDiagnostic] {', 'inout fn checkDeclarationStaticCallEvidence(resolution: StaticMemberResolution, receiverRef: U64, scope: DeclarationTypeScope, offset: U64) -> Result[(), CompileDiagnostic] {']
- codegen-source-call-operand-type-and-retained-conversion-validation: ['inout fn sourceCallArgumentType(source: CallArgumentSource) -> U64 {', 'inout fn checkSourceCallArgumentType(argument: CallTemplateArgument, expected: U64, owner: U64, offset: U64) -> Result[(), CompileDiagnostic] {']
- codegen-selected-direct-and-static-call-signature-contexts: ['inout fn checkSourceDirectCallArguments(template: CallTemplate, function: Func, arguments: CallTemplateArgumentRange, typeArgs: CallTemplateTypeArgumentRange, proofId: U64) -> Result[(), CompileDiagnostic] {', 'inout fn selectedStaticCallSignature(template: CallTemplate, function: Func, typeArgs: CallTemplateTypeArgumentRange, resolution: StaticMemberResolution) -> Result[SourceCallSignature, CompileDiagnostic] {', 'inout fn checkSourceStaticCallArguments(template: CallTemplate, function: Func, arguments: CallTemplateArgumentRange, typeArgs: CallTemplateTypeArgumentRange, resolution: StaticMemberResolution) -> Result[(), CompileDiagnostic] {']
- codegen-source-call-signature-term-and-argument-check: ['inout fn sourceCallSignatureParameter(ref: U64, signature: SourceCallSignature) -> Result[U64, CompileDiagnostic] {', 'inout fn checkSourceCallArguments(template: CallTemplate, function: Func, arguments: CallTemplateArgumentRange, signature: SourceCallSignature) -> Result[(), CompileDiagnostic] {']
- codegen-source-signature-clause-term-and-identity-projection: ['sourceCallSignatureConstraint', 'sourceDeclarationCallBounds']
- codegen-recorded-call-kind-public-bound-signature-dispatch: ['inout fn sourceSelectedCallBounds(template: CallTemplate) -> Result[Array[TraitBound], CompileDiagnostic] {']
- codegen-selected-receiver-and-static-public-signature-bounds: ['inout fn sourceSelectedReceiverBounds(callee: U64, receiverTerm: U64, proof: StaticConformanceProof) -> Result[Array[TraitBound], CompileDiagnostic] {', 'inout fn sourceSelectedStaticSignatureBounds(resolution: StaticMemberResolution, receiverTerm: U64, arguments: Array[U64], offset: U64) -> Result[Array[TraitBound], CompileDiagnostic] {']
- codegen-selected-call-constraint-proof-boundary-matching: ['inout fn selectedCallConstraintMatches(expected: TraitBound, proof: StaticConformanceProof) -> Result[Bool, CompileDiagnostic] {', 'inout fn checkSelectedCallConstraintBoundary(expected: TraitBound, proof: StaticConformanceProof, offset: U64) -> Result[(), CompileDiagnostic] {']

## Actions and Completion
For confirmed scope change actual signatures and all actual consumers with TDD/refactor controls and independent structural review. For unresolved scope deliver a finite read/write/identity/error closure and supported verdict, assigning repair owners without claiming implementation GREEN.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other domains, language acceptance/solver/algorithm redesign, broad new verification requirements, product edits/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Input Investigation Outcome

The original required input/delegate-authority questions are answered, not merely
assigned elsewhere. [Exact answer](../../../evidence/compiler-api-audit/resolutions/source-signature-inputs.json)
and [independent review](../../../evidence/compiler-api-audit/review-resolution-source-signature-inputs.json)
record the complete named scope, necessary inputs/effects, actual caller contexts,
source identity and supported C conclusion. Required input questions remaining
in this scope: none. Product repairs remain unimplemented and unverified.

Repair ownership: [com-cerv](com-cerv.md), [com-bswq](com-bswq.md), [com-majd](com-majd.md). These repair issues are not evidence of the conclusion; the linked
source closure and independent review are. This closes only this finite
investigation, not com-mmk9 or any product implementation milestone.
