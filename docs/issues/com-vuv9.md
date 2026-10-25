---
id: com-vuv9
status: closed
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

## Outcome

Resolved by fixture-only commit 7e0648c1; production remains b6645ac1.
Creation c9da9548 explicitly describes the name-based rejection as a temporary
stack-overflow workaround pending lexical identity. Different declaration scopes
make nominal V and Dictionary's formal V distinct, not ambiguous. The positive
fixture keeps Dictionary[String,V] = [:] and consumes V.n = 42 through generic
insert/get; no source name ban or language change is introduced.

Fresh c50d2a04 passes generic-maintenance-1: native 4 and reject 2, exact
goldens/diagnostics and 258 unchanged inputs. Independent c2_classification_review
accepted the original purposes and canonical lexical/rigid contracts. No
production, API or verifier change. Raw compiler/tmp/phase3-internal-fixtures/generic-maintenance-1;
receipt meta/evidence/existing-feature-conformance/source-owner-facts/generic-fixture-maintenance.json.
Final complete G2 gates remain mandatory and uncertified.
