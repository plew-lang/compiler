---
id: com-vuv9
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
# Replace obsolete parameter name rejection with identity regression


## Boundary and Exit

Reject fixture typeparam_name_collision is accepted by baseline090240dd and measured6ddf8f75, with identical LLVM. It encodes an old name-based parameter identity workaround: caller nominal V and Dictionary generic formal V share spelling but have distinct lexical identities. Verify the canonical spec and adopted identity contract, then migrate to a positive no-stack-overflow regression retaining Dictionary[String,V] construction and nominal/formal distinction. Do not reintroduce a name ban. If normative meaning is unclear, obtain a specification decision before changing the fixture.

All failures were reproduced against the same frozen latest source/std/fixtures. Raw controls: compiler/tmp/perf-six-type-pools/normal-failure-controls; durable milestone: meta/evidence/performance-six-seconds/type-pools-milestone.json. Independent b2 reviewed this finite scope. Normal20261024T193137-test-625275 remains failed. Completion requires preserving original intent and passing focused controls with a fresh compiler. This is a prerequisite of G2b, separate from the completed speed criterion; it does not expand the performance task.
