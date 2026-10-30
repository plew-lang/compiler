---
id: com-lgu1
status: closed
deps: []
links: [com-mmk9]
created: 2026-10-29T18:20:07Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Physical place/call/intrinsic support input investigation

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/llvm-physical-services-and-runtime.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-llvm-physical-services-and-runtime.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Only listed Mid support/preflight/runtime-call components. Close canonical/global/type/newtype/reference/native layout/target C/diagnostic/cache dependencies including allowDeref and Read/Copy/Move/Inout lanes. Decide pure reader vs limited memo/native writer explicitly; do not remove effects based on Bool result.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- llvm-mid-buffer-inout-and-owned-destination-queries: ['midCanonicalBufferInoutOperandSupported']
- llvm-mid-runtime-buffer-call-admission: None
- llvm-mid-strong-weak-cell-control-admission-and-emission: ['midCanonicalCellControlPreflight', 'midCanonicalEmitCellControl']
- llvm-mid-strong-cell-new-move-admission-and-emission: ['midCanonicalStrongCellPreflight', 'midCanonicalEmitStrongCell']
- llvm-mid-direct-call-physical-admission: None
- llvm-mid-canonical-call-argument-and-read-admission: ['midCanonicalReadOperandSupported']
- llvm-mid-runtime-system-call-admission-and-emission: ['midCanonicalRuntimeSystemPreflight', 'midCanonicalEmitRuntimeSystemCall']
- llvm-mid-runtime-core-string-and-ffi-admission-and-emission: ['midCanonicalRuntimeCoreStringFfiPreflight', 'midCanonicalEmitRuntimeCoreStringFfiCall']
- llvm-mid-runtime-numeric-admission-and-emission: ['midCanonicalRuntimeNumericPreflight', 'midCanonicalEmitRuntimeNumericCall']
- llvm-mid-place-and-operand-physical-admission: None
- llvm-mid-initial-rvalue-physical-admission: None
- llvm-mid-inout-storage-and-owned-home-admission: ['midCanonicalInoutPlaceSupported', 'midCanonicalInoutOperandSupported']
- llvm-mid-receiver-mode-physical-admission: None

## Actions and Completion
Finite investigation: map the listed APIs and actual delegated service closure, retain exact owner/provenance/write/error contracts, and independently determine a supported justified/excess/unresolved disposition. Assign bounded repairs if needed, without claiming they passed.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Language/source/ABI/runtime algorithm redesign, unrelated compiler facilities, speculative performance claims and product execution within the audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.


## Input Investigation Outcome

The original required input/delegate-authority questions are answered, not merely
assigned elsewhere. [Exact answer](../../../evidence/compiler-api-audit/resolutions/physical-support-inputs.json)
and [independent review](../../../evidence/compiler-api-audit/review-resolution-physical-support-inputs.json)
record the complete named scope, necessary inputs/effects, actual caller contexts,
source identity and supported C conclusion. Required input questions remaining
in this scope: none. Product repairs remain unimplemented and unverified.

Repair ownership: [com-70tb](com-70tb.md), [com-3j3n](com-3j3n.md). These repair issues are not evidence of the conclusion; the linked
source closure and independent review are. This closes only this finite
investigation, not com-mmk9 or any product implementation milestone.
