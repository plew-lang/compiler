---
id: com-dwp6
status: open
deps: []
links: [com-mmk9]
created: 2026-10-30T14:45:42Z
type: task
priority: 2
assignee: Koji Murata
tags: [verification, frontend]
---
# Narrow Unit array and index shape inputs

Evidence: [input-authority answer](../../../evidence/compiler-api-audit/resolutions/boolean-shape-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-resolution-boolean-shape-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This issue owns product repair; implementing it is not a prerequisite for the source-only input investigation.

## Guarantee and Scope
Exact APIs: exprIsUnit, checkIndexKeyType, valueIsReliablyNonArray. Product calls 5, fixture calls 0. One complete original-family repair owner, coherent source verification/type query owner permitted. Per-entry grants remain distinct; no wholeComp hidden through facade/callback/capture.

UN exprIsUnit only AST Make.typeLen/fields.len readonly. IK checkIndexKeyType always base typeOf then valid Dictionary ref/args gate invokes exactkey tcCheckValue; TC failurelatch retained but no LC/V grant. NA valueIsReliablyNonArray keeps direct Array/Int/Str/Make-name branches, onlyremaining fallbacktypeOf; no TC/V. Onefamily owner preserves these three distinct grants; no blanket union from BC or the same file. Keep actual source/session/lexical owner/binder/type/proof/callsite/constraint/closure/capture/control/ownership/default identity and output lifetime, exact branch/error/default/cache/source-writer conditions and ordering. Bool fullhigher-order verifier/literal effects retained; Unit AST-only; Index gatedTC but noLC; nonArray fallbackquery but noTC. No source owner/bodyready/executable success fabricated. Existing success-only temporary restoration remains observed gap versus all-exitdesign; valid persistentderivedprefix not rolledback.

## Completion
Real API/delegate/caller/capture boundary changes covering all8 actualcalls, meaningful normal/reject/boundary/no-op/missingBool/shape/cachewarm-cold/instance/owner/failure/noninterference cases plus independent structure and appropriatefuturegates. No unread requiredquestion transferred into thisproposal. Preserve all per-entry actual source/session/owner/ParamId/proof/control/closure/cache/default/guard/errorprefix/lifetime. Narrow real signatures/allconsumers and remove unrelated Comp facade/capture; keep legitimate verifier/synthetic writers, all-exit temporary scope endpoint versus existing gap, persistent valid prefixes distinct.

Preserve exact actual caller and source/session/type/proof/pool lifetimes, ordering/defaults, diagnostic provenance, legitimate mutation and error prefixes in the pinned answer. A wrapper or callback retaining unrelated whole compiler authority is not a narrowing. Readonly grants are not writers. Cover relevant normal, rejected, boundary and failure-prefix controls, verify the real producer-to-final-consumer path and remove competing broad signatures. No statement of future GREEN is evidence that the repair has passed.

## Excluded
Other families/J/C/O/optional/mainC/components; source/type/literal/ownership/array/condition algorithm changes; productrepair/execution/performance/GREEN within audit.

## Adopted Implementation Intake

[com-8ttz](com-8ttz.md) classifies the exact confirmed scope as required existing-feature phase3 conformance. Required admission owner(s): met-6e6k, met-acfl; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-source-verification.json) retains all main/mixed roles and normative grounds. Unit AST predicate, gated Dictionary key compatibility and fallback nonarray query are three distinct source typing lanes. TC failure latch exists only at reached key checks; no blanket LC/verifier union.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
