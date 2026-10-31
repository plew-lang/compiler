---
id: com-0u0i
status: open
deps: []
links: [com-mmk9]
created: 2026-10-30T13:33:36Z
type: task
priority: 2
assignee: Koji Murata
tags: [verification, frontend]
---
# Narrow source ownership and pattern access inputs

Evidence: [input-authority answer](../../../evidence/compiler-api-audit/resolutions/check-call-inputs.json) and [independent review](../../../evidence/compiler-api-audit/review-resolution-check-call-inputs.json), source 9665094dcec8aa63ed20573b1306a0015058f595. Linked audit [com-mmk9](com-mmk9.md). This issue owns product repair; implementing it is not a prerequisite for the source-only input investigation.

## Guarantee and Scope
Exact APIs: checkUniquePlaceCopy, expressionProvidesOwnership, matchConsumesValue, matchScrutIsMove, matchScrutIsBorrow, checkMatchAccessMode, checkPatternAccessMode, checkUniqueArgModes, checkArgInoutMode. Actual calls 32. Pure AST/nominal predicates get readonly coherent descriptors; query-using access checks receive only exact type/place query operations and diagnostics. No uniform Q grant to predicates; preserve original typeArgumentConflictDiagnostic owner com-9sa5.

Nine APIs have distinct contracts: four pure AST/nominal predicates remain readonly; typeOf-dependent place/pattern/mode checks retain bounded actual query/place diagnostics. Full arms only len and first isStruct; passive complete records may remain. Preserve explicit borrow/move/struct rejection order, no new source ownership transfer and no broad Q for predicates. Existing typeArgumentConflictDiagnostic mainC/com-9sa5 is outside this component repair. Mutable Comp admits unrelated driver/source loading, arbitrary declaration/AST mutation, independent source owner success/publication, native/runtime/backend and final body admission; none follows from this operation-scoped required read/write map. Remove these actual grants, including captures/facades retaining whole Comp.

## Completion
Change real API signatures and every enumerated actual caller, preserve per-entry input/default/identity/effects and valid derived prefix; own temporary lexical restoration on all exits against current legacy gap; structural closure plus later TDD/refactor verification. This investigation performs no repair or GREEN. Keep each actual per-entry/default/owner/frame/cache/retention/conditional writer map instead of a group union. Preserve source-to-frozen-match-to-Mid final consumer, owned descriptors and pool lineage. No unrelated whole compiler authority through wrappers/captures. Relevant positive/reject/boundary/noninterference/failure controls and independent structural review/gates belong to future repair.

Preserve exact actual caller and source/session/type/proof/pool lifetimes, ordering/defaults, diagnostic provenance, legitimate mutation and error prefixes in the pinned answer. A wrapper or callback retaining unrelated whole compiler authority is not a narrowing. Readonly grants are not writers. Cover relevant normal, rejected, boundary and failure-prefix controls, verify the real producer-to-final-consumer path and remove competing broad signatures. No statement of future GREEN is evidence that the repair has passed.

## Excluded
Other original J/C/O/optional/U scopes and existing com-9sa5; language/source acceptance/ownership/type/solver/general algorithm redesign, product execution/repair/performance/GREEN within this source audit.



## Adopted Implementation Intake

[com-8ttz](com-8ttz.md) classifies the exact confirmed scope as required existing-feature phase3 conformance. Required admission owner(s): met-acfl, met-6e6k, met-ucze; actual tk prerequisites retain this open repair.

[Scoped outcome](../../../evidence/existing-feature-conformance/audit-intake/api-source-verification.json) retains all main/mixed roles and normative grounds. Source ownership/pattern and call argument mode decisions must reach frozen match facts/Mid. Pure AST predicates remain readonly; query-dependent checks keep bounded type/place diagnostics. Conflict diagnostic main remains com-9sa5.

Original audit-time independence does not waive this implementation admission. Preserve the original finite guarantee, actual callers/delegates, controls and excluded optional/new-feature scopes. Assignment is not product repair/GREEN.
