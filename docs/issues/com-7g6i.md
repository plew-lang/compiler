---
id: com-7g6i
status: open
deps: []
links: []
created: 2026-10-13T01:29:04Z
type: task
priority: 3
assignee: Koji Murata
tags: [ownership, runtime]
---
# Investigate stack use when destroying deep owned value trees

Deep recursive owned-value destruction has an unmeasured stack-use boundary. This differs from shared-reference cycle reporting/reclamation in com-2z5l. Design: [runtime](../design/runtime.md).

Evidence scope: retained from meta agents/provisional.md at c539d7b96615a5c59c0165b0a5e3df90ec1f8dac; grammar-specific items additionally come from agents/grammar.md at that revision. These notes mix historical reproduction and uninspected combinations. No current compiler run or exhaustive implementation audit was performed during migration. Recheck current source and minimal run/reject inputs before claiming a defect; close resolved investigations with evidence rather than weakening the specification.

## Acceptance Criteria

Measure representative depth and destruction order, identify any actual resource limitation, and document or implement a semantics-preserving remedy without asserting an unmeasured stack defect.
