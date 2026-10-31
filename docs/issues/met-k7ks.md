---
id: met-k7ks
status: open
deps: [com-bz23, com-ktyj, com-mexd]
links: []
created: 2026-10-21T11:05:50Z
type: task
priority: 3
assignee: Koji Murata
tags: [frontend, diagnostics]
---
# Preserve structured diagnostic provenance through final reporting


## Current Source Inspection

Compiler `ea5f751a8343febe8dfecfa3e88e48ccebdefb27`, spec
`16f2f13970dbe2789214b2206c48af3df21b68c8`, pinned Syntax
`00f740e1178e5b992cfdd30ddaa5a0612ce27b43`. Static source inspection only;
no compiler execution, regression reproduction or performance result is claimed.

## Contract and Observed Gap

[Diagnostics](../design/diagnostics.md#provenance-and-lifetime) requires
domain-owned source provenance and contextual causes to survive final reporting.
It does not require a universal rich object, lint registry or automated fix system.

[Diag](../../src/Diag.pw)::CompileDiagnostic currently has severity, location and
message; DiagnosticLocation supports only unpositioned/line/file+line.
[Emit](../../src/Codegen/Emit.pw)::diagnosticAt/exprOffset use source spans when
available and fallback anchors otherwise. Legacy compileErrorAt adapters terminate
the process; native tool/LLVM errors also have direct stderr paths. Existing owned
diagnostics, warning queues and retained owner failures are useful partial
implementation, not proof of original generated-origin/context preservation or
that every service returns failure without exiting.

## Completion Boundary

Choose only necessary owned provenance/context data, transport the original cause
through adapters and retained failures, and make the final renderer consume it.
Trace generated and instantiated operations, cross-file conflicts, repeated failed
requests, warning draining and returning APIs. Do not infer new acceptance from
recovery or move semantic selection into the renderer. Existing call-specific
checks remain [com-lndr](com-lndr.md). Code suggestions/stable error codes are not
added as mandatory scope by this audit.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Included repair**.

Existing source/generated/instantiated cause provenance, retained request failures and current reporting adapters. Finish cause ownership to renderer, with current multi-file and repeat-failure controls. Rich fix-its, stable error-code catalogs and future embedding services are not required.

## Supporting Observation from Phase-Two Re-review

At compiler production `87b382d2`, the actual Hash derive consumer compiles with root `use @Std/Hash only { Hash, Hasher, SipHasher }`. Removing only Hasher while preserving generated output rejects at `MissingSupport.gen.pw:2` with `implementation requires a trait constraint not guaranteed by the requirement`, rather than naming the missing consumer dependency. [com-io5f](com-io5f.md) preserves the successful/negative pair and [observed diagnostic](../../../evidence/existing-feature-conformance/phase-two-rereview/root-use/hash-missing-support.stderr). Root-use isolation is correct; this is a non-blocking cause-reporting improvement/control for this existing diagnostic task, not an additional phase-two acceptance requirement or prescribed exact wording. Preserve the originating missing binding/constraint cause through final reporting when closing this task.

## Audited Adapter Authority Prerequisites

The adopted com-k35g intake connects declaration diagnostic projection com-bz23, terminal preparation reporting com-mexd and observation/final-output finishing com-ktyj as required prerequisites. Preserve owned diagnostics, same-session provenance, trace/output/exit order and physical module/result transfer. Observation does not grant source meaning or arbitrary compiler mutation. The latter native/output consumers also block [com-h61e](com-h61e.md); this diagnostic scope does not erase that execution boundary. Product repairs and current-candidate admission remain open.
