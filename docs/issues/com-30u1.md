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

## Inherited signature equation checkpoint

The signature fold follows its admitted supertrait path with the same
bound interpretation as ordinary inherited evidence. Each selected edge
interprets the arguments and equations guaranteed by its declaring bound.
In particular, the existing public fixture now carries
`Second.Item = First.Item = I64` through interface signature preparation
and the actual dynamic adapter. No conformance candidate is selected again.

Baseline `449c7555` rejects `supertrait_projection_sibling` in check, JIT
and native compilation. Build `20261112T143017-build-fb2260`, candidate
`9728ec46`, passes all three and prints `42`. Eleven focused fixtures
passed check/native, including the corrected internal identity control;
the nine public fixtures passed JIT too. The internal fixture now feeds a
wrong positional instance directly into the comparison API and retains the
foreign receiver, conflict and known Unit checks. Four rejection fixtures
matched their diagnostics across check/JIT/native. Generation
`20261112T143334-gen-787089` passed. Same-source comparison against
`2fbe0dd9` measured 6.644004 s versus 6.647012 s; LLVM was byte-identical
across all eight runs.

Before closing, trace the remaining associated constraint paths through
final witness preparation and check which legacy reads of provided callable
bounds still interpret raw rows. Reconcile the results with the required
scenarios and obtain an independent completion review.

## Provided source clause replay checkpoint

For static calls to provided methods, the declaration row identifies the
authored clause. Its subject, positional arguments and associated equations
come from the prepared source recipes. Method-local and impl-level clauses
share the same interpretation as retained requirement clauses. Impl-level
recipes are admitted under their original parent scope before replay.

The internal `existential_symbolic_result` fixture substitutes a foreign
subject in the registered `FuncBound` after declaration admission.
Candidate `9728ec46` reaches the expected assertion, “raw where row replaced
the retained provided clause”. Candidate `9b8c7ea5` preserves the prepared
subject. Standard build `20261112T143932-build-202bb3` and generation
`20261112T144251-gen-94b07f` passed. Nine focused fixtures passed check and
native execution, including the retained body-evidence control. Seven
public fixtures also passed JIT. Two supplemental probes with
`T#Source.Output: Marker` on the method and its enclosing impl passed
check/JIT/native and returned 42. Same-source medians were 6.562816 s
and 6.550406 s, with byte-identical LLVM across all eight runs.

The executable handoff already replays the caller's retained proofs and
equations, but body admission still calls `groundCallableSignatureBounds`
on registered rows for comparison. Direct provided copies likewise still
use the ordinary source-bound reader. Complete those paths and bind clause
identity at declaration admission before independent review.

## Provided clause identity and direct-call checkpoint

Admission binds each provided method's assumption index to the exact
lexical clause in the method or its enclosing impl. Both generic static
selection and direct selection of a provided placement read that mapping.
Clause count and authored identity are established before any call reads
them, including a signature with an empty clause list.

With candidate `9b8c7ea5`, removing the copied row's source clause identity
after admission fails the intended assertion in `existential_symbolic_result`.
Build `20261112T144821-build-8f4ab5`, candidate `32c3ead2`, passes.
Nine focused fixtures passed check/native and seven public fixtures passed
JIT. Two direct calls with associated-type bounds in the method and the
enclosing impl returned 42 in JIT and native execution. Standard generation
`20261112T145135-gen-6b290e` passed. Same-source medians were 6.580754 s
and 6.584024 s, with identical LLVM across all eight runs.

Executable admission still needs to compare recorded evidence using
these admitted clause identities and recipes.

## Provided executable clause checkpoint

Body admission verifies the proofs of a recorded provided call, binds them to
the admitted clause IDs, and interprets the authored clause recipes in that
local instance environment. Only a matching clause contract can publish the
environment. A dependent projection uses the retained prerequisite proof.
Direct and static calls share the admitted source clause reader.

The internal `retained_provided_body_constraints` fixture starts from an
actual prepared body. It verifies the original recorded proof, corrupts
the registered clause row, and repeats executable admission. Candidate
`32c3ead2` reaches the intended assertion. Build
`20261112T145514-build-849d77`, candidate `199ab19f`, passes. Nine targeted
fixtures passed check/native and seven public fixtures passed JIT. Four
supplemental direct/generic calls using a projected where subject in the
method or enclosing impl passed check/JIT/native. Standard generation
`20261112T145808-gen-660bf2` passed. Same-source median 6.587857 s before
and 6.620319 s after these two increments, with identical LLVM in all
eight runs.

Before closure, audit the symbolic associated-output read for an authored
function-bound premise, which can still reach the generic declaration-row
reader, and compare direct provided argument/result consumers with the
registered-method sibling's boundary. Then obtain independent review.

## Provided where equation checkpoint

A symbolic projection rooted in a provided declaration's function-bound
premise now uses the admitted assumption-to-source mapping and the
prepared bound instead of reading the registered row. In
`existential_symbolic_result`, candidate `199ab19f` substitutes the wrong
associated output after that row is changed. The fresh candidate retains
the original `Bool` equation.

The 29-fixture group exposed an earlier regression in
`trait_method_inherited_constraint`. Candidates `32c3ead2` and `199ab19f`
count a translated requirement clause on `impl Layer as Action` as if it
were authored in a provided declaration. Source admission and the
direct/executable clause adapters now distinguish these by the original
declaration role. This fixture passes check, JIT and native execution.

Build `20261112T150710-build-543d5e`, candidate `cf1a1eb6`, passes all 29
group checks, ten targeted check/native controls, eight of those controls
under JIT, and generation `20261112T151010-gen-eec5e9`. The separate known
`trait_subject_associated_paths` diagnostic reproduces on both this candidate
and `9b8c7ea5`, with ownership retained by [com-9clj](com-9clj.md).
Same-source comparison against `9b8c7ea5` measured 6.711351 s and 6.709681 s
with identical LLVM in all eight runs.

Independent review confirms this task owns the remaining direct provided
source argument and result consumers, including expected-result
completion in Direct and StaticMethod. Review also identified the need to
distinguish first admission from missing evidence after admission, replay
nested where equation recipes, and preserve the requirement-derived
where contract for synthetic trait-subject forwarding. Check the raw
requirement metadata and the nested Universal rejection controls before
re-review. The review does not establish closure.

## Direct provided signature and forwarding checkpoint

Direct provided argument checking and contextual recording now use the
selected declaration's admitted parameter slots. Source result typing and
expected-result completion use its retained result recipe. Receiver trait
arguments come from the selected proof even for a nominal provided copy;
the expected result only fills the remaining method parameters. Static
provided expected-result completion uses the same signature interpreter.

The fixed `cf1a1eb6` carrier accepted a direct argument check after the
source signature was removed, rejected direct `typedPair()` despite its
annotated result, and lost the original requirement clause when its raw
row was replaced by a sibling with no clauses. The last RED used the
compiler source frozen at `7f36d50a`. All three controls pass with the
fresh carrier. The requirement clause count now comes from its admitted
signature.

A bounded default forwarder on `impl Base as BoundedRead` reproduced the
review's incomplete-evidence failure. It passed before the clause-identity
changes. Its static selection now reads the selected implementation's
own clauses, through the same explicit substitution as a direct
implementation call. The original unbounded test remains, with direct
and generic bounded calls added. A scratch negative control substituting
`Bool` for the `I64` input retained the missing-where diagnostic across
check, JIT and native compilation.

Build `20261112T152503-build-b111e3`, candidate `2bd55d6c`, passes 29 group
checks, ten targeted check/native fixtures, eight public JIT fixtures and
generation `20261112T152753-gen-7fcf7b`. Same-source medians were 6.669746 s
and 6.680291 s. The LLVM outputs differ only by a bijective renaming of
1,541 generated generic body symbols with the same body IDs. This
diagnostic comparison does not certify a new bootstrap fixed point.

The task remains open. Next confirm the remaining requirement metadata
readers, nested where recipes, missing post-admission evidence, and the
Universal rejection boundary. Apply the independent review disposition
before final re-review.

## Sealed admission and static proof boundary checkpoint

The declaration sweep closes early signature construction. Request readers
can use admitted receipts during and after the sweep, but a missing
receipt after admission is an Internal diagnostic. Failed admission
retains the original failure. The same boundary serves provided clauses,
provided callable types, and raw requirement consumers.

In isolated compiler-source copies the only test accessors cleared
`authoredSignatureViews` or `authoredRequirementViews` after successful
analysis. Both lanes reconstructed the receipt at `a675522c`, reaching
the intended assertions. The updated sources reject both while leaving
the source registration intact. The tracked
`global_authored_signature_admission` control exercises first reads of
provided and existential signatures from initializers.

Selected requirement declaration metadata, argument count, and Unit
classification now use the admitted slot. The raw sibling-row swap in
`existential_symbolic_result` reached the expected metadata assertion at
`a675522c`; the new reader retains the original declaration, its where
clause, and Unit result. Mid receives an explicit diagnostic when the
selected requirement metadata cannot be read.

The shared recursive static-proof gate now covers provided source
signatures and clauses as well as raw requirements.
`interface_final_evidence` injects a genuine interface root directly and
inside a conditional witness into the provided signature reader. The
intermediate candidate `a9b873a5` accepted the direct root. The final
candidate rejects both with the explicit static diagnostic. The concrete
adapter's nested control separately requires the universal-scope
diagnostic.

Build `20261112T154429-build-dc628b`, candidate `885d64c4`, passes ten
targeted check/native fixtures, seven public JIT fixtures, and standard
generation `20261112T154825-gen-f8d73f`. A supplemental public nested
where-equation call returned 42 by both direct and generic invocation
in JIT and native execution. Same-source medians against `2bd55d6c` were
6.655639 s and 6.672044 s, with identical LLVM in all eight runs.

Before closure, trace the nested equation's exact source recipe and
translated requirement final comparison under evidence removal. The
successful public control alone does not prove that neither path
re-queries the prerequisites. Then obtain independent re-review.

## Direct provided where-equation checkpoint

A direct provided premise now reads its retained subject, positional
arguments, and only the selected associated equation through the shared
signature recipe reader. Other equations on the premise are independent
until selected. Re-entry into an active projection equation reports Internal.

The strengthened `existential_symbolic_result` control reaches its
intended assertion with `885d64c4`: for `U: Source[Item=Bool]`,
`T: Source[Item=U#Source.Item]`, and `T#Source.Item: Marker`, the last
subject is left symbolic. It resolves to Bool on the new candidate,
including after the raw first clause is overwritten. A separate
source-copy probe reads only the result annotation `T#Source.Item` and
then removes the single admitted view proof whose receiver is the method's
second type parameter. The old source still returns a result. The new
source diagnoses "signature view has no saved proof". The test accessor
exists only in the isolated probe.

Build `20261112T155516-build-1287c2`, candidate `fce04f7c`, passes five
targeted check/native fixtures, three of those in JIT as well, and standard
generation `20261112T155830-gen-b24c70` (25 pass, 5 expected reject).
The public nested equation returns 42 by direct and generic calls in
both JIT and native execution. Same-source interleaved medians were
6.623589 s and 6.633568 s, three samples each after warmup. All eight LLVM
outputs matched byte for byte.

Next, verify and close the inherited and raw requirement premise paths.
At the translated implementation boundary, trace the caller's instantiated
projection equations from static calls and existential thunks to the final
public clause comparison. That comparison currently still calls
`groundCallableBound`; test it with the projection evidence removed before
changing the handoff. Independent re-review remains required for closure.

## Direct raw requirement where-equation checkpoint

The raw requirement reader now uses the same authored clause recipes as the
provided reader for a selected direct premise. The source slot still owns
the proof; the selected receiver and positional instance are checked after
substitution. The nested direct requirement test fails on `fce04f7c` with
an unresolved last clause subject and resolves it to Bool on `096120ea`.
An isolated result-only probe removes the view proof on the second method
parameter. The old source reads the result anyway; the new source reports
"signature view has no saved proof".

Build `20261112T160509-build-620153`, generation
`20261112T160836-gen-2a66a5` (25 pass, 5 expected reject), and five
targeted check/native fixtures passed. Four of those fixtures also passed
JIT. A separate generic call with `T#Source.Item: Number` returned 42 in
JIT and native execution and passed check. Same-source interleaved
medians were 6.633151 s and 6.651190 s; all eight LLVM outputs matched.

Two remaining REDs reproduced on `096120ea` in isolated source copies.
For `Child[Element]: Parent[Output=Element]` and
`T: Child[U#Source.Item]`, reading `T#Parent.Output` still succeeds
after removal of the proof for `U#Source.Item`. The exact inherited
path must retain the source recipes of the inputs it uses. Separately,
the implementation boundary accepts a projected public clause after
receiving the correct concrete bounds and proofs with the projection
normalizations omitted. The public positive above supplies the valid
control. Preserve the instantiated normalization receipt into the final
comparison from both static calls and interface thunks.

## Public clause replay at the implementation boundary

Static calls and existential boxing now hand the instantiated projection
equations to the same implementation boundary. It checks the equations,
structurally substitutes the admitted public clause, replays those equations,
and compares the saved clause and witness. The public comparison no longer
calls `groundCallableBound` or the source-admission predicate comparator.
The implementation's own derivation and declaration-bound validation are
separate from this public clause replay.

`retained_requirement_body_constraints` exercises a real generic call with
`T#Source.Item: Number` and then submits the concrete public bounds and
proofs with the equations omitted. The old `096120ea` source accepted that
submission; the new candidate diagnoses a different public substitution.
Separate positive static and existential calls pass check, JIT and native
with output 42. The existential case uses `Service: Source[Item=Payload]`
and `where Self#Source.Item: Number`. Eight targeted check/native fixtures
passed, including boxing conditions and final interface evidence. Build
`20261112T161447-build-385a23` and generation
`20261112T162032-gen-4fd25d` passed on candidate `0cfdc037`. Same-source
medians were 6.645424 s and 6.640831 s, with eight identical LLVM outputs.

The inherited where-equation RED in the previous checkpoint is still open.
During the existential controls, a declaration-only input also isolated a
source-admission rejection present on both candidates:
`trait Source { type Item } trait Service { type Input: Source fn fetch() -> Input#Source.Item }`.
The diagnostic says that the receiver lacks the exact conformance, despite
the associated bound. Resolve this under the existing declared-premise
guarantee and distinguish it from the later interface-call boundary. Both
source admission and the remaining inherited path precede independent
closure review.

## Associated receiver admission

Both type lowering adapters now bind the written head in
`Input#Source.Item` using the same lexical associated-type lookup as a bare
`Input`. That head is itself an authored occurrence and receives its own
proof. The outer occurrence consumes it through the existing associated
clause admission. Explicit method binders still take priority in the
lexical lookup.

`trait_requirement_signature_associated_receiver` reproduces the unused
requirement rejection on `0cfdc037` and passes check, JIT and native on
`64a80a5e`. Removing `Input: Source` still yields the Source conformance
diagnostic. The value adapter control also passes for the parameterized
`Input: Project[Kind]` with separate parameter and result occurrences.
The existing value fixture had been adding traits after signature admission
was sealed. It now builds each fresh declaration session with an admitted
module binding and invokes the sweep after lowering, preserving the
inherited positive and wrong-instance rejection.

Build `20261112T162444-build-9882c1`, generation
`20261112T163238-gen-dae81a`, four targeted check/native fixtures and three
public JIT fixtures passed. Interleaved medians were 6.603329 s and
6.601279 s with all eight LLVM outputs identical.

The new source admission exposes two later failures in valid associated
receiver programs. With `Entry as Source { type Item = I64 }` and
`type Input = Entry` in the Service implementation, comparing the
requirement's projected result against `fn fetch() -> I64` still fails.
A `fetch() -> I64 where Input#Source.Item: Number` source also reaches
a where-conformance rejection at the requirement. Trace the admitted
nested proof through concrete conformance comparison and interface replay.
The inherited where-equation RED also remains. Two acceptance controls
already show that an unrelated associated predicate or positional
argument can mention the inherited output itself when the parent output
is constant. Do not eagerly read those unrelated source expressions
while resolving that output.

## Associated receiver replay diagnosis

On `a5a75c3d`, substituting `Input = Entry` into
`Input#Source.Item` reaches `Entry#Source.Item` during the implementation
comparison, but the raw type comparator has no evidence to reduce it.
`checkConformances` checks method bounds before it publishes the
conformance's associated-clause rows. Its separate completeness scan also
matches raw parameter types, and callable-form preparation calls the same
raw parameter matcher before either step.

An isolated compiler copy prepared the existing associated-clause rows
first, read the original requirement recipes, and selected the row by
the saved raw Self prerequisite and associated clause ID. It accepted
the declaration and static call with an I64 result, continued to reject
a Bool implementation, and accepted the declaration and static call with
`where Input#Source.Item: Number` after the clause was read the same way.
The experiment did not replace the earlier parameter matcher: an I64
parameter implementing `Input#Source.Item` still failed completeness.
The existential result case reached witness-signature comparison. The
existential where case reached `prepareCallTemplateConstraints` and
rejected the projected bound there. These are distinct from source
admission and the concrete conformance comparison.

Implement the shared requirement interpretation for parameter matching,
result validation and translated where clauses, with the relevant
associated-clause evidence prepared before comparison. Follow the retained
prerequisite and clause for a concrete conformance. For an erased
interface, distinguish a caller-fixed associated receiver from hidden
Self and preserve the resulting proof in the interface's own scope.
Exercise the positive and mismatching declaration controls, then both
static and existential calls. The isolated experiment is diagnostic
evidence and was not installed in the compiler.

## Concrete conformance signature replay

Concrete conformance admission prepares associated-clause evidence before
checking method signatures. Parameter matching, result comparison and
translated public clauses share the admitted requirement, Self environment
and recipe memo. For an associated clause rooted in the selected declaration's
own Self, the recipe reader consumes the conformance's exact saved clause
and proof. Callable-form preparation uses the same parameter reader and
prepares the clause evidence only if it has not already been published.
The separate raw completeness scan is removed. When interpreting an
authored concrete witness, static dispatch tests the saved implementation
plan for the exact requirement slot. Synthesized conformance selection
still uses its own witness list.

The new `trait_requirement_associated_receiver_conformance` fixture
reproduces the incomplete-conformance diagnostic on `64a80a5e` and
passes with the concrete associated receiver in a parameter, result and
where clause. The default-argument variant also passes. A wrong concrete
result still fails at the implementation. Build
`20261112T165311-build-9d447c`, generation `20261112T165722-gen-e30567`,
eight public check/JIT/native fixtures and seven rejection checks passed
with candidate `015ad2cc`. Reusing the trait environment and the read
public clauses removed avoidable work. The same-source comparison was
6.633076 s to 6.648505 s. A separate LLVM comparison matched after
normalizing generated generic-body symbol components by body ID.

The declaration and direct static call now pass, but a generic call with
`R: Service[Input=Entry]` still fails receiver validation when its projected
result is used in another call. The variant that leaves the result unused
passes check. Existential result and where probes still fail at the
witness-signature and source-call-constraint boundaries, respectively.
Preserve a fixed associated receiver's projection proof in those readers
and keep hidden Self abstract. The inherited where-equation proof-removal
case also remains before independent closure review.

## Fixed associated receivers in dispatch

When a requirement proof derives from a clause on the raw requirement's own
Self, a caller-fixed associated receiver may have a closed proof independently
of Self. Admit that exact associated clause once per source proof and
substituted bound. The key includes receiver identity and the full trait
constraint. Preserve the frozen proof across public signature and where
reads. A concrete selected Self instead replays its conformance's saved
associated clause. Existential witness source results use that concrete
proof, while the public signature uses its fixed associated binding.
Replaying a concrete trait-subject conformance retains the path prefix
through its selected trait. Treating only its terminal edge as a nominal
witness reproduced a declaration-subject error in intermediate candidate
`bd1493b1`.

`trait_requirement_associated_receiver_dispatch` fails on `015ad2cc`
when a second call uses the projected result. It passes check/JIT/native
on `25141343`, printing 42 for generic and existential calls with both
a direct conformance and a conferred conformance. The separate result
and where probes now pass check. Removing the generic associated binding
still rejects the call. Build `20261112T170502-build-cb56a3`, generation
`20261112T171046-gen-d462b9`, eight targeted check/native fixtures and
six public JIT fixtures passed. Same-source medians were 6.660946 s and
6.657577 s, with byte-identical LLVM in all eight samples.

Next, close the remaining inherited where-equation path under proof
removal. Resolve only the original recipe inputs that the saved path uses.
Keep the existing controls where an unused sibling equation or argument
mentions the inherited output. Check other inherited associated-premise
paths during independent review rather than generalizing the direct-path
validation to them without evidence.

## Inherited where-clause recipe replay

Raw requirements and provided signatures share the reader for a selected
where premise. For an inherited premise, the reader follows the saved path
in the declaring trait's own type parameters and associated projections.
It reads the source recipes only for the terminal instance's positional
arguments and selected output. The raw bound mirror no longer supplies the
result of either where-premise reader.

`existential_symbolic_result` reaches the intended assertion on
`25141343` when `Child[U#Source.Item]` should imply a Bool output on Parent.
The new candidate also passes the associated predicate and two-edge cases.
Isolated provided and raw result readers both reject when the exact proof
for `U#Source.Item` is removed. Two separate result-only controls still
read I64 when an unused root argument or predicate refers to that same
constant parent output. A public provided call with the inherited where
constraint passes check, JIT and native execution. Build
`20261112T171551-build-b076fe`, candidate `715bb5cd`, generation
`20261112T172227-gen-14b2b6`, and five targeted check/native fixtures
passed. The four public fixtures also passed JIT. Same-source medians
were 6.696342 s and 6.664377 s with all eight LLVM outputs identical.

### Independent review findings under investigation

Three legal source controls still fail on `715bb5cd`:

- `type Input: Source` with `Source: Root` and a requirement returning
  `Input#Root.Item` cannot read the associated clause proof through its
  terminal supertrait path. A concrete implementation returning I64 is
  rejected even though Entry's Root conformance binds Item to I64.
- `trait Service: Root { fn fetch() -> Self#Root.Item }` similarly
  rejects an I64 implementation when the output is supplied by the
  concrete Root witness. Writing a constant Item on Service's parent edge
  already passes. This path has no associated-clause premise.
- A provided method returning `Input#Source.Item` on Service with
  `type Input: Source` still leaves the concrete result symbolic when
  a caller uses it as a method receiver. The provided reader does not
  consume the associated-clause proof on its selected Self.

The associated premise's prerequisite path to the member's owner is
distinct from the terminal path from its declared bound to the requested
trait. Check those paths separately. No legal source control for a nested
projection over an inherited associated member has yet been established.
The explicit double-projection spelling is currently rejected as a
nonfinal projection. Also verify that fixed-receiver proof reuse has a
clear admission/replay boundary under evidence removal. The review is
ongoing and this task remains open.

## Selected supertrait witness replay

Raw requirements and provided signatures now use one Self projection
reader. A declared parent equation can determine the output directly.
Otherwise the reader consumes the selected witness's saved parent edges.
Conformance checking publishes those edges before method checking, so an
implementation can precede the declarations of its parent conformances.
An associated-receiver proof first reads the saved associated clause on
the selected Self, then follows the terminal supertrait path. Raw and
provided owners check their respective prerequisite identities before
using that shared reader.

The review's nominal Self and associated-receiver cases pass check, JIT
and native, including a two-edge Self chain, erased associated dispatch,
and direct and inherited associated projections in provided methods.
An isolated reader rejects when only the selected Service supertrait
row is removed and the Root conformance is still registered. Build
`20261112T173145-build-c42430`, candidate `399c3087`, generation
`20261112T173552-gen-4d31a6`, eight public check/JIT/native fixtures and
five rejection diagnostics passed. Same-source medians were 6.687980 s
and 6.714668 s, with identical LLVM output in all eight runs.

Callable-form synthesis now prepares the declarations reached by its selected
supertrait evidence before reading requirement parameters. The preparation
shares the existing publisher and visits each selected declaration once in
the callable-form pass. Signature readers consume the published rows in both
phases. `supertrait_projection_default_callable` previously rejected the
missing Middle row and now exercises the adapter through the Service view.
Build `20261112T174151-build-d9341c`, candidate `02115514`, generation
`20261112T174454-gen-d9a96f`, and four check/JIT/native controls passed.
The same-source medians were 6.667171 s and 6.663319 s, with identical LLVM
output in all eight runs.

For a generic `Holder[T]` with `Service: Middle: Root` and `Root.Item = T`,
signature checking now substitutes each selected parent row in its owner's
environment while the receiver is still symbolic. Conditional parent edges
read the corresponding clause of the retained witness plan. Executable
replay still requires closed types. Two generic fixtures (unconditional and
conditional) rejected with a return-type mismatch on candidate `02115514`.
Both now pass check, JIT and native on `fb46c683`, alongside four existing
controls. Six rejection controls passed, including the generic wrong result.
Build `20261112T175214-build-188bd2` and generation
`20261112T175514-gen-a3dfc5` passed. The same-source medians were 6.678752 s
and 6.676580 s, with identical LLVM output in all eight runs.

An assumed trait-subject path reaches this boundary when the generic Middle
impl assumes `Holder[T]: Seed[T]` and `impl Seed[Element] as Root`
supplies `Root.Item = Element`. Candidate `fb46c683` rejected the Service
result. Declaration replay now substitutes the retained bridge and preserves
the path's premise. Interface rebasing shares path composition. The resulting
terminal can provide signature data, while executable selection still needs a
concrete path. Candidate `424cb68a` passed the new fixture and five existing
check/JIT/native controls. Removing the Middle assumption rejected with
`supertrait not satisfied`. Build `20261112T180450-build-bb6f17` and
generation `20261112T180757-gen-817897` passed. Same-source medians were
6.704753 s and 6.700268 s, with identical LLVM output in all eight runs.

The fixed-receiver removal probe has a verified RED on `3428d631`.
In an isolated source copy, read the result of
`any Service[Input=Entry]`'s `fn fetch() -> Input#Source.Item`,
where `Service.Input: Source` and `Entry as Source` supplies `Item=I64`.
Check that the result is `I64` and that the fixed-receiver receipt store
contains evidence. Clear that store alone and read the same signature again.
The reader succeeds by re-querying the still-present conformance.

Dynamic call finalization now requires the retained proof. Initial source
signature admission and specialization of an open interface can establish a
closed proof. For a closed source receiver, the dynamic template reader also
requires the existing proof. An isolated AOT probe cleared only the receipt
store immediately before `recordSelectedBodyCallee` read the interface
signature. It verified the receipt existed and left the conformance
registered. The previous reader accepted the final call; the new reader
returns Internal with `fixed requirement lost its admitted associated proof`.
The public instance fixture passes with two bindings, `Input=Entry` and
`Input=Flag`, whose outputs have different types. Build
`20261112T181608-build-a0f697`, candidate `58db42aa`, and generation
`20261112T182038-gen-8bac9c` passed. Nine public check/JIT/native controls and
three native internal controls passed. Same-source medians were initially
6.730798 s and 7.033536 s; a reverse-order repeat measured 6.734468 s and
6.748963 s. All sixteen LLVM outputs matched.

Independent review keeps the task open. The boxing finalizer still reaches
signature admission through `selectExistentialMember` and
`existentialWitnessPlan`; thread a prepared witness signature and method
conditions into that consumer. The existing
`retained_associated_interface_condition` fixture is also a regression in
this task's interface where handoff. It passed on `b71d8507` (see
[source interface normalization evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/retained-source-interface-normalizations.json)),
and passes on the saved static-parameter-b carrier. It rejects at line 9 on
the clause-witness carrier and the current candidate. The transition to
`readRequirementBounds` in `d274fab2` is the first suspect. Restore the
saved conditional proof and projection equation through the actual interface
reader and repeat the independent review.

## Interface where projection replay

An isolated trace confirmed the failure at `instantiateInterfaceCall` during
declaration checking. The expected subject was still an associated projection
while the interpreted proof established the concrete element. Dynamic
interface calls now substitute the source bound structurally, replay the
selected call's saved projection equations in the interface instance, and
compare its condition proof against that normalized bound. No signature
reconstruction is needed at that comparison.

Build `20261112T183231-build-05d503`, candidate `6b3360c3`, and generation
`20261112T183553-gen-627029` passed. Eight public check/JIT/native controls
passed, including the restored `retained_associated_interface_condition`
with output `45`. The missing-promise rejection and the internal
`RetainedSourceCallNormalizations` missing/wrongOutput/wrongProof controls
passed. In the same declaration-checking path, replacing only the saved
equations with an empty list again rejected the otherwise valid input.
Same-source medians were 6.689086 s and 6.692439 s, with all eight LLVM
outputs identical. The unrelated mixed conditional trait-edge fixture is
already assigned to [com-wfq2](com-wfq2.md) and has the same diagnostic on the
before and after carriers.

The boxing issue now also has an isolated RED at the final consumer. In the
fixed-proof removal program above, keep the local conversion to
`any Service[Input=Entry]` and remove the call to `fetch`. Clear the existing
fixed-proof receipt store immediately before `selectExistentialMember` in
`finalizeConversionDependencies`. Candidate `58db42aa` finishes boxing
successfully by reacquiring the missing receipt. Next, retain the prepared
witness plan and where conditions across this boundary, and verify the first
concrete JIT request and the AOT replay independently.

## Prepared existential witnesses

A concrete box now prepares each member's exact signature, result conversion,
selected implementation and checked environment together. Declaration checking
and the first concrete lazy request share this producer. The finalizer reads
its published plan by the source/target types and checks the selected
conformance identity and slot count. It no longer calls the member or
signature admission routines. Recursive adapter-result conversions reuse
prepared boxes. Failed dependent preparation rolls back the new box plans.

Two isolated AOT controls exercise the final consumer. Clearing only the
fixed-proof lookup store leaves the prepared witness plan usable and the
store empty after finalization. Clearing the actual prepared box plan
returns Internal with `existential conversion has no prepared witness plan`.
Build `20261112T184401-build-21b615`, candidate `bfaa29e1`, generation
`20261112T184746-gen-44f25d`, eight public check/JIT/native controls, the
missing-promise rejection and three internal native controls passed.
Same-source medians were 6.724992 s and 6.707252 s, with identical LLVM
output in all eight runs.

The independent review's inherited associated-owner case now has a reduced
source reproducer. `Parent` declares `type Input: Source`;
`Service: Parent` declares a requirement using `Input#Source.Item`.
The current candidate rejects the requirement during authored projection
admission. The directly declared `Service.Input` and the separate terminal
supertrait of `Source` both have working controls. Check the owner path in
the source recipe and the replay of its prerequisite, then check a replaced
fixed associated proof against the full saved bound before independent closure.

## Fixed associated clause integrity and inherited-owner controls

The receipt now retains the selected clause's projection equations. A hit
checks its proof against the full clause, including associated predicates,
using only saved equations. In the isolated replacement control,
`Service.Input: Source[Item=I64]` is fixed to `Entry`. Keep the receipt key
and replace its frozen proof with the `Entry#Alternate as Source` proof
whose `Item` is Bool. Candidate `bfaa29e1` accepted the replacement.
Candidate `bae2673b` rejects it with Internal
`fixed requirement proof does not match its admitted associated clause`.

The explicit qualified form `Wrapper[Self#Parent.Input]#Select.Value`
establishes a legal inherited-owner control. Its where-clause form passes
through `any Service` and runs in both backends. The return-type variant
still fails implementation result matching even on the older
`plewc-retained-source-interface-fixed` carrier. The bare
`Input#Source.Item` form fails independently. The lexical associated-name
lowerer reads only the current trait owner's declarations. Source ordering
must not become a requirement while adding inherited owner resolution.
After the source binds the member, the signature reader must preserve its
parent path and any equations consumed by an enclosing projection.

Build `20261112T185328-build-e2b0b3`, generation
`20261112T185644-gen-7ad1e2`, and seven check/JIT/native controls passed,
including the qualified inherited where case. Same-source medians were
6.699748 s and 6.705766 s, with identical LLVM output in all eight runs.

## Qualified inherited associated results

The reduced output case showed that the enclosing `Wrapper` proof retained
the associated clause of the original `Parent.Input` as a condition.
Reading only the witness's output term left that term symbolic after the
inner projection had already specialized to `Entry`. The requirement
reader now resolves the selected condition by its full receiver and trait
instance, follows the saved parent path, and uses the parent's published
associated clause to read the output. It traverses semantic children when
the resulting projection is inside another type. Nominal conformance
checking and default callable-form preparation publish the necessary
associated clauses before comparing requirements, including when the
parent impl is written later.

Build `20261112T190915-build-1a8148`, candidate `2bbe01c9`, and generation
`20261112T191208-gen-9ed8b8` passed. Nine check/JIT/native controls passed,
including the inherited return and default callable fixtures. The wrong
result was rejected. An isolated removal of only the selected Parent
associated-clause table was rejected, with the Parent conformance still
registered. Same-source medians were 6.697235 s and 6.701365 s, with all
eight LLVM outputs identical.

The generic version remains RED: bind `Worker[T]`'s `Parent.Input` to `T`
under `T: Source`, and implement the same wrapped requirement with
`T#Source.Item` as parameter and result. Candidate `2bbe01c9` rejects it
during requirement matching. The inherited projection must carry the
same symbolic subject and condition evidence while the receiver is open.
Bare inherited associated-name binding also remains open.

## Symbolic inherited associated signatures

The fixed carrier `2bbe01c9` rejected
`inherited_associated_symbolic_signature` during requirement matching.
The associated-clause replay stopped when the selected parent's output
was a rigid parameter. Signature reads now use declaration replay for
that open subject, following the parent's retained associated clause to
the existing condition proof. After validating the exact clause, a
projection without an equality keeps its member and trait instance on
the selected subject. Executable proof replay still requires closure.

Candidate `ad416611`, build `20261112T192041-build-0dc16a`, and generation
`20261112T192326-gen-0d114a` passed. The regression and seven controls
passed check, JIT, and native execution. A wrong result and a missing
parent bound were rejected with their respective diagnostics. A variant
where the symbolic condition is supplied by a supertrait passed check.
Same-source medians were 6.710371 s and 6.722351 s. All eight LLVM
outputs matched.

For the remaining bare-name case, source binding must supply the
declaring parent instance and its substituted arguments before the
lowerer constructs the outer projection and its authored recipe. Both
the syntax path and the value-AST controls currently see only the
current trait's own associated names. Cover a parent declared later,
a parameterized parent reached through another trait, and the qualified
control before closing this scope.

## Prepared trait headers for inherited names

Candidate `ad416611` rejects the bare `Input#Source.Item` signature with
the parent either before or after the child. The same diagnosis occurs
with `Service: Middle[I64]` and `Middle[Element]: Parent[Array[Element]]`.
A separate `Child: Parent[Item=()]` control passes with
`Self#Parent.Item` and fails return-type matching with bare `Item`.

The SyntaxFile frontend now finishes trait identity registration, prepares
each trait's lexical binders and declared supertrait constraints, and then
lowers requirements. The completed trait consumes the same binders and
constraint range. This provides source-order-independent inputs for
binding inherited names. The remaining work is to select the declaring
trait instance, build its projection and argument recipes, and carry its
proof through signature admission and the final consumers. The value-AST
adapter must share the same semantic selection where it handles these
signatures.

Candidate `63c91fad`, build `20261112T192921-build-d59e1c` and generation
`20261112T193207-gen-4e860d` passed. Four public controls passed check,
JIT and native execution: unit and parameterized supertrait projections,
the generic conditional supertrait projection and the symbolic inherited
signature. Three direct SyntaxFile lowering fixtures passed native
execution. The standalone `syntax_lower_func_decl` and
`syntax_lower_conformance_bounds` fixtures still abort in both the
baseline and new candidate. A baseline diagnostic probe confirmed that
the former calls where-clause lookup without admitted module bindings
(already recorded under [com-9hde](com-9hde.md)).

Same-source medians were 6.737406 s and 6.738979 s. The output diff is
confined to the type-reference component of generic body symbol names.
Moving header preparation earlier changes type-reference allocation order;
all other LLVM text was identical. This comparison is separate from the
formal self-host fixed-point gate.

## Bare inherited associated projection

The fixed header candidate `63c91fad` rejects the new
`inherited_associated_bare_signature` fixture at the outer trait view.
The lexical resolver now follows prepared supertrait instances with
simultaneous positional substitution and forms the projection on lexical
`Self`, with the associated member's declaring owner. The nominal
requirement reader uses the same selected associated-clause reader for a
written projection and for a projection in a retained witness output.
After the lexical binding alone, the fixture still failed witness matching;
replaying the saved parent clause closes that second boundary.

Candidate `634efb21`, build `20261112T194215-build-2aa650`, and generation
`20261112T194507-gen-22f782` passed. Eight tracked fixtures passed check,
JIT and native. Four extra controls passed both execution modes: parent
before child, a fixed unit output, existential dispatch with a fixed
inherited receiver, and a provided method with the inherited receiver.

The parameterized two-hop path now reaches signature recipe admission.
`Service: Middle[I64]`, `Middle[T]: Parent[Array[T]]` selects
`Parent[Array[I64]]`, but the recipe builder classifies the inherited
argument as a direct lexical parameter. The verifier correctly refuses
that derived edge. The control with a competing `Parent[Array[Bool]]`
instance fails at the same boundary. Retain argument provenance from the
selected heritage edge and validate it against the admitted parent path;
keep the existing direct lexical parameter rule. The lookup traversal's
analysis-limit diagnostic also needs the Limit failure classification.

The construction path now propagates name-binding diagnostics through its
existing Result callers. Three range/construction controls passed check,
JIT and native. Same-source medians were 6.737422 s and 6.746021 s. The
LLVM diff was limited to type-reference numbers in generic body symbols.

## Retained inherited trait arguments

The two-edge requirement fixture selects `Parent[Array[I64]]` through
`Middle[I64]` while the conformer also has `Parent[Array[Bool]]`. The
previous carrier `634efb21` classified the inherited argument as a direct
lexical parameter and refused its recipe. An intermediate candidate exposed
two further failures: `Parent[Self]` kept the intermediate trait's Self
binder, and repeating the inherited premise in a requirement where-clause
made source admission pick the raw where-clause for a projected receiver.

Inherited argument recipes now describe the structure of the chosen
instance. Admission requires their parent projection to follow the exact
lexical Self supertrait path, and checks its terminal receiver, owner and
all positional arguments. Lexical Self is substituted along with the
declared parameters at each edge. When an authored projection is itself a
projection's receiver, its saved occurrence proof supplies the prerequisite
to source admission. A direct where premise on the projected subject still
has its existing authority.

Build `20261112T200136-build-0f3655`, candidate `475f6a5c`, and generation
`20261112T200421-gen-f03e11` passed. Eleven tracked fixtures and two
parameterized provided/interface controls passed check, JIT, and native
execution. The wrong-instance witness and wrong result were rejected.

A parent positional argument containing a projection still fails at trait
view admission. The control uses
`Middle[T]: Parent[Array[Self#Marker.Type]] + Marker[Type=T]`. Its
declarations and conformances check without the requirement signature.
Both the bare inherited form and the explicit
`Wrapper[Self#Parent[Array[Self#Marker.Type]].Input]#Select.Value` form
fail once used in the signature. This contrast isolates the remaining
argument-normalization handoff; the failure is shared with explicit
projection, rather than a missing bare-name candidate. The value-AST
adapter still needs an order-independent header preparation and its own
producer/consumer check before independent completion review.

Same-source self-compile medians were 6.767873 s and 6.767579 s.
All eight LLVM outputs matched.
