---
id: com-n5lu
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:35:24Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow selected Mid call place and argument evaluation services

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/mid-builder-consumer-services.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-mid-builder-consumer-services.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of audit closure; implementation admission is assigned below; no product repair was performed by the audit.

## Guarantee and Scope
readonly saved-call/place/type/AST navigation と制御された recursive Mid evaluation/access/canonical-provider/literal/type-normalization/diagnostic fronts、coherent draft owner を渡す。 exact keys/modes/evaluationOrder/parameter order、one-time base/index/reference evaluation、strong owner temp/projection range lineage、access-marker lane、no-continuation/error、cache/scope restore、normalized call representation と trace を維持。

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- mid-builder-prior-call-receiver-inputs: ['midPriorCallReceiver']
- mid-builder-direct-receiver-mode-adaptation-inputs: ['midCallReceiver']
- mid-builder-source-receiver-provenance-inputs: ['midSourceCallReceiver']
- mid-builder-call-evaluation-scope-and-completion-inputs: ['buildMidCallInto']
- mid-builder-selected-call-input-order-and-cfg-inputs: ['buildMidCallEvaluation']
- mid-builder-source-place-projection-inputs: ['midPlaceForSourceExpr']
- mid-builder-flat-projection-and-inout-place-inputs: ['midNormalizedInoutPlaceForSourceExpr']
- mid-builder-normalized-reference-owner-inputs: ['midNormalizedReferenceArgument']
- mid-builder-access-occurrence-preparation-inputs: ['midPrepareAccessValue', 'midPrepareAccessPlace', 'midAccessOwner', 'midPrepareAccess']
- mid-builder-template-inout-argument-inputs: ['midTemplateInoutCallArgument']
- mid-builder-evaluated-index-place-inputs: ['materializeMidIndexValue']
- mid-builder-reference-owner-place-materialization-inputs: ['materializeMidReferencePlace']
- mid-builder-index-operand-to-local-inputs: ['midIndexLocalForSourceExpr']
- mid-builder-selected-template-argument-value-inputs: ['midTemplateArgumentOperand']

## Actions and Completion
Change the actual consumer and provider interfaces to scoped closed services, preserving every named mutable effect and all actual source/fixture callers. Independently verify that no raw Comp reader/writer/unwrap/callback escape retains unrelated authority. Coordinate shared services once rather than duplicate implementations. coherent MidBuildState を helper ごとに全分割する要求ではない。shared evaluator/provider front は other Mid followups と一つの実装にできる。 各 exact fact の列挙済み typed production/fixture consumers と、変更対象 API の全 actual source consumers。固定 callsite 件数や代表例だけを完全一覧とは扱わない。

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other compiler domains, source meaning/algorithm changes, all product edits/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Adopted Implementation Intake

[com-ptko](com-ptko.md) classifies the exact confirmed scope as required existing-feature phase3 conformance. Required admission owner(s): met-ucze, com-fuo8, met-6e6k; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-mid-and-lowering.json) retains all main/mixed roles and normative grounds. Selected call/place/receiver and access lowering consumes fixed source selection, evaluation order and modes through final temporaries and CFG. Preserve one-time base/index evaluation, strong owner lifetimes, projections and no-continuation; it cannot select source calls again.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
