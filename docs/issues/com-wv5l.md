---
id: com-wv5l
status: closed
deps: []
links: [com-mmk9]
created: 2026-10-29T18:38:29Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Determine interface check input service requirements

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-verification-and-contract-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-verification-and-contract-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Close only the exact unresolved families/components listed, preserving accepted direct/delegated input and effect contracts. Produce a finite map of actual type/proof/source-owner/cursor/cache/interner/diagnostic/restore authority and determine justified versus excess, or name a smaller finite remaining question. No broad compiler-wide investigation.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-source-interface-root-construction-and-retention: ['inout fn createInterfaceEvidenceRoot(site: CallSiteKey, receiver: U64, traitIndex: U64) -> Result[U64, CompileDiagnostic] {', 'inout fn retainSourceInterfaceRoot(site: CallSiteKey, receiver: U64, traitIndex: U64) -> Result[U64, CompileDiagnostic] {', 'inout fn requireSourceInterfaceRoot(root: U64, site: CallSiteKey, receiver: U64, traitIndex: U64) -> Result[InterfaceEvidenceRoot, CompileDiagnostic] {']
- codegen-interface-call-scope-and-signature-bound-projection: ['inout fn callConstraintScope(template: CallTemplate) -> Result[DeclarationTypeScope, CompileDiagnostic] {', 'inout fn sourceInterfaceSignatureBounds(template: CallTemplate, root: U64, traitIndex: U64, slot: U64) -> Result[Array[TraitBound], CompileDiagnostic] {', 'inout fn interfaceSignatureBounds(root: U64, bound: TraitBound, traitIndex: U64, slot: U64, offset: U64) -> Result[Array[TraitBound], CompileDiagnostic] {']
- codegen-interface-associated-assumption-expansion: ['inout fn appendInterfaceAssociatedAssumptions(source: DeclarationBoundRef, steps: Array[SupertraitRef], assumptions: inout Array[DeclarationBoundRef], depth: U64 = 0U64) -> Result[(), CompileDiagnostic] {']
- codegen-interface-table-member-contract-admission: ['inout fn createInterfaceContractRoot(target: U64, traitIndex: U64, slot: U64) -> Result[U64, CompileDiagnostic] {', 'inout fn interfaceMethodConditions(target: U64, traitIndex: U64, requirement: U64) -> Result[Optional[ExistentialMethodConditions], CompileDiagnostic] {']

## Actions and Completion
For confirmed scope remove real broad signatures/grants at every actual caller/consumer while retaining the listed legitimate effects; use TDD/refactor controls, structural proof and independent review. For unresolved scope independently review exact closure and assign bounded repairs, without claiming repair/GREEN.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other domains, language acceptance/algorithm/ABI changes, unsupported feature work, product edits/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


 ## Input Investigation Outcome

 The original required input/delegate-authority questions are answered, not merely
 assigned elsewhere. [Exact answer](../../../evidence/compiler-api-audit/resolutions/destruction-interface-inputs.json)
 and [independent review](../../../evidence/compiler-api-audit/review-resolution-destruction-interface-inputs.json)
 record the complete named scope, necessary inputs/effects, actual caller contexts,
 source identity and supported C conclusion. Required input questions remaining
 in this scope: none. Product repairs remain unimplemented and unverified.

 Repair ownership: [com-hfwv](com-hfwv.md), [com-r4a9](com-r4a9.md), [com-a3ph](com-a3ph.md), [com-h5be](com-h5be.md), [com-282i](com-282i.md), [com-wsfk](com-wsfk.md), [com-rad4](com-rad4.md), [com-hjrk](com-hjrk.md), [com-dc9e](com-dc9e.md), [com-iucg](com-iucg.md), [com-f99l](com-f99l.md), [com-zml3](com-zml3.md), [com-4j5l](com-4j5l.md), [com-vjj4](com-vjj4.md), [com-k0zf](com-k0zf.md), [com-nz4n](com-nz4n.md), [com-4c9t](com-4c9t.md). These repair issues are not evidence of the conclusion; the linked
 source closure and independent review are. This closes only this finite
 investigation, not com-mmk9 or any product implementation milestone.
