---
id: com-30u1
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
# Retain trait requirement signature evidence through provided and interface use

## Guarantee and Finite Work

Admit raw trait requirement parameter/result annotations using their canonical trait owner, exact requirement slot, trait binders, full Self instance and declared premises. Do not assign a fake registered Function identity or treat translated implementation Requirement evidence as raw source authority.

Retain the original contract into translated/provided signature and existential/interface consumers, including selected associated constraints and saved normalizations. This owns raw/provided/interface signature handoff; registered impl-method ownership is the method sibling, and annotations inside a requested provided body are the body sibling.

Use the prepared ordinary bound admission contract in [com-ffms](com-ffms.md)
when moving raw signature premises. The legacy raw-signature reader can publish
an unresolved `where` trait and does not restore all lexical state on error.
Any switch to earlier rejection must restore both signature and enclosing trait
frames before returning the original diagnostic.

## Required Scenarios

- Unused requirements, siblings with identical terms, trait Self/inherited premise and full positional trait instance in both adapters.
- Valid provided/interface use and absent/wrong-instance/foreign requirement proof; missing promise never becomes an inferred conformance.
- Exact signature slots survive translation and boxing/dynamic use; static consumers still reject direct or nested Universal evidence.
- Reuse existing interface scope/snapshot/native-lazy controls and add production requirements not covered by them; missing evidence fails without re-query.

## Verification and Completion

Follow the parent [contract and closure rules](com-amjl.md#contract-and-closure) and task-start TDD. Confirm the actual old-candidate RED for new behavior, preserve valid controls, then build a fresh candidate and test the real source-to-final-consumer path. Pure refactors use existing GREEN. Record exact inputs/carrier, diagnostic origin, meaningful assertions, applicable modes, removed competing authorities and independent neutral review. Do not close from a table/check/helper-only result. Existing unsupported surfaces must retain their actual diagnostic and be recorded, not silently counted as acceptance.

No new specification or general solver/SCC/unique/opening feature, API-wide authority extraction, main/seed promotion or whole-suite/ASan certification is included. Shared API names alone do not create whole-task prerequisites. Whole-program fixed-point/performance/full-suite gates remain with met-si6j; parent closure still requires the complete original guarantee map.

## First RED

Candidate `c0b0a04f` accepts
`tests/fixtures/reject/trait_requirement_signature_wrong_instance.pw` in
check, JIT and native compilation. The unused raw requirement projects
`Self#Project[I64].Item`, while its owner only declares `Project[Bool]`.
Changing the projection to `Project[Bool]` passes in all three modes and
serves as the exact-instance control. Preserve the actual raw requirement
owner and diagnose the missing proof at its annotation before publication.

## Prepared where checkpoint

The same old carrier also accepted the unknown trait in
`where_unknown_trait_unused_requirement`. Both raw signature adapters now
reserve and prepare clause heads and types in the original scope, and copy the
prepared bounds into the requirement. Rejection restores the signature and
enclosing trait frames and leaves the trait unpublished. This shared lowering
also serves extern signatures. The extern proof/foreign-call handoff remains
with com-ab7u.

Build `20261112T121127-build-c6f80d`, candidate `55e672a1`, rejects the
unknown head at line 2 in check, JIT and native compilation. Eight internal
controls passed, including both adapters, typed Source rejection, no
partial trait publication and the recovered canonical bound. The
`trait_where`, `trait_where_args` and `trait_method_output_constraint`
controls passed check/JIT/AOT. `interface_boxing_conditions` passed check
and AOT; its JIT run was interrupted and has no result.

The initial wrong-instance RED remains. The next boundary is to bind
authored parameter/result occurrences to the registered requirement
slot and admit them under that slot's own Self instance and prepared
premises, including inherited trait evidence.

## Declaration admission checkpoint

Both adapters now attach the authored result or factory-error occurrence to
the registered trait/requirement slot. The existing parameter occurrences
remain distinct. Common recipe admission uses that slot's lexical Self,
full positional trait instance and own prepared where premises. Its proof
references have a distinct raw-requirement kind with slot-local scope. A
registered function identity or translated implementation premise cannot
authorize a raw requirement. Admitted proofs are retained by source scope.

Build `20261112T122226-build-b03af5`, candidate `8f6e1174`, rejects the
original wrong-instance case and the new sibling-premise case at their
annotations in check, JIT and native compilation. The old `55e672a1`
accepted the sibling case. Exact inherited and own-instance controls pass.
The value adapter control checks the valid inherited instance, distinct
parameter/result occurrences, and the wrong-instance Source diagnostic.
Eight public controls passed check/JIT/AOT, including associated outputs,
existential dispatch, and fallible factories. Standard generation
`20261112T122758-gen-35d5de` passed. Same-source medians were 6.520705 s
and 6.529334 s, three interleaved runs after warmup. LLVM matches when
generated generic body symbol components are normalized by body ID.

Next, make translated and existential signatures consume this retained
source evidence. The raw premise currently requires a translation before
executable replay. Preserve that boundary while replacing the existing
consumer-side re-interpretation of raw signature terms.

## Existential slot handoff checkpoint

Existential signature reads now take the selected trait index and zero-based
requirement slot. The registered slot identifies the original source scope
and requires declaration admission, including reads during initializer
recording before the ordinary declaration sweep. The raw premises remain
declaration-local. Symbolic result typing, body-call closure and witness
planning all use the same slot reader.

The previous candidate `8f6e1174` read the signature after the test removed
the source store. The native regression reached the expected RED panic.
Build `20261112T123438-build-0b0714`, candidate `b9bab949`, now returns
the missing-source diagnostic in the Internal domain. The symbolic and
callable result fixtures passed check and native execution, and the
supertrait projection and qualified associated signature controls also
passed JIT. The source-provenance fixture passed. The interface boxing
conditions control passed check and native execution. Its JIT run hit the
no-progress limit. A traced baseline run continued preparing thousands of
bodies in this compiler-embedding fixture and was cancelled. JIT remains
unverified for this control. Standard generation
`20261112T124022-gen-c7bea3` passed.

Three measured same-source runs per candidate after warmup gave medians of
6.638584 s and 6.607788 s. All eight LLVM outputs had the same SHA-256,
`7c12646aea3190f61446967b33a8e45913a30e856e548b902585f89024f2d2e3`.
This is a same-source comparison, separate from fixed-point certification.

This increment establishes exact ownership at the existential reader. Its
projection substitution and the witness's source result still use the
legacy reifier. Next, interpret the saved occurrence proofs in the selected
interface scope or selected concrete witness, and replace those reads. The
provided-signature consumer also remains open.
