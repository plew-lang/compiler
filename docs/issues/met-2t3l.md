---
id: met-2t3l
status: open
deps: []
links: []
created: 2026-10-21T11:05:50Z
type: bug
priority: 2
assignee: Koji Murata
tags: [frontend, ownership, documentation]
---
# Enforce impl-only deinit placement


## Current Source Inspection

Compiler `ea5f751a8343febe8dfecfa3e88e48ccebdefb27`, spec
`16f2f13970dbe2789214b2206c48af3df21b68c8`, pinned Syntax
`00f740e1178e5b992cfdd30ddaa5a0612ce27b43`. Static source inspection only;
no compiler execution, regression reproduction or performance result is claimed.

## Contract and Source-Confirmed Mismatch

Spec03's deinit rule permits explicit destruction only in the defining module's
inherent impl, with unique Self over the impl's entire applicability range. Struct
bodies and enum-level deinit are rejected. Conditional capability ranges are
separately part of [met-b2la](met-b2la.md).

Pinned Syntax parseSyntaxStructDecl still accepts KwDeinit into the declaration's
hasDeinit/deinitBody. [Lower/Decl](../../src/Codegen/Lower/Decl.pw) lowers that
body, and compiler source itself uses struct-body deinit, for example
[CompilerExecution](../../src/CompilerExecution.pw)::SessionRegistration.
[Lower/Impl](../../src/Codegen/Lower/Impl.pw) also supports an impl deinit, so
implementation of the correct form does not establish rejection of the old one.
This is visible acceptance/representation of a prohibited source form; no fresh
execution or new destructor-safety bug is claimed. Checked spec03 and spec15
examples already use impl placement and should not be reported as contradictory.

## Completion Boundary

Migrate compiler/std/tests using the old location and reject it at the shared
syntax/semantic boundary. Preserve defining-module, unique-Self, overlap, ordinary
field cleanup and exactly-once deinit contracts through final destruction.
Cover direct and materialized Syntax paths and normal AOT/JIT uses. Do not remove
the old parser form before bootstrap/source compatibility has a concrete plan.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Included repair**.

Ordinary deinit already has an inherent-impl implementation; rejecting its prohibited struct-body location is an existing-feature correction. Migrate current compiler/std/tests with an explicit current-carrier/add-before-use pin/bootstrap sequence before removing the old parse lane. No conditional unique-generic deinit or new bootstrap strategy.

## Explicit Aggregate Lowering Struct-Body Deinit Lane

Batch0074 adds exactly run/syntax_lower_decl_aggregates.pw/.out. Embedded ordinary Box[T] contains struct-body deinit; current direct Lower registers destructor function/deinit row1. Adopted deinit requires unique Self and defining-module inherent impl, so this intermediate registration oracle is current internal lane only. Preserve generic field/binder and Choice variant registration when reconciling valid impl deinit versus malformed-source checks; do not claim old counts certify adopted source or destructor runtime, or automatically rewrite the golden. Existing generic_deinit_on_struct pins unique-only rejection but combines capability and placement; no new language decision or audit-time repair.

## Scoped Test Audit Intake com-ti5b

The [exact scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/test-dispositions-001-033.json) retains each original row, primary/secondary role, correction and current/excluded boundary. Required original row ordinal(s): 13.

Row13: Exactly the immutable original row findings/qualifiers and receiving task current-feature subset; retain all originals and per-finding corrections. Reuse included impl-only deinit placement/source+std+test migration, preserving actual runtime assertions and the qualified internal lowerer lane. No conditional unique-generic deinit is added. Required admission: com-604k.

Preserve the original finite contract and meaningful controls; intake does not choose unresolved source semantics, implement new APIs, certify product GREEN or close a mixed future/optional parent. Required repair/investigation must finish before its affected admission; classification closure cannot bypass it.
