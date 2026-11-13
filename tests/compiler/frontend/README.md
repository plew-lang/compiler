# Frontend implementation regressions

These are internal tests, separate from the language fixture suite. Each entry
imports the real `src/Frontend` module, including its parts. Never compile an
individual `src/Codegen/...` part as a substitute: it lacks the owning `Comp`
definition and does not test the implementation in context.

`TypeTermPublication.pw` checks projection publication outside Lower, receiver
argument substitution, structural inequality, and allocation-free equality.
Compile it with the selected carrier, link its LLVM with that carrier's runtime,
then compare program stdout with `TypeTermPublication.out`. A failure while
compiling the harness is not an executed assertion failure; no-main is not a
passing internal test. This directory is not picked up by `tests/harness/test.sh`.

The imported compiler implementation currently makes even this harness an
expensive compile. Apply the normal 60-second meaningful-progress rule, retain
the command session and final exit code, and do not overwrite the canonical
compiler or seed with diagnostic artifacts.

`TemplateDependencyUnfinalized.pw` checks that a published implicit-call slot
cannot satisfy a different, unfinalized slot. Compile/link the harness normally;
its execution must exit 0, report the diagnostic in the companion `.err`, and
print the `.out` marker after receiving the failure.
This is a compiler diagnostic test, not a panic (SIGABRT) test.

## Manual execution procedure

Run from the compiler repository root with the selected carrier. Keep all
outputs in a new directory under `tmp/`; these fixtures are not automatically
registered in the normal suite.

1. Compile the selected `.pw` with `--trace-phases`, using
   `python3 -B scripts/support/trace-command.py <compile-log> -- <carrier> ...`
   to supervise progress. Save stdout as LLVM and require compiler exit 0.
2. Export that same carrier's `--runtime` output to a C file. Link it with the
   generated LLVM using `clang -w`, adding the selected `llvm-config --ldflags`.
   Supervise runtime export and linking with `scripts/support/watch-command.py`;
   require exit 0 for each step. Do not execute an old binary after a failure.
3. Execute the new binary through `scripts/support/watch-command.py`, capturing
   stdout, stderr and the actual exit code separately.
4. For `TypeTermPublication`, require exit 0 and byte-compare stdout with its
   `.out`. For `TemplateDependencyUnfinalized`, require exit 1 and the literal
   diagnostic from its `.err` in stderr. A signal, timeout, compile/link failure,
   or another exit code is a failure, even if the diagnostic text appears.

Pass the fixture path under `tests/compiler/frontend/` to the carrier. Neither
procedure updates the canonical compiler or seed, nor replaces the standard
normal or sanitizer gates.

## LLVM-independent program preparation

`PreparedProgram.pw` invokes the production frontend and shared preparation,
without importing Backend. Run `python3 -B tests/compiler/frontend/test-program-preparation.py
--compiler /absolute/path/to/plewc --out tmp/preparation-check` (on one line).
The output directory must be new. The test links the probe with only its C
runtime, asserts that no LLVM dylib is needed, and compares successful
CoW/async/closure preparation and borrow/receiver/global conflict diagnostics
with the selected compiler. It does not execute the checked application's main
or claim whole-target checking of unused bodies. This is a manual test outside
the standard fixture suite.

`FrontendInputs.pw` exercises explicit in-memory input with two independent
Comp instances, source names, and options. The same test-program-preparation.py
command compiles and links it without LLVM, passes a nonexistent source argument
and invalid stdin, and compares with FrontendInputs.out: analysis must use only
the supplied requests.

`DiagnosticValues.pw` is also run by that script. It renders two structured
diagnostics, checks their exact stderr format, and continues to normal exit.
This verifies rendering, not propagation from all existing frontend failures.

The returning-failure mode calls analyzeFrontend directly and then prepares Mid.
It verifies the same diagnostic as the terminal CLI for borrow conflicts, missing
returns, move receivers, deinit constraints, syntax/part rules, unique containment,
trait ownership, existential formation, import visibility/cycles, public API
closure, derive visibility, and parameter ownership modes. The gen failure mode
sets the production gen option while preserving the same returning boundary. FrontendInputs also verifies that
a missing source returns an error before independent valid requests succeed.
This covers migrated boundaries; other frontend checks still terminate.

`DestructionShape.pw` checks declaration-only destruction selection. Compile and
link it with the same procedure as the other frontend probes, then pass
`DestructionShapeInput.pw` and the trailing-slash standard-library path. Require
exit 0, empty stderr, and `destruction-shape:ok` on stdout. It compares every
available finalized contract with its declaration shape, verifies a destructor
is discoverable, and asserts that shape queries add no executable body,
final destruction contract, or record layout. The compiler source itself is
also a valid input. Open TypeTerms and declaration heads with incomplete generic arguments are not
passed to this closed-instance API; their dependencies remain separate analysis
obligations. Every available final contract must pass those eligibility checks
and is compared; filtering cannot silently omit a published contract.

`test-failure-domains.py --compiler PATH --out NEW_DIRECTORY` is a manual scoped
TDD probe for com-yeua. It runs the existing returning-renderer control,
`FailureDomains.pw` (typed diagnostic values with identical rendered messages),
and `ProducerFailureDomains.pw` (actual source/input producers, repeated failed
owner requests, queue draining and stage conversion). It does not certify the
private process-result channel, normal/expose/ASan rejection consumers or the
whole failure-classification migration. Those integration gates remain required.

`TraitCycleInputAdmission.pw` is the met-c1pg raw graph-input regression. Compile
and link by the manual procedure, then run the resulting executable separately
with `missingOwner`, `invalidRef` and `unknownNominal`. Each must exit 0, have
empty stderr and match `TraitCycleInputAdmission.out`. Additional scenarios
`foreignOwner`, `invalidRange` and `traitArity` assert the respective exact Input
refusals. Its Input-domain and exact
input-failure assertions distinguish malformed requests from actual source
cycle refusals. These initial cases do not certify the task's complete binder,
identity, source-set or ordinary-source contract.

`TraitCyclePatternInputs.pw` covers graph-input binder membership versus matching
eligibility, duplicate binders, nominal/primitive/function arity, name identities
and record-projection children. Run separate scenarios `viewedBinder`,
`foreignBinder`, `duplicateBinder`, `nominalArity`, `nameIdentity`,
`binderNameIdentity`, `primitiveArity`, `functionArity`,
`recordProjectionInvalidChild`, `recordProjectionValid`,
`rawMissingProjectionMember`, `rawMissingMemberWithSourceSite` and
`rawMissingMemberWithUseList`. These three assert Input-domain rejection
even with an authored coordinate or a forged public use-list entry. All require exit 0,
empty stderr and the companion stdout golden.
`parameterArity` rejects an applied lexical parameter and `cyclicTypeTerm`
rejects a recursive raw term; `viewedBinder` remains a valid contrast.
View admission scenarios are `invalidViewOwner`, `viewOwnerNameMismatch`,
`unknownExtension`, `multipleTraitViews` and `duplicateTraitView`: exact Input
refusals for malformed selectors, normalization for a repeated valid trait.

`TraitCycleCanonicalIdentity.pw` takes `legacy`, `same`, `distinct`, `recordSame`,
`recordLabelDistinct` or `recordChildDistinct` and checks
that legacy/resolved carriers of one owner close the same cycle, while different
actual owners do not. Record cases ignore ABI layout names while retaining
field labels and field types. Additional scenarios `viewSame`, `viewDistinct`,
`extensionLegacy`, `extensionSet`, `extensionDistinct`, `projectionMirror` and
`viewSameSpellingDistinct` check resolved owner identity, legacy carriers,
unordered/deduplicated extension sets and receiver-owned projection views.
`viewSameSpellingDistinct` loads the two actual same-named trait owners under
`fixtures/TraitCycleViews/`; run from the compiler root.
The `projectionDistinctInstances` and `projectionSameInstance` scenarios use
symbolic projection terms as graph inputs and verify that different positional
arguments keep the edges disjoint while equal arguments close the cycle.
The ordinary source fixture supplies actual conformances to form those projections.
`TraitCycleSourceInputs.pw` takes `unknownNominal`,
`primitiveArity` or `missingProjectionMember` and checks the exact Source
diagnostic for each authored error (no argument retains `unknownNominal`). Compile/link
and compare their companion goldens by the same manual procedure. These bounded
checks do not certify the whole task, source-set semantics or final gates.

`SemanticTraitViewTerms.pw` is a manual com-zdod regression. Compile and link
using the procedure above, then run each of `differentArguments`,
`useProvenance`, `children`, `closedness`, `projectionPresence`, `topLevelView`
`closedControl`, `environment`, `nestedEnvironment`, `callerOwned`, `witness`,
`legacyGrounding`, `projectionNormalization`, `rigidViewMismatch`,
`alphaViewMismatch`, `completeViewSet`, `genericBinding`, `genericBindingControl`, `occursView`
`duplicateBuilder`, `nominalBinderCollision`, `qualifiedAlphaDifferent`,
`qualifiedAlphaOwnerDistinct`, `qualifiedAlphaSame`, `rigidParamScope`
and `rigidParamScopeControl`. Each must exit 0 with empty stderr and the exact `.out`.
It tests production semantic view storage/readers, not source syntax or final
method dispatch (which have separate follow-up tasks).

The com-zdod manual raw-input increment adds TraitCyclePatternInputs scenarios
`viewArity`, `viewExtraArity`, `viewArgumentRef`, `extensionArguments`, `viewArgumentBinder`,
`differentViewInstances`, `viewMetadataAfterNormalization`, and TraitCycleCanonicalIdentity scenarios
`viewArgumentSame`, `viewArgumentDistinct`, `viewArgumentDuplicate`,
`viewNestedDuplicate`. Compare each
successful execution with its existing companion `.out`. Pending RED results
are recorded in com-zdod; an assertion abort is a failed test, never a pass.

`SemanticTraitViewConsumers.pw` is a manual com-zdod regression for production
compatibility, argument recovery and recursive view-cycle consumers. Run
`compatibility`, `compatibilityControl`, `compatibilityMirrorControl`,
`argumentStored`, `argumentExplicit`, `argumentControl`,
`argumentDuplicateControl`, `genericCycleViewArgument`, `genericCycleControl`
`traitSourceActivation` and `bodyInstanceKeys`. Each execution must exit 0, match its `.out`, and
produce empty stderr. The source setup deliberately declares a trait and an
extension with the same spelling to check that resolved source kind controls
activation. It does not certify source parsing of parameterized view syntax.


### Canonical extension identities (manual)

`ExtensionFinalIdentity.pw`, `LegacyExtensionIdentity.pw` and
`ExtensionIdentityBindings.pw` each print their companion golden without arguments.
They exercise the compatibility final resolver, materialized AST conformance
registration and sealed module-binding identity respectively. Legacy identity
also takes `spanless`, `trait`, `spanlessTrait`, `unknown`, `spanlessUnknown`,
`foreign`, `spanlessForeign`, `method`, `spanlessMethod`, `foreignMethod` or
`spanlessForeignMethod`. The foreign setup deliberately chooses the same-spelled
bundle whose module differs from the interner's first name occurrence; method
cases check both registered Func/Conform identities and original defOffsets. These are manual
native diagnostics, not normal-suite coverage. The first covers value and
associated resolver APIs; it does not cover parser-to-associated-call dispatch.

`ViewSourceOwnerAdmission.pw` takes `TraitOnly`, `ExtensionOnly`,
`DistinctSourceKinds` or `DistinctExtensionOwners` and checks actual file graph
admission. Run those source fixtures with `--run` as well to distinguish selected
bodies (`11`, `22`, `11/22`, `22/33`). `FragmentAliasUse.pw` adds two fragments and
two alias/republication paths and must print `41/42`. The related
`FragmentAssociatedUse.pw` is a preserved failing associated-call probe owned by
com-4k31; it is not included among passing identity controls. The existing
normal `extension_assoc_source_select.pw` provides the smaller same-module
associated-call control. See the task evidence for candidates and exact results.


### Collision diagnostic context (manual)

`ModuleBindingCollisionLocations.pw` takes `TypeTrait` (default),
`DifferentImportedKinds` or `ImportedTypeLocalTrait`. Its stdout matches its
`.out`; stderr must contain the primary error and `previous binding is here`
note at the two original fixture lines. It also inspects the returning service's
Source failure and structured note locations. Registration order, rather than
source line order, determines which conflicting binding is primary.
`DiagnosticNotes.pw` has no arguments; compare stdout with `.out` and stderr
exactly with `.stderr`. This leaf test covers notes with unpositioned primaries,
line/file/unpositioned context and warning/failure-domain independence. Both are
manual native diagnostics outside the normal suite.


`ConformanceOnlyExtensionOwners.pw` is another manual native identity control.
It prints its companion golden without arguments. The File graph under
`ViewSourceOwners/ConformanceOnly` uses two same-spelled, differently owned
bundles with no methods. It checks Conform IDs/source modules, individual and
composed view sources, and the actual proof-source activation query's exclusion
of the other bundle. It does not certify complete trait-instance proof search
or associated-call dispatch. The setup itself is also valid for `--check` and
`--run` (no stdout).

### Value source-application consumers (manual)

`ValueViewApplicationConsumers.pw` covers direct Syntax and the materialized
ExprAst adapter. Run without arguments and with `nested`, `multiple`, `missing`,
`extra`, `named`, `indexOnly`, `adapter`, `adapterNested`, `adapterMultiple`,
`adapterMissing`, `adapterExtra`, `adapterNamed`, `adapterIndexOnly`; each must
exit0 with empty stderr and the companion golden. Success inspects exact owner,
arguments/children and original source-name range. Refusals require the selected
branch's Source diagnostic at its original line; the materialized invalid type
receipt also retains its exact offset. Adapter setup must succeed before Lower
is exercised. A comment carries the source text for an explicit programmatic
AST without forcing the setup analysis to consume that expression. These are
formation/handoff controls, not full conformance proof or final method dispatch.
`SourceViewApplications` and `ArrayViewAdmission` preserve existing value/plain
and extension/zero-arity/parenthesized indexing paths separately.

`QualifiedValueViewApplications.pw` takes no arguments (direct import) or
`ValueBarrel`, `ValueAlias`, `ValueQualified`, `ValueQualifiedAlias`. Repeat all
five with second argument `adapter` (`ValueDirect adapter` for the default).
Each must exit0, match its companion golden, and have empty stderr. Actual File
graphs contain I64 and Bool instances of one imported trait; the test checks
canonical owner, each argument and exact original source-token range through
direct Syntax and materialized Lower. CLI fixtures call both target bodies
from main. This covers selector formation, not final method dispatch.

`ModuleBindingPublicationControls.pw` runs without arguments (`MixedAlias`) or
with `MixedReexport`, `MixedNamespace`, `MixedAliasPrivate`,
`MixedReexportPrivate`, `MixedNamespacePrivate`, `SameNamespacePaths`,
`LocalImportedOverloads`, `ExternFunctionValueCollision`,
`ExternTypeTraitCollision`, `ExternSeparateNames`. All11 native invocations
must exit0 with empty stderr and the companion golden. They preserve individual
overload publication and defining-module authority, namespace identity dedup,
local/imported overload unions and unused extern-name collision admission.
Actual CLI executions additionally require11/22 for the three published routes
and same namespace,11/33 for local/imported union, and exit1 with the intended
Source diagnostic for rejected inputs. Source rejection followed by the existing
ORC diagnostic wrapper is not certification of that failure-transport boundary.

### Qualified type paths (manual)

`QualifiedTypeViewConsumers.pw` runs without arguments and with
`QualifiedTypeReexport`. It inspects qualified complete/zero-arity views and
associated projection storage, canonical owner and original source coordinates.
`QualifiedTypePathEdges.pw` runs without arguments and with `precedingExtension`,
`precedingTrait`, `missing`, `extra`, `named`, `suffixArguments`, `multipleSuffix`,
`extensionProjection`, `afterProjection`, `namespaceArguments`. These inspect
receiver/projection separation and require intended Source reasons on invalid
paths. Each native invocation must match its companion golden with exit0 and
empty stderr.

`MaterializedTypePathControls.pw` runs without arguments and with `legacy`,
`foreign`, `empty`, `shorthand`, `nominal`, `any`. It covers materialized rich
Lower, legacy projection with preceding rich extension, spanless lexical type
site authority, malformed-input refusal and non-interference. `shorthand` proves
only existing admission/name/ParamId receiver retention. The extra mode
`shorthandInstance` deliberately remains a manual RED (stdout0 versus golden1)
for com-amjl's complete-bound-instance retention; it must not be counted GREEN
or removed from that task's required work.

## Authored type provenance prefix

`AuthoredTypeUseProvenance.pw` follows the manual native procedure above and
compares stdout with its `.out`. It covers original occurrences/ParamIds, eight
lower entry wrappers across both adapters, nested/error scope restoration and
raw interning. It is not automatically discovered by the normal fixture suite.
`Lowered` is a provenance-store state, not successful source/proof admission;
common source-admission REDs and final-consumer tests remain required by com-amjl.

`AuthoredTypeUseRoles.pw` is a manual native assertion companion to provenance.
It verifies occurrence demand categories and nested/failure restoration, with
exact signature/default/body sites for free functions and methods in both AST
adapters. Its golden is `1\n`. It is not automatically discovered by the normal
fixture runner and does not certify admission, all delayed owners or consumers.

`AuthoredTraitQueryEnvironment.pw` is a manual native assertion test, using the
procedure above and golden `1\n`. Run it once without arguments and with each
of `conditional`, `matching`, `concrete`, `projected`, `projectedNoPremise`,
`conversion`, `callBoundary`, `boxingBoundary`, and `globalBoundary`. It checks that an unrelated
body cursor/substitution cannot change an explicitly scoped conformance query,
associated predicates use type equality rather than value conversion, and
valid generic calls/boxing retain their declaration premises at admission.
It does not certify source-view admission, all interface replay paths or
query-free interpretation of every frozen proof.

### Authored free-signature view admission (manual)

`AuthoredSignatureAdmission.pw` checks declaration occurrence receipts, exact
free-function signature slots, source trait-view admission and interpretation of
retained root proofs. Compile/link it by the manual procedure above. Execute each
of `unrelated`, `wrong`, `foreign`, `declaration`, `standaloneMissing`,
`standaloneDirect`, `direct`, `resultMissing`, `nestedMissing`, `nested`,
`concrete`, `slots`, `valueSlots`, `roles`, `inherited`, `extension`, `store`,
`standaloneReader`, `receiverTrait`, plus a run without arguments. Each must exit 0, match the
companion `.out` and have empty stderr. The standalone reader controls cover
absent callable constraints, a nonconforming substituted receiver, a mismatched
retained proof, and a valid prepared environment.

This harness is not discovered by the normal suite. It does not certify nested
projection consumption, other declaration owners, or the distinction between a
known Unit associated output and missing output. Public companion fixtures
`trait_view_admitted_signature`, `trait_view_unbounded_signature` and
`trait_view_wrong_instance_signature` are discovered by the normal suite.

`AuthoredNestedSignature.pw` checks recursive reading of retained free-signature
recipes. Execute without arguments and with `array`, `record`, `function`,
`siblings`, `short`, `missing`, `once`, `result`, `receiverView`,
`missingReceiverView`, `selectorArgument`, `receiverArgument`, and `proofBinders`.
Each must exit 0, match its `.out` and have empty stderr. These cover nested
projection outputs, exact result slots, independent receiver-view evidence,
missing evidence and one-step caller/proof-binder substitutions. They do not
establish absence of fresh queries deeper in shared proof replay, production
consumer migration, or complete associated-output substitution coverage.

`AuthoredProjectionBoundOrigin.pw` checks that one original where argument
remains Declaration-owned and its recipe is shared by repeated
parameter/result/body short projections. Execute without arguments and with
`value`, `default`, and `valueDefault`. `ProjectionBoundContextControls.pw`
checks later-clause dependencies, nonmember prefiltering, failed-context
restoration, and legacy synthesized subjects; execute `later`, `nonmember`,
`recovery`, and `legacy`. Each must exit 0, match its `.out` and have empty stderr.
The `whereSyntax` and `whereValue` modes check ordinary where-clause diagnostics,
frame restoration, and canonical trait owner publication.
The `requirementWhereSyntax` and `requirementWhereValue` modes check the same
boundary for raw trait requirements, including no partial trait publication.
The `requirementSignatureValue` mode checks the exact inherited trait
instance and distinct authored slots, then rejects a different instance.

`ImplProjectionBoundOrigin.pw` checks that two methods reuse a single
impl-owned bound argument in signature, body and default projections. Execute
`syntax`, `value`, `syntax shadow`, `value shadow`, `syntax later`,
`value later`, `value qualified`, `value recovery`, `value receiverRecovery`
and `value signatureAdmission`. The controls cover same-spelled binders,
later clauses, nonmember filtering, failed frame restoration and the value
adapter's legacy name-only rows. Receiver recovery checks that a rejected
impl cannot authorize its already registered member's implicit receiver premise.
Signature admission checks that the value adapter rejects a different exact trait
instance after accepting a method with the declared instance.

`RetainedMethodSignatureConsumers.pw` takes
`tests/fixtures/run/retained_method_signature.pw` and the standard-library
root with a trailing slash. It compares the selected call and body signature
against the admitted nested projection, checks the inout receiver, and
requires both consumers to reject a body environment with missing impl evidence.
Use `tests/fixtures/run/self_projected_iterable_runtime.pw` as the first
argument and `provided` as the third to check the selected placement and
reject missing receiver evidence or a foreign lexical Self.
For receiver equation replay, pass `receiverReplay`, either
`tests/fixtures/run/provided_signature_concrete_receiver_projection.pw` or
`tests/fixtures/run/provided_signature_nested_receiver_projection.pw`, and
the standard-library root with a trailing slash.

`AuthoredRecipeIntegrity.pw` checks the admitted constructor graph against the
canonical child visitor. Execute `valid`, `shape`, `term`, `label`, `forged`,
`foreign`, `representation`, `validRepresentation`, `representationSource`,
`derived`, `receiver`, `representationPosition`, `memoPosition`, and
`nestedReceiver`. Invalid metadata must be rejected in the Internal domain;
the harness itself must exit 0, match its `.out` and have empty stderr.

These remain manual diagnostics, not automatically discovered normal-suite
cases. The current free-signature increments do not certify other declaration
owners or whole-task completion. Scope and reproducible evidence are linked
from `docs/issues/com-amjl.md`.

### Prepared callable clause snapshots (manual)

`RetainedConstraintSnapshots.pw` checks the shared Function/Requirement clause
reader's immutable bound and publication environment. Execute without arguments
and with `foreignArgument`, `foreignReceiver`, `foreignProof`, `missing`,
`foreignFunction`, `foreignClause`, `duplicate`, `empty`, `unresolvedArgument`,
`unresolvedPredicate`, `wrongArgument`, `wrongPredicate`, `identity`,
`wrongSubject`, and `predicate`. Each must exit 0, match `.out` and have empty
stderr. The raw unresolved snapshots must remain Deferred even when existing
conformance could normalize them; they are internal integrity controls, not
successful source-admission examples. Valid replay preserves the same proof;
instance equality includes the saved full obligation and its original context.

Raw Arena issuance remains a trusted internal construction boundary. These
controls do not certify sealed issuance, all proof variants, deeper witness
normalization replay, or production source-signature consumer migration.


`RetainedConformanceClauses.pw` checks one retained conditional-conformance
clause using the selected witness's own binders and saved normalization equations.
Run without arguments and with `missingNormalization`, `wrongProof`,
`wrongSubject`, `missingPlan`, `noCallerMap`, `foreignMap`, `wrongSubstitution`,
and `cycle`; each exits 0, matches `.out`, and has empty stderr. Missing equations
cannot become Ready. Malformed evidence must return Err. Every case checks
admission-stack restoration and a subsequent valid read preserving the same
child proof. The no/foreign caller-map cases prevent source-bound re-grounding
from becoming an alternative authority.

This reader consumes an already admitted root. It validates the requested child
and shares clause interpretation with whole-plan admission; it does not reseal
raw plan publication or revalidate every unrelated sibling on every read.
Associated/Receiver replay, deeper predicate query removal and final consumer
migration remain separate required work in com-amjl.


`RetainedPredicateNormalizations.pw` checks selected associated outputs whose
normalization is needed only on the actual side. Run without arguments and
with `retained`, `missing`, `view`, `nested`, `nestedMissing`, `viewPlan`,
`viewPlanMissing`, `symbolic`, `wrongProof`, `wrongReceiver`, `wrongArguments`,
`wrongOutput`, and `cycle`. All exit0, match `.out`, and have empty stderr.
Missing/malformed actual-output evidence is rejected by both whole-plan and
clause admission. Normal recovery preserves the child proof and restores the
admission stack. `view` is a semantic visitor control; `viewPlan` additionally
covers an actual view-containing binding through producer publication and
both consumers. The raw reachable cycle check is distinct from plan admission.

`RetainedPredicateAcquisition.pw` runs without arguments and with `mixed`.
Equal raw projections acquire no equations. If only Second mismatches, only
its equation may be acquired; an already equal First is unaffected. This
controls structural non-interference, not a demonstrated user-program output
failure. Both cases exit0 and match `.out` with empty stderr.

The existing `AuthoredNestedSignature` once/proofBinders cases and the internal
`associated_condition_normalization_chain` fixture separately cover once-only
substitution and multiple saved equations. These tests do not adopt chained
projection surface syntax or certify the remaining proof consumers.

`RetainedProjectionPrerequisites.pw` checks saved-equation interpretation under an
explicit caller environment. The equation first passes its own original-binder
admission with the exact Function clause; this is an internal handoff control,
not a production producer/admission test for its entire parent witness plan.
The prepared context succeeds with the same retained prerequisite and output;
`missing` rejects rather than selecting a new globally available conformance.
Both cases recover through the valid context and leave the admission stack empty.
Run the no-argument and `missing` scenarios with the manual procedure above.
Associated row transport, Receiver migration and whole-task gates remain separate.

`RetainedAssociatedClauses.pw` checks the conformance producer's saved complete
pre-normalization bound, exact original clause/proof, and retained equations.
Run no arguments, `generic`, `nested`, `actual`, and `actualMissing`. The latter
two isolate projections appearing only in the selected child's actual output;
the pure boundary must reject equation removal and recover with the saved row.
Generic equations retain the impl's original ParamId. Closed clauses avoid
unrelated equations; the compatibility proof API and empty/absent publication
remain distinct. This representation increment preserves SourceAdmission inputs
and does not certify migration of the associated consumer to saved-only replay.
