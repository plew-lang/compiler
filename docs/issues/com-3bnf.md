---
id: com-3bnf
status: closed
deps: []
links: [com-mmk9]
created: 2026-10-29T17:56:18Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Determine finalized lowering and paired compilation input boundaries

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/session-and-preparation-boundaries.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-session-and-preparation-boundaries.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
At the five lowering entries and matching owner inputs, map concrete required read/write/delegate grants and same-owner pairing. Separate optional passive proof payload narrowing; identify a complete physical metadata/interner/cache/diagnostic contract before repair.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- backend-program-and-requested-module-lowering: lowerPreparedLlvm/lowerRequestedLlvm/lowerExecutableLlvm
- backend-declaration-and-global-definition-modules: lowerCallableDeclarationsLlvm/lowerGlobalStorageLlvm

## Actions and Completion
Narrow the actual APIs and all actual source/fixture consumers, preserving required data/effects and removing competing broad signatures.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Whole-backend algorithm proof, source semantics, new runtime/ABI/backend architecture, product repair or measured costs.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


 ## Input Investigation Outcome

 The original required input/delegate-authority questions are answered, not merely
 assigned elsewhere. [Exact answer](../../../evidence/compiler-api-audit/resolutions/backend-final-emission-inputs.json)
 and [independent review](../../../evidence/compiler-api-audit/review-resolution-backend-final-emission-inputs.json)
 record the complete named scope, necessary inputs/effects, actual caller contexts,
 source identity and supported C conclusion. Required input questions remaining
 in this scope: none. Product repairs remain unimplemented and unverified.

 Repair ownership: [com-6gma](com-6gma.md), [com-w1rq](com-w1rq.md), [com-s8fu](com-s8fu.md), [com-kl06](com-kl06.md), [com-hra0](com-hra0.md), [com-rib7](com-rib7.md), [com-a414](com-a414.md), [com-oaaq](com-oaaq.md). These repair issues are not evidence of the conclusion; the linked
 source closure and independent review are. This closes only this finite
 investigation, not com-mmk9 or any product implementation milestone.

