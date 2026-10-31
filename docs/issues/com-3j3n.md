---
id: com-3j3n
status: open
deps: []
links: [com-mmk9]
created: 2026-10-30T10:22:37Z
type: task
priority: 2
assignee: Koji Murata
tags: [backend, verification]
---
# Narrow paired runtime intrinsic preflight and emission inputs

Evidence: [input-authority answer](../../../evidence/compiler-api-audit/resolutions/physical-support-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-resolution-physical-support-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This issue owns product repair; implementing it is not a prerequisite for the source-only input investigation.

## Guarantee and Scope
Only midCanonicalCellControlPreflight, midCanonicalEmitCellControl, midCanonicalEmitRuntimeCoreStringFfiCall, midCanonicalEmitRuntimeNumericCall, midCanonicalEmitRuntimeSystemCall, midCanonicalEmitStrongCell, midCanonicalRuntimeCoreStringFfiPreflight, midCanonicalRuntimeNumericPreflight, midCanonicalRuntimeSystemPreflight, midCanonicalStrongCellPreflight, their exact98-table actual consumers and bounded reached delegates. Paired preflight/emitter families have one repair owner; per-API query/emission modes remain distinct.

Borrow same-session frozen canonical/type/declaration/proof/literal/source-diagnostic inputs; require only conditional finalDestructionIds alias memo and runtime-name append/interner. Keep matching physical native query/emission/cache owner roles explicit, with targetC policy memo and retain queue consumer contract. No facade/callback/unwrap grants arbitrary Comp. No runtime-name writer for probes; alias memo only paths reaching final layout. Direct extern probe adds physical targetC policy cache. Preserve actual Bool/preflight/Err distinction and native type-kind queries. Fixed selected descriptors + admitted Read/literal or Move values + native builder/destination map. Runtime gateway interner and native cache/instruction effects; FromBytes adds retain-only ownership queue closure. No source-success reader/counter is justified by this scope.

## Completion
Change actual signatures and every affected actual caller; preserve frozen body/global/place/call/type/conversion/newtype/ownership identity, all Read/Copy/Move/Inout and receiver lanes, allowDeref defaulttrue versus explicitfalse,15Buffer shapes, system/Core/Ffi/numeric/cell ABI, native same module/context/target lifetimes and exact Bool/preflight/Err behavior. Preserve alias memo/runtime interner/native target-C policy/declaration/witness queue prefixes where reached, retain:true and forWrite:false specialization, queue fixedpoint/cursor advance, own helper-builder disposal, caller trace and owned diagnostics. Do not grant source-ready acquisition/publication, type/proof/body/Mid construction or cur mutation. Shared helper narrowing must coordinate existing owners and remove whole-Comp captures rather than hide them. Use task-start controls, independent source/behavior review and appropriate future gates.

Preserve exact actual caller and source/session/type/proof/pool lifetimes, ordering/defaults, diagnostic provenance, legitimate mutation and error prefixes in the pinned answer. A wrapper or callback retaining unrelated whole compiler authority is not a narrowing. Readonly grants are not writers. Cover relevant normal, rejected, boundary and failure-prefix controls, verify the real producer-to-final-consumer path and remove competing broad signatures. No statement of future GREEN is evidence that the repair has passed.

## Excluded
No product repair/GREEN or runtime execution within audit; no source selection/ABI/runtime/ownership algorithm redesign, globally minimal service proof or full malformed-IR verification.



## Adopted Implementation Intake

[com-71gu](com-71gu.md) classifies the exact confirmed scope as required existing-feature phase4 conformance. Required admission owner(s): com-h61e; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-llvm-physical.json) retains all main/mixed roles and normative grounds. Current paired runtime numeric/system/String/FFI/cell preflight and emission use fixed selected descriptors/native operands. Preserve probe versus emitter distinctions, conditional native target-C/alias caches and FromBytes retain queue; no source-success acquisition or arbitrary source writer.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
