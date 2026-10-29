---
id: com-if6u
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:38:28Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow retained interface root scope and provenance readers

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-verification-and-contract-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-verification-and-contract-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Exact confirmed three families: root/scope validity, type dependency and frozen proof provenance. Preserve same-session roots, scope origin/binders/Self, canonical child-only navigation, diagnostics/depth/merge/root0; no type/proof selection or new evidence creation.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-interface-proof-root-and-scope-readers: Root validity/bound/scope readers in exact family
- codegen-declaration-type-parameter-dependency-query: declarationTypeDependencies and exact family wrappers
- codegen-interface-proof-provenance-query: Interface root/proof provenance helpers in exact family

## Actions and Completion
For confirmed scope remove real broad signatures/grants at every actual caller/consumer while retaining the listed legitimate effects; use TDD/refactor controls, structural proof and independent review. For unresolved scope independently review exact closure and assign bounded repairs, without claiming repair/GREEN.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other domains, language acceptance/algorithm/ABI changes, unsupported feature work, product edits/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

