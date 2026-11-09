---
id: com-rv7l
status: closed
deps: []
links: [com-1hd3, com-nkoa]
created: 2026-11-09T14:53:00Z
type: task
priority: 2
assignee: Koji Murata
tags: [ownership, backend, mid]
---
# Compare and design guaranteed indirect value passing

## Purpose and Scope

Choose a bounded, semantics-preserving way to remove avoidable physical aggregate transfers from ordinary by-value parameters and implicit self. Start with method and design investigation, not product changes. [Existing observation](../../../evidence/performance-regression-history/value-self-abi.md) and its probe distinguish ARC savings from byval byte copies; compiler-wide contribution and recovery of com-1hd3 remain unproved.

## Work and Decision Boundary

1. Recheck the ownership-to-physical-ABI producer/consumer path in the selected revision and identify where stable storage, snapshot timing and ownership evidence are available.
2. Compare at least: existing byval plus LLVM optimization; guaranteed indirect passing of a stable evaluated snapshot/home; narrowly proved forwarding of an existing home. Use Swift/Rust primary design references and Plew contracts; record why rejected alternatives are unsafe or ineffective.
3. Define the owner of physical lane classification and its saved descriptor, required evidence, conservative fallback, caller/callee binding, temporary storage lifetime, invalidation and verifier obligations. Avoid a second source-type/effect/overload authority.
4. Specify when a snapshot is necessary: later argument evaluation, alias writes, shared cells/global/callback access, escape, return ownership, async acquisition and suspension. Unknown effects remain conservative. No new source borrow semantics, arbitrary size threshold, compiler-only shortcut, or blanket byval deletion.
5. Produce a finite scenario/entry matrix for direct calls, methods, generic/default adapters, closures, witness/existential entries, destruction glue, lazy/JIT and applicable external adapters. Unsupported cases keep a coherent existing ABI; explain how both sides agree, rather than silently mixing conventions.

## Deliverables and Completion

A recommended design and alternatives, source-to-consumer responsibility map, safety proof/fallback conditions, bounded prototype scope and measurement plan are recorded here; adopted contracts belong in [Representation and ABI](../design/representation-and-abi.md), [ownership](../design/ownership-and-access.md) and [pass contracts](../design/passes-and-optimization.md), without duplicating them. Obtain user approval before adopting a heavy ABI/architecture decision or new meaning; this ticket does not grant that approval. Independent review checks semantic preservation, feasibility and finite scope before the prototype begins. Update downstream scope from the findings. Investigation can conclude no viable approach, with evidence and explicitly deferred follow-ups; it does not certify optimization or performance recovery.

## Verification Plan

If no viable design is selected, explicitly defer the dependent tickets and
return to [com-1hd3's checkpoint](com-1hd3.md#interruption-checkpoint-and-return-procedure)
from this task; do not rely on the unexecuted integration task to arrange return.

Separate semantic controls, structural proof of actual byte-copy reduction, small-probe runtime and same-source old/new self-compilation. Fix source/std/toolchain/generation conditions and count analysis/code-size cost as well as benefit. No throughput claim from Swift assembly alone.

## Relationships and Exclusions

This is the next planning step for the optional ABI optimization, linked to com-nkoa and com-1hd3. Broad interprocedural effect precision is not a prerequisite unless this investigation proves a specific dependency. No product implementation, main/seed promotion, or closure of current phase-three guarantees.

## Plan Review

The independent fresh-context reviewer abi_optimization_plan_review checked the
three-ticket plan against compiler base 54761fea, existing evidence and ABI/pass
contracts. Its required no-go return paths and raw/optimized execution controls
were added; permanent safe snapshots were distinguished from temporary
implementation limitations. Re-review found those items resolved with no further
required plan change. Local links/anchors and acyclic dependencies were checked.
This accepts the task plan only, not an ABI design, implementation or speedup.

## Investigation Result and Recommended Design

Status: **proposal for decision, not an adopted ABI**. Source inspection uses
compiler 601a6eb3 (product source f65fa24e); the pre-existing local manifest,
binary and pycache changes are not part of this work. No product experiment or
new timing is claimed. The saved [Swift/Plew probe](../../../evidence/performance-regression-history/value-self-abi-probe.json)
is existing evidence, not a rerun. Implementation and measurement belong to
com-uiri after the decision gate below.

### Primary References and Interpretation

- [Swift calling convention](https://github.com/swiftlang/swift/blob/main/docs/ABI/CallingConvention.rst)
  separates source value/reference semantics, ownership and physical transport.
  Its guaranteed convention makes the caller responsible for validity through
  the call and is useful for forwarding. The paper includes design rationale,
  not a promise that every present Swift parameter uses its suggested default.
- [Swift SIL types](https://github.com/swiftlang/swift/blob/main/docs/SIL/Types.md#function-types)
  makes conventions part of lowered signatures. Its indirect guaranteed input
  requires an initialized pointee that neither side mutates; indirect owned and
  inout are different conventions. This is the closest reference for the
  proposal, not permission to convert an arbitrary source place to that input.
- [Swift ownership](https://github.com/swiftlang/swift/blob/main/docs/SIL/Ownership.md#guaranteed)
  ties a guaranteed value and its forwarding uses to a live base; the interior
  pointer section also requires dependent address uses to respect that base.
  Plew can enforce a finite internal storage contract without adopting Swift's
  full OSSA representation or adding source lifetime annotations.
- [Rust PassMode](https://doc.rust-lang.org/nightly/nightly-rustc/rustc_target/callconv/enum.PassMode.html)
  and [IndirectMode](https://doc.rust-lang.org/nightly/nightly-rustc/rustc_target/callconv/enum.IndirectMode.html)
  separate ordinary indirect pointers from the stack-offset/byval mechanism.
  This supports recording the physical convention explicitly; Rust's ownership
  and ABI defaults do not establish Plew's ARC/CoW proof.

References were read on 2026-11-10; linked main/nightly documentation can change.
Plew's [ABI](../design/representation-and-abi.md),
[ownership](../design/ownership-and-access.md) and [Mid](../design/mid.md)
contracts, rather than those other languages' defaults, own required behavior.

### Rechecked Producer-to-Consumer Map

Paths below are relative to src/ unless native/ is specified. They identify the
current code and the proposed owner, not evidence of an implemented change.

| Current producer or consumer | Observation and responsibility in the proposal |
| --- | --- |
| Mid/Build.pw: midEvaluatedValue, midArgumentNeedsOwnedHome, midTemplateArgumentOperand | Already creates evaluation-time owners for earlier child values and ambient roots. Preserve those semantic operations; a physical address must not delay them to the call. Ordinary synchronous whole parameters have a reuse case; self is explicitly excluded from that particular shortcut. |
| Mid/Build.pw: midCallReceiver, midSourceCallReceiver | Retains selected receiver passing and place provenance. Do not interpret every Borrow as a copyable value: unique read borrows and dependent shared places have different obligations. |
| Mid/Instantiate.pw: canonicalBorrowOperand, canonicalReceiverWithPassing | Preserves guaranteed uses and owned temporary scope; this removes call-edge ARC acquisition, not physical copying. |
| Backend/Llvm/GenMethods.pw: declareOneGenMethod; ProvidedFns.pw: declareGenFns | Builds logical signatures from finalized instance/signature facts. Supply lane roles/ownership to the common representation planner; do not rediscover types or effects. |
| Backend.pw: LlvmValueAbi, LlvmValueParameter, llvmValueAbiPassing | Current mapping only sees LLVM types and classifies sized struct/array values as indirect. Extend the common physical record rather than add a method-specific ABI. |
| Backend/Llvm/ValueAbi.pw: valueAbi, declareValueFunction, callValueFunction, valueParameter | Owns definition/call attributes and physical indices. Currently creates a byval slot from each aggregate LLVM value and loads incoming aggregate parameters. This is the replacement point for the transport protocol. |
| Backend/Llvm/Mid.pw: midCanonicalEmitDirectCall, midCanonicalEmitOperand, midPrepareCanonicalLocals | Currently reads values and stores parameters into fresh locals. Add an address-aware input/binding path; keeping these full-value load/store boundaries would defeat forwarding. |
| Backend/Llvm/Mid.pw: closure and existential call emitters; Closures.pw; Any.pw | Indirect entries and adapter-supplied abiParameterValues need the same typed lane protocol. An array of undifferentiated LLVMValueRef cannot distinguish a logical pointer value from an aggregate's home address. |
| Backend/Llvm/Async.pw, MidAsync.pw | Entry acquisition and frame initialization remain explicit owned operations; a caller stack address cannot become a suspended frame input. |
| Backend/Llvm/StmtDeinit.pw, Arrays.pw, Enums.pw | Synthetic copy/drop/destruction glue also uses the common call helpers. Preserve its ownership lanes; a consuming lane is not guaranteed merely because it has aggregate layout. |
| Backend/Llvm/ProvidedFns.pw: emitExposedEntry; CAbi.pw | External convention stays separate; boundary adapters convert values into the private protocol. |
| native/llvm_backend.cpp: demand definition rewriting | Copies function type, calling convention and attributes when substituting canonical stub declarations. Declaration and requested definition must derive identical protocol records across LLVM contexts. No second JIT/runtime is needed. |

### Alternatives and Recommendation

| Method | Safety and likely effect | Decision |
| --- | --- | --- |
| Keep byval and tune inlining/SROA/argpromotion | Correct baseline; saved final-machine-code recursion probe still copies whole self. Success depends on optimization and does not remove repeated unoptimized materialization. | Keep as comparison/fallback, not the selected remedy. |
| Pass a stable evaluated home through a guaranteed indirect lane, bind it directly for read-only use | Preserves required evaluation snapshots, can avoid caller staging plus ABI hidden copy plus callee copy. Incoming guaranteed homes can forward recursively without whole-value transfer. | Recommended core design. |
| Prove arbitrary original-place stability through interprocedural effects | Could eliminate more initial snapshots, but needs alias/escape/unknown-call reasoning and invalidation beyond this optimization. | Not a prerequisite. Limit reuse initially to the finite proof below. |
| Remove byval while retaining all value load/store staging | Can remove the hidden ABI copy but leaves both ends rebuilding the aggregate; addresses alone do not establish ownership or snapshot validity. | Useful diagnostic contrast only, not the final design. |
| Introduce borrowed source syntax, size thresholds or compiler-specific exceptions | Changes meaning or makes optimization depend on unrelated spelling/size. | Reject. |

Recommend one internal **GuaranteedIndirect** transport lane for sized aggregate
inputs whose finalized role is a guaranteed value. It is not a new language
borrow, not an owned/consuming input and not inout. The caller supplies an
initialized, sufficiently aligned, stable read-only home until synchronous entry
returns. The callee binds read-only parameter places to that home rather than
copying the aggregate into a second stack local. A local owning copy is acquired
by the existing Mid Copy operations if the value is stored, returned, captured
or otherwise needs independent ownership. The transport itself adds no retain
or drop and does not delay or delete an existing semantic Copy/Drop.

Do not add noalias, readonly, memory-effect or pointer-escape LLVM attributes
merely from this lane. Transitive reference payloads can be intentionally
mutable, two read inputs can alias, and the body can have unrelated effects.
Only separately proved attributes may be emitted. Dereferencing shared payloads
retains the existing access checks; stable outer bytes do not freeze identity.

Explicit unique borrow/inout and move lanes preserve their selected semantics
and current appropriate transport. Direct scalars/pointer values, omitted empty
values and return lowering remain unchanged. A readonly pointer representation
is not inferred from the layout of a unique or consuming value.

### One Physical Signature Authority

Extend the existing representation boundary with a physical signature record
containing logical lane type/role, ownership, physical index, transport, required
alignment, result protocol and hidden environment roles. Its inputs are completed
BodySignature/ClosureSignature/witness contracts and target/layout facts. The
LLVM type alone is insufficient: a pointer can be a value, inout, environment,
unique borrow or an aggregate home. Use a typed argument/binding carrier with
Value versus Home cases and explicit provenance; do not overload LLVMValueRef
arrays with undocumented address meanings.

The mapping is deterministic from the completed callable convention, not chosen
per call site from available optimization facts. Direct declarations store the
record; indirect calls lower their completed callable signature through the
same planner. Cache identity includes convention/roles, target/layout, protocol
revision and LLVM context, not just logical LLVM function-type equality. Native
function types/attributes and parameter binding must match that record.
Cross-request JIT modules reconstruct the same structural convention; raw LLVM
pointers or backend-local numeric record IDs cannot serve as session identity.

A call-site storage plan is distinct from the signature: it chooses an existing
proved home or a snapshot feeding the already selected lane. Failure to prove
reuse requires a snapshot under that lane, not silently changing the callee's
ABI. Legacy/byval entries may coexist only as explicitly described boundary
conventions with adapters; definition, caller and every indirect address user
must agree. Never select legacy solely because this caller lacks a body.

### Finite Storage Proof and Conservative Cases

For each supplied home establish: exact completed value type/layout, initialized
value and original evaluation occurrence; stable base lifetime/alignment;
unchanged value-world bytes until last synchronous use; and no escaping use of
the address. Copies of contained references retain their ordinary identity.

| Source or use | Required treatment |
| --- | --- |
| Incoming GuaranteedIndirect ordinary parameter or copyable self | Its caller contract guarantees the outer home. Forward the same home for compatible read uses, including recursion. Do not expose its address as a source pointer. |
| Completed anonymous value temporary | Reuse its dedicated home only if its Mid owner/scope covers the call and no move, replacement or write can intervene. Do not create another semantic owner just to pass its address. |
| Ordinary whole copyable immutable local | Use its finalized immutable-binding fact directly, together with initialized home, live owner and no capture-cell/address alias capable of replacing its outer bytes. No general effect solver is needed to rediscover declared immutability. This does not freeze reference payloads or waive mode/lifetime checks. |
| Earlier value argument followed by an effectful argument/default | Use the evaluation-time snapshot already required by Mid; creating a pointer only at call emission must not reread the old source place. |
| Mutable root, global, capture cell, reference dereference, indexed/accessor result | Do not infer stable value bytes from an immutable handle or a live cell. Preserve the selected getter/copy/borrow operation and timing. Copyable value inputs use a protected evaluated snapshot where necessary; a semantic borrow keeps its actual access/dependency contract and cannot be snapshotted to evade it. |
| Ordinary local not covered by the finite proof | Snapshot at the required evaluation point; broader place/effect reuse is optional future work. |
| Copyable self from a potentially aliased receiver | Consume the existing selected receiver and Access contract; make any required value snapshot at that contract's evaluation point, not at a newly invented order. Distinguish evaluated owner/cell pin from stable referent contents. The owned/read-only home inside the synchronous callee may then forward. |
| Storing/returning/capturing an incoming value | Perform the existing semantic acquisition before caller guarantee ends. Returning a reference-containing value is not returning a pointer to the parameter home. Preserve existing deinit timing and CoW behavior. |
| Async public entry | Home is valid only until entry returns; activation-input plan acquires/transfers owners into the frame before caller guarantee ends, even on synchronous first completion. Resume receives frame storage, never the caller's borrowed address. |
| Foreign call or callback | Keep external ABI. An exposed adapter owns/protects any converted input through its private call. Unknown foreign effects are not purity or no-alias evidence. |

No new whole-program effect solver is needed for these finite reuse proofs
(incoming contracted home, dedicated completed temporary and ordinary immutable
local under the storage conditions above). Ordinary same-call
overlap and unknown-effect cases must still preserve the existing snapshot and
access plan. If inspection cannot establish its required contract, the prototype
must report the gap rather than guess a different source meaning.

Storage planning belongs to verified Mid/representation preparation while typed
places and scopes remain available; LLVM emission consumes it. Do not put a new
AST lookup, method-name check or effect solver in ValueAbi.pw. Reuse preparation
must not repeatedly materialize or scan the whole body for every argument.
Concretely, build the backend-local storage plan from MidExecutableBody and the
completed physical signature at prepareCanonicalForLlvm/midVerifiedLlvmPreflight,
before publishing the LLVM-ready handle. An LLVM-ready value must retain that
plan, and emission must consume the same body/signature identity. Semantic
snapshot/acquisition operations remain authored before Mid ownership/access/drop
verification; if a missing semantic operation is discovered, fix its Mid
producer and rerun that preparation instead of inventing ownership in emission.

### Lifetime, Invalidation and Verification

Entry allocas belong to the function actually being emitted, including synthetic
thunks. Store at the source-prescribed evaluation point, never hoist evaluation
to the entry. A slot reused on loop iterations must not overwrite a value while
an earlier use/owner remains live. Lexical/full-expression cleanup and exceptional
nonlocal exits keep their current rules; no extra unwind/cancellation guarantee
is introduced. Pointer forwarding never extends a temporary's source lifetime.

Attach storage evidence to the prepared body/operation identity and exact
signature/environment/layout version. A change to body/CFG, ownership/access
elaboration, layout, signature or target invalidates affected plans; build them
after the relevant facts stabilize or explicitly regenerate after changes.
Cache reuse does not turn a stale address or matching type into fresh evidence.

Before executable publication, validate all logical/physical lane correspondences,
typed Value/Home cases, type/alignment, scope/base dependencies, readonly binding
uses and ownership acquisition. Reject missing, foreign, stale or mismatched
records as internal failures without a fallback that invents evidence. Conservative
snapshot selection handles absent optimization proof, not malformed IR. LLVM's
verifier alone cannot prove this semantic storage contract.

### Entry and Scenario Matrix

The table assigns required prototype/integration controls, not newly passing
tests. Preserve unsupported source diagnostics and do not claim them as coverage.
Raw LLVM/no-optional-optimization and standard optimized execution must agree;
optional Mid transformations additionally require enabled/disabled comparisons.

| Entry or scenario | Prototype (com-uiri) | Final integration (com-ffar) |
| --- | --- | --- |
| Direct ordinary aggregate parameter and read-only method self | Leaf/forward/recursive calls, final machine-code transfer counts and observed values; no size threshold | Same on final candidate, scalar/empty/nested/enum/CoW controls |
| Snapshot timing/aliases | Later argument/default mutation, mutable global/capture/cell callback; compare old/new values and cleanup | Full affected evaluation/receiver/access matrix, single evaluation and original writeback target |
| Parameter copied to local/return/environment | Independent owned copy, exactly-once lifetime/cleanup, reference identity/CoW unchanged | Escape and destruction edges including user deinit and cleanup callbacks |
| Generic/default/via adapters | One concrete generic and default forwarding chain through common signature records | Every affected synthetic family, receiver/result specialization and adapter agreement |
| Closure call and witness/existential call | Representative indirect entry for each; hidden environment/erased receiver stays distinct from home lanes | All affected direct/indirect paths including mixed guaranteed/inout/move lanes |
| Async entry and resume | Temporary aggregate/String input, first completion and suspension; prove frame acquisition before home ends | Closure/copy-self and unique move controls where currently supported, no address escape |
| ARC/drop/array/enum synthetic glue | Inspect lane classification and run representative actual cleanup | Audit all common helper users; consuming ownership never becomes borrowed by layout |
| Lazy/JIT requested body | Declaration versus requested-definition protocol equality and actual first/later invocation | Generic/closure/witness/default demand adapters; cache/context mismatch rejects |
| C/expose/C-compatible closure adapter | Keep foreign convention; execute representative adapter into private body | Both directions, no adapter retaining temporary homes; existing unsupported surfaces remain rejected |
| Malformed preparation | Wrong lane/role/type/index, missing/stale record, owner ending early, address escape | Production validator independently rejects each affected invariant; valid recovery |

### Bounded Prototype and Measurement Decision

Implement the common descriptor/typed carrier and the finite reuse proofs above,
with all users of the common physical helpers either migrated or explicitly
adapted. This is not permission to ship a direct-call-only ABI and leave indirect
calls inconsistent. The prototype matrix is a finite correctness feasibility
sample; com-ffar owns exhaustive reconciliation of the changed protocol's users.
If the descriptor migration cannot fit a reviewable implementation unit, split
com-uiri into producer/binding and consumer/adapter units before coding, preserving
the single protocol and the end-to-end prototype acceptance.

Before code changes, fix the old candidate, exact input/source/std/toolchain,
native optimization pipeline and final-generation conditions. Establish structural
RED where transfer removal is expected; semantic controls may already be GREEN.
Do not count broken fixture setup as RED. Required snapshots must remain visible
in structural controls, not merely survive by accident in optimized execution.

Measure separately: (1) optimized aggregate load/store/byte transfers and stack
scratch in the saved recursion probe, (2) native probe execution with identical
work/output and repeated balanced samples, (3) same latest compiler source with
old/new candidates in alternating order, at least five samples each under the
existing comparison procedure, (4) formal self-host fixed-point median after a
candidate merits adoption, (5) preparation overhead and generated code size.
Hash inputs, scripts, candidate and outputs. Never overlap formal self-host with
other builds/tests. Investigate unstable sampling instead of deleting slow runs.

Recommend integration only if semantic/structural controls pass, independent
review supports the proof, the expected physical transfers are actually removed,
and measured total compile/runtime cost justifies the complexity. No numerical
speedup is promised. A time difference consistent with noise is inconclusive;
repeat a bounded comparison or explicitly choose no-go/seek a justified tradeoff,
not claim recovery from fewer copies. Current com-1hd3's ~0.68s matched regression
is not attributed to this ABI without new evidence. Existing performance stop
conditions remain in force; failed local trials do not prove repair difficulty.

### Adoption and Completion Gate

The recommendation changes a private physical ABI and its saved contracts, so
present this concrete design and tradeoffs to the user before adoption/prototype.
com-rv7l may close as **investigated** after independent review and requirements
reconciliation; that closure is not design approval. com-uiri retains an explicit
approval gate even when its tk dependency becomes closed. No canonical design
chapter is changed to claim this proposal is already adopted. After approval,
update only the relevant ABI/ownership/pass contracts, then execute the prototype.

If no-go at either investigation or prototype, defer downstream implementation
and follow com-1hd3's recorded return procedure. Its source/candidate checkpoint,
unresolved performance acceptance and phase-three guarantees remain intact.

### Completion Reconciliation and Independent Review

The [Swift mutability supplement](../../../evidence/performance-regression-history/swift-mutability/README.md)
adds source and fresh native/SIL/LLVM/assembly evidence about let/var/self.
It refines this still-unadopted proposal to include ordinary immutable locals
with explicit storage/lifetime conditions. It neither adopts the ABI nor claims
that all Swift let storage is physically forwarded without a copy.

Outcome: **investigated; recommendation awaits user adoption decision**.

| Original obligation | Evidence in this task |
| --- | --- |
| 1. Recheck producers and consumers | Rechecked map above; compiler src tree 23fb2885e3c354e1d73d268033fe5444afeda9a4 and native tree ec09e772869e6b129d1429dc114fa3e8bd3dee5e match f65fa24e; no product edits |
| 2. Compare methods with Swift/Rust | Primary references and alternatives table; proposed indirect homes versus existing byval and broader effect analysis |
| 3. Assign owners, evidence, fallback, binding and verification | Single signature authority, typed carrier, storage plan at executable-to-LLVM-ready admission, lifetime/invalidation/verification sections |
| 4. Preserve snapshots and ownership | Finite storage-case table, explicit receiver/unique distinction, return/capture/async and unknown-effects obligations |
| 5. Cover entry families | Entry/scenario matrix and updated com-uiri/com-ffar scope; unsupported entries retain coherent protocols |
| Bounded prototype, measurement, review and next owners | Prototype/measurement decision and adoption gate; actual tk chain com-rv7l -> com-uiri -> com-ffar (prerequisite first), no cycle |

Fresh-context reviewers guaranteed_abi_design_safety_review and
guaranteed_abi_design_feasibility_review independently checked the task against
the source/contract boundary and Swift material. Both support investigation
closure with no required fixes. Their unproved concerns remain explicitly owned
by com-uiri: first receiver-home stability, synthetic/adapter migration size,
semantic storage-validator implementation and total analysis/transfer cost.
They are prototype proof obligations, not findings that the implementation has
passed. The latest executable-to-ready planning paragraph and downstream updates
were included in their review. Optional plan counters may aid cost explanation;
pinning upstream main links may improve reproducibility. Neither is required
for this investigation; source references include read date and mutability.

All task-local links/headings and dependency acyclicity were checked; source and
native diffs against f65fa24e are empty. Product tests, new Swift/Plew probe
execution, timing and full-suite/fixed-point gates were not run because this is
an investigation/document change. Their owners remain com-uiri/com-ffar. Closing
this task does not certify those gates or resolve com-1hd3's performance issue.

