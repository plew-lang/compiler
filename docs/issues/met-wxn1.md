---
id: met-wxn1
status: in_progress
deps: [met-4dxy]
links: []
created: 2026-11-27T15:58:48Z
type: task
priority: 1
assignee: Koji Murata
parent: met-o5z0
tags: [frontend, generics, diagnostics, verification]
---
# Retain inherited associated selections through source and instantiation

Contract: spec08 inherited associated-member uniqueness and docs/design/types-and-evidence.md#associated-member-selection. Read parent met-o5z0 before work. No new source semantics or main/seed/carrier promotion. Preserve candidate identity separately from conformance evidence paths. TDD and independent final review are required; parent certification remains separate.

Consume the common query for both TypeAst/SyntaxType short and explicit projections and trait lexical associated names. Remove declaration-local traitOwnerHasAssocId prefilters in cachedValue/cachedSyntaxProjectionSource and competing candidate selection in chooseShortProjectionSource/lowerLexicalAssociatedType. Preserve ProjectionBoundState readiness, scope and demand timing rather than blindly preparing every unrelated bound.

Publish canonical actual declaring owner/complete arguments/member together with the authored root selector and justified inheritance/substitution recipe. Changed parent arity requires derived argument recipes, not reusing the child argument count. The original Child view must be admitted independently: T:Parent does not justify T#Child.Output merely because normalization produces T#Parent.Output. Keep same-name modules, aliases and original source positions.

Follow that selection through Source type admission, declaration/body facts, generic instantiation and actual AOT/ORC execution. Audit Lower/TypeRecipes, Check/AuthoredTypes, Mono/Resolve assocBindingFor and selected proof output readers. Concrete witness output access is legitimate; fresh member-name/source selection is not. Preserve the original root's conformance path and no late canonical-term mutation to repair missing publication. Remove replaced decision paths.

Guarantees must run end to end, including qualified/short/lexical forms, parameterized/arity-changing inheritance, diamonds, ambiguous/equal-output cases, missing Child view proof, same-name modules and unused body controls. Do not close from saved fields or added invariants alone. If split further, retain this complete producer-to-final-consumer guarantee at this owner.




## Producer-to-consumer implementation sequence

The inherited language matrix is already RED on fixed149aac (39 cases,27 target
mismatches); do not replace it with service-only outcomes. Query unit A is closed.

1. Inspect the two TypeAst/Syntax projection adapters and lexical-self projection
   adapter together with Source recipes/admission. LoweredTypeProjection currently
   has only one source and argument-recipe list: it cannot represent both the
   authored Child proof and substituted Parent output when their arities differ.
   Add the explicit saved selection/provenance at that handoff before changing
   canonical term ownership; do not reconstruct it from an interned term later.
2. Replace chooseShortProjectionSource and direct-member prefilters with the
   common query over admitted matching roots/equation context. Retain bound
   readiness and original declaration scope; avoid eager unrelated clause loading.
3. Derive Parent argument recipes from retained substitution edges, preserve the
   authored Child receiver/view recipes and admission obligations, and consume
   saved selection through AuthoredTypes, facts, Mono and witness output readers.
4. Run qualified/short/lexical and changed-arity accepts through AOT/ORC and
   generic instantiation; NoChildProof must still reject at the authored view.
   Audit/remove competing source/member selection and review the whole B chain.

This is an execution sequence within the existing task, not a relaxation of its
final-consumer completion boundary. Missing/Ambiguous owned transport belongs C.
