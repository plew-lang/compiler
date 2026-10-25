---
id: com-cev5
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
# Migrate trait member owner fixture to selected source proofs


## Boundary and Exit

Internal run fixture trait_member_owner_identity calls removed traitMemberRetInfo at line26 and fails with no matching method for this argument list on baseline090240dd and measured6ddf8f75. Migrate the fixture to current selected-source/proof APIs without restoring the obsolete helper. Preserve same-named members owned by distinct traits, private provided member nonleakage, and invalid owner sentinel controls; confirm that checks observe the final consumer.

All failures were reproduced against the same frozen latest source/std/fixtures. Raw controls: compiler/tmp/perf-six-type-pools/normal-failure-controls; durable milestone: meta/evidence/performance-six-seconds/type-pools-milestone.json. Independent b2 reviewed this finite scope. Normal20261024T193137-test-625275 remains failed. Completion requires preserving original intent and passing focused controls with a fresh compiler. This is a prerequisite of G2b, separate from the completed speed criterion; it does not expand the performance task.

## Outcome

Resolved by fixture-only commit 137c92d7. A real embedded module graph replaces
the removed traitMemberRetInfo calls and incomplete manual declaration headers.
Both same-spelled Read owners produce distinct selected Requirement identities,
canonical I64/String results in immutable expression/operation records and the
preparedBodyExpression consumer. The same-owner private Provided call succeeds;
another trait and another module both refuse it and publish no successful facts.
Canonical existential owner and invalid-owner sentinel controls remain.

Fresh c50d2a04 completes member-owner-1 with exit 0, original five-line golden
and 248 unchanged inputs. Independent body_receiver_completion_review checked
095ad407, cea93a49 and bd7e727f and accepted preservation through the real source
consumer rather than a boolean-only replacement. No production, API, verifier
or language change. Raw compiler/tmp/phase3-internal-fixtures/member-owner-1;
receipt meta/evidence/existing-feature-conformance/source-owner-facts/trait-owner-fixture-maintenance.json.
Final complete G2 gates remain mandatory and uncertified.
