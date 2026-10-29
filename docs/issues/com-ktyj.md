---
id: com-ktyj
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T17:18:38Z
type: task
priority: 2
assignee: Koji Murata
tags: [backend, driver, diagnostics, verification]
---
# Narrow phase observation and compiler finishing inputs

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/boundary-values-and-observation.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-boundary-values-and-observation.json), audited from source 9665094dcec8aa63ed20573b1306a0015058f595. Parent audit: [com-mmk9](com-mmk9.md). This follow-up is independent repair/investigation ownership, not a new completion requirement for com-jno0 or phase 3.

## Guarantee and Scope
Public phase helpers receive an observation flag/service plus explicit label/count/stride. LlvmModule.writeText receives no Comp solely for tracing; output stays stdout. finishCompilation receives owned diagnostics drained by its caller, owned LlvmLoweringResult, emitText and observation policy rather than full Comp. Preserve all other native module/context/JIT/argv ownership APIs.

## Actions and Completion
Characterize trace enabled/disabled, stride/count boundaries, diagnostic-before-output ordering, success/failure and emitText modes. Move the existing diagnostic drain to the corresponding caller point without evaluating it twice; preserve warning/error values and module release/transfer order. Update all real observers/consumers and remove broad forwarding routes. Verify no unrelated arena/Mid/decls/cur/Mono/source-fact authority remains in these observer/finishing APIs. Follow TDD/refactor rules and obtain independent review.

## Excluded
Changing phase or CLI semantics, monitoring, work counters, native/JIT lifetime algorithms, diagnostic conversion policy or performance optimization. CLI orchestration may still own the full construction session.


