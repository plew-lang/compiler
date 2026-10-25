---
id: met-ia09
status: open
deps: [com-v2xk, com-yojf, com-072n, com-3qne, com-6cw6, com-cwu1, com-ra96, com-y8l4, com-sby0]
links: []
created: 2026-10-13T01:40:08Z
type: epic
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, generics, verification]
---
# Close saved constraint evidence through callee environments and final use

## Current Review Reopening

The fresh specification-first [com-9hf7](com-9hf7.md) review found required
existing-contract gaps. This task/area is reopened for [com-cwu1](com-cwu1.md), [com-ra96](com-ra96.md), [com-y8l4](com-y8l4.md), [com-sby0](com-sby0.md).
Prior scoped controls and accepted repairs retain their exact inputs, but do
not certify this newly evidenced boundary. Follow these finite dependencies
through source production, successful publication and actual final use, then
independently re-admit the affected contract. No new language feature is
required; no prior gate is attributed to a repaired future candidate.

## Bounded Execution and Gate Ownership

This is an area epic, not one executable multi-week task. Its current bounded
work and real prerequisites are tk dependencies under the
[parent policy](met-si6j.md#bounded-task-policy):

- [B3](com-v2xk.md): exact callee clause/ParamId/inherited environment closure.
- [B4](com-yojf.md): bounded universal nominal proof disposition.

Close this area's exact existing contract after required children/repairs and
their scoped fresh verification. The final frozen candidate normal/gen/deps/full
sanitizer/fixed-point/performance obligation is explicitly owned by
[G2a](com-p5um.md)/[G2b](com-9l3b.md) and cannot be waived when this
area closes. Historical checkpoint gates are not current-candidate certification.
Earlier current/next/WIP observations refer to their named revisions; the bounded
children reconcile what actually remains before any repair. No new meaning or
unsupported feature is authorized by this allocation.

## Scope and Completion

Included repair under [met-si6j](met-si6j.md) and [com-604k](com-604k.md), on the
currently provided callable surface. Close source construction and owner admission
through explicit substitution, actual callee environments, and final Mid/backend
use. Checks and private storage alone are insufficient: remove the replaced
lookup/decision paths and structurally close construction authority. Do not add
allowunique, unsupported opening, a runtime trait solver or a new ABI here.

The parent retains all eleven completion criteria. Worklog owns the selected
source/carrier, active handles and gates; the
[retained evidence index](https://github.com/plew-lang/meta/blob/main/evidence/existing-feature-conformance/source-owner-facts/README.md)
owns bounded results. Earlier implementation sequences and measurements are Git
history, not additional pending work or proof of current-tree readiness.

## Evidence Contracts

- Distinguish Existence, SourceAdmission and MemberDispatch at one common query.
  Source admission requires a unique specification-valid declaration path even
  for an unused bound or empty trait. Equal executable endpoints do not merge
  different source paths. Canonical representations of an exact duplicate
  authored premise are not additional paths.
- Preserve source/view precedence and conditional applicability. Select the path
  before checking associated outputs; an output mismatch cannot reopen a shadowed
  source. Missing, Found and Ambiguous are typed outcomes. An exact opaque caller
  premise keeps its authority; a stronger derived output cannot replace it.
  Normalize empty positional input by declaration arity at the query boundary.
- Bind callee conditions by original declaration-bound identity. Function,
  Requirement, Conformance, MethodReceiver, TraitSelf, TraitSubject and
  AssociatedType roots are distinct. Retain conditional children, supertrait and
  trait-path edges, projection normalization and original associated clauses.
  Public requirement and implementation conditions are not positional arrays to
  zip: use the retained conformance/requirement/implementation derivation.
- Preserve condition bindings in environment rebuilding, equality and body keys.
  A legitimate prepared empty set differs from missing/unprepared evidence.
  Provided placement and original lexical source have separate identities.
  Explicit caller environments replace ambient Mono Cursor state.
- A derived unresolved source path receives SourceAdmission at its first concrete
  substitution independently of member use. The result validates the retained
  path; it does not replace that path or reopen callable selection. Exact authored
  Function/Requirement premises consume their already-admitted caller bindings.
- Cover Written Direct, Static Requirement/Provided, operator, protocol, try,
  entry/root, extern/bodyless, synthetic and ExistentialBox paths. Bodyless calls
  still admit complete signatures. Entry consumes selected body identity. Both
  declaration and execution worklists interpret saved evidence rather than
  becoming AST-driven body checkers.

## Erased Receivers and Member Availability

Adopted user decision: erasing a value to any P does not implicitly select #P as
its route to another trait Q. An impl P as Q alone does not guarantee unique Q
for the hidden Self; another route may coexist. Explicit interface, supertrait
and associated guarantees retain their authority. Caller-owned parameters and
fixed outputs retain their actual premises/first-concrete admission.

```plew
trait Q {}
trait P { fn get() -> I64 where Self: Q }
impl P as Q {}
fn probe(value: any P) -> I64 { return value.get() } // reject
```

The specification in spec/08 and spec/09 owns that rule. An existential container
does not thereby conform to its own trait. Hidden Self is a rigid proof-only
binder distinct from lexical Self, inference variables and independent boxes.

The immutable interface node pool has distinct source-call, declaration-contract
and interpreted-instance provenance. Source roots bind session, exact operation,
receiver and trait instance; a contract cannot borrow a fake CallSiteKey or caller
premise. Root/owner/caller mismatches must fail. Explicit interpretation preserves
original root identity and capture-avoiding caller substitution.

Concrete and universal proof interpretations share the selected witness,
conditional, supertrait, associated and projection workers. Their result types
remain distinct: universal interface evidence cannot become static Ready or
enter a static body queue. Final dynamic descriptors retain an immutable evidence
capability checked at publication, Mid signature preparation and LLVM preflight.

At boxing, consume the selected concrete witness and the exact retained method
plan, map public clauses to implementation-bound identities and prepare the real
body. Signature checking and both worklists consume the same privately admitted
environment. Cached source/target identity does not repair missing, replaced or
foreign trait/proof evidence. Distinct explicit source views retain their tables.

Formation is separate from availability: an unused member whose public conditions
are not guaranteed cannot invalidate the whole existential. Malformed evidence
for a promised member remains an error. Do not catch proof-error strings or
weaken scope/integrity checks to turn them into absent slots.

## Inherited Receiver Boundary

The public inherited signature uses logical newtype Self; the original body runs
with its original physical Self. Keep the original requirement clause and the
checked method ParamId alpha map. A declaration-normalized entailment bound is
not the public signature of every inherited receiver. Concrete type names do not
become implicit Self.

Both worklists follow the same explicit inherited boundary with retained
condition IDs/proofs. Selected witness interpretation preserves its chosen
conformance/path while changing logical Self within valid newtype inheritance;
no Declaration fallback or receiver-name conformance search repairs that edge.
Actual adapter chains, original implementation conditions and real Mid are
covered by interface_boxing_conditions and existential_newtype_condition_witness.
Self in inherited trait arguments and existing generic-method derivations have
separate positive controls.

## Reconciled Area Completion

Independent body_receiver_completion_review accepts the finite evidence contract
with all required children and repairs closed. Original conditions and selected
paths reach the real callee; the following Outcomes retain exact source, removed
paths, applicable controls and independent receipts.

| Contract | Closure evidence owners |
| --- | --- |
| Existence / SourceAdmission / MemberDispatch, precedence and ambiguity | com-4kti and B4/com-yojf: complete instances and path authority; output mismatch cannot choose another source. |
| Original condition IDs, method ParamIds, associated/supertrait evidence | B3/com-v2xk: retained requirement-to-implementation derivation shared by both worklists and real body environments. |
| Placement vs lexical source vs body identity | B3, com-6paa, com-072n/com-9clj and com-3qne: original source remains separate from concrete placement; exact receiver survives body keys and signatures. |
| First concrete admission, prepared-empty vs missing | B3 and D3/com-wqa0: retained conditions interpreted in explicit caller environments; missing/unprepared evidence cannot become success. |
| Hidden Self, Universal vs Ready, formation vs availability | B4 and C6/com-3q2n: four root authorities, static escape rejection and corrupted/unavailable distinctions through Mid/dynamic descriptors. |
| Inherited logical/physical Self and boxing | B3: two-stage newtype chains, original clauses, alpha maps, real adapters and Mid. |
| Written, implicit, root, bodyless and synthetic entry | B1/B2/B3, com-6paa, C6 and com-3qne: complete signature admission and saved callee identity rather than downstream name selection. |

providedBodyProof and concrete witness interpretation retain an already selected
copy's placement evidence. They do not revive removed source-selection fallbacks.
The original exact-environment contract has no unfinished in-scope descendant.
This scoped closure adds no general opening, allowunique, runtime trait solver or
new ABI. Whole frozen-candidate gates remain G2a/G2b; phase three and main/seed/
adopted-carrier promotion remain uncertified here.

## Reference Boundaries

[Rust item-bound satisfaction](https://doc.rust-lang.org/reference/trait-bounds.html#bound-satisfaction)
requires conditions when an item is used; its
[dyn-compatibility restrictions](https://doc.rust-lang.org/reference/items/traits.html#dyn-compatibility)
are not imported wholesale. [Swift SE-0309](https://github.com/swiftlang/swift-evolution/blob/main/proposals/0309-unlock-existential-types-for-all-protocols.md)
separates formation from individual member availability.
[Swift SE-0352](https://github.com/swiftlang/swift-evolution/blob/main/proposals/0352-implicit-open-existentials.md)
distinguishes a box from its hidden conforming type; no general opening feature
is introduced by this repair. [Rust placeholder checking](https://rustc-dev-guide.rust-lang.org/traits/hrtb.html)
informs rigid identity and capture avoidance, not new lifetime/HRTB syntax.

## Trait Chain Readmission

com-6cw6 closes the G2b-discovered placement regression at production b16439fa /
fixture573ff620. Original source edge, complete receiver, surface owner and root
birth edge remain distinct from lexical provided-body ownership. Both concrete
copy readers interpret the saved ordered proof; gated diagnostic candidates
never select a call. Independent body_receiver_completion_review accepts the
repair and this area's reclosure after native47/reject23 and sourcecheck, with
both 381-input maps unchanged. Original fifteen rejection pairs and 3qne41/6
remain intact; nested-root and exact-duplicate controls pass. Receipt
meta/evidence/existing-feature-conformance/source-owner-facts/trait-chain-placement-repair.json.
Final changed-input G1/G2 gates remain separate; historical gates do not qualify.
