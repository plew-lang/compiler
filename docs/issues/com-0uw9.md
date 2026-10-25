---
id: com-0uw9
status: closed
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

## Confirmed Precondition and Repair

Staged array-diagnostic-1 reproduces the old fixture's exact Err:
array construction requires the ambient Array declaration. The original
creation commit d27dc611 tested storage allocation before recording a parent
newer than its literal child; it was not a Mid execution or arbitrary bare-Comp
API contract. Preserve that purpose under the current owner-local storage.

The fixture now loads a minimal canonical Lang/Core graph, parses one authored
array initializer, asserts parent > child and an Unrecorded/zero parent fact
before any owner publication, then requests the real lexical body and reads its
immutable payload. Canonical Array identity, one child and child/element type
equality remain mandatory. Do not expose writer APIs, manually append incomplete
AST metadata or accept the old Err. No production implementation changes.

## Outcome

Resolved by fixture-only commit 4a2c3388; production remains b6645ac1.
Fresh c50d2a04 executes the complete array-1 fixture with exit 0 and original
ok golden; 248 recorded inputs are unchanged. Independent
body_receiver_completion_review inspected d27dc611 and the exact old Err,
confirmed that Unrecorded/zero parent precedes real lexical-body recording,
and checked canonical Array/child equality through the immutable payload.
It certifies this finite maintenance without exposing writers or changing
production, API, verifier or language semantics. The before diagnostic is kept.

Raw compiler/tmp/phase3-internal-fixtures/array-1; receipt
meta/evidence/existing-feature-conformance/source-owner-facts/array-record-fixture-maintenance.json.
Final complete G2 gates remain mandatory and uncertified.
