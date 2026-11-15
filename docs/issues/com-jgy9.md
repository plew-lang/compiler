---
id: com-jgy9
status: in_progress
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

## Implementation checkpoint

`prepareSelectedCalleeDescriptor` prepares the selected environment, callable
identity/signature and final descriptor. The compatibility caller requests the
body through `demandFinalBody`; inherited adapter targets enter the execution
queue before their wrappers. Signature preparation reads the signature's own
readiness. The fixed compiler plewc-phase3-backend-index-fixed accepted the
updated compiler source with both --check and compile-to-LLVM.

Before completion, exercise descriptor-only requests through a scoped control,
including signature-derived ownership closure, adapter ordering and any
secondary body demand produced during descriptor conversion. Compare native
candidate output and performance and obtain independent review.

The signature frontier now reads the Arena's first-ready signature order.
Ordinary and closure signature setters publish only the first readiness
transition, so descriptor-only signatures contribute type/ownership closure
without entering the executable worklist. Fixed-carrier compile-to-LLVM
succeeded for this slice. Native linking and focused controls are pending.
