---
id: com-1fxn
status: open
deps: []
links: [com-mmk9]
created: 2026-10-30T14:51:45Z
type: task
priority: 2
assignee: Koji Murata
tags: [verification, frontend]
---
# Narrow argument view ID recovery inputs

Evidence: [input-authority answer](../../../evidence/compiler-api-audit/resolutions/candidate-recovery-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-resolution-candidate-recovery-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This issue owns product repair; implementing it is not a prerequisite for the source-only input investigation.

## Current API Resumption Map

The endpoint names and call counts in the original audit below describe its
frozen source, not instructions to recreate removed APIs. Removal commits:
`f2841f6f`. Current same-path entries: `argViewSources` in [Codegen/Resolve/TypeRecovery.pw](../../src/Codegen/Resolve/TypeRecovery.pw).
The replacement carries complete ResolvedViewSource records. Do not narrow it back to view IDs or discard positional arguments/associated equations to match the original audit API. Existing semantic repair owner: [com-zdod](com-zdod.md).

Apply this task's original per-entry authority/lifetime guarantees to the
surviving path and its actual callers. Retain the existing audit evidence as the
baseline; reconcile which grants still need narrowing versus those eliminated
by the semantic repair. Deleted names alone do not prove the whole family fixed.
The task remains open until that finite reconciliation and required controls /
independent review establish closure; do not widen it to every API of the repair
owner or restore a superseded decision path.

## Guarantee and Scope
Audit-time APIs (9665094d): argViewIds; actual calls 1. Exactly this whole original main or component scope has one finite repair owner. Preserve existing mainC/com-g5lm leaves, shared domain/query services only actual required per-entry portions; no inherited full graph-union grant.

At audit source9665094d this was only the argViewIds component; typeRefViewIds/appendDistinctViewId (mainC/com-g5lm) were unchanged at that snapshot. Both helpers were also removed by f2841f6f; the current full-source result is described above. Historical per-entry observation: Raw outer ExtView IDs first-seen order; strip clears and bypasses exprType/base/TypeInfo sources. Normal path conditional base query and only unchangedroot TypeInfo.ref IDs, no resolved-owner interpretation invented. Whole mutable Comp grants unrelated syntax/parser/Mid state and independent source builder/publication/preparation/outcome operations beyond the closed per-entry operations. Coherent domain owners/passive complete descriptors remain legitimate. No direct LlvmCtx/native ownership claim is needed for this concrete excess conclusion.

## Completion
Change actual API grants/signatures/all typed consumers, preserve source/session/owner/ParamId/receiver/proof/view/term/cache/diagnostic/current-frame/default/error-prefix/lifetime and current candidate local commit/discard/rank behavior. Keep all-exit temporary restore as existing design endpoint against actual inner success-only gaps, without rollback of valid persistent derived pools. Do not add new selection/inference/coverage semantics. Eventual structural review/TDD/refactor validation belongs implementation; no repair/GREEN claim in investigation. Keep per-entry required operations/defaults/source/session/owner/ParamId/proof/view/guard/Err/retention across every actual consumer and zero-call body contract. No unrelated Comp facade/capture or service union; all-exit temporary lexical scopes distinct from current gaps and valid persistent derived prefix.

Preserve exact actual caller and source/session/type/proof/pool lifetimes, ordering/defaults, diagnostic provenance, legitimate mutation and error prefixes in the pinned answer. A wrapper or callback retaining unrelated whole compiler authority is not a narrowing. Readonly grants are not writers. Cover relevant normal, rejected, boundary and failure-prefix controls, verify the real producer-to-final-consumer path and remove competing broad signatures. No statement of future GREEN is evidence that the repair has passed.

## Excluded
Other original J/C/O/optional/U/mainC; language/source/type/solver/overload/coverage/ownership algorithms, productrepair/execution/performance/GREEN within audit.

## Adopted Implementation Intake

[com-yjyu](com-yjyu.md) classifies the exact confirmed scope as required existing-feature phase3 conformance. Required admission owner(s): met-6e6k, met-ucze; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-defaults-and-literals.json) retains all main/mixed roles and normative grounds. Existing argument outer-view ID recovery participates in source type/applicability context; preserve stripped path bypass and first-seen view order, no projection-owner interpretation or whole Comp service union.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
