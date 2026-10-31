---
id: com-xx65
status: open
deps: []
links: [com-mmk9]
created: 2026-10-30T10:38:55Z
type: task
priority: 2
assignee: Koji Murata
tags: [backend, verification]
---
# Narrow prepared closure instance, capture and body emission inputs

Evidence: [input-authority answer](../../../evidence/compiler-api-audit/resolutions/prepared-closure-evidence-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-resolution-prepared-closure-evidence-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This issue owns product repair; implementing it is not a prerequisite for the source-only input investigation.

## Guarantee and Scope
Only declareClosureEnvironmentDrop, emitClosureEnvironmentDrops, declareClosure, collectClosures, prepareClosureMidBody, bindMidClosureCaptures, emitClosures, midCanonicalMakeClosureSupported, midCanonicalEmitMakeClosure and their affected actual21-table consumers, with all bounded required generic prepared-Mid and growing-queue consumers. Existing closureSlot J and older release/metadata C scopes remain unchanged.

All nine actual signatures/callers/delegates use exact source reader/measurement capability and frozen instance/type/body/Mid/diagnostic views, plus bounded alias/interner effects where reached and coherent physical owner. Keep existing closureSlot J and unrelated release/capture-metadata C. No callback/facade can retain general Comp.

## Completion
Change all real signatures and exact callers; demonstrate no whole Comp retained behind capability/callback/capture. Coordinate shared already-owned native/layout/Mid/query services without reclassifying existing findings. Owner/session/outcome Registered/Active/Building/Failed/Succeeded guards; positive and negative cache hint/fallback; no false source/global/runtime readiness from registered symbol or Prepared token. Source and concrete closure body/function/capture/parameter/result/drop-origin/environment proof agreement; empty/captured/value Copy/Move/shared cell borrow and inout modes. Erased witness implementation bodyId vs adapterBodyId, cache hit/null/parameter and receiver lanes; private ABI/direct/indirect/omitted and implicit environment lane. All actual Bool/preflight/Err/panic distinctions, partially updated memo/interner/acquisition/native/coverage/queue state and actual restore behavior. Full selected generic prepared-body consumers, nested growing queues/fixpoint/cursor and same module/context/target lifetime. No unexamined Comp grant moved into another task. Source/structural independent review and meaningful behavior controls/gates for actual future narrowing; audit itself performs no product execution. Preserve actual source strength: closure requires successful source outcome, interface final check reads saved Source/Contract/Instance provenance as implemented without an extra prepared-outcome or fabricated Instance-only tag check. current cur.sourceFactReader is readhint only; conditional acquisition counter is a writer, not source publication. Keep fixed source/native/session and final body/capture/drop owner identity; allow no unexamined full Comp delegate.

Preserve exact actual caller and source/session/type/proof/pool lifetimes, ordering/defaults, diagnostic provenance, legitimate mutation and error prefixes in the pinned answer. A wrapper or callback retaining unrelated whole compiler authority is not a narrowing. Readonly grants are not writers. Cover relevant normal, rejected, boundary and failure-prefix controls, verify the real producer-to-final-consumer path and remove competing broad signatures. No statement of future GREEN is evidence that the repair has passed.

## Excluded
No product implementation/GREEN/performance or runtime/ABI/ARC/proof algorithm certification in source-only audit. No language/source acceptance strengthening or runtime execute permission from Mid Ready, row, alias memo or native symbol.



## Adopted Implementation Intake

[com-71gu](com-71gu.md) classifies the exact confirmed scope as required existing-feature phase4 conformance. Required admission owner(s): com-h61e; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-llvm-physical.json) retains all main/mixed roles and normative grounds. Current prepared closure environment/capture/body declaration/emission consumes same-session source-reader and frozen instances/Mid/type views plus limited reached derived effects. Preserve coherent LLVM owner and existing justified closureSlot, not a general Comp callback.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
