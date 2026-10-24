---
id: com-072n
status: open
deps: []
links: []
created: 2026-10-24T20:09:24Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [validation, phase3, regression]
---
# Repair provided member receiver declaration identity


## Boundary and Exit

Valid run fixtures trait_assoc_fn and trait_blanket are rejected on baseline090240dd and measured6ddf8f75 with internal error: body receiver does not match its selected declaration, lines8 and24 respectively. Trace selected declaration through body receiver construction and final consumer. No-receiver associated provided functions and concrete trait-subject provided methods are distinct routes: split into finite child repairs before implementation if root causes differ. Preserve outputs42/15 and5/21/10/9, direct and generic dispatch, owner identity and the verifier. Do not assert an ABI root cause before diagnosis or weaken the mismatch check.

All failures were reproduced against the same frozen latest source/std/fixtures. Raw controls: compiler/tmp/perf-six-type-pools/normal-failure-controls; durable milestone: meta/evidence/performance-six-seconds/type-pools-milestone.json. Independent b2 reviewed this finite scope. Normal20261024T193137-test-625275 remains failed. Completion requires preserving original intent and passing focused controls with a fresh compiler. This is a prerequisite of G2b, separate from the completed speed criterion; it does not expand the performance task.
