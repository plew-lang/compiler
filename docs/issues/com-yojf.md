---
id: com-yojf
status: in_progress
deps: []
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-ia09
tags: [frontend, verification]
---
# Resolve the stronger universal nominal proof audit with bounded counterexamples

## Boundary

Phase 3B / B4. **Bounded investigation; no speculative semantic change.** Parent criteria: 3, 4, 8.
This is a bounded child of [met-ia09](met-ia09.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Codegen/Check/InterfaceEvidence.pw`; `src/Codegen/Mono/InterfaceEvidence.pw`; `src/Codegen/Mono/Call.pw`.

Inspect replayConstraintProof/replaySelectedWitness and declaration dependency classification for four proof roots: interface assumption, nominal witness with hidden arguments, conditional witness, associated/supertrait projection. Construct a minimal promised member, unguaranteed unused member and malformed-proof contrast; follow boxing and final dynamic use. Reuse the saved f67c8fce availability controls.

## Exit and Evidence

Record which exact root/child conditions establish universal admission versus concrete readiness, with source locations and positive/counterexample results. Do not try to prove all possible predicates. If an unsound edge is reproduced, create a bounded mandatory repair child and block the area and G1 on it; this investigation may close only with that exact disposition. If meaning or ABI is undecidable from policy, stop for a user decision. An unavailable member and corrupt evidence remain distinct.

Existing starting controls: `interface_declared_guarantees`, `interface_final_evidence`, `interface_boxing_conditions`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.

## Four-root Disposition

The source audit at a0e04c49 follows `Check/InterfaceEvidence`,
`Check/Obligations` and `Mono/InterfaceEvidence`. Four roots are distinct:

| Proof root | Admission and dependency classification | Replay and final use |
| --- | --- | --- |
| Interface assumption | retainSourceInterfaceRoot / checkInterfaceAssumptionScope tie a rigid hidden binder to one source call; contract roots cannot borrow it | createInterfaceProofContext rebases it to an instance root; replayConstraintProof returns Universal in this scope and the static adapter rejects it |
| Nominal witness containing hidden arguments | scopedWitnessDependencies traverses receiver and all binder terms even if interfaceProofRoot finds no assumption child; hidden dependency is unguaranteed, not a universal certificate | instantiateConcreteConstraintProof requires a closed receiver and selectedWitnessTypesAreClosed; an open nominal witness stays Deferred; after explicit grounding it can become Ready |
| Conditional witness | integrity admits the exact witness condition plan before scopedWitnessDependencies follows all child proofs and normalization prerequisites | interfaceProofRoot follows the complete owned child tree; rebaseInterfaceWitness/replaySelectedWitness preserve selected conformance and replay every child; universal proof cannot escape to static Ready |
| Associated/supertrait guarantee | scopedAssumptionDependencies checks original associated clause and prerequisite with cycle/scope checks; supertrait paths retain their root | interfaceAssumptionRoot follows associated prerequisites; rebaseInterfaceBound/Supertrait and projection replay preserve the root and selected derivation |

A source method's hidden-Self condition must follow a retained interface,
supertrait or associated guarantee (spec/08). An arbitrary nominal hidden-argument
witness is conservatively unavailable, including the unconditional Wrapper[Self]
shape: absence of an Interface assumption child does not certify a universal
source path. This audit does not invent a stronger universal predicate solver or
change the admitted language surface. Fixed associated outputs and caller-bound
parameters instead keep their actual premises and first-concrete admission.

`interface_nominal_hidden_readiness` adds a direct contrast for the root-free
nominal case: declaration support rejects it in the hidden scope, static replay
stays Deferred, and an explicitly grounded receiver can become Ready. It does
not assert that a concrete factory has proved arbitrary hidden conditions.
`interface_declared_guarantees`, `interface_source_scope`, and the unchanged B3
`interface_final_evidence`/`interface_boxing_conditions` cover promised versus
unused unguaranteed slots, conditional/projection child trees, missing/foreign/
replaced evidence, static escape, actual Mid and executable dynamic calls.

Fresh focused execution at 8fa419b7 passed: four native golden controls and
ten expected rejects, no internal diagnostics, session59644 exit zero. B3
boxing/final-evidence/inherited controls are reused only after their inputs
were rehashed unchanged. Evidence is
`meta/evidence/existing-feature-conformance/source-owner-facts/phase3b-universal-proof.json`.
Independent completion review is pending. The new
internal fixture needed its required empty associated-predicate array and a
properly grounded receiver argument at the static replay API; both corrections
preserve the intended contrast and do not alter compiler code or existing tests.
