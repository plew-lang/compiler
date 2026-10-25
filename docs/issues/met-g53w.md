---
id: met-g53w
status: in_progress
deps: [com-qlnc]
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
rejected the existing Optional API. [com-qlnc](com-qlnc.md) remains the open
canonical specification/design prerequisite. Do not implement the superseded
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

## Current Planning Boundary

The user resolved the API/rule choice in favor of bounded structural proofs
and preserving Optional.unwrapOr. Await com-qlnc's actual spec/design update and
independent review before resuming implementation. This request updates task
contracts only. Existing WIP routes ordinary, trait, provided-extension and
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
