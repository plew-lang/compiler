---
id: com-vk09
status: open
deps: []
links: [com-mmk9]
created: 2026-10-30T10:38:55Z
type: task
priority: 2
assignee: Koji Murata
tags: [backend, verification]
---
# Narrow erased witness and dynamic call evidence inputs

Evidence: [input-authority answer](../../../evidence/compiler-api-audit/resolutions/prepared-closure-evidence-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-resolution-prepared-closure-evidence-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This issue owns product repair; implementing it is not a prerequisite for the source-only input investigation.

## Guarantee and Scope
Only buildAnyThunk, emitExistentialWitnesses, midCanonicalClosureCallPreflight, midCanonicalEmitClosureCall, midCanonicalExistentialCallPreflight, midCanonicalEmitExistentialCall and their affected actual21-table consumers, with all bounded required generic prepared-Mid and growing-queue consumers. Existing closureSlot J and older release/metadata C scopes remain unchanged.

Preserve exact source/body/site/root/trait/slot/binding/field/type/ABI identities, cached read hint/fallback and error distinction. Frozen witness/adapter selection and immutable Mid input only; native ownership/CoW/call/queue effects explicit; no source preparation/reselection or full Comp hidden in dependencies.

## Completion
Change all real signatures and exact callers; demonstrate no whole Comp retained behind capability/callback/capture. Coordinate shared already-owned native/layout/Mid/query services without reclassifying existing findings. Owner/session/outcome Registered/Active/Building/Failed/Succeeded guards; positive and negative cache hint/fallback; no false source/global/runtime readiness from registered symbol or Prepared token. Source and concrete closure body/function/capture/parameter/result/drop-origin/environment proof agreement; empty/captured/value Copy/Move/shared cell borrow and inout modes. Erased witness implementation bodyId vs adapterBodyId, cache hit/null/parameter and receiver lanes; private ABI/direct/indirect/omitted and implicit environment lane. All actual Bool/preflight/Err/panic distinctions, partially updated memo/interner/acquisition/native/coverage/queue state and actual restore behavior. Full selected generic prepared-body consumers, nested growing queues/fixpoint/cursor and same module/context/target lifetime. No unexamined Comp grant moved into another task. Source/structural independent review and meaningful behavior controls/gates for actual future narrowing; audit itself performs no product execution. Preserve actual source strength: closure requires successful source outcome, interface final check reads saved Source/Contract/Instance provenance as implemented without an extra prepared-outcome or fabricated Instance-only tag check. current cur.sourceFactReader is readhint only; conditional acquisition counter is a writer, not source publication. Keep fixed source/native/session and final body/capture/drop owner identity; allow no unexamined full Comp delegate.

Preserve exact actual caller and source/session/type/proof/pool lifetimes, ordering/defaults, diagnostic provenance, legitimate mutation and error prefixes in the pinned answer. A wrapper or callback retaining unrelated whole compiler authority is not a narrowing. Readonly grants are not writers. Cover relevant normal, rejected, boundary and failure-prefix controls, verify the real producer-to-final-consumer path and remove competing broad signatures. No statement of future GREEN is evidence that the repair has passed.

## Excluded
No product implementation/GREEN/performance or runtime/ABI/ARC/proof algorithm certification in source-only audit. No language/source acceptance strengthening or runtime execute permission from Mid Ready, row, alias memo or native symbol.


