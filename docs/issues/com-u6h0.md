---
id: com-u6h0
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T17:41:17Z
type: task
priority: 2
assignee: Koji Murata
tags: [backend, diagnostics, verification]
---
# Narrow selected finalized LLVM helper service inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/llvm-native-and-path.json), [independent review](../../../evidence/compiler-api-audit/review-capability-llvm-native-and-path.json); fixed source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md); independent of com-jno0/phase 3. No repair has been performed by this audit.

## Guarantee and Scope
Replace full Comp on the selected APIs with finalized metadata/layout/cache, runtime-symbol interning and diagnostic contracts; remove unused literal len and nonphysical receiver authority while preserving exact native ownership/error/evaluation behavior.

Affected APIs: llvmPrimitiveTy; genLlvmArrayValues/genLlvmBufferNew/genLlvmBufferEqValues; genTimerSleep/closureLlvmFnTy; structIdxOfRef; bodyResultType/bodyReturnLlvmTy/bodyParameterLlvmTy; llvmTypeOfRef/emitF64NanCheck; getOrDeclare/genLlvmStr/emitStrSinkValue/emitPathStrIntrinsicValue. Keep the already physical enum payload, bytewise marker and integer coercions unchanged. Separate limited finalized metadata/signature/cache, runtime symbol interner and diagnostic services; full Comp hidden inside a facet is not narrowing. getOrDeclare actually appends arena bytes/name IDs; checkedFinalDestruction updates finalDestructionIds using type equality. Preserve both effects without source-selection or arbitrary publication authority. genLlvmStr needs decoded payload, not unused len. Narrow nonphysical structIdxOfRef/bodyResultType receivers too. Update immediate buffer/layout adapters required by these APIs only; unrelated backend families remain outside this task.

## Actions and Completion
Inventory actual callers and delegated effects for these exact APIs. Apply TDD/refactor rules with behavior-preserving controls, narrow real signatures and update consumers, remove competing broad alternatives, and prove no full compiler/JIT authority is retained indirectly. Preserve failure provenance, source/session identity, borrowed/owned native lifetimes and ordering. Obtain independent review and gates appropriate to the future change.

## Excluded
Whole-backend redesign, source semantics, descriptor publication algorithms and performance work.

