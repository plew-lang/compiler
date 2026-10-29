---
id: com-ough
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:45:54Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Narrow source record/layout and metadata construction leaves

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/source-construction-and-declaration-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-source-construction-and-declaration-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Only ensureRecordStruct/Span peer, dictionary lowered-entry writer, source BindRange metadata and TopLevel appendLoweredNewtype/Global. Keep coherent row/index/child/origin stores, readable name bytes and exact defaults.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- codegen-condition-syntax-to-shared-clause-pool: ['lowerValueCondition']
- codegen-destructure-bind-provenance-range-lowering: ['destructureSiteBinds', 'syntaxDestructureSiteBinds']
- codegen-record-layout-struct-name-and-registration: ['ensureRecordStruct', 'ensureRecordStructSpans']
- codegen-dictionary-source-entry-sequence-lowering: ['lowerDictLit.span', 'lowerDictionaryEntries.self general Comp; retain Expr pool writer']
- codegen-newtype-source-decoder-and-declaration-publication: ['appendLoweredNewtype']
- codegen-global-statement-lowering-and-row-publication: ['appendLoweredGlobal']

## Actions and Completion
For exact named APIs/components, enumerate all actual typed caller lanes/defaults/read-write/retained/delegated effects; independently review a closed necessary input contract. Preserve identities/cache/name/diagnostic/failure/restore/order. Narrowing must remove accessible raw Comp/CompRef; immutable coherent pools/passive descriptors may remain. Confirmed scopes must remove actual broad API grants from all actual source/fixture consumers, preserving the per-row mutable effects with TDD/refactor controls and independent review; investigation scopes close finite input/effect questions and assign repairs, not implementation GREEN.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Other compiler domains, passive descriptor field minimization, source acceptance/algorithm/ABI change, unsupported feature work, product repair/execution/performance within this audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

