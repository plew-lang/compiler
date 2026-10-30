---
id: com-duny
status: open
deps: []
links: [com-mmk9]
created: 2026-10-30T14:14:28Z
type: task
priority: 2
assignee: Koji Murata
tags: [verification, frontend]
---
# Narrow retained selected environment reader inputs

Evidence: [input-authority answer](../../../evidence/compiler-api-audit/resolutions/source-selected-environment-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-resolution-source-selected-environment-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This issue owns product repair; implementing it is not a prerequisite for the source-only input investigation.

## Guarantee and Scope
Exact APIs: recordedDirectCallEnvironmentAt, recordedDirectCallEnvironmentForExpression, recordedDirectCallEnvironment. Actual calls 12. Saved source location/session/owner and selected Func/receiver/typeArgs/proof interpreter; readonly operation/catalogue/type/proof pools, lexical Self name/interner/owned env; stderr only trace adapters. No inference/query/type publisher or cur write.

At/ForExpression/plain Direct environment readers preserve exact site/session/owner and selected Func/receiver/typeargs/proof, bound count/completeness and mismatch errors. Lexical Self name/interner+owned env and actual trace stderr retained only proper adapters. No Q/proof publication/typepublisher/cur writer imported from caller or fallback.

## Completion
Change actual signatures/all exact source+fixture consumers and necessary narrow reader/publisher/trace helpers, not wrapper/capture retaining broad Comp/raw mutable Arena. Preserve per-entry real defaults/owner/ParamId/proof/lifetime/diagnostic/error/prefix and adopted all-exit temporary scope design. Relevant behavior/structural controls and independent review/gates are separate future implementation. No input question delegated unresolved. Preserve per-entry source/domain/owner/ParamId/proof/environment/default/guard/error/lifetime distinction, no broad Comp through captured facade. Current legacy success-only restoration gaps are observations; all-exit temporary scope restoration is the adopted endpoint, valid persistent query prefix remains.

Preserve exact actual caller and source/session/type/proof/pool lifetimes, ordering/defaults, diagnostic provenance, legitimate mutation and error prefixes in the pinned answer. A wrapper or callback retaining unrelated whole compiler authority is not a narrowing. Readonly grants are not writers. Cover relevant normal, rejected, boundary and failure-prefix controls, verify the real producer-to-final-consumer path and remove competing broad signatures. No statement of future GREEN is evidence that the repair has passed.

## Excluded
Other original J/C/O/optional/API domains, source/solver/algorithm redesign, product execution/performance/GREEN.


