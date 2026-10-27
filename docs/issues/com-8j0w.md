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

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Mixed: split current subset**.

Currently admitted process/main/exit and non-generic storage controls are com-cgdk; initializer ordering is com-fkxl. Absent new Process/ExitCode API forms and generic stored assoc are not added; specified generic stored-assoc rejection remains.

## Test Audit Evidence

Scoped audit at compiler test/source baseline `9665094d` is saved in
[review dispositions](../../../evidence/test-audit/scoped-reviews/disposition.json).
Frontend F6 classifies argCount/argAt argument tests as old admitted-subset
regressions, not current Process.args/ExitCode API conformance. New API migration
remains in this parent; it is not a fixture-only expectation correction or an
extra requirement for the admitted-subset child com-cgdk.
