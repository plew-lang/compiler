---
id: com-1qbr
status: open
deps: []
links: []
created: 2026-11-02T21:37:24Z
type: bug
priority: 2
assignee: Koji Murata
tags: [tooling, verification]
---
# Complete failed ASan stage group cancellation after leader exit

## Contract and audit evidence

Only asan-schedule.run_stages failed cleanup56-74. It owns PGIDs created atlaunch23-27; exited stage leader does not prove no group members. Do not skip owned group TERM/KILL solely because leader exited; preserve failed result, finite grace and prepared binary invalidation.

From [com-6lza](com-6lza.md), [tooling intake](../../../evidence/compiler-failure-audit/tooling-owner-candidates.json), unit `asan-cancel-new`. Source-backed findings and saved controls are distinct; audit assignment is not product GREEN.

## Scenarios

- Dummy bounded same-group member with already-exited leader; leader exits after TERM but member survives until escalation; live watcher reap; nonexistent group; jobs1/separate parallel budgets/barrier/failure result; normal complete stage.

## Excluded

- No executed orphan claimed, arbitrary OS process-tree/global PID registry theorem, recollect every nested new session after arbitrary watcher death, or panic unwind/host recovery promise. process_watch normal tool-group deadline branch already unconditional KILL; outer run_gate top-level PGID is separate.

## Admission boundary and prerequisites

- type: standard ASan orchestration failure cleanup
- owners: ["com-9l3b", "com-604k final integration"]
- consumer: asan-gate→asan-schedule sibling stages; actual failed/cancelled gate must clean its owned stage groups. Not source rejection classifier or normal compiler correctness.



This is an admission proposal, not an installed dependency. Record actual dependencies after cycle and responsibility review.

## Completion

Follow task-start TDD. Inspect original scripts and owner contracts; obtain discriminating RED through the actual production path and preserve meaningful positive/negative controls. Repair the named boundary from producer to final consumer; do not weaken assertions, sanitizer checks, progress supervision or failure categories. Reconcile all listed scenarios, run affected gates and obtain independent review. No unapproved CLI/panic policy or all-suite rewrite is authorized.


