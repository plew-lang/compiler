---
id: com-6ygf
status: closed
deps: []
links: []
created: 2026-10-13T00:48:29Z
type: bug
priority: 1
assignee: Koji Murata
tags: [backend, driver]
---
# Reject incompatible nonempty DataLayout before ORC admission

Resolved discrepancy: object output rejected an incompatible nonempty module DataLayout, while ORC consumeModule replaced it with the engine layout without comparison. Previously emitted layout-dependent offsets cannot safely be reinterpreted merely by replacing the string.

Evidence: compiler source base 6fe09bc7c0e75260b3f773643921478b5020b94f, rechecked during documentation consolidation. native/llvm_backend.cpp consumeModule calls setDataLayout unconditionally after triple validation; object output compares LLVMGetDataLayoutStr first. This is source inspection, not a demonstrated user-program miscompile or a completed audit of all layout consumers.

## Design

[LLVM backend target and layout contract](../design/llvm-backend.md#target-and-native-output) requires agreement/rejection before layout-dependent consumption. Trace earlier layout attachment and object/JIT consumers; retain owned Module/Context transfer and failure cleanup.

## Acceptance Criteria

Reject a nonempty incompatible ORC layout before publication; allow absent layout to be attached at the appropriate boundary. Test compatible/absent/incompatible layouts and failure ownership on object and ORC paths. Verify earlier layout-dependent emission uses the same target contract; update design audit scope.

## Source Recheck for the Conformance Inventory

Compiler `ea5f751a`, spec `16f2f13`, Syntax `00f740e1`; static inspection only,
without executing a compiler or reproducing runtime/test failures. The bounded
[whole-reference inventory](met-z0ro.md) does not close this implementation issue.

Rechecked native/llvm_backend.cpp::consumeModule: after verifying IR and the
native target triple, it still calls setDataLayout(engine.getDataLayout()) without
comparing an existing nonempty layout. The object path's agreement check remains
separate. This confirms the recorded source discrepancy at the audit input; it
is not a demonstrated application miscompile, a new severity escalation, or proof
that every malformed layout reaches this function.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Included repair**.

Current object/ORC layout admission and failure ownership. Compatible/absent/incompatible input controls; no new target.

## Implementation Increment

A bounded native probe built from the unchanged bridge accepted a module with e-p:32:32 (return zero), demonstrating the mismatch on this 64-bit native host. The repair shares compatibleDataLayout between object and consuming ORC admission: empty is permitted and then attached; nonempty must agree with the selected native layout before publication. Module/Context ownership and terminal failure remain in the existing common consumeModule path used by add, signature declarations and lazy callbacks.

The inspected earlier producers lowerExecutableLlvm, lowerCallableDeclarationsLlvm and lowerGlobalStorageLlvm set the native triple without attaching another DataLayout. Native global-size queries occur after consumeModule; object optimization follows its agreement/attachment boundary. This closes native layout admission, not the separate whole-representation audit.

Extended OrcNative.cpp covers missing/compatible/incompatible layouts on borrowed object and consuming ORC paths, unchanged output on object rejection, no callable publication after rejection, and signature-only mismatch. Normal LLVM20 and LLVM22 ASan/LSan pass; bridge/host instrumentation does not cover nested JIT instructions. The check is now registered in the normal suite. Fresh compiler self-host/performance and product entry checks also pass; main/seed are unchanged.

## Outcome

Resolved in 9fd85bb6. [Saved evidence](../../../evidence/existing-feature-conformance/orc-layout/README.md) records the pre-fix admission probe, normal LLVM20 and native LLVM22 ASan/LSan controls, generation-2 LLVM/runtime fixed point, median 6.302362 seconds and final-binary lazy CLI/direct-object checks. Empty layout attachment and native-only target support are preserved. Original whole normal/gen evidence belongs to the preceding root-use increment; it is not relabeled as a post-native-fix run. Full final-candidate integration gates remain in com-604k. This closes the bounded admission contract, not the separate whole-representation audit.
