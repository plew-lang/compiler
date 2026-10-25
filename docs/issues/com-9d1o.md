---
id: com-9d1o
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
# Use a canonical destructor receiver in the publication fixture


## Boundary

Existing internal finalization_publication.pw compiles, then aborts134 with
"called unwrap on an Err Result" on original performance baseline090240dd and
measured6ddf8f75. Its embedded input defines its own same-named Index/IndexSet
traits; compiler synthetic indexing requires canonical Std/Core trait identity.
This is a likely stale fixture input, but the exact failing unwrap is not yet
diagnosed. Do not claim panic text alone proves the internal Err cause.

Identify the failed preparation request, use canonical indexing traits/valid
source inputs and preserve the original test intent: incremental publication of
access input provenance, earlier row identity and idempotent empty publication;
malformed destructor ABI rejection and repeat failure stability. Do not expose
private writers or weaken publisher verification to satisfy the fixture.
If a real implementation defect remains with valid canonical inputs, record
and repair the actual boundary separately before closing.

Controls compiler/tmp/perf-six-type-pools/normal-failure-controls/; durable final
performance milestone receipt will reference them. Independent b2 accepted
this finite diagnosis/fixture-maintenance scope. Normal20261024T193137-test-625275
remains failed; required before G2b green, not a new performance regression.

## Confirmed Failure and Fixture Repair

The staged native diagnostic publication-diagnostic-1 reaches both incremental
publications and idempotence assertions, then fails specifically at
`destruction-enqueue`: body receiver does not match its selected declaration.
The generic unwrap panic was not evidence of an Index failure. The actual
broken precondition is simpleTypeRef(Resource), which omits the selected nominal
owner now required by destructor body admission.

Use canonical Core Index/IndexSet source input in a minimal embedded standard graph,
select Resource explicitly rather than the first unique library type, and
construct the destruction receiver from its registered declaration identity.
Keep every publication/provenance/idempotence/malformed ABI/repeat-failure
assertion. Named require helpers retain diagnostics on unexpected preparation
failure; they do not accept errors. No production change is needed unless these
valid inputs expose a further compiler defect. Original intent:37df9c94 and
later c53a16b5/781253b2 move publication through explicit call/body APIs.

The first new canonical-input attempt used a filesystem stdRoot without its
required directory separator and fails during frontend preparation. Preserve
publication-1 as a failed test setup. Use the existing internal-test embedded
SourceResource pattern instead: minimal Lang/Core at canonical plew:std paths,
public primitive declarations and canonical Core indexing requirements, with the
probe in its own module. This keeps the test isolated from unrelated library
bodies while exercising actual module/trait identity.

## Outcome

Resolved by fixture commits 08cde1ea/b7b6ab4a; production remains b6645ac1.
Fresh c50d2a04 executes the complete publication-2 fixture with exit 0,
original ok golden and empty stderr; 248 recorded inputs remain unchanged.
Both incremental access/provenance publications, earlier row/callee identity,
empty publication idempotence, malformed destructor ABI rejection and repeated
failure stability execute. No implementation, publisher API or verifier changed.

Independent c2_classification_review checked original 37df9c94 intent,
c53a16b5/781253b2 API updates, all retained assertions, staged before failure,
canonical source graph and Resource identity, carrier/output/input hashes.
It certifies this finite internal maintenance. The failed publication-1 setup
is retained separately. Raw compiler/tmp/phase3-internal-fixtures/publication-2;
durable meta/evidence/existing-feature-conformance/source-owner-facts/publication-fixture-maintenance.json.
Final G2 complete gates remain mandatory and uncertified.
