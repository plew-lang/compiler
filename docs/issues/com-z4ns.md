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
# Reconcile foreign-type impl fixtures with module ownership

## Finite Boundary

Source-only batch0089 audit at9665094d/spec5bd65a5: tests/fixtures/run/array_methods.pw declares pub impl[T] Array[T] in an unrelated module. spec07 unnamed impl placement requires the defining module; Array is now an ordinary standard type. The historical766c3791 generic builtin Array dispatch regression remains useful but cannot license an external inherent-impl exception. Report meta/evidence/test-audit/scoped-reviews/runtime-batch-0089.json.

Preserve generic element substitution and method/call-result behavior through an authorized named extension or defining-module form, plus a precise foreign-inherent rejection and authorized positive contrast. Do not merely delete the regression or introduce compiler/test-name privileges. Derive selection source/owner from normal lookup and retain it through final call. Actual repair follows TDD and scoped independent review; existing output10/20/3 is correct conditional on old admission, no current compiler execution was made in audit. No global extension feature rewrite or phase3/whole-audit certification.


## Explicit Foreign Trait-Impl Setup Extension

Batch0008 adds exactly tests/fixtures/reject/any_sendable_generic_shadow_newtype.pw and .err. Besides the intended generic sendable-guarantee rejection, this root writes `impl I64 as Numberish` outside I64's defining Core module. Spec09 requires a named extension even when the target trait is local. The negative's type-mismatch companion can fail on a correct earlier ownership diagnostic; current acceptance of the illegal setup is not normative proof.

Preserve the original shadowing stress: global newtype Payload inherits the intended Numberish evidence, but the function's generic Payload must not borrow that global nominal/sendability fact. Recover the original setup and find an owner-authorized local nominal/extension form keeping that contrast. Do not merely remove the bait witness and weaken the regression. Include missing generic sendable proof, valid declared proof and foreign-impl rejection contrasts. This explicitly adds one root to the earlier Array inherent-impl fixture; different custom-trait versus inherent paths remain separately exercised. No general coherence rewrite or unread-corpus transfer.

## Explicit Conditional-Proof Fixture Setup

Batch0011 adds tests/fixtures/reject/conditional_conformance_nested.pw and .err (foreign impl I64 as Marker), plus the fully read supplemental run/conditional_conformance_{constant_subject,edge_path,methodless,nested,permuted,root_path,view}.pw and .out. All seven positives append foreign impl I64 as Required, and nested also declares foreign I64 as Marker. Preserve constant-subject, selected root/edge paths, methodless/nested/permuted substitutions and extension-view proof provenance using an owner-authorized setup. Empty output is intentional compile/body-check coverage, not proof of a runtime effect.

Specific missing-bound companions do not treat an earlier foreign-owner error as success. Recover original intent and retain clean positive/negative contrasts without broadening or weakening proof requirements. Conditional trait-to-trait edge acceptance is a separate adopted-oracle question owned by com-wfq2; correcting foreign I64 ownership does not settle it. This is exactly one primary negative plus seven supplemental positives, not newly completed primary obligations for the latter.

## Explicit Dictionary Selected Signature Source

Batch0044 adds exactly run/dictionary_selected_method_signature.pw/.out. Unnamed impl[Key,Value] Dictionary[Key,Value] as locally owned NumberKey is still a foreign-type implementation under spec07. Preserve distinct method key:I64 versus receiver Key=String signature selection using an owner-authorized type or named extension; no compiler special case based on dictionary spelling.

## Explicit Primitive Generic Method-Inout Source

Batch0050 adds exactly run/generic_method_bound_inout.pw/.out. pub impl U64 as locally owned Absorb is a foreign unnamed implementation; spec07/09/15 require type-owning module regardless trait ownership. Preserve actual8085b90e primitive/String transitive method-instance and nested inout source purpose via an authorized named extension or defining-module form. Do not merely delete primitive coverage or create a local-trait exception. No current compiler behavior was tested.

## Explicit Inherited Newtype Custom Trait Setup

Batch0063 adds exactly run/newtype_conformance_inherit.pw/.out. pub impl String as local Loud is foreign unnamed impl under spec07/09. Preserve inherited standard String/I64 formatting and custom witness dispatch using owner-authorized setup, not a local-trait exception. No current compiler bug reproduced.
