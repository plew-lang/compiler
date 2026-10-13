---
id: com-ydgx
status: open
deps: []
links: []
created: 2026-10-13T01:19:50Z
type: task
priority: 2
assignee: Koji Murata
tags: [tooling, verification, ownership]
---
# Instrument generated Plew instructions in manual return-transfer diagnostic

The manual test-mid-return-transfer.py --asan path passes clang sanitizer flags directly over generated LLVM and runtime C but does not run the ASan IR pass over Plew instructions. It cannot establish memory-safety coverage for Plew load/store operations. The standard sanitizer gate has a separate instrumentation path and is not invalidated by this manual diagnostic limitation.

Evidence: focused source inspection at compiler source base 6fe09bc7c0e75260b3f773643921478b5020b94f, tests/compiler/codegen/test-mid-return-transfer.py lines selecting flags and linking LLVM. No diagnostic execution was performed while migrating this record. [Test layout](../../tests/README.md) and [instrumentation contract](../design/verification.md#sanitizer-evidence) define the boundary; verify the current script before changing it.

The diagnostic has dedicated retain/drop assertions and remains manual. Preserve those assertions and explicit discovery; do not label an unexecuted manual test a standard green gate. Use the selected toolchain consistently for IR instrumentation, clang linking and sanitizer runtime.

## Acceptance Criteria

Route the manual sanitizer mode through the shared full IR instrumentation/link path, preserve retain/drop checks, and verify emitted ASan accesses plus intentional detection controls and clean positive cases. Record the actual coverage separately from the standard gate.
