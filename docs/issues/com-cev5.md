---
id: com-cev5
status: open
deps: []
links: []
created: 2026-10-24T20:09:24Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [validation, phase3, regression]
---
# Migrate trait member owner fixture to selected source proofs


## Boundary and Exit

Internal run fixture trait_member_owner_identity calls removed traitMemberRetInfo at line26 and fails with no matching method for this argument list on baseline090240dd and measured6ddf8f75. Migrate the fixture to current selected-source/proof APIs without restoring the obsolete helper. Preserve same-named members owned by distinct traits, private provided member nonleakage, and invalid owner sentinel controls; confirm that checks observe the final consumer.

All failures were reproduced against the same frozen latest source/std/fixtures. Raw controls: compiler/tmp/perf-six-type-pools/normal-failure-controls; durable milestone: meta/evidence/performance-six-seconds/type-pools-milestone.json. Independent b2 reviewed this finite scope. Normal20261024T193137-test-625275 remains failed. Completion requires preserving original intent and passing focused controls with a fresh compiler. This is a prerequisite of G2b, separate from the completed speed criterion; it does not expand the performance task.
