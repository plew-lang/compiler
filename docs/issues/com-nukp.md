---
id: com-nukp
status: open
deps: []
links: [com-mmk9]
created: 2026-10-30T12:25:51Z
type: task
priority: 2
assignee: Koji Murata
tags: [verification, frontend]
---
# Narrow structural method receiver environment matching inputs

Evidence: [input-authority answer](../../../evidence/compiler-api-audit/resolutions/selected-constraints-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-resolution-selected-constraints-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This issue owns product repair; implementing it is not a prerequisite for the source-only input investigation.

## Guarantee and Scope
Exact APIs: methodReceiverEnvironment. Readonly canonical newtype/binder/view/child reader plus local witness bindings using nonzero receiver-pattern/empty traitargs specialization. No semantic writer or Comp fallback.

methodReceiverEnvironment is readonly semantic newtype/binder/view/child traversal with local witness bindings: nonzero subjectTy and empty declaredTraitArgs/traitArgs make legacy name interning and trait argument grounding infeasible. Keep recvPatternParams preference and logical Self; do not attach general conformance query/keyword/canonical/cursor writers.

## Completion
Change real signatures and every actual consumer in this exact group; retain the complete per-entry direct/delegated grants, source/session/binder/proof/recipe identities, defaults, return variants, error and restoration prefixes in the linked independent source record. A wrapper/capture of whole Comp is not narrowing. Use relevant normal/rejected/boundary/failure controls and independent structural review/gates for future product work. Change actual signatures/all69 actual consumers within exact15 API scope and retain unusedclosedProtocol bodyclosure. Per-entry profiles preserve same-domain coherent owner, defaults, guard/order, evidence/cachewriter and lifetime, while excluding whole mutableComp through facade/capture/unwrap. Proposed repair is finite, unimplemented/unverified; no solver/source acceptance/iteration general algorithm redesign or GREEN claim.

Preserve exact actual caller and source/session/type/proof/pool lifetimes, ordering/defaults, diagnostic provenance, legitimate mutation and error prefixes in the pinned answer. A wrapper or callback retaining unrelated whole compiler authority is not a narrowing. Readonly grants are not writers. Cover relevant normal, rejected, boundary and failure-prefix controls, verify the real producer-to-final-consumer path and remove competing broad signatures. No statement of future GREEN is evidence that the repair has passed.

## Excluded
Other groups and already-owned repairs; language/solver/iteration/source algorithm redesign, product execution/changes/performance or GREEN within this audit. Outer source publication, body readiness and executable queues stay with their callers.


