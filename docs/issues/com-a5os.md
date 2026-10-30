---
id: com-a5os
status: closed
deps: []
links: [com-mmk9]
created: 2026-10-29T19:04:13Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Determine selected proof and public constraint replay inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/selected-instance-and-proof-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-selected-instance-and-proof-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Only named U components: exact declaration clause/selected path/provided source/environment/prepared constraints, interface versus static interpretation and first concrete demand. Map required type/name/proof/condition/normalization/associated evidence/cache/trace writes and restoration. No new overload/proof replacement or executable-ready inference; unused formal C subsets stay separate.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-selected-witness-replay-and-concrete-proof-completeness: ['groundSelectedWitness', 'concreteStaticMemberProof']
- codegen-bound-first-concrete-proof-instantiation: ['instantiateBoundProof']
- codegen-selected-path-root-and-edge-instantiation: ['groundSelectedTraitPath']
- codegen-static-member-proof-explicit-instantiation-dispatch: ['instantiateStaticMemberProof']
- codegen-retained-authored-supertrait-constraint-instantiation: ['instantiateSupertraitConstraint']
- codegen-retained-constraint-proof-prefix-selection: ['retainedConstraintPrefix']
- codegen-body-receiver-constraint-retained-proof-instantiation: ['instantiateReceiverConstraint']
- codegen-associated-constraint-prerequisite-instantiation: ['instantiateAssociatedConstraint']
- codegen-concrete-declaration-bound-proof-instantiation: ['instantiateConcreteConstraintProof']
- codegen-ambient-body-call-constraint-adapter: ['instantiateBodyCallConstraints']
- codegen-first-concrete-source-admission-uniqueness-check: ['checkFirstConcreteSourcePath']
- codegen-selected-call-public-constraint-proof-replay: ['instantiateSelectedCallConstraints']
- codegen-selected-member-public-constraint-evidence-routing: ['selectedMemberConstraintEvidence']
- codegen-selected-call-constraint-operation-routing: ['selectedCallConstraintEvidence']
- codegen-requirement-implementation-entailment-evidence-packaging: ['requirementCallConstraintEvidence']
- codegen-selected-access-writeback-finalization-closure: ['finalizeAccessWriteFacets']
- codegen-static-proof-interpretation-and-selected-clause-replay: ['instantiateConstraintProof', 'instantiateSelectedSupertraitConstraint remaining selected replay', 'instantiateSelectedAssociatedConstraint']
- codegen-selected-witness-condition-and-projection-replay: ['replaySelectedWitness']
- codegen-interface-versus-concrete-proof-replay-frontier: ['replayConstraintProof']
- codegen-interface-bound-path-and-witness-rebasing: ['rebaseInterfaceBound', 'rebaseInterfaceSupertrait', 'rebaseInterfaceWitness', 'rebaseInterfaceProof']

## Actions and Completion
Close the listed finite per-entry direct/delegated reader/writer/retained/identity/error/restore services. Independently decide justified/excess or retain a smaller explicitly owned question; assign any repair separately without claiming implementation GREEN.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
No product repair/execution in this audit; no whole solver/source-selection/equality/algorithm correctness certification, language change, runtime/native/macro execution, whole-compiler architectural redesign or speculative performance proof.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Input Investigation Outcome

The original required input/delegate-authority questions are answered, not merely
assigned elsewhere. [Exact answer](../../../evidence/compiler-api-audit/resolutions/selected-proof-service-inputs.json)
and [independent review](../../../evidence/compiler-api-audit/review-resolution-selected-proof-service-inputs.json)
record the complete named scope, necessary inputs/effects, actual caller contexts,
source identity and supported C conclusion. Required input questions remaining
in this scope: none. Product repairs remain unimplemented and unverified.

Repair ownership: [com-ct0w](com-ct0w.md), [com-0htd](com-0htd.md), [com-kt7y](com-kt7y.md), [com-eatt](com-eatt.md). These repair issues are not evidence of the conclusion; the linked
source closure and independent review are. This closes only this finite
investigation, not com-mmk9 or any product implementation milestone.
