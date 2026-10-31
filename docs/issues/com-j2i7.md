---
id: com-j2i7
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T19:04:13Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow matching stores and value equality inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/selected-instance-and-proof-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-selected-instance-and-proof-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of audit closure; implementation admission is assigned below; no product repair was performed by the audit.

## Guarantee and Scope
Explicit typed values/ranges/IDs plus matching coherent Arena/Decls readonly canonical/proof/condition/source-root pools or the exact owned descriptor/index/evidence/serializer publisher. Source-root/path bound projection may need narrow canonical Self/name publisher and session root checks. Preserve tag/hash/serialization/order/defaults and pool lineage; no solver/admission/body/Mid/source builder.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-final-dependency-frontier-presence-reader: ['hasFinalDependencies']
- codegen-final-existential-endpoint-index-reader: ['finalExistentialIndex']
- codegen-final-aggregate-fact-index-and-upsert: ['rebuildFinalAggregateIndex', 'ensureFinalAggregateIndex', 'finalAggregateIndex', 'putFinalAggregate']
- codegen-final-storage-fact-index-and-upsert: ['rebuildFinalStorageIndex', 'ensureFinalStorageIndex', 'finalStorageIndex', 'putFinalStorage']
- codegen-final-return-fact-index-and-upsert: ['rebuildFinalReturnIndex', 'ensureFinalReturnIndex', 'finalReturnIndex', 'putFinalReturn']
- codegen-final-await-fact-index-and-upsert: ['rebuildFinalAwaitIndex', 'ensureFinalAwaitIndex', 'finalAwaitIndex', 'putFinalAwait']
- codegen-final-try-fact-index-and-upsert: ['rebuildFinalTryIndex', 'ensureFinalTryIndex', 'putFinalTry']
- codegen-final-for-fact-index-and-upsert: ['rebuildFinalForIndex', 'ensureFinalForIndex', 'putFinalFor']
- codegen-final-match-fact-hash-index-and-upsert: ['finalMatchHash', 'rebuildFinalMatchIndex', 'ensureFinalMatchIndex', 'finalMatchIndex', 'putFinalMatch']
- codegen-final-source-result-and-carrier-projection-contract: ['callResultProjectionIsValid']
- codegen-final-call-body-and-signature-environment-identity-checks: ['bodySignatureReceiverMatches']
- codegen-semantic-proof-freeze-thaw-and-conversion-tag-adapters: ['freezeStaticConformanceProof', 'freezeValueConversionProof', 'thawStaticConformanceProof', 'thawValueConversionProof', 'conversionProofIsIdentity', 'conversionProofIsMissing']
- codegen-closure-body-key-and-semantic-receiver-equality: ['closureBodyKey', 'sameBodyRuntimeRef', 'sameBodyReceiver']
- codegen-static-proof-presence-and-substitution-equality: ['proofIsMissing', 'sameWitnessSubstitution', 'sameProofTerms']
- codegen-witness-condition-and-static-proof-structural-equality: ['sameSupertraitSteps', 'sameStaticConformanceProof', 'sameWitnessMatch']
- codegen-selected-witness-replay-and-concrete-proof-completeness: ['selectedWitnessTypesAreClosed']
- codegen-semantic-body-instance-complete-environment-equality: ['sameInstanceEnvironment']
- codegen-final-call-payload-copy-readers: ['copyFinalCalleeTypeArgs', 'copyFinalCalleeParameterTypes', 'copyFinalCalleeConversions', 'copyFinalCalleeArgumentPassings']
- codegen-published-nonstatic-selection-equality: ['samePublishedNonStaticSelection']
- codegen-call-target-and-intrinsic-tag-equality: ['sameCallTarget', 'sameNumericIntrinsic', 'sameNumericConversionIntrinsic', 'sameBufferIntrinsic', 'sameNumericWidth', 'sameNumericOverflow', 'sameFloatWidth', 'sameIntegerOperation', 'sameFloatOperation', 'sameBoolOperation']
- codegen-call-result-projection-equality: ['sameCallResultProjection']
- codegen-final-type-and-conversion-proof-structural-equality: ['sameResolvedTypeRefs', 'sameValueConversionProof', 'sameValueConversionProofs', 'sameFrozenValueConversionProofs']
- codegen-selected-callable-receiver-and-argument-passing-projection: ['selectedReceiverPassing', 'selectedArgumentPassings']
- codegen-call-passing-mode-equality: ['sameCallReceiverPassing', 'sameCallArgumentPassings']
- codegen-published-static-call-resolution-equality: ['sameStaticCallResolution']
- codegen-selected-constraint-terminal-witness-tag-reader: ['selectedConstraintWitness']
- codegen-trait-proof-argument-origin-and-state-equality: ['sameProofTraitArgs', 'sameTraitProofOrigin', 'traitProofStateSeen', 'traitProofPathContains']
- codegen-trait-proof-state-to-static-evidence-value: ['traitProofStateEvidence']
- codegen-conformance-proof-query-to-required-diagnostic-adapter: ['requireConformanceProof']
- codegen-associated-bound-evidence-deduplicating-publication: ['registerAssociatedBoundEvidence']
- codegen-source-proof-root-and-path-query-local-equivalence: ['sameSourceProofRoot', 'sameSourceProofPath']
- codegen-trait-proof-selection-result-projection: ['finishTraitProofSelection']
- codegen-member-dispatch-proof-endpoint-comparison: ['sameMemberProofEndpoint']
- codegen-canonical-recursive-type-equality: ['typeRefEq']

## Actions and Completion
Change the exact real signatures/services and every actual source/fixture consumer to the named closed boundary. Preserve all per-row legitimate effects/defaults/errors/identity/caches/lifetime/restore, remove unrelated raw Comp/unwrap/callback escapes, use task-start TDD/refactor controls and independent structural review, and run appropriate repair validation. An interface proposal alone does not complete this repair follow-up.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
No product repair/execution in this audit; no whole solver/source-selection/equality/algorithm correctness certification, language change, runtime/native/macro execution, whole-compiler architectural redesign or speculative performance proof.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Adopted Implementation Intake

[com-4sg9](com-4sg9.md) classifies the exact confirmed scope as required existing-feature phase3 conformance. Required admission owner(s): met-ia09, met-6e6k, met-acfl; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-selected-instances.json) retains all main/mixed roles and normative grounds. Final facts/indexes/serializers and exact selected proof/identity/result/passing comparisons retain closed source evidence into instances. Narrow each readonly value/range operation or exact publisher without a solver/source builder or whole mutable compiler.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
