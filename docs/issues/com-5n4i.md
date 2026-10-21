---
id: com-5n4i
status: open
deps: []
links: []
created: 2026-10-13T01:29:04Z
type: task
priority: 3
assignee: Koji Murata
tags: [ownership, frontend, mid]
---
# Audit remaining unique-result and region capability boundaries

Retained boundaries: unique values themselves as block/if/match give results (historical tests/fixtures/reject/give_unique.pw), escaping borrow, region inference and allowUnique. Ref or copyable payload results are distinct. Ordinary collection storage of unique values requires closing the applicable ownership/generic prerequisites first. These implementation limits must not be promoted into specification prohibitions. Design: [ownership](../design/ownership-and-access.md), [Mid](../design/mid.md).

Evidence scope: retained from meta agents/provisional.md at c539d7b96615a5c59c0165b0a5e3df90ec1f8dac; grammar-specific items additionally come from agents/grammar.md at that revision. These notes mix historical reproduction and uninspected combinations. No current compiler run or exhaustive implementation audit was performed during migration. Recheck current source and minimal run/reject inputs before claiming a defect; close resolved investigations with evidence rather than weakening the specification.

## Acceptance Criteria

Check each current limitation against spec and minimal inputs, distinguish extensions requiring decisions from already specified behavior, and retain producer-to-cleanup implementation obligations for selected work.
