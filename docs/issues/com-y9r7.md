---
id: com-y9r7
status: open
deps: []
links: [com-mmk9]
created: 2026-10-30T14:48:45Z
type: task
priority: 2
assignee: Koji Murata
tags: [verification, frontend]
---
# Narrow operator shape and expression inputs

Evidence: [input-authority answer](../../../evidence/compiler-api-audit/resolutions/operator-projection-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-resolution-operator-projection-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This issue owns product repair; implementing it is not a prerequisite for the source-only input investigation.

## Guarantee and Scope
Exact APIs: bareOperatorResult, operatorTypeRef, operatorOutputType, binResultTypeInfo, binResultTypeInfoWithChainHole; actual calls 16. One finite owner for this original family and all its APIs/callers. Shared grounding/query/selection owner can be reused through individually required operations; shape and selected result entries must not receive whole OP:QUERY union.

bare result uses runtime outer-view guard/type shape; operatorTypeRef ref-less fallback simpleTypeRef->pushType only, no namespace/nominal recovery/latebare/Q. Output selector retains candidate/signature service. Binary wrappers first lexical output then both operands under explicit chainHole order; wrapper default0 evenzero-call body retained. Only staticBinary/bin have full source query, not group union. Whole mutable Comp grants unrelated syntax/parser/Mid state and independent source builder/publication/preparation/outcome operations beyond the closed per-entry operations. Coherent domain owners/passive complete descriptors remain legitimate. No direct LlvmCtx/native ownership claim is needed for this concrete excess conclusion.

## Completion
Change actual signatures/all tracked callers and preserve explicit defaults/early guards/lexical versus concrete selection/current sentinel/receiver-view/selected proof/ParamId/source-chain-hole/identity/result/error/lifetime. Preserve necessary canonical/interner/keyword/proof/layout/query derived prefix and exact restoration scope. Existing all-exit compiler-state contract is repair endpoint, not retention of observed success-only leakage. No new ranking/type inference/selection semantics. TDD/refactor controls and independent structural review belong eventual implementation; investigation does not claim repair or GREEN. Keep per-entry required operations/defaults/source/session/owner/ParamId/proof/view/guard/Err/retention across every actual consumer and zero-call body contract. No unrelated Comp facade/capture or service union; all-exit temporary lexical scopes distinct from current gaps and valid persistent derived prefix.

Preserve exact actual caller and source/session/type/proof/pool lifetimes, ordering/defaults, diagnostic provenance, legitimate mutation and error prefixes in the pinned answer. A wrapper or callback retaining unrelated whole compiler authority is not a narrowing. Readonly grants are not writers. Cover relevant normal, rejected, boundary and failure-prefix controls, verify the real producer-to-final-consumer path and remove competing broad signatures. No statement of future GREEN is evidence that the repair has passed.

## Excluded
Other original J/C/O/optional/U/mainC; language/source/type/solver/overload/coverage/ownership algorithms, productrepair/execution/performance/GREEN within audit.

## Adopted Implementation Intake

[com-yjyu](com-yjyu.md) classifies the exact confirmed scope as required existing-feature phase3 conformance. Required admission owner(s): met-6e6k, met-ucze; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-defaults-and-literals.json) retains all main/mixed roles and normative grounds. Current operator shape/result and binary/chain-hole adapters have distinct per-entry lexical/concrete query profiles. Preserve selected proof/result and early-view guards without granting one graph-wide service union.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
