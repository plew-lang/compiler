---
id: com-jc6v
status: in_progress
deps: []
links: [com-mmk9]
created: 2026-10-29T18:38:29Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Determine check generic input service requirements

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-verification-and-contract-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-verification-and-contract-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Close only the exact unresolved families/components listed, preserving accepted direct/delegated input and effect contracts. Produce a finite map of actual type/proof/source-owner/cursor/cache/interner/diagnostic/restore authority and determine justified versus excess, or name a smaller finite remaining question. No broad compiler-wide investigation.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-provided-trait-abstract-item-term: ['inout fn abstractProvidedItemRef(f: Func) -> U64 {']
- codegen-identifier-value-callable-and-qualifier-recording: ['inout fn resolveIdent(start: U64, len: U64, tpFn: U64) -> IdentBinding {', 'inout fn classifyIdent(start: U64, len: U64, tpFn: U64) -> I64 {', 'inout fn recordIdent(id: U64, start: U64, len: U64, tpFn: U64) -> I64 {', 'inout fn bindIsValue(code: I64) -> Bool {', 'inout fn identIsTypeQualifier(start: U64, len: U64, tpFn: U64) -> Bool {']
- codegen-generic-bound-spelling-and-extension-applicability: ['inout fn boundHasTraitNamed(fnIdx: U64, tpStart: U64, tpLen: U64, traitName: String) -> Bool {', 'inout fn boundAllowsExtension(fnIdx: U64, tpStart: U64, tpLen: U64, extStart: U64, extLen: U64) -> Bool {']
- codegen-generic-signature-view-cycle-adapter: ['inout fn checkGenericTypeViewCycles(ref: U64, offset: U64) -> Result[(), CompileDiagnostic] {']
- codegen-generic-declaration-field-type-grounding-scope: ['inout fn genericCheckFieldsUnder(params: Array[Bind], targs: Array[U64], defFields: Array[FieldDef], makeFields: MakeFieldRange) -> Result[(), CompileDiagnostic] {']
- codegen-recorded-direct-call-generic-argument-validation: ['inout fn checkRecordedDirectCallArguments(exprId: U64, args: ArgRange) -> Result[(), CompileDiagnostic] {']
- codegen-generic-value-against-explicit-expected-type: ['inout fn checkGenericTypeMatch(expectedRef: U64, valueExpr: U64) -> Result[(), CompileDiagnostic] {']

## Actions and Completion
For confirmed scope remove real broad signatures/grants at every actual caller/consumer while retaining the listed legitimate effects; use TDD/refactor controls, structural proof and independent review. For unresolved scope independently review exact closure and assign bounded repairs, without claiming repair/GREEN.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other domains, language acceptance/algorithm/ABI changes, unsupported feature work, product edits/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

