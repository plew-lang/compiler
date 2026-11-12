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
