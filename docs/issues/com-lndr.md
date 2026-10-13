---
id: com-lndr
status: open
deps: []
links: []
created: 2026-10-13T01:29:04Z
type: task
priority: 3
assignee: Koji Murata
tags: [diagnostics, frontend]
---
# Audit structured call failure diagnostic coverage

Check how call-resolution failures distinguish no candidate, visibility, label/type mismatch, ambiguity and view restrictions. Design: [diagnostics](../design/diagnostics.md), [name lookup](../design/name-lookup.md).

Evidence scope: retained from meta agents/provisional.md at c539d7b96615a5c59c0165b0a5e3df90ec1f8dac; grammar-specific items additionally come from agents/grammar.md at that revision. These notes mix historical reproduction and uninspected combinations. No current compiler run or exhaustive implementation audit was performed during migration. Recheck current source and minimal run/reject inputs before claiming a defect; close resolved investigations with evidence rather than weakening the specification.

## Acceptance Criteria

Produce focused failures and valid controls, preserve structured frontend causes/provenance through rendering, and avoid downstream name lookup as a substitute for missing evidence.
