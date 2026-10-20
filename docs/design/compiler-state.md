# Compiler State, Identity, and Computation

**Status:** Reviewed draft. This chapter specifies shared contracts derived from adopted decisions. It does not introduce a universal query engine or choose the unresolved physical storage strategy for checked bodies.

Detailed producer-to-consumer obligations, saved-fact admission, and bounded
implementation observations are retained in [Frontend Handoffs](frontend-handoffs.md).

## 1. Responsibility

This chapter owns the rules for identifying compiler inputs and results, constructing and publishing results, and reusing them within a compilation session. Domain chapters own what those results mean: lookup chooses candidates, checking establishes source meaning, instantiation discharges concrete obligations, and mandatory analyses establish their own validity guarantees.

The purpose is practical: when adding a computation, a contributor must be able to identify its key, its decision owner, its permitted dependencies, and the consumers entitled to use its result. A cache must not become a second semantic authority.

## 2. Sessions and Input Identity

A session admits one consistent set of source versions, resolved dependencies, compiler options, and target configuration. Later requests operate on these admitted inputs. They must not reload an edited file into the existing semantic universe. A new input version requires a new session unless a future, separately designed invalidation mechanism proves which results remain valid.

The session owns mutable construction state and the lifetimes needed by published results. Callers request operations through its boundaries; an escaping mutable arena would allow callers to invalidate the guarantees of already published results. Whole-target checking and execution preparation may transfer ownership of this same state rather than reconstructing an unrelated compiler and attaching an old success token.

An active demand session has one [compiler-affine control owner](driver-and-execution.md#worker-demand-coordination), independent of application workers. Session/registry access occurs there after native request routing; sending an identity is not sending a nonsendable session value. The service begins application-triggered preparation only under the runtime's managed-pause grant. Common runtime implementation does not merge compiler/application state ownership.

Persistent caches, cross-session ID stability, and incremental invalidation are not promised here. An integer that happens to match in two sessions is not a shared identity. Native handles must preserve session association and reject stale or foreign use at their admission boundary.

## 3. Identity Domains

| Identity | What it identifies | What cannot substitute for it |
|---|---|---|
| Source/node identity | A location or node in admitted syntax | Equal text in another file or version |
| Declaration identity | A declaration in its module and lexical context | Name spelling alone |
| Binder identity | One lexical type parameter | Another parameter also spelled `T` |
| Source body origin | The lexical body whose meaning is checked | A copied provided body or an arbitrary current cursor |
| Body instance | A body origin interpreted in a complete instance environment | Function name, receiver layout, or type arguments without their binders/evidence |
| Type identity | A semantic type in its owning context | LLVM type equality or source spelling |
| Evidence identity/context | The admitted reason an obligation holds | A same-shaped receiver or proof of a different requirement |
| Native symbol/session handle | A published native entry or registered session | Permission to skip checking or proof that its owner is alive |

IDs are opaque outside their owning API even if represented as array indices. Sentinel values and bounds checks are representation details; neither a nonzero ID nor an existing row proves successful preparation. Diagnostics retain provenance separately from semantic identity, so moving a diagnostic attachment does not create a different type.

An instance environment carries lexical binder substitutions, the selected receiver where applicable, and the evidence needed for associated outputs or a provided body. Substitution must not read whichever receiver or scope happens to be installed in a mutable cursor. Environment equality must include every component that can change the result. Individual domains may use a smaller key only when their result is independent of the omitted components.

## 4. Construction, Publication, and Consumption

Construction has one owner. Its private work may be incomplete; consumers must not observe that work as a successful result. Publication is the boundary at which the owner checks completeness for the promised scope and returns an artifact with read permissions appropriate to that scope.

Successful publication guarantees that required facts exist, belong to the advertised owner and environment, and cannot later be independently overwritten. A later stage may derive a new result; it must not silently revise the earlier result's meaning. An abstract obligation can be a complete source-level result while remaining unresolved for execution. This is explicit content of the result, not a partially initialized concrete answer.

| Operation | Permission and obligation |
|---|---|
| Begin construction | Establish the owner, key, and dependency context; keep incomplete state private |
| Publish success | Establish all guarantees of this result kind; expose no writer that can invalidate them |
| Read optional fact | Distinguish legitimate absence from failure or incomplete preparation |
| Read required fact | Require the correct successful artifact; missing required data is an invariant failure, never permission to reselect source meaning |
| Instantiate | Preserve source-selected identities and explicitly discharge instance-dependent obligations |
| Validate | Check the published meaning under the analysis's rules; do not invent a replacement interpretation |

The capability is scoped. Source-body success is not ownership-analysis success; local analysis is not interprocedural closure; checked declarations are not executable publication. These distinctions apply to synthesized code, globals, closures, and default generators as well as ordinary functions. Their detailed producer/consumer contracts belong in their domain chapters.

## 5. Requests, Dependencies, and Failure

A request identifies a computation kind and its complete key within a session. Its implementation owns the answer. Dependencies must use their owning boundary rather than inspect another computation's construction scratch or rerun its selector.

The following states describe the protocol, not mandatory enum names:

| State | Allowed behavior |
|---|---|
| Not requested | Start the owning computation when demanded |
| Active | Record or diagnose dependency re-entry according to the domain's cycle policy; do not return unfinished data as success |
| Succeeded | Reuse the result under the same validity contract |
| Failed | Preserve failure and diagnostic provenance; do not reinterpret partial storage as success |

A successful result with deferred obligations is not a fifth, ambiguous request state. The obligations are part of its scoped guarantee. A genuinely suspended computation, if introduced, needs an explicit continuation and completion protocol rather than a Boolean marked ready.

Recursive functions do not inherently create illegal preparation cycles. Registered signatures allow a source body to check a call without recursively checking the callee's body. Interprocedural analyses may explicitly construct a graph and solve recursion using their own worklist or fixed-point rules. That graph algorithm does not authorize arbitrary cyclic queries to consume incomplete facts. Each domain must specify which cycles are legal, what is available while visiting them, and when its result becomes publishable.

A failed request must remain failed for the unchanged inputs. Diagnostic rendering or deduplication may be centralized, but must not erase the cause or turn a retry into success. This contract does not require every failure to poison unrelated requests: the driver determines whether the command/session can continue, while an execution failure must prevent unsafe execution through that session.

Temporary lexical context must be restored on every exit, including failure. Restoring a cursor prevents incidental corruption; it is not a substitute for explicit owner/environment arguments in authoritative results.

## 6. Storage and Cost Boundaries

Logical ownership and physical allocation are separate. Shared interned types, immutable pools, and indices are compatible with owner-scoped results if references retain their context and published facts cannot change. Plew's value semantics and CoW preserve snapshots, but do not make snapshot acquisition or later mutation free.

A consumer should acquire the required result/context at its preparation boundary and reuse it while consuming that body. Reading one fact must not require constructing a snapshot of every owner's mutable tables. Appending another owner's facts must not invalidate existing readers. Designs must account for retain/drop traffic, CoW separation, index lookup, and the lifetime of referenced pools rather than describing a value copy as costless.

The physical checked-body storage choice remains open:

| Candidate | Benefit | Cost or condition to resolve |
|---|---|---|
| Owner-scoped immutable payload | Direct completeness and lifetime boundary; unrelated owner construction need not copy its facts | Per-owner allocations and references to shared types/evidence; publication and lookup layout must be specified |
| Shared immutable store with prepared handles | Compact shared storage and cheap indexed access | Must specify how append/build work coexists with immutable publication without global CoW copies or exposed mutable state |

Neither candidate is adopted by this chapter. The body-checking design must resolve this comparison using concrete saved fields and consumer paths before implementation resumes. A new typed IR is also not implied by the need for immutable results.

## 7. Example and Change Impact

Consider checking a generic source body once and preparing two concrete instances. Source checking publishes its selected trait requirement and abstract evidence under lexical binders. Each instance substitutes its own environment and resolves the legitimate concrete witness for that same requirement. Neither instance searches unrelated same-named members. Both can share the source artifact; their concrete facts cannot be keyed only by the source body ID.

If source checking fails, requesting either instance cannot bypass the failure by finding a registered function row. If an instance fails, an unchanged retry cannot succeed by reading partially appended finalization entries. If checking a second source body appends facts, readers of the first published body retain its exact meaning.

For a new cached computation, review its input identity, key completeness, publication guarantee, cycle behavior, failure reuse, and final consumer together. For a new generated body, establish its source origin and environment before adding a cache. For a new native callback, establish session lifetime and stale-handle behavior before passing an ID across C.

Validation should cover repeated success and failure, foreign-session/foreign-owner rejection, distinct lexical binders with equal names, two instances with different evidence, and stability while another owner is prepared. Domain execution tests must also show that the final consumer uses the published result; reader-only tests cannot establish that end-to-end property.

## 8. References and Plew's Choices

[Rust's query model](https://rustc-dev-guide.rust-lang.org/query.html) separates keyed computations from their providers and memoizes results. It motivates explicit keys and dependency ownership here. Plew does not thereby adopt Rust's generated query framework, disk cache, or incremental dependency machinery. Request granularity must follow Plew's guarantees rather than copying Rust's query names.

[Swift's request-evaluator design](https://github.com/swiftlang/swift/blob/main/docs/RequestEvaluator.md) identifies hidden mutable AST dependencies, coarse lazy callbacks, and cycles as architectural problems. Its account supports keeping authoritative construction behind request boundaries. The document also describes transitional caches and open projects; it is not evidence that every Swift result is immutable today. Plew should not duplicate mutable state merely because an incremental migration can temporarily require adapters.

[Rust's memory-management account](https://rustc-dev-guide.rust-lang.org/memory.html) explains arena lifetimes and interned types. Plew can retain the same distinction between semantic identity and allocation strategy without importing Rust lifetimes or pointer equality into source semantics. Its own ARC/CoW costs must determine the physical representation.

## 9. Implementation Mapping and Audit Limits

Inspected source base: `6fe09bc7c0e75260b3f773643921478b5020b94f` (documentation changes excluded). Focused reading covered [`CompilerSession` and preparation result types](../../src/CheckedProgram.pw), [`InstanceEnvironment`](../../src/Ir.pw), and the [native session registry](../../src/CompilerSessions.pw). The session hides mutable `Comp`; instance environments carry substitutions, receiver, and proof; the registry uses non-recycled numeric IDs and shared cells, with ORC destruction required before unregistering.

These observations do not prove every request key, writer, cycle path, or final reader satisfies this chapter. The paused type-checking work includes unresolved physical publication/storage boundaries and source-selection duplication. No new runtime or performance experiment was performed for this chapter. [Owner publication and final-consumer closure](../issues/met-si6j.md) tracks the retained migration boundary; absence of additional issue links is not an implementation-completeness claim.

Chapter review found no blocking design problem. Physical storage and domain-specific publication APIs still require resolution in their owning chapters; this review does not certify their implementation.

## Unresolved Checked-body Storage

The concrete ownership/storage choice and implementation restart requirements are
in [Checked-body Storage](checked-body-storage.md); this chapter retains the logical
session and publication contracts. [met-si6j](../issues/met-si6j.md) tracks whole-path
completion, rather than equating private stores with a sealed successful owner.
