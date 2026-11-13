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

The next fixed-input build `20261113T090637-build-82dfed` produced
`c4220a2dae0189776e1498fe2db01aa02d01a4ba960eef0d632188ea22dcfa6b`.
Seven nominal fixtures pass check, JIT and linked native execution.
The previously failing associated-bound case now uses the canonical
newtype declaration offset while type rows are still being resolved.
Independent review identified a regression for a trait instance with
`Self` as a positional argument. The new fixture passes after keeping
the trait being selected out of witness Self while preserving selected
extensions as evidence sources. The extension, rigid generic, and unique
deinit scratch controls still pass JIT.

The follow-up review found that matching a proof handle to its receiver and
trait instance cannot on its own detect replacement of a whole row by a
different authored occurrence. The final receipt needs exact membership
in the slot's recipe and verified projection equations. Also outstanding:
the related but earlier associated-binding RHS `type Item = Wrapped#Marker`
fails before the admission window opens. It reproduces with both direct
and projected underlying types; this is separate from the now passing
`type Item: Marker` requirement. Keep the task open pending those
boundaries, failure-restoration controls and final independent review.

A same-source development comparison on the preceding `6d107091a574`
candidate measured medians 7.151 s (c5146239) and 7.180 s (candidate).
The emitted LLVM hashes matched across all eight runs. This comparison
does not establish formal self-host timing.

## Nominal recipe integrity and associated RHS checkpoint

A scratch compiler based on `b4a21146` replaced two retained proof rows
with copies of the first row. It still accepted the nested
`(first: A#Left, second: B#Right)` field and ran its construction,
printing 42 (fault-injected SHA `fea3705211f2`). With the same
substitution, the updated reader rejects at the second annotation
in check and JIT (fault-injected SHA `4c99c6eb7941`). The plain
candidate walks the original recipe in admission order and verifies
projection equations and their replayed output before consuming the type.

The associated RHS can now request a newtype RHS while associated
bindings are being admitted. The later compatibility sweep recognizes
the exact already-admitted RHS recipe and retains its extension checks.
The end-to-end fixture reads `Provider#Project.Item` and prints 42
through the viewed newtype. Fixed-input build
`20261113T092231-build-772973` produced
`ee112676d216c739efbdfe9f860c73a0a97e31bcf33d7116646a913813b8e1ab`.
Eight positive fixtures passed check, JIT and linked native execution.
Four negative fixtures passed check and lazy diagnostic checks.

The independent review identified a remaining proof-handle check:
matching erased receiver and trait arguments can accept a foreign
witness using a different extension source if the row's own metadata
was preserved. This needs a selected-source comparison at the reader.
The independent review stopped before completing its follow-up.

## Extension witness identity checkpoint

Using the valid enum layout with `Number#First#Marker` and
`Number#Second#Marker`, replacing only the second saved proof handle with
the first still produced 42 before this increment (instrumented SHA
`fd94305cf2d7`). After comparing the full proof receiver, including its
extensions, and the complete trait instance, the identical verification
rejects at the annotation (`a690c7253826`). The uninstrumented
`2b4c8e27e7ae`, built by `20261113T093116-build-2f296a`, passed all nine
nominal run fixtures in check, JIT and linked native modes.

The independent review confirmed the tested repair and identified a
stronger invariant to close. Validating the contents of a witness still
allows a different declaration identity to be paired with the expected
receiver in the same internal row. Retain the exact admitted proof
identity through the reader, including the projection equation that uses
it. Also verify whether semantic field/cast readers are dominated by
checked underlying evidence or still take the raw declaration route.

Fixed-input build `20261113T093925-build-59f683` produced
`139d826ac73629bb53444c4efad14c79b7e737a26d1b202d23d3012b5914f241`.
The nominal reader now checks the source extension of each saved
conformance path edge and requires the projection's retained equation to
use that occurrence's selected proof. All nine nominal positive JIT
fixtures plus the selected-extension, rigid-generic and unique-deinit
controls passed. The additional internal substitutions identified by
review still need direct verification. The proof-count shortcut and the
semantic field/cast readers' raw underlying queries remain open.

Fixed-input build `20261113T094322-build-4b7ee4` produced
`1dd9f553a4b5dde55f32ddce6402f215d690011580d451e44b29b46de380b030`.
All nine positive fixtures passed check, JIT and native. Four negative
fixtures produced their required diagnostics in check and JIT. The source
recipe's expected proof count is recorded at admission independently of
the consumed payload. Semantic field selection/aggregate preparation and
Mid cast instantiation now read the checked newtype RHS. The preliminary
layout helper retains the declaration-shape read required by matching;
the executable consumers use the checked path.

Remaining before closure: exercise missing and mismatched proof handles,
failure restoration and the checked field/cast boundaries, compare
same-source performance on the final candidate, and complete independent
review. Struct/enum declaration `where` is outside supported syntax.

The second independent review reproduced nine positive and four negative
check/JIT outcomes on `1dd9f553` and identified unchecked newtype reads in
struct patterns, cast-literal contextual typing, and zero-slot aggregates.
Fixed-input build `20261113T094959-build-260ff3` produced `138ad47e4bc4`
with the first two readers connected. The newtype literal, forward-view,
projected-underlying view and generic field/payload JIT controls pass.
The manual `NominalTypeUseProvenance.pw` probe passed on `1dd9f553`,
covering value-AST field/payload/newtype provenance, distinct generic
binders and failure-scope restoration for both adapters.

Same-source development medians for `c5146239` and `1dd9f553` were
7.112 s and 7.176 s, with identical LLVM hashes on all runs. This is
not formal self-host timing. The review identified repeated recipe and
projection-equation validation as a bounded performance candidate. The
zero-slot aggregate path, missing-proof substitution controls and final
review remain open.

Fixed-input build `20261113T095340-build-6526be` produced
`8a65d98d5d62b2eb1b67ca148476c2b3d4a43b3092149b71aa68d6a0ca8efa0e`.
Record now selects checked aggregate storage once before the slot loop,
covering zero-slot constructions and eliminating repeated RHS checks
per field in that loop. All nine nominal JIT fixtures and the existing
newtype literal/adapter controls pass on this candidate.
