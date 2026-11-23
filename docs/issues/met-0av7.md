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
