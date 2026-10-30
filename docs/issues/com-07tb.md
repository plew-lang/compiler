---
id: com-07tb
status: open
deps: []
links: [com-mmk9]
created: 2026-10-30T14:14:28Z
type: task
priority: 2
assignee: Koji Murata
tags: [verification, frontend]
---
# Narrow saved and unselected source call environment inputs

Evidence: [input-authority answer](../../../evidence/compiler-api-audit/resolutions/source-selected-environment-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-resolution-source-selected-environment-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This issue owns product repair; implementing it is not a prerequisite for the source-only input investigation.

## Guarantee and Scope
Exact APIs: callParameterEnvironment. Actual calls 6. Distinct saved first and legally unselected supplied-argument constructor. Keep bounded wide semantic inference/cache/proof/layout/typecollection/body-ID/frame/trace only fallback, reject saved incomplete/mismatch/selected other kind. No source preparation/publication/executable demand.

Saved-first callParameterEnvironment: matching complete Direct environment returns; saved Direct invalid/incomplete/mismatch Err and selected nonDirect no-retry Err; only absent/Pending/ExpectedValue allows supplied-argument construction. Bounded full inference/cache/ground/proof/layout/typecollection/bodyidentity/frame/trace effects belong only that actual fallback. No source preparation/publication/final executable demand.

## Completion
Change actual signatures/all exact source+fixture consumers and necessary narrow reader/publisher/trace helpers, not wrapper/capture retaining broad Comp/raw mutable Arena. Preserve per-entry real defaults/owner/ParamId/proof/lifetime/diagnostic/error/prefix and adopted all-exit temporary scope design. Relevant behavior/structural controls and independent review/gates are separate future implementation. No input question delegated unresolved. Preserve per-entry source/domain/owner/ParamId/proof/environment/default/guard/error/lifetime distinction, no broad Comp through captured facade. Current legacy success-only restoration gaps are observations; all-exit temporary scope restoration is the adopted endpoint, valid persistent query prefix remains.

Preserve exact actual caller and source/session/type/proof/pool lifetimes, ordering/defaults, diagnostic provenance, legitimate mutation and error prefixes in the pinned answer. A wrapper or callback retaining unrelated whole compiler authority is not a narrowing. Readonly grants are not writers. Cover relevant normal, rejected, boundary and failure-prefix controls, verify the real producer-to-final-consumer path and remove competing broad signatures. No statement of future GREEN is evidence that the repair has passed.

## Excluded
Other original J/C/O/optional/API domains, source/solver/algorithm redesign, product execution/performance/GREEN.


