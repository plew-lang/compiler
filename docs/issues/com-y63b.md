---
id: com-y63b
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:20:07Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Typed ARC and conversion service input investigation

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/llvm-physical-services-and-runtime.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-llvm-physical-services-and-runtime.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Only listed unresolved components/families plus their exact immediate final/type/ownership/vtable/witness dependencies. Enumerate read/write/cache/diagnostic/queue/type and source-ready dependencies per ARC class/conversion lane, not whole compiler algorithm. Produce complete narrow service contract before classifying raw Comp excess.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- llvm-typed-value-cell-cow-and-final-strong-release: None
- llvm-array-writable-capacity-and-owner-retain-gate: None
- llvm-finalized-value-arc-dispatch: None
- llvm-concrete-struct-retain-witnesses: ['emitStructRetain', 'emitRetainWitnessWalk', 'emitRetainWitnessBodies']
- llvm-array-final-owner-and-element-range-arc: None
- llvm-existential-copy-and-drop-thunk-generation: None
- llvm-finalized-existential-vtable-and-box-construction: None
- llvm-mid-runtime-buffer-call-emission: None
- llvm-mid-canonical-drop-admission-and-emission: None
- llvm-mid-canonical-aggregate-elements-and-construction: None
- llvm-mid-enum-cell-take-and-destructuring-emission: None
- llvm-mid-canonical-place-materialization: None
- llvm-mid-canonical-operand-value-and-type-readers: ['midCanonicalEmitOperand']
- llvm-mid-frozen-value-and-borrowed-conversion-emission: None
- llvm-mid-frozen-array-repack-emitter: None
- llvm-mid-frozen-enum-repack-emitter: None
- llvm-struct-drop-witness-registration-and-invocation: ['emitDeinitValue']
- llvm-finalized-struct-destruction-expansion: None
- llvm-typed-ownership-witness-queue-drain: None
- llvm-enum-active-payload-ownership-expansion: ['remaining enumNeedsDeinit/ownership physical services']
- llvm-concrete-enum-ownership-witness-registration-and-drain: ['emitEnumReleaseWitnessBodies', 'emitEnumRetainWitnessBodies', 'emitEnumRetainRef']

## Actions and Completion
Finite investigation: map the listed APIs and actual delegated service closure, retain exact owner/provenance/write/error contracts, and independently determine a supported justified/excess/unresolved disposition. Assign bounded repairs if needed, without claiming they passed.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Language/source/ABI/runtime algorithm redesign, unrelated compiler facilities, speculative performance claims and product execution within the audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

