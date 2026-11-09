---
id: com-rv7l
status: open
deps: []
links: [com-1hd3, com-nkoa]
created: 2026-11-09T14:53:00Z
type: task
priority: 2
assignee: Koji Murata
tags: [ownership, backend, mid]
---
# Compare and design guaranteed indirect value passing

## Purpose and Scope

Choose a bounded, semantics-preserving way to remove avoidable physical aggregate transfers from ordinary by-value parameters and implicit self. Start with method and design investigation, not product changes. [Existing observation](../../../evidence/performance-regression-history/value-self-abi.md) and its probe distinguish ARC savings from byval byte copies; compiler-wide contribution and recovery of com-1hd3 remain unproved.

## Work and Decision Boundary

1. Recheck the ownership-to-physical-ABI producer/consumer path in the selected revision and identify where stable storage, snapshot timing and ownership evidence are available.
2. Compare at least: existing byval plus LLVM optimization; guaranteed indirect passing of a stable evaluated snapshot/home; narrowly proved forwarding of an existing home. Use Swift/Rust primary design references and Plew contracts; record why rejected alternatives are unsafe or ineffective.
3. Define the owner of physical lane classification and its saved descriptor, required evidence, conservative fallback, caller/callee binding, temporary storage lifetime, invalidation and verifier obligations. Avoid a second source-type/effect/overload authority.
4. Specify when a snapshot is necessary: later argument evaluation, alias writes, shared cells/global/callback access, escape, return ownership, async acquisition and suspension. Unknown effects remain conservative. No new source borrow semantics, arbitrary size threshold, compiler-only shortcut, or blanket byval deletion.
5. Produce a finite scenario/entry matrix for direct calls, methods, generic/default adapters, closures, witness/existential entries, destruction glue, lazy/JIT and applicable external adapters. Unsupported cases keep a coherent existing ABI; explain how both sides agree, rather than silently mixing conventions.

## Deliverables and Completion

A recommended design and alternatives, source-to-consumer responsibility map, safety proof/fallback conditions, bounded prototype scope and measurement plan are recorded here; adopted contracts belong in [Representation and ABI](../design/representation-and-abi.md), [ownership](../design/ownership-and-access.md) and [pass contracts](../design/passes-and-optimization.md), without duplicating them. Obtain user approval before adopting a heavy ABI/architecture decision or new meaning; this ticket does not grant that approval. Independent review checks semantic preservation, feasibility and finite scope before the prototype begins. Update downstream scope from the findings. Investigation can conclude no viable approach, with evidence and explicitly deferred follow-ups; it does not certify optimization or performance recovery.

## Verification Plan

If no viable design is selected, explicitly defer the dependent tickets and
return to [com-1hd3's checkpoint](com-1hd3.md#interruption-checkpoint-and-return-procedure)
from this task; do not rely on the unexecuted integration task to arrange return.

Separate semantic controls, structural proof of actual byte-copy reduction, small-probe runtime and same-source old/new self-compilation. Fix source/std/toolchain/generation conditions and count analysis/code-size cost as well as benefit. No throughput claim from Swift assembly alone.

## Relationships and Exclusions

This is the next planning step for the optional ABI optimization, linked to com-nkoa and com-1hd3. Broad interprocedural effect precision is not a prerequisite unless this investigation proves a specific dependency. No product implementation, main/seed promotion, or closure of current phase-three guarantees.

## Plan Review

The independent fresh-context reviewer abi_optimization_plan_review checked the
three-ticket plan against compiler base 54761fea, existing evidence and ABI/pass
contracts. Its required no-go return paths and raw/optimized execution controls
were added; permanent safe snapshots were distinguished from temporary
implementation limitations. Re-review found those items resolved with no further
required plan change. Local links/anchors and acyclic dependencies were checked.
This accepts the task plan only, not an ABI design, implementation or speedup.

