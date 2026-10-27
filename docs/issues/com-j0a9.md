---
id: com-j0a9
status: open
deps: []
links: []
created: 2026-10-27T20:14:26Z
type: task
priority: 2
assignee: Koji Murata
tags: [runtime, verification]
---
# Reconcile Array swap removal with the Buffer-only API design

## Finite Contract Reconciliation

Selected tests/fixtures/run/array_surface_stepc.pw invokes Array.swapRemove and current std/Lang.pw exposes its forwarder. Design collections-and-buffer.md Collection Layer explicitly assigns swap removal to Buffer while Array ergonomic removal retains order. spec02 documents Buffer.swapRemove but does not make an arbitrary extra user method syntactically invalid. Original01a93b9b intentionally added this historical surface. Source-only audit9665094d/spec5bd65a5: arithmetic output is correct for supported implementation, no new policy/removal or current execution is certified.

Recover adopted API decision and compare exact Array forwarder/fixture versus Buffer counterpart; distinguish order-preserving Array removal tests from lower-level swap replacement. Resolve canonical documentation or implementation/test migration in its owning area, asking for surface judgment if existing decisions do not settle it. Do not remove the API or change spec merely to fit an audit report. Preserve shifted removeAt, last-element swap/count, boundary and value-ownership intent in authorized locations.

Completion: finite ruling with rationale and owned repairs/controls; actual repairs follow TDD and independent review. No all-standard-library reorganization, new collection semantics or broad Buffer rewrite. Evidence runtime-batch-0089.json. Unread source/driver obligations remain audit work.

