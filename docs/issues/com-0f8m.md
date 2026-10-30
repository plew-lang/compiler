---
id: com-0f8m
status: closed
deps: []
links: [com-mmk9]
created: 2026-10-29T18:13:59Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Close default value and declaration mode checker inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-default-literal-and-recovery.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-default-literal-and-recovery.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
checkFieldDefaultValue/checkParamDefaultValue/checkParamModes/checkAllParamModes only. Trace generator lexical context, literal/tcCheckValue/grounding/parametricSelfRef writers, proof/cache/failure/restore and diagnostic obligations before a narrower verdict.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-field-default-restriction-and-type-check-adapters: ['checkFieldDefaultValue']
- codegen-declared-parameter-ownership-mode-validation: ['checkParamModes', 'checkAllParamModes']
- codegen-parameter-default-restriction-and-type-check-adapters: ['checkParamDefaultValue']

## Actions and Completion
Map complete actual read/write/retained/delegated effects and same-session/body/source keys for exact APIs; confirmed repair scopes must remove unrelated Comp/CompRef reachability while retaining legitimate writers/errors. Investigations must produce a supported verdict or explicit bounded remaining question.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Source/algorithm redesign, unsupported-feature implementation, speculative cost claims, product execution and whole compiler audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


 ## Input Investigation Outcome

 The original required input/delegate-authority questions are answered, not merely
 assigned elsewhere. [Exact answer](../../../evidence/compiler-api-audit/resolutions/ownership-pattern-default-inputs.json)
 and [independent review](../../../evidence/compiler-api-audit/review-resolution-ownership-pattern-default-inputs.json)
 record the complete named scope, necessary inputs/effects, actual caller contexts,
 source identity and supported C conclusion. Required input questions remaining
 in this scope: none. Product repairs remain unimplemented and unverified.

 Repair ownership: [com-37u0](com-37u0.md), [com-m66h](com-m66h.md), [com-6fnh](com-6fnh.md), [com-k3i6](com-k3i6.md), [com-jciu](com-jciu.md), [com-q51y](com-q51y.md), [com-ysl5](com-ysl5.md). These repair issues are not evidence of the conclusion; the linked
 source closure and independent review are. This closes only this finite
 investigation, not com-mmk9 or any product implementation milestone.
