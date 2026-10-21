---
id: com-b1ro
status: open
deps: []
links: []
created: 2026-10-13T01:29:04Z
type: task
priority: 3
assignee: Koji Murata
tags: [frontend, ownership, mid]
---
# Audit unsupported closure environment shapes

The retained implementation note reports generic struct instantiations, function-typed captures and nested closures unsupported, rather than prohibited by source type kind. Known shapes should diagnose at declaration checking, shapes exposed by substitution at instantiation. Unique capture semantics are a separate specification constraint. Design: [Mid closure details](../design/mid-entry-audit.md#closures-and-synthetic-ownership-bodies).

Unique move capture remains a separate future design, not a prerequisite for spawn fn's move arguments. Decide capture-time ownership transfer, the environment/closure's copy capability, and call-time consumption independently. Owning a unique capture does not by itself require a unique closure if handles share one environment, and moving a value into that environment does not by itself make invocation one-shot. Consuming a capture without restoring it needs a distinct consumption contract. No choice among these future environment or call models is adopted here.

Evidence scope: retained from meta agents/provisional.md at c539d7b96615a5c59c0165b0a5e3df90ec1f8dac; grammar-specific items additionally come from agents/grammar.md at that revision. These notes mix historical reproduction and uninspected combinations. No current compiler run or exhaustive implementation audit was performed during migration. Recheck current source and minimal run/reject inputs before claiming a defect; close resolved investigations with evidence rather than weakening the specification.

## Acceptance Criteria

Reproduce current scope, close selected capture type/environment/drop paths consistently, preserve declaration versus instance diagnostics and ordinary value ownership, and do not use AST backend fallback.

## Source Recheck for the Conformance Inventory

Compiler `ea5f751a`, spec `16f2f13`, Syntax `00f740e1`; static inspection only,
without executing a compiler or reproducing runtime/test failures. The bounded
[whole-reference inventory](met-z0ro.md) does not close this implementation issue.

Codegen/Mono/Call.pw::checkedCaptureCell still explicitly rejects unique, generic-struct
or function-typed captured values. The generic/function-shaped capture restriction
is retained implementation coverage, not a new language prohibition. Unique move
capture remains a separately deferred design, so its absence alone is not a bug
or an expansion of the current type-checking parent's completion scope.
