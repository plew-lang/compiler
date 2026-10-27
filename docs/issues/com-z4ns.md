---
id: com-z4ns
status: open
deps: []
links: []
created: 2026-10-27T20:14:26Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Reconcile external Array method fixture with module-owned implementations

## Finite Boundary

Source-only batch0089 audit at9665094d/spec5bd65a5: tests/fixtures/run/array_methods.pw declares pub impl[T] Array[T] in an unrelated module. spec07 unnamed impl placement requires the defining module; Array is now an ordinary standard type. The historical766c3791 generic builtin Array dispatch regression remains useful but cannot license an external inherent-impl exception. Report meta/evidence/test-audit/scoped-reviews/runtime-batch-0089.json.

Preserve generic element substitution and method/call-result behavior through an authorized named extension or defining-module form, plus a precise foreign-inherent rejection and authorized positive contrast. Do not merely delete the regression or introduce compiler/test-name privileges. Derive selection source/owner from normal lookup and retain it through final call. Actual repair follows TDD and scoped independent review; existing output10/20/3 is correct conditional on old admission, no current compiler execution was made in audit. No global extension feature rewrite or phase3/whole-audit certification.

