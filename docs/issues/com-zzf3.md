---
id: com-zzf3
status: open
deps: [com-erlx]
links: []
created: 2026-11-09T08:54:16Z
type: task
priority: 1
assignee: Koji Murata
parent: com-amjl
tags: [frontend, generics, verification]
---
# Preserve associated binding occurrences through selected output derivation

## Guarantee and Finite Work

Both impl lowering adapters currently store AssocBinding.ty but drop PType.authoredUse. Retain each binding RHS occurrence/recipe under its original impl owner and binders; admit its views there and preserve its derivation in the selected witness output.

Read the retained RHS through explicit selected substitution and saved equations into real associated projection and interface consumers. Do not reconstruct authority from the type term, mirrored declaration, absent free binder, caller query or unrelated equal output. Reuse existing saved Associated/Receiver/equation mechanisms; API narrowing remains with existing owners.

## Required Scenarios

- Concrete, generic and nested RHS with impl/member conditions; same semantic RHS at distinct occurrences and two different trait instances.
- Actual parameter/result/interface associated output use, including abstract output zero versus absent derivation and known Unit.
- Missing/wrong RHS receipt, binder, clause, proof or normalization rejects without query rescue; valid read recovers and caller substitutions apply once.
- Both adapters and existing associated-row/prerequisite/predicate/dependency controls remain meaningful through final native/lazy use.

## Verification and Completion

Follow the parent [contract and closure rules](com-amjl.md#contract-and-closure) and task-start TDD. Confirm the actual old-candidate RED for new behavior, preserve valid controls, then build a fresh candidate and test the real source-to-final-consumer path. Pure refactors use existing GREEN. Record exact inputs/carrier, diagnostic origin, meaningful assertions, applicable modes, removed competing authorities and independent neutral review. Do not close from a table/check/helper-only result. Existing unsupported surfaces must retain their actual diagnostic and be recorded, not silently counted as acceptance.

No new specification or general solver/SCC/unique/opening feature, API-wide authority extraction, main/seed promotion or whole-suite/ASan certification is included. Shared API names alone do not create whole-task prerequisites. Whole-program fixed-point/performance/full-suite gates remain with met-si6j; parent closure still requires the complete original guarantee map.
