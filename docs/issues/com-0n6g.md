---
id: com-0n6g
status: in_progress
deps: []
links: []
created: 2026-11-09T08:54:17Z
type: task
priority: 1
assignee: Koji Murata
parent: com-amjl
tags: [frontend, generics, verification]
---
# Admit nominal field payload and newtype views through declared type use

## Guarantee and Finite Work

Close supported struct-field, enum-payload and newtype underlying-RHS type annotations under their actual nominal declaration owner and binders. Lower/Decl lowerType/lowerSyntaxType currently publish FieldDef.ty; Lower/TopLevel has both newtype adapters. Retain exact authored annotation recipes/proofs instead of relying only on the later all-types verifier.

Connect admitted facts to actual field/payload/underlying type consumption and selected instance layout/type use, keeping semantic evidence separate from layout. Field-default expressions belong to the default sibling; newtype extension-recursion receiver preservation belongs to the shared-view sibling. No typealias feature, recursive-layout redesign or new syntax is included.

## Required Scenarios

- Unused and instantiated struct fields, enum payloads and supported newtype RHS, nested constructor/view arguments and exact nominal binders in both adapters.
- Missing/unrelated/wrong-instance/foreign nominal proof, repeated identical terms, generated nominal declarations and restoration on failure.
- Declaration success and real field/payload/newtype use retain the same evidence; missing saved facts do not use a later global type scan/query to recover authority.
- Existing layout/newtype semantics, supported check/build/lazy/gen demand timing and unrelated field defaults remain unchanged.

## Verification and Completion

Follow the parent [contract and closure rules](com-amjl.md#contract-and-closure) and task-start TDD. Confirm the actual old-candidate RED for new behavior, preserve valid controls, then build a fresh candidate and test the real source-to-final-consumer path. Pure refactors use existing GREEN. Record exact inputs/carrier, diagnostic origin, meaningful assertions, applicable modes, removed competing authorities and independent neutral review. Do not close from a table/check/helper-only result. Existing unsupported surfaces must retain their actual diagnostic and be recorded, not silently counted as acceptance.

No new specification or general solver/SCC/unique/opening feature, API-wide authority extraction, main/seed promotion or whole-suite/ASan certification is included. Shared API names alone do not create whole-task prerequisites. Whole-program fixed-point/performance/full-suite gates remain with met-si6j; parent closure still requires the complete original guarantee map.

## Fixed-candidate regression boundary

At `c5146239` the three unused `nominal_*_wrong_view_instance`
declarations all pass check and JIT. Their written argument projects
to Bool, and Number has only Marker[I64]. Declaration admission must
reject each at the annotation. The corresponding valid field and
enum payload constructions print 42 in JIT, supplying controls for
the existing layout and dispatch.

`nominal_newtype_projected_underlying_view` is the concrete final-use
RED. Its RHS selects Marker[I64] through a concrete associated
projection, and check accepts it. Both native object generation and
JIT fail with "destruction underlying type is not closed". Retain
the exact RHS recipe and use its resolved type in inherited behavior,
layout and destruction.
