---
id: com-bfvd
status: open
deps: []
links: []
created: 2026-10-27T19:19:55Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, runtime, verification]
---
# Reconcile ordinary panic function admission in five runtime fixtures

## Contract, Evidence and Scope

spec 11-control-flow requires explicit use of ordinary @Std/Core diverge fn panic(message~:String). Five panic fixtures (diverging_call, diverging_callable_storage, diverging_field_invocation, diverging_local_invocation, match_expr_panic_arm) use no Core panic import, some with legacy panic statement form. Existing runtime intent is sound; source does not certify current-spec admission. Pinned current implementation still admits legacy forms; no candidate execution. Existing com-8j0w mentions panic/exit integration generally but does not explicitly own this migration.

Bounded follow-up: recover original five test purposes; trace public Std/Core panic declaration, parser keyword/statement path, ordinary name/import lookup and divergence callable result handling. Produce a concrete migration/repair with finite required consumers and source controls before editing fixtures; do not merely add imports or change statements before the ordinary-function API exists. Preserve abort/no-unwind behavior and direct/local/field/generic/associated-value invocation coverage. Distinguish current supported subset from adopted surface. No new general effect/lifetime feature, no all-Std migration. TDD and independent review for any later implementation; audit itself only assigns this work.

Scoped evidence: meta/evidence/test-audit/scoped-reviews/runtime-batch-0084.json and batch-0084-disposition.json (test/source baseline 9665094d). This is a separate finite follow-up, not a child/prerequisite of the audit epic or a claim repairs passed.


