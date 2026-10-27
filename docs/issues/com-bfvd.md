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
# Reconcile ordinary panic function admission in nine representative fixtures

## Contract, Evidence and Scope

spec 11-control-flow requires explicit use of ordinary @Std/Core diverge fn panic(message~:String). Six panic fixtures (diverging_call, diverging_callable_storage, diverging_field_invocation, diverging_local_invocation, match_expr_panic_arm, span_equality_identical_out_of_bounds) use no Core panic import, some with legacy panic statement form. Existing runtime intent is sound; source does not certify current-spec admission. Pinned current implementation still admits legacy forms; no candidate execution. Existing com-8j0w mentions panic/exit integration generally but does not explicitly own this migration.

Bounded follow-up: recover original six test purposes; trace public Std/Core panic declaration, parser keyword/statement path, ordinary name/import lookup and divergence callable result handling. Produce a concrete migration/repair with finite required consumers and source controls before editing fixtures; do not merely add imports or change statements before the ordinary-function API exists. Preserve abort/no-unwind behavior and direct/local/field/generic/associated-value invocation coverage. Distinguish current supported subset from adopted surface. No new general effect/lifetime feature, no all-Std migration. TDD and independent review for any later implementation; audit itself only assigns this work.

Scoped evidence: meta/evidence/test-audit/scoped-reviews/runtime-batch-0084.json and batch-0084-disposition.json (test/source baseline 9665094d). This is a separate finite follow-up, not a child/prerequisite of the audit epic or a claim repairs passed.



## Additional Same-Contract Evidence

The exact seven internal-panic-outcome audit adds only the span fixture to the
representative root-input scope above; its fallback has a legacy panic statement.
Imported Frontend/Ir/SourceFiles invariant guards and positive controls also use
legacy panic. Inventory their affected migration handoffs when planning the
ordinary-function boundary; do not rewrite them anonymously inside this audit or
claim that changing six root fixtures alone implements the public API. This
remains bounded admission/migration investigation, not an all-compiler rewrite.
The original first-five review remains exact historical evidence; the extension
is recorded explicitly here rather than silently changing that report.

## Explicit Seventh Representative Root

Batch0088 adds `tests/fixtures/run/any_sendable_erasure.pw`: both unused failure
arms use the legacy panic statement. Keep this positive-path context when
inventorying ordinary imported panic admission; it is not a claim those branches
ran or trapped. Its nominal-Self/container conversion reconciliation is com-vp0o,
not part of implementing panic. Seven representative roots do not constitute an
all-source migration inventory; imported guards still require the bounded
handoff investigation above.

## Explicit Eighth Representative Root

Batch0089 adds `tests/fixtures/run/array_forward_element_context.pw`: three
positive-control fallback calls use panic without importing the ordinary Core
function. Preserve array forward context, generic String payload and nested
empty-array checks; no failure branch was executed by this audit. This expands
only the named representative input set, not the complete compiler migration.

## Explicit Ninth Representative Root

Batch0009 adds exactly tests/fixtures/reject/associated_literal_context_unknown.pw and its .err context. Holder[T].empty's unused body calls panic without explicitly importing the ordinary Core function; the intended negative is absent generic receiver/result context at Holder.empty(). Preserve that inference rejection and its specific diagnostic, rather than allowing ordinary panic name/surface migration to replace it. No failure arm or compiler was executed. This extends only one representative root, not an all-compiler migration or an audit of other unread associated calls.
