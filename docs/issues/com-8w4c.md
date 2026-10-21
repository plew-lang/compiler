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
# Verify the retained JIT memory-libcall repair on Syntax AST workloads

Historical Syntax AST --run workloads reported unresolved LLVM-generated _memcpy while native execution succeeded. [Original reproduction scope](https://github.com/plew-lang/meta/blob/main/evidence/standalone-block-expressions/README.md#対象外の既存不具合). This is not a fresh assertion about current main. Design: [LLVM backend](../design/llvm-backend.md), [driver](../design/driver-and-execution.md).

Evidence scope: retained from meta agents/provisional.md at c539d7b96615a5c59c0165b0a5e3df90ec1f8dac; grammar-specific items additionally come from agents/grammar.md at that revision. These notes mix historical reproduction and uninspected combinations. No current compiler run or exhaustive implementation audit was performed during migration. Recheck current source and minimal run/reject inputs before claiming a defect; close resolved investigations with evidence rather than weakening the specification.

## Acceptance Criteria

Reproduce with pinned source/toolchain, identify intended backend libcall resolution authority separately from source symbols, fix if still present and compare native/JIT behavior without arbitrary host-symbol fallback.

## Later Evidence Superseding the Earlier Unresolved Note

The later type-checking remediation record explicitly reports the memory-libcall repair: LLVM-generated memcpy/memmove/memset and Darwin bzero resolve through a limited fallback JITDylib to the common host implementation; general process lookup for source symbols remains prohibited. [Immutable later record](https://github.com/plew-lang/meta/blob/39db039d6d20a53b19966440a9886a30c4476858/agents/typechecking-design-review.md#再開順序発散仕様を確定して共通基盤へ統合する). Treat the original unresolved reproduction as historical, not current failure. The retained follow-up is fresh scoped/full-gate confirmation of the repair, not implementing it again. The internal-session JIT interruption under final-call-authority is a separate investigation in [met-rzt4](met-rzt4.md).
