---
id: met-6hrd
status: in_progress
deps: []
links: []
created: 2026-11-23T19:21:47Z
type: task
priority: 1
assignee: Koji Murata
parent: met-ajht
tags: [frontend, generics, verification]
---
# Build retained effective existential interface views

Own the source producer and shared readers for explicit-supertrait existential requirements. Keep TraitDef.reqs as original declarations; retain root/effective slot separately from original trait/slot, canonical parent instance/binding recipe and checked SupertraitRef path. Root direct slots remain ordered first; diamond sharing requires identical public requirement and compatible saved evidence, never a same-spelling heuristic. Expand explicit supertraits only, not trait-to-trait impl search. Declaration views are finite and independent from per-target binding/witness data; cache immutable views instead of repeating traversal per member. Preserve finite recursion/admission errors rather than publishing partial views.

Migrate source candidate enumeration, type/result queries, dispatchability and interface signature readers to this contract. Audit raw .reqs uses and distinguish declaration requirements from effective interface endpoints. Keep original authored signature ownership and source proof scope. Cover direct/inherited/generic root, multi-level, identical diamond, distinct binding and unrelated protocol cases with producer/native boundary tests and source probes. TDD red is the fixed0655 six inherited dot/subscript refusals; direct/generic six controls remain valid. This child establishes semantic construction/selection only; do not adopt a source-only candidate as executable support or remove missing physical-contract guards. Build/scoped controls and independent review close this child; the parent integration owns actual final ORC/full gates.


## In-progress evidence and remaining checks

See [retained evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-inherited-existential-interface.json). Fixed carrier0655 rejects15 inherited modes and passes6 direct/generic controls. Internal native source interface RED, warm-cache failed admission RED, reversed associated binding order RED, and checked-call inherited RED are repaired in WIP; five semantic scenarios plus inherited input-Self and invalid-slot controls pass. These are not executable-support adoption.

Independent review requires target-converging ancestor candidates (P[T]/P[U] under T=U) to share their original signature after substitution, preserving source slots and all witness paths. Explicitly check unequal-depth diamond binding propagation, Open-to-complete admission cache stability and inherited Self-result re-erasure before closure. Keep logical witness planning/conditions in this child; physical witness preparation stays met-0av7.

Target-convergence and complementary-associated-equation native REDs are repaired: target-level conjunction precedes canonical member selection while retaining source slots/edges. Unequal-depth diamond, inherited Self-result re-erasure, admitted Open-to-Complete cache stability and saved Failed propagation pass. The shared interface contract/conditional reader also consumed raw root slots; its own native RED is fixed by retaining the source-interface ID and reading original signature/parent bound. Latest conditions-boundaries-v1 passes eight normal cases, Self input/invalid slot refusals, Self result conversion and positive/negative inherited conditions, with runtime File fixture hashes frozen. Final source review/build remain outstanding.

Source CallTemplate obligations had one further raw-slot reader. Recording alone passed and is not counted as RED; explicitly consuming real Dynamic/Protocol templates through sourceSelectedCallBounds failed with `selected interface has no retained requirement`. The retained root/effective signature reader replaces the raw helper; native source-obligation-green-v1 succeeds. Tracked `tests/compiler/frontend/test-existential-interfaces.py` and `.err` golden now reproduce eight source scenarios and semantic boundaries, including actual template consumption; carrier and runtime File fixtures are checked before/after. Independent semantic source review finds no further must-fix; final build/scoped controls are pending.

Fresh fc0a08 preserves six check/AOT/ORC normal controls, but reveals additional semantic raw-slot readers in source argument/arity verification. They are migrated through the common effective declaration/signature reader, including invocation divergence and post-substitution Unit classification. Owned prepareLexicalBody plus actual saved template selection/bounds/Unit consumers now run in the internal test. Explicit and associated Unit exposed a further real RED, repaired by reading the substituted result rather than hasRet. Latest tracked native gate passes all eight source cases and four inherited invocation forms (omitted/explicit/associated Unit, diverge), preserving Self/conditional/cache controls and all input fingerprints. Final independent source review finds no further must-fix; final build and normal controls are still pending.
