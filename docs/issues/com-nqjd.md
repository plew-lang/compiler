---
id: com-nqjd
status: in_progress
deps: [com-m0bf]
links: []
created: 2026-10-24T02:29:50Z
type: task
priority: 1
assignee: Koji Murata
parent: met-6e6k
tags: [frontend, verification]
---
# Stamp late nominal source and synthetic type producers

## Boundary and Entry

Planned paired repair from [C3 inventory](com-m0bf.md#producer-and-reader-inventory),
not a new language feature. Parent criteria 1, 2, 3, 8. C3 classifies;
this task implements its late source/synthetic nominal producer boundary.

Entry: `Resolve/Expr::typedIrRefOfInfo`, `semanticCallableReturnTerm`,
`arrayRefOfElem`; `Resolve/Record::concreteTypeQualifierTerm`;
`Resolve/TypeRecovery::typeInfoOfName`;
`Mono/FreeFn::tyRefOfInfo`/`findOrAddTypeRef`;
`Resolve/ExprType::groundFinalMethodReturn`, `groundFinalMethodParameter`,
`boundMethodRetInfo`; `Mono/Call::groundedSelectedCalleeReturn`,
`chainStageResultRef`/`registerChainSiteInsts`.
Normal named constructions already preserve the selected declaration through
`inferMakeInstance`; do not replace that working path with name lookup.

## Finite Actions

1. Distinguish source nominal recovery from primitive/structural construction.
   A source nominal append after declaration publication must receive the already
   selected owner/complete term or resolve once in its explicit source domain at
   its producer. Use existing declaration APIs; do not globally stamp pushType
   rows by spelling or mutate a published declaration facet. A bare-name cache
   cannot select among unrelated declarations or bind a lexical ParamId.
   Include concreteTypeQualifierTerm: its resolved declaration branch is valid;
   its missing-identity branch may not publish a nominal receiver. Distinguish
   explicit primitive qualifiers from unresolved/foreign nominal names.
2. Preserve the canonical bundled Promise identity for async implicit Unit,
   and Optional/continuation identities for Chain-generated registration.
   Complete terms from child expressions stay complete through nested arrays,
   aliases and generic instances; do not rebuild them from a TypeInfo head.
3. Pair each migrated producer with its actual semantic fact, signature/scan and
   descriptor reads. Reject missing source identity at publication rather than
   reconstructing it downstream. Retire only the paired recovery calls; remaining
   registered-body key recovery belongs to com-6paa. Primitive leaves, Unit,
   function/record structures and rigid ParamId/projection terms need no invented
   nominal declaration.
   This task owns missing complete receiver/return term and lexical ParamId
   recovery, including ExprType adapters and groundedSelectedCalleeReturn. It
   must not attach a nominal owner to boundMethodRetInfo's lexical parameter.
   A missing annotated result is distinct from genuine omitted Unit. fyxe owns
   selecting/reading associated argument context, not these term constructors.

## Exit and Controls

Exact migrated/removal sites and producer -> fact -> explicit environment ->
final read recorded. Add positive alias/same-spelling declaration, nested array,
async implicit Unit and Chain continuation cases plus missing/wrong-owner
internal controls. Preserve already committed arguments and existing source
order/inference limits. Reuse `async_implicit_promise`, `mid_type_recipe_instances`,
`type_term_closedness`, namespace construction/identity and Chain controls.
A source passing now does not excuse an unstamped published nominal term.
Fresh source check/scoped native and rejection controls, pinned hashes and an
independent completion review are required. Global final gates remain G2.
General type-checker/ABI/inference redesign is outside this bounded task.

## Implementation Checkpoint

The first source increment is ready for a fresh build, not certified complete.
Canonical late named/Lang constructors now retain the resolved declaration;
literals supply their fixed ambient type rather than relying on a ref-less head.
Array indexing projects the complete saved child for simple, nested and
existential elements. Missing nominal qualifiers and annotated callable results
no longer create anonymous nominal terms. Chain Promise/Optional/continuation
construction uses the same identity-preserving producer boundary.

The old bound-member return-name traversal is removed in favor of the shared
selected instance/proof. Source result queries and Record use one provided-call
environment, retaining the selected proof. The raw bare-index test is narrowed
to its original index-order intent, and internal async declaration clients now
explicitly supply their minimal ambient Promise fixture; these are internal-test
adjustments permitted by the active goal, not changes to language expectations.
The registered-body key and Self-environment repairs remain com-6paa.

Old candidate6 checks the new compiler source successfully. New positive controls
cover late carrier owner, same-head distinct declaration construction, missing
nominal non-creation, saved array element type and nested nominal execution.
Fresh candidate, affected old controls, negative/corruption controls, final reader
trace and independent completion review are still required.

### Static Review Corrections in Progress

The first static review of 95032393 does not certify closure. It identified the
actual Record literal producer (not just its ExprType fallback), the ref-less
Array reconstruction through the name-keyed element registry, missing ambient
Array/String, and incomplete bare-cache facet filtering. Those paths are now
migrated in the pending source increment: Record uses fixed Lang terms, missing
String/Array produces a diagnostic before publication, a ref-less array stays
unresolved, and missing implicit async Promise is rejected at declaration
admission and the retained final reader. Registered numeric primitive atoms for
minimal declaration clients remain distinct from ordinary nominal String.

Late zero-arity nominal terms are cached by resolved declaration owner, using
that declaration's canonical spelling; the old raw-name index is only a validated
initial reuse probe. This prevents repeated append after a non-bare first row.
The producer validates actual nominal kind and arity, so an absent owner, plain
trait or missing generic argument vector does not become a closed nominal term.
New controls inspect saved literal owners, trait-only first-cache rows and stable
repeated lookups, missing ambient carriers, annotated result/field/qualifier
absence, and ref-less array input with competing owner/ParamId element rows.
All remain pending fresh execution and independent re-review.
