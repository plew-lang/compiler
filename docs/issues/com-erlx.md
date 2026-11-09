---
id: com-erlx
status: open
deps: []
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
