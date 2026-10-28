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
# Distinguish explicit argument retirement from via call results


## Contract and Evidence

Exact tests/fixtures/run/call_argument_via_lifetime.pw/.out at source baseline9665094d. Original2fbf760fcf220d332d7c7afc32f512e8799a73f4 added this test while ending temporary argument ownership at call completion. Spec03 call ownership and spec04 explicit-before-default evaluation distinguish callee completion from the enclosing print.

Each of the direct perform, via read and generic invoke paths passes a temporary named "explicit" and two default temporaries. After body, current expected output is default last, default first, explicit, explicit. One explicit is Resource.deinit and the other the outer print's returned String. A fault that delays only the explicit temporary until after outer print produces identical bytes in all three paths. Default cleanup order and worker survival are still observed. This is a source-backed indistinguishable-oracle gap, not a reproduced compiler miscleanup or new language rule. Independent contract-first batch0091 finding and parent source/golden/original-intent check support the finite scope.

## Guarantee and Scope

Retain useful explicit-before-default, default cleanup, body, returned value and worker-lifetime observations. Distinguish the explicit argument's destruction marker from the returned text in these three paths, so releasing it at call completion versus after the enclosing print cannot both pass. Preserve legitimate retained return ownership; do not demand release of values still owned by the result. Existing reference/deinit migration is separate and cannot be inferred complete from this audit.

Limit work to this fixture's direct/via/generic bridge with actually owned values and meaningful correct/late-release controls. No full argument-combination matrix, general closure lifetime rewrite, backend mechanism assertions, source semantic change or compiler bug repair is assigned.

## Completion

Use task-start TDD on fixed inputs and selected carrier. Show that the resulting oracle rejects the specific late-explicit-release order and accepts the specified call-completion order on the real relevant path; retain result validity, default order and worker cleanup checks. Independently review expected markers, actual producer-to-final-observer path and relevant controls/gates. Do not claim ordinary stdout proves all ARC safety. This repair is outside test-audit closure and is not its prerequisite; the audit executed no actual compiler/program/sanitizer and changed no fixture.
