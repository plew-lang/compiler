---
id: met-0av7
status: open
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
