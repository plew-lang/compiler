---
id: com-2qi1
status: open
deps: []
links: [com-mmk9]
created: 2026-10-30T14:45:42Z
type: task
priority: 2
assignee: Koji Murata
tags: [verification, frontend]
---
# Narrow legacy view source count inputs

Evidence: [input-authority answer](../../../evidence/compiler-api-audit/resolutions/view-validation-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-resolution-view-validation-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This issue owns product repair; implementing it is not a prerequisite for the source-only input investigation.

## Guarantee and Scope
Exact API viewSourceCount; actual calls 1. Intern type span; canonicalTraitOwner uses traitOwnerIndex(offset:srcStart) and nameLen equality, not arbitrary same-name lookup. Extension applicability contributes one. Bare conform rows require nonzero exact trait owner, extId0, matching typeId/owner and conformanceSubjectMatches(typeRef). First owner/traitArgs arity contributes one; same owner/arity dedup, differing owner/arity early2. No proof returned and no source success writer.

viewSourceCount interns type span and reads canonicalTraitOwner by exact offset-index+nameLen, not arbitrary same-name search. Keep ext applicability contribution and exact nominal conform subject matcher/typeId/owner/arity dedup saturated2. Legacy newtype ext recursion omits typeRef(default0); preserve actual input/error differences without calling that algorithm correct. No caller-only collectViewSources/conformsInstance/bare fallback or resolved-selector trace grant. Whole mutable Comp grants unrelated syntax/parser/Mid state, source builder activation/publication and source preparation/outcome operations beyond the closed semantic view/count/validation operations. This conclusion makes no direct LlvmCtx/native ownership claim; coherent type/proof/layout/name services and passive complete data remain legitimate.

## Completion
One finite owner for this entire original family. Change real API and sole actual caller, keep required delegate implementation grants explicitly bounded per operation; no captured full Comp/facade. Preserve same-source identity/default/order/live-walk/diagnostic/trace/derived-prefix and lifetime. Required inner temporary lexical context restores all exits versus mapped existing success-only gap. Keep semantic behavior and known compatibility differences recorded; eventual structural independent review/TDD/refactor validation separate from this input investigation. Keep exact per-entry source/session/owner/nominal/view/ParamId/proof/default/cursor/retention/errorprefix and actual conditional writers. No group/graph union or broad Comp facade/capture. All-exit temporary scopes distinct from persistent valid derived pools; no general source/solver redesign.

Preserve exact actual caller and source/session/type/proof/pool lifetimes, ordering/defaults, diagnostic provenance, legitimate mutation and error prefixes in the pinned answer. A wrapper or callback retaining unrelated whole compiler authority is not a narrowing. Readonly grants are not writers. Cover relevant normal, rejected, boundary and failure-prefix controls, verify the real producer-to-final-consumer path and remove competing broad signatures. No statement of future GREEN is evidence that the repair has passed.

## Excluded
Other original J/C/O/optional/U, source/view/name/ownership/type/solver/general checker algorithms, product changes/execution/performance/GREEN within this audit.
