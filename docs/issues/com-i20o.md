---
id: com-i20o
status: closed
deps: []
links: []
created: 2026-10-25T00:02:03Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-072n
tags: [frontend, generics, verification]
---
# Preserve lexical Self and namespace identity for trait associated bodies


## Boundary and Exit

Repair no-value-receiver trait-associated body environment construction. withLexicalSelfBinding currently excludes authored !hasRecv/isAssoc members despite retained lexical provTraitOwner and recvTy=Self@ParamId. Bind by the saved lexical trait owner, independent of ABI receiver presence. Separately validate the namespace against provTraitOwner (not originTraitOwner) and its complete saved trait arguments; do not make the checker vacuous by accepting arbitrary Beta as Self. Preserve legitimate abstract same-ParamId preparation, provided-copy concrete Self and ordinary nominal assoc handling. Carry the result through BodyInstance/signature/final consumer; ABI signature.receiverType stays0. Controls: trait_assoc_fn original42/15, Eq derive UnresolvedField generation then application rejection, distinct same-ABI trait namespaces including foreign/missing owner rejection, repeated keys and abstract same-binder contrast. Fresh compiler validation and independent completion review required.

Independent body_receiver_completion_review classified the two roots and reviewed these finite scopes at476b8e2b. Evidence: meta/evidence/existing-feature-conformance/source-owner-facts/phase3f-mode-parity-initial.json and compiler/tmp/phase3f-mode-parity/receiver-trace-1. F1 and full G2 remain separate gates; no source or test weakening.

## Outcome: Resolved

Production9b72ec5b/01e17fdb, fixture113a1de9. Source lexical trait ownership
now binds Self independently of the physical receiver. Namespace identity and
complete trait arguments remain separate validation inputs; exact symbolic Self
is preserved. The guard follows the canonical authored declaration so instance
method default generators retain concrete receiver context.

Standard build20261025T000933-build-5be053 passed; saved fresh
bin/plewc-trait-associated-owner-2 SHA033ff8473787d5fd300e6ce5d2f2df9b6e7a978c7188acbfb947f4f3dd84e244.
Whole compiler sourcecheck and native10 pass, inputs unchanged. Original
trait_assoc_fn emits42/15; distinct namespace/owner/binder/trait-arg and ABI
signature corruption controls pass. Eq derive emits the canonical output before
whole check/build reject the invalid application; lazy empty main omits its
unused Eq body. Separate demanded generated invalid body rejects in all modes.

The initial guard1 candidate passed the new fixture but broke existing
 default_generator_environment; independent review caught and reproduced this.
01e17fdb fixes classification using the original declaration. Failed original6dd
red4, guard1 and mode run2 are retained; none is relabelled green. No visibility,
final receiver verifier, runtime or language rule was weakened.

Canonical receipt: meta/evidence/existing-feature-conformance/source-owner-facts/
trait-associated-namespace-repair.json and phase3f-mode-parity.json.
Independent body_receiver_completion_review verified11 references,208 focused
inputs,301 mode inputs, sourcecheck and actual final outputs, and accepted this
finite producer-through-consumer completion. com-9p68, com-072n, G2, main and
seed/adopted carrier remain outside this closure.
