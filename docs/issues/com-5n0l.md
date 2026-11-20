---
id: com-5n0l
status: open
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

