---
id: com-0cwy
status: closed
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

## Validate generator selection and inherited recipes

Independent review found a regression in impl-bound shorthand and a gap
in validating a selected generator against the requested declaration
slot. `6c7b2b8e` checks both directions of the slot relation and lets
the default scope use its declaring method's prepared impl bounds.
The native fault probes show that a valid same-typed generator for a
different parameter or field is rejected as Internal. Retrying the
failed request preserves its diagnostic and the caller cursor.

A second review found that the inherited trait's positional argument
recipe also needs the method's admitted parent context. `e834d530`
reuses the saved method metadata for that child recipe and identifies
generator bodies independently of their origin table. Build
`20261113T064138-build-a460a4` produced `ebacc84b`; the parameterized
`default_method_inherited_short_projection` fixture passes check, JIT
and native. The old candidate `972d2df6` rejected the foreign occurrence.
The direct generator request now rejects a deleted origin as Internal
and the neighboring request succeeds. Generation
`20261113T064452-gen-88e518` passes with fixed inputs.

Same-source development medians for `109a757c` and `972d2df6` were
7.996 s and 7.826 s, with identical LLVM across all eight runs. An earlier
comparison overlapped a source change and is excluded. A generation
run for `972d2df6` also detected changed inputs and is superseded by the
fixed-input run above.

## Verify retained local annotations and view arguments

`46d41cfd` attaches the authored occurrence to the lowered local
declaration. Record, compatibility checking and Mono consume that
identity. Inferred locals, generated locals and declarations with a
separate owner have no body annotation. Removing the old statement-ID
dictionary removes the fallback caused by loss of its entry.

The fixed-input build `20261113T065214-build-77d487` produced `03c05701`.
All three projection fixtures pass check, JIT and native with output
42. Typed loop, ordinary local projection and interpolation controls
also pass. A native probe accepted the missing authored occurrence on
`e834d530`; invalidating the ID while preserving the authored variant on
`46d41cfd` returns Internal twice, preserves the caller cursor, publishes
no facts and leaves the sibling inferred local request usable. Separate
faults remove a view's authored arguments, its saved argument receipts,
and a saved annotation proof. All three report their missing evidence;
the intact control prints 42. A real derive harness using two defaults
emits a method returning 4243.

Alternating three timed same-source runs after warm-up, `ebacc84b` and
`03c05701` took median 7.787 s and 7.790 s. All eight runs emitted the
same 73,111,576 bytes of LLVM IR (SHA-256 `2a380a2d7db8`). This is a
development comparison, with the formal fixed point and performance
gate owned by met-si6j.

## Independent re-review and scope identity

The independent reviewer reran projected defaults, order and lifetime
controls, and proved that a caller-only generic premise cannot admit a
default in the declaration. The reviewer traced the zero-argument
generator call into the original callable in emitted LLVM and ran a
native derive harness that consumes an omitted default. Old carrier
`109a757c` rejects the derive input in the default; `03c05701` emits
the expected output.

Review also found that a literal default's lookup could accept the
sibling's completed scope. `da15170d` validates the root expression
origin, kind, and completion state at lookup, including when the
default has no type occurrences. The same native probe rejects on
first request and retry and leaves the sibling usable. The review of
this patch found no remaining blocker.

Candidate `f14e6539` passed fixed-input build
`20261113T070303-build-9b143a` and generation
`20261113T070617-gen-5ddf98`, the three check/JIT/native regression
fixtures, the caller-premise rejection, the derive harness, and all 47
lazy CLI cases. Fault
inputs, patches and commands are in the
[default-expression evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/default-expression-view-origins/README.md).

The reviewer found an existing cast-target limitation on both old and
new carriers. A projected trait view in an `as` target reports the
exact-instance diagnostic. A concrete cast target passes check but
fails Mid preparation under JIT. The cast-target formation path belongs
to the remaining shared type/value entry inventory in
[com-3jtd](com-3jtd.md); these cases are recorded as unsupported, not
as passing default-view tests.

The final scope check comparison alternated the same compiler source
on `03c05701` and `f14e6539`, with one warm-up and three timed runs per
carrier. Medians were 7.093 s and 7.135 s, with overlapping ranges and
identical LLVM IR in all eight runs (SHA-256 `9e1a28326d4a`). These
measurements compare the local increment only.

Resolved at product revision `da15170d`; the independent reviewer found
no further issue in the supported paths after the scope-origin fix.
