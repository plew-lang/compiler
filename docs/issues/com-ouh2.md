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

## Question and Actions

Determine what tests actually run and what each assertion observes. Read
[tests layout](../../tests/README.md), [verification](../design/verification.md),
meta agents/test-inventory.md and standard validate profiles. Begin with
tests/harness/test.sh, test-gen.sh, test-deps.sh and asan-gate.sh; locate the
actual filenames and trace all explicit script invocations and generated inputs.
Include tooling and manual diagnostics; do not infer registration from filenames.

Produce a reproducible inventory of fixture/project, companions, assertion,
runner/caller, mode, instrumentation and automatic/manual status. Include missing
companions, unregistered/unknown files and dynamically generated cases. Freeze
the inventory revision and distinguish source-file counts from assertions.

Assign every assertion to one primary audit owner: com-lbnc for contracts
needed by phase three regardless of directory, com-e713 for remaining
frontend language behavior, com-8iys for remaining Mid/backend/ownership/
runtime behavior, com-5zvv for remaining driver/gen/deps/tooling/harness
behavior. Record secondary relationships without double-counting coverage.
The partition follows actual assertions, not prefixes. Assign a newly observed
assertion before claiming completeness; manual tests are not standard-gate passes.

Size finite audit batches and their contract areas for these owners. If a domain
is too large for one bounded task, create/arrange bounded children under existing
planning/approval rules before its audit starts. Store generated inventory data
through the existing evidence conventions; do not create a parallel hand-maintained
file/status index or a general new workflow platform.

## Exit and Evidence

Known entry points and profile discovery reconcile to the generated inventory;
every discovered item has a scope/owner or an explicitly owned investigation.
Independent review checks sampling of registration and omitted/generated paths.
This closes discovery/routing only, not semantic test validity, new tests or fixes.
