---
id: com-i20o
status: in_progress
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
