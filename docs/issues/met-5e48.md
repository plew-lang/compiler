---
id: met-5e48
status: open
deps: []
links: []
created: 2026-11-28T15:39:46Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [mid, performance]
---
# Measure and eliminate repeated draft statement prefix copies

## Guarantee and scope

This task is **not complete**. Eliminate redundant draft statement-prefix copies while preserving bounds/closed-block no-op, statement order/payload, terminators, sibling blocks and external CoW snapshots. No canonical storage change, compiler-only ARC exemption, check bypass or selected-call semantic change is delegated. [Mid storage](../design/mid.md#draft-construction-and-canonical-storage) permits owned temporary arrays; the general indexed access meaning remains spec03.

## Confirmed evidence and rejected prototype

[Evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/projection-members/performance-recovery/draft-append/): scoped private runtime probes measure381605 appends;256782 shared reallocations copy755249 elements/138965816bytes, max prefix59. The direct nested-place prototype d6a1136d changes draft statements to mut val and avoids explicit prefix replacement, but copies stay identical while prepare checks double. These are O0 counts, not optimized-time predictions. Target/declared std/manifest/lock input fingerprints and identical LLVM are retained; product runtime/LLVM were not patched.

Private behavior controls passed before/after, including explicit current/sibling Open, outer/inner/other-block snapshots, payload/order and bounds. Three existing continuation/value CFG programs passed with identical LLVM. Ordinary functions necessarily traverse Mid/Program→templates→buildParametricMidBody and Backend/Llvm/Any Ready→genLlvmPreparedMidBody; no AST fallback. Optimized prototype build/own-source smoke passed, but five same-source pairs observed7.759354→7.910669s (all10LLVM equal/input unchanged). Stable universal slowdown is not claimed; the experiment did not remove its target cost.

Prototype product changes were rejected and restored to f967a9fa; all src hashes match the retained ac8 snapshot. Tests/runner/harness registration are retained and the restored root unit probe passed. Candidate ac8 remains the latest finite-adopted source; final related whole gate and formal7s are not certified.

## Mechanism and required replanning

Independent review corrects the original endpoint assumption: direct source place spelling is not physical in-place mutation. Spec03's indexed mutation model is getter→owned temporary→modify→setter. Build.midTemplateInoutCallArgument routes Field-of-Index through Access; Access's getter writes valueLocal, its setter consumes the changed place, then cleanup drops it. The original slot is not emptied and can keep the inner backing shared. Source and counts support this mechanism; they do not prove every retain has only this cause.

The active goal's task-plan-error stop condition applies: the proposed local endpoint was insufficient. Before implementation resumes, replan the general Access/ownership optimization boundary and its controls. Proven physical mutation must preserve one-owner backing, no invalidating reentry, nonoverlap, selected getter/setter effects, evaluation order, writeback and external snapshots. Do not substitute compiler-specific ARC suppression or take/clear workarounds. No language specification change has been decided or shown necessary. Keep the finite follow-up owned here until the new scope is agreed; do not close by merely assigning it elsewhere.
