---
id: com-9hde
status: open
deps: [com-zdod]
links: [com-amjl]
created: 2026-11-06T23:54:58Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, generics, verification]
---
# Parse and lower complete trait-instance views in type and value syntax

Contract: [spec09](../../../spec/spec/02-type-system/09-extensions.md) method-source selection and complete trait-instance views; [Types and Evidence](../design/types-and-evidence.md) sections2-4 and [Name Lookup](../design/name-lookup.md) section5. A selector means canonical trait owner plus every positional argument; no argument omission even with one conformance. Memberless views and associated projections are distinct. Extension sets remain separate from the single complete trait selector; unrelated base members remain visible under the existing rules.

Evidence: [executed investigation](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-view-instance-state.json), source8a2ab6c6, exact Syntax8c89204230c3d865ea95a03382c3fd213731e1de. Sixteen check inputs and five JIT/five AOT executions were independently reviewed. The carrier has experimental cycle Source annotations unrelated to selection; it is not an adopted final candidate. Initial direct-requirement declaration overlap is excluded as a view control; wrong-instance refusal is not validated by failures that also reject matching calls.

## Scope and Endpoint

After the shared term artifact exists, support a#P[I64] and A#P[I64] through exact shared @Plew/Syntax nodes, legacy AST adapter, immutable Syntax lowering and authored provenance. Value parsing currently treats the brackets as indexing (Syntax3348); type parsing5008 drops P without a following member and leaves projection arguments, which Lower/Types742 copies into assocTraitArgs. Resolve the selector declaration in lexical scope before validating positional arity; do not infer omitted arguments or recover an absent owner from global spelling.

Both source forms must lower to the same complete selector contract, with T#P[I64].Item preserving its existing receiver/trait/member identity. Require all positional arguments even for one available conformance; preserve argument-free traits and distinguish wrong arity from unknown trait. Preserve refusal of impl A as P when P has parameters; when using the shared trait arity admission, diagnose the known declaration's missing arguments rather than an unknown trait. Update Syntax exact dependency revision/lock consistently; no local override as completion.

## Guarantees and TDD

Turn the saved explicit value-view and matching annotated-view failures into producer-boundary regressions. Cover value/type/projection syntax, zero/one/multiple positional args, missing/extra args, nested type applications, aliases/qualified owners and two instances of one trait. Inspect actual lowered selector and children/provenance; parse success or byte spelling alone does not prove valid formation. Pair malformed syntax/error recovery with ordinary indexing: a#P[Args] must not become an index operation, and existing legitimate indexing after views and parenthesized expressions must not silently change. Include valid setups for array#Ext[index], array#NoArgTrait[index] and (array#Ext)[index], alongside parameterized trait arguments; these are preservation test requirements, not a new ambiguity rule. Do not guess type versus value from identifier spelling; if an actual grammar/meaning conflict cannot be resolved under the approved rules, stop for a decision rather than silently add a new precedence/whitespace rule.

## Completion and Boundaries

Close the Syntax->Lower->shared published selector path with meaningful RED/GREEN, exact Syntax pin uptake and neutral review. A successfully formed term is not proof of receiver conformance or correct method dispatch. Associated projection and memberless view arguments must not share phantom storage. com-amjl owns common source-conformance evidence admission; the call-selection task owns actual exact-instance dispatch/final consumers. Existing extension bindings, ordinary indexing, block/interpolation syntax and projection rules are preserved; no parser-wide cleanup, new surface feature, blanket undeclared-type recovery or verifier weakening.


