---
id: com-2p9p
status: open
deps: []
links: []
created: 2026-10-13T01:29:04Z
type: task
priority: 3
assignee: Koji Murata
tags: [frontend, verification]
---
# Audit shared grammar closure across arena and value AST paths

The direct compiler arena and macro value-AST parser paths must share grammar decisions. Design: [Syntax](../design/syntax.md). This retained boundary is not evidence that either consumer already covers every construct; discarded Plew.g4 status does not describe the current parser.

Evidence scope: retained from meta agents/provisional.md at c539d7b96615a5c59c0165b0a5e3df90ec1f8dac; grammar-specific items additionally come from agents/grammar.md at that revision. These notes mix historical reproduction and uninspected combinations. No current compiler run or exhaustive implementation audit was performed during migration. Recheck current source and minimal run/reject inputs before claiming a defect; close resolved investigations with evidence rather than weakening the specification.

## Acceptance Criteria

Inspect shared parse producers and both consumer representations, compare supported syntax/errors with paired fixtures, and close divergences without a second grammar authority.
