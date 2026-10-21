---
id: met-k7ks
status: open
deps: []
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
