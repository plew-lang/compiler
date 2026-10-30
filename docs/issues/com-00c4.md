---
id: com-00c4
status: open
deps: []
links: [com-mmk9]
created: 2026-10-30T13:13:22Z
type: task
priority: 2
assignee: Koji Murata
tags: [verification, frontend]
---
# Narrow empty argument protocol requirement selection inputs

Evidence: [input-authority answer](../../../evidence/compiler-api-audit/resolutions/viewed-static-selection-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-resolution-viewed-static-selection-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This issue owns product repair; implementing it is not a prerequisite for the source-only input investigation.

## Guarantee and Scope
Exact APIs: selectStaticRequirement. Actual calls 1. Encode actual empty-argument protocol request/shape in signature or controlled entry; retain proof/signature/grounding, not expression authority. If general nonempty API contract retained, keep separately controlled wide expression query there; do not silently clamp input.

Exact sole actual consumer recordProtocolCallTemplate supplies pushArgs([]). Encode this shape in a controlled protocol entry; keep labels/signature/static proof/grounding, exclude expression loop authority only on this actual shape. If arbitrary nonempty declared contract is kept, retain a separate bounded wide service rather than silently clamping arguments or generalizing readonly behavior.

## Completion
Change concrete signatures and every actual consumer; no facade retaining fullComp/capture. Relevant behavior/structural controls and independent review including restoration, identity and prefixes. Product implementation/GREEN separate from this substantive investigation. Preserve complete per-entry source/domain/pool/trait/view/ParamId/proof/environment/default/guard/error and lifetime contract, no unrelated Comp access via wrapper/capture. Actual success-only legacy restore gaps are observed, not a replacement for adopted all-exit temporary scope design. Relevant positive/reject/boundary/noninterference/failure controls and independent structural review/gates remain future product work.

Preserve exact actual caller and source/session/type/proof/pool lifetimes, ordering/defaults, diagnostic provenance, legitimate mutation and error prefixes in the pinned answer. A wrapper or callback retaining unrelated whole compiler authority is not a narrowing. Readonly grants are not writers. Cover relevant normal, rejected, boundary and failure-prefix controls, verify the real producer-to-final-consumer path and remove competing broad signatures. No statement of future GREEN is evidence that the repair has passed.

## Excluded
Other repair groups and original J/C/O/optional/other U scopes; language/source/solver/general selection or proof algorithm redesign, product execution/performance/GREEN within this audit.


