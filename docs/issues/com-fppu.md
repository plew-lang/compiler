---
id: com-fppu
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:13:59Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow existing unique declaration metadata checks

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-default-literal-and-recovery.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-default-literal-and-recovery.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of audit closure; implementation admission is assigned below; no product repair was performed by the audit.

## Guarantee and Scope
Named stored unique/field/deinit/container gates only; retain boxed-field membership, legacy name interner, resolved declaration identity and original diagnostic anchors. No change to language support or uniqueness algorithms.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-unique-type-containment-and-nominal-field-check: ['typeIsTransitivelyUnique', 'checkFieldContagion']
- codegen-deinit-owner-uniqueness-declaration-validation: ['checkDeinitOnlyOnUnique']
- codegen-array-and-generic-unique-argument-validation: ['checkArrayElemsNotUnique', 'checkGenericUniqueArgs']

## Actions and Completion
Map complete actual read/write/retained/delegated effects and same-session/body/source keys for exact APIs; confirmed repair scopes must remove unrelated Comp/CompRef reachability while retaining legitimate writers/errors. Investigations must produce a supported verdict or explicit bounded remaining question.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Source/algorithm redesign, unsupported-feature implementation, speculative cost claims, product execution within the originating audit and whole compiler algorithm certification. Appropriate later repair validation remains required.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Adopted Implementation Intake

[com-yjyu](com-yjyu.md) classifies the exact confirmed scope as required existing-feature phase3 conformance. Required admission owner(s): met-6e6k, met-ia09; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-defaults-and-literals.json) retains all main/mixed roles and normative grounds. Current static unique containment/field/deinit/generic argument gates are existing type/declaration admission. Narrow exact stored metadata and diagnostic anchors without adding unique generics, changing current restrictions or workers.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
