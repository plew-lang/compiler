---
id: com-g70q
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:38:29Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Determine check call input service requirements

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-verification-and-contract-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-verification-and-contract-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Close only the exact unresolved families/components listed, preserving accepted direct/delegated input and effect contracts. Produce a finite map of actual type/proof/source-owner/cursor/cache/interner/diagnostic/restore authority and determine justified versus excess, or name a smaller finite remaining question. No broad compiler-wide investigation.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-recorded-source-call-declaration-and-parameter-projection: ['inout fn recordedSourceCallDeclaration(exprId: U64) -> Result[Optional[Func], CompileDiagnostic] {', 'inout fn recordedCallParameterState(exprId: U64) -> Result[SourceCallParameterState, CompileDiagnostic] {', 'inout fn sourceExistentialCallParameters(template: CallTemplate, traitIndex: U64, slot: U64, root: U64) -> Result[SourceCallParameterState, CompileDiagnostic] {']
- codegen-recorded-call-argument-context-and-value-checking: ['inout fn checkRecordedCallLiteralArguments(exprId: U64, args: ArgRange) -> Result[Bool, CompileDiagnostic] {']
- codegen-symbolic-selected-requirement-argument-checking: ['inout fn checkSymbolicMethodArgs(exprId: U64, fnIdx: U64, receiverRef: U64, nameStart: U64, nameLen: U64, args: ArgRange) -> Result[Bool, CompileDiagnostic] {']
- codegen-unique-value-ownership-and-pattern-access-observation: ['inout fn checkUniquePlaceCopy(exprId: U64, inoutOk: Bool) -> Result[(), CompileDiagnostic] {', 'inout fn expressionProvidesOwnership(exprId: U64) -> Bool {', 'inout fn matchConsumesValue(scrut: U64, typeTerm: U64) -> Bool {', 'inout fn matchScrutIsMove(scrut: U64) -> Bool {', 'inout fn matchScrutIsBorrow(scrut: U64) -> Bool {', 'inout fn checkMatchAccessMode(scrut: U64, arms: MatchArmRange) -> Result[(), CompileDiagnostic] {', 'inout fn checkPatternAccessMode(scrut: U64, isStruct: Bool) -> Result[(), CompileDiagnostic] {']
- codegen-call-argument-ownership-mode-and-conflict-diagnostic: ['typeArgumentConflictDiagnostic only']
- codegen-free-call-legacy-parameter-and-literal-validation: ['inout fn localTypeRefByName(nameStart: U64, nameLen: U64) -> U64 {', 'inout fn checkCallArgs(id: U64, nameStart: U64, nameLen: U64, args: ArgRange) -> Result[(), CompileDiagnostic] {']
- codegen-receiver-owned-generic-parameter-count: ['inout fn recvOwnParamCount(rt: TypeInfo) -> U64 {']
- codegen-method-argument-selected-and-legacy-validation: ['inout fn checkMethodArgs(exprId: U64, recv: U64, nameStart: U64, nameLen: U64, args: ArgRange) -> Result[(), CompileDiagnostic] {']

## Actions and Completion
For confirmed scope remove real broad signatures/grants at every actual caller/consumer while retaining the listed legitimate effects; use TDD/refactor controls, structural proof and independent review. For unresolved scope independently review exact closure and assign bounded repairs, without claiming repair/GREEN.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other domains, language acceptance/algorithm/ABI changes, unsupported feature work, product edits/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

