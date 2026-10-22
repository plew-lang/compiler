---
id: met-ia09
status: open
deps: []
links: []
created: 2026-10-13T01:40:08Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, generics, verification]
---
# Close saved constraint evidence through callee environments and final use

Reconcile the cumulative candidate before work: historical Direct evidence transfer, presence environments, supertrait edges, receiver/TraitSubject, associated-clause evidence, requirement-to-implementation derivations and Provided Static handoff already have bounded implementations/evidence. Do not re-register their earlier next-step paragraphs as untouched work. [Migration evidence](https://github.com/plew-lang/meta/blob/main/evidence/typechecking-remediation/design-migration.md) gives revision boundaries.

Remaining closure audit: bind each callee declaration-bound identity to its saved evidence in the explicit instance environment; include those bindings in sameInstanceEnvironment, withLexicalSelfBinding and body identity. Preserve legitimate empty bindings versus missing/unprepared. Source public requirements and chosen implementation obligations are not positional arrays to zip: retain conformance, requirement clause, implementation declaration and derived proof identities. Check Function/Requirement/Conformance/MethodReceiver/TraitSelf/TraitSubject/AssociatedType roots, AssumedBound/AssumedSupertraitPath/AssumedTraitPath, conditional child proofs, projection normalization and ExistentialBox consumers. Declaration worklists (Check/Bounds iteration and Check/Obligations) and execution preparation need explicit environments; ambient Mono Cursor cannot replace them.

Presence evidence does not establish unique member dispatch. Preserve source existence proofs and prepare member uniqueness at the correct boundary without silently privileging a caller path or demanding unused bounds be unique. Conditional WitnessConditionPlan children are not a substitute for complete supertrait derivations. Ground concrete selected evidence without repeating selection; abstract/deferred evidence remains distinct from a missing concrete binding.

Cover Written Direct, Static Requirement/Provided, operator, protocol, try conversion, root/entry, extern/bodyless and synthetic calls. Entry must consume selected body identity. Associated declaration proofs must reach projection prerequisite -> selected conformance -> original clause -> final consumer; do not merely privatize stores. Requirement derivations must handle weaker/reordered impl bounds, supertrait and conformance-where entailment.

Acceptance: producer construction/storage -> owner admission -> explicit substitution -> real callee body context/final consumers all closed; remove old lookup and reader-side source obligation reconstruction only after publisher authority is structural. Positive and missing/foreign/clause/path/replacement controls, differing evidence with same type arguments, AOT/JIT and applicable parent gates. Public storage writers are not semantic success capabilities.

## Existing-Feature Conformance Classification

[com-604k](com-604k.md), scope record [com-esri](com-esri.md): **Included repair**.

Current declaration-bound identity, binder/proof/environment keys and selected-call instances through real callee contexts. Preserve existing simultaneous substitution and proof keys. Coordinate the saved-source operation contract with met-ucze; no new allowunique/conditional capability solver.

## Source-selected Static Enqueue Increment (WIP)

The existing Direct/Static evidence readers are reused, not replaced by a new
constraint store. enqueueSelectedCallee now requires the retained CallTemplate;
it constructs the exact evidence from that source operation in the explicit
caller environment. Written calls, operators, protocol slots and try conversion
all use this entry. Its default Declaration evidence parameter is removed.
Protocol grounding and selection consume the same acquired template rather than
independently acquiring or interpreting its source occurrence.

Declaration worklists route static requirements/provided methods, protocol and
operator calls through the same explicit-environment reader. A shared substitution
gate distinguishes deferred/open arguments before concrete evidence instantiation.
Bodyless requests admit signature/evidence before completing without a body.
Root and synthetic declaration producers retain their separate legitimate path.
Requirement-to-implementation mapping retains the existing conformance method
plan and original clause identities; no public/implementation bound arrays are zipped.

Whole-compiler source checking succeeds with the preceding fixed carrier.
An internal source-imported control is being added for operator/protocol callee
bindings, explicit environments and malformed bodyless evidence. Fresh binary,
matching-source cost and applicable full gates remain pending. This increment does
not close dynamic descriptors, associated proof consumers or the entire issue.

Current-source imported controls pass existing requirement derivation (including
reordered/weaker/conformance bounds), provided-body bindings, Direct evidence,
selected conditional proofs and independent global owners. The new implicit-call
control reaches real operator/protocol callee environments and succeeds with an
explicit caller environment while the ambient cursor is cleared. A canonical
nominal/binder confusion exposed by this control is recorded in met-6e6k.
Additional empty-evidence replacement and provided-placement guards require the
next fresh candidate's checks; no full-gate success is claimed yet.

The fixed 2b241be3 full normal run found lexical_body_requests reading a failed
owner's unpublishable operation before testing writer rejection. Preserve that
fixture's original refusal/retry/cursor/independence checks: retain the attempted
row while Building, then use it for the post-failure rejected writer call. Do not
make failed-owner rows readable to satisfy this internal fixture.
