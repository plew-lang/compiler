---
id: com-7knz
status: open
deps: []
links: []
created: 2026-10-13T01:56:55Z
type: task
priority: 1
assignee: Koji Murata
tags: [design, verification]
---
# Resolve specification-level findings from the compiler design review

## Scope

Whole-reference design review requested on 2026-10-13. Design input is compiler
`54d8cc1ff0c46fa60d876120d7b07d61be84a9b3`; language input is spec
`29e4cadea5a7c5968f3607e4bef2e666f8304e6f`. Current implementation is deliberately
excluded. No compiler, test, sanitizer or performance execution is evidence for
this review. Earlier chapter approval is not proof of architectural completeness.

The standard is whether the reference can guide implementing Plew's specified
meaning without duplicate decision authorities or ad hoc fallback paths, at a
reasonable maintenance cost for an individual using LLM implementation. It is not
an implementation-ready API specification for every subsystem.

Three independent reviewers cover semantic checking; Mid/ownership/ABI/runtime/
demand execution; and overall architecture/input/generation/diagnostics/maintenance.
Official comparison sources and concrete change scenarios support the findings.
Cross-review checks challenge the principal findings rather than counting votes.

## Findings

The review is complete. Design-level resolutions and their remaining gates are
listed below; implementation verification is outside this task. R6's external-input
freshness assurance boundary is awaiting a user decision. The other repairs have
canonical text and scoped reviewer confirmation; final whole-reference review
and first-edition acceptance remain separate.

| Item | Design-level disposition | Canonical evidence |
|---|---|---|
| R1 | Addressed; implementation separate | Conformance path identity and admission below |
| R2 | Addressed; language synchronization complete | Runtime RC plan/publication and spec14 |
| R3 | Addressed; managed/native scope approved | Driver coordination, Runtime participant protocol and spec15 |
| R4 | Handoff specified and chapter reviewed | Sources native-build service |
| R5 | Stage order aligned and rechecked | Architecture and Mid |
| R6 | User decision pending | Minimum external-observation assurance; no silent adoption |
| R7 | Aggregation and state-preservation fixes rechecked | Metaprogramming host units and one publication |
| R8 | Initialization contract aligned and rechecked | Mid and operation supplement |
| S0 | Adopted language rules synchronized and domain reviewed | spec03/04/05/06/07/08/11/14/15 and canonical capability/runtime chapters |
| S1 | Stale derive visibility condition repaired and rechecked | spec16 ordinary construction visibility |
| S2 | Stale explanations repaired and rechecked | spec12/15/17 |
| E1 | Migration progress wording removed | Syntax, Sources, Metaprogramming and Generics; audit limits retained |

No proposed resolution is adopted merely by recording it here.

### R1 — P1: Conformance admission needs path uniqueness, not only a terminal witness

[Types and Evidence](../design/types-and-evidence.md#5-conformance-evidence),
[Generics](../design/generics.md#declaration-bound-evidence-transport), and the
proof admission boundary distinguish existence from static member selection, but
must not admit a source bound from one arbitrary existence derivation. Spec09
343–365 rejects ambiguous trait-subject paths even when no member is called.
C -> B -> A and D -> B -> A remain a real path choice even if B -> A uses the
same final witness. Duplicate discovery of the same path is a different case.

Required direction: preserve path-selection identity and require specification-
valid unique conformance admission, including unused/empty bounds, selector
resolution and shared-terminal intermediate branches. Internal existence queries
may remain weaker but cannot establish source-bound validity alone. This follows
existing specification; allowing real branches solely because the terminal is
equal would require an approved specification change.

Comparison: [Rust trait resolution](https://rustc-dev-guide.rust-lang.org/traits/resolution.html)
and [coherence](https://doc.rust-lang.org/reference/items/implementations.html#trait-implementation-coherence)
separate internal proof work and admissibility. Rust's coherence assumptions are
not a substitute for Plew's explicit path-selection rule.

Design resolution: [Conformance Evidence](../design/types-and-evidence.md#5-conformance-evidence) now separates internal existence, source path admission and terminal executable witness selection. [Capability contracts](../design/types-and-evidence.md#capability-and-conditional-selection-contracts) and [instance admission](../design/generics.md#capability-discharge-and-witness-admission) retain path identity through witness construction, including unused/empty bounds and branches sharing a terminal. The design requirement is addressed; source-rule synchronization and implementation verification are distinct from one another.

### R2 — P1: Static allocation-mode analysis is not connected to lazy publication

[Runtime](../design/runtime.md#storage-arc-and-cow) explicitly leaves closure of
sharing analysis over lazily checked bodies unresolved. Spec14 requires mode fixed
at allocation, backward propagation from sharing, homogeneous retain/release joins,
and no dynamic promotion. A value allocated before a later-demanded function sends
it to a worker must already have the correct mode.

Specify analysis producer, saved result/identity, dependency closure, completion
and publication authority. Consider sufficiently broad pre-execution analysis
with machine code still lazy, or conservative constraints that remain valid under
later requests. Failing a later request is a safety fallback, not an implementation
of every otherwise valid program. Spec15 permits wider checking dependencies.
This requires an architecture choice, not more assertions in runtime helpers.

Comparison: [Rust Arc](https://doc.rust-lang.org/std/sync/struct.Arc.html) fixes a
thread-safe ownership mechanism explicitly; Plew hides that choice and therefore
needs its own allocation-sharing contract.

Design resolution under the adopted sharing proposal: [Storage, ARC, and CoW](../design/runtime.md#storage-arc-and-cow) assigns AOT plan production to execution preparation, retention to the session and admission to the driver. Demand execution fixes ordinary managed allocations and typed operations to a conservative atomic baseline before execution; later requests do not reclassify live allocations. [Callable publication](../design/driver-and-execution.md#demand-call-and-publication) consumes this mode contract alongside effect closure. The adopted AOT/JIT baseline is synchronized into spec14 under S0. This addresses R2's initial publication gap at reference-design scope; it neither verifies implementation nor resolves R3's worker-pause protocol.

### R3 — P1: Worker demand and application-wide compilation pause have no protocol

[Runtime](../design/runtime.md#one-execution-implementation) and
[Driver](../design/driver-and-execution.md) left real-thread quiescence
open. With specified spawn, a worker can first call an unmaterialized entry while
root or another worker is executing or waiting. Stopping event delivery alone does
not stop a computing worker or define who may operate the compiler session.

Specify request execution thread, routing/coalescing, safe stopping and held-lock
rules, native-call treatment, root-waits-worker progress, and terminal failure.
Possible approaches include compiler-affine coordination with cooperative stopping
or a defined pre-spawn preparation closure. Neither approach inherently requires
separate build/run runtimes. These are alternatives requiring a design decision.

Comparison: [LLVM ORCv2](https://llvm.org/docs/ORCv2.html) coordinates its own
materialization, not Plew application stopping or session ownership;
[Dart thread registry](https://github.com/dart-lang/sdk/blob/main/runtime/vm/thread_registry.h)
illustrates explicit thread/safepoint management.

Adopted pause scope: stop all Plew-managed application execution, event delivery, continuation execution, callback entry and user destruction. A registered external C call may continue, but managed return/callback waits at the common gate. External effects and OS activity are not stopped or cancelled. This scope was explicitly approved after comparing Dart and HotSpot native-state transitions; it is not inferred solely from FFI safety responsibility.

Design resolution: [Worker Demand Coordination](../design/driver-and-execution.md#worker-demand-coordination) assigns a single independent compiler-affine owner, synchronized request admission/coalescing, managed quiescence, private preparation, complete publication and terminal failure. [Managed Pause and Native Boundaries](../design/runtime.md#managed-pause-and-native-boundaries) defines participant states, cooperative polling, membership races, stable native boundaries, lock/wakeup rules and retained roots/access/code. [Session ownership](../design/compiler-state.md#2-sessions-and-input-identity) prevents application workers from reading the nonsendable compiler registry. Root-waits-worker and C-waits-worker scenarios can reach the service without draining application events or waiting for C to return. No compiler-required lock can remain held by a waiting requester, including ORC materialization callbacks. These contracts address the design gap. The managed/native pause scope is synchronized into spec15's run contract; the wider sharing/capability rules are synchronized under S0 and implementation validation is not claimed. Two chapter reviewers confirmed the protocol and the follow-up fixes for ORC followers, managed generated helpers, native departure ordering and transitive service-lock dependencies.

Rationale and alternatives: waiting for every C call to return can create a cycle when C awaits a worker that first needs JIT. Arbitrary OS-thread suspension can strand allocator/library locks. A compiler service attached only to the application's root can become unavailable in either example. The chosen independent owner and cooperative managed boundary avoid those added dependencies while retaining synchronous calls and one runtime implementation. The runtime comparison sources concern safe stopping, not a claim that Dart or HotSpot stop their applications for every compilation.

### R4 — P2: Native host execution is assigned to a layer without a handoff contract

[Sources](../design/sources-and-modules.md#2-packages-are-not-modules-or-directories)
names the package layer as owner of native dependencies. Spec17 219–225 also
requires resolved host-exec/tool/loader closures, trust admission, sandbox input
boundaries and artifact provenance, including runtime Rust dependency build.rs.
General host/target separation or process isolation does not define these steps.

Add a bounded native-build service contract in the existing Sources chapter:
validated execution plan -> trust/policy admission -> execution -> provenance-
bound artifact -> driver/generator consumer. Separate host/target identities and
cache validity, reject execution/input outside the admitted closure, and retain
failure without publishing a reusable artifact. New chapter/framework is not
required. This concretizes existing specification, not a new language feature.

Comparison: [Cargo build scripts](https://doc.rust-lang.org/cargo/reference/build-scripts.html)
are actual host executable work; [Cargo build cache](https://doc.rust-lang.org/cargo/reference/build-cache.html)
separates build artifacts and their inputs. Plew's stricter trust/sandbox contract
must be designed explicitly rather than attributed to Cargo.

Design resolution: [Native Build Service Handoff](../design/sources-and-modules.md#native-build-service-handoff) assigns plan validation, user-local policy admission, constrained execution, successful provenance publication and driver/generator consumption. The resolver does not gain execution authority, the lock does not imply trust, and Cargo children remain in the admitted tool/input/loader closure. Native artifacts are separate from the generator-owned Plew harness. Chapter review confirmed this concretizes spec17 rather than introducing a general build-hook framework; physical isolation and cache implementation remain unverified.

### R5 — P2: Overview and canonical Mid stage order disagree

[Architecture](../design/architecture.md#3-compilation-model-and-handoffs) puts
concrete facts before CFG construction, while [Mid](../design/mid.md#preparation-stages-and-executable-admission)
constructs/freezes parametric Mid before instantiation. Generic declaration CFG
analysis must not acquire different input/owner assumptions depending on which
chapter is read first. Align the overview graph/table with the canonical stages
and distinguish symbolic declaration analysis from concrete execution preparation.
No new specification or representation choice is required.

Design resolution: [Architecture](../design/architecture.md#3-compilation-model-and-handoffs) now shows checked facts -> frozen parametric Mid -> concrete Mid/evidence -> prepared Mid. Its table no longer assigns first CFG construction to concrete instantiation. Symbolic declaration analysis remains independent of executable instance preparation. The affected chapter comparison was rechecked.

### R6 — P2: Generation freshness admission needs a defined minimum guarantee

[Metaprogramming](../design/metaprogramming.md#6-output-provenance-and-ordinary-checking)
assigns freshness to the correct owner, but leaves the acceptance predicate open.
A new checkout with committed output, a changed provider revision, and external
provider input must have defined receipt/admission outcomes without running the
provider during ordinary build. Specify receipt producer/consumer and minimum
input identity, absent/invalid receipt behavior and failure publication. Choose
explicitly which external observations freshness covers; that assurance boundary
requires a decision. Wire format and exact publication API can remain details.

Pending decision: whether first-edition freshness covers only recorded source,
configuration/provider/dependency identity and output content, leaving arbitrary
provider filesystem/environment/network observations outside that guarantee, or
requires an external-input declaration/validation mechanism. The former is the
recommendation presented to the user, not an adopted rule yet. Ordinary build
must not run providers in either case. After the boundary is chosen, specify
producer/loader receipt admission for a fresh checkout, missing/mismatched
receipts, provider changes and interrupted publication without conflating
freshness with output semantic correctness.

### R7 — P2: Provider isolation needs a generator-level aggregation boundary

[Metaprogramming](../design/metaprogramming.md#3-syntax-input-and-the-process-boundary)
requires incompatible Syntax/package graphs to be isolated, but the host-program
construction procedure does not close their combined output protocol. Define the
generator's division into compatible host units, ordered result aggregation and
one successful output publication for the target source. Separate processes or
serialized schemas are not automatically required. This concretizes the existing
String boundary and avoids independent runners publishing partial output.

Design resolution: [Host Units and One Output Publication](../design/metaprogramming.md#host-units-and-one-output-publication) assigns compatible-graph grouping and invocation identity to the generator, isolates nominally incompatible graphs, collects ordered Strings and publishes once after all successes. A logical host unit retains ordinary global identity, one initialization, shared state and cleanup; runner batching cannot reset a provider between repeated invocations. Chapter review identified that state-preservation gap and the native-artifact/harness boundary; the corrective diffs were rechecked. The unit plan scans invocations in source order and selects the earliest valid merged resolved graph, preserving revisions; nontransitive compatibility is not assumed to define an equivalence class. No AST serialization framework or per-directive process requirement is introduced.

### R8 — P2: Mid initialization order contradicts runtime force-on-read

[Mid](../design/mid.md#preparation-stages-and-executable-admission) says it retains
frontend initialization order; [Mid details](../design/mid-entry-audit.md) line124
calls this the frontend dependency order. Spec15 lines27–39 explicitly uses
runtime memoized force-on-read rather than static dependency ordering, including
function-mediated dependencies, asynchronous waiting and root/worker cycles.
Driver's startup contract preserves runtime forcing.

Distinguish initial root enumeration from actual initialization order. Mid must
realize the force/read operation and initialized-state publication contract;
frontend source order or a static graph cannot replace it. Existing source
semantics decide this repair; no new language choice is needed. Include a read
through an initializer-called function and async/worker waits in the cross-domain
trace, not only direct acyclic roots.

Design resolution: [Mid](../design/mid.md#preparation-stages-and-executable-admission) and its [operation supplement](../design/mid-entry-audit.md) distinguish initial root enumeration from runtime dependency execution. Selected reads force the common state machine, including initializer-called functions, async waiting and root/worker cycles; initialized ownership publishes only on success. The affected chapter comparison was rechecked against spec15. No static dependency sort or extra language policy was added.

### S0 — P1, specification decision: Read capability is not immutable sharing

Spec03 lines156/176/178 permit Ref[T] to be sendable when T is sendable and
MutableRef.asRef() to retain the same mutable cell without freezing. Spec14
explicitly permits copying such Ref values into spawn. A root can retain a
MutableRef, create its Ref view, pass that Ref to a worker and update through the
MutableRef while the worker reads the cell. Thread-locality of the mutable
handle does not make its aliased payload thread-local. Atomic reference counts
protect lifetime, not concurrent payload access.

The reference cannot implement all these promises with structural sendability
alone. Reconcile the specification and design before claiming the cross-thread
contract is closed. Possible directions include an independent snapshot,
restriction of remaining mutable aliases at transfer, or a distinction between
read capabilities and cross-thread immutable references. None is adopted here;
this is a language/safety decision requiring the user. Also cover WeakRef
conversion/upgrade and generic or existential transport of the capability.
An independent cross-review found no alias-exclusion or transfer rule that removes
this counterexample. The finding is a conflict between specified rules, not a
tested compiler race.

Adopted resolution: ordinary Ref/MutableRef and corresponding weak handles are nonsendable. FrozenRef and MutexRef provide distinct access/ownership contracts without repairing nonsendable payloads. Explicit capabilities, autounique, conditional candidates, existential opening, unique outcomes, global effects and implicit destruction connect those rules through the language. The formal specification owns the rules; [standard-library boundaries](../design/standard-library.md) and the semantic/runtime chapters own their handoffs. Three domain reviewers checked synchronization and repairs, including old Ref capture permission, place generalities, Optional/Result declarations, method candidate families and buffer destruction destination. Their follow-up checks found those contradictions resolved. A separate compression review retained rationale, future scope and Guard verification obligations while replacing the two meta drafts with canonical links. This is document/design evidence, not a tested concurrency implementation.

### S1 — Specification conflict: Parameterized derive and private fields

Spec16 line110 requires public argument fields for parameterized derive construction.
Spec05 lines201–204 explicitly permits a public memberwise factory to accept
private fields. [Metaprogramming](../design/metaprogramming.md#2-macro-identity-and-host-contracts)
correctly delegates to ordinary construction rules. Reconcile the stale special
condition in the specification with the already approved public-factory decision;
do not add a derive-only field-visibility exception to the design. This is a
specification inconsistency, not a demonstrated implementation bug.

Resolution: spec16 now requires an applicable visible factory and public API closure, not public storage fields. Chapter recheck confirmed the rule is ordinary construction, with no derive-only privilege or extra visibility requirement.

### S2 — Stale specification explanations and comparisons

- Spec12's old claim that Plew has no ownership/borrowing conflicts with Spec03.
  Its compound-index assignment illustration uses an immutable receiver snapshot
  for an inout setter and omits writeback to the original root. Preserve the
  Spec03/design get-modify-set rule; repair the explanation, not the design.
- Spec15 lines719/721 still describe self-contained C output and piping Plew output
  as C to clang. The adopted backend is LLVM; remove old implementation recipes
  without changing the native ABI and manifest-linking contracts.
- Spec15 lines515/611 describe C publication as excluded/future despite the same
  chapter's adopted expose section.
- Spec17 line194 overstates SwiftPM's exclusion of commands. [SE-0303](https://github.com/swiftlang/swift-evolution/blob/main/proposals/0303-swiftpm-extensible-build-tools.md)
  defines build/prebuild commands. Retain Plew's no-arbitrary-build-hook choice
  without using a false claim about SwiftPM as its justification.

These are specification maintenance findings, not evidence of implementation
bugs. Align them with existing decisions rather than inventing new behavior.

Resolution: spec12 now acknowledges ownership/borrowing and uses the existing place contract. Its indexed compound-assignment explanation preserves key/value evaluation and writes the element into the current container rather than overwriting unrelated changes with an earlier container snapshot. spec15 describes LLVM/manifest linking and adopted expose/callback contracts; spec17 accurately distinguishes SwiftPM build/prebuild commands from Plew's own no-general-hook choice. The corrective writeback diff and other changes were rechecked.

### E1 — Editorial: Migration status remains in otherwise canonical chapters

Syntax and Metaprogramming retain “gap migration in progress” language although
README records consolidation complete. Remove migration progress wording while
retaining scoped evidence and genuine unresolved design/implementation questions.
Do not confuse an implementation audit's date with adoption of a design contract.

Resolution: canonical chapters point to retained follow-up issues without claiming migration is still in progress. Scoped inspection revisions, unaudited implementation boundaries and the physical checked-body restart gate remain intact.

## Project Fit and Preservation

The principal separation of source selection, concrete witness preparation, Mid
control/evaluation, ownership-ending edges, type destruction contents and physical
ABI realization is useful and proportionate. Explicit failure/publication contracts
and one runtime prevent recurring alternate paths. No additional universal solver,
query framework, new backend, or one chapter per concern is justified by this review.

[Swift RequestEvaluator](https://github.com/swiftlang/swift/blob/main/docs/RequestEvaluator.md)
provides a reference for hidden dependency/authority hazards; [Swift SIL ownership](https://github.com/swiftlang/swift/blob/main/docs/SIL/Ownership.md)
for explicit lifetime obligations; [Rust MIR type checking](https://rustc-dev-guide.rust-lang.org/borrow-check/type-check.html)
shows that downstream consistency checking can legitimately coexist with one source
selection authority. “No duplicate authority” must not become “never verify twice.”

Detailed checked-body storage/API design remains an explicit implementation restart
gate, not grounds for silently inventing an extra IR. First-edition responsibilities
and implementation-ready physical API detail are distinct completion levels.

The necessary improvements mostly fit existing sections. Keep normative contracts
short and authoritative; separate scoped historical observations and avoid making
every optional/unsupported feature a mandatory architecture framework. Native
sandbox requirements come from the current spec and are substantial project work;
the compiler reference must assign them honestly without pretending Cargo or an
ordinary subprocess supplies that guarantee.

## Coverage and Limits

After explicit follow-up for truncated/missing reads, the three reviewers together
read all 18 main design chapters, all seven detailed contract/decision supplements,
maintenance, and all specification topic files 01–18. Domains were divided as:

- Source semantics: spec03–13; Lookup, Types, Body Checking, Generics, Frontend
  Handoffs, Checked-body Storage and Divergence.
- Execution: spec03/04/11/14/15; Mid/Mid details, Ownership, Passes, ABI, LLVM,
  Runtime, Driver, Collections and Hot Restart.
- Architecture/tooling: spec01/02/15/16/17/18; README, Architecture, Compiler
  State, Sources, Syntax, Metaprogramming, Diagnostics, Verification, Maintenance,
  Declaration/Execution audit, with overlap of semantic/execution chapters.

Concrete scenarios included unused ambiguous trait bounds and shared terminal
witnesses; allocation before a later spawn dependency; worker first-call demand
while root waits; Rust build.rs invoking a tool in host and target configurations;
a committed generated file in a fresh checkout; differing provider Syntax graphs;
generic CFG analysis; indirect/async global forcing; and mutable/read-reference
aliases across spawn. Additional positive traces covered new construction sugar,
diagnostic failure propagation, native lazy callback ownership, nested indexed
writeback and conditional unique cleanup.

This is a thorough document/design review, not a formal proof or exhaustive test
of every source-language combination. Primary-language references were checked
for relevant mechanisms; the review does not claim a complete audit of the
Rust/Swift/Go/Dart/LLVM implementations. Current compiler implementation and its
performance are outside scope. No new design is accepted merely by comparison.

## Completion

Record accepted repairs or decisions in their canonical chapters and
re-review affected cross-domain paths. Do not declare the full-spec reference
complete by silently restricting it to the currently implemented subset.
This review does not authorize compiler implementation, build or integration.
