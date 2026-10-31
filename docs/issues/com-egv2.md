---
id: com-egv2
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T17:53:14Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Isolate canonical Access transformation inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/mid-domain-services-and-values.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-mid-domain-services-and-values.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
11 Access algorithm families listed in rows; passive constructors/scopes validator excluded

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- mid-access-frozen-input-place-and-operand-materialization: ['canonicalAccessLocalPlace', 'canonicalAccessGlobalPlace', 'canonicalAccessInputPlace', 'canonicalAccessInputOperand']
- mid-access-selected-chain-and-local-prefix-navigation: ['canonicalAccessFor', 'canonicalAccessChainLen', 'canonicalAccessChainAt', 'canonicalAccessMarkerLocalBase', 'canonicalAccessSetterLocal', 'canonicalAccessSetterStart', 'canonicalAccessTotalChainLen', 'canonicalAccessGetterStart', 'canonicalAccessMutableLocalCount']
- mid-access-evaluation-dag-plan-and-recipe-index: ['canonicalAccessPlanInput', 'canonicalAccessPlanForTerm']
- mid-access-marker-enumeration-and-body-layout: ['canonicalAccessSiteAt', 'canonicalAccessSite', 'canonicalAccessLayout']
- mid-access-canonical-statement-and-terminator-copy: ['canonicalAccessCopyStatements', 'canonicalAccessCopyTerminator']
- mid-access-selected-temporary-local-append: ['canonicalAccessAppendLocals']
- mid-access-canonical-operand-and-selected-abi-adapters: ['canonicalAccessAppendPlace', 'canonicalAccessAppendCopy', 'canonicalAccessAppendInoutBorrow', 'canonicalAccessAppendReadBorrow', 'canonicalAccessAppendMove', 'canonicalAccessBaseOperand', 'canonicalAccessKeyOperand', 'canonicalAccessAppendResolvedTarget', 'canonicalAccessAppendValueReceiver', 'canonicalAccessAppendSelectedReceiver', 'canonicalAccessAppendSelectedArgument']
- mid-access-parent-call-container-reservation-emission: ['canonicalAccessParentBorrow', 'canonicalAccessAppendParentTerminator']
- mid-access-reference-pin-and-getter-call-emission: ['canonicalAccessAppendReference', 'canonicalAccessAppendRecipeGetter', 'canonicalAccessAppendGetter']
- mid-access-reverse-setter-cleanup-emission: ['canonicalAccessAppendSetter']
- mid-access-block-expansion-and-public-rewrite: ['canonicalAccessExpandBlock', 'elaborateCanonicalMidAccesses']

## Actions and Completion
all selected input/access/call/type-capability views and canonical writer form isolated Access domain; no general syntax/source checking/cursor capability reachable; preserve evaluation occurrence/plan/remap/writeback/accessScope/error semantics; structural and behavioral controls required at repair time

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other compiler APIs/algorithms, source semantics, product repair/execution and speculative performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Adopted Implementation Intake

[com-ptko](com-ptko.md) classifies the exact confirmed scope as required existing-feature phase4 conformance. Required admission owner(s): com-an0b; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-mid-and-lowering.json) retains all main/mixed roles and normative grounds. The11 canonical Access rewrite families consume frozen selected access plans and append canonical CFG/locals/operands/getter/setter operations. Existing Mid transformation authority must be bounded without changing source meaning or introducing another selector.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
