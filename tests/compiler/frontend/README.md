# Frontend implementation regressions

These are internal tests, separate from the language fixture suite. Use the real
owning module and its imports: usually `src/Frontend`, with declaration/session
bridge probes rooted in their owning modules. Never compile an individual
`src/Codegen/...` part as a substitute: it lacks the owning `Comp` definition and
does not test the implementation in context.

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

`TypeHeadResolution.pw` directly checks `Comp.resolveTy` with lexical ParamIds,
shadowing, recursive substitutions, existential/applied heads, retained views,
contextual Self/Item, legacy zero-nameId input and out-of-range identities.
Use the manual procedure below: require exit0, empty runtime stderr and exact
`TypeHeadResolution.out`. It does not establish source-wide conformance or
replace the ordinary generic/associated-type language controls.

`TypeGroundHead.pw` directly checks `Comp.tyRefIsGround` head-only returns,
nominal canonical closedness and recursive ordinary/record/associated/view
children, plus deferred and failed projections. Its synthetic declaration
facets exercise structural queries, not executable source admission. Require
exit0, empty runtime stderr and exact `TypeGroundHead.out` with the same manual
procedure. This is a manual implementation test outside the normal fixture suite.

`OwnershipFailureDomains.pw` checks raw semantic ownership refusal/cache retention,
foreign-session/unknown-owner/out-of-range provenance, owned lazy repeated
requests and whole/eager checks. Require its exact `.out`, exit0 and empty
runtime stderr. It does not authorize raw mutable verifier state as source.

`InheritedDeclarationProgramMain.pw` is appended to a frozen DeclarationProgram
root and checks actual declaration Mid preparation. `InheritedCheckedProgramMain.pw`
is appended to CheckedProgram and collects whole-check/executable-preparation
outcomes, including inherited arguments, closures, provided methods and unused
parameters. These stages do not execute emitted code. The separate
`test-inherited-projection-admission.py` checks CLI/JIT; pass `--native-backend`
with a fixed archive to also link and execute AOT, checking actual stdout.
Fixtures and expected refusals remain strict even while a task is open.
`ExpectedResultBoundaryMain.pw` runs the real Direct contextual-result proposal
inside a frozen Frontend root. It checks rigid caller-owned replacements,
unknown binder completion, known-slot preservation and mismatched-result refusal.
`RecursiveExpectedResultMain.pw` runs whole Source checking in a CheckedProgram
root, comparing an inferred closure with an explicitly typed control; it does
not instantiate an unbounded recursive call. Both are explicit named entries
of the projection-members/run-query-private.py diagnostic driver and require
native exit0 with empty stdout/stderr. Neither replaces CLI execution gates.


## Manual execution procedure

`FreeCallVisibilityFailureDomains.pw` checks the three ordinary free-call
visibility failures, private retained evidence, raw/retry/drain preservation,
shared ownership observation and eager/session interpretation. It covers
Function/Global/Closure owners, expression0, unused lazy bodies, forged
kind/location/session/owner/arguments, changed/synthetic operations and
same-text ordinary reports. Its `.out` is the exact native execution golden.

`NonCallableBindingFailureDomains.pw` checks the actual selected-value refusal,
raw/cache/drain retention, owning lazy/whole/eager interpretation, and rejection
of foreign or mismatched owner, target, type and argument provenance. Require its
exact `.out`, exit 0 and empty runtime stderr using the procedure below.

`LexicalCallBindingFacts.pw` checks inferred, annotated and imported-alias global
callee identity in source templates, together with original pending type-cycle
and implementation-limit failures. It does not claim global callable execution;
that final consumer is tracked by `com-za4f`.

`GlobalCallableSnapshotOrigin.pw` checks the canonical callee snapshot's actual
global source and receiver identity, including same-type swaps, a forged origin,
overwrite and inout mutations, with a valid read control. Compile/link and
compare its `.out` using the manual procedure below.

`GlobalCallableDependencyOrder.pw` checks single-global and two-global callable
storage-read cycles, source-owner failure and repeated failure without publishing
an initializer plan. It does not certify transitive callee effects or the general
startup dependency graph (`com-fkxl`). Require exact `.out`, exit 0 and empty
runtime stderr.

`FreeCallCacheOutcomes.pw` checks that a nonstatic marker and an out-of-range
selected cache row cannot publish a source refusal. The existing ordinary
`callee_cache_declaration_growth` fixture separately preserves the observational
no-static answer across declaration growth. Require this manual fixture's exact
`.out`, exit 0 and empty runtime stderr.

Run `python3 -B tests/compiler/frontend/test-lexical-call-access.py --compiler
/absolute/path/to/plewc --out tmp/lexical-access` on one line to check argument
access recording for a function-value call. The driver creates isolated source
copies with a private observation shim and requires its deliberately omitted
recording control to fail. It exports no product test API and does not establish
complete function-value argument admission (`com-l4x2`).

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

`PublicSurfaceFailureDomains.pw` is a manual native diagnostic. It checks raw
analysis and repeated public rechecks stay Unclassified, fresh lazy/eager
admission classifies its own hidden-surface exposure as Source, and a public
type succeeds. Exit0 must match `.out` with empty stderr. This is not full-suite
coverage or authority to reclassify inference failures.

`MissingFieldFailureDomains.pw` is a manual native diagnostic. It checks raw
semantic cause/cache/retry/drain retention, receiver-owner and exact-operation
matching, foreign/unknown owners and forged operation rejection, owned lazy
retries, whole check and eager admission. Require exit0, exact `.out` and empty
stderr. It does not classify construction or record-pattern failures. Registered
`diagnostic_missing_field_lifetime` covers owned cause/location lifetime;
`field_unit_payload` preserves successful generic and record Unit-field reads.

`test-closure-capture-limits.py` is registered in normal and ASan B. Its
`fixtures/ClosureCaptureLimits/` inputs assert current implementation limits,
not forbidden source shapes. Six former reject fixtures remain covered, with
precise Limit/status/reason checks, deferred substitution cases and unrequested
lazy successes. The profile never widens the Source-only reject lane. Unique
capture source restrictions stay in `tests/fixtures/reject/`; future shape
support, including nested closures, belongs to com-b1ro.

`UniqueCaptureFailureDomains.pw` checks unique-capture refusal provenance through
raw repeated requests/drain and owned lazy/whole/eager requests. It covers
struct/enum/generic, mutable bindings and borrowed parameters, retaining unused
lazy success. Foreign sessions, failure indices, closure expressions and binding
targets cannot reuse a retained failure; equal-text Internal reports remain
Internal. Run with the manual compile/link procedure and require its exact `.out`.

`NestedClosureLimitDomains.pw` checks the recorded nested-closure capability
failure through raw retry/drain and owning lazy/whole/eager requests. It also
reaches the direct executable-scan fallback and requires Limit there. The unused
lazy body stays unrequested. Require exit0, exact `.out` and empty stderr.

`EmptyArrayCandidateContexts.pw` reads a real File with Std, repeats scalar/Array candidate comparisons for direct, block and branching operands, requires no expression-type or callee-cache publication, then checks the committed source call identities. Require exact `.out`, exit0 and empty runtime stderr. The ordinary `empty_array_overload_context` fixture separately checks AOT/JIT execution.

`MemberCandidateIdentities.pw` loads real provided declarations/instances, then registers implementation-only aliases to exercise duplicate collection through bare, view-set and single-source lookups. Two copies remain one candidate; a third different declaration or proof instance must remain ambiguous. Raw alias lookups must not gain Source authority. Require exact `.out`, exit0 and empty stderr; this is not source-language alias syntax.

`NumericCandidateContexts.pw` compares real File/Std integer-wrapper candidates without publishing operand types or a callee, then checks repeated ambiguity refusals and typed/local/mixed-branch context preservation. Its run fixture separately verifies evaluation order and final execution. Require exit0, exact `.out` and empty stderr.

`ProvisionalCallAuthority.pw` requires a real selector-only mismatch to preserve its diagnostic while leaving no selected-callee cache, including failed retries. Successful numeric, Array and typed-closure generic calls separately retain Selected entries. Compile/link manually and require the exact `.out`, exit0 and empty stderr.

`test-array-context-failure-domain.py --carrier PATH --output DIR --modes check aot orc`
checks producer-owned failure-channel classification for real empty-array/non-array
refusals, with three valid Array context controls. It uses generated inputs in the
explicit output directory and fails on off-target diagnostics as well as wrong
domains. This is a focused manual diagnostic, not registered in the normal suite;
it does not replace native Raw/event-mutation/cache/lifetime boundary controls.

`ArrayContextFailureDomains.pw` checks the low-level Unclassified/owned Source
boundary, active-owner Raw recursion, retained request/cache/retry/drain, cause
mutations/foreign sessions/plain reports, real diagnostic-only free/member/
associated/extension frontiers, and exact Index/Factory operand provenance.
Index read mutations are distinct from detached IndexSet writeback. Require
exit0, exact `.out`, and empty runtime stderr; apply ASan/LSan to this native
internal fixture for failure-event lifetime checks.

`PhaseTrace.pw` preserves the phase-monitor protocol: trace disabled/enabled,
empty labels, zero/multi-digit/U64-max counters and stride hit/miss. Compile
against the implementation under test, link normally, and compare both `.out`
and `.err` byte-for-byte. Whole-source traced/plain LLVM and phase-event
comparisons additionally cover the private lowering/verification progress paths.

`PreparedContextualOperands.pw` tests raw and partially prepared aggregate
constraints without publishing source facts or callee authority. Its `.out`
covers nested Arrays, structural records, fixed typed mismatches, partial
closure signatures, root generic inference, view identity, and function
arity/labels with rigid caller binders. Repeated probes preserve parent and
child terms, cache and template counts. Compile/link the real frontend and
compare stdout byte-for-byte; stderr must be empty.

`ProvidedCandidateProofAdmission.pw` checks that copied provided methods with a
missing conformance proof cannot enter as matching candidates, while the valid
trait-subject path remains selected for distinct nominal receivers and the
existing generic/newtype fixture prepares successfully.

`AssociatedReceiverPendingArguments.pw` compares an omitted generic receiver,
its explicit concrete instance and the declaration receiver equation. Omitted
arguments remain candidate-local context obligations; they are not a completed
zero-argument instantiation. Both tests are manual native frontend diagnostics:
compile/link against the implementation, require exit0, exact `.out` and empty
stderr. `PreparedContextualOperands.pw` also covers raw non-value return branches
and candidate-owned deferred projections, including rigid caller mismatches.

`BranchCandidateFrontiers.pw` is a manual native public-ranking test of first-normal branch readiness: late/early typed closures and numeric literals, source-nonnormal branches, a unique contextual candidate, independent generic argument completion and raw nominal values. Repeated probes preserve every expression fact, selected-callee cache, closure descriptor and template count. Compile/link the actual frontend; require exit0, exact `.out` and empty stderr.

`test-provided-source-endpoints.py` is a normal-suite private API gate. It copies
exact compiler source and appends `ProvidedSourceEndpointMain.pw` to Frontend's
own module, without rewriting or exposing any production declaration. It checks
source/implementation endpoint positions, pinned-terminal failures, distinct
generic substitutions and retained assumption/supertrait roots. The repeated
owner/edge injection is a raw position control, not evidence that a source
program with that graph was accepted. Public multi-module provided-helper
fixtures and MemberCandidateIdentities cover actual candidate lookup and final
execution separately. Require exit0, exact `.out`, empty native stderr and source
immutability; compiler/link stages use the shared semantic-progress supervisor.

The endpoint gate also compares the shared signature/obligation receiver argument
vector on actual Box[I64]/Box[String] copies, for helpers and authored conformance
implementations. It covers strict/zero/symbolic receiver failure, foreign helper
proof, conflicting nonzero ParamIds, legitimate receiver-free slots and retained
argument completion versus admission. Concrete retained contradictions are
Internal; symbolic terms stay on the existing readiness path. The generic public
fixture's associated projection is asserted in a real StaticMethod.Provided
saved argument before full frontend checking. Fixture/std/dependency and support
input hashes accompany the exact source snapshot.

`FreeCallAmbiguityFailureDomains.pw` and `StaticMemberAmbiguityFailureDomains.pw` have exact `.out` goldens for manual native checking of retained negative selection. They preserve ordinary free/static/associated ambiguity and add numeric free/member/extension-view controls. Require exit0, exact golden and empty stderr. The assertions cover original operand locations, kind/path/line and owner/session/argument mutations, Raw versus owned adapters, synthetic origins, retries/drains and absence of successful parent result/callee publication. The malformed-cast query Report passthrough is distinct from the equal-text Internal observer control. Public rejection fixtures are discovered separately by the normal/ASan profiles.

`GenericCallConflictMain.pw` is a private-boundary probe: append it to an exact
copy of `src/Frontend.pw`, without widening production visibility. It exercises
Raw and source-owned typed/prepared Conflict decisions, retained known bindings
and candidate role, foreign metadata, changed arguments, synthetic operations,
equal-text Internal reports, drain retention and absence of parent publication.
Require native exit 0 with empty stdout/stderr. Whole-session consumers and
language fixtures are separate controls; this probe alone cannot close the task.

`GenericCallConflictFailureDomains.pw` checks typed, partially contextual closure
and named-factory conflicts through raw cache/drain, owned lazy repeated body
requests, whole-session failure retention and fresh eager checking. Its `.out`
is the exact 12-line native golden. Run it with the manual procedure above;
public language and private provenance mutation probes remain separate controls.

`CandidateReceiverRankMain.pw` checks that a bare generic receiver with
conflicting operands remains a diagnostic candidate instead of invoking strict
selected-call inference. `ArrayContextScopeMain.pw` checks independent request
identity and Regular/Diagnostic/Unavailable Array admission, including Raw and
foreign inputs, frontier bounds and recursive/return-context preservation.
Append each to a frozen `Frontend.pw`, or combine their helpers with
`GenericCallConflictMain` under one entry. Require exit0 and empty stdout/stderr.

`OpaqueNumericFailureDomains.pw` is the whole/eager consumer regression for
opaque caller type parameters and provided Self with integer/float literals.
Its `.out` is the exact eighteen-line success golden, including Raw repeated
requests/drain and source-owned lazy retries followed by whole-session failure.
Private provenance mutation controls remain separate.

`LexicalTypeBinderBinding.pw` checks the actual function/method/nominal type
binder classification in the presence of a same-named module callable, including
module function target0. Run from a frozen compiler root; require native exit0,
`ok` and empty stderr. The normal run fixture
`lexical_type_binder_callable_receiver.pw` also checks bound dispatch, an outer
binder used inside a closure, local closure priority and the ordinary global call.

`MissingOperatorFailureDomains.pw` checks actual missing operator selection in
function, closure and global owners through Raw cache/drain, owned requests and
whole/eager consumers. Require its twelve-line golden. `MissingOperatorMain.pw`
is appended only to a fresh Frontend snapshot and checks Lower serial/span,
operation/operand/owner mutation, Raw/foreign requests, unknown terms/Core,
ambiguity and failure/cursor lifetime. Require native exit0 and empty streams.
`tests/tooling/test-missing-operator-origin.py` is a normal-harness gate for
concrete missing selection, lazy non-demand and preserved normal dispatch.

`OpaqueBlockFailureDomains.pw` extends the same owned/Raw consumer guarantee
to integer, float and nested block results; require its exact twelve-line golden.
`tests/tooling/test-opaque-block-origin.py` is registered in the normal harness
and checks demanded and unused bodies plus valid concrete/generic value contexts.
Successful check/build may retain existing standard-library warnings.

`OpaqueNumericMain.pw` is appended to an exact Frontend source snapshot. It
checks Raw versus private requests, retained literal/expected identities, foreign
metadata, recorded synthetic copied-span nodes, serial/span/kind mutation,
Internal same-text reports, drain and both syntax Lower entry contracts. Require
native exit0 and empty stdout/stderr; do not expose private production APIs.

`SourceTypingFailureDomains.pw` checks unresolved empty-array source typing
through Raw cached retry/drain, owned lazy request then whole check, fresh whole
and eager checking, nested closure failure and global initialization. Require
exact `SourceTypingFailureDomains.out`, exit0 and empty runtime stderr.
`SourceTypingMain.pw` is appended only to a fresh private Frontend diagnostic
snapshot. It checks Raw/request/owner/session/serial/span boundaries, missing
facts, missing completion and obligation discharge before fault injection.
Require exit0 and empty stdout/stderr; it does not widen product visibility.
`tests/tooling/test-source-typing-origin.py` separately exercises the actual CLI
channel in check/AOT/ORC, unused lazy bodies and typed-array language controls.
The normal harness registers this inexpensive CLI gate; the private/native
implementation probes retain their separate manual execution contract.


### Index requirement refusal ownership

`SourceIndexMain.pw` is a private same-module probe appended to a frozen Frontend
snapshot; do not expose its internal authority constructors. It distinguishes
actual read/write Lower receipts from public synthetic builders and checks
request/event/owner/serial consistency, including an optional failed-call owner.
`SourceIndexFailureDomains.pw` and its golden exercise raw versus owned failure,
retry/drain, whole/eager requests, closure and global lifetime. The copied
`fixtures/IndexRefusals` inputs are runtime File reads and must be included in
input fingerprints. CLI acceptance and non-interference are also covered by
`test-index-requirement-origin.py` and `test-dynamic-protocol-requirement.py`.

`NamespaceDeclarationMain.pw` is appended to a frozen Frontend root to exercise private Lower Field / lexical namespace normalization receipts. It checks original versus synthetic/replaced expressions, request and owner boundaries, qualification identity/module/kind, and failed-builder retention. `NamespaceCallableValueFailureDomains.pw` exercises the public Raw, owned lazy, whole and eager consumer paths for function/closure/global owners, retry and diagnostic drain. Its `.out` is the native execution golden; both use `fixtures/NamespaceDeclaration/`. These are focused manual frontend diagnostics, not language fixture discovery.

`TypeVisibility*Main.pw` are private same-module templates appended individually
to a frozen Frontend root. They cover Lower occurrence provenance, declaration
and body slots, actual implementation receiver binding, retained normalization,
failure caches and exact owning consumers; `InventoryMain` also reconciles the
actual declaration occurrences with registered roots. Use the native runners
linked from `met-un2r`, require exit0 and empty stdout/stderr, and keep product
APIs private. These diagnostics do not replace the public missing-import CLI
controls or certify task completion by themselves.

`test-discovery-membership.py --carrier PATH --out NEW_DIRECTORY` executes real
check/AOT/ORC controls for shared membership admission. It creates single-cause
source graphs, preserves the private failure channel and source fingerprints,
and verifies legal root reuse and multiple-annotation aggregation as well as
conflict rejection. It is a manual focused gate, not the complete normal suite.
`DiscoveryMembershipMain.pw` is a private-root diagnostic appended to the actual
Frontend module; it checks raw core refusals, source authority, both diagnostic
origins and generation suppression. `DiscoveryMembershipFailureDomains.pw` is
a standalone service probe for retained failed-session diagnostics. Their native
snapshot commands/results are linked from issue met-iv6d's evidence.

`test-declaration-labels.py --carrier PATH --out EXCLUSIVE_DIR` compares local
and unused imported nominal declarations in check/AOT/ORC. It requires Source
rejection for duplicate struct fields, variant names and payload labels, and
keeps legal names in separate variants/types and generic declarations accepted.
`DeclarationLabels.pw` exercises the dependency-light name comparison core,
including malformed ranges; run it with the selected carrier's `--run`.
These focused controls do not certify the whole compiler or declaration-owner
authentication, which additionally needs private/native admission controls.

`test-parameter-group-admission.py --carrier PATH --out NEW_DIRECTORY` is a manual declaration-admission matrix (114 cases): named/requirement binding-name uniqueness in local/imported declarations under check/AOT/ORC, including suppressed labels and legal explicit shadowing. It requires the binding-name diagnostic and Source failure domain; closure and function-type admission have separate owners.

`ParameterGroupAdmissionMain.pw` is a manual private-root diagnostic: equal-byte/zero-nameId comparison, distinct suppressed names, malformed ranges/spans, Raw registration/verifier/public Syntax decoding, Source/previous locations, and failed Func/trait publication. `ParameterGroupFailureDomains.pw` tests retained refusals across repeated session-open attempts. Run with the versioned declaration-parameters/run-private.py (optional `session` argument); both require exit0 and empty native stdout/stderr.

`test-closure-parameter-admission.py --carrier PATH --out NEW_DIRECTORY` is a
manual96-case check/AOT/ORC matrix for closure group admission, contextual and
shadowing positives, local/imported bodies, globals/defaults/provided/generic
owner paths. `ClosureParameterAdmissionMain.pw` is a private-root native probe
for pre-publication checks, malformed input, cache/Raw/forged/foreign identity,
actual cross-owner transplantation and failed-builder proof retention.
`ClosureParameterFailureDomains.pw` checks Raw preparation/drain and owned
service retries, whole and eager checks with exact previous-location notes.
Use the declaration-parameters/run-closure-private.py driver (`session` for the
latter). Both native probes require exit0 and empty stdout/stderr.
