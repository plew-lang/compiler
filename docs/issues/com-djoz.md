---
id: com-djoz
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:20:07Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Receiver-free physical/metadata leaves and unread arguments

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/llvm-physical-services-and-runtime.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-llvm-physical-services-and-runtime.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Exactly affected unused Comp/LlvmCtx/body/eid inputs named by rows. Preserve row/type/body/index/sentinel/source occurrence identity; no mandatory decomposition of passive descriptors; update exact typed callers.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- llvm-concrete-struct-retain-witnesses: ['structRetainWitness: unused c']
- llvm-mid-buffer-inout-and-owned-destination-queries: ['midCanonicalOperandNeedsOwnedDestination']
- llvm-mid-canonical-binding-to-local-index: ['midCanonicalBindingLocal']
- llvm-mid-physical-boundary-layout-comparison: ['midBoundaryLayoutMatches']
- llvm-mid-coverage-reason-to-scalar: ['midPreflightCoverageDetail', 'midCallPreflightCoverageDetail', 'midEligibilityCoverageDetail']
- llvm-mid-buffer-element-type-reader: ['midBufferElementRef']
- llvm-mid-canonical-operand-value-and-type-readers: ['midCanonicalOperandTypeTerm: whole Comp/unused body/unused self']
- llvm-mid-canonical-call-argument-and-read-admission: ['midCanonicalCallArgumentAt']
- llvm-mid-closure-capture-admission-and-emission: ['midCanonicalClosureCaptures']
- llvm-mid-inout-storage-and-owned-home-admission: ['midCanonicalInoutStorage', 'midCanonicalInoutIsShared']
- llvm-struct-drop-witness-registration-and-invocation: ['structDropWitness: unused c']
- llvm-enum-active-payload-ownership-expansion: ['emitEnumOwnership.eid', 'emitEnumRelease.eid', 'emitEnumRetain.eid']
- llvm-concrete-enum-ownership-witness-registration-and-drain: ['enumReleaseWitness: unused c', 'enumRetainWitness: unused c']

## Actions and Completion
Confirmed narrowing follow-up: change the exact actual signatures/consumers, remove competing broad grants, preserve legitimate physical/native/cache/interner/diagnostic/source-ready/lifetime/restore effects, and independently verify with appropriate TDD/refactor controls. This audit itself performs no repair.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Language/source/ABI/runtime algorithm redesign, unrelated compiler facilities, speculative performance claims and product execution within the audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Adopted Implementation Intake

[com-71gu](com-71gu.md) classifies the exact confirmed scope as required existing-feature phase4 conformance. Required admission owner(s): com-h61e; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-llvm-physical.json) retains all main/mixed roles and normative grounds. Exact unused Comp/LlvmCtx/body/eid inputs and receiver-free metadata/physical leaves grant no unrelated authority. Preserve body/type/local/index/sentinel/source occurrence identities and already-admitted descriptors instead of decomposing coherent passive values.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
