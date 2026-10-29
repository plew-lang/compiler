---
id: com-61ji
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T19:03:37Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Determine source explicit grounding inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-expression-and-recording-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-expression-and-recording-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Saved expected/typearg and saved expression term grounding with explicit environment/Self/Item; exact canonical/projection/proof/interner/cache/error closure. Establish exact caller/reader/writer/retained identity and necessary delegated effects for this listed API/component scope; unresolved components may remain a smaller finite question.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-saved-call-context-and-type-argument-body-grounding: ['groundCallTemplateExpectedResult', 'groundCallTemplateTypeArgs']
- codegen-saved-expression-explicit-body-grounding-readers: ['groundSemanticExprTypeInfo', 'groundSemanticExprTypeRef']

## Actions and Completion
Produce a finite direct/delegated input/effect/identity/error closure for the exact listed APIs; independently decide justified/excess or retain a smaller explicitly owned question. Assign any required repair separately, without claiming implementation GREEN.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other API components/domains, passive record field decomposition, language acceptance/algorithm/performance/ABI changes or whole compiler correctness/GREEN. No product repair/execution occurs within the originating audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

