---
id: com-3njd
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:13:59Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Close operator query and signature projection service inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-default-literal-and-recovery.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-default-literal-and-recovery.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Exactly four assigned Operator families. Trace explicit/lexical receiver/bound/proof/witness/type writer/diagnostic and legacy cursor/layout effects per API; determine minimum closed domain without new selection semantics.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-operator-candidate-and-witness-inputs: ['operatorCalleeForRef', 'findBinTraitWitnessForRef', 'unaryOperatorCallee']
- codegen-operator-selected-signature-result-inputs: ['unaryOperatorResultType', 'operatorCalleeType', 'operatorCalleeResultType']
- codegen-operator-lexical-bound-result-inputs: ['staticBinaryOperatorResultRef']
- codegen-operator-shape-and-expression-adapters: ['bareOperatorResult', 'operatorTypeRef', 'operatorOutputType', 'binResultTypeInfo', 'binResultTypeInfoWithChainHole']

## Actions and Completion
Map complete actual read/write/retained/delegated effects and same-session/body/source keys for exact APIs; confirmed repair scopes must remove unrelated Comp/CompRef reachability while retaining legitimate writers/errors. Investigations must produce a supported verdict or explicit bounded remaining question.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Source/algorithm redesign, unsupported-feature implementation, speculative cost claims, product execution and whole compiler audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

