---
id: com-dsfy
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:35:24Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow Mid statement control and pattern evaluation services

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/mid-builder-consumer-services.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-mid-builder-consumer-services.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of audit closure; implementation admission is assigned below; no product repair was performed by the audit.

## Guarantee and Scope
admitted statement/transfer/pattern/type/recipe reader と common evaluation/continuation/diagnostic fronts、coherent local/scope/loop/CFG owner に限定。 Return/Give/Break/Continue exact targets、condition binding/reachability/order、source completion と CFG の区別、Storage/ReturnBoundary、Overwrite、capture/destructure/drop markers、for/try abstract recipes、sequence/default flags、failure-prefix/restore を維持。

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- mid-builder-admitted-let-and-binding-end-inputs: ['buildMidLet', 'buildMidLetAdmitted']
- mid-builder-admitted-assignment-and-overwrite-inputs: ['buildMidAssign', 'buildMidAssignAdmitted']
- mid-builder-admitted-match-statement-router: ['buildMidMatch', 'buildMidMatchAdmitted']
- mid-builder-condition-clause-sequence-inputs: ['buildMidConditionClauses']
- mid-builder-condition-chain-scope-and-join-inputs: ['buildMidConditionChain']
- mid-builder-if-shared-cfg-and-statement-inputs: ['buildMidIfCfg', 'buildMidIf', 'buildMidIfAdmitted']
- mid-builder-admitted-while-cfg-inputs: ['buildMidWhile', 'buildMidWhileAdmitted']
- mid-builder-admitted-for-protocol-recipe-inputs: ['buildMidFor', 'buildMidForAdmitted']
- mid-builder-condition-evaluation-boundary-inputs: ['materializeMidCondition']
- mid-builder-admitted-return-transfer-inputs: ['buildMidReturn', 'buildMidReturnAdmitted']
- mid-builder-lexical-block-and-give-dispatch-inputs: ['buildMidBlockInto', 'buildMidBlock']
- mid-builder-pattern-binding-snapshot-inputs: ['buildMidPatternBindings']
- mid-builder-irrefutable-pattern-scope-inputs: ['buildMidIrrefutablePattern']
- mid-builder-consuming-enum-destination-inputs: ['buildMidConsumingEnumArm']
- mid-builder-ordered-pattern-test-cfg-inputs: ['buildMidOrderedPatternMatch']
- mid-builder-frozen-match-strategy-and-subject-inputs: ['buildMidPatternMatch']
- mid-builder-pattern-continuation-and-discriminant-input: ['buildMidPatternContinuation', 'midDiscriminantType']

## Actions and Completion
Change the actual consumer and provider interfaces to scoped closed services, preserving every named mutable effect and all actual source/fixture callers. Independently verify that no raw Comp reader/writer/unwrap/callback escape retains unrelated authority. Coordinate shared services once rather than duplicate implementations. source pattern/exhaustiveness/typechecking、ownership/drop analysis、CFG algorithm 全正当性や executable success の認定に拡張しない。46 の pure count は変更不要で discriminant は scalar front。 各 exact fact の列挙済み typed production/fixture consumers と、変更対象 API の全 actual source consumers。固定 callsite 件数や代表例だけを完全一覧とは扱わない。

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other compiler domains, source meaning/algorithm changes, all product edits/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Adopted Implementation Intake

[com-ptko](com-ptko.md) classifies the exact confirmed scope as required existing-feature phase3 conformance. Required admission owner(s): com-fuo8, met-acfl; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-mid-and-lowering.json) retains all main/mixed roles and normative grounds. Admitted statements, condition chains, patterns and transfer lowering consume successful source completion and exact Return/Give/Break/Continue targets. The closure spans source publication to final CFG/cleanup consumption; preserve normal-value versus no-continuation and local/scope owner semantics.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
