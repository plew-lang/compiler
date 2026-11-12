---
id: com-zqqi
status: in_progress
deps: [com-erlx]
links: []
created: 2026-11-09T08:54:16Z
type: task
priority: 1
assignee: Koji Murata
parent: com-amjl
tags: [frontend, generics, verification]
---
# Admit method signatures through their selected call and body consumers

## Guarantee and Finite Work

Connect registered inherent/trait-impl method parameter/result annotation occurrences to common lexical admission and retained signature consumption. Bind exact registered method, originating impl/member premises, Self receiver and any extension source; preserve authored Self independently from public/provided placement.

Carry those facts into selected method-call types and actual BodySignature publication, rejecting missing justification before source declaration success. Raw trait requirement/translated provided-signature handoff belongs to the requirement sibling; body-local annotations belong to the body sibling. Do not duplicate com-4k31 candidate/path dispatch selection or API authority-narrowing repairs.

The [com-erlx re-review](com-erlx.md#resumed-checkpoint) found that a failed
parent can retain raw registered callable rows after a successful earlier
member. Check the existing missing/failed-owner admission guarantee against
that prefix, including the implicit trait-receiver premise. Authored where
premises are staged by com-erlx.

## Required Scenarios

- Unused and instantiated inherent/trait methods; direct/inherited/selected-extension premise and missing/unrelated/wrong-instance premise.
- Receiver/Self, same-spelled foreign binders and impl/member conditions remain exact through parameter/result/BodySignature consumption.
- Missing retained evidence cannot be repaired by ambient body state; actual native/lazy calls agree with saved types and preserve passing modes.
- Default helpers and async/Unit representations remain noninterfering; both adapters and error recovery are covered.

## Verification and Completion

Follow the parent [contract and closure rules](com-amjl.md#contract-and-closure) and task-start TDD. Confirm the actual old-candidate RED for new behavior, preserve valid controls, then build a fresh candidate and test the real source-to-final-consumer path. Pure refactors use existing GREEN. Record exact inputs/carrier, diagnostic origin, meaningful assertions, applicable modes, removed competing authorities and independent neutral review. Do not close from a table/check/helper-only result. Existing unsupported surfaces must retain their actual diagnostic and be recorded, not silently counted as acceptance.

No new specification or general solver/SCC/unique/opening feature, API-wide authority extraction, main/seed promotion or whole-suite/ASan certification is included. Shared API names alone do not create whole-task prerequisites. Whole-program fixed-point/performance/full-suite gates remain with met-si6j; parent closure still requires the complete original guarantee map.

## First RED

On candidate `1f9a99d6`, the new
`method_signature_unproved_trait_projection` is incorrectly accepted by
`--check`: the unused method's `T#Project.Item` has only an unrelated Marker
premise. Adding the direct Project premise passes; expressing the same
invalid signature as a free function rejects at the projection with the
expected source diagnostic. This confirms the existing admission rule can
be reused and the method path is missing the handoff.
