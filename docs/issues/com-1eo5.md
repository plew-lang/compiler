---
id: com-1eo5
status: open
deps: []
links: [com-mmk9]
created: 2026-10-30T13:33:36Z
type: task
priority: 2
assignee: Koji Murata
tags: [verification, frontend]
---
# Narrow selected literal and legacy argument validation inputs

Evidence: [input-authority answer](../../../evidence/compiler-api-audit/resolutions/check-call-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-resolution-check-call-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This issue owns product repair; implementing it is not a prerequisite for the source-only input investigation.

## Guarantee and Scope
Exact APIs: checkRecordedCallLiteralArguments, checkSymbolicMethodArgs, localTypeRefByName, checkCallArgs, checkMethodArgs. Actual calls 11. Per-entry saved signature, symbolic obligations, contextual literals/value checker and actual legacy inference/query writer contracts. localTypeRefByName is the restricted stored-local reader/pending-global append operation, not full Q.

Five APIs retain exact saved/symbolic/concrete/legacy argument routes, label mapping/modes, semantic literal expected refs, full type/value compatibility when reached. localTypeRefByName only name interner+stored local/global pending-row append, no type forcing. Literal construction source writer/putExpression+identifier metadata, currentSourceOwner and tcLog failure latch are genuine; source success is distinct. Match payload local pop and G:L restore success-only are observed gaps; future repair owns all-exit scopes without erasing valid derived/source failure prefix. Do not invent function-value arity semantics or retry saved selection. Mutable Comp admits unrelated driver/source loading, arbitrary declaration/AST mutation, independent source owner success/publication, native/runtime/backend and final body admission; none follows from this operation-scoped required read/write map. Remove these actual grants, including captures/facades retaining whole Comp.

## Completion
Change real API signatures and every enumerated actual caller, preserve per-entry input/default/identity/effects and valid derived prefix; own temporary lexical restoration on all exits against current legacy gap; structural closure plus later TDD/refactor verification. This investigation performs no repair or GREEN. Keep each actual per-entry/default/owner/frame/cache/retention/conditional writer map instead of a group union. Preserve source-to-frozen-match-to-Mid final consumer, owned descriptors and pool lineage. No unrelated whole compiler authority through wrappers/captures. Relevant positive/reject/boundary/noninterference/failure controls and independent structural review/gates belong to future repair.

Preserve exact actual caller and source/session/type/proof/pool lifetimes, ordering/defaults, diagnostic provenance, legitimate mutation and error prefixes in the pinned answer. A wrapper or callback retaining unrelated whole compiler authority is not a narrowing. Readonly grants are not writers. Cover relevant normal, rejected, boundary and failure-prefix controls, verify the real producer-to-final-consumer path and remove competing broad signatures. No statement of future GREEN is evidence that the repair has passed.

## Excluded
Other original J/C/O/optional/U scopes and existing com-9sa5; language/source acceptance/ownership/type/solver/general algorithm redesign, product execution/repair/performance/GREEN within this source audit.


