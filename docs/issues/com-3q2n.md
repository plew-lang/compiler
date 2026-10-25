---
id: com-3q2n
status: open
deps: [com-cwu1, com-ra96]
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, verification]
---
# Verify closure and dynamic descriptors retain semantic dependencies

## Current Review Reopening

The fresh specification-first [com-9hf7](com-9hf7.md) review found required
existing-contract gaps. This task/area is reopened for [com-cwu1](com-cwu1.md), [com-ra96](com-ra96.md).
Prior scoped controls and accepted repairs retain their exact inputs, but do
not certify this newly evidenced boundary. Follow these finite dependencies
through source production, successful publication and actual final use, then
independently re-admit the affected contract. No new language feature is
required; no prior gate is attributed to a repaired future candidate.

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

## Outcome

Bounded C6 is complete at production **b9187931** (closure producer/read repair
**20c5b9b8**). `finalizeClosureSignature` checks the registered callable origin,
body key and exact lexical environment before publishing. Ready republication
uses `requirePreparedClosureInstance`; final scanning, MakeClosure Mid and LLVM
closure declaration share that reader. It compares the prepared declaration,
published type results, signature/parameter passing, capture identity/mode and
owned environment-drop signature. It does not select or normalize source meaning.

`checkFinalClosureCallEvidence` retains the source operation owner and exact
binding/field/function term at publication, Mid signature admission and LLVM
preflight. Both final consumers also compare a closure-field receiver with the
actual Mid operand's semantic type. Interface admission already retained exact
root/body/site/receiver/trait/slot through `instantiateInterfaceCall`,
`checkFinalInterfaceEvidence`, `midSelectedSignature` and
`midCanonicalExistentialCallPreflight`; the controls now explicitly change the
receiver, trait and slot as well as operation proof/body. No new ABI or runtime
capture/drop model was introduced; later API-closure tasks retain their scope.

Three decisive negative controls reproduce damaged-descriptor admission:
same-ABI different closure declaration; foreign cursor environment under a
registered closure instance; and same-function-type different field/binding in an
otherwise fully copied valid instance. The new controls exercise actual canonical
Mid, including distinct nominal generic instances. They do not establish an
ordinary-source miscompilation. Preliminary never-green test setup failures remain
separate from those decisive baselines and from repaired successful executions.

Fresh `bin/plewc-phase3c-descriptors-1` SHA256
**6ca009d50989a0e6ea01825994d64fc9acec442d3942601f256e582fc5b15ff5**:
standard build **20261024T092115-build-3d8faf**, full compiler sourcecheck,
native26/reject9 and module2 all pass with unchanged inputs. Equal-ABI source-view
and same-named module/slot controls retain their distinct selected semantics.
Independent completion review by /root/body_receiver_completion_review recognizes
C6 complete without blockers/unassigned repairs, verifies the fresh carrier and
255/195 scoped input fingerprints, plus all21 receipt references.

Durable evidence: meta **71a714de**, `evidence/existing-feature-conformance/
source-owner-facts/phase3c-descriptor-closure.json`. Separate formal checkpoint
**20261024T092627-self-host-d759d3** reaches generation2 fixed point, median
**6.850077s**, exit0 and unchanged inputs; `phase3c-descriptor-self-host.json` saves
the measurements and toolchain. The measured compiler is retained as
`bin/plewc-phase3c-descriptors-fixed`, SHA256
**d6c3e55adfd54876c6b6f2a0d2afb60fdfe2a371eb5111fd436131a8c8d139a5**.
All build/check/scoped/formal sessions are recovered to terminal status.
Subsequent phase-three tasks, parent completion and latest full G2 gates remain
outside this closure. Main, seed and adopted carrier are unchanged.
