---
id: com-zgk9
status: open
deps: []
links: []
created: 2026-10-13T01:29:04Z
type: task
priority: 3
assignee: Koji Murata
tags: [ownership, runtime, verification]
---
# Audit collection place and reentrant ownership coverage

Retained uninspected boundaries: place reads; Buffer and Dictionary/Set reentrant commit order; iteration-value ownership; inout calls through pub(get) arrays. Design: [collection and Buffer contracts](../design/collections-and-buffer.md), [ownership](../design/ownership-and-access.md).

Evidence scope: retained from meta agents/provisional.md at c539d7b96615a5c59c0165b0a5e3df90ec1f8dac; grammar-specific items additionally come from agents/grammar.md at that revision. These notes mix historical reproduction and uninspected combinations. No current compiler run or exhaustive implementation audit was performed during migration. Recheck current source and minimal run/reject inputs before claiming a defect; close resolved investigations with evidence rather than weakening the specification.

## Acceptance Criteria

Check minimal executable/reject cases against current specification, preserve independent owners and commit-before-user-code safety, and distinguish current evidence from whole-API/combination coverage.
