---
id: com-j0r9
status: open
deps: []
links: [com-mmk9]
created: 2026-10-30T13:13:21Z
type: task
priority: 2
assignee: Koji Murata
tags: [verification, frontend]
---
# Narrow partial callable type substitution inputs

Evidence: [input-authority answer](../../../evidence/compiler-api-audit/resolutions/viewed-static-selection-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-resolution-viewed-static-selection-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This issue owns product repair; implementing it is not a prerequisite for the source-only input investigation.

## Guarantee and Scope
Exact APIs: groundKnownCallTypeArguments. Actual calls 3. Exact partial FuncBindRange/value holes/Self adapter and controlled structural canonical publisher; no cursor/query/cache.

Check FuncBindRange/values arity, omit onlyzero holes, simultaneous substitution with explicit receiver Self/defaultItem0; preserve rigid ParamIds and type facets. Only structural canonical/type-name publication/reader/diagnostic is needed, no ambient cursor/query/cache or full environment assumption.

## Completion
Change concrete signatures and every actual consumer; no facade retaining fullComp/capture. Relevant behavior/structural controls and independent review including restoration, identity and prefixes. Product implementation/GREEN separate from this substantive investigation. Preserve complete per-entry source/domain/pool/trait/view/ParamId/proof/environment/default/guard/error and lifetime contract, no unrelated Comp access via wrapper/capture. Actual success-only legacy restore gaps are observed, not a replacement for adopted all-exit temporary scope design. Relevant positive/reject/boundary/noninterference/failure controls and independent structural review/gates remain future product work.

Preserve exact actual caller and source/session/type/proof/pool lifetimes, ordering/defaults, diagnostic provenance, legitimate mutation and error prefixes in the pinned answer. A wrapper or callback retaining unrelated whole compiler authority is not a narrowing. Readonly grants are not writers. Cover relevant normal, rejected, boundary and failure-prefix controls, verify the real producer-to-final-consumer path and remove competing broad signatures. No statement of future GREEN is evidence that the repair has passed.

## Excluded
Other repair groups and original J/C/O/optional/other U scopes; language/source/solver/general selection or proof algorithm redesign, product execution/performance/GREEN within this audit.



## Adopted Implementation Intake

[com-lk60](com-lk60.md) classifies the exact confirmed scope as required existing-feature phase3 conformance. Required admission owner(s): met-6e6k, met-ucze, met-ia09; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-constraints.json) retains all main/mixed roles and normative grounds. selected FuncBindRangeの部分代入はcanonical termとlexical ParamIdを保存するsource call／instance handoff。全Compは当該意味責務に不要。

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
