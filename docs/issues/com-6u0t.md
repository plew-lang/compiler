---
id: com-6u0t
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:20:07Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Finalized representation/C ABI input separation

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/llvm-physical-services-and-runtime.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-llvm-physical-services-and-runtime.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Exactly affected frozen type/layout/C/global/local/capture/proof APIs. Limited mutable contract memo and diagnostics/name views remain; target/module physical caches preserved, no semantic lookup introduced.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- llvm-closure-capture-slot-and-environment-layout: ['captureValueTy', 'captureSlotTy', 'closureEnvTy']
- llvm-finalized-nominal-layout-registration: ['physicalLayoutContract', 'requireStructLayoutSlot', 'requireEnumLayoutSlot', 'registerFinalLayoutNames', 'registerFinalStructBodies']
- llvm-c-scalar-and-parameter-representation: ['cScalarType', 'cParameterType', 'scalarToC', 'scalarFromC']
- llvm-c-inout-temporary-and-writeback: ['prepareCInout', 'completeCInouts']
- llvm-target-narrow-c-integer-policy: ['cIntegerExtension', 'checkCIntegerExtension', 'attachCIntegerExtension']
- llvm-resolved-foreign-call-admission-and-declaration: ['resolvedCTypeSupported', 'resolvedCCallSupported', 'declareResolvedCFunction']
- llvm-mid-canonical-local-storage-and-parameter-binding: ['midPrepareCanonicalLocals']
- llvm-mid-integer-and-contextual-float-constant: ['midIntegerConstant']
- llvm-mid-canonical-local-global-storage-queries: ['midCanonicalLocalTy', 'midCanonicalGlobalIndex', 'midCanonicalGlobalTy', 'midCanonicalGlobalPtr', 'midCanonicalPlaceTy']
- llvm-mid-frozen-conversion-support-readers: ['midCanonicalConversionProofSupported', 'midCanonicalBorrowedConversionSupported']
- llvm-reference-pointee-and-cell-physical-adapters: ['refPointeeTy']
- llvm-finalized-global-storage-declarations: ['declareGlobalStorage']
- llvm-exposed-c-entry-admission-and-adaptation: ['exposedCTypeSupported', 'emitExposedEntry']
- llvm-finalized-enum-payload-layout-and-construction: ['enumPayloadWords', 'typeWords', 'variantPayloadTy', 'buildEnumFromValues']

## Actions and Completion
Confirmed narrowing follow-up: change the exact actual signatures/consumers, remove competing broad grants, preserve legitimate physical/native/cache/interner/diagnostic/source-ready/lifetime/restore effects, and independently verify with appropriate TDD/refactor controls. This audit itself performs no repair.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Language/source/ABI/runtime algorithm redesign, unrelated compiler facilities, speculative performance claims and product execution within the audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

