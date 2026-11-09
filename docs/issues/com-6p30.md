---
id: com-6p30
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
# Retain global annotation and initializer view evidence by declaration

## Guarantee and Finite Work

Admit supported global type annotations at declaration preparation and initializer-owned annotations/value views at the existing initializer request boundary. Retain exact global declaration identity and its lexical evidence into saved initializer facts and final use.

A canonical no-function initializer scope is legitimate but is not authority for every global sharing a synthetic function sentinel. Preserve existing initialization dependency/order rules and lazy/whole-check behavior; do not add a new initialization model. Nominal field/payload types and defaults remain separate.

## Required Scenarios

- Two globals with identical terms but different origins, ordinary and nested viewed types, missing/wrong-instance evidence and source-site diagnostic.
- Valid no-function empty premise scope, foreign body/initializer evidence refusal, failure restoration and no double initializer evaluation.
- Requested versus whole-check initializer behavior and actual saved global/type/operation consumers in build/native/lazy.
- Missing saved initializer facts cannot become success through a shared sentinel, cache or ambient declaration.

## Verification and Completion

Follow the parent [contract and closure rules](com-amjl.md#contract-and-closure) and task-start TDD. Confirm the actual old-candidate RED for new behavior, preserve valid controls, then build a fresh candidate and test the real source-to-final-consumer path. Pure refactors use existing GREEN. Record exact inputs/carrier, diagnostic origin, meaningful assertions, applicable modes, removed competing authorities and independent neutral review. Do not close from a table/check/helper-only result. Existing unsupported surfaces must retain their actual diagnostic and be recorded, not silently counted as acceptance.

No new specification or general solver/SCC/unique/opening feature, API-wide authority extraction, main/seed promotion or whole-suite/ASan certification is included. Shared API names alone do not create whole-task prerequisites. Whole-program fixed-point/performance/full-suite gates remain with met-si6j; parent closure still requires the complete original guarantee map.
