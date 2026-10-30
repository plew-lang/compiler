---
id: com-cuiw
status: open
deps: []
links: [com-mmk9]
created: 2026-10-30T09:49:11Z
type: task
priority: 2
assignee: Koji Murata
tags: [backend, ownership, verification]
---
# Narrow existential copy drop and vtable semantic inputs

Evidence: [input-authority answer](../../../evidence/compiler-api-audit/resolutions/typed-ownership-service-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-resolution-typed-ownership-service-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This issue owns product repair; implementing it is not a prerequisite for the source-only input investigation.

## Guarantee and Scope
buildAnyCopyThunk/buildAnyDropThunk/ensureAnyVtable/boxIntoAny and exact actual consumers. Preserve finalized resolution/member/body identity, pre-cache-before-recursion global ordering, runtime allocation/box ownership and success-only physical helper restore. Exact target APIs: buildAnyCopyThunk, buildAnyDropThunk, ensureAnyVtable, boxIntoAny.

Retain coherent inout LlvmCtx for the matching native module/context/target, current physical function/builder/ABI/registry/queue/ambient state. Replace whole Comp with only same-session frozen type/declaration/layout/destruction/conversion/static-proof/final-callee/final-existential/body/Mid/source-success/evidence readers, precise source/config/diagnostic/trace projections and actually reached bounded writers: finalDestructionIds alias memo, runtime symbol bytes+interner, and successful prepared-reader measurement acquisitions. Grant each API/ARC branch only its actual required parts, preserving conditional recursive/queued consumers separately. No source prepare/check/type/proof/layout/body/destructor/Mid/monoWork construction, arbitrary options writer or Comp capture/unwrap remains behind wrappers.

## Completion
Change the actual named broad Comp signatures and every listed actual expression for this subset, plus bounded delegated/queued consumer wiring; the full177-expression table retains exact same-line duplicate columns. Preserve ready guards, all10 ARC classes with branch-direct versus recursive requirements, canonical Copy/Move/Read/Inout and default forWrite=false, frozen conversion tags0/2/3/4/5 and selected payload order, source-owner/session/sealed-readiness and ambient evidence, runtime and private/C ABI identities/modes/lifetime, three necessary writer prefixes and actual success-only BB/curFn/ambientPermit restoration. Preserve declaration-before-body, fixedpoint drains/cursor advance ordering, rawbuf final-owner/live-range and replacement/count commit-before-release. Existing missing/unsupported/null/preflight/Result/panic/trace/coverage distinctions remain. Use task-start TDD/refactor controls, structural no-Comp-retention checks and independent repair review/gates; coordinate existing physical-owner services without duplicating semantic selection.

Preserve exact actual caller and source/session/type/proof/pool lifetimes, ordering/defaults, diagnostic provenance, legitimate mutation and error prefixes in the pinned answer. A wrapper or callback retaining unrelated whole compiler authority is not a narrowing. Readonly grants are not writers. Cover relevant normal, rejected, boundary and failure-prefix controls, verify the real producer-to-final-consumer path and remove competing broad signatures. No statement of future GREEN is evidence that the repair has passed.

## Excluded
No product repair/execution/GREEN in input audit, no runtime/ABI/source acceptance or algorithm redesign, no mathematically minimal per-native-field decomposition. Old unused-formal/eid and existing justified physical registry scopes are not reclassified.


