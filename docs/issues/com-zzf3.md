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
