---
id: com-3jtd
status: in_progress
deps: [com-v5zn]
links: []
created: 2026-11-09T08:54:16Z
type: task
priority: 1
assignee: Koji Murata
parent: com-amjl
tags: [frontend, generics, verification]
---
# Unify complete-instance admission at remaining type and value view entries

## Guarantee and Finite Work

Close the common source view-formation boundary outside the accepted free-signature receipt gate. Actual type/value entries must pass semantic receiver, canonical trait owner, every positional argument and exact lexical premises into the same source-admission query and retain its selected proof. Inventory these finite adapters before changing them; distinguish confirmed structural gaps from unexecuted source cases.

Remove boundLhsMatches raw-form/lexical-owner shortcuts that discard semantic receiver/ParamId or instance arguments; preserve unique inherited short-form selection and the newtype-underlying full receiver ref in extension recursion. Extension selectors remain distinct from trait selectors. This task owns common formation/applicability and evidence handoff, not each sibling's owner lifecycle or com-4k31 final member dispatch.

## Required Scenarios

- Standalone/projected type and value view; no/unrelated/wrong positional premise, direct/inherited premise, qualified and ambiguous/unique short forms.
- Same-spelled foreign binders, full Array/newtype receiver, inherited extension recursion, mismatched/missing extension and no-view controls.
- Inventory every actual caller and preserve its exact selected-evidence handoff; exercise at least one real production consumer for each changed shared adapter. No alternate unchecked source-success or ambient lookup repair may remain.
- Missing owner/member/arity stays distinct; supported bad source is Source failure, raw malformed input remains typed non-Source; bounded Limit and recovery remain intact.

## Verification and Completion

Follow the parent [contract and closure rules](com-amjl.md#contract-and-closure) and task-start TDD. Confirm the actual old-candidate RED for new behavior, preserve valid controls, then build a fresh candidate and test the real source-to-final-consumer path. Pure refactors use existing GREEN. Record exact inputs/carrier, diagnostic origin, meaningful assertions, applicable modes, removed competing authorities and independent neutral review. Do not close from a table/check/helper-only result. Existing unsupported surfaces must retain their actual diagnostic and be recorded, not silently counted as acceptance.

No new specification or general solver/SCC/unique/opening feature, API-wide authority extraction, main/seed promotion or whole-suite/ASan certification is included. Shared API names alone do not create whole-task prerequisites. Whole-program fixed-point/performance/full-suite gates remain with met-si6j; parent closure still requires the complete original guarantee map.

## Repeated declared supertrait instance

[com-30u1](com-30u1.md#static-requirement-result-checkpoint) found a source
admission regression in `supertrait_projection_instances`. The common
`searchTraitPatternProofFromFacts` collects an inherited candidate before
`assumedTraitInstanceSeen` can coalesce its repeated complete constraint.
This divides equivalence between search and result selection. The repair
must preserve the exact root, positional arguments and associated equations.
Explicit source priority and distinct `impl Trait as Trait` paths retain
their existing behavior. Reuse the raw requirement regression and its
verified fix when auditing the remaining shared view entries. The repair and
both old-candidate regressions are recorded in the
[diamond checkpoint](com-30u1.md#declared-supertrait-diamond-checkpoint).

## Nested projection in a provided receiver

The existing run fixture `provided_signature_nested_receiver_projection`
passes `--check` on `plewc-com-zqqi-receiver-20261112` and rejects at
its provided impl header on `plewc-com-ab7u-final` and `8720f079`,
with the missing exact-instance Source diagnostic. The receiver
uses `Source[Key#Seed[Token#Leaf.Kind].Output]` and the registered
conformance itself uses `Token#Leaf.Kind` as a positional argument.
The common instance-formation audit must cover this declaration case,
preserve the earlier accepted fixture and bisect the first failure.
The reproduced failure predates the local body work in com-yjq0.

The example passes check and JIT with `4fac5791` after
[retained-equation matching](com-yjq0.md#match-a-selector-under-its-retained-equations).
Keep it as a declaration control for the common formation audit.

## Cast-target trait-view formation

Include the `as` target adapter in the existing source-view entry inventory.
The [default-generator review](com-0cwy.md#independent-re-review-and-scope-identity)
reproduced the same rejection at a projected target on baseline and final
carriers. A concrete positional argument passed check but failed lazy Mid
preparation. Compare the cast adapter to the same complete instance written
as a local annotation or direct value view. The issue is in the existing
formation audit; downstream conversion/Mid failures need attribution to
their actual owner after the source admission path is traced.

## Entry inventory and fixed baseline

Baseline `f0ac23c4` uses development candidate `92b3cf006403`.
The authored nominal/signature recipe visitor and Record's value-view
producer use the complete trait query. Verify's type-use compatibility
sweep still has a separate owner/arity head check; its match is not
proof of a complete trait instance. Record and Verify also have distinct
extension formation call sites, both reaching the same name-based
newtype recursion in `extAppliesToType`. The callable source-head collector
has different responsibilities and its remaining dispatch migration is
tracked by com-4k31.

Both ordinary declaration adapters reserve lexical projection clauses
before lowering type consumers. The raw `boundLhsMatches*` fallback
therefore serves the unscoped compatibility calls, including an internal
test that injects arrays into Comp, rather than ordinary declaration
lowering. Compare the adapter through its actual scoped declaration
entry before removing the fallback and stale arrays.

Fixed candidate check/JIT accepts a default-independent value view
`Number#Marker[T#Project.Item]` under `T: Project[Item=I64]` and prints
42. Both stored cast probes still reproduce their original outcomes.
Per spec/09, formation and admissibility of the target type must be
established separately from whether `as` can convert the operand.
The five selected short-projection/provided controls pass check and
JIT. The existing distinct-argument and foreign-receiver controls
reject at short-projection selection.

For `newtype Wrapped = Box[I64]`, standalone `Wrapped#Numbers` and
`wrapped#Numbers` pass on the fixed candidate when Numbers implements
`Box[I64]`. Replacing the underlying with `Box[Bool]` rejects in
both check and JIT. Invoking an inherited extension method through
the valid view passes check but fails in Mid body preparation.
This is tracked separately from merely admitting the extension view.

The recursive extension applicability reader now follows canonical
receiver identity through the checked newtype RHS, with the full type
term passed into the next applicability check. The no-term compatibility
lookup can still identify its existing direct extension control; it no
longer recovers an inherited receiver by spelling. Fixed-input build
`20261113T112303-build-54a05c` produced `9ee2aa877955`. Both newtype
view positives and the projected trait value view passed check, JIT
and native with output 42. Both wrong-underlying forms reject in check
and JIT. Existing conformance-only and stored extension controls pass.
