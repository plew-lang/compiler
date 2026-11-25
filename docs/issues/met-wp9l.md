---
id: met-wp9l
status: in_progress
deps: [met-u9uu, met-uy77]
links: []
created: 2026-11-24T05:14:39Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-eqw2
tags: [frontend, diagnostics]
---
# Classify qualified declaration members before value admission


## Contract and boundary

Establish argument-independent qualified member category and canonical declaration-set identity before rejecting callable declarations as values. Reuse receiver/view/module/visibility discovery, not empty-argument callable applicability or typeHasAssocFn Bool. Preserve structural fields, namespace-qualified globals, lexical value precedence, normal assoc invocation and instance/static distinction. Missing/private members and dependency failures stay distinct. Retain real source operation/owner and negative category through cache and owning consumer.

## Scenarios and completion

Existing assoc_fn_value_arg check/AOT/reachable ORC RED-to-GREEN, methods as values, overloads/aliases/views, real closure fields/static globals/type qualifiers/missing/private controls, Raw/synthetic/foreign owner/session and failed builder retries/drain. Producer through final consumers, shared lookup responsibility, fresh candidate and independent review required. Named declaration transport is met-5vgp; successful binding readers remain com-tr3a.

## Reviewed implementation increments

1. Establish a receiver-scoped candidate reader before groundedMethodArgMatchRank in findAssocWithOrigin/findMethodWithOrigin. It retains canonical declaration or abstract requirement, associated/instance category, receiver/source/view proof and visibility disposition; use name-index cursor if whole candidate-array allocation would add normal-call cost. Normal call alone performs argument label/type/default/rank/ambiguity selection. Do not select one overload without arguments.
2. Record classifies real storage fields first and retains actual callable-category failure through private source provenance/cache/owning consumers. Remove typeHasAssocFn/typeHasMethodNamed Bool authority from the migrated path. Preserve Raw/unknown/malformed and missing/private differences.

Independent typing_obligation_plan_review endorsed these boundaries, not implementation completion. Actual source confirms Resolve/Lexical rewrites namespace Field to Ident and records namespace-use identity; associate-value reads are rewritten by rewriteAssocValReads before Record. Preserve those transformations and their source origins, rather than mistaking any Field or qualifier as a callable. Generic binder/bound and provided/conditional receiver evidence need small probes before extraction; call-argument-dependent conditions cannot be invented at a non-value use. Full findMethod redesign and successful generic reader migration stay out of scope.

## Current Remaining Scope

Name-reader extraction, namespace/type-binder prerequisite met-u9uu and namespace
Field-to-Ident provenance met-uy77 are independently accepted finite increments.
On the measured carrier, the qualified60-mode control has18 unmet assertions,
all associated/instance/trait-bound; namespace refusal and lazy/normal controls
pass. The remaining work is the declaration-group producer and retained owned
refusal for those member surfaces, not repeating the namespace repair.
[Current evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-namespace-declaration-origin.json).
The initial RED below remains a historical reproduction. Parent completion still
requires the remaining scenarios and applicable whole gates.

## Fixed-candidate RED

Measured fixed-point cb9eebb5 (named product b43af163) runs42 qualified modes:21 intended RED assertions,21 normal/lazy controls pass; immutable inputs. Concrete associated and abstract bound T.make fail unavailable value typing, instance method-as-value is reported as missing structural field, namespace Field-to-Ident retains correct named-declaration text but loses owned source origin. All18 ordinary assoc-val/namespace/import/alias/type-binder/overload controls pass; three unrequested ORC bodies remain uninspected. Scratch result: meta/tmp/phase3-forward-frontier/qualified-callable-cli-red-v1/result.json. No qualified product repair yet.

## Name-reader increment (not task completion)

Private TraitMemberNames cursor is shared by staticMemberResolution before labels and proof. It returns canonical slot/function, associated role and visibility, never applicability/Source authority. Requirements/provided arrays, labels-before-proof, preferred source and instance dedup/rank order remain at the consumer. Independent source review found no must-fix; an extra provided Func read is an unproven cost concern, not permission to introduce signature snapshots. Baseline label-frontier native succeeds with actual query count; poisoning Selected gives expected -6, while Unrelated wrong labels is not queried. The direct reader/no-proof controls and fresh build were subsequently
independently accepted in the name-reader increment below. Namespace source
transport is independently closed in [met-uy77](met-uy77.md); associated,
instance and trait-bound category transport remains unfinished. Evidence: meta/evidence/rejection-domains/diagnostic-domain-implementation/phase3-qualified-member-discovery.json.

## Declaration-group admission versus call applicability

Neutral review clarified that an admitted non-value binding is not an applicable call. For an inherent nominal declaration group, retain canonical receiver/group identity, role, visibility and matching receiver pattern; method/call argument conditions are not solved without a call. Different concrete receiver specializations must remain distinct, and an incomplete generic head retains the unresolved matching group rather than selecting one specialization. For lexical-bound/provided/trait-view surfaces, existing receiver/bound/source proof establishes where the group comes from. Neither case invents call arguments or an expected function type. Lower origin/owner and actual binding admission remain required; a spelling Bool or name-reader alone cannot publish Source authority. Preserve real fields/assoc values/globals first. Required contrasts: conditional inherent groups, incompatible concrete receiver pattern, incomplete generic head, private candidate, field/static value, absent provided/trait-view proof.

The first name-reader increment5c81e676 is independently recognized as complete after build8f7316/exact197source/native reader and poison sensitivity/qualified45 unchanged/named45 GREEN. It is only one increment; remaining qualified rejection cases are still RED. met-u9uu separately repairs the real namespace/type-binder prerequisite.

## Current implementation boundary

Nominal reader9d488af2 is shared by normal method/assoc lookup. Frozen build
20261125T141437-build-df9d68 passed; corrected adjacent-std setup preserves old
60-mode result exactly (18 expected REDs, normal contrasts GREEN). The initial
missing-std run was a setup failure, not a product regression.

Uncommitted member admission now derives Field/receiver internally and saves an
opaque private admission journal; rejection/consumer use its index, not a caller-
supplied group. Kind, Lower serial/span/base/name, session/root/owner, failure
retention and retry are checked. Independent review exposed supplied-group
permission and preferred-proof ordering defects; both were repaired, with the
ordering helper shared with normal static lookup. Value-Field Bool diagnostics
were removed. Source/ViewSet reader extraction preserves normal call filters,
proof/rank/pass order; read-only source predicates now accurately use fn.

Lower.SourceSelection written dotted members now use pushAuthoredField with
prefix spans; synthetic fields remain untrusted. Native controls cover concrete,
bound, provided, trait/extension/static views, newtype, conditional inherent,
incomplete heads, Raw/foreign/mutated/synthetic/retry/cursor, mismatched receiver,
absent proof, foreign private provided and real function storage. These passed
in member-declaration-storage-proof-native-v2 before two new boundary REDs.
Frozen group build20261125T142908-build-6d3f1f passed and75/78 CLI modes passed;
remaining3 were inherited-newtype refusal, subsequently fixed in native probes.

### Remaining confirmed defects before next candidate

- Independent review: group must retain distinct canonical source/priority
  families, not discard fallbacks based on basename before arguments exist.
  Native Families control expects2 alternatives; current name-only preference
  leaves1. Preserve true same-declaration/path dedup, not cross-family selection.
- Independent review and actual MultiTrait RED: full Reader[I64] selector still
  admits Reader[Bool] nominal member. Owner/arity/source head and saved receiver
  alone are insufficient. Bind each trait-owned alternative to its exact
  conformance/witness and complete instance, preserve that proof in the group,
  and filter against the admitted selector before publishing Source authority.
  Include intermediate proof-path instances when a selected source is a bridge.

Native/CLI logs and fixed snapshots are under meta/tmp/phase3-forward-frontier;
archive necessary compact evidence before cleanup. No parent/task closure, no
current formal performance/main green claim. Next: fix these two REDs, extend
producer/consumer contrasts, fresh candidate and formal7.5s validation.
