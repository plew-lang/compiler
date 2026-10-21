---
id: met-z0ro
status: open
deps: []
links: []
created: 2026-10-21T11:01:35Z
type: task
priority: 1
assignee: Koji Murata
tags: [design, verification]
---
# Inventory specification and design conformance at the current implementation

## Scope and Method

Inventory adopted specification/design contracts against compiler
`ea5f751a8343febe8dfecfa3e88e48ccebdefb27`, spec
`16f2f13970dbe2789214b2206c48af3df21b68c8`, and pinned Syntax
`00f740e1178e5b992cfdd30ddaa5a0612ce27b43`. Implementation is read-only;
no compiler/test/performance execution or feature repair is part of this task.
The existing dirty binary is not an audit carrier.

Inspect each reference chapter's responsibilities and evidence limits, compare
representative producer-to-consumer paths with source and tests, and reconcile
existing issues before creating follow-ups. Classify observed semantic/design
mismatches separately from absent implementations, partially implemented contracts,
unverified coverage, and intentionally deferred features. Absence of one name or
one passing test is not proof of absence/completeness.

Completion: every reference domain has a bounded source-inspection record; major
evidenced gaps have owning issues and completion boundaries; uncertain cases stay
explicit; the resulting dependency/order recommendation does not start repairs or
expand the type-checking parent's scope automatically. This is a finite audit,
not a second hand-maintained issue/status index.

## Findings

In progress.
