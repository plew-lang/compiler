---
id: com-9p68
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
# Select provided copies by proof placement and complete receiver


## Boundary and Exit

Repair proofConcreteWitness mapping of an already-selected trait-subject witness to its concrete provided copy: sourceWitnessFuncId/sourceConformIdx/originTrait alone identify multiple A/B placements and currently choose firstA for actualB. Close providedCopyForDeclaration's traitSubject unconditional receiver match in the same finite identity family. Use retained exact proof/source placement plus complete directional receiver matching, including generic arguments/newtype/view semantics; do not rerun conformance/member selection or weaken bodyReceiverMatchesDeclaration. Distinguish no match and ambiguity, preserve wrong-owner/edge rejection. Controls: original trait_blanket5/21/10/9; direct and generic calls; A/B ordering reversed; same ABI distinct owners; foreign/swapped placement and generic argument mismatch. Follow producer→recorded selection→concrete copy→BodyInstance→Mid/LLVM. Fresh validation and independent completion review required.

Independent body_receiver_completion_review classified the two roots and reviewed these finite scopes at476b8e2b. Evidence: meta/evidence/existing-feature-conformance/source-owner-facts/phase3f-mode-parity-initial.json and compiler/tmp/phase3f-mode-parity/receiver-trace-1. F1 and full G2 remain separate gates; no source or test weakening.

## Repair and Validation

Production1f442206 now uses a single private selected-copy receiver admission family in source candidate applicability and both selected-copy readers. Source callableReceiverMatches first proves the exact target edge, then admits the candidate only when originConformIdx and complete receiver agree. A Direct CallTemplate keeps that source-selected callee through obligation and concrete worklists. proofConcreteWitness checks every exact source-edge candidate and rejects ambiguity; if no receiver copy matches, traversal continues to later witness functions. providedCopyForDeclaration no longer treats trait subjects as unconditional matches. Shared templates are classified by saved declaration/placement identity, not hasRecv or recvTraitArgs arity; nominal patterns match directionally and merge ParamId bindings with conflicts rejected.

Fresh candidate09dac934 passed standard build20261025T003855-build-f5aebc, whole compiler sourcecheck, normal16/reject4 focused controls (283 inputs unchanged) and F1 mode parity15/15 (internal2 reused only after candidate/input hashes match). Original trait_blanket golden5/21/10/9 and trait_assoc_fn42/15 unchanged. New user fixture reverses A/B declaration order, distinguishes generic arguments and covers inherited newtype calls; internal fixture rejects swapped/foreign proofs, ignores wrong lexical Self copy and rejects duplicate applicable shared copies. Failed red1 and fresh2 are retained, including the initially immutable fixture setup correction.

The finite producer gap for trait-subject associated functions is explicitly out of this existing-copy repair; required successor com-9clj is attached to com-072n and G1. Do not close parent or claim general associated-copy support from this receipt. Independent body_receiver_completion_review verified the final receipt8 references, focused283 inputs, parity301 inputs, standard build and whole sourcecheck; accepted the finite task as complete.

Durable receipt: meta/evidence/existing-feature-conformance/source-owner-facts/selected-copy-receiver-repair.json. No full normal/gen/deps/ASan/fixedpoint/performance/main certification from focused success.
