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

Replace owner/arity-only view identity with retained canonical owner and positional semantic argument terms. Trace ResolvedViewSource/ViewSource, view construction/publication, interning/equality, traversal/folding, occurs/free-binder queries, substitution/grounding, view-set normalization and keys consumed downstream. The original owner-only carriers and comparisons identified by the investigation must be replaced through their real structural consumers. Establish one shared semantic instance authority rather than another lookup-specific tuple or projection-field mirror.

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

## Implementation Decisions

ResolvedViewSource retains TraitInstanceKey (canonical owner plus positional
semantic arguments). CallableSourceHead is explicitly a coarse candidate
bucket, not semantic identity or a final selection receipt (com-4k31).
Full instance equality compares argument terms; head matching leaves children
to the designated-binder traversal. Exact source-set equality has a separate
name and is used by the existential compatibility consumer. Projection mirror
views remain receiver-owned. Obsolete pooled-id and duplicated set relations
were removed from the migrated structural paths.

Environment/witness/legacy grounding and body projection normalization transform
view arguments using their existing substitution/proof authority. The rebuilding
bridge preserves owner and diagnostic use metadata. Caller-owned replacement
terms are not recursively captured by the same substitution. typeRefViewSources
is read-only and does not require mutable Comp access.

Raw source heads are checked before folding, so normalization cannot hide a
malformed duplicate. Complete-instance comparison follows child admission, so
unchecked cyclic children cannot enter equality. The admitted receipt maps raw
terms to immutable normalized terms; graph nodes and constructor/binder ranking
consume that mapping. Common semantic-child reconstruction handles projection
receivers, record fields, ordinary/associated arguments and selector arguments.
Original rows are not rewritten, and unchanged terms do not allocate replacement
child arrays. No separate graph-only equality solver was added. This boundary
does not solve concrete receiver conformance.

## Executed Evidence

- [Carrier/readers](../../../evidence/rejection-domains/diagnostic-domain-implementation/semantic-trait-view-first-increment.json): five native REDs, two positive controls, fresh build and existing identity/publication controls.
- [Grounding](../../../evidence/rejection-domains/diagnostic-domain-implementation/semantic-trait-view-grounding-increment.json): six native RED/GREEN cases across explicit/nested/caller-owned/witness/legacy/body normalization.
- [Relations/builders](../../../evidence/rejection-domains/diagnostic-domain-implementation/semantic-trait-view-relations-increment.json): rigid/alpha/full-set equality, designated-binder consistency and positive control, occurs, duplicate builders; actual nongeneric direct/stored view check/JIT/AOT controls. An initial binder test rejected for mismatched compatibility mirrors and is excluded from RED evidence; aligned builders expose the intended RED.
- [Raw boundary RED](../../../evidence/rejection-domains/diagnostic-domain-implementation/semantic-trait-view-raw-boundary-red.json) and [admission repair](../../../evidence/rejection-domains/diagnostic-domain-implementation/semantic-trait-view-admission-increment.json): missing/extra arity, extension arguments, invalid refs/foreign binders, distinct instances, top-level/nested duplicates, and malformed metadata combined with child normalization. The intermediate metadata-fold WIP was tested RED and repaired before claiming GREEN. Native assertion aborts are failed tests, never passing rejections.

Latest build 20261107T020653-build-11a31c passed with fixed inputs. Candidate
bin/plewc-semantic-trait-view-admission passes six internal fixtures/69 case
executions. The final duplicate tests also assert that original input rows retain
their duplicate source data. The first broad run remains recorded as failed:
multipleTraitViews originally omitted the parameterized A selector's argument.
Its internal setup now supplies [I64], preserving the original multiple-trait
Input diagnostic assertion. Only changed fixtures were rerun; unchanged inputs
retain their exact prior result. This is not whole-suite or task certification.

## Remaining Work

Reconcile remaining Infer/Type and TypeRecovery view-id consumers, alias/owner
and normalization composition scenarios, complete keys/rebuild/caller use,
applicable normal/fixed-point/performance gates and neutral completion review.
Keep known projection-versus-receiver category repair assigned to com-bvc8;
coordinate shared readers without claiming that whole repair here. Syntax,
source conformance proof and final executable view selection remain separate
mandatory tasks. Task and parent remain open.
