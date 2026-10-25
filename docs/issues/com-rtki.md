---
id: com-rtki
status: closed
deps: []
links: []
created: 2026-10-24T19:45:10Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [validation, phase3, regression]
---
# Update legacy binder view fixture to canonical ParamId identity


## Boundary

Existing internal run fixture ground_environment_views.pw fails at
"legacy parameter view lost" on both original performance baseline090240dd and
measured6ddf8f75. It expects a same-spelled leaf without ParamId to bind to an
explicit ParamId11 binder. Canonical substitution preserves such legacy leaves;
source-name recovery would violate the adopted type identity contract.

Update only the obsolete internal expectation to require the legacy leaf remain
unchanged. Retain real ParamId/view composition, foreign binder isolation,
records/nested/projection children, simultaneous substitution and unchanged-input
contrasts. Run the whole fixture after repair, since earlier panic masks later
checks. No user language behavior change is authorized by this task.

Both control executions exit134 with identical panic, inputs unchanged.
Raw controls compiler/tmp/perf-six-type-pools/normal-failure-controls/; final
durable milestone receipt will reference them. Independent b2 reviewed scope.
Normal20261024T193137-test-625275 stays failed; required before G2b green.

## Outcome

Resolved by fixture-only commit 68e7274b. The identity contract in Types and
Evidence requires a declared ParamId; a same-spelled leaf without it remains
unchanged, including its views. Only that obsolete expectation changed.
The original view composition, nested/record/projection, foreign binder,
Self/Item bridge, unchanged-subtree and simultaneous-substitution assertions,
and the existing golden, remain intact. No implementation/API/verifier changed.

Fresh carrier c50d2a04 (production b6645ac1) executes the whole fixture with exit 0
and exact golden; 248 recorded inputs are unchanged. Independent
body_receiver_completion_review inspected the original fixture at 06fbe78f,
the simultaneous-substitution addition at 523a466e, the diff and all input hashes,
and certifies this finite maintenance. Raw record:
compiler/tmp/phase3-internal-fixtures/binder-1. Durable receipt:
meta/evidence/existing-feature-conformance/source-owner-facts/binder-view-fixture-maintenance.json.
The failed normal run remains failed; G2 must rerun the integrated candidate.
