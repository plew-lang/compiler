---
id: com-6vcb
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:53:37Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Determine selected callable inference / signature / instance demand closure

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-query-and-module-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-query-and-module-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
selected Func/receiver/proof/retained args、argument type/matching、public interface signature、provided Item/trait Self/groundnessとbody-callee registry需要までのnamed servicesを調べる。 binder order/ParamId/retained proof、defaults Missing/[]/constraints None、symbolic nonzero versus groundness、bodyCalleeIndexがcur.bodyId=0でBodyInstance/BodySignature/owner indexesを登録しcur.bodyIdを更新する効果、final evidence/type caches、scanType demandsとdiagnosticsを保存。

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-call-receiver-self-and-bare-qualifier-normalization: ['callReceiverTerm']
- codegen-selected-method-inference-environment-construction: ['inferMethodEnvironment']
- codegen-final-method-inference-completeness-gate: ['finalMethodEnvironment']
- codegen-selected-provided-item-associated-output-query: ['finalMethodItemRef']
- codegen-selected-method-signature-type-grounding: ['groundFinalMethodSignatureTerm', 'groundFinalMethodSignatureInEnvironment']
- codegen-associated-receiver-from-complete-call-argument-inference: ['associatedReceiverFromArguments']
- codegen-method-return-and-parameter-signature-grounding-adapters: ['groundFinalMethodReturn / groundFinalMethodParameter: shared signature query closure']
- codegen-static-provided-environment-and-call-result-projection: ['staticProvidedCallEnvironment', 'staticMemberCallResultType']
- codegen-bound-method-result-signature-query: ['boundMethodRetInfo: remaining query / whole Comp']
- codegen-existential-selected-requirement-result-typeinfo: ['anyMemberRetInfo']
- codegen-selected-call-type-argument-inference: ['inferFnArgs', 'fnArgsAllGround']
- codegen-selected-final-call-instance-demand: ['registerCallInst: final-argument/body registry/groundness services', 'registerMethodInst: selected receiver / scanType / final-result services']

## Actions and Completion
For confirmed scopes change exact actual signatures and all actual consumers, retain necessary mutable service effects, remove raw Comp/unwrap/callback escapes and verify with TDD/refactor controls plus independent review. For unresolved scopes deliver exact direct/delegated closure and supported verdict/finite followups. exact factのtyped source/fixture contextsを起点に、当該affected APIsの全actual consumers。高fanoutの代表例を固定callsite件数や完全一覧にしない。

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other domains, source/algorithm/ABI changes, optional passive payload shrinking, product repair/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

