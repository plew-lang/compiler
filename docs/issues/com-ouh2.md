---
id: com-ouh2
status: open
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
