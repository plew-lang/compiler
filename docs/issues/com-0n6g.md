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

## Declaration and final-use checkpoint

Product increment `0fd73c12`, fixed-input build
`20261113T082820-build-a43f50`, candidate SHA `5ff5ed07551a501ecd258a5eebd9078a71c1e7bd3a72cf66e18f8cf7c631ed65`.
The three declaration rejections identify the exact trait instance at
line 8. The projected newtype view (including inherited method execution),
the projected newtype base, and generic struct construction/enum matching
pass check, JIT and linked native execution. Field defaults and the
existing newtype adapter fixture pass JIT. The newtype adapter uses the
stored viewed underlying for selection and the selected callable's own
receiver surface for execution.

Independent review reproduced missing receipt checks at newtype final
readers and at enum conversion, and identified that a same-owner sibling
slot's occurrence could be substituted. Closed fields also need evidence
for the admitted recipe, including nested views, even when their normalized
type is already closed. The review independently ran the newtype JIT
controls and a nested generated record layout. Generated source parts
retain the existing prohibition on nominal top-level declarations. The
value-AST compatibility adapter still needs direct coverage.

The review also reproduced a forward-reference admission gap on both
baseline and candidate: if a projected newtype's underlying conforms to
`Marker`, declaring a field `Wrapped#Marker` requires the underlying to
have been admitted already. Forward newtype-to-newtype views need the
same dependency. An associated-binding conformance bound using that
projected newtype can be reached even earlier in declaration preparation.
Keep these examples as ordering probes. The baseline also accepts a bare
source cast to a viewed newtype in check before failing Mid preparation;
the passing regression uses the exact viewed source cast.

Build `20261113T083350-build-52e21e` produced `db491d28559e`.
The newtype-first admission order fixes the field-through-projected-newtype
probe in JIT. The earlier three run fixtures, generic field defaults and
the inherited newtype adapter also pass JIT. Final newtype body and
destruction preparation now check the receipt, enum repacking reads the
same selected slot as construction, and admission and selection compare
the annotation source site as well as occurrence ID and owner. Arbitrary
forward newtype dependencies, closed nested proof coverage, fault
injection and the value-AST control remain open.

Fixed-input build `20261113T084222-build-6afca4` produced `7b74205e6e76`;
the four nominal run fixtures and the generic-default and adapter controls
pass JIT. The nominal receipt now records the required number of proof
rows and checks their stored handles for a closed output. The value-AST
scratch control ran `lowerTopItem` for a generic structure, generic enum
and newtype and verified distinct recorded occurrences and scope restoration
on success. Receipt substitution, lowering-failure restoration and forward
newtype admission still require final verification. An earlier build was
excluded because the scratch test file changed during validation. The
fixed-input rerun produced the same binary.

## Forward newtype dependency checkpoint

The conformance physical-subject traversal now requests each newtype's
authored RHS while declaration admission is open. A completed dependency
is reused, and re-entering an active declaration reports a source cycle.
The explicit declaration pass seals this window before checking field and
payload annotations. Fixed-input build `20261113T085340-build-13a447`
produced `6d107091a5741a4289dfce4ba7cd0041a21a91fe2bd1e93d8c4d5fa1c4f10840`.
Five positive fixtures pass check, JIT and linked native execution, and
all four rejection fixtures report the intended diagnostic in check and
lazy run. The forward-view regression prints 42; its paired cyclic view
is rejected.

The associated-bound probe still rejects `type Item = Wrapped` with
"associated type does not satisfy its declared trait constraint" in
both check and run. This occurs with both a projected RHS and a direct
`newtype Wrapped = Number`, even though using `Number` directly passes.
The direct newtype also fails on the original carrier. The nominal
forward-reference fix alone does not repair the inherited-conformance
query used by associated bounds. Exact failure origin and responsibility
still need to be established. Receipt corruption and restoration-on-error
probes remain to be completed before closing this task.
