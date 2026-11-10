---
id: com-h8b1
status: in_progress
deps: [com-9hny]
links: []
created: 2026-11-09T17:11:02Z
type: task
priority: 2
assignee: Koji Murata
parent: com-uiri
tags: [ownership, backend, mid]
---
# Connect guaranteed home transport through all entry consumers

## Guarantee and Scope

Freeze an inventory of actual common-helper call sites, then migrate caller and callee binding coherently across normal, method/default, synthetic, closure/witness, external adapters, async and demanded JIT entries. Split this unit by coherent migration boundary before coding when needed. No direct-only rollout. Preserve conservative snapshots, ownership, async frame acquisition and external ABI.

Canonical proposal: [com-rv7l](com-rv7l.md#investigation-result-and-recommended-design). Parent [com-uiri](com-uiri.md) retains end-to-end prototype and no-go/return responsibilities. This task does not change source language semantics or authorize main/seed promotion.

## Execution and Completion

Enumerate finite assertions and real producer/consumer inventory before editing; use task-start TDD and independent neutral review at each reviewable increment. Structural RED must identify the missing handoff/protocol rather than unrelated fixture failure. Record actual execution and retained snapshots as separate evidence. Each required obligation above must be reconciled; deferred implementation cannot count as completion. Measure metadata/preparation cost at W2/W4 even when this unit does not claim speedup.



## Reviewed Execution Plan

The neutral read-only review derives this boundary from com-rv7l, the pinned Swift
study and the W1/W2 producer/consumer implementation. A native Home proves type
and provenance only; it does not prove initialized lifetime or interval stability.
Do not treat a nonzero MidLocalDecl.sourceBinding as a const proof.

Use two coherent increments within this task (not a direct-only ABI rollout):

1. Introduce GuaranteedIndirect for completed copyable Borrow value lanes in the
   sole physical planner. Move, Inout, unique borrow, scalar/empty/result and
   external C remain unchanged. Change declaration/call attributes and all
   Body/Closure/Witness/Glue/Async/C-to-private consumers together. Retain typed
   Value/Home until transport emission. Bind guaranteed parameters to read-only
   homes without a redundant alloca/load/store. Incoming guaranteed parameters
   are a scoped proof provider and may forward. Every other unproved source
   supplies a conservative evaluated snapshot under the same ABI. Async must
   acquire/copy before public entry returns; no caller address enters the frame.
2. Complete the W1-stability-to-Ready storage-plan handoff for initialized owned
   immutable locals, dedicated evaluation temporaries and eligible nonboxed
   static value fields. Project the sealed accepted facts once, retain compact
   body/operation/root/layout/scope correspondence, and consume it at emission.
   No AST/effect search or per-argument body scan. Globals lacking readiness,
   boxed fields lacking owner evidence, dereference/index/cells/unknown effects
   retain existing snapshot/acquisition timing. A malformed required fact is an
   Internal failure; explicitly missing optimization proof is conservative.

The first increment must carry explicit completed copyability independently of
native layout and source passing; ptr/environment/erased receiver are not value
homes. Native incoming/projection-home validation must use the admitted descriptor
and exact parent/index/type/scope, not accept arbitrary ptr arguments when byval
is removed. Do not add readonly/noalias or invent source ownership from addresses.
Do not use alias:Bool to conflate read-only parameter binding with Inout.

For each increment freeze actual call-helper and binding consumers, then pair
structural/native RED with real source controls: normal leaf/forward/recursive,
method self, generic/default, closure, witness, async immediate/suspended, glue,
C-to-private and requested JIT. Check required evaluation-time snapshots under
later argument/default/callback mutation, managed fields/CoW, returns/captures
and exact destruction. Keep scalar/empty/Move/Inout/unique borrow noninterference.
Reject stale/wrong type/role/index/body/scope, underaligned or unproved homes and
invalid projections. Check raw and optimized output: byval and callee copies
must disappear only for guaranteed lanes, and incoming addresses must reach the
next call. Record actual machine transfer reduction separately from ARC at W4.

Neutral source/evidence review is required before accepting each increment.
This plan grants no source semantics/lifetime changes or main/seed promotion.

## Incoming Home Source Checkpoint

[Retained checkpoint](../../../evidence/performance-regression-history/value-passing-implementation/w3-transport/incoming-home-checkpoint.json) records the structural RED, fresh standard build, native private producer/consumer and updated raw/optimized source tests. Completed copyability selects typed byref(T)+align in the common planner; all families retain typed carriers, and readonly synchronous incoming parameters bind and forward directly. Other values/homes retain snapshots. Move/Inout/unique and outer C remain unchanged; async acquires its frame-owned value before returning.

The independent source review found and closed a retained local/lane mapping hole: normal ordinal or closure/witness parameter binding and canonical semantic lane identity are now checked, with same-native two-lane index-swap rejection. LLVM byref is only physical ABI/type evidence, never source stability/lifetime permission. No readonly/noalias or new ARC suppression was added.

This is a source checkpoint, not W3 completion. Next complete sealed local/temporary/eligible static-field facts through canonical instantiation, Ready use correspondence and final call consumption. Source-origin integers or an arbitrary alloca/GEP are not stability proofs. Initialisation/lifetime/access remain the existing verified Mid contract. Remaining final private/family/gates and W4 adoption stay open.
