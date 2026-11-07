---
id: com-zdod
status: in_progress
deps: []
links: [com-oir7, com-bvc8, met-c1pg]
created: 2026-11-06T23:54:58Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, generics, verification]
---
# Retain complete trait instances in semantic view terms

Contract: [spec09](../../../spec/spec/02-type-system/09-extensions.md) method-source selection and complete trait-instance views; [Types and Evidence](../design/types-and-evidence.md) sections2-4 and [Name Lookup](../design/name-lookup.md) section5. A selector means canonical trait owner plus every positional argument; no argument omission even with one conformance. Memberless views and associated projections are distinct. Extension sets remain separate from the single complete trait selector; unrelated base members remain visible under the existing rules.

Evidence: [executed investigation](../../../evidence/rejection-domains/diagnostic-domain-implementation/trait-view-instance-state.json), source8a2ab6c6, exact Syntax8c89204230c3d865ea95a03382c3fd213731e1de. Sixteen check inputs and five JIT/five AOT executions were independently reviewed. The carrier has experimental cycle Source annotations unrelated to selection; it is not an adopted final candidate. Initial direct-requirement declaration overlap is excluded as a view control; wrong-instance refusal is not validated by failures that also reject matching calls.

## Scope and Endpoint

Replace owner/arity-only view identity with retained canonical owner and positional semantic argument terms. Trace ResolvedViewSource/ViewSource, view construction/publication, interning/equality, traversal/folding, occurs/free-binder queries, substitution/grounding, view-set normalization and keys consumed downstream. Current Ir.pw:81/2865, Frontend.pw:964 and Registration.pw:1089 cannot distinguish argument values. Establish one shared semantic instance authority rather than another lookup-specific tuple or projection-field mirror.

Publish a well-formed structural selector artifact that later syntax lowering and lookup can consume. Positional arguments are semantic children in their owning compilation/binder environment. Projection-only assoc fields cannot represent memberless views. Normalize duplicate identical selectors; retain extension-set order independence; distinguish different arguments and same-spelled foreign owners. Preserve selected evidence/cache identity through storage, copying and rebinding. Do not mark existing source/call paths fixed merely because a new field/type or equality helper exists.

## Guarantees and TDD

Meaningful structural REDs for same-owner/same-arity different arguments; same complete instance with distinct use spans/aliases; nested generic argument substitution, rigid versus designated binder matching, view argument traversal/occurs, duplicates/order, foreign owner/domain and malformed arity/ref inputs. Exercise production builders and actual structural consumers, not self-mirroring tests. Record real callers and remove owner/arity-only competing identity decisions from the covered term layer. Common structural validation must distinguish raw Input from authored diagnostics without solving concrete conformance.

## Completion and Boundaries

Close when the retained term plus affected real construction/structural-operation callers share the contract, targeted native/structural tests and neutral review pass, and compatibility adapters have explicit removal conditions. Syntax support, source proof and executable method selection remain owned by dependent tasks; no full view implementation claim. met-c1pg consumes this artifact for scoped graph admission/relations; do not invent another cycle-only type solver. com-bvc8 retains projection-versus-receiver mirror category repair; coordinate shared readers without absorbing its whole scope. com-oir7/com-vh0x/com-j2i7 remain API-authority repairs, not substitutes for this algorithm/representation repair. No whole-TypeRef redesign, new lifetime/unique features, general conformance solver or main/seed promotion.



## Execution Scenarios and Increments

1. Structural carrier migration: reuse TraitInstanceKey in ResolvedViewSource;
   keep owner/arity-only callable buckets explicitly separate from complete
   semantic selectors. Preserve currently valid zero-argument view behavior with
   existing identity/publication and native nongeneric view controls. This is
   representation-only scaffolding, not a behavioral RED or feature completion.
2. Once the input can carry arguments, execute native REDs against unchanged
   owner-only semantic comparison/traversal: different same-arity arguments,
   actual child reachability, open/projection-containing view arguments. Pair
   identical keys, use-span differences and different owners with GREEN controls.
3. Repair the shared structural owner: semantic head/children, normalization,
   equality/matching, closedness/projection caches and malformed-input admission.
   Record and projection receiver mirrors must not introduce competing children.
4. Follow production rebuild/substitution/grounding paths; preserve nested
   caller-owned argument terms and scoped binders without recursive reapplication.
   Test retained view identity through real builder/readers and invalid-input
   typed boundaries. Keep final source/call selection assigned to dependents.
5. Reconcile actual callers and every scenario, remove obsolete semantic
   identity paths, build a fresh candidate and run affected positive/negative
   controls, applicable normal validation and neutral completion review.
   Performance follows the unchanged parent policy; no claim from unmeasured
   counters or a constructor-only test.

Do not count missing-new-field harness compile failures as defect RED. Pure
carrier migration uses preserved GREEN controls; newly representable input must
reach an executed assertion before being counted as a behavior regression.

## First Structural Reader Checkpoint

Carrier migration and the first equality/traversal/cache repair are implemented,
not task completion. [Executed RED/GREEN and build evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/semantic-trait-view-first-increment.json)
records five genuine native REDs, two preserved controls and fresh-candidate
GREEN for all seven; TypeTermPublication and seven canonical identity controls
also passed. Standard build 20261107T012241-build-3ee70c passed with fixed inputs.
The coarse callable head has been named CallableSourceHead; it intentionally
remains insufficient for final selection (com-4k31). Full semantic equality
compares argument terms, while head matching leaves those terms to designated
binder traversal. Projection compatibility mirrors remain receiver-owned.

Still required: normalization and ordering/duplicates, structural raw admission,
view arguments in explicit/witness/body/legacy grounding and rebuild paths,
rigid versus designated-binder scenarios, nested and caller-owned replacements,
real key/caller reconciliation, applicable gates and neutral completion review.
The graph uses normalized source heads, so its children must be reconciled with
that normalization before claiming parameterized duplicate-selector support.

## Grounding Checkpoint

[Six executed RED/GREEN cases and second fresh build](../../../evidence/rejection-domains/diagnostic-domain-implementation/semantic-trait-view-grounding-increment.json)
cover explicit environment substitution, nested selector arguments,
caller-owned replacement terms, witness grounding, legacy grounding and
body projection normalization. Build 20261107T013334-build-ea255b passed;
the fresh candidate retained the original seven assertions and eight existing
native controls. The view-rebuilding bridge changes selector children while
preserving owner/use provenance; each grounding operation keeps its existing
substitution/proof authority. typeRefViewSources is read-only and no longer
requires mutable Comp access.

Task remains in progress. Next cover raw selector normalization/admission,
rigid versus designated-binder matching and occurs checks. In particular,
unifyPatterns/typeRefsAlphaEq/occursInPattern still have legacy argument-only
walks; reconcile these actual consumers rather than declaring the shared
reader fix sufficient. Follow with keys/callers, gates and independent review.
