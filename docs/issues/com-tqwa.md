---
id: com-tqwa
status: closed
deps: []
links: [com-mmk9]
created: 2026-10-29T18:40:57Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Close viewed static member selection and admission input services

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/constraints-and-declaration-obligation-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-constraints-and-declaration-obligation-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
For only the exact unresolved APIs/components listed by these rows, map every direct/delegated reader, writer, retained callback/owner, query-local guard, same-session/type/binder/proof/source identity, cache/interner effect, diagnostic and success/error restoration. Close the named dependency edges without requiring all compiler algorithms; then independently decide justified versus excess, or retain a smaller finite question with explicit owner.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-viewed-constraint-query-and-result-projections: ['inout fn viewedTypeConformsTraitConstraint(demand: ConformanceProofDemand, ref: U64, constraint: TraitConstraint, assumptions: Array[DeclarationBoundRef] = []) -> Result[Bool, CompileDiagnostic] {', 'inout fn viewedTraitConstraintProof(demand: ConformanceProofDemand, ref: U64, constraint: TraitConstraint, assumptions: Array[DeclarationBoundRef] = []) -> Result[StaticConformanceProof, CompileDiagnostic] {', 'inout fn queryViewedTraitConstraint(demand: ConformanceProofDemand, ref: U64, constraint: TraitConstraint, assumptions: Array[DeclarationBoundRef] = []) -> Result[ConformanceProofResult, CompileDiagnostic] {']
- codegen-ambient-function-static-trait-pattern-query: ['inout fn staticTraitPatternProof(receiverRef: U64, traitId: U64, traitOwner: U64, traitArgs: Array[U64], patternParams: PatternBindInput) -> Result[StaticConformanceProof, CompileDiagnostic] {']
- codegen-known-call-type-argument-partial-substitution: ['inout fn groundKnownCallTypeArguments(ref: U64, params: FuncBindRange, values: Array[U64], receiver: U64) -> Result[U64, CompileDiagnostic] {']
- codegen-static-member-argument-type-ranking: ['inout fn staticRequirementMatchRank(resolution: StaticMemberResolution, requirement: Func, args: ArgRange) -> Result[U64, CompileDiagnostic] {']
- codegen-selected-trait-requirement-frontier-ranking: ['inout fn selectStaticRequirement(proof: StaticConformanceProof, traitIdx: U64, memberId: U64, args: ArgRange) -> Result[StaticMemberResolution, CompileDiagnostic] {']
- codegen-static-member-source-frontier-and-selection: ['inout fn staticMemberResolution(fnIdx: U64, receiverRef: U64, nameStart: U64, nameLen: U64, args: ArgRange, requiredTraitOwner: U64 = 0U64) -> Result[StaticMemberResolution, CompileDiagnostic] {']
- codegen-selected-static-member-instance-source-admission: ['inout fn admitStaticMemberInstance(resolution: StaticMemberResolution, receiverRef: U64, assumptions: Array[DeclarationBoundRef]) -> Result[StaticMemberResolution, CompileDiagnostic] {']
- codegen-static-operator-lexical-bound-resolution: ['inout fn staticOperatorResolution(fnIdx: U64, receiverRef: U64, traitName: String, memberName: String, arity: U64, traitArity: U64 = 0U64) -> Result[StaticMemberResolution, CompileDiagnostic] {']

## Actions and Completion
For confirmed scope change actual signatures and all actual consumers with TDD/refactor controls and independent structural review. For unresolved scope deliver a finite read/write/identity/error closure and supported verdict, assigning repair owners without claiming implementation GREEN.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other domains, language acceptance/solver/algorithm redesign, broad new verification requirements, product edits/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Input Investigation Outcome

The original required input/delegate-authority questions are answered, not merely
assigned elsewhere. [Exact answer](../../../evidence/compiler-api-audit/resolutions/viewed-static-selection-inputs.json)
and [independent review](../../../evidence/compiler-api-audit/review-resolution-viewed-static-selection-inputs.json)
record the complete named scope, necessary inputs/effects, actual caller contexts,
source identity and supported C conclusion. Required input questions remaining
in this scope: none. Product repairs remain unimplemented and unverified.

Repair ownership: [com-9mqu](com-9mqu.md), [com-j0r9](com-j0r9.md), [com-33jc](com-33jc.md), [com-00c4](com-00c4.md), [com-zai9](com-zai9.md). These repair issues are not evidence of the conclusion; the linked
source closure and independent review are. This closes only this finite
investigation, not com-mmk9 or any product implementation milestone.
