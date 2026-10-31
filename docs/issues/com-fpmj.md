---
id: com-fpmj
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:38:28Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow provided Self binder membership and operator spelling inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-verification-and-contract-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-verification-and-contract-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of audit closure; implementation admission is assigned below; no product repair was performed by the audit.

## Guarantee and Scope
Only isSelfTypeInProvided/isTypeParamOf/binOpTraitName/unOpTraitName. Preserve lexical/current binder/trait provenance, byte/name interner effects and exact pure operator map.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-lexical-provided-self-and-binder-name-membership: isSelfTypeInProvided/isTypeParamOf
- codegen-operator-code-to-trait-spelling-projection: binOpTraitName/unOpTraitName

## Actions and Completion
For confirmed scope remove real broad signatures/grants at every actual caller/consumer while retaining the listed legitimate effects; use TDD/refactor controls, structural proof and independent review. For unresolved scope independently review exact closure and assign bounded repairs, without claiming repair/GREEN.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other domains, language acceptance/algorithm/ABI changes, unsupported feature work, product edits/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Adopted Implementation Intake

[com-8ttz](com-8ttz.md) classifies the exact confirmed scope as required existing-feature phase3 conformance. Required admission owner(s): met-ia09, met-ucze; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-source-verification.json) retains all main/mixed roles and normative grounds. Provided Self/binder membership is lexical source ownership; pure operator-code spelling projection feeds source operation selection. Preserve distinct effects without general source-query grants.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
