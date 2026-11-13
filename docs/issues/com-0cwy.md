---
id: com-0cwy
status: in_progress
deps: []
links: []
created: 2026-11-09T08:54:16Z
type: task
priority: 1
assignee: Koji Murata
parent: com-amjl
tags: [frontend, generics, verification]
---
# Admit default-generator type views in their authored request scope

## Guarantee and Finite Work

Keep default argument and supported field-default expression annotations/value views owned by DefaultGeneratorOrigin (declaration plus exact parameter/field slot). Admit them on their generator request using the original lexical premises, then retain those facts through generated calls and final use.

This owns expressions inside generators, not the declared parameter/field type (owned by signature/nominal siblings). Preserve explicit-arguments-before-defaults evaluation, default lifetime and existing suspend/self-containment rules. Do not eagerly admit defaults during an unused signature check or assign generated helper imports/owners.

## Required Scenarios

- Used versus unused defaults, two slots sharing identical expressions/types, generic defaults and field defaults on supported surface.
- Missing/wrong-instance/foreign owner evidence, generation failure and recovery, and caller versus declaration premise noninterference.
- Actual default helper call and final value/types in check/AOT/lazy, preserving ordering, lifetime and supported gen behavior.
- Missing receipt/proof is rejected at the proper request; no reconstruction by source span or term.

## Verification and Completion

Follow the parent [contract and closure rules](com-amjl.md#contract-and-closure) and task-start TDD. Confirm the actual old-candidate RED for new behavior, preserve valid controls, then build a fresh candidate and test the real source-to-final-consumer path. Pure refactors use existing GREEN. Record exact inputs/carrier, diagnostic origin, meaningful assertions, applicable modes, removed competing authorities and independent neutral review. Do not close from a table/check/helper-only result. Existing unsupported surfaces must retain their actual diagnostic and be recorded, not silently counted as acceptance.

No new specification or general solver/SCC/unique/opening feature, API-wide authority extraction, main/seed promotion or whole-suite/ASan certification is included. Shared API names alone do not create whole-task prerequisites. Whole-program fixed-point/performance/full-suite gates remain with met-si6j; parent closure still requires the complete original guarantee map.

## Default expression source scopes

Carrier `109a757c` rejected both new fixtures at their default
value's exact-instance view. Both the generic parameter default and
the field default supply enough evidence. Lowering had not retained
their ordered view argument recipes for Record.

Give each default expression a separate lowering scope. Its generator
reads that scope through the registered declaration/slot origin.
Parameter defaults reuse the declaring callable's admitted signature
recipes and the generator's lexical constraints. Field defaults retain
the struct's binders without needing an authored callable signature.
Record admits local annotations and ordered view arguments in that
scope, and finalization reads the same receipts.

Fixed-input build `20261113T062358-build-802517` produced `218b2286`.
Both new fixtures pass check, JIT and native, each printing 42. Five
existing default evaluation/field/trait controls pass check and JIT.
A mismatched view instance is rejected in check and JIT. Supplying the
argument explicitly leaves that invalid default unrequested in JIT
(output 13), while whole check still rejects it.

Remaining: exercise slot/owner substitution, missing origins and proof
publication, failure recovery and generation. Confirm scope restoration
and closure/default context isolation in an independent review before
closing the task.
