---
id: com-16j0
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:40:57Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Close selected trait substitution and associated reification input services

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/constraints-and-declaration-obligation-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-constraints-and-declaration-obligation-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
For only the exact unresolved APIs/components listed by these rows, map every direct/delegated reader, writer, retained callback/owner, query-local guard, same-session/type/binder/proof/source identity, cache/interner effect, diagnostic and success/error restoration. Close the named dependency edges without requiring all compiler algorithms; then independently decide justified versus excess, or retain a smaller finite question with explicit owner.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-static-trait-self-and-instance-term-substitution: ['inout fn staticRequirementType(ref: U64, traitDef: TraitDef, receiverRef: U64, traitArgs: Array[U64]) -> U64 {']
- codegen-bound-owned-trait-term-and-constraint-reification: ['inout fn traitBoundTypeTerm(ref: U64, bound: TraitBound, traitIndex: U64, includeInherited: Bool = true) -> U64 {', 'inout fn traitConstraintInBound(constraint: TraitConstraint, bound: TraitBound, traitIndex: U64, includeInherited: Bool = true) -> TraitConstraint {']
- codegen-missing-and-supertrait-bound-value-projection: missingTraitBound only
- codegen-conformance-owned-bound-and-assumption-projection: ['inout fn conformanceTraitBound(conformance: Conform) -> TraitBound {', 'inout fn conformanceDeclarationAssumptions(conformIndex: U64) -> Array[DeclarationBoundRef] {']
- codegen-static-proof-selected-trait-bound-projection: ['inout fn staticProofBound(proof: StaticConformanceProof, traitIdx: U64) -> Result[TraitBound, CompileDiagnostic] {']
- codegen-authored-trait-associated-equality-traversal: ['inout fn traitProjectionEquality(bound: TraitBound, receiver: U64, owner: U64, arguments: Array[U64], member: U64, context: TraitBound, projectionPath: Array[U64], path: Array[U64] = []) -> TraitProjectionEquality {']
- codegen-static-proof-path-bound-projection: ['inout fn staticPathBound(edges: Array[WitnessMatch], traitIdx: U64) -> Result[TraitBound, CompileDiagnostic] {']
- codegen-static-requirement-parameter-type-projection: ['inout fn staticRequirementParamType(resolution: StaticMemberResolution, args: ArgRange, argIdx: U64) -> Result[U64, CompileDiagnostic] {', 'inout fn staticRequirementParamTypeAt(resolution: StaticMemberResolution, paramIdx: U64) -> Result[U64, CompileDiagnostic] {']
- codegen-bound-associated-term-structural-reification: ['inout fn reifyBoundAssociatedTerms(ref: U64, traitDef: TraitDef, receiverRef: U64, traitOwner: U64, traitArgs: Array[U64], predicates: Array[TraitAssocPredicate], includeInherited: Bool = true, projectionPath: Array[U64] = []) -> U64 {']
- codegen-static-requirement-result-signature-reification: ['inout fn staticRequirementResultTypeForProof(traitDef: TraitDef, req: Func, receiverRef: U64, traitArgs: Array[U64], predicates: Array[TraitAssocPredicate]) -> U64 {']
- codegen-static-requirement-method-argument-and-result-inference: ['inout fn staticRequirementCallArguments(resolution: StaticMemberResolution, args: ArgRange) -> Result[Array[U64], CompileDiagnostic] {', 'inout fn staticRequirementCallResultType(resolution: StaticMemberResolution, args: ArgRange) -> Result[U64, CompileDiagnostic] {', 'inout fn staticRequirementResultType(resolution: StaticMemberResolution) -> Result[U64, CompileDiagnostic] {']

## Actions and Completion
For confirmed scope change actual signatures and all actual consumers with TDD/refactor controls and independent structural review. For unresolved scope deliver a finite read/write/identity/error closure and supported verdict, assigning repair owners without claiming implementation GREEN.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other domains, language acceptance/solver/algorithm redesign, broad new verification requirements, product edits/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

