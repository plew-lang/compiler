---
id: com-zai9
status: open
deps: []
links: [com-mmk9]
created: 2026-10-30T13:13:22Z
type: task
priority: 2
assignee: Koji Murata
tags: [verification, frontend]
---
# Narrow lexical operator arity selection inputs

Evidence: [input-authority answer](../../../evidence/compiler-api-audit/resolutions/viewed-static-selection-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-resolution-viewed-static-selection-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This issue owns product repair; implementing it is not a prerequisite for the source-only input investigation.

## Guarantee and Scope
Exact APIs: staticOperatorResolution. Actual calls 5. Explicit lexical assumptions/Core protocol/member/traitarity/arity and controlled names/canonical views only; preserve authored supertrait path/depth and no expression solver.

functionBoundAssumptions emits Function and MethodReceiver only; retain exact lexical owner/ParamId, Core trait/member/trait arity(default0) and operator arity, canonical view stripping/name interning and authored supertrait path/depth. No expression rank/ArgRange fabrication/proof query/admission/interface/source evidence or keyword/bare memo writer on this specialized route.

## Completion
Change concrete signatures and every actual consumer; no facade retaining fullComp/capture. Relevant behavior/structural controls and independent review including restoration, identity and prefixes. Product implementation/GREEN separate from this substantive investigation. Preserve complete per-entry source/domain/pool/trait/view/ParamId/proof/environment/default/guard/error and lifetime contract, no unrelated Comp access via wrapper/capture. Actual success-only legacy restore gaps are observed, not a replacement for adopted all-exit temporary scope design. Relevant positive/reject/boundary/noninterference/failure controls and independent structural review/gates remain future product work.

Preserve exact actual caller and source/session/type/proof/pool lifetimes, ordering/defaults, diagnostic provenance, legitimate mutation and error prefixes in the pinned answer. A wrapper or callback retaining unrelated whole compiler authority is not a narrowing. Readonly grants are not writers. Cover relevant normal, rejected, boundary and failure-prefix controls, verify the real producer-to-final-consumer path and remove competing broad signatures. No statement of future GREEN is evidence that the repair has passed.

## Excluded
Other repair groups and original J/C/O/optional/other U scopes; language/source/solver/general selection or proof algorithm redesign, product execution/performance/GREEN within this audit.


