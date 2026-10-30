---
id: com-017t
status: open
deps: []
links: [com-mmk9]
created: 2026-10-30T13:53:10Z
type: task
priority: 2
assignee: Koji Murata
tags: [verification, frontend]
---
# Narrow Chain associated and continuation query inputs

Evidence: [input-authority answer](../../../evidence/compiler-api-audit/resolutions/source-chain-scan-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-resolution-source-chain-scan-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This issue owns product repair; implementing it is not a prerequisite for the source-only input investigation.

## Guarantee and Scope
Exact APIs: chainValueArgIndex, chainStageResultRef, typeConformsToChain. Actual calls 15. 3 Chain query families remain per-entry: associated binder/proof construction, continuation Q and interner-only nominal presence, not union grants.

Three per-entry contracts stay distinct: chainValueArgIndex retains selected symbolic binders/associated Value actual binder position and proof/query effect; chainStageResultRef preserves explicit stageHole query/default receiver term; typeConformsToChain is finite13method source name/byte/interner+localunification presence only, no keyword/proof/query/layout grant. Do not grant the union to presence predicate. Current inout Comp grants arbitrary source/AST/declaration replacement, unrelated source-owner outcomes/prepare authority, driver/config/session lifecycle and body queues beyond these finite operations. Scanner-specific saved Index rewrite and selected semantic finalization/queue are legitimate; excluding arbitrary AST writes is not excluding those required local writes. No claim Comp directly owns LlvmCtx.

## Completion
Replace actual signatures and every enumerated caller with per-entry coherent needed readers/writers; no whole Comp captures/facades. Preserve exact source/session/owner/ParamId/evidence, input defaults/order, canonical/layout/proof/reader/queue/trace and persistent failure prefix. Own temporary lexical restoration on all exits, distinguish current legacy gap; do not rollback valid derived pools. Structural independent review and future TDD/refactor gates, not product completion in this source investigation. Keep per-entry services/default/identity/guard/error/retention and complete original family under one owner; no group union or unrelated Comp capture. Actual scanner-specific finalization/Index writers remain necessary. Known lexical restore leaks are observations, not adopted design.

Preserve exact actual caller and source/session/type/proof/pool lifetimes, ordering/defaults, diagnostic provenance, legitimate mutation and error prefixes in the pinned answer. A wrapper or callback retaining unrelated whole compiler authority is not a narrowing. Readonly grants are not writers. Cover relevant normal, rejected, boundary and failure-prefix controls, verify the real producer-to-final-consumer path and remove competing broad signatures. No statement of future GREEN is evidence that the repair has passed.

## Excluded
Other original J/C/O/optional/U scopes and existing chainSiteFor/com-qadp; language/source/type/proof/ownership/finalization general algorithm redesign, product execution/repair/performance/GREEN within source audit.


