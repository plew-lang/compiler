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
# Reconcile ordinary panic function admission in selected regression fixtures

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

## Explicit Two Divergence-Declaration Negatives

Batch0012 adds exactly reject/diverging_async_modifier.pw and reject/diverging_call_following_statement.pw with the latter .err. The first combines async/diverge illegally but also calls panic without explicit use; the second has legacy panic statement syntax inside a diverge function before testing forbidden following code at its call site. Preserve the modifier and source-transfer diagnostic purposes through ordinary imported panic migration. Specific following-statement .err prevents unrelated missing-panic rejection from being credited. Current legacy admission is not proof of adopted source validity. These extend only the representative set; compiler guards and all unread fixtures are not silently transferred.

## Explicit Five Divergence-Value Negatives and Three Storage/Flow Controls

Batch0013 adds exactly reject/{diverging_call_value,diverging_closure_contract_erasure,diverging_closure_contract_strengthening,diverging_dynamic_call_value,diverging_spawn_modifier}.pw with their existing companions. Four use legacy panic statement syntax; spawn uses panic() without importing it. Preserve direct/dynamic invocation value prohibition, strict normal/diverge closure contracts and forbidden spawn/diverge combination through ordinary panic migration. Specific .err predicates remain distinct from unrelated setup rejection.

The fully read supplemental run/{diverging_call_flow,diverging_callable_declarations,diverging_callable_storage}.pw/.out add three bounded contexts using the same legacy/unimported panic forms. Preserve branch result42, uncalled divergence declarations and stored/copied/projected callable values; they are source/oracle controls, not evidence their abort branches executed. run/diverging_loop_invocation_boundary is a separate panic-free control, not a migration input. The finite representative set is19 roots after these exact eight additions; neither unread source nor all compiler internal guards are silently transferred.

## Explicit Four Memberwise-Collision Negatives

Batch0015 adds exactly reject/factory_memberwise_{collision,default_collision,empty_collision,generic_collision}.pw and their .err companions. All custom factory bodies call panic() without the adopted ordinary Core import. Preserve full/default/empty/generic collision declaration rejection and its specific anonymous-factory-overlap diagnostic under a coherent panic migration. A body/name error cannot replace the required companion. The representative set is23 roots after these exact four additions; no compiler/test/expectation change or execution occurred in audit.

## Explicit Generic Enum-Inference Fallback Control

Batch0017 adds the supplemental run/generic_enum_field_inference.pw/.out, whose two unexecuted failure arms call panic without importing the ordinary Core function. Preserve successful array/String payload inference and fallback diagnostics without pretending those arms executed. Optional payload labels are owned by met-2wca. This adds one representative root (24 total at this intake), not all generic-enum fixtures or actual abort-path coverage.

## Explicit Source-Transfer Mapping Control

Batch0018 adds exactly run/source_transfer_targets.pw/.out as a supplemental internal control. Its invariant-failure branches call panic without the adopted ordinary Core import. Preserve source return/give/break/continue owner identity, wrong-session/kind rejection and the final Mid consumer mapping; this source-only read neither executes those arms nor certifies the complete internal service API. This extends the representative set to25 named roots, not all source guards.

## Explicit Import-Provenance Supplemental Control

Batch0019 adds run/import_origin_provenance.pw/.out. Internal provenance-table assertions use legacy unimported panic statements. Preserve original/local module identity, independent copy tables, re-export distinctions and first-binding retention through ordinary panic migration; no failure branch was executed. This is the26th named representative root, not a claim to have inventoried every internal guard or audited its complete primary service contract.

## Explicit Mid Source-Owner Supplemental Control

Batch0020 adds run/mid_source_owner_admission.pw/.out. Its invariant-failure arms use panic without the ordinary Core import. Preserve valid prepared source acceptance, wrong-owner statements/facts, absent admission and foreign-session rejection through coherent panic migration. This27th representative root is a qualified supplemental read; it neither ran the failure branches nor certifies all Mid/source fact APIs.

## Explicit Return-Path Supplemental Control

Batch0021 adds run/return_paths.pw/.out. The C arm of classify uses a legacy unimported panic statement. Preserve source-return coverage for exhaustive match, if/else and the noncompleting while form, all five normal outputs and abort behavior under ordinary imported panic migration. This28th representative root is a supplemental source read, not proof the panic arm ran or a complete control-flow API audit.

## Explicit Diverging Operator-Witness Negative

Batch0022 adds reject/operator_diverging_witness.pw/.err. Its assoc diverge fn Neg witness uses a legacy unimported panic statement. Preserve normal-versus-diverge requirement contract mismatch and the specific incomplete-conformance diagnostic under ordinary panic migration. This29th representative input is not evidence the operator was invoked; no new conformance exception or primary control execution is claimed.
