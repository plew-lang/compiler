---
id: com-9p68
status: open
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
