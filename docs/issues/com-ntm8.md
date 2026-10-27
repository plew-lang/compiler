---
id: com-ntm8
status: open
deps: []
links: []
created: 2026-10-27T19:08:00Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, diagnostics, verification]
---
# Strengthen scoped frontend rejection reasons and arity path controls

## Contract and Evidence

Scoped review F2 lists nine no-reason negatives; F3 generic_arity_construction also contains invalid annotation, so annotation rejection could mask construction handling; F4 test-check-command unused-type-error/global-conflict compare same generic errors across modes without intended reasons.

Contract: tests/README.md Test validity and coverage review and docs/design/verification.md. Scoped evidence: [F2,F3,F4](../../../evidence/test-audit/scoped-reviews/review-frontend.json); controlled driver observations and runtime controls reside alongside it. Audit did not modify compiler, fixtures, expectations or runners.

## Scope and Completion

For exactly F2 nine inputs, F3 construction/annotation pair and F4 two generated cases, verify original intent and isolate intended source rule with meaningful reason and neighboring positives. Preserve driver check/build agreement and no-execution checks. Separate shared classification com-fsuq; no arbitrary rewrite of every absent .err or new unsupported feature.

Repair requires task-start TDD, fixed candidate/input identity, relevant actual consumer checks, scoped independent review and applicable gates. This is a separately owned follow-up, not a child or dependency of com-jno0 or its audits. No phase-three certification implied.

## Explicit Part/Identity Control Extension

The later part outcome audit independently read four additional rejection
controls that have no diagnostic companion:

- `tests/fixtures/partreject/trait_view_unimported/Main.pw`
- `tests/fixtures/partreject/trait_owner_required_identity/Main.pw`
- `tests/fixtures/partreject/phantomdep/Main.pw`
- `tests/fixtures/reject/trait_subject_cycle_generic_edge_reuse.pw`

Include these exact four reason assertions alongside the original nine, not
the entire absent-.err corpus. They must distinguish missing explicit selector
binding, the actually selected trait's missing requirement, missing direct
dependency, and exact-instance cycle respectively. `phantomdep` also has legacy
manifest setup; com-7u8z must resolve the relevant canonical schema before using
that setup as a diagnostic oracle. A manifest parse/version failure is not its
intended rejection. Original intent and companion positive controls are recorded
in meta/evidence/test-audit/scoped-reviews/part-tail-0087.json. These were source
reads, not observed current-candidate reasons. Shared exit/internal-failure
classification remains com-fsuq, and audit repair remains separate.

## Explicit Part-Diamond Reason Control

Source-admission batch0003 independently reads exactly `tests/fixtures/partreject/partdiamond/{Main,A,B,C}.pw` as the paired root/part control. Main imports print but calls `print(1)` without a numeric type context and has no Main.err. The loader currently rejects the repeated part parent first; if that check regresses, forward-only numeric inference can still reject the bare literal, so generic rejection is insufficient evidence of diamond detection. Isolate the diamond reason and keep the single-parent positive. This adds one exact control to the existing finite diagnostic work, not the unread partreject corpus. No fixture was run or repaired.

## Explicit Two Visibility-Reason Controls

Batch0005 adds exactly `tests/fixtures/partreject/crossmoduleprivate/{Main,Pub,Priv}.pw` and `tests/fixtures/partreject/crossmoduleprivateglobal/{Main,Gl}.pw`. Both Main files use `print(value: ...)` while the selected Std print has an unlabeled parameter. Neither has Main.err. Even if visibility protection regresses, unrelated outer-call label rejection can still satisfy the generic rejection worker. Recover and preserve the original cross-module private callable/global isolation, isolate intended diagnostics, and use valid outer contexts with reachable public positives. No actual candidate or controlled execution is claimed. This exact five-file extension is separate from common failure classification and the unread no-reason corpus.

## Explicit Two Part-Structure Masking Controls

Batch0006 adds exactly partreject/partmissing/Main.pw and partreject/partcrossmodule/{Main,Other,Shared}.pw. partmissing has bare print(1) without numeric context, so rejection can persist if missing-part discovery is incorrectly skipped. partcrossmodule's Shared impl Z is also unbound in Other's module if shared membership is incorrectly allowed. Both lack Main.err. Isolate missing input and unique part membership reasons while preserving valid neighbor controls.

partfreefn was also read, but removing its intended part-only-impl restriction leaves a well-typed I64 triple. Missing diagnostic text alone is not a demonstrated competing-failure setup. Its reason coverage is optional, not a newly required fixture repair or a duplicate of shared com-fsuq classification.

## Explicit Arithmetic Rejection Setup

Batch0008 adds exactly tests/fixtures/reject/arith_no_trait.pw. It intends Add-unimplemented rejection for Pt, but has no .err and also writes malformed postfix `print(c.x~)` without importing print. Even if the Add check is missing, syntax/name failure can still pass the generic rejection predicate. Recover the original arithmetic-trait purpose, remove unrelated failure from the eventual scoped test and distinguish a valid Add-conforming control. Missing memberwise factory is not a defect here: same-module default construction is legal. No compiler/test modification occurred in audit.

## Explicit Chain Diagnostic-Anchor Regression

Batch0010 adds exactly tests/fixtures/reject/chain_value_type_mismatch.pw. Original path-fixed3d5bd4ec introduced it to ensure the synthetic optional-chain error points to the real ?.n token. The worker has no .err/reason/location assertion, so it cannot detect that original anchor regression. Moreover `use @Std/Core` binds namespace Core, not bare Chain used in its impl, and root Some(v=...) differs from the adopted payload label. Missing trait binding or label setup can reject before the intended continuation check.

Preserve the real source-offset assertion and intended failure class through an explicitly valid setup. Canonical inference of the output carrier is a separate finite question; do not guess a mismatch diagnostic from current lowering or freeze a guessed language rule to repair the test. met-2wca owns label migration; the new carrier question is separately named by the batch report. No arbitrary all-no-.err rewrite or compiler/fixture repair in audit.

## Explicit Nonassociative Comparison Detection

Batch0011 adds exactly tests/fixtures/reject/cmp_non_associative.pw. Its I64 a==b==c has no diagnostic companion: if the parser incorrectly groups left-associatively, the intermediate Bool is still compared to I64 and can fail for a different reason. Thus exit1 alone does not detect the intended nonassociative syntax rule. Preserve original d4a7a247 intent with a discriminating parser reason or a well-typed Bool chain contrast and valid explicitly parenthesized control. No observed compiler regression is claimed; shared crash classification remains com-fsuq.

## Explicit Two Empty-Match Rejection Controls

Batch0013 adds reject/empty_match_bool.pw and empty_match_unit.pw. Original ca23b3dd protects the rule that inhabited Bool/unit cannot have exhaustive zero-arm matches. Both instead return match value {} and have no .err: if coverage wrongly accepts zero arms, the match is classified source-diverging and its use as a return value can still reject. Isolate coverage from forbidden source-divergence value use with statement/branch context or a precise coverage reason; retain a genuinely empty enum elimination positive and rejected empty-enum direct value-use contrast. No observed candidate defect or new Never/type rule is claimed.

## Explicit Floating, Named-Value and Field-Anchor Controls

Batch0015 adds exactly reject/float_remainder.pw, fn_value_sig_binding.pw and field_typo_read.pw/.err. float_remainder uses two unsuffixed decimal literals inside generic print, so an erroneous floating % implementation can still leave ambiguous F32/F64 inference and satisfy exit1. Preserve original63b9b302 no-float-remainder intent using typed operands/context and valid integer/float-arithmetic contrasts.

fn_value_sig_binding originated5503b46f as function-signature incompatibility, but current comment instead protects named declarations not being values. The input still also mismatches I64 and String function signatures, so generic rejection cannot isolate that newer non-value rule. Recover both purposes and reuse existing named_fn_value_{untyped,field,arg,return} negatives plus the explicit fn_value closure-wrapper positive. They already isolate the non-value boundary; this root alone has weak discrimination, not a confirmed suite-wide coverage hole. Treat its reason/comment precision or deletion as optional after checking old signature coverage, avoiding redundant new tests.

field_typo_read originated3d5bd4ec to anchor .typo at the actual source token. Its specific message companion detects missing-field reason but not location, and no separate selected consumer was found by script/checker search. Retain message and add an actual path/line/token anchor assertion through the standard compiler diagnostics path; do not equate generic rejection with source-span verification. This exact three-root extension does not rewrite all missing companions, public FFI rules or unread span tests.

## Explicit Foreign-Declaration Label Boundary

Batch0015 also adds exactly reject/ffi_extern_c_label.pw. It intends to reject C declarations lacking explicit ~: suppression, but main invokes those labeled a:/b: parameters positionally. If declaration admission incorrectly permits labels while preserving them, ordinary call-label mismatch still yields exit1 and masks the declaration-boundary defect. Original72b7df2e requires explicit suppression rather than silently stripping labels. Isolate declaration rejection or require its exact reason, preserving a valid explicitly suppressed C declaration/call and ordinary labeled wrapper contrast. No blanket FFI change or actual compiler failure is claimed.

## Explicit Generic Factory Call-Syntax Context

Batch0017 reads exactly reject/generic_factory_requires_construction.pw/.err. The declared generic build body incorrectly calls a factory as T.make rather than JSX, and the companion pins that specific reason. Main also uses build[Value](), a retained unimplemented explicit free-call type-argument form documented by com-uutc. Preserve the intended body/call-kind rejection independently of that unsupported caller syntax, using the normal unused generic-body checking contract or another supported caller context. Do not require implementing the unrelated explicit-call feature just to isolate this regression, or credit its generic unsupported-form diagnostic as the specific factory reason. No current candidate was executed and no wrong-error PASS is proved by the companion.

## Explicit Source-Transfer and Newtype Declaration Controls

Batch0018 adds reject/give_result_before_return.pw: original e607bd5b checks give-result Array[String] versus [1I64], but a following return is now independently forbidden by the adopted source-transfer rule. Isolate block-result typing from that already-invalid suffix; preserve separate source-after-give rejection. No current candidate failure is claimed.

The read reject/give_unreachable_name.pw originated a73b1528 to catch an unknown name in an unreachable suffix. Since any code after give is now forbidden, it no longer discriminates unreachable-name checking. Its valid rejection can be retained/reclassified or removed as redundant after checking explicit source-transfer controls; this is optional purpose precision, not a demand for diagnostic recovery after the first error.

Batch0018 also adds reject/impl_on_newtype.pw. Original b27eeae5 intended the prohibition on user impls for newtypes. Main calls print without importing ordinary Std/Io, so an unrelated missing-name rejection can mask loss of the impl gate under adopted lookup. Preserve the declaration-only ban and valid inherited-method/as contrast using an isolated reason/input; do not make newtype methods user-definable or infer a language exception from current acceptance. These are exactly three inspected roots, not all give/newtype tests.

## Explicit Inline-Constraint Reason Isolation

Batch0019 adds reject/inline_trait_constraint.pw. Its original f81f8480 selected adding diff intended to catch silently discarded inline [T: Show] constraints. Show is undeclared/unimported and no .err is required: a different regression accepting inline constraints normally can still fail on Show lookup. Isolate the forbidden syntax with a valid local/imported trait or an appropriate diagnostic assertion, while retaining the original silent-drop regression intent. No blanket requirement for every missing .err is implied.

## Explicit Match Identity and Duplicate-Field Isolation

Batch0020 adds reject/match_unknown_variant.pw and match_pattern_dup_field.pw. The former constructs current Some(v=...), so an adopted-label error can reject even if unknown variant Other is accepted; keep the unknown-variant oracle distinct during met-2wca migration. The latter repeats field a and omits b: current checkDestructureComplete separately rejects duplicates and then missing fields. Removing duplicate detection alone still rejects for missing b. Preserve the original8978934c exactly-once regression, using a duplicate-specific assertion or a form covering all real fields as well as duplicating one. This does not require every pattern error to be independently diagnosed after the first failure.

## Explicit Type-View Rejection Isolation

Batch0021 adds reject/multiple_trait_type_view.pw. It writes both an illegal Sample#A#B annotation and the same illegal sample#A#B value. Current checkTypeViewSources and checkResolvedViewValid enforce these through separate type/value readers; losing the type-only gate can still reject at the RHS. Preserve the single-trait selector contract with a genuinely type-only input or type-specific diagnostic. The existing multiple_trait_value_view is the separate value-only contrast. This is a selected finite detection gap, not a reproduced compiler bug or a general demand for duplicated tests.

## Explicit Or-Pattern Legacy Setup Reclassification

Batch0022 adds reject/or_pattern_bind_mismatch.pw for optional purpose/setup disposition. Legacy enum payload braces can reject before the intended unequal-binding names. The same batch's canonical or_pattern_binding_names.pw/.err already isolates that rule with typed constant body and specific diagnostic. Recover original a4ef7a08 intent before retaining/migrating/reclassifying/removing the redundant old root; do not require another duplicate mandatory test or treat the stale brace form as adopted.

## Explicit Equality and Floating-Range Reason Isolation

Batch0023 adds reject/payload_enum_eq.pw and range_float_iterator.pw. The first originally2428a6fa guarded payload-enum equality without Eq, but unimported ordinary print can still reject if the Eq gate regresses. The second originally5303254e guarded the absence of Step on floating types, but both floating endpoints lack type context and its bare for value refers to no existing mutable binding (spec11:209); these failures can mask Step/Iterable admission. Establish explicit floating endpoint type and a legitimate loop binding while preserving the non-Step rejection, paired with range.contains and integer iteration contrasts.

The supplemental run/range_iterator_values.pw/.out has five bare for value loops with no prior mutable value binding. Preserve its six output lines, signed traversal, singleton maximum, repeated exhausted next and empty-range termination with valid new/previously mutable loop bindings. This exact positive setup pair belongs to the same finite iterator-oracle repair, not an all-for migration or a new language rule. No fixture was run or edited by the audit.

## Explicit Publication Visibility and Source-Anchor Checks

Batch0024 adds reject/selected_call_constraints_publication_private.pw/.err. Its outer publishPreparedCallConstraints and nested admitSelectedCallConstraints are independently private and share the same expected method-private text. Publishing only the outer method can still pass via inner rejection. Isolate publication using an external helper parameter of the already-public AdmittedCallConstraints type, without exposing its factory or skipping real admission. The inner admission gate has its own existing exact negative.

Also add record_lit_destructure_bad_field.pw and ref_arrow_missing_field.pw/.err to the finite source-anchor scope. Original108951ff and3d5bd4ec moved diagnostic provenance from interned names to actual bind/field tokens; current workers observe no location (first status-only, second message-only). Preserve the selected field/bind location contracts through a meaningful assertion or existing diagnostic checker; reference syntax migration remains met-op15.

return_unreachable_type.pw now violates the source-after-return rule before its old dead-type purpose. This is optional purpose reclassification/retention/deletion after original intent, like give_unreachable_name; do not require continued diagnostics after decisive forbidden suffix rejection.

## Explicit Generic-Payload Label Masking and Unknown-Pattern Purpose

Batch0027 adds exactly reject/tc_generic_arg_mismatch.pw and tc_generic_payload_value.pw. Both use Some(v=...) while adopted Optional declares value. Status-only rejection can survive a lost generic-instance/payload-type gate through unrelated wrong-label rejection. Original6541be59/cf3e07e4 intent is generic argument identity versus expected payload substitution, respectively. Isolate both under coherent met-2wca migration with positive grounded payload controls.

struct_pattern_type_mismatch.pw uses undeclared P, but original539c37a8 deliberately covers unknown/nonstruct pattern crash-to-clean rejection. Keep that original guarantee; a known-struct/wrong-subject contrast or precise reason is optional coverage, not a newly proved mandatory mask merely because P is absent.

## Explicit Optional-Try Rejection and Dead-Operator Purposes

Batch0030 adds exactly reject/try_on_optional.pw. Some(v=...) can reject for an unrelated adopted payload-label failure if the intended Result-only try gate regresses; preserve actual Optional versus Result early-return semantics through met-2wca migration and selected reason.

The exact type_operator_reject_dead_{block_59,if_68,match_77}.pw and type_operator_return_dead_invalid_add.pw originally799bc300 check bad operators after a transfer. Adopted spec11 now forbids every such source suffix. Reclassify/retain/delete their optional old purpose without demanding additional operator diagnostics after the decisive transfer error. Live-invalid operator control stays meaningful.

The fully read supplemental run/source_operator_literal_context.pw/.out has two bare for operation loops without an existing mutable binding (spec11). Preserve closed first-source operator selection, contextual operands, refusal to repair missing frozen selection and comparison Bool projection through valid loop bindings. This is one exact positive setup pair, not an all-for migration; no fixture was executed or edited.

## Explicit Enum-Deinit Rejection and Unique-Return Control

Batch0031 adds exactly reject/unique_enum_deinit.pw. It intends to reject explicit enum deinit but its Cell struct also contains a forbidden struct-body deinit (spec03); with status-only expectation, losing enum rejection can still pass on unrelated placement error. Preserve enum-specific rejection with an admitted payload declaration under met-2t3l migration.

Supplemental run/unique_move.pw/.out also returns the existing local f bare from makeFile and describes implicit move. spec03 requires explicit ownership mode and has no located local-return exception; spec04 return completion does not grant it. Preserve the four ownership/output events through adopted explicit transfer and coherent deinit migration rather than certifying this old positive as source-clean. This is one exact control, not all unique return bodies or an added implicit-move rule.

## Explicit Local-Type Visibility and Missing-Give Isolation

Batch0033 adds exactly reject/use_type_without_import_localval.pw. Its initializer is the undeclared identifier none, not <Optional.None />. If the Tok local-annotation visibility gate regresses, unknown none can still keep this status-only negative passing. Preserve local annotation visibility with an admitted Optional empty initializer and selected reason. Tok and kindCode exist in the pinned Syntax source, so this is not absence of the external declaration; the parameter/newtype sibling negatives have no located independent setup mask.

Also add value_if_no_give.pw and value_match_no_give.pw for their intended missing-give reason isolation. Both contain unsuffixed discarded integer expressions without a local type; source Literal/Record walks retain a no-context numeric failure independently of the give requirement. Originalcebb4528 explicitly describes this alternative error. Keep distinct if-branch and match-block coverage through a typed/suffixed payload or selected diagnostic, preserving no implicit tail value. This is static detection analysis, not an executed checker mutation or a demand for extra diagnostics after decisive rejection.
