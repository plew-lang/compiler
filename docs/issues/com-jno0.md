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

## Closure Readiness Checks

Verify the existing Completion contract without closing this epic:

- Compare all nine required child contracts with their actual scoped evidence,
  current source/document identity and independent acceptance, not status alone.
- Confirm mandatory rule entry points and preserved decision grounds; distinguish
  discoverability from future operational effectiveness.
- Reconcile audit coverage, every required API input answer and finite finding
  owners. Preserve open repairs/source-oracle investigations and incomplete
  implementation-phase intake without treating them as completed or silently
  moving required audit questions out of scope.
- Independently review readiness and record required corrections, limits and
  the reasoned adoption. No product execution, new semantic rule, gate change or
  issue-state transition is part of this verification.

## Plan Review

Independent reviewer `/root/review_epic_scope_separation` reviewed the reorganization
against compiler `a36279a0` / meta `8a054734`. It confirmed whole-compiler scope,
complete audit partitioning and no implementation-milestone dependencies or lost
required work, and found no mandatory correction. The author accepts the
source/graph-backed conclusions. This is plan verification only; inventories,
audits and operating effectiveness remain unverified.

## Closure Readiness Result

Ready for closure under the existing audit-and-rules Completion contract.
This is a readiness assessment only: status remains open as requested.

[Readiness evidence](../../../evidence/llm-development-workflow/epic-readiness.json)
retains the original contract and exact observed document/child/evidence scope.
[Independent parent review](../../../evidence/llm-development-workflow/epic-readiness-review.json),
SHA256 5a58a8bef62e8f4c35f4e74b5fbe0e0bf86d9f332ef44755ed0c9a9b67d551d1,
accepts readiness at meta c3f26b28 / compiler 651f5404 with the documented
readiness-check addition. Required violations/concerns remaining: zero.

Adopt the grounded review, not child status/count alone: nine child contracts
have applicable independent evidence; API input questions490/490 are answered
with no required omission; all test-audit obligations retain intent/oracle/path
and bounded finding dispositions; common rules are mandatory and discoverable;
necessary proposal grounds survive at their canonical owner.

All320 API product owners and55 separate test follow-ups remain open. Inspected
source-oracle questions, implementation repairs and global phase intake retain
their owners and limits. They are not declared fixed or silently made part of
phase three. This readiness neither certifies future workflow effectiveness nor
GREEN, performance, implementation-phase completion, main or seed admission.
A later actual closure must retain these distinctions and record its outcome;
this verification performs no issue-state transition.
