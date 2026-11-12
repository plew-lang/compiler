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
