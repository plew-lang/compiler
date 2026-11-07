---
id: com-9hde
status: in_progress
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



## Initial Producer Scenarios

Start with the existing-API producer regression in Syntax/tests/TraitViewSelectors:
memberless A#P[I64] must retain its selector through direct parsing, materialization
and freezing; zero-argument A#P and A#P[I64].Item are preserved controls. Extend
this to complete child arguments, aliases/qualified paths and ordinary indexing
before final uptake. A parser setup failure is not semantic RED. Product source
remains unchanged until the executed regression is established.

## Grammar Handoff Contract

The [executed producer RED](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-view-syntax-producer-red.json)
shows the lost type-position selector. Value-position brackets may be positional
trait arguments or existing indexing. Shared Syntax must preserve sufficient
syntax to classify that application after lexical source binding. Parameterized
traits require a complete application; extension and zero-arity trait views are
already complete before the preserved index. No name-spelling guesses, semantic
fallback between meanings, or compiler-owned reparser is permitted.

A prior implementation note incorrectly made this internal direction contingent
on user approval. [Neutral contract review](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-view-type-alias-controls.json)
confirmed it follows from spec09, this task's preservation requirements and the
adopted syntax handoff design. No approval was inferred from a continuation;
the unnecessary confirmation request is withdrawn. The concrete representation
still requires design and meaningful producer/consumer tests. Consult the user
only if meaning remains undecidable under existing rules, or a proposed solution
changes the surface/precedence/parenthesis requirement. Qualified namespace vs
trait/projection interpretation follows the same existing ownership boundary.

## Type-position increment (in progress)

Shared Syntax ae70dd4ef7ee67aa12d9449f909a356cb0c84989 / 0.1.11-dev.31
retains rich view-source rows separately from associated projections, including
arguments, labels and original spans through direct parsing/materialize/freeze.
[Producer increment](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-view-type-syntax-increment.json)
records 15 golden fixtures / 34 distinct reconciled cases and neutral review.
This is not package-wide or task-wide completion. Exact manifest and lock uptake
uses the normal resolver, without a local override.

[Executed Lower RED](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-view-type-lowering-red.json)
uses actual Frontend analysis plus an AST adapter control. Annotation, AST,
nested and multiple arguments lose the complete selector. Missing/extra/named
arguments and extension arguments are accepted. Plain and projection controls
pass. Unknown source is already rejected; retain its existing message rather
than treating wording alone as an acceptance defect. Its missing Source
classification remains an actual failure of the new domain assertion. The new never-green test's
expectation was corrected accordingly.

Current repair passes the rich rows to a shared finalizer, keeps legacy mirrors
as fallback only, and preserves rows through type-path/projection normalization.
Known-owner arity and positional-only checks do not establish conformance.
Standard build and focused native verification succeeded; see the finite increment below. Value
bracket handoff, qualified selector production, impl known-owner arity admission,
alias/module controls and task-wide completion remain open.

Neutral incremental review found legacy viewNames/extView bypassed the shared
finalizer. Added two compatibility AST cases; both executed RED after the first
build. All four rich retention cases and plain/projection controls passed.
The invalid forms now reject, but their Unclassified domain failed the new
Source assertions. The second repair routes both carriers' compatibility fields
through the same finalizer and marks authored rejection producers as Source.
Second standard build: 20261107T093420-build-5cbd97 succeeded. No blanket
adapter conversion and no conformance-evidence admission change.


[Type Lower increment verification](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-view-type-lowering-increment.json):
13 new cases and 43 existing consumer/matching/projection controls pass through
fresh compile/link/native, exact goldens and empty runtime stderr. Both input
inventories remain unchanged and match current files. The standard build passed.
Neutral review confirmed the compatibility fix and producer-only classification;
final review independently reran all 56 saved native cases and verified all
187/191 recorded input hashes against current files. No additional required fix
was found for this finite increment. This finite increment does not close
the whole task or certify a full suite/performance gate. The remaining boundaries
listed above stay open.


## Known-owner impl arity increment (in progress)

This existing task requirement is independent of the still-open value-bracket
implementation. [Executed RED and scope](../../../evidence/rejection-domains/diagnostic-domain-implementation/impl-trait-arity-increment.json):
valid one-argument and zero-argument conformances pass; missing/extra arguments
incorrectly diagnose an unknown trait. Unknown trait is already rejected, not an
acceptance defect. New AST/spanless controls additionally exercise the adapter.

Resolve the lexical owner before strict positional arity admission. Reuse the
trait instance arity check and carry the resulting canonical head to method
provenance, associated bindings and conformance registration instead of resolving
it again at each consumer. Remove raw-name fallback after a failed resolution.
Standard build 20261107T094608-build-12b01f succeeded. Neutral review found
a new-test positive Err loophole (corrected), and an existing open-owner helper
that did not follow reexports. The17-case native run confirmed14 successes and
3 barrel/alias/missing-through-barrel failures; the previous CLI accepts the
valid File graphs. Both open-helper import/reexport branches now use the existing
recursive surface resolver. Source follow-up found no additional required fix.
Second standard build 20261107T095229-build-77741a passed. All17 native cases
(source, AST/spanless, direct/barrel/alias and hidden-name controls),13 type-view
cases and5 existing generic/trait controls pass with unchanged recorded inputs.
Independent final review reran all35 native cases and checked194/197 input
hashes and6 preservation fixture goldens against current files; no additional
required fix for this finite increment. The full task remains open.


## Type alias preservation and qualified-path investigation

[Actual File alias controls](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-view-type-alias-controls.json)
pass direct import, barrel and alias type views, retaining canonical owner,
I64 argument and exact written selector coordinates. All17 executions (including
the13 existing cases and no-argument golden default) pass with197 recorded
inputs unchanged. Neutral review independently reran the cases and checked hashes.
These are preserved GREEN contracts, not a new product repair or task closure.

Namespace-qualified impl setup succeeds, but `S#Types.P[I64]`,
`S#Types.P[I64].Item` and `S#Types.Zero` fail with projection-arity diagnostics.
The parser currently converts the first dot after# into projection fields
before namespace resolution. Do not patch this by spelling guesses or a Lower
parser. The shared-path handoff must preserve segments until their ordinary
binding owner can distinguish namespace, trait and associated projection.
The scope remains in this existing task. Neutral review confirmed unresolved retention follows from the adopted
single-grammar/handoff contract; the earlier unnecessary user-confirmation
request is withdrawn. Concrete representation design is the next step.
