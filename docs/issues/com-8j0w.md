---
id: com-8j0w
status: open
deps: []
links: []
created: 2026-10-13T01:29:04Z
type: task
priority: 3
assignee: Koji Murata
tags: [driver, frontend, runtime]
---
# Audit specified process entry and mutable associated storage

Compare Process/ExitCode, unit main, diverge functions and panic/exit integration against existing driver argument/exit APIs. Separately check mutable associated values. Generic stored associated values are prohibited in v1 and are not an implementation omission; computed associated functions differ. Design: [driver startup](../design/driver-and-execution.md), [runtime](../design/runtime.md).

Evidence scope: retained from meta agents/provisional.md at c539d7b96615a5c59c0165b0a5e3df90ec1f8dac; grammar-specific items additionally come from agents/grammar.md at that revision. These notes mix historical reproduction and uninspected combinations. No current compiler run or exhaustive implementation audit was performed during migration. Recheck current source and minimal run/reject inputs before claiming a defect; close resolved investigations with evidence rather than weakening the specification.

## Acceptance Criteria

Record current support and source requirements for each entry/storage case, close selected final consumers and startup/exit behavior, and preserve the v1 generic stored-assoc prohibition.
