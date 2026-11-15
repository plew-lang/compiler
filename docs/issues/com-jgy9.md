---
id: com-jgy9
status: open
deps: [com-1a6q]
links: []
created: 2026-11-15T06:28:19Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, mid, verification]
---
# Separate direct call descriptors from executable body requests

Extract the distinct descriptor and executable-body obligations currently combined by enqueueSelectedCallee for checked direct calls. Keep descriptor validation at existing lexical scope points, so local types and prior-call result recipes remain available.

## Design

Follow Frontend Handoffs section 8 and the inventory in com-1a6q. Preserve direct selection, constraint validation, body/signature identity, generated site keys, and pre-Access read/write descriptors required by freezeFinalAccesses. Keep registration and signature identity distinct from requesting executable preparation. Do not introduce a Frontend-to-Mid import or replace the full scanner in this prerequisite.

## Acceptance Criteria

Trace descriptor and executable request consumers through AOT, lazy, direct Frontend and generation entry points. Verify a reached direct call, a reached diverging callee, result-dependent callers, and nested inout getter/setter writeback, including missing-evidence and repeat-publication checks. Demonstrate via a scoped structural or executable test that descriptor construction can be used without requesting executable preparation. Preserve existing diagnostics and the resource limit. Obtain independent review and compare fixed-source output and performance.


Audit the current use of `monoWork.containsBody` as a signature readiness
shortcut. Keep signature-derived ownership/type closure available for
descriptor-only registrations, and preserve stable identity and signature
validation for both ends of inherited newtype adapters. Exercise a direct
generic function and an inherited adapter as controls.
