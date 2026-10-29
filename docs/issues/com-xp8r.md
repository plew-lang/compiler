---
id: com-xp8r
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T19:04:13Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow trace formatting inputs inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/selected-instance-and-proof-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-selected-instance-and-proof-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Immutable type/name/function/body descriptor views, explicit trace policy and stderr sink only. Remove traceProvidedFinalCallee args formal while preserving caller computation effects; render/order/gating stays unchanged.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-monomorphization-type-and-provided-callee-trace-formatters: ['traceMonoTypeHead', 'traceProvidedFinalCallee']
- codegen-final-body-instance-fanout-diagnostic: ['traceFinalBodyInstanceSummary']
- codegen-incomplete-final-static-call-diagnostic-trace: ['traceIncompletePublishedStaticCallee']

## Actions and Completion
Change the exact real signatures/services and every actual source/fixture consumer to the named closed boundary. Preserve all per-row legitimate effects/defaults/errors/identity/caches/lifetime/restore, remove unrelated raw Comp/unwrap/callback escapes, use task-start TDD/refactor controls and independent structural review, and run appropriate repair validation. An interface proposal alone does not complete this repair follow-up.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
No product repair/execution in this audit; no whole solver/source-selection/equality/algorithm correctness certification, language change, runtime/native/macro execution, whole-compiler architectural redesign or speculative performance proof.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

