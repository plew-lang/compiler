---
id: com-ej0z
status: open
deps: []
links: []
created: 2026-10-13T01:29:04Z
type: task
priority: 3
assignee: Koji Murata
tags: [backend, driver, verification]
---
# Assess additional compiler target support

Additional target support is retained future scope, distinct from clean-host release admission for currently supported targets (com-ao7z). Design: [representation and ABI](../design/representation-and-abi.md), [backend](../design/llvm-backend.md).

Evidence scope: retained from meta agents/provisional.md at c539d7b96615a5c59c0165b0a5e3df90ec1f8dac; grammar-specific items additionally come from agents/grammar.md at that revision. These notes mix historical reproduction and uninspected combinations. No current compiler run or exhaustive implementation audit was performed during migration. Recheck current source and minimal run/reject inputs before claiming a defect; close resolved investigations with evidence rather than weakening the specification.

## Acceptance Criteria

Select a target and explicit support scope before implementation; validate target layout/ABI, runtime and available execution modes. Do not infer iOS/mobile or other target support from local macOS ORC diagnostics.
