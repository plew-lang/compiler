---
id: com-3q2n
status: in_progress
deps: []
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, verification]
---
# Verify closure and dynamic descriptors retain semantic dependencies

## Boundary

Phase 3C / C6. **Bounded closure verification.** Parent criteria: 2, 3, 8.
This is a bounded child of [met-6e6k](met-6e6k.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Codegen/Mono/Call.pw`; `src/Codegen/Mono/InterfaceEvidence.pw`; `src/Backend/Llvm/Closures.pw`; `src/Backend/Llvm/GenericAny.pw`; `src/Ir.pw`.

For closure and dynamic/interface descriptors, trace source result/parameter/receiver terms and dependencies into per-instance descriptor publication, Mid signature preparation and LLVM preflight. Check that phantom/nominal/view information is not erased because payload layouts happen to match. Use the existing interface capability; proof admissibility belongs to B4.

## Exit and Evidence

Each of the two descriptor families has exact publication/reader functions and missing/foreign/instance/proof-replacement plus equal-ABI-distinct-semantics controls. Separate declaration dependency scope from demanded runtime reachability. Close actual descriptor gaps end to end; do not redesign runtime capture/drop or add a new ABI.

Existing starting controls: `dynamic_call_template_generic_instances`, `interface_final_evidence`, `closure_enum_owned`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.

## Current increment

The closure audit reproduced two internal admission gaps: a same-ABI, zero-capture
descriptor from another declaration reached actual canonical Mid, and a foreign
cursor environment could publish a signature under a different registered body.
These are damaged internal descriptors, not established ordinary-source
miscompilations. Baselines and the corrected embedded-compiler preflight remain
separate in `tmp/phase3c-descriptors/`.

`20c5b9b8` adds producer key/origin/environment admission and the common
`requirePreparedClosureInstance` reader for final scanning, MakeClosure Mid and
LLVM declaration. It reads the checked declaration and existing body type results;
it does not select another declaration or normalize projections. The paired
`closure_descriptor_identity` and `closure_instance_environment` preflight passed.
The follow-up increment also verifies the complete environment-drop shape.

The dynamic-call audit found that field/binding selection needed the same source
identity check even when both targets have one function ABI. The current increment
adds a shared `checkFinalClosureCallEvidence` at publication, Mid signature admission
and LLVM preflight, and compares a field receiver's semantic type with its actual
Mid operand. `dynamic_closure_descriptor_identity` exercises actual canonical Mid
with a fully copied valid instance and a changed target. Its never-green setup is
being checked before a fresh build; no fresh-success claim is made here.

Interface publication/reader audit: source recording retains the interface root;
`instantiateInterfaceCall` binds it to the registered environment/source owner;
`checkFinalInterfaceEvidence`, `midSelectedSignature` and
`midCanonicalExistentialCallPreflight` retain body/site/receiver/trait/slot. Existing
proof admission stays B4's responsibility. Include `interface_final_evidence`,
`existential_selected_source_tables`, `mid_dynamic_call_signatures` and the two
`namespace_existential_*identity` module controls in final scoped verification.

The independent intermediate review found no design blocker. It requested the
remaining drop-signature shape checks; they are included in the current increment.
Final fresh verification, evidence preservation and independent completion review
are still required. No runtime model, ABI, parent completion or final gate changes.
