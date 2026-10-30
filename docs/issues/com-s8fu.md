---
id: com-s8fu
status: open
deps: []
links: [com-mmk9]
created: 2026-10-30T15:18:33Z
type: task
priority: 2
assignee: Koji Murata
tags: [backend, verification]
---
# Narrow normalized access emission inputs

Evidence: [input-authority answer](../../../evidence/compiler-api-audit/resolutions/backend-final-emission-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-resolution-backend-final-emission-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This issue owns product repair; implementing it is not a prerequisite for the source-only input investigation.

## Guarantee and Scope
Exact APIs: ambientStorageValues, midAmbientCheck, midAmbientBeginOperand, midAmbientBeginCall, midAmbientAllocateScopes, midAmbientEnd, midCanonicalEmitCall; actual calls 12. Narrow these APIs and every enumerated actual source/fixture caller to per-entry profiles/shared service slices. Keep coherent physical LLVM owner and matching source/session/body/canonical/signature/native owner pairing; preserve branch/default/mode gates, bounded derived writers, prefix order, diagnostic/trace, retained payload/native lifetime. No full Comp fallback, wrapper capture or source preparation delegate. One finite owner for this original family; coordinate runtime leaf mainC com-9h5s without duplicate ownership.

Preserve actual recorded success-only gaps as gaps, not future permission. Owning implementation must restore temporary permit/scoped state on all exits and balance actual begun records under existing design, while keeping legitimate memo/interner/physical derived prefixes. Do not roll back intentionally installed native function state or invent runtime panic unwind. Preserve per-entry full branch/default/frame/service profiles; coherent LlvmCtx/Module/Context native owner is justified. Concrete excess is unrelated source/syntax/preparation/publication authority, not native ownership.

## Completion
Real API/delegate/actual caller/capture narrowing, meaningful normal/reject/absence/requested/declaration/global/async/type/access/Err-prefix/restore/lifetime and noninterference controls; independent structural repair review and applicable validation later. Investigation has answered all required inputs, not implemented repair. Narrow these APIs and every enumerated actual source/fixture caller to per-entry profiles/shared service slices. Keep coherent physical LLVM owner and matching source/session/body/canonical/signature/native owner pairing; preserve branch/default/mode gates, bounded derived writers, prefix order, diagnostic/trace, retained payload/native lifetime. No full Comp fallback, wrapper capture or source preparation delegate. One finite owner for this original family; coordinate runtime leaf mainC com-9h5s without duplicate ownership.

Preserve exact actual caller and source/session/type/proof/pool lifetimes, ordering/defaults, diagnostic provenance, legitimate mutation and error prefixes in the pinned answer. A wrapper or callback retaining unrelated whole compiler authority is not a narrowing. Readonly grants are not writers. Cover relevant normal, rejected, boundary and failure-prefix controls, verify the real producer-to-final-consumer path and remove competing broad signatures. No statement of future GREEN is evidence that the repair has passed.

## Excluded
Old mainC/com-9h5s runtime leaves, optional passive declarationAccess, justified LLVM owner/slots; language/runtime/ABI/async/scheduling/backend algorithm redesign, product execution/performance/GREEN.
