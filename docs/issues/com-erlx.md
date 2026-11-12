---
id: com-erlx
status: closed
deps: [com-v5zn, com-ffms]
links: []
created: 2026-11-09T08:54:16Z
type: task
priority: 1
assignee: Koji Murata
parent: com-amjl
tags: [frontend, generics, verification]
---
# Prepare impl and member clauses once under their original owners

## Guarantee and Finite Work

Extend the existing free DeclarationBoundContext protocol to original impl/member clauses in both lowering adapters. Preserve actual conformance or separate inherent-impl identity, receiver (nominal or trait subject), impl/member ParamIds, module/extension provenance and canonical clause/argument recipes. Do not invent a function/conformance owner for an inherent impl.

Replace concatenation and repeated unique*ProjectionSourceCore AST lowering with reads of the same prepared clauses by short-projection selection, FuncBound publication and existing condition checking. Complete this clause producer-to-reader slice; method-signature and associated-RHS admission themselves belong to their dependent siblings, not this task.

## Required Scenarios

- Two methods share one original impl clause; member-specific conditions remain distinct, including same-spelled impl/member binders and repeated parameter/result/body/default short uses.
- Both adapters, qualified/later-clause dependencies, legacy rich-field omission, nonmember filtering and canonical argument recipes.
- Missing/foreign/failed owner or clause cannot confer evidence; error/depth/role restoration and existing bounded Limit behavior remain intact.
- Production short-projection/FuncBound/condition readers consume the original clause once, rather than merely testing a new store.

## Verification and Completion

Follow the parent [contract and closure rules](com-amjl.md#contract-and-closure) and task-start TDD. Confirm the actual old-candidate RED for new behavior, preserve valid controls, then build a fresh candidate and test the real source-to-final-consumer path. Pure refactors use existing GREEN. Record exact inputs/carrier, diagnostic origin, meaningful assertions, applicable modes, removed competing authorities and independent neutral review. Do not close from a table/check/helper-only result. Existing unsupported surfaces must retain their actual diagnostic and be recorded, not silently counted as acceptance.

No new specification or general solver/SCC/unique/opening feature, API-wide authority extraction, main/seed promotion or whole-suite/ASan certification is included. Shared API names alone do not create whole-task prerequisites. Whole-program fixed-point/performance/full-suite gates remain with met-si6j; parent closure still requires the complete original guarantee map.

## Checkpoint: exact identity at short projection selection

The work branch contains a candidate, not an accepted repair. A neutral
review found a concrete overlap with [com-3jtd](com-3jtd.md): exact nominal
identity must be available to both the impl clause consumer and common
complete-instance selection before the late nominal-resolution pass.

With two modules that each declare `pub struct Wrap[T] { pub val item:T }`,
an impl containing `where A.Wrap[T]: P` and
`fn accept(value: B.Wrap[T].Item) {}` must reject. The old measured carrier
rejects, whereas the first owner-aware candidate accepts. Replacing `B.Wrap`
with `A.Wrap` gives the positive control, which the old carrier also rejects.
Before declaration resolution, the candidate's term equality compares
unresolved nominal heads by spelling. For the same reason, both binaries
collapse `T:P[A.Wrap], T:P[B.Wrap]` to one instance, and treat `A.Wrap`
and its import alias as distinct instances. The module binding admission
already retains the original declaration identity at this point. Confirm the
shared owner and dependency for using that identity before continuing.

The old candidate independently reproduced repeated impl argument lowering in
both adapters and spelling-based ambiguity between same-spelled impl and
member binders. The first owner-aware build
`20261112T044058-build-eacc2d` passed both adapters for these probes, including
default and body roles, later-clause/nonmember controls, and value-adapter
recovery and legacy omission. It passed check, AOT and lazy execution of
`impl_prepared_projection_conditions`, plus six existing associated-type
runtime controls. Build `20261112T044931-build-390d35` compiled the
separate owned/inherited clause ranges. The latest added late-failure
assertions have not been run.

Review also identified early publication after a later method or conformance
registration fails. Staging those premise rows until their implementation
can publish is within this ticket. Eagerly treating an ordinary bound as a
view source also changes the diagnostic for an unused unknown trait. Keep
ordinary constraint binding distinct from short-projection candidate
filtering. The old compiler's unused unknown-trait acceptance is a
separate admission defect.

## Resumed checkpoint

[com-v5zn](com-v5zn.md) closed the shared nominal identity prerequisite.
The resumed implementation stages authored method bounds until the owning
impl succeeds, and publishes conformance bounds only after registration
checks. Pending subjects use the same admitted nominal identity, with the
qualified later-clause fixture exercising that route. The value recovery
probe reproduced the old failed-prefix leak and now checks both method
and conformance bound publication. The pre-existing low-level duplicate
conformance diagnostic is still unclassified; the probe pins the diagnostic
message and absence of newly published premises.

Build `20261112T102103-build-6c2fe4` succeeded. Candidate `da939fd0`
passed all eight impl provenance scenarios, including qualified later-clause
preparation through the value adapter, eight existing free-bound controls,
and the conditional-conformance check/AOT/lazy control.

Independent re-review confirmed these paths. Failed raw callable and implicit
trait-receiver admission remains with [com-zqqi](com-zqqi.md); no authored
`where` premise from that prefix remains published.

Removing view-source lookup from ordinary clause lowering exposed a missing
admission check. The current candidate accepts an unused free function with
`where T:Unknown`, which both prior fixed candidates rejected. The older
baseline already accepted the corresponding impl forms. See [com-ffms](com-ffms.md)
for the exact differential and the common admission repair. This ticket
remains in progress until ordinary bound admission no longer regresses.

## Outcome

Resolved after [com-ffms](com-ffms.md#outcome), production `57a452a5`.
The exact final carrier `1f9a99d6` passed both lowering adapters, shared
impl versus member clause recipes (including shadowed binders, body,
default and result uses), qualified/later clauses, legacy omission,
nonmember filtering, typed Limit and restored scopes, and failed-prefix
publication controls. The conditional-conformance fixture ran through
check, AOT and lazy execution. Generation and the scoped performance
comparison are recorded in com-ffms. No stage-wide gate or promotion
is claimed by these results.

Independent review reproduced the earlier receiver identity and partial
publication failures and verified the repaired paths. Failed raw callable
and implicit receiver admission is tracked by com-zqqi, raw requirements
by com-30u1, and associated RHS admission by com-zzf3. They use this
prepared-clause producer without reopening its closure.
