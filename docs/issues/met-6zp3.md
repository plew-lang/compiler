---
id: met-6zp3
status: open
deps: []
links: []
created: 2026-10-28T03:43:46Z
type: bug
priority: 2
assignee: Koji Murata
tags: [ownership, verification]
---
# Distinguish argument destruction from nested call results


## Contract and Evidence

Exact tests/fixtures/run/call_argument_via_lifetime.pw/.out at source baseline9665094d. Original2fbf760fcf220d332d7c7afc32f512e8799a73f4 added this test while ending temporary argument ownership at call completion. Spec03 call ownership and spec04 explicit-before-default evaluation distinguish callee completion from the enclosing print.

Each of the direct perform, via read and generic invoke paths passes a temporary named "explicit" and two default temporaries. After body, current expected output is default last, default first, explicit, explicit. One explicit is Resource.deinit and the other the outer print's returned String. A fault that delays only the explicit temporary until after outer print produces identical bytes in all three paths. Default cleanup order and worker survival are still observed. This is a source-backed indistinguishable-oracle gap, not a reproduced compiler miscleanup or new language rule. Independent contract-first batch0091 finding and parent source/golden/original-intent check support the finite scope.

## Guarantee and Scope

Retain useful explicit-before-default, default cleanup, body, returned value and worker-lifetime observations. Distinguish the explicit argument's destruction marker from the returned text in these three paths, so releasing it at call completion versus after the enclosing print cannot both pass. Preserve legitimate retained return ownership; do not demand release of values still owned by the result. Existing reference/deinit migration is separate and cannot be inferred complete from this audit.

Limit work to this fixture's direct/via/generic bridge with actually owned values and meaningful correct/late-release controls. No full argument-combination matrix, general closure lifetime rewrite, backend mechanism assertions, source semantic change or compiler bug repair is assigned.

## Completion

Use task-start TDD on fixed inputs and selected carrier. Show that the resulting oracle rejects the specific late-explicit-release order and accepts the specified call-completion order on the real relevant path; retain result validity, default order and worker cleanup checks. Independently review expected markers, actual producer-to-final-observer path and relevant controls/gates. Do not claim ordinary stdout proves all ARC safety. This repair is outside test-audit closure and is not its prerequisite; the audit executed no actual compiler/program/sanitizer and changed no fixture.

## Closure Callable Temporary Boundary

Batch0093 explicitly extends scope by exactly run/closure_temp_arg_arc.pw/.out, one additional fixture alongside the original via-lifetime pair. Nested g(c: temporary Cell v=2) returns I64=2 while that Cell deinit also prints2, so correct call-end release and faulty release after enclosing print both yield2/2/after-temp. The returned scalar owns no Cell; spec03:113 includes closure calls before the outer expression resumes. Original10b686d8 targeted anonymous temporary ownership homes and place arguments; preserve that leak regression, String temporary and retained keep/end/9 observations.

Use distinct destructor/result markers and meaningful correct/late-release controls for this closure callable path, preserving the original three direct/via/generic routes. Existing ordinary borrow/default tests do not cover the same closure entry; closure_param_borrow_arc has no destruction marker. No general closure rewrite, argument matrix, source semantic change, actual compiler fault or audit-time repair is asserted. Existing reference/deinit migrations and optional old statement-end prose remain separate. The second exact pair extends the finite scope; other exclusions and audit-nondependency remain unchanged.

## Scoped Test Audit Intake com-5azh

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-067-098.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 85.

Row85: Distinct markers/correct-vs-late controls must retain direct/via/generic/closure routes, defaults, worker/leak/retained result purposes. No new semantics/compiler fault or general closure rewrite; ref/deinit migration separate. Source selected call evaluation/default/passing ownership and actual common Mid child-scope cleanup must implement spec03 call-end temporary boundary. Two exact fixtures conflate explicit/closure dtor marker with enclosing returned print. Required admission: met-ucze, com-an0b.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
