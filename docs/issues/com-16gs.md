---
id: com-16gs
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
# Verify canonical associated bounds in lowering fixture


## Boundary and Exit

Internal run fixture syntax_lower_associated_type_bounds aborts134 with assertion failed on both baseline090240dd and measured6ddf8f75; emitted LLVM is byte-identical. Identify the exact assertion and direct/legacy lowering path before changing expectations. Compare the adopted associated projection and lexical ParamId contracts. Preserve bound count/order, trait owner, canonical Self/ParamId predicates, positional arguments, offsets, and absence of monomorphization side effects. Do not assume the fixture is wrong from an undifferentiated assertion panic; split a valid-source implementation defect if found.

All failures were reproduced against the same frozen latest source/std/fixtures. Raw controls: compiler/tmp/perf-six-type-pools/normal-failure-controls; durable milestone: meta/evidence/performance-six-seconds/type-pools-milestone.json. Independent b2 reviewed this finite scope. Normal20261024T193137-test-625275 remains failed. Completion requires preserving original intent and passing focused controls with a fresh compiler. This is a prerequisite of G2b, separate from the completed speed criterion; it does not expand the performance task.
