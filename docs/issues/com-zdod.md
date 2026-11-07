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

## Consumer Migration Checkpoint

Executed SemanticTraitViewConsumers REDs show compatibility and stored/explicit
argument recovery dropping positional arguments, a view-argument traversal gap,
and a same-spelled trait incorrectly activating an extension. Three positive
controls passed. Production consumers now retain ResolvedViewSource through
exact set comparison, argument recovery and extension activation. Semantic
compatibility mirrors no longer decide identity; view-cycle traversal uses the
shared semantic child reader. Extension activation tests the retained kind
(owner zero), not merely a matching name. Spelling-only recovery/set helpers
have no remaining callers and were removed.
[Executed evidence and caller/key reconciliation](../../../evidence/rejection-domains/diagnostic-domain-implementation/semantic-trait-view-consumers-increment.json)
records five REDs, three preserved controls, and fresh GREEN for 11 consumer
cases plus all 69 earlier cases (80 total). Build 20261107T022411-build-4fedcf
passed. New controls cover compatibility mirrors, duplicate parameter source
sets and actual internBodyInstance/findBodyInstance keys. Layout-only array
mangles remain distinct from semantic body keys; do not add selector spellings
to physical layout names or use those names as semantic equality.
Task-wide gates and completion review remain pending.

## Qualified Binder Checkpoint

Four native REDs expose qualified alpha head short-circuiting, owner-established
nominals mistaken for same-spelled binders, and same-spelled non-designated
parameters treated alike. Matching explicit alpha binder slots now establishes
only a head correspondence; view sources and children still compare. A shared
head classifier distinguishes canonical parameters from nominal/structural
constructors; plainBinder additionally requires an unqualified occurrence.
Non-designated ParamIds remain rigid. This changes no implicit policy for
solving an unknown view-qualified generic argument. Positive same-alpha and
same-rigid-identity controls passed before repair.
[Four REDs, two preserved controls and fresh verification](../../../evidence/rejection-domains/diagnostic-domain-implementation/semantic-trait-view-qualified-binder-increment.json)
records successful build 20261107T023851-build-3d74c1 and all seven fixture/86
native case executions passing. binderIndex is read-only. Completion gates and
independent review are still outstanding; this checkpoint does not certify them.

## Independent Completion Review

Neutral read-only review of b7083d0e derived the guarantees from spec/design
before inspecting the implementation and evidence. It found two scoped defects:
directional unification ignores non-designated ParamIds, and postorder view
normalization does not consume canonical nominal owners established by admission.
Executed counterexamples confirm the former (wrong true result) and the latter
(mixed stamped/unstamped duplicates rejected, also in reverse order and nested).
Same-identity/designated-binder and already-stamped controls remain GREEN.
Repair impact review at 472595cb accepted both fixes and test validity.
[Executed repair evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/semantic-trait-view-review-repair.json)
records build 20261107T025754-build-a0396f and all seven fixtures/97 native
cases passing with unchanged inputs. The reviewer independently reconciled the saved GREEN and changed-file hashes.
Formal performance and whole-task gates remain outstanding; no closure yet.

The normalized result must publish established declaration identity, rather than
make later equality repeat lookup or depend on private admission tables. Raw
input rows remain immutable. Rigid parameter heads compare lexical IDs, while
only explicitly designated pattern binders may bind. Alias/original-name and
same-spelled foreign-owner controls remain part of the required reconciliation.
The known projection/record head relation belongs to com-bvc8; a selector with
those arguments inherits that boundary, so results do not claim universal
projection/record identity is repaired.

## Measured Reader Cost

[Formal self-host and diagnosis](../../../evidence/rejection-domains/diagnostic-domain-implementation/semantic-trait-view-self-host-before-reader-repair.json)
reached generation-three LLVM/runtime fixed point, median 11.444476s. The
adopted carrier compiled that same source in 7.178753s. This is not acceptance
of the seven-second performance condition. CPU samples and optimized LLVM
identify the newly added view-argument loop passing the whole Comp by value
from hot child-count queries. The loop only needs its range and source pool.
A scoped behavior-preserving repair moves those loops to the pooled-range
owner, retaining read-only semantics and the common semantic-child API. No
compiler-specific retain/drop exception or fake mutable receiver is allowed.
Build 20261107T034443-build-7cc5a2 passed for ec812e66. All production
callers now use the owning Arena readers directly; five Comp wrappers were
removed, and two internal tests follow the API without expectation changes.
Neutral impact review found no semantic change or missing child. The linked
[reader-cost record](../../../evidence/rejection-domains/diagnostic-domain-implementation/semantic-trait-view-reader-cost.json)
retains alternating same-source diagnosis: old median 11.189354s versus fresh
candidate 6.992590s. This is not a new formal fixed-point measurement. [Native revalidation](../../../evidence/rejection-domains/diagnostic-domain-implementation/semantic-trait-view-arena-readers-green.json)
passes all seven fixtures/97 cases with unchanged inputs. [Formal remeasurement](../../../evidence/rejection-domains/diagnostic-domain-implementation/semantic-trait-view-arena-readers-self-host.json)
reaches generation three but median 7.045220s is still over the strict seven
second threshold (samples 7.646217/7.045220/6.659092). Do not certify from the
single sub-seven sample. A final local read optimization uses the already-held
empty view-source range in all four grounding wrappers before asking the pool
for its argument count. Full sources still enter the unchanged traversal.
Build 20261107T041032-build-26fd48 passed; candidate
bin/plewc-semantic-trait-view-empty-range. Neutral impact review confirms that
the guards follow from the old count relation, including raw empty-range and
legacy/projection behavior. Same-source alternating diagnosis compares the
previous fixed-point median 6.751016s with fresh candidate 6.615871s. [Native revalidation](../../../evidence/rejection-domains/diagnostic-domain-implementation/semantic-trait-view-empty-range-green.json)
passes all seven fixtures/97 cases with fixed inputs. New formal performance
and applicable task gates remain pending.

## Remaining Work

Reconcile qualified-binder handling, alias/owner
and normalization composition scenarios, complete keys/rebuild/caller use,
applicable normal/fixed-point/performance gates and neutral completion review.
Keep known projection-versus-receiver category repair assigned to com-bvc8;
coordinate shared readers without claiming that whole repair here. Syntax,
source conformance proof and final executable view selection remain separate
mandatory tasks. Task and parent remain open.
