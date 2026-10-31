---
id: com-nei5
status: open
deps: []
links: [com-mmk9]
created: 2026-10-30T09:24:20Z
type: task
priority: 2
assignee: Koji Murata
tags: [verification, frontend]
---
# Separate Self and Item frame writes from selected proof queries

Evidence: [input-authority answer](../../../evidence/compiler-api-audit/resolutions/grounding-service-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-resolution-grounding-service-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This issue owns product repair; implementing it is not a prerequisite for the source-only input investigation.

## Guarantee and Scope
assocItemRef/setSelfItemEnv/setSelfItemEnvForBody/clearSelfItemEnv/associatedOutputInProof/bodyProvidedItemTerm and exact typed consumers. Only setters get explicit Self/Item slots; clear gets just those two fields, not the entire shared I service or Comp.

Use the per-API narrow contract and only the required parts of shared T/P/W/L/B/R/I/K/E/D services: same-session canonical/name/keyword/proof/condition publishers, exact explicit body/witness/ParamId/receiver/Self/Item/assumption inputs, owner-specific declaration/interface readers, original-body sourceKind2 cache writer, conditional structural-layout publisher, explicit selected legacy frame access and source diagnostic projection. Shared service identifiers describe dependency closure, not permission to pass their whole union to every helper. No raw Comp, full mutable Arena/Decls/MonoWork/Mid or callback retaining them may survive behind these boundaries.

## Completion
Change the named actual signatures and every exact typed consumer in the linked235-expression table for this subset. Preserve source/session/body/ParamId/declaration/proof/view identity, defaults and no-reselection behavior; needed canonical/name/keyword/cache/proof/normalization/layout writes; invariant/zero/open/Err distinctions and failure prefixes. Coordinate shared service extraction without duplicating decision owners or retaining Comp through a facade. Temporary map scopes must restore on both Result exits according to compiler-state contract; lasting Self/Item entry setters and outer phase restoration stay separate. Keep original source terms/sourceKind/cache guards and collection permission. Use meaningful task-start TDD/refactor controls and independent review/gates for the eventual repair.

Preserve exact actual caller and source/session/type/proof/pool lifetimes, ordering/defaults, diagnostic provenance, legitimate mutation and error prefixes in the pinned answer. A wrapper or callback retaining unrelated whole compiler authority is not a narrowing. Readonly grants are not writers. Cover relevant normal, rejected, boundary and failure-prefix controls, verify the real producer-to-final-consumer path and remove competing broad signatures. No statement of future GREEN is evidence that the repair has passed.

## Excluded
No implementation or GREEN in this input audit, no language/ABI/algorithm/performance change, no automatic reclassification of neighboring APIs or passive-record decomposition. This bounded responsibility task does not require a globally minimal compiler service proof.



## Adopted Implementation Intake

[com-3z5o](com-3z5o.md) classifies the exact confirmed scope as required existing-feature phase3 conformance. Required admission owner(s): met-ia09, met-6e6k; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-source-queries.json) retains all main/mixed roles and normative grounds. Associated output and provided Self/Item environments preserve original binder/evidence identity for source and final consumers. Restrict setters to actual Self/Item slots and keep explicit canonical/proof services per operation.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
