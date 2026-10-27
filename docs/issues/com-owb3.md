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
