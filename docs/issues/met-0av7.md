---
id: met-0av7
status: in_progress
deps: [met-6hrd]
links: []
created: 2026-11-23T19:21:47Z
type: task
priority: 1
assignee: Koji Murata
parent: met-ajht
tags: [frontend, generics, verification]
---
# Realize inherited existential witnesses from retained interface slots

Consume the first child's retained interface and exact ancestor proof at existential boxing. Build member/adapter/Ready descriptors in the same effective slot order, using original declaration identity, parent instance bindings and selected witness proof. Shared signature/condition/result/ownership readers must consume this mapping; do not pass effective slots into TraitDef.reqs or reselect declarations/conformances in backend lowering. Preserve existing fat-any layout and saved descriptor slot extraction, direct-member behavior and Self/input restrictions. Check vtable length/order, interface target identity, parameter/result ABI, recursive Self conversion and missing/corrupt prepared mappings. No temporary unchecked slot or fallback that emits invalid IR.

Inventory and migrate selected existential readers in Mono/Call, InterfaceEvidence, Existentials, checked target/Ready and emission paths. Static requirement declaration readers stay raw and unchanged. Source-to-ORC dot/subscript/generic/diamond controls must actually execute the chosen witness; negative mismatched binding/unrelated protocol retains refusal. Inspect tests/native and LLVM22 ownership/lifetime where changes affect erasure/adapters. Build/scoped native/ORC plus independent review close this finite consumer boundary; no new C/public persistent ABI guarantee is introduced. If the contract needs such a change, stop for a design decision.

## Concrete handoff plan and independent boundary review

Prepare ancestor proofs once in the retained graph's topological order from the root box evidence, replaying the exact declaration trait/clause, substitutions and normalizations of every incoming edge. Check every provenance path and converging target instance; canonical candidate aliases never certify witness equality. Do not rerun conformance lookup to repair missing evidence.

Implementation selection, requirement-to-implementation plan and callee environment consume the parent original signature/slot/proof together. Root box evidence remains separate for public any Self re-erasure and condition scope. Preserve logical-to-concrete body receiver interpretation. Prepared/Final/Ready/vtable arrays keep every effective slot including nondispatchable Optional entries; no compacted member indices.

The concrete-payload logical witness validation in checkAbstractExistentialPlans depends on this ancestor-proof preparation and is included here. It is distinct from met-6hrd's public virtual interface metadata/conditions; no source-only result is executable adoption. The source-to-physical baseline has all ten check modes and six normal modes passing, with eight inherited AOT/ORC pairs still refused by the old Mono.Call slot guard. Parent integration owns final whole/ASan/formal gates.

Independent reviewer typing_obligation_plan_review finds this boundary/plan appropriate; specifically verify parent proof reaches environment construction as well as selection, all incoming paths remain checked, and preparation is shared per ancestor rather than repeated per member. This is a plan review, not implementation acceptance.

## WIP implementation and tests

Actual native RED: direct real Index witness succeeds, inherited prepared box publishes zero members. Frozen native output/inputs are retained in compiler/tmp/frontend/existential-witnesses-red-v1. Parent proof preparation, selected implementation proof receipt and effective Prepared/Final slots are implemented; root evidence remains for Self re-erasure/condition scope. A second RED shows warm prepared-box cache bypassing Failed admission; it now propagates before lookup.

Tracked private witness tests cover twelve concrete scenarios including generic erasure, target convergence/complementary equations, unequal-depth diamond, unavailable Self-input slot, recursive Self return, inout and repeated cache/parent environment. A real full-frontend dispatch case checks missing final members/invalid target, caller/receiver/slot/evidence/interface faults, and transport of async/mode/argument metadata. The source-owned interface token provides the slot count without a duplicate scalar. The actual backend endpoint preflight is a private associated function under LlvmCtx, tested with twelve valid/refusal cases independently of LLVM storage emission; remaining storage/lane checks remain in the full preflight. These are component successes, not final execution acceptance.

Full compiler-source --check succeeded on current changes. Fresh candidate AOT/native/ORC, existing normal controls, applicable memory gates and final independent review are pending. Temporary test setup mistakes (reserved binding names, free function in part file) were corrected and are not counted as product RED. See canonical parent evidence for exact source/support inputs and reports.

## Final Mid consumer and executable diagnostic evidence

A genuine RED against 4c9b28de Mid/Instantiate passes direct Index and fails inherited signature retention. Mid now consumes the validated full saved InterfaceCallEvidence signature; receiver/count/argument passing checks remain, without root declaration reselection or duplicate mode/count authority. The private actual-Mid probe is GREEN. Diagnostic O0 fresh compiler passes all 45 check/AOT-emission/ORC modes and 15 separately linked native apps; LLVM22 ASan+LSan passes all 15 apps and private frontend witnesses (24033 instrumented function checks). Exact input hashes and RED/GREEN reports are saved in canonical parent evidence. Independent reviewer typing_obligation_plan_review found no must-fix in this source/test boundary and verified support64 hashes. Optimized frozen build existential-witness-build-v2 is running; final candidate execution remains required before closure. Parent met-lrep retains whole/gen/formal gates.
