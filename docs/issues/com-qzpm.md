---
id: com-qzpm
status: open
deps: []
links: []
created: 2026-10-13T01:10:11Z
type: task
priority: 3
assignee: Koji Murata
tags: [ownership, runtime]
---
# Implement adopted concurrency and atomic allocation contracts

spawn/channel and whole-program sendability/effect propagation remain implementation boundaries, not a redesign of the specified event-loop baseline. Allocation sharing determines a fixed atomic/non-atomic mode; no boundary graph-copy or dynamic promotion is adopted. AOT must close its sharing plan before execution; demand execution adopts a conservative atomic baseline before allocation/publication. Current non-atomic helpers do not establish concurrency implementation.

Design: [runtime](../design/runtime.md). Source contracts: [modules](https://github.com/plew-lang/spec/blob/main/spec/04-execution/15-modules.md), [concurrency](https://github.com/plew-lang/spec/blob/main/spec/04-execution/14-concurrency.md), [basic types](https://github.com/plew-lang/spec/blob/main/spec/01-basics/02-basic-types.md) and [packages](https://github.com/plew-lang/spec/blob/main/spec/04-execution/17-packages.md), as applicable.

Evidence scope: migrated from meta agents/design-decisions.md at d2c317318126e994c86e4a3c1f71bfef75606fa2. No new compiler execution or full implementation audit was performed. This is retained follow-up work, not blanket evidence of defects.

## Acceptance Criteria

Audit current implementation, preserve selected protocol from semantic roots through allocations and consumers, and obtain a design decision for any newly necessary lazy/concurrent interaction instead of silently guessing confinement.

## Retained provisional audit scope

Also audit sendable closure snapshot captures, sendable-to-ordinary function guarantee erasure, capture ownership/non-escaping use and read capabilities through Ref. The former grammar note reports shallow sendability/type carriers but loud rejection of sendable fn literals and spawn; do not equate accepted type syntax with execution support or turn this retained limitation into a new specification prohibition.

Evidence scope: retained from meta agents/provisional.md at c539d7b96615a5c59c0165b0a5e3df90ec1f8dac; grammar-specific items additionally come from agents/grammar.md at that revision. These notes mix historical reproduction and uninspected combinations. No current compiler run or exhaustive implementation audit was performed during migration. Recheck current source and minimal run/reject inputs before claiming a defect; close resolved investigations with evidence rather than weakening the specification.

## Source Recheck for the Conformance Inventory

Compiler `ea5f751a`, spec `16f2f13`, Syntax `00f740e1`; static inspection only,
without executing a compiler or reproducing runtime/test failures. The bounded
[whole-reference inventory](met-z0ro.md) does not close this implementation issue.

The current implementation is smaller than the adopted spec14 contract. Pinned
Syntax has a spawn token but no spawn declaration/expression in the inspected
semantic input; fixtures spawn_fn_rejected, pub_spawn_fn_rejected and
spawn_block_rejected intentionally reject those forms. No standard Sync endpoints
or worker transport implementation accompanies this route. Backend.pw's generated
rawbuf retain/release and weak operations use ordinary increments/decrements;
there is no allocation-mode plan or JIT atomic variant in this inspected runtime.

There is also a source-confirmed semantic mismatch independent of runtime worker
support: Codegen/Infer/Sendability.pw::typeRefIsSendableDepth treats Ref[T] and
WeakRef[T] as sendable when T is sendable, whereas spec03/14 makes these handles
nonsendable. MutableRef is already rejected. This does not demonstrate a live
cross-thread race, since spawn is currently rejected, but it is not merely missing
optimization or uncertain coverage.

Worker/JIT pausing is separately [met-b04w](met-b04w.md); standard reference
migration is [met-op15](met-op15.md). This issue retains worker/channel transport,
sendability/effect closure, fixed RC allocation modes, typed delivery/cleanup and
AOT/JIT agreement. Do not enable spawn or declare RC support by changing the type
predicate or adding the missing syntax alone.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Mixed: split current subset**.

Current sendable binder/annotation predicate is com-f8bw, used independently of spawn by Infer/Type and Infer/Check. Ref/WeakRef nonsendability is therefore an in-scope static correction. Worker/channel transport, sharing modes and atomic RC remain outside; changing that predicate cannot claim workers safe.
