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

Design-only prerequisite for the paused type-checking remediation. The [adopted physical design](../design/checked-body-storage.md) selects owner-local sealed payloads with private read-only strong handles and shared session term/proof IDs, compared against a live shared-store alternative. Restart reconciliation remains required; this is not an implemented or measured representation. Private arrays and snapshots already present do not implement the adopted owner boundary. Do not add another implementation layer instead of reconciling the existing producers/readers.

Acceptance: provide actual field/key/state/API and writer/reader permissions, failure isolation, acquisition/append/copy-retain/index cost, worked end-to-end examples and finite old-to-new removal map. Resolve open architecture decisions with the user where required. Obtain design review, then establish one fresh cumulative baseline before implementation. An interned handle, CoW snapshot or new IR is not prescribed by this ticket.

## Current Design Boundary

The supplement now specifies the source/instance keys, payload fields, Building/Succeeded/Failed publication, registered-signature queries, required/optional readers, synthetic plans, worked paths and finite migration families. Read-only comparison against the retained 2983c47f candidate identified all-owner semantic snapshots in preparedSemanticFacts; no compiler was run. Independent design comparison supports the owner-local direction without claiming shared stores inherently require whole-table CoW.

Before implementation, finish reconciliation of every migration family with the selected cumulative revision and its final consumers, then establish one fresh baseline. The independent comparison and corrective design review are complete; adoption falls within delegated internal decisions because it preserves the existing public/semantic contracts and replaceable reader boundary. Source/instance authority, failure isolation and missing-fact rejection are fixed; index shape, packing and allocation refinements follow the recorded correctness/cost measurements. No implementation gate or 5.7-second condition is waived.
