---
id: com-e6zm
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T19:04:13Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow final call argument signature readers inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/selected-instance-and-proof-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-selected-instance-and-proof-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Matching final body/site/call/signature/source/interface readers plus narrow body registry/cache, canonical runtime-view publisher, keyword/name cache, argument/descriptor/result-recipe/finalFor/signature/local append stores as named per row. Keep duplicate/false/absent diagnostics, physical range lineage and prefix writes; no proof solver or source selection.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-existential-witness-adapter-signature-publication: ['prepareExistentialWitnessSignature']
- codegen-final-for-protocol-layout-publication: ['freezeForResolution']
- codegen-recorded-call-argument-navigation-and-pool-adapters: ['callArgumentExprId', 'callArgumentRangeForCurrentBody', 'templateArgumentRange', 'templateArgumentRangeFromValues', 'operatorTemplateArgs']
- codegen-current-body-identity-and-call-site-key-adapters: ['currentBodyInstanceId', 'currentCallSiteKey']
- codegen-final-call-evaluation-argument-preparation-and-comparison: ['prepareFinalCalleeArguments', 'sameFinalCalleeArguments']
- codegen-final-call-validated-publication-gateway: ['appendFinalCallee']
- codegen-body-site-final-call-index-with-interface-validation: ['bodyCalleeIndex']
- codegen-instance-invariant-callee-cache-reader: ['cachedInvariantCallee']
- codegen-final-call-receiver-result-and-signature-payload-readers: ['bodyCalleeReceiverRef', 'selectedCallReceiverRef', 'bodyCalleeResultRef', 'bodyCalleeTypeArgs', 'bodyCalleeParameterTypeRefs']
- codegen-final-match-payload-type-by-binding-reader: ['finalMatchPayloadTypeRef']
- codegen-final-pattern-local-binding-from-grounded-facts: ['scanAddFinalMatchArmBinds', 'scanAddFinalPatternBinds']
- codegen-selected-declaration-runtime-target-tag-projection: ['runtimeIntrinsicTarget', 'callTargetIsDirect']
- codegen-final-call-target-and-body-navigation-projections: ['bodyCalleeTargetKind', 'bodyCalleeTargetTraitIdx', 'bodyCalleeTargetSlot', 'bodyCalleeTargetTypeRef', 'bodyCalleeBodyId', 'bodyCalleeTargetBindingDeclStart', 'bodyCalleeTargetPart']

## Actions and Completion
Change the exact real signatures/services and every actual source/fixture consumer to the named closed boundary. Preserve all per-row legitimate effects/defaults/errors/identity/caches/lifetime/restore, remove unrelated raw Comp/unwrap/callback escapes, use task-start TDD/refactor controls and independent structural review, and run appropriate repair validation. An interface proposal alone does not complete this repair follow-up.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
No product repair/execution in this audit; no whole solver/source-selection/equality/algorithm correctness certification, language change, runtime/native/macro execution, whole-compiler architectural redesign or speculative performance proof.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

