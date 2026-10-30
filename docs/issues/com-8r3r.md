---
id: com-8r3r
status: in_progress
deps: []
links: [com-mmk9]
created: 2026-10-29T19:04:14Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Determine condition proof query services inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/selected-instance-and-proof-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-selected-instance-and-proof-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Finite exact query/condition/projected/output services only: demand/trait args/assumptions/views/preferred source/path/root/associated output and candidate local state. Map canonical/name/condition/proof serializer/associated evidence/legacy layout and cursor effects; preserve guard removal on both Results and persistent None/Err prefixes. Pure answer C adapter stays separate; no whole solver/algorithm soundness certification.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-assumed-trait-instance-query-local-dedup: ['assumedTraitInstanceSeen']
- codegen-selected-witness-condition-request-and-recursion-scope: ['witnessConditionsSatisfied', 'witnessWithConditions']
- codegen-conformance-condition-evidence-plan-selection: ['selectWitnessConditionEvidence']
- codegen-conformance-edge-source-precedence-query: ['witnessSourceSelected']
- codegen-trait-proof-state-condition-completion: ['completeTraitProofState']
- codegen-selected-proof-associated-output-compatibility: ['selectedProofAssociatedTypesMatch']
- codegen-conformance-proof-query-to-required-diagnostic-adapter: ['traitPatternProof']
- codegen-projected-proof-request-recursion-scope: ['queryTraitPatternProof']
- codegen-associated-projection-trait-proof-query: ['projectedTraitPatternProof']
- codegen-associated-projection-declaration-assumption-production: ['projectedTraitAssumptions']
- codegen-trait-member-instance-discovery-and-projected-extension: ['traitMemberInstanceProofs', 'projectedMemberInstanceProofs']
- codegen-associated-clause-retained-prerequisite-interpretation: ['associatedClauseBound']
- codegen-fact-proof-query-candidate-output-adapter: ['traitPatternProofFromFacts']
- codegen-shared-trait-proof-fact-search-worker: ['searchTraitPatternProofFromFacts']
- codegen-trait-proof-selection-accumulation: ['collectTraitProof']
- codegen-concrete-trait-proof-and-associated-binding-adapters: ['concreteConformanceProof', 'assocBindingFor']

## Actions and Completion
Close the listed finite per-entry direct/delegated reader/writer/retained/identity/error/restore services. Independently decide justified/excess or retain a smaller explicitly owned question; assign any repair separately without claiming implementation GREEN.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
No product repair/execution in this audit; no whole solver/source-selection/equality/algorithm correctness certification, language change, runtime/native/macro execution, whole-compiler architectural redesign or speculative performance proof.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

