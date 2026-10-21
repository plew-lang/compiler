---
id: met-ukm5
status: closed
deps: []
links: []
created: 2026-10-21T11:40:54Z
type: task
priority: 1
assignee: Koji Murata
tags: [design, verification]
---
# Re-review compiler architecture against the adopted language specification

## Review Input and Scope

User-requested renewed review of the architecture itself, before a detailed
implementation/design conformance audit. Input: compiler design
`1d83231ed5a282f69bcd1579875d62d8eb940fa1`, language specification
`16f2f13970dbe2789214b2206c48af3df21b68c8`. Implementation, current support and
performance are excluded as evidence of the design's correctness.

Three independent reviewers cover (1) source semantics/types/generics/storage,
(2) Mid/ownership/ABI/runtime/lazy execution, and (3) architecture/input/tooling/
maintenance. Each compares the assigned documents against relevant complete
specification topics and current primary reference-language documents. The parent
checks cross-domain cases and challenges candidate findings before saving results.

Review standards:
- Preserve Plew's specified meaning; do not substitute another language's rules.
- Identify one decision owner, explicit inputs/output guarantees, remaining
  legitimate decisions and final consumers, including failure/cleanup/cycles.
- Show concrete contradictions or missing handoffs rather than asking for detail
  or another general framework by default.
- Test whether a small new change can be located and finished from the reference.
- Consider runtime/compile costs and individual LLM-project maintenance; distinguish
  genuine design changes, existing accepted boundaries and optional elaboration.
- Record coverage/limits and accepted/rejected findings. Prior chapter approval or
  met-ukm5 completion does not certify implementation or first-edition acceptance.

## Verdict

The overall architecture is appropriate for Plew's adopted semantics and the
reference's stated purpose. No demonstrated need to replace its pipeline, add a
universal query/trait framework, or restart the reference from scratch was found.
The separation between checked source decisions, legitimate concrete discharge,
Mid correctness, representation and executable publication is worth preserving.

At the reviewed input, it was not yet a fully closed instruction for every
affected implementation: three actionable contract gaps remained in two areas.
R1/R2 belong to one capability
design task; R3 belongs to the async ownership boundary. Their existence does not
invalidate already closed unrelated increments. Close the affected contracts
before implementing those areas; do not silently fill them with local selectors
or backend cleanup. No proposed solution or language change is adopted here.

| Finding | Impact | Follow-up |
|---|---|---|
| R1: recursive capability summaries lack a solution/termination contract | P1 design prerequisite for recursive autounique | [met-yotl](met-yotl.md) |
| R2: bounded conditional reasoning has no minimum shared fragment | P2 risk of different call/via/deinit decision procedures | [met-yotl](met-yotl.md) |
| R3: async input ownership acquisition is not connected explicitly to Mid entry/cleanup | P2 handoff omission, not a reproduced runtime bug | [met-6kzo](met-6kzo.md) |
| E1: contract navigation and stale descriptions | P3 editorial improvement | [met-m7wx](met-m7wx.md) |

Severity here describes review impact, not the tk priority scheme or a measured
implementation failure. The task metadata controls work ordering.

## R1: Recursive Capability Derivation Has No Selected Solution

Locations at the pinned input: Types and Evidence 77, 81, 83; Generics 92;
Compiler State 73. [Nominal finalization](../design/types-and-evidence.md#capability-and-conditional-selection-contracts)
publishes ownership edges and a normalized copyability condition; instantiation
must consume it rather than derive a competing condition. General computation
rules require each domain to define legal cycles and publication. The capability
domain does not yet supply that definition.

Spec05 accepts recursive value types; spec06 derives autounique from all owned
fields/variants and rejects declarations whose capability never varies. Consider
this specification-level example, not an executed test:

```plew
autounique enum List[allowunique T] {
    Nil
    Cons(value: T, rest: List[T])
}
```

The structural equation is
`Copy(List[T]) = Copy(T) AND Copy(List[T])`. For copyable T both false and true
satisfy that equation; Plew's intended value-copy semantics require the copyable
solution. Naming Active/Ready/Failed is insufficient to choose it. Treating an
active visit as false or success without closing the recursive derivation risks
wrong capability, wrong autounique admission or wrong ownership operations.

Recommendation: state the solution for nominal ownership SCCs, provisional versus
published summaries, and capability stops at shared handles. Greatest-fixed-point
copyability or least-fixed-point may-be-unique are possible equivalent descriptions
within the appropriate finite structural domain. Do not apply this indiscriminately
to arbitrary conformance proofs, sendability or destruction.

Changing recursive type arguments can be harder than revisiting the same node.
An allowunique trait with an allowunique `Next` associated type can permit a
recursive payload family requiring `Copy(T)`, `Copy(T.Next)`,
`Copy(T.Next.Next)`, and so on. Specify which summaries close finitely and what
happens otherwise. A recursive condition graph/schema may be appropriate; this
review does not require every condition to flatten to parameter Boolean atoms.
Known finite summaries must not be rejected merely because syntax changes a
type argument. A resource limit is not permission to guess a capability.

The ordinary structural SCC rule is an internal realization of existing meaning.
A new ban on accepted recursive forms, conservative reclassification to unique,
or public annotation would require user judgment. No such choice is made here.

[Rust coinduction](https://rustc-dev-guide.rust-lang.org/solve/coinduction.html)
uses recursive List/Send as an example and distinguishes cyclic proof handling
from unrestricted generalization. [Swift SE-0427](https://github.com/swiftlang/swift-evolution/blob/main/proposals/0427-noncopyable-generics.md)
separately discusses recursive associated-type Copyable requirements. These
comparisons support separating the two problems, not importing either solver.

## R2: Bounded Capability Reasoning Needs a Shared Minimum Contract

Locations: Types and Evidence 78, 83; Generics 94, 166, 178; spec06 83–96.
The producers and saved outputs are well assigned, but "adopted bounded reasoning"
has no actual minimum supported predicate fragment or common discharge contract.

For an aggregate with `Copy(T) AND Copy(U)`, complementary copyable/unique
candidates should have provable coverage and disjointness. When two projections
are equated by retained associated bindings, normalization changes whether a
family has overlap, a hole or an unproved relation. The reference does not state
which cases ordinary call, via and conditional deinit must answer identically.
Each implementation could invent its own small solver while claiming to satisfy
the same general prose. That is precisely a duplicate-authority risk.

Recommendation: define minimum supported atoms/operations, canonical term and
projection equality inputs, shared overlap/coverage outcomes and saved proof
obligations. Separate proved overlap, unproved disjointness, deferred obligation
and resource exhaustion. A data-layout choice, SAT engine, general trait solver
or formal proof of every formula is not required for the first edition. The
specification already admits conservative rejection outside its limited reasoning;
changing the promised basic acceptance cases still needs a source decision.

## R3: Async Entry Needs an Explicit Initial Ownership Handoff

Locations: Mid Entry Audit 185–190, 336; Ownership and Access 13;
Runtime 100; Frontend Handoffs 332–337; Representation and ABI 49.
The [call contract](../design/mid-entry-audit.md#evaluation-homes-and-call-materialization)
describes ordinary inputs as caller-guaranteed +0; guaranteed inputs are not local
owners. Async entry must own its accepted inputs, and entry-to-resume arguments
use the frame. What is missing is the producer connecting acquisition/transfer
to the logical body's initial ownership state and Mid cleanup.

```plew
async fn keep(text: String) -> Promise[()] {
    await delayed()
    print(text)
}
val pending = keep(text: makeString())
```

This illustrative trace assumes suitable declarations for the helpers. The
caller temporary's guarantee ends when entry returns, but the suspended activation
still needs its String. Descriptor-byte storage alone is insufficient. A backend
inventing an independent drop would violate Mid's source-cleanup authority.

Counterargument checked: the general stored-value rule already requires a new
share when borrowed input becomes an independent stored owner, and Frontend
Handoffs says async entry owns accepted inputs. Thus the intended semantics are
derivable; this is a missing explicit producer/consumer connection, not a proven
contradiction, UAF or need for a new language feature.

Recommendation: define activation-owned ordinary inputs/copy-self/environment
retention and transferred unique inputs before caller guarantees expire; connect
them to initial Mid ownership and exactly-once cleanup. Cover synchronous first
completion and suspension under the same rule. Keep frame storage and Promise
bookkeeping separate from source ownership. A +0 public entry acquiring activation
owners fits the present ABI; an internal consuming ABI is an alternative requiring
all caller/adapter consumers to agree. New coroutine IR is not required.

[Rust async functions](https://doc.rust-lang.org/reference/items/functions.html#async-functions)
explicitly describe capture into the returned state machine; their lazy Future
start/cancellation rules are not Plew's Promise rules.
[Swift Ownership SSA](https://github.com/swiftlang/swift/blob/main/docs/SIL/Ownership.md)
provides the ownership-reference point: guaranteed uses need an enclosing owner.
Neither byte-level `byval` nor a frame slot is that owner by itself.

## E1: Improve Discoverability Without Expanding Architecture

Frontend Handoffs mixes stable obligations with legacy row/count sentinels and
migration status (87–98, 460–514); its pending reconciliation prose can disagree
with the worklog/issue authority. Move changeable migration details to existing
issues while preserving necessary invariants/rationale and linking the physical
storage home. This overlaps prior com-7knz E1; it is not a newly discovered
semantic failure.

String decoding is described across Syntax, Declaration and Execution Audit
202–206, and Mid Entry Audit 37. Existing rules prohibit LLVM-only semantic
validation, so there is no demonstrated double-selector bug. A direct link from
the syntax handoff to the common decoder contract is enough to aid change location.

Spec15 593 still describes generated C/header typedefs for opaque handles, whereas
its FFI linkage section uses Plew-owned declarations and LLVM. Correct that stale
mechanism-only explanation without changing foreign ABI/lifetime responsibility.

## Purpose, Cost and Reference-Language Assessment

The reference largely meets its purpose: a reader can locate the decision owner,
affected consumers and a finite verification boundary without reconstructing the
current implementation first. Important strengths are:

- Distinct source/body/binder/evidence/session identities; fixed input versions;
  private construction followed by scoped immutable publication and stable failure.
- Lookup gathers candidates; checking fixes source meaning; instantiation resolves
  legitimate abstract obligations; later stages cannot rescue missing facts by
  source search. Conformance existence, source-path admission and executable witness
  selection remain separate.
- Expected-type guidance does not overwrite completed types. Block/if/match share
  value/completion decisions; source divergence is separate from loop analysis.
- Defaults, via, synthetic operations and newtype adapters use the common selected
  call/evidence path instead of introducing parallel semantic interpreters.
- Mid owns evaluation/access/cleanup; ABI chooses representation; runtime consumes
  execution protocols. Body-local preparation is not whole-program effect closure
  or permission to publish executable code.
- AOT/JIT share runtime semantics; compiler/application ownership and managed pause
  are explicit. Atomic lifetime is not payload synchronization. Guard retention,
  Promise result rights, worker delivery and global readiness are distinct contracts.
- Host generation, input receipts, native build policy and diagnostics have defined
  producers, failures and final consumers; success tokens do not exceed their scope.

[Swift's compiler overview](https://www.swift.org/documentation/swift-compiler/)
separates semantic checking, SIL generation, mandatory correctness transformations
and optional optimization. Plew appropriately uses this responsibility separation
without adopting Swift's source inference. [Swift RequestEvaluator](https://github.com/swiftlang/swift/blob/main/docs/RequestEvaluator.md)
explains the hazards of hidden mutable AST dependencies and coarse lazy callbacks.
[Rust queries](https://rustc-dev-guide.rust-lang.org/query.html) provide a reference
for keyed producers and memoized results; [Go's compiler overview](https://go.dev/src/cmd/compile/README)
shows that a straightforward staged compiler can separately own syntax, typing,
IR lowering and evaluation order. These are architectural comparisons, not proof
that Plew must copy a universal request framework or every stage name.

For an individual LLM-assisted project, body-local sealed payloads, shared pool
IDs, explicit small pass chains and domain-specific worklists are proportionate.
Eighteen conceptual chapters do not require eighteen implementation modules.
Additional complete typed trees, a general trait solver, a disk incremental cache,
a second backend/runtime or a broad IDE recovery framework are not needed now.

There are real costs: AOT RC-mode propagation, descriptor-based concrete existential
bridges, all-worker JIT quiescence and native-build sandbox/trust enforcement.
The reference acknowledges specialization growth and runtime/compile costs. They
follow adopted semantics or consequential prior choices, not accidental prose
complexity. [LLVM ORCv2](https://llvm.org/docs/ORCv2.html) supplies materialization
and symbol infrastructure; it does not supply Plew's effect closure or application
quiescence. [Cargo build scripts](https://doc.rust-lang.org/cargo/reference/build-scripts.html)
are not a precedent for claiming Plew's stronger native sandbox is automatic.
Simplifying those guarantees would need an explicit user decision. No measurement
here establishes acceptable speed, memory or implementation effort.

Deferred public C callbacks, arbitrary foreign threads, reusable hosts/Hot Restart,
unique move capture and additional lifetime facilities remain separate future
work. This review does not add them to first-edition or type-checker completion.

## Change-Location Exercises

These are design traces, not implemented tests or exhaustive proofs.

| Hypothetical change | Decision owner and final closure located from design |
|---|---|
| Expected type lost across a block wrapper | Body Checking/value region → saved expression/use facts → Parametric Mid; direct/wrapped outcomes and exits |
| Trait requirement satisfied through defaults/via | Common applicability → evaluation/lifetime plan → retained evidence/adapter → instantiated call |
| Existential hidden Self passed to a generic | Opening/re-erasure plan → registered descriptor → private bridge → ordinary concrete callee |
| MutableRef nested indexed writeback | Selected projection → once-only base/key → Access/writeback → enforcement → LLVM; preserve owner/Guard/early exits |
| Weak restoration representation | Private operation registration → exact typed restoration → strong promotion → runtime cell/mode |
| New generator project setting | Host input/receipt producer → loader freshness admission → ordinary part checking; interruption and fresh-checkout controls |
| New source-byte provider | Fixed identity/provenance → shared parser/module graph → diagnostics; preserve one admitted snapshot |
| Warning output destination | Diagnostics presentation → driver; no acceptance/failure-state change |
| Recursive autounique/conditional family | Owner is located, but R1/R2 must define the producer's result and discharge boundary |
| Heap-bearing async input | Owner/consumer boundaries exist, but R3 must connect acquisition to Mid initial ownership/cleanup |

The successful exercises support purpose-fit; the last two explain why an
unqualified "all boundaries complete" claim would be premature.

## Coverage and Limits

Three independent read-only reviewers collectively read all 28 design Markdown
files (18 chapters, README/maintenance and detailed contracts/decisions) and all
18 numbered specification chapters. Split reading and overlaps covered source
semantics/storage, execution/ownership and architecture/tooling; truncated reads
were recovered by the reviewers. The parent challenged candidate findings against
general contracts, prior findings and cross-domain traces before consolidation.

Primary comparisons included Rust queries, trait/coinductive solving, async/drop/
Arc and monomorphization; Swift request evaluation, type checking, ownership,
noncopyable generics and Mutex; Go compiler/generation; Zig AIR/compilation state;
Dart safepoint/native transitions; and LLVM ORC/ABI. The linked materials support
the particular comparisons, not a claim that those entire implementations were
audited. References were read on 2026-10-21 and upstream main pages can change.

Prior com-7knz R1–R7/S0/S1/F1 closure was considered after independent assessment;
no concrete reason was found to reopen those corrected contracts. Heavy specified
features, uninspected implementation combinations and optional API details were
not counted as fresh design bugs. No formal termination/decidability proof for all
projection recursion, exhaustive language-combination proof, OS sandbox feasibility
test, compiler execution, sanitizer, fixed-point or performance run was performed.

## Outcome and Next Boundary

The review and its design/editorial follow-ups are complete at their stated
scopes. The adopted contracts, rationale, limits and independent delta-review
controls are retained in the owning chapters and resolution issues:

- R1/R2: [met-yotl](met-yotl.md) records the recursive summaries and shared bounded
  capability judgment. Implementation, including the fixed limit's numeric
  selection, belongs to [met-b2la](met-b2la.md).
- R3: [met-6kzo](met-6kzo.md#resolution-design-handoff-closed) records the async
  ownership handoff; implementation and execution controls belong to
  [com-tn1m](com-tn1m.md).
- E1: [met-m7wx](met-m7wx.md#resolution-editorial-boundary-closed) records the
  navigation corrections and preserves displaced implementation observations.

The comparisons were incorporated and their temporary proposal files removed.
The subsequent [detailed implementation conformance audit](com-nsxb.md) records
pinned traces, findings, unverified combinations and repair boundaries. Neither
review closure nor that static audit certifies compiler implementation, adopts
the first edition, or automatically resumes paused type-checker work. Current
work selection remains in the meta worklog.
