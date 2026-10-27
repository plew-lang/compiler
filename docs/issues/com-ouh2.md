---
id: com-ouh2
status: in_progress
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

## Investigation Scenarios

Pinned starting source: compiler `9665094d`, meta `24eae464`. Existing dirty
`bin/plewc` and Python caches are not compiler candidates or audited inputs.
This is read-only source discovery; no compiler execution or semantic repair.

Reconcile (1) normal glob roots and companions, (2) explicit and transitive
checker calls, (3) gen/generated scratch inputs and genast's explicit registration,
(4) deps' generated packages and named checks, (5) sanitizer A/B/C/D/E and raw
control, (6) manual/unregistered internal/native checks and their support files,
(7) unknown/orphan files and conditional paths, and (8) assertion ownership and
finite audit batches. Source locators are not independently validated assertions
or dynamic test counts. Unknown dispatch remains explicit until traced.

## Discovery Checkpoint

[Initial snapshot and limits](../../../evidence/test-audit/README.md) records
5,790 files, 70 checker scripts, 2,864 normal/gen fixture entries, 648 check-site
locators and 80 raw compiler ownership inputs. The source-only generator pins
input hashes and its own identity. These are not executed assertion counts.
Absolute module references are unresolved strings, not compiler-import identity.

Independent review `review_test_discovery_checkpoint` matched the initial
source hashes/globs/manifest and memory-only regeneration. It identified an
incorrect compiler-import classification; renamed and widened the lexical
extraction, preserving unresolved ownership. The expanded runner assertions,
manual/dynamic edges, primary audit owners and finite batches remain unfinished;
this task stays in_progress. The README records diagnostic-companion gaps and a
contradictory manual-probe exit instruction for later owned audit, without
changing tests or certifying defects from current output.

The reviewer additionally caught omitted root `/` module references and ambiguous
owner wording. Both were fixed; the final extraction records 422 unresolved
absolute-import entries. Its limited re-review reproduced the JSON exactly in
memory and found no remaining required correction for this initial checkpoint.
This acceptance is not completion review of the full inventory/audit.
