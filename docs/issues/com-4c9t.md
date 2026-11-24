---
id: com-4c9t
status: open
deps: []
links: [com-mmk9]
created: 2026-10-30T15:50:24Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, ownership, verification]
---
# Narrow existential member environment inputs

Evidence: [input-authority answer](../../../evidence/compiler-api-audit/resolutions/destruction-interface-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-resolution-destruction-interface-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This issue owns product repair; implementing it is not a prerequisite for the source-only input investigation.

## Current API Resumption Map

The endpoint names and call counts in the original audit below describe its
frozen source, not instructions to recreate removed APIs. Removal commits:
`6869aab7`. Current same-path entries: `prepareExistentialMember`, `prepareExistentialBox` in [Codegen/Mono/InterfaceEvidence.pw](../../src/Codegen/Mono/InterfaceEvidence.pw).
existentialImplementationEnvironment survives. Member/witness preparation is retained before final boxing; final readers consume prepared members instead of selecting again. Existing semantic repair owner: [com-30u1](com-30u1.md).

Apply this task's original per-entry authority/lifetime guarantees to the
surviving path and its actual callers. Retain the existing audit evidence as the
baseline; reconcile which grants still need narrowing versus those eliminated
by the semantic repair. Deleted names alone do not prove the whole family fixed.
The task remains open until that finite reconciliation and required controls /
independent review establish closure; do not widen it to every API of the repair
owner or restore a superseded decision path.

## Guarantee and Scope
Audit-time APIs (9665094d): selectExistentialMember, existentialImplementationEnvironment; actual calls 4. Narrow this original family as one finite owner across real APIs, necessary actual semantic/read/write delegates and all enumerated source/fixture callers; preserve every entry-specific default/frame/identity/retain/error prefix and cache/interner/layout/proof/source-bound mode. Only actual needed service slices, no whole Comp wrapper/capture or facade exposing source prepare/publish.

Keep old main C/J and other J/C/O/optional records/owners; declaration-only does not gain executable queues. Coordinate overlapping existing shape/layout/G services without duplicate API ownership. Preserve every per-entry required operation/branch/producer/default/session/owner/binder/view/proof/field/layout/cache/diagnostic/graph/queue/publication/lifetime effect. Coherent domain owner and passive full descriptors remain legitimate; concrete unrelated Comp authority must go.

## Completion
Future actual signature/delegate/caller/capture narrowing with appropriate behavior/absence/invalid/Deferred/ready/cycle/recursive/source-owner/identity/mode/cache/restore/lifetime controls, independent structural review and relevant gates. Actual legacy restore gap is distinct from adopted all-exit endpoint, legitimate derived prefixes retained. Investigation completion does not claim product repair/GREEN.

Preserve exact actual caller and source/session/type/proof/pool lifetimes, ordering/defaults, diagnostic provenance, legitimate mutation and error prefixes in the pinned answer. A wrapper or callback retaining unrelated whole compiler authority is not a narrowing. Readonly grants are not writers. Cover relevant normal, rejected, boundary and failure-prefix controls, verify the real producer-to-final-consumer path and remove competing broad signatures. No statement of future GREEN is evidence that the repair has passed.

## Excluded
Other prior mainC/J/O/optional/API scopes; no language/destruction/interface/proof/type/solver/ABI correctness redesign, native/performance/GREEN or product execution within source-only audit.

## Adopted Implementation Intake

[com-4sg9](com-4sg9.md) classifies the exact confirmed scope as required existing-feature phase3 conformance. Required admission owner(s): met-ucze, met-ia09, met-6e6k; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-selected-instances.json) retains all main/mixed roles and normative grounds. Existential member selection and implementation environment carry exact public requirement/source identity and selected proof to callable consumers. Retain current supported shape and bounded services, not arbitrary source or runtime preparation.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
