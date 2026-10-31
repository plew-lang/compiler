---
id: com-v7fu
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:35:24Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Separate prepared Mid body requests and canonical cache ownership

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/mid-builder-consumer-services.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-mid-builder-consumer-services.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of audit closure; implementation admission is assigned below; no product repair was performed by the audit.

## Guarantee and Scope
same-session prepared function/closure/global request、canonical store/check と closure/template registry を一つの制御された owner front にする。internal Comp を維持しても mutable Comp/arena/source directory の外部 escape、unwrap、Comp を渡す callback は許さない。 function/closure/global、cache hit/miss/failure と measured reader acquisition、synthetic/global owner、foreign session pairing、canonical IDs/structural checks、capture owner/lifetime/default を維持する。

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- mid-builder-parametric-function-body-inputs: ['buildParametricMidBody']
- mid-builder-parametric-closure-body-inputs: ['buildParametricMidClosureBody']
- mid-builder-prepared-closure-canonical-cache-inputs: ['ensureParametricMidClosureBody', 'ensurePreparedParametricMidClosureBody']
- mid-builder-composite-global-initializer-inputs: ['buildParametricMidGlobalInit']
- mid-builder-function-template-cache-construction-inputs: ['globalInitializer', 'body']
- mid-builder-closure-value-and-parametric-registration-inputs: ['materializeMidClosureValue']

## Actions and Completion
Change the actual consumer and provider interfaces to scoped closed services, preserving every named mutable effect and all actual source/fixture callers. Independently verify that no raw Comp reader/writer/unwrap/callback escape retains unrelated authority. Coordinate shared services once rather than duplicate implementations. private owner の具体的配置と cache の session association は実装で選ぶ。現 caller が foreign reuse していると断定せず、source-only facts から runtime bug を認定しない。 各 exact fact の列挙済み typed production/fixture consumers と、変更対象 API の全 actual source consumers。固定 callsite 件数や代表例だけを完全一覧とは扱わない。

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other compiler domains, source meaning/algorithm changes, all product edits/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Adopted Implementation Intake

[com-ptko](com-ptko.md) classifies the exact confirmed scope as required existing-feature phase3 conformance. Required admission owner(s): met-acfl; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-mid-and-lowering.json) retains all main/mixed roles and normative grounds. Function/closure/global parametric body requests expose a controlled same-session owner front consuming strong published source facts. Preserve cache/failure/source owner/lifetime and canonical registry behavior, with internal Comp private and no unwrap/callback escape.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
