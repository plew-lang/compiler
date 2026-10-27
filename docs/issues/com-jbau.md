---
id: com-jbau
status: open
deps: []
links: []
created: 2026-10-27T20:24:53Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, ownership, verification]
---
# Separate static-alias rejection from dynamic shared-access test guarantees

## Finite Analysis-Frontier Question

Source-only frontend audit at9665094d/spec5bd65a5. Initial nine exact panic roots: borrow_shared_argument, borrow_shared_receiver, borrow_shared_reversed, overlapping_inout_container, overlapping_inout_mixed, overlapping_inout_receiver_container, overlapping_inout_ref, receiver_shared_field_overlap, receiver_shared_unique_overlap. These preserve current dynamic-tier regressions: different spelling roots/Ref aliases reach the same cell. They were not executed in audit.

spec03 and design ownership-and-access permit early source rejection for statically established shared-cell identity/projection overlap and require runtime checks when identity remains unknown. An immutable alias=owner or owner.asRef() may be provable with stronger analysis; the specification does not promise these exact sources must always compile. Current Verify/Ops classifyInoutPair compares normalized expression syntax; different roots route to runtime rather than tracing alias assignment. Backend compares evaluated pointers. This is a useful current-path test, not an evidenced current compiler defect or a requirement to forbid future static proof.

## Deliverables and Completion

Recover original nine current-path purposes, classify existing direct-static rejection/distinct-cell/read-read controls, and state the current proof frontier explicitly. Plan finite runtime-dependent alias controls that cannot be rejected merely by proving a fixed source alias, with deterministic runner/setup and corresponding legal nonalias contrast. Verify the actual selected request/worker path and discriminator before claiming dynamic coverage. Existing exact sources may remain implementation-lane regressions if labelled appropriately; do not weaken the runner to accept arbitrary compile rejection OR runtime panic, silently change public semantics, or require implementing general alias propagation.

Close investigation with exact qualification/control decisions and concrete owned corrections where required. Any later implementation follows TDD/scoped independent review; shared old reference/panic migration owners remain separate. No all-ownership audit or new lifetime/optimization feature. Evidence frontend-batch-0002.json, runtime outcome records and real Verify/Ops/Backend source paths under meta/evidence/test-audit/scoped-reviews. Unread admission obligations remain audit work.


## Explicit Eight-Root Ambient Extension

The remaining panic source-admission audit adds exactly ambient_capture,
ambient_cell, ambient_combined, ambient_dispatch, ambient_drop,
ambient_enum_capture, ambient_receiver_write, and ambient_writeback_drop.
The current17-root scope covers both different Ref roots and callback/global/
destructor effects whose storage relation may become statically established.
Do not promise unconditional source acceptance merely because the present
implementation keeps an erased-target/dynamic fallback. Preserve each actual
current regression and distinguish proven static source overlap from genuinely
runtime-dependent alias/effect cases.

com-l92e retains the separate combined/drop/writeback-drop final destructor
path-attribution question; this extension neither resolves that attribution nor
requires implementing a general effect/alias optimizer. Root syntax/deinit and
ordinary panic API migration remain separately owned. The outcome and source
admission obligations are not the same assertion and are not double counted.
