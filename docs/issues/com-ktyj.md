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



## Adopted Implementation Intake

[com-k35g](com-k35g.md) classifies this exact confirmed scope as required existing-feature phase4 conformance. Required admission owner(s): met-k7ks, com-h61e; actual tk prerequisites retain the open repair.

[Scoped intake outcome](../../../evidence/existing-feature-conformance/audit-intake/api-session-and-inputs.json) preserves every main/mixed role and the normative reason. Current phase observations and owned diagnostic/output finishing must not inherit arbitrary compiler mutation. Preserve quiet/trace/output/error/native release ordering; no new monitoring or CLI semantics.

The original audit-time independence does not waive this implementation admission. Keep the original finite guarantee, caller/delegate/control and excluded optional scopes. This is assignment only, not product repair/GREEN.
