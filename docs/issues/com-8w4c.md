---
id: com-8w4c
status: open
deps: []
links: []
created: 2026-10-13T01:29:04Z
type: task
priority: 3
assignee: Koji Murata
tags: [backend, driver]
---
# Reassess unresolved JIT backend memcpy for Syntax AST workloads

Historical Syntax AST --run workloads reported unresolved LLVM-generated _memcpy while native execution succeeded. [Original reproduction scope](https://github.com/plew-lang/meta/blob/main/evidence/standalone-block-expressions/README.md#対象外の既存不具合). This is not a fresh assertion about current main. Design: [LLVM backend](../design/llvm-backend.md), [driver](../design/driver-and-execution.md).

Evidence scope: retained from meta agents/provisional.md at c539d7b96615a5c59c0165b0a5e3df90ec1f8dac; grammar-specific items additionally come from agents/grammar.md at that revision. These notes mix historical reproduction and uninspected combinations. No current compiler run or exhaustive implementation audit was performed during migration. Recheck current source and minimal run/reject inputs before claiming a defect; close resolved investigations with evidence rather than weakening the specification.

## Acceptance Criteria

Reproduce with pinned source/toolchain, identify intended backend libcall resolution authority separately from source symbols, fix if still present and compare native/JIT behavior without arbitrary host-symbol fallback.
