---
id: com-owb3
status: open
deps: []
links: []
created: 2026-10-27T19:56:08Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, generics, verification]
---
# Reconcile generic factory fixture binders with explicit impl declarations

## Finite Investigation and Repair Boundary

Audit source baseline9665094d/spec5bd65a5. Exact scopes: part/namespace_type_generic/Models.pw (`pub impl Box[T] { factory }`, T has no explicit impl binder), run/aggregate_infer_recorded_fields.pw (`pub impl Measurement { factory }`) and run/any_generic_param.pw (`pub impl Wrapper { factory }`). spec06 impl parameters require introduction by impl[...] and distinguish binders from type uses. First shape has an undeclared T and is a confirmed explicit-binder migration candidate. The two bare-owner publication markers are not automatically the same invalid shape: determine whether a specified shorthand exists before changing them; consult spec05/07 and original intent.

Source-only evidence in part-batch-0086.json/run-head-0087.json under meta/evidence/test-audit/scoped-reviews. Original c0b5b54b intended qualified Box[I64] identity/output41, not implicit binder syntax. Preserve the numeric/identity regression; never bless syntax because current compiler accepts it.

## Deliverables and Guarantees

Derive each admission ruling from canonical rules, preserving default memberwise factory publication and correct lexical ParamIds. If the bare-owner shorthand lacks a decided meaning, obtain a surface decision instead of inferring a new rule. Migrate confirmed stale fixture syntax and add actual positive/reject controls distinguishing explicit binder, unbound T, concrete Box[I64] and any accepted bare publication form. Ensure actual registration and final factory call consume the same binder identity; no special-case fixture handling.

## Completion

Rulings for all selected forms and exact extended roots, preserved original coverage, finite owned implementation gap if found, relevant RED/GREEN and independent review. Not a whole-corpus generic rewrite. The rest of source-admission audit remains its original work.


## Paired Rejection Setup

`tests/fixtures/partreject/namespace_type_argument/Models.pw` repeats the undeclared `Box[T]` form. Read its Main.pw/Main.err and preserve the intended rejection of type arguments on a namespace; setup migration must not silently replace that reason with an unbound-binder rejection. This exact auxiliary scope accompanies the Box positive, not an audit of all partreject inputs.

## Explicit Three-Root Same-Form Intake Extension

Batch0089 adds bare generic-owner factory markers in exactly
`tests/fixtures/run/array_generic_field.pw` (Holder),
`tests/fixtures/run/array_literal_inferred_element.pw` (Box), and
`tests/fixtures/run/associated_callable_invocation.pw` (Projected). Apply the
same eventual bare-publication ruling, without conflating them with the
undeclared Box[T] binder. Preserve their respective generic field, inferred
array element and associated callable result/control coverage. The rule is
undecided; no fixture change is authorized merely by current parser behavior.

## Explicit Variant-Argument Rejection Setup

The source-admission audit also reads exactly `tests/fixtures/partreject/namespace_variant_argument/{Main.pw,Models.pw,Main.err}`. Models repeats the same undeclared `pub impl Box[T]` binder. Main intends to reject `<Models.Choice.Some[I64] value=41I64 />`, with the specific reason that only the constructed type accepts type arguments. Preserve that reason while migrating the unrelated Box setup; unbound-T failure is not a substitute. This is one supplementary control, not a newly audited primary plan unit or the unread partreject corpus.

## Explicit Paired Literal-Range Bare-Publication Context

Batch0007 reads `tests/fixtures/reject/aggregate_infer_literal_range.pw` and its .err. It repeats the bare generic `pub impl Measurement { factory }` of the already named run positive. Include this exact negative when deciding any bare-owner publication shorthand, preserving the intended 256-versus-U8 range reason and com-pxja's separate forward sibling-inference question. This is not the confirmed unbound Box[T] form or an extra source rule.

## Explicit Associated-Receiver Negative Context

Batch0008 adds exactly tests/fixtures/reject/assoc_disjoint_receiver_ambiguous.pw. The bare generic `pub impl Box { factory }` has the same unresolved publication meaning as the existing bare-owner representatives. Preserve its actual source requirement: Box.tag() cannot select Box[I64] versus Box[String] by declaration order without receiver type information. Missing .err alone is optional diagnostic coverage, not another proved masking bug; do not conflate a declaration-setup question with permission to resolve that ambiguous call.

## Explicit Four Standalone Rejection Setups

Batch0011 adds exactly tests/fixtures/reject/{closure_capture_generic_inst,concrete_conformance_does_not_match_other_instance,concrete_conformance_trait_view_mismatch,concrete_supertrait_does_not_cover_other_instance}.pw. Each has the unresolved bare generic pub impl Box { factory } publication marker, not an undeclared Box[T] binder. Include them in the same eventual source ruling while preserving distinct captured generic representation, concrete conformance instance, explicit trait-view and supertrait coverage. Capture of generic structures is an explicitly current unsupported lane, not an adopted prohibition or a request to implement it in audit. No other unread bare-owner roots are transferred.

## Explicit Three Named-Extension Negative Setups

Batch0014 adds exactly reject/{extension_conformance_generic_overlap,extension_conformance_only_view_generic_mismatch,extension_generic_concrete_receiver_overlap}.pw. Their pub impl Box {factory} markers repeat the unresolved bare generic publication form. Apply the same canonical shorthand/binder ruling while retaining same-extension overlapping conformance, inapplicable concrete receiver view and generic/concrete member receiver overlap as separate rejection purposes. These are not newly proved undeclared-T defects or all unread extension tests.

## Explicit Generic Field-Default Control

Batch0015 additionally reads run/field_defaults_generic.pw/.out, whose pub impl Box {factory} is the same unresolved bare-publication shape. Include exactly this pair in the existing source ruling, preserving concrete default field substitution, fresh array and override results5/99/0/1/2. This is supplemental control scope only, not a newly completed primary admission/outcome or an automatic invalid-binder diagnosis.
