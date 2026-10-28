---
id: met-g53w
status: in_progress
deps: [com-qlnc, met-tfbl]
links: [com-y8l4]
created: 2026-10-25T12:03:16Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-ucze
tags: [frontend, generics, verification]
---
# Unify overload declaration admission with bounded structural proofs

## Confirmed Contract and Evidence

P2 finding from independent review of com-ra96/com-zy6r/com-y8l4.
This is a newly recorded ordinary/trait inconsistency, not a regression in that
repair. At the recorded baseline spec/07 required matching generic arity and
positions, while spec/08 gave trait requirements the ordinary rules. The user
selected a structural refinement after the strict fixed-type rule at cc13283
rejected the existing Optional API. [com-qlnc](com-qlnc.md) has now passed two
independent documentation reviews at spec5bd65a5 and the companion design update.
Do not implement the superseded
plan of imposing the old generic-shape restriction on trait requirements.

```plew
trait Picker {
    fn pick[T](value: I64, other: T)
    fn pick(value: Bool, other: Bool)
}
fn main() {}
```

Old candidate bin/plewc-dynamic-argument-admission SHA256
23f7d582501b394f3390fbd9e2ebd577cc9892cf6c7de4d5129b70ae5f14b583
and WIP bin/plewc-overload-identity-wip SHA256
b0f8cccb49deb0dc3fb271c62b1e044f8a4201b3f0216f6958987ddd6a9429a5
both accept this unused requirement group with --check exit0 (contrary to the
baseline written rule; acceptance is intended under the new canonical rule).
The equivalent ordinary free declarations both reject with the spec/07
same-type-argument-count/generic-positions diagnostic. A trait group with
matching generic shapes, differing concrete first arguments and alpha-renamed
method binders accepts on both. Six bounded --check commands; no application
or invalid dispatch was executed. Full sources, exact commands/hashes/results
are retained in meta/evidence/existing-feature-conformance/source-owner-facts/
overload-identity-checkpoint.json; raw scratch is meta/tmp/
phase3-overload-identity-repair/generic-shape/results.json.

## Exposed Design Defect: Fragmented Admission Authority

This is not merely an incorrect valid/invalid result or a missing trait check.
The complete overload-admission contract is scattered across entry points:
Lower/Registration.pw::checkFuncRegistration applies sameGenericShape outside
callableFormsMayOverlap, whereas Check/Duplicate.pw::checkDuplicateTraitReqs
calls only callableFormsMayOverlap. A shared overlap helper did not prevent the
callers from implementing different acceptance contracts.

The required repair centralizes responsibility for that complete decision.
Adding an equivalent condition to the trait loop, keeping parallel predicates
in sync, or adding an assertion that compares independent authorities is not the
finite end state. This causal finding is based on the inspected paths and the
ordinary/trait check contrasts above; it does not assert that every callable
entry has already been audited or that unrelated declaration rules are identical.

## Design Boundary and Required Finite End State

After com-qlnc closes, implement its bounded structural distinguishing-position
contract through one source declaration-admission authority. Keep the receiver's
parameter environment common across compared methods, but candidate-owned
method parameters lexically distinct. A parameter merely coming from the
receiver does not prove it different from another type for all receivers.
Use the specified type structure, consistent substitutions, occurs check and
retained equalities; do not solve general where bounds to discriminate candidates.
Concrete-type differences remain sufficient but are not mandatory.

Preserve default omission and existing selector/origin/capability boundaries.
Remove the old generic-shape restriction and independent acceptance predicates;
neither the old unifier's binder-by-position shortcuts nor the strict WIP's
closedness gate implement the selected contract. Audit the existing structural
relation against lexical binder identities and cyclic substitutions before reuse.

Reject invalid groups before successful declaration/source publication even
when unused. Preserve selected identity/evidence through generic and existential
consumers, without trait-only inference, late source reselection or weaker full
argument checks. Trace successful admission and failure to actual retained use.

Cover different generic counts/positions, pairwise groups, structurally proved
distinction versus possible overlap, aliases/Self/projections, defaults, ordinary/trait consistency,
explicit type arguments and ambiguous calls. Perform affected execution modes
and independent finite completion review. Final G1/G2a/G2b/G3 remain required;
no threshold, verifier or test weakening is authorized by this contract update.

Completion must include an entry-to-authority audit covering free functions,
methods, associated functions, explicit and default/memberwise factories,
trait requirements and default-omitted callable forms. Record the actual
producer/decision locations, remaining legitimate domain-specific checks,
removed independent predicates and successful-admission boundary. All supported
entries must use the canonical overload rule before reporting declaration
success. Paired valid/reject controls across applicable declaration kinds must
demonstrate agreement, including unused declarations; call/runtime controls
must retain the selected identity through final use. Matching outputs for the
original counterexample alone do not establish this architectural completion.

This is distinct from com-y8l4's canonical duplicate-signature identity and is
linked for coordination, not imposed as an invented sequencing dependency.
The source-selection area met-ucze and G1 require this separate repair.

## Executable Repair and Acceptance Cases

1. After com-qlnc closes, construct the comparison environment from canonical
   receiver/trait identity and its parameter mapping. Unify the receiver domain
   before comparing arguments, so its shared parameters denote the same type
   across candidates. Keep each method's own ParamIds independent, including
   alpha-renamed, reordered and different-length binder lists. Remove the old
   assumption that equal binder-list positions identify one logical variable.
2. Replace the strict WIP's typeIsClosed-only discriminator in
   callableAdmissionTypes/callableFormsConflictAt with the documented bounded
   structural proof. Maintain a consistent substitution and finite occurs check
   inside each distinguishing-position query. Preserve different nominal heads,
   function/record structure, nested arguments and known projection equalities;
   do not unfold recursive nominal fields or invoke general trait satisfiability.
   Do not add an Optional-specific exception or rename its public operations.
3. Return a justified distinction, possible overlap, or an unproved/limit result
   with provenance. Unknown/AnalysisLimit is not proof of distinction or overlap.
   Receiver-domain unification may share the existing primitive only after its
   lexical identity/occurs behavior is audited. If that primitive changes, cover
   its affected conformance/witness callers too; do not repair overloads by
   silently changing the meaning of those other consumers.
4. Keep the WIP's legitimate shared-admission wiring only where it satisfies the
   final design: ordinary registration, trait groups, provided-extension domains,
   default/memberwise signatures and later registrations. Enumerate actual entry
   and success locations, remove independent acceptance gates and verify common
   omitted forms. Preserve one distinguishing position per candidate pair;
   cross-position constraint interactions alone do not expand acceptance.
5. Reclassify WIP fixtures by the final contract before testing. Require receiver
   T/fn()->same T and Array[T]/Box[U] to distinguish; receiver T/I64, A/B,
   Array[T]/Array[I64] and candidate-owned T/fn()->independent U can overlap and
   must reject without another discriminator. Exercise shared receiver versus
   independent method binders in normal/trait/factory routes where applicable,
   defaults that remove a discriminator, aliases/projections and unused groups.
   Restore real Optional.unwrapOr eager/lazy success and conditional execution
   controls, including generic callers. A standard-library failure cannot count
   as a successful application reject test.
6. Follow accepted declarations through saved source selection, generic/any
   consumers and native/JIT execution with full argument validation. Record a
   fresh build, fixed inputs, targeted success/reject/mode results, same-source
   performance comparison and independent task/area completion review. Keep
   formal G2a/G2b/G3 separate; no earlier fixed-only review/build closes this task.

## Current Planning Boundary

The user authorized phase-three resumption. The structural spec/design update
has passed independent review; implement that now-canonical contract while
preserving Optional.unwrapOr. Existing WIP routes ordinary, trait, provided-extension and
memberwise entries through callableDeclarationConflict, removes sameGenericShape
and callableFormsMayOverlap, and defers initial group admission until nominal
identities resolve. Its strict fixed-type discriminator is superseded, so this
WIP is not an implementation of the new structural contract or an accepted fix.

Build 20261025T153817-build-3074d1 passed using carrier23f7 with 6086 fixed
inputs. Candidate bin/plewc-overload-admission SHA256
508b1bdae60984f9aea6e9516c2b4f8265e73bd7bef80ec913b92dba6725d599
rejects the ambient std Optional.unwrapOr overload pair at Lang.pw:88, even for
an empty main. Old23f7 accepts that same empty main/std. This is a conflict
between the superseded fixed-type rule and an explicitly promised public API.
The chosen resolution changes the general structural rule, not that API.

Targeted native/reject slice failed before meaningful application verification;
apparent reject passes from the std error are not successful target evidence.
New positive fixture1 also had never-green unsupported factory[T] syntax, now
corrected to a generic impl factory after slice exit. Compiler source matches
the successful build; this fixture is the sole postbuild input delta. No new
performance, fixed-point, full suite or implementation acceptance is claimed.

Fixture changes made under the superseded fixed-only rule: overload_generic_shape_mismatch
moves from reject to run because fixed first types distinguish it. The former
run overload_generic_nonoverlap_cycle (introduced to exercise finite structural
unification; source retained at12e819f6) and factory_receiver_type_overload
(created202fe764 to ground receiver-dependent signatures) move to reject: neither
pair has a fixed discriminator. Their original purposes/source and proposed
new outcomes are retained in the stopped receipt; these changes remain WIP
until each case is classified against the structural contract and freshly
verified. In particular, the new dependent-only rejection fixtures cannot be
retained merely because both signatures mention parameters: Array[T]/Box[U]
should be accepted, whereas T/I64 can overlap. Re-evaluate the whole fixture
change set from original intent; do not mechanically preserve WIP outcomes.

Existing return-owner/dynamic-argument closures retain their finite scopes. The
three preceding overload repairs and this implementation remain WIP. Receipt:
meta/evidence/existing-feature-conformance/source-owner-facts/overload-admission-stopped.json.

## Current Review Boundary

The three earlier reviews accepted the strict fixed-type proposal, not the
structural contract now selected. Their historical reports and the stopped
probe remain in Git/evidence. com-qlnc requires a new independent review of the
actual specification/design changes, including standard APIs and shared versus
independent binders. This task then requires producer-to-final-consumer target
verification and its own independent completion review. A successful build of
the strict WIP, the old public API's existence or a new predicate in isolation
cannot close this task or certify phase three.

## Structural Implementation Checkpoint

The structural implementation uses canonical lexical ParamIds and receiver-domain
substitutions, copied independently for each argument-position proof. It uses
canonical head/child/label traversal for nominal/function/record terms, consistent
substitution within one position and an occurs check; unresolved projections are
unproved. The previous directional witness matcher is not a disjointness oracle:
its positional alpha shortcuts cannot establish this contract. Existing witness
consumers remain unchanged in this slice. Obsolete receiver-overlap/selector
helpers are removed rather than left as alternative admission predicates.

The independent intermediate soundness review found no concrete false-Disjoint
counterexample, but required retaining Unproved to diagnosis and avoiding repeated
default-omission paths. The follow-up keeps Possible/Unproved/AnalysisLimit distinct
and memoizes the finite (left-position,right-position) selector state per pair.
No additional rule-count, elapsed-time or user-adjustable acceptance budget is added.

Initial build 20261026T010113-build-0743b7 passed after the failed prior build's
missing root imports were fixed. Native slice restored std Optional.unwrapOr and
passed the preceding existential/array/trait-signature inputs. New generic-shape
calls still failed because ordinary ranking compared abstract generic parameters
as concrete names, while method ranking skipped abstract expected terms. The repair
extracts the existing trait candidate-local inference/full-type algorithm into
callableParameterTypeMatchRank and connects normalized free/method/trait entries.
Candidate inference stays transactional; where bounds do not rank candidates.
No successful source selection is replaced by a later overload search.

The new never-green tests also inadvertently used explicit free-call type argument
syntax. That feature is already classified as absent/future by [com-uutc](com-uutc.md),
not an admitted feature being repaired in phase three. Positive calls now use the
supported inference form. The new explicit-count reject was removed: rejection as
an Index operation did not test selected-call arity and must not count as evidence.
Preserve spec06's explicit-call contract; do not implement that excluded feature
or claim its semantic arity/bounds gate tested here. Cover inference/bounds failure
and no reselection on supported calls instead. Historical receipts retain the
initial failed inputs; they are not current acceptance evidence.

This remains implementation WIP pending the fresh build, target modes, performance
comparison and independent completion review. No task/area/full gate is closed by
this intermediate structural review or initial slice.

## Resumption Results and Required Task-Assignment Stop

Fresh build **20261026T010812-build-b038fc** passes using carrier23f7 with fixed
inputs. Saved candidate **bin/plewc-overload-structural-shared**, SHA256
**e6ff9d19d8501b32422f7c7bc1c8e0a8fc189105015fef6d67bc00347cdf0a6d**,
passes the complete compiler-source --check smoke. The target slice passes
11/13 native cases and16/16 rejects (the latter include6 existing missing-give
controls). The pairwise generic shapes, inferred free calls, standard eager/lazy
Optional controls and prior existential/array/trait signatures execute successfully.
Unknown projections and depth-limit rejects have distinct required diagnostics.
No performance, fixed-point, full-mode/full-suite or completion acceptance is claimed.
Only a nonsemantic method-inference comment was corrected after the fixed-input build.

Two positives remain failing; neither is reclassified as a successful rejection:

1. An app-level free function named fallback makes std Optional.unwrapOr's local
   closure parameter call fallback() fail visibility. The isolated standard-shadow
   input fails --check on both old23f7 and newe6ff. Check/Visibility.pw::
   checkExpressionVisibility(Expr.Call) classifies a call with global spelling
   searches without consuming its lexical/dynamic binding. This is a separate
   semantic authority, not an overload constraint or a reason to rename a user
   function. The independent architecture review finds it outside closed com-cwu1
   and the finite Verify/Call repair recorded in com-qb05. A new finite repair
   must own lexical call visibility from binding through all modes/final use,
   remove the global-name reclassification, retain real import failures and
   include shadowed parameter/local/global closure controls. Investigation is
   assigned to [met-tfbl](met-tfbl.md), with met-ucze, com-qb05 and G1 depending
   on its evidence-backed disposition. The user requires thorough investigation
   before selecting a repair; implementation has not started.
2. Boxing Worker as any Picker fails when Picker has an unused generic requirement,
   even when only its nongeneric overload is called. An isolated single generic
   requirement reproduces the same unbound implementation parameter error on
   old23f7 and newe6ff. The independent review found no precise recorded exclusion
   for this formation case; generic existential invocation is not thereby assumed
   implemented. Save a finite investigation/classification task, separate unused
   formation/nongeneric member availability from invoking a generic requirement,
   and assign a bounded repair or evidenced future-feature disposition. General
   com-uutc wording is insufficient evidence to dismiss this actual failure.

The initial task-omission stop was recorded before assignment. The user has now
requested an investigation-first ticket: [met-tfbl](met-tfbl.md) owns lexical
priority, candidate/failure handling and diagnostic isolation, including deleting
an optional inaccessible-name hint if appropriate. This task depends on that
investigation; its repaired disposition must precede completion. Keep met-g53w
and all dependent areas/gates open. No implementation repair is claimed. The intermediate
soundness review's Unit matching concern was also probed: a Bool/Unit method group
with a literal Unit argument passes --check on both carriers. This check-only
contrast does not prove all Unit contexts; com-sby0 retains the broader audit.

Durable receipt: meta/evidence/existing-feature-conformance/source-owner-facts/
overload-structural-checkpoint.json. Its exact inputs and failed sources are the
handoff boundary; do not turn partial slice success into phase-three completion.

## User-directed Investigation Boundary

Do not presume this is only a missing closure exemption or only a hint defect.
The user requests a thorough investigation of multiple possible responsibility
failures before repair. met-tfbl distinguishes confirmed misrejection from
unproven priority/fallback defects, inventories scoped and unrestricted searches,
checks genuine error versus optional hints, and produces finite follow-up tasks.
Removing a hint is permitted; removing legitimate visibility enforcement is not.
The unrelated generic-requirement boxing observation remains unclassified here,
and was not bundled into the newly requested lexical/visibility task.

## Explicit Existential Capability Overload Oracle

Batch0064 adds exactly run/overload_existential_capability_distinct.pw/.out for finite source-oracle reconciliation. Spec08:375 allows any sendable P to erase guarantee to any P; spec07:109 separates valid declaration pair from call uniqueness and adds no specialization. plain call only fits ordinary parameter, safe call fits both unless an already adopted selection rule resolves it. Recover canonical grounds before preserving expected2 or changing test; current exact-before-erasure implementation is not normative evidence and no compiler bug was reproduced. Preserve declared capability distinction, directional erasure and ordinary unambiguous call. Existing overload_shared_declaration_admission unused generic requirement box formation remains explicitly unclassified above, not blanket future unsupported invocation scope.
