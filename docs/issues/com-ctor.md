---
id: com-ctor
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T19:04:13Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow closure source readers and publisher inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/selected-instance-and-proof-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-selected-instance-and-proof-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Closure source/index/building owner domain, prepared strong payload/outcome/measurement, immutable type/origin/signature/drop readers, canonical nominal alias/name interner bridge and source diagnostics. Preserve active/inactive SourceFacts.activate transition and building/outcome failure guard; no semantic solver or body publication.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-closure-capture-representation-support-query: ['captureSupported']
- codegen-closure-capture-cell-mode-admission: ['checkedCaptureCell']
- codegen-semantic-closure-key-hash: ['semanticClosureHash']
- codegen-semantic-closure-declaration-index-read-and-rebuild: ['rebuildSemanticClosureIndex', 'ensureSemanticClosureIndex', 'semanticClosureIndex']
- codegen-closure-source-owner-building-state-guard: ['requireBuildingClosureOwner']
- codegen-semantic-closure-source-builder-and-index-publication: ['putSemanticClosure']
- codegen-closure-checked-declaration-value-publication: ['publishSemanticClosure']
- codegen-prepared-semantic-closure-plan-reader: ['preparedSemanticClosureAt']
- codegen-published-body-type-result-equality-reader: ['publishedBodyTypeMatches']
- codegen-prepared-closure-instance-signature-and-drop-authority-validation: ['requirePreparedClosureInstance']
- codegen-final-closure-call-source-selection-validation: ['checkFinalClosureCallEvidence']

## Actions and Completion
Change the exact real signatures/services and every actual source/fixture consumer to the named closed boundary. Preserve all per-row legitimate effects/defaults/errors/identity/caches/lifetime/restore, remove unrelated raw Comp/unwrap/callback escapes, use task-start TDD/refactor controls and independent structural review, and run appropriate repair validation. An interface proposal alone does not complete this repair follow-up.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
No product repair/execution in this audit; no whole solver/source-selection/equality/algorithm correctness certification, language change, runtime/native/macro execution, whole-compiler architectural redesign or speculative performance proof.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

