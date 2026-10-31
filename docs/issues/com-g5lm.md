---
id: com-g5lm
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:13:59Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow source syntax/byte/type projection and decode-cache leaves

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-default-literal-and-recovery.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-default-literal-and-recovery.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of audit closure; implementation admission is assigned below; no product repair was performed by the audit.

## Guarantee and Scope
Named fold/numeric/leaf range/view/comparable/arm/decode helpers only. Same-arena readers/cache/diagnostics; retain failures/defaults and no semantic query authority.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-string-literal-decode-cache-preparation: ['prepareStringLiteral']
- codegen-constant-integer-fold-and-range-check: ['foldConst']
- codegen-literal-numeric-shape-and-span-classifiers: ['tiIsInt', 'tiIsFloat', 'spanIntTy']
- codegen-integer-literal-leaf-range-validation: ['checkLitLeaf']
- codegen-argument-view-id-set-recovery: ['typeRefViewIds', 'appendDistinctViewId']
- codegen-overload-argument-grounded-shape-recovery: ['refsGenericArgComparable']
- codegen-match-pattern-exhaustiveness-query: ['armCovers']

## Actions and Completion
Map complete actual read/write/retained/delegated effects and same-session/body/source keys for exact APIs; confirmed repair scopes must remove unrelated Comp/CompRef reachability while retaining legitimate writers/errors. Investigations must produce a supported verdict or explicit bounded remaining question.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Source/algorithm redesign, unsupported-feature implementation, speculative cost claims, product execution within the originating audit and whole compiler algorithm certification. Appropriate later repair validation remains required.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Adopted Implementation Intake

[com-yjyu](com-yjyu.md) classifies the exact confirmed scope as required existing-feature phase3 conformance. Required admission owner(s): met-6e6k, com-fuo8; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-defaults-and-literals.json) retains all main/mixed roles and normative grounds. Existing literal decode-cache/numeric fold/range/view/comparable leaves and armCovers use bounded source/type readers and precise cache/diagnostic writes. Type/decoded-value admission and match coverage consumers retain their separate roles.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
