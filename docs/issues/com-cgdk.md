---
id: com-cgdk
status: open
deps: []
links: []
created: 2026-10-21T15:16:01Z
type: task
priority: 2
assignee: Koji Murata
parent: com-8j0w
tags: [design, verification]
---
# Audit admitted process entry exit and associated storage

## Existing-Feature Conformance Scope

Part of [com-604k](com-604k.md); scoped from [com-8j0w](com-8j0w.md). This is planned implementation/verification, not a completed fix. Reuses static audit [com-nsxb](com-nsxb.md), compiler `f89857b1` (runtime source unchanged from its `78bd9691` audit input), spec `1e0c4d0` and Syntax `00f740e1`. No compiler/probe/sanitizer/performance execution in this classification.

Currently accepted main signatures/arguments, panic/exit/status/signals, one-shot session/registry lifetime and existing non-generic top-level/associated storage. New Process/ExitCode public API shapes not currently admitted, generic stored assoc, new shutdown APIs and reusable host execution are excluded.

## Producer to Final Consumer and Removal

Existing driver/CompilerSession roots -> initializer execution and application entry -> event loop/exit/signal forwarding and child reaping. Ordinary storage ownership follows the common checked/global/instance records. Do not require deterministic user deinit on panic/process teardown where the spec excludes it, and do not equate registry retention with a leak or completed reusable teardown.

## Completion and Verification

Current main forms and rejection controls; arguments/status, synchronous and supported async INT/TERM/HUP exit, repeated one-shot admission failure, unknown/stale session IDs and ordinary associated-storage identity/mutation. Establish current accepted cases rather than adding missing public APIs. Initializer dependency ordering is separately owned by the startup-plan unit.

Close with exact revision/scope, final-consumer evidence, removed competing paths and applicable correctness/performance gates. Preserve matching-input baseline evidence; the approved formal self-compilation target is below 7 seconds. This task does not close the mixed/new-feature parent automatically.
