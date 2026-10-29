---
id: com-ozkj
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T19:04:13Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Determine grounding body environment inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/selected-instance-and-proof-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-selected-instance-and-proof-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Close only these named type/recipe/environment/front services: exact source/body/ParamId/receiver/selected proof/Self/Item/namespace and source-ready reader inputs; identify canonical/type/name/proof/condition/result cache/cursor/layout writes, trace and both-result restore owners. Decide explicit service versus coherent owner per API without certifying algorithm correctness.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-declaration-closure-capture-identity-registration: ['recordDeclarationCapture']
- codegen-enum-repack-declaration-payload-boundary-grounding: ['enumRepackPayloadBoundaries']
- codegen-existential-requirement-explicit-bound-construction: ['existentialRequirementBound']
- codegen-existential-requirement-public-signature-grounding: ['existentialRequirementSignature']
- codegen-recorded-body-value-type-grounding: ['groundRecordedValueTypeForBody']
- codegen-final-call-argument-source-type-vector: ['finalCallArgumentTypes']
- codegen-body-owned-semantic-type-recipe-evaluation-and-publication: ['groundSemanticTypeRecipe', 'groundSemanticTypeRecipeForBody', 'evaluateSemanticTypeRecipeForBody']
- codegen-for-statement-semantic-recipe-finalization: ['finalizeForTypeRecipes']
- codegen-selected-function-body-receiver-normalization: ['canonicalBodyReceiverRef']
- codegen-current-body-protocol-template-and-selection: ['protocolTemplateForCurrentBody', 'selectedProtocolTemplateCall']
- codegen-protocol-and-call-template-receiver-grounding: ['groundedProtocolTemplateReceiver', 'groundCallTemplateReceiver']
- codegen-selected-callee-explicit-environment-signature-grounding: ['groundedSelectedCalleeReturn', 'groundedSelectedCalleeParameterTypes']
- codegen-body-receiver-and-associated-namespace-signature-admission: ['bodyReceiverMatchesDeclaration', 'traitNamespaceReceiverMatches']
- codegen-selected-callable-body-environment-construction: ['bodyInstanceEnvironment']
- codegen-final-callable-cursor-environment-installation: ['enterFinalCallableEnvironment']
- codegen-recorded-call-argument-grounding: ['groundCallArgumentSource']
- codegen-selected-associated-result-hint-grounding: ['selectedResultHint']
- codegen-executable-local-declaration-type-source-consumer: ['scanLocalDeclarationType']
- codegen-prepared-existential-witness-signature-contract-check: ['checkPreparedExistentialWitnessSignature']
- codegen-final-existential-trait-identity-adapter: ['finalAnyTraitIdx']
- codegen-direct-template-selected-receiver-dependency-grounding: ['groundSelectedDirectReceiver']
- codegen-selected-direct-template-call-value-construction: ['selectDirectTemplateCall']
- codegen-selected-dynamic-template-call-value-construction: ['selectDynamicTemplateCall']

## Actions and Completion
Close the listed finite per-entry direct/delegated reader/writer/retained/identity/error/restore services. Independently decide justified/excess or retain a smaller explicitly owned question; assign any repair separately without claiming implementation GREEN.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
No product repair/execution in this audit; no whole solver/source-selection/equality/algorithm correctness certification, language change, runtime/native/macro execution, whole-compiler architectural redesign or speculative performance proof.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

