---
id: com-lm8j
status: open
deps: []
links: []
created: 2026-10-27T20:14:26Z
type: chore
priority: 3
assignee: Koji Murata
tags: [verification, tooling]
---
# Align inspected fixture descriptions with current execution contracts

## Finite Documentation Correction

Selected source-audit descriptions assert mechanisms no longer owned by their current tests. Correct only the named comments/claim boundaries while retaining input behavior and meaningful assertions:

- run/assoc_val.pw: stored eager associated value, not a zeroarg function reevaluated per access; original fee81cae explains historical intent. Constants/read/composition output remains valid, not a startup-effect test.
- run/array_enum_payload_function_copy.pw: non-main call remains useful; no retired separate direct-LLVM path is claimed when bodies all require Mid.
- run/ambient_core.pw: fixed language-item names/syntax operations are ambient, not all of Core.
- run/any_box_value_semantics.pw, any_basic.pw, any_generic_param.pw, any_array_covariant_erasure.pw: logical value independence, not mandatory immediate deep copies or fixed8/16-byte physical layouts.
- run/any_for_iterator.pw: iterator() produces the protocol iterator copy; do not assert original binding state from loop output alone.
- part/trait_owner_reexport_generic/Main.pw: current signature has no associated projection; part/trait_owner_reexport_type is the separate concrete projection control.
- part/reexport/Barrel.pw: pub use supplies the local binding as well as forwarding; the consumer does not observe local binding in this fixture.

## Completion and Limits

Use spec/design as authority, preserve original limited regression purposes and links to separate stronger controls. Accurate descriptions of a deliberately tested internal representation need not be erased; remove only false current-path claims and wording that promotes an incidental mechanism to a semantic requirement. Actual fixture comment edits belong to repair after audit, no requirement to add every stronger interaction or rewrite outputs. any_array_covariant_erasure admission migration remains com-vp0o; coordinate rather than retain contradicted commentary. Do not add broad startup/ARC requirements to this chore. Verify comment-only diff/unchanged executable inputs, references and independent review; no fabricated TDD RED for prose. Evidence run-head-0087.json, part-tail-0087.json, runtime-batch-0088.json and runtime-batch-0089.json under meta/evidence/test-audit/scoped-reviews. This issue is separate from audit completion.


## Explicit Dictionary Rejection Comment

Batch0007 additionally reads exactly tests/fixtures/reject/any_dict_covariant_no_repack.pw and its .err. Rejection remains correct under generic invariance. The comment instead grants Array/generic-enum covariance and justifies Dictionary exclusion by historical fixed layouts/absent backend repacking. Align that one description with the adopted invariant source rule, preserving the useful direct per-insert boxing contrast and intended rejection; do not change semantics or golden just to retain a former physical explanation.

## Explicit Imported-Overload Tier Wording

Batch0005 also read exactly tests/fixtures/partreject/imported_overload_ambiguity/Main.pw and its .err. Its two numeric overloads legitimately make the unsuffixed literal ambiguous, but the comment calls a directly imported module a resolution tier. Canonical spec15 combines visible public candidate sets without source-origin priority. Keep the ambiguity assertion and describe that set rather than preserving an obsolete origin-tier model. No test behavior is changed in this audit.

## Explicit Generic Description Precision

Batch0017 adds optional description-only cleanup for exactly reject/generic_field_on_typeparam.pw (traits do support field requirements; this particular T has no bound granting field access) and generic_recv_arg_width.pw (comment says U32 but actual typed argument is I32). Preserve both valid rejections and executable inputs. These are not missing trait-field capability or numeric-conversion feature requests.

## Explicit Generic Capability Wording

Batch0018 adds optional comment precision for reject/generic_unique_arg.pw: the ordinary Box[T] parameter is copyable-only and correctly rejects File, but the comment's blanket claim that all generics are copyable-only is superseded by explicit unique/allowunique capability declarations. Preserve the useful ordinary-[T] negative and Ref-handle contrast without turning the old implementation limit into a new specification prohibition.

## Explicit Match/Method Historical Backend Comments

Batch0020 adds only reject/match_unknown_field.pw and method_value.pw as optional comment precision. Historical emitted-C/clang descriptions explain original failures but are not the current LLVM mechanism or oracle. Preserve unknown-field/method-nonvalue rejection. No source repair or new semantic requirement is implied.

## Explicit Generic Overload Rule Comments

Batch0022 adds reject/overload_generic_concrete.pw and overload_generic_nonoverlap_cycle.pw/.err as optional comment precision. The former is invalid because T and I32 can coincide, not because every generic/concrete pair is forbidden. The latter requires a discriminator at an individual argument position; its comment claiming cross-position joint unification must keep the declarations distinct contradicts the adopted rule and reject oracle. Preserve those rejections; no general solver or inference expansion is implied.

## Explicit Range/Provided-Method Control Comments

Batch0023 adds supplemental run/range_value.pw/.out and provided_method_valid.pw/.out only for optional comment precision. arr.count() is U64, despite an I64 comment; total returns first() rather than combining both requirements, while the golden3/4 is correct. Preserve the actual output and purpose instead of inventing a missing sum assertion. No primary source-admission/outcome credit is added.

## Explicit All-Diverging Match Negative Comments

Batch0025 adds exactly reject/source_divergent_mid_value_match_all_diverge_{choose,throughAggregate,throughCall}.pw and their .err contexts as optional comment precision. Historical comments describe producing a match result type or emitting Mid around wholly diverging value use, while current spec11 and these specific rejection oracles forbid such value use. Preserve those negatives and the partial-divergence normal control; do not reintroduce a bottom coercion or claim these compile-reject tests exercise runtime cleanup/CFG emission.

## Explicit Dictionary-Key Negative Comment

Batch0027 adds reject/tc_dict_key_type.pw for optional comment precision. Its .at desugaring, skipped generic-argument checking and exclusive TypeRef-checker explanation describe a retired mechanism. Preserve Dictionary[String,I64] versus I64 key rejection through canonical Index selection; do not weaken that valid negative or require a broad comment rewrite.

## Explicit Eager Cycle Purpose Comment

Batch0029 adds reject/trait_subject_cycle_generic_active_view.pw as optional purpose/comment reclassification. Bare A→B plus bundle E B→A is already rejected eagerly at declaration consistency, before the generic view body matters (spec09). Preserve the rejection but do not credit it as evidence that the generic body was visited. Neighboring source-set-only cycle tests supply the distinct late view obligation; no duplicate mandatory fixture or first-error recovery rule is required.

## Explicit Try Primitive Conversion Comment

Batch0030 adds reject/try_error_type.pw for optional comment precision. The valid rejection is absence of From[String] on the I64 target, not absence of all from factories merely because I64 is primitive. Preserve the same error-type conversion negative and avoid introducing a primitive-only exception.

## Explicit String Unary Negative Comment

Batch0031 adds reject/unary_neg_string.pw for optional explanation precision. This source has no applicable Neg witness, but being a standard primitive does not in general prohibit providing external-type operator conformance inside an explicitly selected named extension (spec09). Preserve the valid bare String unary rejection; do not infer a universal extension prohibition from the current witness set.

## Explicit Existential Value-Copy Comment

Batch0034 adds run/any_box_value_semantics.pw/.out for optional comment precision. Its required guarantee is that mutation of the original Array field does not change the boxed value; eager deep-copy at boxing is not required by CoW/value semantics. Preserve outputs1/99 while describing semantic independence without making a physical allocation strategy the oracle. This admission audit does not claim fresh execution or verify every existential copy/drop path.
