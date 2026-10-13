---
id: met-j9mv
status: open
deps: []
links: []
created: 2026-10-13T01:40:08Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, architecture]
---
# Decide checked-body storage and implementation restart boundary

Design-only prerequisite for the paused type-checking remediation. Choose owner-local immutable payload versus shared immutable store with a prepared handle using the concrete design/restart checklist in [Checked-body Storage](../design/checked-body-storage.md). Private arrays and snapshots already present do not settle the physical ownership choice. Do not add another implementation layer before this decision.

Acceptance: provide actual field/key/state/API and writer/reader permissions, failure isolation, acquisition/append/copy-retain/index cost, worked end-to-end examples and finite old-to-new removal map. Resolve open architecture decisions with the user where required. Obtain design review, then establish one fresh cumulative baseline before implementation. An interned handle, CoW snapshot or new IR is not prescribed by this ticket.
