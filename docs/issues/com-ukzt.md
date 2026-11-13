---
id: com-ukzt
status: open
deps: [com-6esv]
links: [com-mmk9]
created: 2026-10-30T14:58:25Z
type: task
priority: 2
assignee: Koji Murata
tags: [verification, frontend]
---
# Narrow via declaration signature inputs

Evidence: [input-authority answer](../../../evidence/compiler-api-audit/resolutions/conformance-via-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-resolution-conformance-via-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This issue owns product repair; implementing it is not a prerequisite for the source-only input investigation.

## Guarantee and Scope
Exact APIs: viaSignatureMatches, checkViaTargets; actual calls 5. Per-entry explicit inputs and precise controlled service permissions above, not group-wide union. Keep all original family APIs under one owner, including conformsInstance/typeConformsToName despite their distinct authority.

Per-entry services T/N/K/Q/P/L/F only where actually reachable; readonly coherent catalogs/passive records and explicit selected source/proof/ParamId/environment/default/diagnostic/lifetime preserved. No blanket graph union or receiver-field-count decomposition. Concrete whole Comp unrelated Syntax/parser/source loading/activation/preparation/signature/body/executable worklist/configuration writers, not Comp directly owning native handles. Keep per-entry source operation/default/guard/identity contract and existing unused witnessedHas formals classification separate.

## Completion
Change real signatures/all25 source+fixture consumers and necessary reader/publisher/unifier/name/query/frame helper signatures without Comp/raw mutable Arena facade/capture. Preserve tag/default/source/namespace/selected Conform/ParamId/proof/diagnostic/retention/lifetime/false-vs-Err/error prefix and all-exit temporary restoration. Behavior/structural TDD/gates and independent repair review are future implementation, not this investigation.

Preserve exact actual caller and source/session/type/proof/pool lifetimes, ordering/defaults, diagnostic provenance, legitimate mutation and error prefixes in the pinned answer. A wrapper or callback retaining unrelated whole compiler authority is not a narrowing. Readonly grants are not writers. Cover relevant normal, rejected, boundary and failure-prefix controls, verify the real producer-to-final-consumer path and remove competing broad signatures. No statement of future GREEN is evidence that the repair has passed.

## Excluded
Other J/C/O/optional/mainC scopes, source/solver/proof/conformance/selection/applicability algorithm redesign, product execution/GREEN/performance. Existing unused witnessedHas tps/targs mainC/com-crym separate; evaluation effects retained.

## Adopted Implementation Intake

[com-lk60](com-lk60.md) classifies the exact confirmed scope as required existing-feature phase3 conformance. Required admission owner(s): met-ia09, met-ucze; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-constraints.json) retains all main/mixed roles and normative grounds. via宣言のsignature compatibilityとtarget candidate検査はtrait satisfactionと通常callの共通applicability。source適合が終点なので工程3。

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.

## Dependent Receiver Counterexample

The [view formation review](com-3jtd.md#independent-completion-review) found
that a projected inherent receiver can be called explicitly from a witness
body but rejected as a `via` target. Candidate `03b9f51b` rejects
`fn read() -> I64 via code` with “target signature does not match” for
`impl Box[Number, I64] as Read` when `code` belongs to
`impl[T] Box[T, T#Source.Item] where T: Source`, with
`Number: Source[Item=I64]`. Replacing the delegation with
`fn read() -> I64 { return self.code() }` passes check and runs with
stdout `42`. The nonprojected target also passes check.

`checkViaTargets` calls `viaSignatureMatches` on raw receiver and
result terms, before the forwarding body's ordinary selection can use
the dependent receiver evidence. A favorable precheck result is only a
Boolean and cannot constrain the forwarding body's selection. The
[applicability contract](../design/name-lookup.md#6-applicability-and-publication)
requires shared selection and preservation of the result and receiver
modes. [com-6esv](com-6esv.md) owns that behavioral repair and is a prerequisite.
Reconcile this audit scope against the surviving entries after that change.
