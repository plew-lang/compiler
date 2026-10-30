---
id: com-dt5y
status: open
deps: []
links: [com-mmk9]
created: 2026-10-30T13:33:35Z
type: task
priority: 2
assignee: Koji Murata
tags: [verification, frontend]
---
# Narrow generic signature view cycle inputs

Evidence: [input-authority answer](../../../evidence/compiler-api-audit/resolutions/check-generic-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-resolution-check-generic-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This issue owns product repair; implementing it is not a prerequisite for the source-only input investigation.

## Guarantee and Scope
Exact APIs: checkGenericTypeViewCycles. Product calls 3, fixture calls 0. VC readonly conformance/view graph with bounded interner and conditional legacyprojection canonical writer; preserve primary t.args traversal and local cycle algorithm behavior.

VC view/conformance graph reader with own interner and conditional legacy projection bridge canonical writer only. Preserve actual primary normal t.args traversal; this audit does not certify whole view cycle soundness/completeness or add other child traversal. No Q/K/source/body/trace writer. Change actual signatures and all matching callers/consumers without full Comp escape/capture. Keep exactservicebranch/default/source/session/owner/type/ParamId/proof/frame/memo/diagnostic/prefix/lifetime contracts, outputidentity and errors; preserve passive coherent records. Existing success-only gaps are actualobservations, not endorsement of all-exit design violations. Any behavior correction is separately authorized work.

## Completion
Finite input boundary repair with meaningful behavior/refactor controls and source structural independent review. No product repair/execution/GREEN performed by audit. Keep per-entry source/session/owner/type/ParamId/proof/environment/default/guard/error/cache/publication/lifetime distinction and actual producer-to-final-consumer path; change real signatures/every exact consumer without unrelated whole Comp through facade/capture. Use meaningful positive/reject/boundary/noninterference/failure controls and independent real-boundary review/gates for future product repair.

Preserve exact actual caller and source/session/type/proof/pool lifetimes, ordering/defaults, diagnostic provenance, legitimate mutation and error prefixes in the pinned answer. A wrapper or callback retaining unrelated whole compiler authority is not a narrowing. Readonly grants are not writers. Cover relevant normal, rejected, boundary and failure-prefix controls, verify the real producer-to-final-consumer path and remove competing broad signatures. No statement of future GREEN is evidence that the repair has passed.

## Excluded
Other groups/original J/C/O/optional/other U; language/source/type/ownership/solver/general algorithm redesign, product execution/repair/performance/GREEN within this audit.


