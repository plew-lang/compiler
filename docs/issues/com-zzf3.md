---
id: com-zzf3
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

## Concrete witness RHS through an inherited signature

The [com-5wze](com-5wze.md#retained-parent-admission-and-replay) independent
review isolated this consumer. Given `trait Marker { type Type }`,
`trait Parent { type Item }`, and
`trait Middle: Parent + Marker { fn get() -> Item }`, declare
`impl Worker as Parent { type Item = Worker#Marker.Type }` and
`impl Worker as Marker { type Type = I64 }`. A valid
`impl Worker as Middle { fn get() -> I64 { return 42I64 } }` is rejected
at implementation result comparison on both `fefa4c07` and `072faa8a`.
Writing `Marker[Type=I64]` in the Middle declaration is a positive
control, as is writing the literal I64 binding. Include a call through
the inherited signature as well as the existing direct RHS consumers.

## Lowering checkpoint

Both impl adapters attach the original one-based type occurrence directly
to the associated binding. The same binder spelling in different
`Parent[I64]` and `Parent[Bool]` conformances retains distinct occurrence
and impl identities. The internal `associated_binding_rhs_occurrences`
fixture exercises both adapters and verifies the original recipe, scope,
binding slot, and ParamId. Baseline `072faa8a` cannot read the missing
field. The public inherited-signature example still rejects at result
comparison and will verify the selected-output handoff.

The initial build produced a binary but was invalidated by a changed
fixture. With frozen inputs, build `20261112T221428-build-c78f08` passed
and candidate `e5ccdcc1` passed check/native for the new fixture. The
pre-existing standalone `syntax_lower_conformance_bounds` fixture
aborts with the same unwrap error on both candidates, as already
recorded in [com-30u1](com-30u1.md#prepared-trait-headers-for-inherited-names).
Same-source medians were 6.798193 s and 6.831020 s, with identical LLVM
in all eight runs.

Next use the exact binding row and impl scope at declaration admission,
publish the selected proofs for the RHS recipe, and migrate the
concrete and trait-path output consumers to read it through the
selected witness substitution. Distinguish symbolic declaration
interpretation from fully instantiated output and cover absent/foreign
evidence before closure.

## Declaration admission checkpoint

The shared recipe checker now admits each authored conformance binding in
its original implementation scope before callable forms and trait-subject
conferral. The receipt is keyed by binding row and retains the exact
conformance, occurrence, recipe and selected view/projection proofs.
The scope accepts its own conformance conditions and trait subject and
rejects foreign assumptions.

`associated_binding_rhs_requires_conformance` was accepted by `e5ccdcc1`
despite lacking the prerequisite for its unused RHS. Candidate `9fe88cf2`
rejects it at the RHS in check, JIT and native compilation. Adding
`where T: Marker` makes the declaration check and run. Standard build
`20261112T222237-build-9e9a69` and generation
`20261112T222531-gen-c384e9` passed. Same-source medians were
6.834570 s and 6.831517 s, with identical LLVM in all eight runs.

The inherited-signature RED still fails return type comparison. The next
increment must make the selected concrete/trait-path output reader replay
the receipt in its witness environment, including symbolic impl-condition
evidence and guarded recursive RHS reads.

## Selected witness output checkpoint

The output reader now resolves the binding in the selected terminal witness
and reads its admitted recipe under that witness's substitution. Recipe
projections replay their saved proof, including an impl where condition
from the selected witness. The reader verifies the conformance, occurrence,
and recipe identity and detects re-entry for the same binding and
substitution. The raw output term reader still has consumers that require
migration and reconciliation with saved equations.

`associated_binding_inherited_signature` rejects return comparison on
`9fe88cf2` and prints 42 on `c061fc4a`. It and five adjacent public
controls passed check, JIT and native. A conditional generic binding
with RHS `T#Marker.Type` also prints 42. Standard build
`20261112T223041-build-a6eb12` and generation
`20261112T223412-gen-35a687` passed. Same-source medians were 6.814885 s
and 6.817123 s, with identical LLVM in all eight runs.

The nested `Array[T#Marker.Type]` RHS used as a parameter still fails
when an index call checks its saved receiver; the baseline rejected
earlier for a missing lexical parameter dependency. Reconcile the
original and normalized receiver through its saved type and proof.
The existential control with an interface guarantee
`Middle: Parent[Item=I64] + Marker` prints 42. With the interface output
opaque, the dynamic call still rejects its result conversion. Check
the remaining interface, nested RHS, and corrupted-evidence controls
before independent review and closure.

## Nested parameter handoff

The authored parameter `Box[Worker]#Parent.Item` resolves to
`Array[I64]` via a conditional `Parent` witness whose RHS is
`Array[T#Marker.Type]`. Candidate `c061fc4a` selected `Index` on the
resolved array but stored the unreduced parameter as the call receiver.
The declaration boundary rejected those mismatched endpoints.

Lexical recording and verification now read that concrete parameter
from the admitted signature, sharing the RHS derivation used by callers
and executable body signatures. Symbolic templates retain their existing
parameter representation. A broader eager lexical read was discarded
because it changed symbolic terms before instance-specific Mid type facts
were available and regressed existing native and lazy controls.

Candidate `a895020e` passed standard build
`20261112T225153-build-58d36a` and generation
`20261112T225540-gen-8c23a7`. The new
`associated_binding_nested_parameter` and four existing controls
(`associated_binding_inherited_signature`,
`inherited_associated_rhs_equations`,
`concrete_supertrait_projected_signature`,
`conditional_joint_supertrait_projection`) passed check, JIT and
native. Same-source medians were 6.830393 s and 6.835228 s with identical
LLVM in all eight runs.

The original parameter handoff is covered. Reconcile the retained
projection equations with the authored RHS reader and verify the
symbolic/interface and fault cases before closure.

## Immediate equation origin

The immediate output used to establish and validate projection equations
now selects the same witness binding as the normalized output reader. It
reads the original RHS occurrence through its admission receipt, applies
the selected substitution, and leaves RHS projections in the immediate
equation. During declaration admission the immediate reader can inspect
the original source occurrence before its receipt exists. The binding
owner must still match, and the concrete and trait-path cases share the
same selection.

`associated_binding_equation_origin` replaces a binding's source
occurrence with that of a different instance of the same trait with the
same RHS type. The old `a895020e` native executable fails the rejection
assertion. Candidate `fc39f507` rejects the substituted occurrence and
reads the original again after restoration. Standard build
`20261112T230119-build-f27796` passed. Five public controls passed check,
JIT and native. Additional source probes for Unit, a conditional
consumer, a forward reference in a nested RHS, and an inherited
existential with a fixed associated result passed check and JIT.
Same-source medians were 6.892316 s and 6.836507 s with identical LLVM in
all eight runs.

The immediate equation still does not transport nested RHS proofs to
the generic/interface replay that needs them. Continue with that
handoff, the missing/foreign proof and clause controls, and a committed
Unit/interface control before closure.

## Nested receiver proof replay

The binding `Wrap[T#Marker.Type]#Other.Value` needs the result of
`T#Marker.Type` to replay the `Other` witness on `Wrap[I64]`. Candidate
`fc39f507` rejected the retained conformance at the outer projection in
both the lexical parameter and an existential witness. The authored RHS
reader now returns the child equations with its output. Parent recipes
compose those equations and compare the replayed witness bound in the
same normalized context as the authored receiver.

Candidate `a2312c45` passed standard build
`20261112T230744-build-9857d1` and generation
`20261112T231130-gen-50357b`. The nested receiver, existential dispatch
with an interface equality, and explicit Unit output fixtures passed
check, JIT and native, along with five neighboring controls.
Same-source medians were 6.845093 s and 6.864734 s, with identical LLVM
in all eight runs.

The conditional normalization producer and the requirement reader
still have raw term consumers to reconcile. Exercise missing and
foreign proof, clause and normalization failures through final reads
before independent review.

## Conditional normalization from admitted RHS

After declaration admission, condition normalization reads concrete RHS
projections from the selected binding's recipe and publishes those child
equations before the parent projection equation. It applies the selected
binding substitution once. Abstract equalities and initial declaration
admission still use their existing symbolic interpretation.

The nested conditional witness fixture is a behavior-preservation
control and passed on both `a2312c45` and `8047fb30`. The latter also
passed six neighboring fixtures in check, JIT and native, standard
build `20261112T231429-build-9a1255`, and generation
`20261112T231827-gen-a868cc`. Same-source medians were 6.856170 s and
6.902417 s with identical LLVM in all eight runs. The admission path
now reads the binding slot twice for this operation; combine its
immediate and normalized outputs when reconciling the remaining
requirement and equation readers.

The remaining lexical requirement reader starts from the raw RHS and
looks through the witness condition list. Move it to exact occurrence
replay in the requirement's interpretation and exercise corrupt
receipts, proof/clause identity and normalization before review.

## Single selected output read

The signature reader and conditional normalization now obtain the
immediate RHS, normalized RHS and child equations from one selected
binding. Validation of an already stored equation can still read only
the immediate term from the exact occurrence.

Candidate `27421b95` passed standard build
`20261112T232127-build-a2ba0f`, generation
`20261112T232538-gen-c2652a`, and the seven condition, signature,
existential and Unit fixtures in check, JIT and native. The same-source
medians were 6.857562 s and 6.849593 s. The raw LLVM differed. A comparison
of the complete outputs after removing only the embedded TypeTerm number
from generic-body symbol names was identical, including the body IDs
and the calls to those bodies. This does not certify the final fixed point.

The requirement-side interpretation of selected associated clauses
and the remaining evidence fault tests are pending.

## Requirement RHS replay

A conditional witness selected in a requirement now reads its own
authored binding. The RHS projection replays its exact impl condition
and, for a requirement-associated premise, interprets that clause in
the requirement's environment. The old scan through all witness
conditions by projected term is removed. A symbolic result keeps the
selected member on its requirement subject. Interface results also
apply the requirement's lexical substitution to remaining rigid
binders.

Candidate `a828deac` passed build `20261112T233830-build-0fc390`,
generation `20261112T234215-gen-6552a0` and eight check/JIT/native
controls, including the inherited symbolic signature, inherited
interface where clause and nested existential witness. Same-source
medians were 6.856663 s and 6.853942 s. All eight LLVM outputs were
identical. The earlier attempts rejected the symbolic signature or
the interface where clause and were discarded.

Next extend the evidence fault cases to cover a missing RHS receipt,
foreign substitution, and missing or replaced prerequisite or equation
at the output reader. Then review the full guarantee before closing.

## Nominal witness substitution integrity

The native fault control `associated_binding_witness_substitution` on
`a828deac` accepted a witness for `Box[I64]` whose binder mapped to
`Bool`. The normalized RHS reader now checks that the substituted
nominal declaration subject matches the witness receiver, accounting
for the retained equations. The control rejects the foreign and
missing substitutions and reads the original again.

Candidate `c1b0a874` passed standard build
`20261112T234530-build-851176`, generation
`20261112T234931-gen-20402d`, the native fault control, and eight public
controls in check, JIT and native. Same-source medians were 6.891331 s
and 6.882613 s. LLVM differences were confined to the TypeTerm numbers
in generic-body symbol names.

Independent review in progress found additional gaps. A conditional
witness with its condition-plan ID removed can still yield a literal
or binder RHS. An extra witness binder row can disagree with the
canonical substitution. Requirement-associated evidence needs its
replacement proof checked against the retained clause. The task stays
open for these checks and the remaining fault controls.

## Declaration order and independent review

Independent reviewer `zzf3_completion_review` reviewed `5967aa0b`
and the nominal-substitution change. The reviewer identified a
declaration-order dependency, missing or malformed witness condition
plans, surplus binder rows, a requirement proof that could change its
subject after rebasing, ambiguity between absent concrete and valid
abstract output, and a provided-signature route still reading only the
immediate output. The review also called for exact once-only caller
substitution and evidence corruption/restore coverage. Completion is
pending. The nominal subject fix covers the distinct mismatched receiver
case.

The forward-condition fixture reproduced the declaration-order failure
on `c1b0a874`. The first binding requests a later conditional witness
whose associated equality uses a third, later binding. During binding
admission, the comparison now reads the registered immediate equation.
After admission, output consumers require its receipt. Candidate
`45e860c7` passed build `20261112T235211-build-16c253` and the new
fixture plus four controls in check, JIT and native. Same-source
medians were 6.866589 s and 6.867015 s, all eight LLVM outputs identical.

## Conditional witness and binder integrity

The fault fixture now obtains a real conditional witness from an
existential conversion, then removes its plan or child proof and
injects a surplus binder. The RHS is a plain binder, so it exercises
conditions that the RHS itself would not otherwise read. The baseline
`45e860c7` aborts with `accepted a missing witness condition plan`.
Candidate `dde3a784` rejects each corruption and still reads the original.
The retained context checks owner, plan, clause count, and proof
presence. The environment requires exactly one valid binding per slot.
Full premise matching stays with the boundary that owns the lexical
assumptions, rather than recursively calling it from a predicate output
read.

Standard build `20261112T235826-build-280a92` passed. The native fault
fixture and seven public check/JIT/native controls passed. Same-source
medians were 6.876373 s and 6.875553 s, with all eight LLVM outputs
identical. The matching of replacement requirement evidence, missing
concrete versus abstract output, and provided-signature RHS reader are
still pending from independent review.

## Concrete output absence

The native equation-origin fixture now checks three boundaries.
An abstract proof without an equality retains an unknown output, an
optional read for an undeclared member can return no output, and a
selected concrete witness missing its declared binding fails. It
restores the original binding and verifies recovery. The public Unit
fixture separately exercises a bound Unit output.

The baseline `dde3a784` aborts with `accepted a missing concrete
associated binding`. Candidate `97fd3623` rejects the corruption.
The concrete slot reader also rejects duplicate bindings. Standard
build `20261113T000442-build-774f37`, the native fault fixture and six
public check/JIT/native controls passed. Same-source medians were
6.873550 s and 6.870970 s with all eight LLVM outputs identical.

## Requirement clause validation

The requirement's conformance-associated clause reader checks the
stored clause shape, predicate member identities and normalization
proofs before validating the selected proof against the normalized
bound. The bound's subject must agree with the requirement's selected
associated output. Provided source signatures now consume the shared
associated output reader for selected proofs.

Candidate `2ff432b1` passed build `20261113T001036-build-29ae0d`,
generation `20261113T001432-gen-741515` and eleven check/JIT/native
controls. The new provided-signature fixture is a behavior-preservation
control and also passed check and JIT before the change. Same-source
medians were 6.865532 s and 6.856540 s, all eight LLVM outputs identical.

The direct replacement fault for the private conformance clause table
is still unverified. Verify a valid but foreign proof and restore the
original through an internal test without expanding the production
mutation API. Confirm remaining evidence cases and re-review before
closing.

## Full declaration bound validation

The native scratch probe kept the clause and output type fixed while
substituting another subject's valid `Source` proof. `de958158`
accepted the replacement and `93ba3600` rejected it. Both accepted
the original before and after the replacement. No production mutation
API was added.

The independent follow-up review found a second issue. Replacing the
row bound and its proof together from `Entry: Source[I64]` to
`Entry: Source[Bool]` passed `93ba3600` even though both instances
returned the same associated type. The declaration producer, requirement
reader and interface replay now share construction of the complete
pre-normalization bound from the original impl. In the native probe,
`Service.Input: Source[I64]` drives a requirement returning
`Wrapper[Self#Service.Input]#Select.Value`. The producer's selected
row is replaced before publication with the valid extension witness
and bound for `Entry: Source[Bool]`. Candidate `a1fc14fc` reports
`retained associated clause differs from its declared bound` and
accepts the original control before and after the replacement. It also
continues to reject the subject-only proof replacement.

Build `20261113T002212-build-c65a55`, generation
`20261113T002656-gen-ed1b75` and eight public check/JIT/native controls
passed. Same-source medians were 6.855093 s and 6.879164 s, with
identical LLVM output across all eight executions. The broad diagnostic
batch on the prior candidate timed out during a compiler-importing JIT
fixture and is not counted. The review also identified a remaining
case to verify: replacing a clause proof with a same-shaped premise
from an unrelated lexical owner. Final independent review and that
scope check are pending.

## Lexical scope of retained associated clauses

The native scratch control replaces only the saved proof with an
assumption from a free function with the same `Entry: Source` bound.
On `d4ed3dff` the foreign premise passes the reader and reaches its
return. Candidate `752239a5` rejects it at the reader with
`associated binding cannot borrow another declaration premise`.
Both candidates accept the original proof before and after the fault.
The shared reader checks the proof and its normalization dependencies
in the owning impl's declaration scope.

Build `20261113T003036-build-36825e`, generation
`20261113T003441-gen-c00e6a` and eight public check/JIT/native controls
passed. Same-source medians were 6.874314 s and 6.878091 s, with
identical LLVM output across all eight executions.
