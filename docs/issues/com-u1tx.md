---
id: com-u1tx
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:40:58Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow constraint identity and declaration metadata query inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/constraints-and-declaration-obligation-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-constraints-and-declaration-obligation-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of audit closure; implementation admission is assigned below; no product repair was performed by the audit.

## Guarantee and Scope
Exact confirmed readonly/pure helpers only, including same-session interface navigation validation. Remove unused receivers, preserve canonical type equality, tagged identities/owner mapping/sentinels/ordered merge and original diagnostics. No solver semantics change.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-trait-constraint-canonical-value-comparison: sameTraitConstraint
- codegen-source-lexical-function-and-bound-assumption-collection: sourceLexicalFunction/functionBoundAssumptions/conformanceBoundAssumptions
- codegen-declaration-bound-reference-validity-query: declarationBoundIsValid
- codegen-declaration-bound-tagged-identity-comparison: sameDeclarationBound
- codegen-static-operator-requirement-and-supertrait-navigation: staticOperatorRequirement/staticOperatorInSupertraits
- codegen-missing-and-supertrait-bound-value-projection: missingTraitBound only
- codegen-trait-associated-equality-merge: mergeTraitProjectionEquality
- codegen-viewed-trait-query-explicit-demand-adapters: conformanceQueryFound only
- codegen-conformance-fixed-owner-trait-declaration-query: resolveTraitDef
- codegen-existential-formation-bound-completeness-check: anyHasNamedBinding only
- codegen-declared-async-call-result-carrier-query: hasDeclaredCallResult

## Actions and Completion
For confirmed scope change actual signatures and all actual consumers with TDD/refactor controls and independent structural review. For unresolved scope deliver a finite read/write/identity/error closure and supported verdict, assigning repair owners without claiming implementation GREEN.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other domains, language acceptance/solver/algorithm redesign, broad new verification requirements, product edits/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Adopted Implementation Intake

[com-lk60](com-lk60.md) classifies the exact confirmed scope as required existing-feature phase3 conformance. Required admission owner(s): met-ia09, met-ucze, met-6e6k; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-constraints.json) retains all main/mixed roles and normative grounds. canonical constraint/tagged identity、lexical assumptions、operator/supertrait navigation、formation completeness、declared async resultのmainCを一括してsource evidence metadataの有限責務へ狭める。

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
