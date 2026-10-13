---
id: com-6ygf
status: open
deps: []
links: []
created: 2026-10-13T00:48:29Z
type: bug
priority: 1
assignee: Koji Murata
tags: [backend, driver]
---
# Reject incompatible nonempty DataLayout before ORC admission

Known implementation discrepancy: object output rejects an incompatible nonempty module DataLayout, while ORC consumeModule replaces it with the engine layout without comparison. Previously emitted layout-dependent offsets cannot safely be reinterpreted merely by replacing the string.

Evidence: compiler source base 6fe09bc7c0e75260b3f773643921478b5020b94f, rechecked during documentation consolidation. native/llvm_backend.cpp consumeModule calls setDataLayout unconditionally after triple validation; object output compares LLVMGetDataLayoutStr first. This is source inspection, not a demonstrated user-program miscompile or a completed audit of all layout consumers.

## Design

[LLVM backend target and layout contract](../design/llvm-backend.md#target-and-native-output) requires agreement/rejection before layout-dependent consumption. Trace earlier layout attachment and object/JIT consumers; retain owned Module/Context transfer and failure cleanup.

## Acceptance Criteria

Reject a nonempty incompatible ORC layout before publication; allow absent layout to be attached at the appropriate boundary. Test compatible/absent/incompatible layouts and failure ownership on object and ORC paths. Verify earlier layout-dependent emission uses the same target contract; update design audit scope.

