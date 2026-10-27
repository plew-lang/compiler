---
id: met-2wca
status: open
deps: []
links: []
created: 2026-10-27T20:42:00Z
type: task
priority: 2
assignee: Koji Murata
tags: [frontend, verification]
---
# Plan adopted Optional payload labels for selected regressions


## Contract and Finite Scope

Source-only admission audit at compiler9665094d/spec5bd65a5: `tests/fixtures/part/namespace_chain_identity/{Main,First,Second,Noise}.pw` protects nominal Chain identity, permuted binder positions, equal concrete arguments and empty behavior. First/Second.chain construct Optional.Some using `v=`; spec05 declares Some(value:T). Current std/Lang57-60 defines Some(v:T), and Core's Optional Chain implementation527-531 constructs v=. The Chain requirement names themselves match the adopted contract. This fixture has current-public-API grounds, not fully adopted payload-label admission.

## Deliverables

Recover the original Chain identity regression and enumerate exactly this root's Optional producers plus the defining Lang Some declaration and Core Optional Chain producer. Plan the label handoff from canonical declaration through construction/pattern/member checks and the compiler's structural Optional consumer, keeping the four existing results and nominal/binder/empty controls. Distinguish payload-label migration from autounique/allowunique capability work (met-b2la); do not silently extend that epic or require its whole implementation just to classify this existing copyable case. Check correctly labeled construction, wrong-label rejection and corresponding Some/None decomposition under a coherent fixed Std input.

## Completion

An explicit bounded migration/disposition with concrete owned repair if needed, preserving the current regression and adopted public signature. This audit neither changes source/Std/expectations nor adopts an alias label or new rule. Unread Optional/Result fixture obligations remain in the audit; this is not an all-Std rewrite. Evidence: meta/evidence/test-audit/scoped-reviews/frontend-part-0003.json and its independent review.

## Explicit Three Array-Negative Producers

Batch0008 adds exactly tests/fixtures/reject/array_forward_context_block_conflict.pw, array_forward_context_explicit_conflict.pw, and array_forward_context_none_first.pw, with their .err companions. All root-authored Some constructors use current `v=` rather than adopted `value=`. The first two must fail for incompatible I64/U64 element context, not merely wrong label yielding a generic type-mismatch message. The third must preserve the leading unbound None forward-inference rejection; its later Some label still needs a coherent public-API migration.

Include these exact three roots with the existing namespace_chain_identity root, not every unread Optional/Result fixture. Preserve direct/block equivalence, explicit type mismatch and no later-element backward inference. No new label alias, capability feature prerequisite or source/expectation change is adopted by audit.

## Explicit Two Chain-Negative Producers

Batch0010 adds exactly tests/fixtures/reject/chain_missing_factory.pw with .err and chain_value_type_mismatch.pw (no companion). Both explicitly construct Optional.Some(v=...) against the current Std signature. Preserve missing empty() conformance versus continuation Value/result mismatch and the original source-anchor purpose as separate reasons; migrating labels is not proof those checks ran. The selected scope is now the original part Chain root plus five standalone negative roots, not the entire Optional corpus.

## Explicit Supplemental Coalescing Control

Batch0011 also reads run/try_coalesce.pw and .out as a positive for removed ?? versus current unwrapOr and try behavior. Its Some(v=5) is the same current/adopted payload-label difference. Include this exact pair in the finite label migration, preserving six outputs, successful/error propagation and eager/lazy fallback contrasts; no all-Optional corpus intake or new primary audit count.

## Explicit Enum-Destructure Supplemental Producer

Batch0013 adds exactly run/enum_payload_destructure.pw/.out. Its current Some(v=7I64) must migrate coherently to the adopted value label without dropping full/discard/bare-tag pattern coverage or changing 30/10/99 outputs. It is one supplemental pair, not an all-enum rewrite or a newly audited primary admission/outcome.

## Explicit Generic Associated-Self Supplemental Producer

Batch0016 adds run/generic_associated_self.pw/.out: two Some(v=value) constructors and the Some(v:val result) pattern use current payload label v instead of adopted value. Preserve generic/associated Self substitution through Optional[T], immediate unwrap and pattern extraction with 42/heap/42/heap outputs. This exact pair is not an all-Optional rewrite or a completed primary admission/outcome obligation.

## Explicit Generic Enum-Payload Type Negative

Batch0017 adds exactly reject/generic_enum_payload_wrong_type.pw. It intends Bool versus grounded I64 payload rejection but currently writes Some(v=true), against adopted Some(value:T). Preserve the payload-type reason through a coherent label migration; wrong-label rejection alone is not that type check. This is one named standalone negative, not an all-enum/Optional migration or a new primary credit for earlier controls.

## Explicit Generic Enum-Inference Supplemental Producer

Batch0017 adds run/generic_enum_field_inference.pw/.out. Root Some(v=...) constructors and v: payload patterns use current labels. Preserve inferred enum payload type/layout, forward context through block/match/array, owned String payload and all twelve outputs under the adopted value label. Panic fallback migration is com-bfvd's separately explicit exact root; no primary admission/outcome count is added.

## Explicit Guard Supplemental Producer

Batch0018 adds run/guard_stmt.pw/.out: three Some(v=...) constructors use the current label rather than adopted value. Preserve failure-branch return, successful binding escape, combined condition and all seven output lines under a coherent migration. Positional pattern binding is a separate contract, not automatically a mislabeled constructor. No execution or primary admission/outcome credit is added.

## Explicit Unknown-Variant Negative

Batch0020 adds reject/match_unknown_variant.pw. Some(v=...) construction and the v punned payload pattern use the current Optional label; reconcile both with adopted value while preserving the unknown Other variant rejection, not merely rejecting on label setup. com-ntm8 owns the selected reason-isolation requirement. This exact root is not an all-pattern migration intake.

## Explicit Optional-Chain Negatives and Receiver-Identity Control

Batch0022 adds reject/optchain_chain_incomplete.pw/.err and optchain_chain_not_nominal.pw/.err: their Optional.Some(v=...) producers use current rather than adopted labels. Preserve whole Chain requirements versus nominal-proof absence and their specific diagnostics. Custom MyOpt.Has(v:T) is its author's field label and must not be mechanically renamed. Supplemental run/overload_receiver_structural_identity.pw/.out uses <.Some v=5I64>; migrate that exact constructor while retaining nine overload/receiver/record/eager-lazy outputs. No unread Optional roots or primary admission/outcome credits are added.

## Explicit Generic Type-Checker Negatives and Context Control

Batch0027 adds exactly reject/tc_generic_arg_mismatch.pw, tc_generic_payload_value.pw and supplemental run/generic_enum_payload_context.pw/.out. Some(v=...) and v patterns require coherent adopted value-label migration. Preserve different Optional generic arguments, expected I64 payload checking and contextual integer typing in let/return/generic field positions with5/7/9 outputs. Wrong-label rejection must not mask the selected negative purposes (com-ntm8). Bare generic factory publication is com-owb3, not automatically an invalid binder.

## Explicit Trait-Method Result-Context Control

Batch0028 adds exactly supplemental run/trait_method_result_context.pw/.out. absent uses Optional.Some(v: _) against adopted value label; migrate that exact pattern coherently while preserving expected-result inference through required/provided/default generic members, block/if wrappers, associated output record members and bound discharge. Optional.None needs no payload-label change. This pair is a qualified control, not completed primary admission/outcome or a request to change inference semantics.

## Explicit Shared-Witness Optional and Protocol Negatives

Batch0029 adds exactly reject/trait_subject_chain_conflict_{existential_enum,protocol,protocol_bound}.pw/.err. Their Some(v=...) producers differ from adopted value. Preserve ambiguity inside shared witness bodies through generic erasure and direct/generic iteration protocol calls; the specific ambiguity companions must not pass on wrong-label rejection. The enum whole-container conversion has its separate com-vp0o setup disposition. No implicit label alias or new primary positive credit is adopted.
