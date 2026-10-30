---
id: com-jno0
status: open
deps: [com-5by1, com-ouh2, com-e713, com-8iys, com-5zvv, com-tqzw, com-3p7m, com-am6u, com-mmk9]
links: []
created: 2026-10-26T12:48:12Z
type: epic
priority: 1
assignee: Koji Murata
tags: [verification, tooling]
---
# Audit compiler API inputs and tests and establish common development rules

## Purpose and Scope

Own the user's cross-compiler API-input audit, test-validity/coverage audit and
common development principles. This epic is independent of implementation
milestones: it neither owns their fixes nor requires their completion.

- API audit: find values/capabilities passed to functions or struct constructors
  beyond their responsibility, across the production compiler.
- Test audit: check actual assertions, expectation grounds, exercised paths,
  registration and missing controls across the complete existing corpus.
- Operating rules: intended-RED TDD from a task-wide scenario list, guarantees in
  task bodies with action-oriented titles, independent evidence-based review.

[Architecture](../design/architecture.md), [compiler state](../design/compiler-state.md),
[Mid](../design/mid.md), [ownership](../design/ownership-and-access.md) and
[driver](../design/driver-and-execution.md) assign distinct API responsibilities.
The API question therefore spans the whole compiler, not only source typing.
Checking algorithm correctness, implementing discovered repairs/new features,
formal performance admission and release/seed promotion are outside this epic.

## Work Routing

| Responsibility | Owner |
|---|---|
| Common operational rules | [com-5by1](com-5by1.md) |
| Whole-compiler API-input inventory | [com-am6u](com-am6u.md) |
| Whole-compiler API-input/capability audit | [com-mmk9](com-mmk9.md) |
| Actual test discovery and audit partition | [com-ouh2](com-ouh2.md) |
| All frontend test assertions | [com-e713](com-e713.md) |
| Mid/backend/ownership/runtime assertions | [com-8iys](com-8iys.md) |
| Driver/gen/deps/tooling/harness assertions | [com-5zvv](com-5zvv.md) |
| Corpus reconciliation and finding ownership | [com-tqzw](com-tqzw.md) |
| Durable rules and proposal cleanup | [com-3p7m](com-3p7m.md) |

Inventories define finite batches before audit execution; use tk for state and
actual prerequisites. No separate mutable status index is kept here.

## Completion

Required rules are installed and independently reviewed. Inventories and audits
meet their substantive task-specific completion conditions; confirmed findings
have finite repair owners. In particular, com-mmk9 must answer all required API
input-authority questions, including mixed components. Assigning an unanswered
question to another issue does not complete that audit or this epic. API repairs
remain separate and are not prerequisites. Audit completion does not mean the
findings are repaired or that unknown bugs are absent. A fresh-context check confirms the rules are discoverable; it
cannot prove their future effectiveness. User per-task paperwork does not grow.

No implementation-phase task is a child, dependency or linked issue of this epic.
Audits may report findings to their appropriate owners, but implementation
completion and its gates do not become epic prerequisites. A mandatory issue
must still be fixed before its own affected implementation scope is admitted.
No guard platform, new tool/DSL, weakened gate or changed language semantics is
part of this plan.

## Plan Review

Independent reviewer `/root/review_epic_scope_separation` reviewed the reorganization
against compiler `a36279a0` / meta `8a054734`. It confirmed whole-compiler scope,
complete audit partitioning and no implementation-milestone dependencies or lost
required work, and found no mandatory correction. The author accepts the
source/graph-backed conclusions. This is plan verification only; inventories,
audits and operating effectiveness remain unverified.
