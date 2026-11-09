---
id: com-amjl
status: in_progress
deps: [com-x95z, com-zdod, com-1hd3, com-erlx, com-zqqi, com-30u1, com-ab7u, com-zzf3, com-yjq0, com-0cwy, com-6p30, com-3jtd, com-1a3k, com-0n6g]
links: [com-oir7, com-8egj, met-c1pg, com-16j0, com-0w38, com-wka4, com-9hde]
created: 2026-11-06T09:51:26Z
type: epic
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, generics, verification]
---
# Complete authored trait-view admission and retained evidence consumers

This epic groups the remaining implementation of the original com-amjl contract.
It remains in progress. Child tasks own finite repairs through their actual final
consumers; the epic owns the original guarantee map and final reconciliation.
Splitting work does not complete a repair, waive a guarantee or certify a suite.
Product work is paused at compiler1841797d; task decomposition does not resume it.

## Contract and Closure

[Spec09](../../../spec/spec/02-type-system/09-extensions.md#拡張ビューと-トレイトビューの非対称混同しやすい)
requires existing conformance before a type or value trait view is formed.
[Spec08](../../../spec/spec/02-type-system/08-traits.md) makes
`T#P[Args].Item` an exact source/instance selection; `T.Item` is shorthand only
when lexical premises uniquely determine the complete instance and member.
An abstract declared premise can justify a symbolic receiver without a concrete
conformer. No implicit bound or new language rule is adopted.

Follow [Types and Evidence](../design/types-and-evidence.md#4-substitution-and-projection),
[Frontend Handoffs](../design/frontend-handoffs.md),
[Generics](../design/generics.md) and [Name Lookup](../design/name-lookup.md).
The original [investigation](../../../evidence/rejection-domains/projection-admission-investigation/README.md)
and [controls](../../../evidence/rejection-domains/projection-admission-investigation/cause-controls.json)
showed signature acceptance with no/unrelated premise and the wrong trait instance.
Free-signature admission repairs do not certify every other source entry.

Every migrated path must close:

`authored occurrence/recipe -> exact lexical owner/premises -> common source
admission -> saved selected proof/equations -> explicit instantiation -> real
signature, operation, projection or interface consumer`.

- Preserve canonical receiver, trait owner and all positional arguments; distinct
  occurrence IDs survive equal semantic terms. ParamId, not spelling, is identity.
  Both TypeAst/TypeId lowering adapters remain applicable.
- Source admission uses the shared conformance/source query, with unique path
  and ambiguity rules; Existence is not source-success authority. Keep member,
  arity, short-form uniqueness, inherited and selected-extension rules.
- Preserve the original scope, clause, complete expected bound, frozen proof and
  normalization context. Saved readers substitute/replay those facts, not a new
  source search through an ambient cursor. Caller replacements and proof outputs
  are not recursively re-substituted through the callee recipe.
- Raw owners, receipts or append-only proof rows do not by themselves confer
  successful source/body admission. Failed scopes and partially retained prefixes
  cannot authorize success. Restore depth/role/cursor/request state on failure.
- Invalid authored views diagnose Source at the selection; malformed internal
  inputs remain typed non-Source failures. Limit is resource exhaustion, not proof
  of invalid source. Preserve the existing bounded request policy.
- Abstract interface output zero can be a valid unknown output, not missing
  derivation or known Unit. Original prerequisites/equations retain scope; direct
  or nested Universal evidence cannot escape through a static adapter.
- Declaration preparation must not eagerly admit unrequested body/default uses.
  Request timing, async call/body results, Unit, evaluation and lifetimes stay
  unchanged. Record actual check/build/lazy/gen callers and applicability; an
  unsupported input or pre-existing gen failure is not a passing target test.

Each child uses task-start TDD, fresh targeted execution and independent neutral
review. A store/check/helper-only increment cannot close a producer-to-consumer
child. Parent closure requires all children closed, a contract-to-result and
actual-caller reconciliation including nested saved evidence/alternate paths,
preservation of the accepted baseline below and correct old fixture oracles.
Reconcile the actual candidate, input hashes and diagnostic grounds; no GREEN or
completion claim follows from task count or review receipt alone.

Final whole-program fixed-point/performance/full-suite/ASan gates remain G2a/G2b
under [met-si6j](met-si6j.md), not repeated as mandatory gates for every child.
Main/seed/carrier promotion is excluded. The current formal median is7.101924s;
7 seconds remains unmet, and repair difficulty has not been established.

## Guarantee Allocation and Execution Order

This is a scope map; tk metadata is the status/dependency authority. All children
are open at decomposition. No completed historical prefix is recast as a new
completed child.

| Child | Finite producer-to-final-consumer guarantee |
| --- | --- |
| [com-1hd3](com-1hd3.md) | Free annotation slots/proofs into actual call and body signatures, including async/Unit representation |
| [com-erlx](com-erlx.md) | Original impl/member owner and clauses prepared once, consumed by short projection/bound/condition readers |
| [com-zqqi](com-zqqi.md) | Registered method annotation admission into selected call/body signatures |
| [com-30u1](com-30u1.md) | Raw trait slot/Self signature through translated/provided/interface signature use |
| [com-ab7u](com-ab7u.md) | Actual extern owner/annotation evidence through foreign-call signatures |
| [com-zzf3](com-zzf3.md) | Associated binding RHS occurrence into the selected witness output and projection/interface use |
| [com-yjq0](com-yjq0.md) | Requested local/closure/provided/deinit body annotations and value views through saved final facts |
| [com-0cwy](com-0cwy.md) | Default argument/field expression evidence through its exact generator and actual use |
| [com-6p30](com-6p30.md) | Global annotation and initializer evidence through exact declaration/request identity |
| [com-0n6g](com-0n6g.md) | Struct-field/enum-payload/newtype RHS annotation evidence through declared-type use |
| [com-3jtd](com-3jtd.md) | Common complete-instance type/value formation, semantic receiver/inherited premise/short-form and newtype receiver preservation |
| [com-1a3k](com-1a3k.md) | Authorized success-fixture correction with original equality/cycle/growth/binder graph oracles intact |

Begin with [com-1hd3](com-1hd3.md); then [com-erlx](com-erlx.md) before its method and associated-RHS consumers.
The latter two have real tk prerequisites on [com-erlx](com-erlx.md). Other rows can progress
independently on the shared admitted contract; this suggested order is not an
invented blanket dependency. Select each task from tk ready/blocked state and
its finite contract. Do not fold siblings into the current task when another
owner is encountered. If a new actual API prerequisite is discovered, record
its concrete handoff before updating dependencies.

Default generators own expressions, while signature/nominal tasks own declared
parameter/field types. Raw requirement/provided/interface signatures belong to
[com-30u1](com-30u1.md); registered implementation method ownership to [com-zqqi](com-zqqi.md);
provided/deinit body-local annotations to [com-yjq0](com-yjq0.md). Common source applicability
belongs to [com-3jtd](com-3jtd.md), while final member dispatch remains com-4k31.

## Existing Owners and Exclusions

Keep original prerequisites com-x95z/com-zdod and downstream consumers
met-ia09/met-6e6k/com-604k and com-4k31 connected to this epic. No blanket wait for
com-9hde, com-4k31, com-yeua/com-fsuq or the separate raw graph repair met-c1pg is
introduced. Coordinate actual shared boundaries without duplicating their work.

API-authority narrowing remains with com-oir7 (view-check inputs), com-nhtx
(callable environment services), com-pmiz/com-j2i7 (output/matching adapters),
com-p5q2/com-4vvt/com-be0m/com-4oor/com-hnm8 and
com-d4m2/com-9nbx/com-nei5. This epic owns semantic admission and retained
handoffs, not their full service extraction. Known Unit/absent and explicit
Self/Item frame contracts coordinate with com-nei5. Narrow inputs touched during
repair where justified; a shared API name is not a whole-task dependency.

Source-operation Building publication is already the distinct com-wqa0 contract.
The earlier attribution of all proof/binding issuance to com-oir7 was incorrect:
immutable allocation can precede a later error without certifying source success.
Conformance associated/method/supertrait rows and callable bindings must be
validated at their actual producers/readers; no new blanket allocator-sealing
project is inferred. Existing row-level malformed-input controls remain useful.

Excluded: new projection/trait-to-trait/unique/opening/typealias features,
implicit conformance, general solver/SCC/layout redesign, unrelated API-wide
narrowing and certifying scope-wide success from finite helper comparisons.

## Accepted Baseline and Evidence

Reuse these finite results with their recorded source/candidate/input limits.
They do not certify all descendants or a fresh aggregate candidate. Implementation
chronology and superseded Next instructions are retained in Git, not an execution
plan embedded in this epic.

| Finite boundary / decision | Canonical saved evidence |
| --- | --- |
| Complete Array receiver query; newtype underlying full-ref migration is still [com-3jtd](com-3jtd.md) | [diagnosis](../../../evidence/rejection-domains/diagnostic-domain-implementation/array-view-receiver-investigation.json), [repair](../../../evidence/rejection-domains/diagnostic-domain-implementation/array-view-receiver-repair.json) |
| Structural normalization oracle and nested conditional controls | [test repair](../../../evidence/rejection-domains/diagnostic-domain-implementation/structural-normalization-test-repair.json), [nested controls](../../../evidence/rejection-domains/diagnostic-domain-implementation/nested-conditional-wrapper-controls.json) |
| Explicit original owner identity/roles and rigid query premises | [provenance](../../../evidence/rejection-domains/diagnostic-domain-implementation/authored-type-provenance-prefix.json), [query](../../../evidence/rejection-domains/diagnostic-domain-implementation/rigid-trait-query-environment.json) |
| Free root admission; production consumer remains [com-1hd3](com-1hd3.md) | [admission](../../../evidence/rejection-domains/diagnostic-domain-implementation/authored-signature-admission.json) |
| Canonical child recipes, original free clause and recursive admission/reader | [recipes](../../../evidence/rejection-domains/diagnostic-domain-implementation/authored-type-recipes.json), [free bounds](../../../evidence/rejection-domains/diagnostic-domain-implementation/authored-free-bound-context.json), [admission](../../../evidence/rejection-domains/diagnostic-domain-implementation/authored-recipe-admission.json), [reader](../../../evidence/rejection-domains/diagnostic-domain-implementation/authored-recursive-reader.json) |
| Exact callable snapshot and conformance clause interpretation | [snapshots](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-callable-bound-snapshots.json), [clauses](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-conformance-clauses.json) |
| Saved predicate/prerequisite/associated context through actual readers | [predicates](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-predicate-normalizations.json), [prerequisites](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-projection-prerequisites.json), [associated clauses](../../../evidence/rejection-domains/diagnostic-domain-implementation/associated-clause-snapshots.json), [equations](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-proof-equation-contexts.json), [associated rows](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-associated-row-reader.json) |
| Interface-failure localization and output-context diagnosis | [localization](../../../evidence/rejection-domains/diagnostic-domain-implementation/interface-admission-localization.json), [context](../../../evidence/rejection-domains/diagnostic-domain-implementation/interface-admission-output-context.json) |
| Retained dependency context and abstract interface scope | [dependency](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-declaration-dependency-context.json), [scope](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-interface-projection-scope.json) |
| Source/interface equations through concrete boxing and final use | [normalizations](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-source-interface-normalizations.json), [formal checkpoint](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-source-interface-self-host.json) |
| Single full-integrity check then scope/pure comparison; no demonstrated speedup | [current finite validation and formal/matched timing](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-single-integrity.json) |

Retain ShortProjectionBoundInstances and MaterializedTypePathControls
shorthand/qualified complete-instance controls, the once-only free-bound controls,
and the source-call predicate-only missing-equation sensitivity. Do not replace
these semantic oracles with unrelated early rejections. The original authorized
fixture details and exact scenarios are owned by [com-1a3k](com-1a3k.md).

## Decomposition Review

Independent contract-first review `amjl_split_review` compared the actual twelve
children and this epic against the full original contract at1841797d. Accepted:
no required guarantee omission, store-only completion boundary, duplicated whole
repair owner or artificial dependency was found. The review's worklog link/Next
instruction corrections were applied. Its optional shared-view clarification was
adopted: inventory every caller's evidence handoff, then execute meaningful
production-consumer controls. Current tk graph has no dependency cycle.

This is documentation/task-scope acceptance only. No product/test inputs were
changed or executed, no implementation child was closed, and no performance or
whole-epic completion was certified.
