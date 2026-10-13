---
id: com-b1ro
status: open
deps: []
links: []
created: 2026-10-13T01:29:04Z
type: task
priority: 3
assignee: Koji Murata
tags: [frontend, ownership, mid]
---
# Audit unsupported closure environment shapes

The retained implementation note reports generic struct instantiations, function-typed captures and nested closures unsupported, rather than prohibited by source type kind. Known shapes should diagnose at declaration checking, shapes exposed by substitution at instantiation. Unique capture semantics are a separate specification constraint. Design: [Mid closure details](../design/mid-entry-audit.md#closures-and-synthetic-ownership-bodies).

Evidence scope: retained from meta agents/provisional.md at c539d7b96615a5c59c0165b0a5e3df90ec1f8dac; grammar-specific items additionally come from agents/grammar.md at that revision. These notes mix historical reproduction and uninspected combinations. No current compiler run or exhaustive implementation audit was performed during migration. Recheck current source and minimal run/reject inputs before claiming a defect; close resolved investigations with evidence rather than weakening the specification.

## Acceptance Criteria

Reproduce current scope, close selected capture type/environment/drop paths consistently, preserve declaration versus instance diagnostics and ordinary value ownership, and do not use AST backend fallback.
