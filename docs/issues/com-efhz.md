---
id: com-efhz
status: closed
deps: []
links: [com-mmk9]
created: 2026-10-29T18:53:37Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Determine ranked callable / view source query closure

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-query-and-module-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-query-and-module-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
free/method/associated/view-source selectionのlisted rank/receiver/proof/type query delegatesを、written module/source owner/visibility/gen policyとselected binder contextに分けて必要入力を確定する。 argument label/order/defaults、inherent/provided/origin ambiguity、required trait/surface newtype、sourceIdとtraitOwner、strip/static/lexical view、typeOf/typedLocal/global TYPE forcing、cursor/cache/interner/proof/error/trace effectsを保存。semantic priority/visibility algorithmの正誤認定は範囲外。

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-free-function-argument-ranked-selection-and-generator-fallback: ['findFunc']
- codegen-bare-method-and-provided-associated-call-selection: ['findMethod']
- codegen-single-source-extension-method-name-adapter: ['findExtMethod']
- codegen-written-view-source-semantic-key-resolution: ['resolveViewSourceKey']
- codegen-expression-and-static-type-view-source-collection: ['collectViewSources']
- codegen-concrete-receiver-final-method-query: ['resolveMethodForResolvedReceiver']
- codegen-concrete-receiver-final-associated-query: ['resolveAssocForResolvedReceiver: remaining selection / whole Comp']
- codegen-view-set-common-method-and-associated-selection: ['findCallableInViewSet']
- codegen-view-set-method-and-associated-selection-adapters: ['findMethodInViewSet', 'findAssocInViewSet']
- codegen-written-extension-view-final-call-query: ['resolveExtMethodFinal']
- codegen-ordinary-method-final-query-and-explicit-type-adapter: ['resolveMethodFinal', 'resolveMethodFinalForType']
- codegen-single-semantic-source-method-selection: ['findExtMethodById', 'findExtMethodBySource']
- codegen-bare-associated-callable-ranked-selection: ['findAssoc']

## Actions and Completion
For confirmed scopes change exact actual signatures and all actual consumers, retain necessary mutable service effects, remove raw Comp/unwrap/callback escapes and verify with TDD/refactor controls plus independent review. For unresolved scopes deliver exact direct/delegated closure and supported verdict/finite followups. exact factのtyped source/fixture contextsを起点に、当該affected APIsの全actual consumers。高fanoutの代表例を固定callsite件数や完全一覧にしない。

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other domains, source/algorithm/ABI changes, optional passive payload shrinking, product repair/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Input Investigation Outcome

The original required input/delegate-authority questions are answered, not merely
assigned elsewhere. [Exact answer](../../../evidence/compiler-api-audit/resolutions/ranked-lookup-inputs.json)
and [independent review](../../../evidence/compiler-api-audit/review-resolution-ranked-lookup-inputs.json)
record the complete named scope, necessary inputs/effects, actual caller contexts,
source identity and supported C conclusion. Required input questions remaining
in this scope: none. Product repairs remain unimplemented and unverified.

Repair ownership: [com-79k3](com-79k3.md), [com-q8eb](com-q8eb.md), [com-13js](com-13js.md). These repair issues are not evidence of the conclusion; the linked
source closure and independent review are. This closes only this finite
investigation, not com-mmk9 or any product implementation milestone.
