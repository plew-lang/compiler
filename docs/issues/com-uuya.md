---
id: com-uuya
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
# Refresh rigid generic argument rejection diagnostics


## Boundary and Exit

Reject fixtures generic_assumed_bound_member_argument_mismatch and generic_associated_self_argument both still reject exit1 on baseline090240dd and measured6ddf8f75 with identical type mismatch: no trait member matches these arguments. Verify the original rigid T/Self incompatibility and selected requirement/common applicability contracts first. Then update only stale detailed diagnostic expectations, preserving inputs and semantic rejection assertions. Do not weaken to an arbitrary error substring or change a legitimate rejection into acceptance.

All failures were reproduced against the same frozen latest source/std/fixtures. Raw controls: compiler/tmp/perf-six-type-pools/normal-failure-controls; durable milestone: meta/evidence/performance-six-seconds/type-pools-milestone.json. Independent b2 reviewed this finite scope. Normal20261024T193137-test-625275 remains failed. Completion requires preserving original intent and passing focused controls with a fresh compiler. This is a prerequisite of G2b, separate from the completed speed criterion; it does not expand the performance task.

## Outcome

Resolved by fixture-only commit 7e0648c1; production remains b6645ac1.
The original inputs from 07931963 and 0398004b are unchanged. Both still
reject I64 as rigid T/Self, following the specification's abstract generic body
contract. Only the exact detailed diagnostic changed to type mismatch: no trait
member matches these arguments. Neither arbitrary-error matching nor acceptance
replaces the rejection.

Fresh c50d2a04 passes generic-maintenance-1: native 4 and reject 2, exact
goldens/diagnostics and 258 unchanged inputs. Independent c2_classification_review
accepted the original purposes and canonical lexical/rigid contracts. No
production, API or verifier change. Raw compiler/tmp/phase3-internal-fixtures/generic-maintenance-1;
receipt meta/evidence/existing-feature-conformance/source-owner-facts/generic-fixture-maintenance.json.
Final complete G2 gates remain mandatory and uncertified.
