---
id: com-tn1m
status: open
deps: []
links: []
created: 2026-10-13T01:29:04Z
type: task
priority: 3
assignee: Koji Murata
tags: [mid, runtime, verification]
---
# Audit async expression and composite payload coverage

Retained uninspected combinations: await in for and nested expressions, method/generic async, composite Promise payloads, frame ownership and result transfer. Explicit borrow/inout parameters cannot carry synchronous borrows over suspension and must be rejected; this is a semantic restriction rather than missing support. Design: [async Mid details](../design/mid-entry-audit.md#async-and-machine-boundaries), [runtime](../design/runtime.md).

Evidence scope: retained from meta agents/provisional.md at c539d7b96615a5c59c0165b0a5e3df90ec1f8dac; grammar-specific items additionally come from agents/grammar.md at that revision. These notes mix historical reproduction and uninspected combinations. No current compiler run or exhaustive implementation audit was performed during migration. Recheck current source and minimal run/reject inputs before claiming a defect; close resolved investigations with evidence rather than weakening the specification.

## Acceptance Criteria

Establish each currently supported/rejected combination with source and minimal controls; close selected payload/frame/result consumers without weakening synchronous borrow restrictions or inventing cancellation semantics.
