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

## Existential signature replay checkpoint

The public signature and the source result used by its witness adapter now
read the admitted requirement's parameter and result occurrences. They fold
the same canonical recipes as registered callable signatures. For projections
on the interface's Self, the reader follows the exact saved supertrait clauses
and substitutes the selected positional and associated bindings. It keeps
unresolved output terms symbolic and does not use the interface substitution
as static conformance evidence.

The symbolic-result fixture replaces the published raw row with a sibling
after declaration admission. Old candidate `b9bab949` then returns the
sibling's result and reaches the RED assertion. Build
`20261112T125549-build-5a6381`, candidate `f7f918e2`, returns the admitted
result. Both internal existential signature fixtures, inherited projection
and qualified associated signatures passed check and native execution. The
two public projection controls also passed JIT. Conditional boxing passed
native execution. The intermediate recipe reader also passed 13 existing
registered-signature assertions. Standard generation
`20261112T125838-gen-059d3f` passed. Same-source medians after warmup
were 6.641706 s and 6.630960 s across three interleaved samples each. All
eight LLVM outputs matched. This comparison does not establish a new
formal fixed point.

Requirement candidate ranking and hidden-Self availability still read the
legacy parameter terms before selecting the operation. Move those parameter
reads to the admitted recipe before migrating the translated/provided static
signature and its retained clause evidence.

## Existential argument selection checkpoint

Candidate ranking, hidden-Self availability, the final dynamic signature,
and the adapter now share the admitted requirement parameter reader. Name and
label collection still happens at the existing source selection boundary.
The existing candidate-local type matcher compares the instantiated parameter
terms and retains its usual ranking and generic-inference behavior.

Old candidate `f7f918e2` reached both RED assertions in the native
symbolic-result fixture: a candidate ranked without its source signature,
and replacing a raw row made a requirement with a hidden Self input callable.
Build `20261112T130337-build-7dc5ff`, candidate `f52a35b6`, passes both
regressions. The symbolic and callable result fixtures, inherited projection,
and qualified associated signature passed check and native execution. The
two public projection controls also passed JIT. Six other public controls
passed check and JIT, including existential overload selection, iteration,
and conditional member guarantees. The four rejection controls preserve
their diagnostics in eager modes, including nested Self and the prohibition
on using existential dispatch evidence as static conformance. The invoked
nested-Self and static-evidence controls reject in JIT too. The two
unrequested-body controls are accepted by lazy run in both candidates.
Generation `20261112T130650-gen-1b56df` passed. Three interleaved measured
runs per candidate after warmup gave same-source medians of 6.666492 s and
6.686778 s. All eight LLVM outputs were identical. This is a diagnostic
comparison, separate from a formal fixed-point result.

Next, retain the requirement slot and authored term at static source
signature consumers, then translate its raw Self and clause premises through
the selected bound or implementation plan. Keep ordinary provided method
and concrete executable environments separate from the public interface
interpretation.

## Static requirement result checkpoint

The static source result reader now consumes the admitted result occurrence
for the selected requirement slot. It uses the selected bound's associated
equations and can read a direct associated output from a selected concrete
witness. Interface-root evidence cannot authorize the static reader. The
fallible factory result preserves the nominal wrapper resolved at declaration
time while substituting its receiver and authored error type.

The native symbolic-result fixture replaces the raw static requirement row
with a sibling after admission. Candidate `f52a35b6` reaches the expected RED
assertion. Build `20261112T131552-build-dc7625`, candidate `03fc0e86`,
preserves the admitted result. Thirteen public static and mixed controls
passed check/JIT/native execution, including associated outputs, inherited
Unit, iteration, overloads and both fallible factory forms. Four existential
controls passed check/native, with JIT passing on the two public controls.
Standard generation `20261112T131838-gen-3fcc6b` passed. Same-source
medians were 6.962234 s and 6.950459 s across three interleaved runs each
after warmup. All eight LLVM outputs matched after normalizing the generated
generic body symbol component by its body ID. This was a diagnostic
comparison, not a fixed-point certification.

The existing `supertrait_projection_instances` success fixture is a
remaining raw-admission regression. It passes candidate `55e672a1` and
rejects at its first qualified result on `8f6e1174`, `f52a35b6` and
`03fc0e86`. The source-admission collector considers a repeated inherited
state before the traversal deduplicates its full associated constraint.
The fixture covers the same declared parent instance and equality reached
through a diamond as well as a second positional instance. Repair the shared
source admission in this regression scope, with the query's separate
trait-subject paths and selected source priority protected. See
[shared view admission](com-3jtd.md#repeated-declared-supertrait-instance).

Static parameters, call-specific where premises, provided source results
and executable witness translation remain open.

## Declared-supertrait diamond checkpoint

One search admission now controls both inherited candidate collection and
worklist expansion. Two declared-supertrait paths are equivalent here when
they start from the same authored premise, have the same subject and complete
trait constraint, and agree on whether they match the active source selector.
The chosen representative retains its original path. Trait-subject witness
edges stay outside this equivalence.

Candidate `03fc0e86` rejects `supertrait_projection_instances` in check,
JIT and native compilation. The added case in `retained_supertrait_evidence`
queries both explicitly preferred branches beyond a convergence point. It
reaches the intended panic with the baseline compiler source in an isolated
copy, and passes against the repaired source. The new conflicting-equalities
fixture preserves the existing ambiguity diagnostic.

Build `20261112T132326-build-6f3910`, candidate `d600caa4`, passes the
diamond regression and five public controls in check, JIT and native
execution. Seven rejection controls preserve their expected diagnostics in
all three modes, including the conflicting equality, wrong positional
instance and ambiguous trait-subject paths. Standard generation
`20261112T132645-gen-671bf3` passed. The associated static selection
control `trait_subject_associated_paths` still reproduces the pre-existing
failure tracked by [com-9clj](com-9clj.md#reopened-current-source-regression-controls).

A disk-full comparison produced empty LLVM files despite successful exit,
reproducing [com-x386](com-x386.md#additional-capacity-associated-observation).
That run is invalid. A repeat drained LLVM to memory and verified nonempty
output. After warmup, the same-source medians of three alternating samples
were 6.490329 s and 6.485967 s. All eight outputs were exactly 67,780,020
bytes and shared SHA-256
`9721d3d9e89189bbef31aa9a7227db7099c5fe1648ff43b6396358f1cdc496a1`.

Next, move the static requirement parameter consumers to the admitted
signature and then translate its clause evidence into the selected
implementation. The view-adapter work in [com-3jtd](com-3jtd.md) can reuse
this query fix.

## Static requirement parameter checkpoint

Static overload ranking, argument context and method type-argument inference
now read the exact admitted parameter slots using the selected static
conformance. Source checking of recorded static and existential calls also
uses those slot terms. It uses the existing argument matcher and keeps
method-binder substitution separate from trait-instance substitution.
Provided methods still use their own source signature path.

The native symbolic-result regression also replaces the parameter row with
a sibling after admission. Candidate `d600caa4` reaches the intended RED
assertion. Initial build `20261112T133654-build-647852`, candidate
`c3b4a55e`, preserves the original parameter and result. In the initial
same-source comparison the candidate median was 6.553251 s versus 6.518940 s
for the baseline, with all eight LLVM outputs identical. The selected
generic call now reuses one validated signature context for reading the
result and inferring the method arguments. Rebuilt as
`20261112T134249-build-705f7d`, candidate `cd17a8c5`. On that candidate,
fourteen public static/mixed controls passed check/JIT/native. Four
additional signature fixtures passed check/native, with JIT passing for
the two public fixtures. The nested Self and static-evidence negative
controls preserved their expected diagnostics. Generation
`20261112T134533-gen-07861c` passed. A fresh three-way same-source run
gave medians of 6.558847 s (baseline), 6.587564 s (initial), and
6.601308 s (context reuse). The structural cleanup removes a repeated
proof-context check but did not show a timing improvement. All twelve
LLVM outputs were byte-identical. This is a diagnostic comparison,
separate from formal fixed-point certification.

Next, retain the authored clause terms and map each raw requirement premise
through the selected caller and implementation evidence. Provided-method
source signature lookup and final witness translation remain open.

## Requirement clause replay checkpoint

Both lowering adapters retain the subject, positional argument, and associated
equality recipes of each prepared requirement clause. Declaration admission
checks the exact source scope and clause identity before recording the
premise. Static source calls and the existential interface interpret those
same recipes with their own explicit substitutions. Implementation admission
uses the same saved clause with the checked method alpha map, validates the
public evidence, and applies the existing requirement-to-implementation proof
derivation.

The source-reader regression in `existential_symbolic_result` and the
implementation-reader regression in `retained_requirement_body_constraints`
both mutate the raw clause row after admission. Baseline `cd17a8c5` reaches
the intended assertion in each, with its original compiler source frozen.
Build `20261112T135636-build-2a655d`, candidate `2fbe0dd9`, preserves the
retained clause in both cases. The implementation fixture also exercises
reordered bounds, weaker bounds, an empty public clause list, and a
trait-subject witness. Fourteen public static/mixed controls passed
check/JIT/native, the signature group passed check/native and the two public
JIT controls, and the existential condition and rejection controls passed.
Generation `20261112T140029-gen-99bf5a` passed. In three interleaved
same-source runs per candidate after warmup, medians were 6.597499 s and
6.640045 s. All eight LLVM outputs were byte-identical. This diagnostic
comparison does not establish a new formal fixed point.

The older internal fixture `source_call_constraint_evidence` separately
fails in the baseline's ordinary free-call lane on its injected Missing proof
diagnostic. It did not reach this increment's trait requirement boundary.
The observation is recorded with [com-qb05](com-qb05.md#missing-proof-control-diagnostic).

Next, migrate the provided source signature consumers and audit the remaining
inherited and associated proof interpretations through final publication.

## Provided source signature checkpoint

Source result inference, call recording and selected argument validation now
read the provided declaration's admitted signature slots. The source reader
substitutes the selected receiver and its exact trait instance into the
declaration's own receiver premise. Open associated outputs can remain
symbolic. The concrete body reader still requires instantiated proof.
The candidate-rank path and the remaining inherited/associated proof replay
audit are open.

The internal test in `existential_symbolic_result` first reads `Item=Bool`
through an assumed bound, then removes the authored signature store. The
`2fbe0dd9` carrier's native fixture reached the assertion “read a provided
result without its source signature”. The fresh carrier returned an Internal
diagnostic and the full fixture passed.

Build `20261112T141347-build-d56e61`, candidate `7248fd5d`. Check passed for the
provided and trait-method fixture groups. Ten focused controls passed check and
native execution. Nine of those public controls also passed JIT, including
generic trait paths with and without an extension view, nested associated
types, a foreign receiver's projection, and contextual result inference.
Standard generation run `20261112T141802-gen-290bbd` passed. On identical
compiler source the old/new median was 6.646001/6.595748 seconds, with the same
68,047,127-byte LLVM output in all eight runs. This comparison is separate from
the integration fixed-point gate.

## Provided candidate parameter checkpoint

Tentative provided-member ranking uses admitted parameter slots with only
the candidate receiver substitution. Method inference still belongs to the
shared argument matcher. A hole preserves the lexical binder. Ranking and
result inference request only the signature slots they use. Source type
reads do not construct executable body signatures.

The internal `existential_symbolic_result` control selects a valid candidate
before removing the source signature store. Candidate `7248fd5d` still
ranked that member after removal, reaching the expected RED assertion.
Build `20261112T142147-build-01dc71`, candidate `449c7555`, passes that control
in check and native execution. All 29 provided and trait-method fixtures
passed check. Fourteen focused fixtures passed check/native, with the 13
public fixtures also passing JIT. Standard generation
`20261112T142552-gen-8cd3e8` passed. The `2fbe0dd9` and `449c7555` carriers
compiled identical source at medians of 6.641948 s and 6.588426 s with
byte-identical LLVM across all eight runs.

The inherited associated-equation audit has a public regression to
resolve: `supertrait_projection_sibling` is rejected by both candidates
in check and JIT as an unsupported existential result conversion. Its
selected `Second.Item` equation refers to the independently inherited
`First.Item=I64`. Separately, the internal
`inherited_projection_identity` panics in native execution under both
candidates. Its setup declares a requirement against an unavailable
`Parent[String]` instance and unwraps declaration analysis. Keep that
test's wrong-instance comparison at the internal boundary; declaration
rejection already has dedicated coverage.
