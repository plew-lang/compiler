---
id: com-9clj
status: in_progress
deps: []
links: []
created: 2026-10-25T00:44:22Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-072n
tags: [frontend, generics, verification]
---
# Generate trait-subject associated-function copies from retained witness owners


## Boundary and Exit

A valid selected trait-subject associated requirement has no concrete copy producer. `applyBlanketTo` and `instantiateProvidedMethods` copy only hasRecv functions, whereas Lower registers assoc witnesses with hasRecv=false, isAssoc=true and canonical lexical Self. Repair this finite producer family (including preserving receiver-free ABI), carry exact source/placement identities and complete binders through public/generic selection to BodyInstance/final descriptor. Do not treat an abstract original as a concrete source or introduce post-selection name fallback. No new language feature or namespace semantics.

Control: trait Source {}; trait Target { assoc fn value() -> I64 }; impl Source as Target { assoc fn value() -> I64 { return 7I64 } }; struct S {}; impl S as Source {}; fn invoke[T](value: T) -> I64 where T: Target { return T.value() }; main invokes inferred S. Expected 7. The actual source uses newlines, no semicolon syntax. Add a canonical run fixture before repair, retain direct and generic namespace/owner negatives and ABI receiver0 controls. Existing trait_assoc_fn remains42/15. Cover default form generator only if this same producer requires it, not wholesale callable redesign.

Fresh same-source probes: compiler/tmp/phase3f-copy-identity/associated-producer.pw and postcheck-3. Carrier033 rejects in finalization with body receiver mismatch; carrier09dac934 (production1f442206) rejects in obligations with selected trait member has no concrete conformance. This was already invalid in033; B's corrected classification no longer presents abstract source as concrete. Evidence in meta/evidence/existing-feature-conformance/source-owner-facts/selected-copy-receiver-repair.json.

Independent body_receiver_completion_review approved separation from com-9p68's existing-copy admission. Parent com-072n and G1 must stay open until this producer task closes. Fresh validation and independent completion review required.

## Scope Guard from Producer Review

Independent body_receiver_completion_review found that unconditionally copying plain `impl Trait` associated helpers (such as Eq.derive) would expand the existing namespace surface without an adopted specification contract. Do not do this. Repair only the bare trait-subject edge's recorded associated requirement witnesses in applyBlanketTo, retaining hasRecv=false and exact witness/lexical/placement IDs. instantiateProvidedMethods keeps its existing hasRecv-only public provided-method family. methodInRange/conferredCopyExists must account for real associated witnesses to preserve inherent precedence and idempotence. Never-green fixture expectations for conformer.twice/helper inheritance were removed before acceptance; initial bad Self namespace setup and original red results remain in scratch. Explicit Self argument calls test existing value receiver requirements without inventing Self.namespace syntax. Extension-associated witness production is not certified by this finite bare-conferral repair.
