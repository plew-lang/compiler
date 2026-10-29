---
id: com-50me
status: open
deps: []
links: [com-mmk9]
created: 2026-10-29T17:18:38Z
type: task
priority: 2
assignee: Koji Murata
tags: [driver, diagnostics, verification]
---
# Determine terminal preparation-diagnostic input authority

Evidence: [capability decision](../../../evidence/compiler-api-audit/capabilities/boundary-values-and-observation.json) and [independent review](../../../evidence/compiler-api-audit/review-capability-boundary-values-and-observation.json), audited from source 9665094dcec8aa63ed20573b1306a0015058f595. Parent audit: [com-mmk9](com-mmk9.md). This follow-up is independent repair/investigation ownership, not a new completion requirement for com-jno0 or phase 3.

## Question and Finite Scope
The legacy terminal presenter has no current production caller, but programPreparationDiagnostic reaches declarationProgramDiagnostic, reportMidBuildError and midPreparationDiagnostic. Follow the finite ProgramPreparationError variant/converter tree and record required owner/source/body lookup, diagnostics, trace and failure effects. Decide whether its Comp authority is justified, excessive or removable as an unused adapter.

## Deliverable and Completion
Pin source/facts, identify actual callers including fixture-only/recursive paths, distinguish converting domain errors from rendering/exit policy, and specify a narrower required service only when it preserves provenance/effects. Independently review the classification and assign any confirmed finite correction. Close as investigated without claiming a renderer repair.

## Excluded
Implementing a renderer refactor, deleting diagnostics, changing CLI behavior or auditing all compiler algorithms. Do not assume all preparation errors already contain fully rendered diagnostics.


