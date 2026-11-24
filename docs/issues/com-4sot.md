---
id: com-4sot
status: open
deps: []
links: [com-mmk9]
created: 2026-10-30T15:16:03Z
type: task
priority: 2
assignee: Koji Murata
tags: [verification, frontend]
---
# Narrow source construction type query inputs

Evidence: [input-authority answer](../../../evidence/compiler-api-audit/resolutions/source-type-grounding-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-resolution-source-type-grounding-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This issue owns product repair; implementing it is not a prerequisite for the source-only input investigation.

## Current API Resumption Map

The endpoint names and call counts in the original audit below describe its
frozen source, not instructions to recreate removed APIs. Removal commits:
`40fecbc0`. Current same-path entries: `makeFieldArgument` in [Codegen/Resolve/Expr.pw](../../src/Codegen/Resolve/Expr.pw).
expressionSourceType, groundedTypeOf and typeOf survive. The removed helper returned reconstructed type data; the current field reader returns the actual initializer expression for the existing source typing/evidence path. Existing semantic repair owner: [com-3jtd](com-3jtd.md).

Apply this task's original per-entry authority/lifetime guarantees to the
surviving path and its actual callers. Retain the existing audit evidence as the
baseline; reconcile which grants still need narrowing versus those eliminated
by the semantic repair. Deleted names alone do not prove the whole family fixed.
The task remains open until that finite reconciliation and required controls /
independent review establish closure; do not widen it to every API of the repair
owner or restore a superseded decision path.

## Guarantee and Scope
Audit-time APIs (9665094d): expressionSourceType, groundedTypeOf, typeOf, makeFieldArgRef. One complete original-family scope per assigned repair; precise required per-entry profiles retained.

One finite complete owner for each listed original unanswered family/component; retain per-entry service contract, passive full values, exact source/session/owner/ParamId/receiver/selected-proof/default/callsite identity and dependent pool lifetime. Required conditional canonical/cache/name/keyword/proof/layout/source and temporary cursor effects remain only on actual routes. Real API/delegate/caller/retained-capture change must remove unrelated Comp access, not hide it behind facade/callback. Comp Frontend305-435 mutable Mid/syntax/parseScratch/lowerWhereSyntax+types/associatedscratch/nextParamId and arbitraryunrelatedsource/domain/executable/driverconfigwriter paths notneeded for these operations. No native directownerpremise. Remove real API/delegate/capture grants, not only outerparameter spelling.

## Completion
Implement later with meaningful behavior-preserving normal/absence/zero/Unit/NoNormalValue/invalid/missing-carrier/partial-proof/cold-warm-cache/currentenv/sourceowner/recorded-vs-construction/Errprefix/panic/restore/noninterference controls, all actual consumers and independent structural review/appropriate gates. All required input questions are answered here, not deferred unread. All-exit temporary restoration endpoint distinguished from observed success-only gaps; valid persistent derivation prefixes retained.

Preserve exact actual caller and source/session/type/proof/pool lifetimes, ordering/defaults, diagnostic provenance, legitimate mutation and error prefixes in the pinned answer. A wrapper or callback retaining unrelated whole compiler authority is not a narrowing. Readonly grants are not writers. Cover relevant normal, rejected, boundary and failure-prefix controls, verify the real producer-to-final-consumer path and remove competing broad signatures. No statement of future GREEN is evidence that the repair has passed.

## Excluded
Existing main C/old J/C/O/optional/API subsets and repair owners com-rs2x/com-v9md remain unchanged/open; no repair completion, language/algorithm/ABI/performance/GREEN claim.

## Adopted Implementation Intake

[com-7kzd](com-7kzd.md) classifies the exact confirmed scope as required existing-feature phase3 conformance. Required admission owner(s): met-6e6k, met-acfl; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-recording.json) retains all main/mixed roles and normative grounds. Source typeOf/grounded expression and construction-field context queries are current semantic-type authority. Preserve recorded versus construction/failure and exact owner-local services; final consumers may not reinfer committed meaning.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
