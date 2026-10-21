---
id: met-31n6
status: open
deps: []
links: []
created: 2026-10-21T10:42:55Z
type: chore
priority: 2
assignee: Koji Murata
tags: [documentation, design]
---
# Audit decision retention and remove superseded discussion documents

## Scope and Completion

Audit the adopted outcomes, rationale, rejected alternatives/reconsideration
conditions and outstanding work before removing superseded discussion documents.
Source input: meta `9979e825` and pre-consolidation versions in its Git ancestry;
reference input: compiler `c71cc68d` and spec `3b73ea3`. Three independent reviewers
cover sharing/runtime, unique generics, and the remaining discussion families.
Current implementation and compiler/performance execution are outside this audit.

- Map retained decisions to specification, design/decision notes and local issues.
- Repair evidenced omissions without reviving superseded proposals or adding policy.
- Remove redundant discussions and redirect live navigation to the canonical homes.
- Preserve historical evidence and its revision/scope rather than presenting it as
  current implementation certification.
- Check links, anchors, issue metadata and diffs; preserve candidate/carrier and
  unrelated binary/cache changes. Keep this issue after scoped completion.

## Result

In progress. Removal follows the independent reviews and required corrections.
