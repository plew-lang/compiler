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

## Producer / Reader Closure Repairs

Fresh0f18ea91 executes direct/generic/newtype associated calls and internal ABI0 controls, but added precedence/path/pattern probes exposed three same-family gaps. methodInRange erased a trait witness whenever any same-name inherent member existed; conferredCopyExists used only receiver head; source proof reconstruction chose a first target-existence path before checking the saved edge. The replacement separates semantic body generation from bare inherent priority, deduplicates the complete receiver pattern, and enumerates completed paths before filtering exact source/placement edges. Existing MemberDispatch collect/finish supplies endpoint identity and ambiguity; no owner-only path hint or post-Direct reselection. Direct nominal provided witnesses retain their existing fast path.

findAssoc retains its existing inherent/trait-namespace path and sends only generated associated copies into shared findMethod admission, with typeMatchOnly so rank1 provided cannot replace the original label fallback. Controls include paired instance/assoc inherent versus generic witness, same receiver head with Left/Right arguments, explicit LeftSource/RightSource selection and bare ambiguous rejection. New failed controls and prior frozen successes remain separate raw records. This is a paired bounded closure of the same producer/reader family, independently reviewed, not permission to implement plain trait-associated helper inheritance or Self.namespace syntax.
