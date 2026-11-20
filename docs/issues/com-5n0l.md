---
id: com-5n0l
status: in_progress
deps: []
links: []
created: 2026-11-20T06:16:22Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-yeua
tags: [frontend, verification]
---
# Eliminate declaration-order-dependent empty-array overload selection

Contract: body-checking.md Contextual Inference and Commitment, name-lookup.md shared callable applicability, spec/02 available forward expectations. Fixed33d1011d reproduces declaration-order-dependent acceptance: fn accept(value: I64) {} then fn accept(value: Array[I64]) {}, main accept(value: []) rejects with the non-array empty-literal diagnostic; reversing declarations succeeds. Source and actual statuses/messages are retained in meta evidence/rejection-domains/diagnostic-domain-implementation/phase3-array-context-refusal-plan.json issuer_controls. This is not a valid negative oracle to bless via diagnostic classification.

Investigate and repair the actual candidate-to-context path: no candidate-local expected typing may commit into shared source state or become selected authority before all applicable candidates are considered. Pin the precise first-authority producer and eliminate the competing early path; do not merely ignore the resulting error or change final diagnostics. Preserve forward local inference, evaluation order, callable labels/defaults, generic caller binders, normal selected signatures, Array element identity and dynamic method/free call distinctions.

This exact empty/context-demand selection defect differs from com-zy6r (already typed nested array identity), com-m13a (input-authority narrowing) and com-kuls (factory-privacy test intent). Relate those scopes without treating their assignment as this repair. com-8uik must not adopt classification before this prerequisite restores the positive overload control. Part of existing-feature phase3, not a new language feature.

## Acceptance Criteria

RED before repair: both declaration orders and direct/block-yield empty array arguments; ground scalar versus Array and two genuinely viable Array contexts; exact saved selection and source publication checks. Confirm expected outcomes from spec, not the old first-order failure. Cover shared free/method paths that use the same defective producer and generic forwarding/closure/non-array rejection noninterference. GREEN must reach actual check/AOT/ORC and retained selected-call/final execution, preserve raw API behavior, and receive independent source/test review. Document exact root and removed competing authority. Parent phase3/whole gate remains open.


## RED and actual first authority

Fixed33d1011d rejects the new ordinary run fixture at its first scalar-first empty-array call. It incorrectly accepts both direct and block-wrapped two-Array ambiguity fixtures. Exact results: meta tmp/phase3-array-context-refusal/overload-red.json (classification audit evidence links the source controls). A Text-loader raw-API probe finds two visible candidates, both rank1 and an Uncomputed callee cache before preparation: no candidate-state mutation was established. Text does not force-load Std, so this probe does not by itself establish the File CLI first-authority path; a real File/Std probe is required. Empty Expr.Array returns false from expressionNeedsTypeContext; both candidate comparisons fail and selectFreeFunction uses its firstLabel diagnostic fallback.

WIP uses the shared context-demand rule for empty arrays plus one private syntax/canonical-Array-identity shape filter in common contextualArgumentMatchesType. Blocks/if/match forward the same possible-shape constraint; numeric/function behavior, rigid/unknown contexts and actual selected-parameter checking remain distinct. It does not check or publish a candidate value type. Fresh CLI/final-consumer checks and independent review are pending; no repair completion claim.

File/Std probe has now completed: original33d1011d gives candidate ranks1/1 with Uncomputed cache and nonzero canonical Lang Array identity; WIPea57228a gives1/2. Std is loaded and both parameter heads retain declaration identity. This confirms the actual fallback path independently of the earlier noLang Text probe. Independent source review found no current must-fix; it requires if/match/divergent-branch, nested-array, fn/record/any, symbolic/projection/noLang preservation and final publication/execution controls before closure.

The first trial exposed an actual reentry bug before adoption: unconditional empty demand recurred after Array type publication, and merely checking term0 still left non-Array contexts reentering before refusal. Record now applies its completion context through a private core with recordMissing=false; the public contextual-construction entry retains recordMissing=true. This closes the same-expression construction backedge without a global flag or scalar-success fallback. Independent source review accepts this phase separation. The new manual File/Std harness now exits0 with its exact golden and empty stderr, proving repeated candidate comparisons do not publish expression/callee state, actual15-control source preparation retains selected callee identity, and the existing non-Array I64 refusal is finite and cached. Fresh CLI/negative-wrapper/nested/noninterference and performance gates remain pending.

Fresh3ea44674 build20261120T064044-build-4ff513 passed immutable. All15normal outputs reached AOT/ORC;54old/new mode controls preserved acceptance, domain and execution (8positive LLVM pairs exact, generic_empty_array_arg differs only by a verified bijective internal-symbol renaming with all definitions/references/bodies equal). New ambiguity tests remained RED: argIsUntypedIntLit mistook an unresolved array scalarInfo for an integer, emitted the old integer-only Unclassified error. Current local fix preserves argResolvedTypeInfo and its failures, then additionally requires the existing integer numeric-expression shape; no domain classifier bypass. Independent source review accepts this correction. The enhanced manual test rejects the old integer misidentification and passes source-native with exact stdout/empty stderr. Second fresh candidate, numeric-wrapper diagnostic deltas and final gates remain pending.
