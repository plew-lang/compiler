# Standard Library Boundaries

**Status:** Reviewed design supplement. This supplement assigns source ownership and public routes for the adopted foundation, reference and communication contracts. It does not claim implementation, select a physical repository layout, or define every standard package API. The language specification owns source semantics; the first-edition synchronization of the sharing and unique-generic proposals is tracked by [the whole-reference review](../issues/com-7knz.md).

## Responsibility and Public Ownership

[Sources and Modules](sources-and-modules.md) owns package admission and declaration identity. This supplement assigns the standard declarations that those services admit. Public package routes, declaration ownership, private construction and native runtime linkage are distinct decisions. `@Std/Sync` is one reserved standard package name, not an externally addressable directory within Core.

| Public package | Owned surface and boundary |
|---|---|
| `@Std/Core` | Core-owned scalar/String declarations and protocols, Buffer, Ref, MutableRef, FrozenRef, WeakRef and Weakable, drop and replace, and core formatting/conversion. Existing Core public routes remain. |
| `@Std/Hash` | Hash, Hasher and the existing hashing surface, depending on Core. Existing Hash public routes remain; no relocation into Core is implied. |
| `@Std/Lang` | The language-item entry: Core scalar/String reexports and the defining declarations/implementations for Optional, Result, Array, Dictionary, ranges, Promise and JoinHandle. It admits Core and Hash; its implicit surface remains exactly the specification's fixed type list. |
| `@Std/Async` | Existing explicit timer/async helpers above the common runtime. It does not own Promise or a second scheduler. |
| `@Std/Set`, `@Std/Random` | Existing explicit collection/random surfaces above their Core/Hash dependencies. They are not new language items. |
| `@Std/Sync` | MutexRef and MutexGuard; Sender, Receiver, BoundedSender, channel construction, communication errors and per-operation cancellation. Synchronization and worker communication depend on Core; Core does not import Sync. |
| `@Std/Ffi` | The existing explicit foreign-pointer, boundary and bindgen-facing surface. It depends on Core; it is not a source dependency of Core's internal allocation mechanisms. |
| `@Std/Io`, `@Std/Process` | Existing I/O and process services, using Core and any explicitly admitted Ffi/Sync services they require. They do not become Core dependencies to provide diagnostics or initialization. |
| `@Std/Http` | Existing HTTP-facing services above the foundation and applicable I/O services. No HTTP surface or dependency becomes implicit through Core. |
| `@Std/Testing` | Existing test facilities above their admitted foundation/services. Production Core/Sync declarations do not import Testing to host their tests. |

The table fixes ownership for the foundation and synchronization surface, not a requirement that every higher package depend on every lower one. Selected source roots and explicit use edges determine the actual DAG. Core has no standard-package use edge; Hash depends on Core, Lang on Core/Hash, and Sync on the admitted Core/Lang foundation. Ffi is independent of Sync. Other standard packages can depend on either and on lower services without reverse edges. Test targets are separate consumers, not production reverse dependencies. Startup admits the fixed Lang/Core/Hash source closure and registers declaration identities before validating their operation contracts or checking bodies. Core code can refer to the admitted language-item identities without introducing a reverse source use or requesting Lang again. Ambient name availability and body/instantiation dependencies are not extra use edges; they must not conceal an explicit source cycle. No new umbrella package, blanket reexport or standard-library prelude is introduced.

The ownership table preserves the existing Lang/Hash/Async/Set/Random entry points as well as Core; it is not a silent consolidation into Core. Existing explicit reexports retain original declaration identity. A declaration has one defining module and one semantic identity. A public facade can use ordinary explicit `pub use` without creating a second type, conformance or intrinsic identity; it must not be needed to compensate for an illegal dependency cycle. Parts organize implementations within their defining module under ordinary part rules. They are not arbitrary file inclusion for declarations or an internal-visibility escape hatch. Physical source files, native runtime sources and distribution archives need not have one-to-one correspondence with these public packages.

## Private Construction and the Common Runtime Floor

Fields representing cells, counters, locks, completion state, queue links, restoration descriptors and worker identities remain private. Ordinary module visibility applies to standard code too. A package name or membership in the standard distribution grants no access to another module's private factory. Do not add friendship, package-private visibility, general unsafe construction or a user-callable raw Ref API merely to connect these packages.

| Producer and defining owner | Guarantee consumed downstream |
|---|---|
| Core reference factories and conversions | Valid initialized shared cell; frozen/mutable authority and typed ownership operations |
| Core strong-reference weak operations; Sync MutexRef.weak | Correct weak control and restoration to exactly R, through the [typed weak operation contract](representation-and-abi.md#typed-operations-and-weak-restoration) |
| Sync MutexRef.lock / tryLock | A unique nonsendable Guard retaining the exact locked cell; no public Guard factory |
| Lang async/spawn/join construction; Sync channel operations | Destination-affine completion state with exactly one terminal result, using [typed outcomes](runtime.md#typed-outcomes-and-worker-results) and the [completion protocol](runtime.md#cross-worker-completion-delivery) |
| Sync channel construction | Matching endpoints, one receiving worker, owned transport and admitted typed payload operations |

The native/generated runtime floor connects these producers by validated operation contracts, not source-level private-field calls. [Declaration registration](sources-and-modules.md#compiler-known-declaration-contracts) binds each required operation to its exact admitted declaration/signature and ownership/effect contract. Lowering can issue only the corresponding typed internal operation. A method with equal spelling in another module cannot request those capabilities. This is a bounded integration of the already trusted standard reference/scheduling operations, not privilege for all declarations in Sync.

For example, MutexRef.weak in Sync supplies its admitted cell and restoration contract to the common weak operation, which produces Core's WeakRef[MutexRef[T]]. Core's generic upgrade consumes the saved R restoration descriptor; Core source need not import MutexRef or inspect its private representation. Likewise, a Sync receive registers typed result/completion obligations through the common runtime; it does not manufacture a Promise by writing Lang fields, expose a public resolver, or use an unrelated async implementation. Source and witness identity, type-specific copy/drop behavior, RC mode and destination affinity survive this handoff. Intrinsic registration, lowering, ABI and runtime consumers must be changed together.

These operations must not let ordinary callers construct arbitrary WeakRef values, duplicate a unique Promise result, create an unlocked Guard or complete another worker's local Promise. The library owns queue policy and public APIs; the runtime supplies synchronized transport, typed payload operations, destination notification and local completion. It does not infer source types or select user overloads. Low-level operation encoding and helper names remain implementation details, with admission and negative validation required before claiming a working implementation.

## Explicit Names and Language Items

The existing language-item list remains the complete implicit surface. Promise and JoinHandle remain available for their async/spawn syntax; this does not make every Core declaration implicit. Ref, MutableRef, FrozenRef, WeakRef, Weakable, Buffer, drop, replace and all Sync names require ordinary `use` when named. Traits remain explicit even when syntax implicitly dispatches through their admitted identities.

Using `.*` on a known reference or calling an already resolved method does not perform a fresh lookup of the pointer type or Weakable name. Lang/Core/Hash can be admitted to bind language items without importing all their public names into each file. The Lang entry is a manifest/defining module, not permission to make arbitrary future exports implicit. Loading Sync does not itself create workers or impose atomic RC on an otherwise nonsharing AOT program. Compiler-known representation is neither implicit visibility nor a second namespace authority.

## Channel Construction and Operation Results

The following are public interface signatures; implementations and ordinary visibility checks are still required. Payload parameters admit copyable and unique sendable types. Sender and BoundedSender are copyable and sendable for their admitted sendable payload types, regardless of the payload's copy capability; Receiver is copyable but remains nonsendable and bound to the creating worker. All endpoint, operation, control and error types below are exported by the Sync root; a public result never relies on an unnameable internal type.

```plew
// @Std/Sync
fn channel[allowunique sendable T]() -> (sender: Sender[T], receiver: Receiver[T])
fn boundedChannel[allowunique sendable T](capacity: U64)
    -> (sender: BoundedSender[T], receiver: Receiver[T])

// Existing basic contracts are unchanged.
// Sender[T]
fn send(value~: move T) -> Result[(), SendError[T]]
// Receiver[T]
fn receive() -> Promise[Result[T, ChannelClosed]]
fn close()
```

Each construction call creates a new transport and a Receiver for the current worker. There are no public independent Sender/Receiver factories or user-supplied worker IDs. Copying endpoints shares this transport; it does not create another channel. The labeled record needs no new Channel wrapper or destructuring syntax. Sending the resulting Sender to a worker follows ordinary sendability; the Receiver is kept by its creator. Copyable payloads use normal value arguments; unique owned locals use explicit move under the adopted generic mode adaptation.

SendError[T] is an autounique enum with `Closed(value: T)`. A consuming match recovers an unsent unique payload without permitting partial moves from unique structs. ChannelClosed is an inert copyable error value. Its construction creates no resource or authority. A successful send transfers the value into the transport's responsibility, not proof of receipt or processing.

### Explicit Receive Cancellation

```plew
// Receiver[T]
fn receiveCancellable()
    -> CancellableChannelOperation[Result[T, ReceiveError]]
// ChannelCancellation
fn cancel() -> Bool
```

ReceiveError is a copyable enum with `Closed` and `Cancelled`. CancellableChannelOperation[allowunique T] is a public autounique enum with one variant, `Registered(result: Promise[T], cancellation: ChannelCancellation)`. Registered identifies the operation bundle, not a still-pending state; completion may already have occurred. The caller destructures the whole enum with a consuming match when unique to obtain the Promise and control as separate locals. It is not a unique-bearing unnamed record or a struct requiring a partial move. The same wrapper serves cancellable receive and send; it grants no new receipt or cancellation capability by repackaging already owned values. ChannelCancellation is a copyable nonsendable control for exactly one operation on its initiating worker. It has no public factory and carries no result-receipt right. A copy shares the same cancellation right; it does not create another reservation. It may be retained separately while a unique result Promise is consumed by await. Internally it must not keep a terminal reservation or its payload alive merely because the control survives.

`cancel()` returns true only when that invocation changes a still-unassigned operation into cancelled. It returns false after assignment, after the operation completes with Closed, or after an earlier successful cancellation. It neither rolls back receipt nor requeues a value. Dropping the result or control does not cancel. The existing atomic winner, FIFO removal, late-notification and pending-work contracts apply; this API supplies names and ownership without a general Promise cancellation feature.

### Bounded Sending

```plew
// BoundedSender[T]
fn send(value~: move T) -> Promise[Result[(), SendError[T]]]
fn sendCancellable(value~: move T)
    -> CancellableChannelOperation[Result[(), CancellableSendError[T]]]
```

Capacity is fixed at construction. It bounds accepted values waiting in the buffer, not pending sends, registered receives or work already handed to a receiver. Zero capacity is a rendezvous channel: a send is accepted only when assigned to a waiting receive. Positive capacity admits a send when it can be assigned directly or occupy a free slot. There is no synchronous thread-blocking capacity wait, silent eviction or Full error on these asynchronous methods. Applications must still limit the number of outstanding operations.

Before acceptance, the send operation owns the payload and retains its initiating loop's result-delivery obligation. Every unterminated send also retains internal producer ownership: losing the last public BoundedSender does not disconnect a still-pending send. Release this ownership once acceptance, cancellation or closure failure is committed. A terminal result Promise or surviving cancellation control does not retain a hidden sending endpoint; explicitly stored Sender values inside user payloads remain ordinary owners. This mirrors the receive operation's independent internal ownership. Acceptance moves it once into buffer/receive ownership and schedules success on the sender's initiating loop. Receiver closure or disappearance before acceptance returns the payload in SendError.Closed. Accepted values retain the ordinary drain-on-close and one-time disposal rules. Queued sends are admitted in their registration order under the synchronized transport; a later send cannot bypass an earlier valid waiting send. Older buffered values and earlier valid waiting sends cannot be bypassed by a new direct handoff. Zero-capacity acceptance and assignment to a receive reservation commit together: if receive cancellation wins first the send remains unaccepted; if pairing wins, cancellation of either operation fails. Cross-worker wall-clock invocation order and scheduler fairness are not promised.

CancellableSendError[T] is an autounique enum with `Closed(value: T)` and `Cancelled(value: T)`. The cancellable operation uses the same acceptance protocol, with cancellation as another possible winner before acceptance. A successful `cancel()` removes the waiting send and transfers the owned value to its cancellation result, delivered at the initiating worker. After acceptance cancellation returns false, even if success has not yet been observed by await. Control identity, late notifications and terminal-result disposal follow the same common protocol as receive cancellation. Noncancellable send has no hidden cancellation; its dropped result still requires eventual delivery/disposal if the send completes. No global abort token, per-worker cancellation or trySend API is added.

## Rationale, Alternatives and Validation

[Rust's core](https://doc.rust-lang.org/core/) and [alloc](https://doc.rust-lang.org/alloc/) separate basic facilities from allocation and platform services. Plew already assumes managed allocation and an event loop, so it does not reproduce Rust's no_std feature matrix. [Rust std](https://doc.rust-lang.org/std/) groups synchronization and message passing while keeping I/O separate. [Swift SE-0433](https://github.com/swiftlang/swift-evolution/blob/main/proposals/0433-mutex.md) places Mutex in an explicitly imported Synchronization module. These support a focused Sync package; they do not determine Plew's guard, sendability or callback rules.

Keeping all references, channels and their implementations in Core could avoid cross-module construction handoffs, but would make every language-item input carry an expanding synchronization surface and tie private ownership domains together. Splitting every Ref/WeakRef into its own public package would instead multiply routes and disturb existing Core users. The chosen boundary preserves Core routes, separates optional synchronization, and makes the narrow trusted handoffs explicit. A public Promise resolver, generic raw-cell constructor or new visibility keyword is not required by this first edition. Future public asynchronous producer APIs need their own source contracts rather than inheriting access from this internal floor.

[Rust's prelude](https://doc.rust-lang.org/std/prelude/) contains widely used traits and functions. Plew deliberately keeps the smaller, syntax-defined implicit list and explicit trait names. [Rust sync_channel](https://doc.rust-lang.org/std/sync/mpsc/fn.sync_channel.html) supplies a useful bounded/rendezvous model; Plew expresses waiting as destination-local Promise operations rather than blocking a worker and retains its own explicit cancellation and nonsendable Receiver rules.

Review a new library operation by tracing its defining declaration, package edges, visibility, saved typed operation, resource owner, final completion/destruction and public import route. Validation must reject forged standard names, direct private construction and cross-worker completion access; demonstrate the Lang/Core/Hash foundation without Sync, explicit Sync use, same-identity reexports and retained language-item shadowing; and cover copyable/unique construction, consuming enum extraction with a unique Promise, cancellation/acceptance/closure races, pending sends after public sender loss, zero-capacity rendezvous, FIFO and dropped-result disposal. AOT and JIT consume the same runtime contracts, including managed pause and final-release rules. These are validation obligations, not executed tests.
