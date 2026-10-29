---
id: com-og6p
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:40:57Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Close remaining conformance and via contract helper input services

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/constraints-and-declaration-obligation-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-constraints-and-declaration-obligation-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
For only the exact unresolved APIs/components listed by these rows, map every direct/delegated reader, writer, retained callback/owner, query-local guard, same-session/type/binder/proof/source identity, cache/interner effect, diagnostic and success/error restoration. Close the named dependency edges without requiring all compiler algorithms; then independently decide justified versus excess, or retain a smaller finite question with explicit owner.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-viewed-trait-query-explicit-demand-adapters: ['viewedTypeConforms', 'queryViewedTraitProof']
- codegen-legacy-conformance-associated-span-and-head-substitution: ['inout fn conformAssocBindingSpan(cf: Conform, nameStart: U64, nameLen: U64) -> Bind {', 'inout fn substReqParamHeadId(cf: Conform, recvStart: U64, recvLen: U64, tps: Array[Bind], targs: Array[U64], prStart: U64, prLen: U64) -> U64 {', 'inout fn substReqParamArrayElemRef(tps: Array[Bind], targs: Array[U64], prStart: U64, prLen: U64) -> U64 {']
- codegen-conformance-requirement-parameter-alpha-comparison: ['inout fn conformanceParameterTypesMatch(cf: Conform, witness: Func, requirement: Func, parameters: FuncParamRange) -> Bool {']
- codegen-conformance-witness-completeness-and-legacy-result-check: ['reqReturnMismatch', 'witnessedHas remaining parameter/result services', 'confWitnessesAll']
- codegen-existential-formation-bound-completeness-check: ['checkAnyFormation', 'checkAnyTypeFormation']
- codegen-via-target-common-callable-signature-validation: ['inout fn viaSignatureMatches(witness: Func, target: Func) -> Bool {', 'inout fn checkViaTargets() -> Result[(), CompileDiagnostic] {']
- codegen-legacy-nominal-conformance-and-witness-name-queries: ['inout fn typeConformsTo(typeStart: U64, typeLen: U64, traitStart: U64, traitLen: U64) -> Bool {', 'inout fn witnessFnFor(typeStart: U64, typeLen: U64, nameStart: U64, nameLen: U64) -> U64 {']
- codegen-conformance-instance-bool-and-legacy-trait-spelling-adapters: ['inout fn conformsInstance(demand: ConformanceProofDemand, ref: U64, traitStart: U64, traitLen: U64, traitArgs: Array[U64] = [], traitArgsOpen: Bool = false, assocNames: Array[U64] = [], assocValues: Array[U64] = []) -> Result[Bool, CompileDiagnostic] {', 'inout fn typeConformsToName(typeStart: U64, typeLen: U64, traitName: String) -> Bool {']

## Actions and Completion
For confirmed scope change actual signatures and all actual consumers with TDD/refactor controls and independent structural review. For unresolved scope deliver a finite read/write/identity/error closure and supported verdict, assigning repair owners without claiming implementation GREEN.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other domains, language acceptance/solver/algorithm redesign, broad new verification requirements, product edits/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

