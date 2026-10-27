---
id: com-ouh2
status: closed
deps: []
links: []
created: 2026-10-26T12:48:12Z
type: task
priority: 1
assignee: Koji Murata
parent: com-jno0
tags: [verification, tooling]
---
# Inventory actual test discovery assertions and audit ownership

## Actions

Enumerate actual tests/assertions from tests/harness/test.sh, test-gen.sh,
test-deps.sh, asan-gate.sh and their explicit calls/generated inputs. Include
manual/unregistered checks, companions, modes, instrumentation and unknown files.
Read tests/README.md and verification design; filenames do not prove registration.

Pin the inventory revision and distinguish input-file counts from assertions.
Assign each assertion to exactly one primary audit owner by its contract:
com-e713 for frontend language checking, com-8iys for Mid/backend/ownership/
runtime behavior, com-5zvv for driver/gen/deps/tooling/harness behavior. Preserve
secondary relationships without counting an assertion twice. No implementation
phase defines the partition or needs to finish before inventory/audit can run.

Size finite batches; split oversized domains before audit execution. Use existing
evidence conventions, not another hand-maintained file/status index.

## Completion

Known discovery entries reconcile to the reproducible inventory. Every assertion
or unknown item has an owner/scope, with independent review of registration and
omitted/generated paths. This completes discovery/routing, not semantic validity,
repairs or an implementation milestone.

## Discovery and Routing Completion

Closed as investigated, source/test baseline `9665094d`, using the
[finite plan](../../../evidence/test-audit/audit-plan.json) and
[scope/limitations](../../../evidence/test-audit/README.md#finite-routing-and-current-audit-boundary).
All 5,790 files reconcile into 5,065 obligation bundles / 143 bounded batches,
including 319 exact support/unknown intake obligations. Known checker/native
helpers, generated locators and 51 local import/patch sites have actual owners.
No test, expectation or compiler was changed and no actual compiler was run.

Independent review review_audit_inventory_partition reproduced the generated
plan in memory and checked all hashes and membership. Fixed its findings:
execution-result routing no longer uses deinit/await keyword heuristics; unknown
files enter real batches; associated helper lines count against bounds;
DiagnosticValues.err follows its consumer. Re-review found no required correction
and accepted the discovery/routing completion boundary. Transitive Plew imports,
conditional generated paths, mixed-contract assertions and expectation validity
remain explicit domain-audit work, not a claim of semantic completion.

Partial domain review evidence and separately owned findings are retained in
[scoped reviews](../../../evidence/test-audit/scoped-reviews/README.md).
The three domain audits and final reconciliation remain unfinished.
