---
id: met-zva3
status: in_progress
deps: []
links: []
created: 2026-11-09T19:53:23Z
type: bug
priority: 1
assignee: Koji Murata
tags: [frontend, verification]
---
# Preserve authored provenance for omitted function-type Unit results


## Guarantee and Boundary

Restore omitted `fn()` result annotations without changing language semantics.
Lowering must retain the exact authored result occurrence when mapping its Unit
representation to an empty record; the authored recipe validator must validate
the same finite mapping only at a FunctionResult edge. Preserve rejection of
non-Unit substitutions, invalid destination shape, wrong edge and forged source
provenance. No global occurrence search or weakening of signature admission.
Both SyntaxType and TypeAst lowering share the mapping owner.

## Confirmed Cause and RED

At compiler d62392d6, the fixed field candidate SHA
8028679c1752770eebb68cd8ee6fb9c9aa02ae04cd5962687f283c771969b4fa
rejects the unchanged value_snapshot_callback fixture before linking, with
`source argument changed without a representation mapping`.
The supervised minimal controls in compiler/tmp/value-abi-callback-minimal-investigation
show omitted fn() input and local annotations reject, while explicit fn() -> ()
and fn() -> I64 compile. Fresh fixture inputs were unchanged.

Types.pw converts a nonzero empty nominal Unit result into an empty record.
TypeRecipes.pw incorrectly requires the source term to be zero and compares a
newly allocated result term by raw ID. Check/AuthoredTypes.pw also requires a
zero source. Read-only independent investigation callback_recipe_investigation
confirmed both producer and verifier defects and the retained-edge obligations.

## Execution and Completion

Add targeted positive and malformed-recipe controls before product changes;
confirm meaningful RED on fixed baseline. Fix the common representation mapping,
then verify actual callbacks with omitted/explicit Unit and non-Unit results,
source occurrence replay and invalid mapping/edge rejection. Run the unchanged
value_snapshot_callback as a required production consumer and reconcile actual
output/owner behavior. Fresh build and neutral independent review are required.
Save concise reproducible evidence; final prototype and com-ffar gates remain
separate. This is a prerequisite to W1b callback certification, not W1b closure.

No new syntax, semantic Unit rule, general type equality or ABI optimization.

## Neutral Scope Review

callback_recipe_investigation independently confirmed the bounded scope.
Required controls also include both SyntaxType and TypeAst entrances, a real
nonzero omitted-Unit source occurrence through admission and reader replay,
and malformed destination/foreign occurrence rejection. Preserve existing
AuthoredRecipeIntegrity validRepresentation, non-Unit/non-Authored source,
wrong-edge and memoPosition assertions; its hand-made zero source positive is
not a substitute for the real producer. Minimal controls only establish compile
behavior. The unchanged callback must execute against its existing golden.
[Saved investigation](../../../evidence/performance-regression-history/value-passing-implementation/callback-unit-investigation/investigation.json).
