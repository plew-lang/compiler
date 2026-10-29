---
id: com-4wxu
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:13:59Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Separate label/default and bound-copy input services

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-default-literal-and-recovery.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-default-literal-and-recovery.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Exactly named label/index/bind/generator slot/ParamId projection, recordsFieldDefault and copied FuncBound methods. Keep isolated label interning, one-based IDs, owner/range lineage and original source clause provenance.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-default-parameter-binding-and-generic-projection: ['bindCallParameters', 'defaultArgumentGenerator', 'defaultGeneratorTypeArguments']
- codegen-field-default-generator-preparation-and-occurrence-selection: ['recordsFieldDefault']
- codegen-parameter-default-generator-declaration-and-bound-publication: ['copyDefaultGeneratorBounds']
- codegen-callable-label-form-traversal-and-index-mapping: ['callableLabelMatchesParameter', 'argMatchesParamLabel', 'callableInputMatchesLabel', 'callableNextParameter', 'callableInputLabelsOk', 'paramIndexForArg', 'argIndexForParam', 'paramsLabelsOk']

## Actions and Completion
Map complete actual read/write/retained/delegated effects and same-session/body/source keys for exact APIs; confirmed repair scopes must remove unrelated Comp/CompRef reachability while retaining legitimate writers/errors. Investigations must produce a supported verdict or explicit bounded remaining question. Product repairs/behavior verification and task creation/assignment are parent work.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Source/algorithm redesign, unsupported-feature implementation, speculative cost claims, product execution and whole compiler audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

