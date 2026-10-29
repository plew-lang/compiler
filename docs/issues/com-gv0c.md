---
id: com-gv0c
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T18:20:07Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Prepared async activation input investigation

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/llvm-physical-services-and-runtime.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-llvm-physical-services-and-runtime.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This finite follow-up is independent of com-jno0/phase 3; no product repair was performed by the audit.

## Guarantee and Scope
Only listed async entry/frame/resume/suspend components. Close program lookup/liveness/body signature/source-ready/typed ARC/type layout/caches/diagnostic/runtime inputs, and explicit sync/async/local storage/parameter defaults. No Promise payload ABI or scheduling redesign.

Exact affected API subsets and preserved required data are owned by the linked decision rows:
- llvm-finalized-async-callable-registry: ['declareAsyncFns']
- llvm-async-entry-and-runtime-call-emission: ['genLlvmAsyncFunc', 'emitAsyncFns']
- llvm-async-canonical-frame-preparation: None
- llvm-async-resume-suspend-and-completion-emission: ['midAsyncSuspend', 'genLlvmMidAsyncResume']

## Actions and Completion
Finite investigation: map the listed APIs and actual delegated service closure, retain exact owner/provenance/write/error contracts, and independently determine a supported justified/excess/unresolved disposition. Assign bounded repairs if needed, without claiming they passed.

For an unresolved input question, first produce an exact direct/delegated reader/writer, identity, error and caller map for this finite scope and independently review the resulting justified/excess/unresolved disposition; assign finite repairs if necessary. For a confirmed narrowing, apply task-start TDD/refactor rules, preserve behavior with relevant controls, change real signatures and final consumers, and prove full unrelated authority is not retained through a wrapper/capture. Preserve cache/interner effects, source/session/owner lineage, diagnostics, restoration, lifetime and ordering. Readonly grants are not mutable grants. Enumerate actual callers rather than assuming representative examples or helper counts equal all call expressions. Review independently and run gates appropriate to the eventual change. Investigation completion must not claim repair/GREEN.

## Excluded
Language/source/ABI/runtime algorithm redesign, unrelated compiler facilities, speculative performance claims and product execution within the audit.
Optional components stay optional and must not become mandatory merely because they share a row. No changes to language acceptance are delegated by this issue.

