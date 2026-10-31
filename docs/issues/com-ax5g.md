---
id: com-ax5g
status: open
deps: [com-mmk9, com-tqzw]
links: []
created: 2026-10-31T05:40:51Z
type: task
priority: 1
assignee: Koji Murata
parent: com-604k
tags: [design, verification, tooling]
---
# Route audited findings into implementation scopes and admission dependencies

## Contract and Inputs

Preserve every adopted audit finding through implementation-scope classification,
its existing finite repair/investigation owner and actual admission dependencies.
This is bounded assignment work under com-604k, not another compiler audit or an
anonymous implementation bucket. The completed com-jno0 audit must not be reopened
merely because its separately owned repairs remain unfinished.

Use the canonical [API conclusions](../../../evidence/compiler-api-audit/whole-audit-reconciliation.json),
[API answer index](../../../evidence/compiler-api-audit/capability-resolution-index.json),
and [test dispositions](../../../evidence/test-audit/scoped-reviews/disposition.json).
The API audit has320 unique open product owners and optional/mixed subsets;
the test dispositions contain98 rows with55 separate subjects plus qualified
existing/historical/unsupported/duplicate roles. These sets overlap and are not
375 independent bugs. Read their exact source/provenance/scope, not titles alone.
Use com-esri as a historical classification input, not as a current classification
of findings added later. Current inclusion authority is com-604k and its contracts.

## Actions and Guarantee

1. Pin the current finding/owner sets and reconcile every finding or scoped subset
   to its existing owner, relevant design/spec contract and actual affected domain.
   Reuse accepted evidence only for matching identity/scope; review only changed or
   missing portions. Do not repeat the completed whole audits.
2. Classify current-feature conformance work versus unsupported/new feature,
   optional improvement and unresolved source-contract decision with grounds.
   Do not silently settle semantics, change expectations or label uncertain cases
   unsupported. Required classification questions need finite evidence/decision
   owners and blocking edges; they cannot disappear through reassignment.
3. Map applicable work to actual existing implementation areas, including phase3
   only where its contracts apply. Use com-2hx2/com-sn9w/com-lbnc/com-x7r3 for that
   intake; preserve independent phase4/backend/runtime/driver/tooling scopes.
   Neither all findings nor all non-phase3 findings are automatically mandatory
   phase3/phase4 work. Do not make phase3 wait for unrelated global routing.
4. Reuse existing finite repair owners; merge duplicate ownership only with an
   explicit redirect preserving findings. Keep original audit artifacts immutable.
   Scope titles remain actionable; bodies name producer, retained decision/fact,
   final consumer, removed competing path and meaningful intended-RED controls.
5. Install actual required repair/investigation prerequisites on the affected
   area/admission owner and com-604k as appropriate. A closed routing/audit task
   alone must never allow an affected area, G1 or integration to pass while its
   required repair is open. Do not indiscriminately add all320 owners as direct
   integration prerequisites or change existing gates/performance policy.

## Working Bound and Scenarios

Target1-2 active human working days per executable assignment unit. Before
traversal exceeds this, partition the pinned subjects into finite domain children
with exact finding membership, actual questions/actions, outputs and dependencies.
Keep this task blocked on required classification children; no partly answered
routing question may be counted complete because another issue owns it.

Check all subjects exactly once with secondary relationships retained, mixed
API subsets, optional and unsupported lanes, source-oracle questions, duplicate
redirects, multi-domain producers/consumers, old closed evidence versus open repair,
and same-input evidence reuse. Check the real graph for cycles and ready/blocked
behavior, including that required repairs block their real admission owner.

## Completion and Excluded Work

Every pinned finding has a supported classification, finite receiving scope/owner
and justified dependency or explicit outside/optional disposition. Required scope
questions are answered; implementation repairs can remain open because actual
admission dependencies retain them. Record a bounded immutable reconciliation and
real tk graph diff, not a second mutable status list. Independently review exact
coverage, scope, task granularity and graph before closure. Preserve closed valid
work and existing guards; stop for unapproved semantic/architecture decisions.

No product source/std/test/expectation/binary/runner edit, actual behavior repair,
new compiler feature, full gate execution, main/seed/carrier promotion or future
workflow-efficacy claim belongs to this assignment task. Product repairs follow
normal TDD/review and affected-scope gates in their own tasks.
