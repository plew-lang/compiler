---
id: com-fsxx
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:45:53Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow unread explicit inputs and receiver removal

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-construction-and-declaration-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-construction-and-declaration-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Only appendSyntaxBound.rawTrait, appendLoweredArg.self, lowerDictLit.span, declaredTypeRef.nameLen, checkMethodVis.ownerStart/ownerLen and explicitly unused scalar helpers. No compulsory shrinking of passive records or broad checker refactor.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-syntax-trait-constraint-and-function-bound-lowering: ['appendSyntaxBound.rawTrait']
- codegen-source-call-argument-reservation-and-value-fill: ['appendLoweredArg.self']
- codegen-dictionary-source-entry-sequence-lowering: ['lowerDictLit.span']
- codegen-selected-declaration-late-nominal-type-registration: ['declaredTypeRef.nameLen']
- codegen-member-and-default-construction-visibility: ['checkMethodVis.ownerStart', 'checkMethodVis.ownerLen']

## Actions and Completion
For exact named APIs/components, enumerate all actual typed caller lanes/defaults/read-write/retained/delegated effects; independently review a closed necessary input contract. Preserve identities/cache/name/diagnostic/failure/restore/order. Narrowing must remove accessible raw Comp/CompRef; immutable coherent pools/passive descriptors may remain. Confirmed scopes must remove actual broad API grants from all actual source/fixture consumers, preserving the per-row mutable effects with TDD/refactor controls and independent review; investigation scopes close finite input/effect questions and assign repairs, not implementation GREEN.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other compiler domains, passive descriptor field minimization, source acceptance/algorithm/ABI change, unsupported feature work, product repair/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Adopted Implementation Intake

[com-7a5t](com-7a5t.md) classifies the exact confirmed scope as required existing-feature phase4 conformance. Required admission owner(s): com-604k; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-construction.json) retains all main/mixed roles and normative grounds. Remove only exact unused scalar/span inputs and the unused Comp receiver of the raw appendLoweredArg value constructor. Existing semantic lookup/type/publication actor narrowing stays in separate phase-three owners. This independent current-feature API cleanup remains mandatory at integration, preserving all caller computation/grounding and retained descriptors. For lowerDictLit.span, this owner performs the one shared signature removal; com-ough retains its distinct dictionary Expr writer boundary and consumes that change.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
