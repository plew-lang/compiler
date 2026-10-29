---
id: com-qadp
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T19:04:13Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow source navigation and nominal metadata inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/selected-instance-and-proof-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-selected-instance-and-proof-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Only named C subset: source AST/span/building-term writer for retarget; saved ChainSite reader; gen prepared reader/demand writer with unused start/len removal; intrinsic head/bytes, boxed-offset set; nominal field/name alias interner bridge; canonical projection/view/Self publisher and readonly unifier where actual. No general grounding/proof/instance/body or executable grant.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-chain-hole-navigation-and-synthetic-type-publication: ['retargetChainHole', 'recordSyntheticExprType']
- codegen-chain-site-layout-dependency-registration: ['chainSiteFor']
- codegen-associated-function-spelling-index-reader: ['findAssocByName']
- codegen-generation-binding-use-global-demand-adapter: ['scanBindingInsts']
- codegen-intrinsic-type-head-and-generic-predicates: ['isFnType/isRefInst/isMutableRefInst/isStrongRefInst/isStrongRefCellInst/isWeakRefInst/isWeakMutableRefInst/isWeakRefLikeInst/isWeakRefCellInst/isRawBufInst']
- codegen-boxing-container-boundary-classification: ['isIndirectContainer', 'isTransparentContainer']
- codegen-boxed-field-membership-query: ['fieldIsBoxed']
- codegen-nominal-selected-field-descriptor-query: ['findFieldDef']
- codegen-runtime-view-and-plain-projection-type-adapters: ['runtimeTypeRef', 'plainRefOfProjection']
- codegen-extension-proof-source-activity-query: ['proofSourceIsActive']
- codegen-trait-subject-edge-witness-substitution: ['traitSubjectWitnessMatch']
- codegen-trait-proof-source-owner-filtering: ['traitProofStateMatchesSources', 'traitProofMatchesSources']
- codegen-generic-enum-instantiation-classification: ['isGenericEnumInst']

## Actions and Completion
Change the exact real signatures/services and every actual source/fixture consumer to the named closed boundary. Preserve all per-row legitimate effects/defaults/errors/identity/caches/lifetime/restore, remove unrelated raw Comp/unwrap/callback escapes, use task-start TDD/refactor controls and independent structural review, and run appropriate repair validation. An interface proposal alone does not complete this repair follow-up.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
No product repair/execution in this audit; no whole solver/source-selection/equality/algorithm correctness certification, language change, runtime/native/macro execution, whole-compiler architectural redesign or speculative performance proof.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

