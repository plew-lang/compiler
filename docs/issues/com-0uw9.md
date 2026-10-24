---
id: com-0uw9
status: open
deps: []
links: []
created: 2026-10-24T19:53:11Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [validation, phase3, regression]
---
# Migrate array recording fixture to canonical source construction


## Boundary

Internal run fixture mid_record_array_storage.pw is a source record contrast,
not actual Mid execution. It starts with bare Comp, directly appends Int/Array
AST nodes and calls recordExpr, aborting134 on an Err unwrap. Same frozen
fixture fails with original performance baseline090240dd and measured6ddf8f75.
Their generated LLVM is byte-identical and runtime hashes match.

Identify the exact failed construction precondition, then migrate fixture
inputs to the canonical source path with authored owner/canonical Array. Retain
its original intent: parent expression newer than child, no preallocated parent
type row, saved parent fact and Array[E] child type equality. Do not swallow
Err, delete the assertions or weaken owner admission. If valid canonical input
still fails, split the actual implementation defect before widening this task.
The exact Err cause is not yet diagnosed; do not claim owner or Array absence
as a proven sole cause merely from the generic unwrap panic.

Independent b2 accepted this finite scope. Raw baseline/current controls and
llvm-identity.json are in compiler/tmp/perf-six-type-pools/normal-failure-controls.
Normal20261024T193137-test-625275 remains failed; required before G2b green,
separate from the successfully measured performance task.
