# Collections and the Safe Buffer Floor

**Status:** Design supplement. This document consolidates the adopted storage
boundary and its proof obligations. It is not an audit certifying every current
Buffer operation, optimizer, library collection, or target. The
[Buffer specification](https://github.com/plew-lang/spec/blob/main/spec/01-basics/02-basic-types.md#buffer)
owns public methods, panic, capacity and value behavior. [Runtime](runtime.md)
owns execution protocols; [Ownership and Access](ownership-and-access.md) owns
semantic transfer and place elaboration; [Representation and ABI](representation-and-abi.md)
owns physical calls/layout. This supplement owns their collection-specific
composition and rationale, not competing definitions of those contracts.

## Why the Floor Owns Lifecycle

Plew hides storage mechanisms and costs while keeping meaning and provenance
explicit. Safe Plew code, including standard-library code, does not manually
initialize raw element slots, invoke synthesized copy/drop witnesses, or adjust
reference counts. Those witnesses cannot be named, overridden, or called as a
user-defined lifecycle API. Source unique deinit is the separately specified
visible destruction hook.

Given that premise, a capacity-only storage floor cannot delegate element
lifecycle to ordinary Plew collection code. Buffer owns count, initialized extent,
CoW separation and typed element operations together. This is a consequence of
Plew's chosen internal-language boundary, not a universal indictment of raw
storage designs. Non-atomic ARC, monomorphization and the restriction of deinit
to unique types are not independent proofs of this conclusion.

Public Buffer permits user collections to use the same safe storage operations
as the standard library. No privileged Array/Dictionary implementation receives
an unchecked slot API. The split encloses the lifecycle boundary: Buffer owns all
operations touching element initialization/liveness; library collections own
algorithms using complete value operations. Adding a lifecycle primitive requires
justifying why the existing finite floor is insufficient.

## Conditional Safety Argument

For copyable T, invariant I requires:

- Exactly `[0, count)` contains initialized, valid T values owned by the backing;
  `[count, capacity)` is uninitialized and cannot be read or destroyed.
- Every live element has the ownership required by its finalized type contract.
  Reference-bearing elements have the corresponding owned shares; a byte slot
  alone is not evidence of ownership.
- Shared backing is not observably mutated. A write first establishes private
  writable storage and preserves the values of other owners.

The proof obligation for each admitted operation is preservation of I, bounds
and checked allocation arithmetic, no raw slot/pointer/uninitialized-region or
long-lived element-borrow escape, and valid observable state at reentry points.
The operation cannot silently discard an owner: retired elements are destroyed
or ownership is transferred to a returned value. The compiler-generated typed
copy/drop operations, allocator and access protocols are assumptions of this
argument and need their own correctness evidence.

Under these assumptions, sequential composition of safe operations preserves
Buffer memory invariants. This closes the floor's proof surface over a finite
operation vocabulary instead of proving every future collection's raw memory
code. It does not prove every collection algorithm correct, prevent ARC cycles,
force a program to release every retained owner, cover unsafe FFI, certify thread
sharing, or establish that the current implementation satisfies the assumptions.
There is no unconditional claim that every possible collection is leak-free or
race-free. Whole-program concurrency/atomicity follows the runtime contract,
not an additional theorem derived merely from dense storage.

### Commit Before Release

Panic aborts rather than unwinds, but this does not make release side-effect-free.
A copyable Ref holding a unique payload may release its last owner and invoke
user deinit synchronously. Therefore prepare bounds checks, checked arithmetic,
allocation and new-value ownership before mutation; commit a valid post-operation
state; only then release retired elements or backing. After release, do not use
stale pre-operation storage/state. Reentrant observation must see a valid committed
state, subject to ordinary access-conflict enforcement.

Set first acquires the replacement owner, commits the slot, then releases the
retired value. Remove shrinks the live extent and transfers the removed owner to
the result. Clear/truncate commit the shortened count before releasing the retired
range. Relocation transfers live owners without treating stale source bytes as
additional live values. A floor mutator does not take a user comparator to call
inside a temporarily broken representation; nonmutating predicate algorithms
remain possible under ordinary calls/access rules.

## Representation and Finite Intrinsic Vocabulary

Buffer is an opaque intrinsic primitive with one pointer value. Count, capacity,
reference-count state and contiguous element storage belong to one heap backing
block in the chosen representation.
The exact header byte order, padding, pointer origin, growth policy and empty or
immortal encoding are private compiler/runtime choices, not a stable serialized
or foreign struct ABI. StrongRefCell/WeakRefCell use the analogous opaque-cell
pattern; public Ref families wrap their cells as ordinary types. This analogy
does not equate their lifetime/capability semantics.

Compiler-known declarations are admitted by intrinsic declaration identity and
validated signatures, not arbitrary spelling. The complete safe operation set is:

| Intrinsic | Logical operation |
|---|---|
| `bufferNew[T]()` | Create an empty Buffer[T] |
| `bufferWithCapacity[T](capacity: U64)` | Create empty storage with requested capacity |
| `bufferCount[T](buffer~: Buffer[T]) -> U64` | Read live count |
| `bufferCapacity[T](buffer~: Buffer[T]) -> U64` | Read capacity |
| `bufferReserve[T](buffer: inout Buffer[T], additionalCapacity: U64)` | Reserve room without changing live values |
| `bufferGet[T](buffer~: Buffer[T], index: U64) -> T` | Return an owned value copy |
| `bufferSet[T](buffer: inout Buffer[T], index: U64, value~: T)` | Replace a live value |
| `bufferAppend[T](buffer: inout Buffer[T], value~: T)` | Append a value copy |
| `bufferInsertAt[T](buffer: inout Buffer[T], index: U64, value~: T)` | Insert while retaining order |
| `bufferRemoveLast[T](buffer: inout Buffer[T]) -> T` | Transfer the last value out |
| `bufferRemoveAt[T](buffer: inout Buffer[T], index: U64) -> T` | Transfer a value out and preserve remaining order |
| `bufferSwapRemove[T](buffer: inout Buffer[T], index: U64) -> T` | Transfer a value out and fill its position from the end |
| `bufferClear[T](buffer: inout Buffer[T])` | Retire all live values |
| `bufferTruncate[T](buffer: inout Buffer[T], count: U64)` | Retire a suffix |

The two creation operations return Buffer[T]; unspecified result entries above
return Unit. This table records intrinsic interface intent, not proof that all
current declaration registrations match it. Recover T from the selected typed
Buffer signature, never from a guessed Array name. Each intrinsic is a complete
safe operation including bounds, CoW and typed lifecycle. No public unchecked
load/store, uniqueness observation, raw header write, or retain/release pieces
are exposed for library authors to assemble correctly themselves.

Public Buffer factories/methods are thin ordinary Plew forwarding wrappers.
IsEmpty and pop combine existing safe operations; they need no new intrinsic.
Index/IndexSet conformances connect ordinary subscript resolution to get/set.
Count/capacity are methods reading headers, not compiler-recognized computed
properties. Capacity guarantees are logical lower bounds from the spec, not
exact allocation/growth promises. Overflow of count-plus-reserve, element-byte
multiplication or allocator representation and allocation failure must follow
specified panic-without-receiver-change behavior. Dictionary sentinel, load
factor and bucket-growth limits can be narrower than Buffer capacity.

## Collection Layer and Dense Indexing

Array, Dictionary, Set and String are ordinary structs holding Buffer fields.
Their method/trait resolution, storage and recursive ownership use the generic
mechanisms. Literal recognition is a separate compiler-known declaration
contract; it does not authorize type-name-based surface or lifecycle dispatch.
Opaque method dispatch must not depend on having an LLVM struct layout.

Array holds one Buffer[T]; its count is not a second Array-owned field. A one-field
wrapper may be physically normalized under ABI rules; this is not a promise that
all nested structs flatten or that Dictionary has one pointer. String holds
private UTF-8 Buffer[U8] storage in the chosen large-string representation. Privacy
protects validity and future representation changes such as small strings.
Equality is value/element Eq, not pointer identity; byte comparison needs evidence
that the representation/equality contracts permit it. Printing uses Format and
indexing/iteration use their ordinary traits.

SwapRemove belongs to Buffer's lower-level API; Array's ergonomic removal retains
order. Dictionary uses dense keys/values/hashes Buffers plus a scalar bucket-index
Buffer; Set uses dense items/hashes plus buckets. A bucket can encode zero as empty
and n as dense index n−1. Removing dense entry r swaps in the last entry, updates
its bucket reference, and repairs the removed probe chain with backward-shift
logic where needed. Merely setting a collided bucket empty can break lookup.
Rehash reconstructs indices without reordering dense elements; iteration is over
count rather than bucket capacity.

An alternative Buffer[Optional[T]] represents holes with valid Optional values,
not uninitialized slots. It is safe but may reserve payload space at load-factor
capacity and scan O(capacity). Dense values plus indices improve iteration and
rehash behavior at the cost of more complex index repair. Neither representation
is made correct merely by Buffer's memory safety.

Parallel Buffer alignment is a collection-level invariant: Dictionary keys[i],
values[i], hashes[i] and buckets must describe the same entry; Set items/hashes
and buckets likewise. Commit all columns and indices before releasing retired
values/backings that can reenter. Deferred retirement or rebuilding whole state
are possible mechanisms, not a mandated algorithm. Individual safe calls alone
do not prove these logical/reentrancy invariants.

## Value Reads, Places and Costs

Get returns an owned value that survives growth/reallocation. It does not expose
a long-lived element borrow. Copyable v1 generics need no new move/borrow/consuming
surface API. A logical copy may retain shared backing rather than clone bytes;
it is still a value-semantic copy, not absence of a copy operation.

Distinguish ownership acquisition from a nonescaping observation. Reading an
eligible element field may project/load directly without materializing the whole
element or retaining unrelated fields. This is a compiler optimization under the
place/access contract, not permission to retain an invalid address across calls,
CoW separation or reallocation. Nested write projections separate outer storage
before inner storage; reads do not privatize. Buffer and Array must consume the
same checked Index/place contract rather than duplicate syntax-specific rules.

Returning/binding a whole element needs a surviving value representation and
its owned shares. Inline descriptor transfer does not copy referenced String or
nested-collection contents. Arbitrary Eq receives values under the common ABI
and can retain/escape them; do not suppress ownership solely because the caller
wanted a comparison. Guaranteed input lifetime or nonescape proofs can eliminate
redundant transfers only under the shared ABI and effect/access rules. Guaranteed
shares are not owned callee shares to destroy. Native byval snapshots are not
additional semantic copies. Consuming a sole backing can permit owner transfer,
but an optimization must prove no other owners need the original element.

Privatization copies the live inline element array and acquires its element
shares; nested heaps remain shared until their own mutation. Unique-backing grow
and relocation can transfer bytes/owners without retain/drop pairs when stale
slots cannot be observed and destruction timing remains correct. Last-reference
release can have effects, so equivalence is not justified by calling every drop
pure. An owned read may retain, shared mutation may cost O(count), and deinit may
have arbitrary cost. Zero extra cost for all reads or guaranteed performance
parity is not an adopted theorem. Verify projection coverage and optimize measured
hot paths rather than introducing an unsafe borrow escape.

## Generated Helpers and Release Protocol

The retained code-generation design has a shared array/buffer release emitter
consuming data plus finalized element type. If elements need no destruction,
release raw backing directly. Otherwise decrement the backing reference count without
freeing its header, and only on the final-owner path read the live element count,
destroy live elements, then free backing. That ordering assumes the decrement helper preserves
the header until explicit free. Shared-owner paths need not observe count.
Clear/truncate's retired ranges are distinct operations and still obey their
commit-before-release protocol.

Null-safe internal LLVM count/capacity readers can be emitted once per module:
null yields zero; nonnull reads the agreed header slots. Normal LLVM inlining and
commoning can avoid per-call CFG duplication or mandatory external C calls.
Runtime C may retain its own header reader for runtime implementation. These
helpers own physical observation only, not user execution, ownership decisions,
CoW policy or bounds semantics. Changing the header requires synchronizing every
reader, allocator and destruction consumer. This is a retained mechanism design,
not a fresh source audit of all emitted helpers.

## Alternatives, Costs and Future Scope

A capacity-only RawBuffer with exposed get/set is rejected under Plew's no-manual-
lifecycle premise. Splitting unchecked operations from a safe Plew wrapper would
move the very proof obligations that the floor is intended to close back into
library/user code. This is a deliberate difference from other languages, not an
argument that their standard libraries are unsafe by construction.

Per-element boxing solely to avoid inline descriptor transfer is not the default:
it adds allocation/indirection and loses locality on every access. Whole-buffer
CoW is the chosen flat-storage tradeoff; it does not forbid persistent trees built
from Ref and Buffer. Lists/trees/graphs can use Ref/WeakRef, with cycle management
and ARC costs. Integer handles into Buffer can implement arenas/pools. Multiple
Buffers can express SoA data structures; the restriction is raw allocation/layout
control, not a ban on ordinary arrangements of safe values.

The floor does not offer user-defined allocators, raw alignment/layout, stable
memcpy serialization, arbitrary slot initialization or long-lived element borrows.
Compiler-internal small-buffer representations remain possible; users cannot
specify raw inline storage through this floor. FFI conversion is explicit. FFI
CPtr/extern(c) opt-in addresses externally originated lifetime/provenance hazards;
it is not a back door for language-internal manual ARC/lifecycle. The foreign
boundary chapter/spec governs the exact surface and programmer responsibility.

Unique elements are outside this copyable v1 floor. A future allowUnique design
must reconsider moves, borrow reads, access and relocation instead of silently
extending this proof. Ref-wrapping a unique resource permits shared ownership but
changes its meaning; it is not interchangeable with a unique element collection.

SubBuffer is an unadopted extension candidate: an owning CoW view with base,
offset and length, privatizing on mutation to preserve both directions of value
independence. It would allow cheap slices/substrings, not a long-lived raw borrow
or persistent-tree sharing. A small view retaining a large backing is an explicit
memory-retention cost, distinct from unreachable leakage. Bounds, destruction
extent and CoW must be proved before admitting the extension; it is not free
merely because the existing floor is safe. [Library design follow-up](../issues/com-mnsx.md)
tracks the related slice/iterator questions.

## Reference Designs and Verification Boundary

[Rust RawVec source](https://doc.rust-lang.org/src/alloc/raw_vec/mod.rs.html)
explicitly leaves destruction of stored values to its consumer. This storage/
lifecycle split works with Rust's unsafe library mechanisms; Plew declines that
surface internally and places live count and typed destruction in Buffer instead.
[Swift ManagedBuffer](https://github.com/swiftlang/swift/blob/main/stdlib/public/core/ManagedBuffer.swift)
combines a generic header and element storage while exposing unsafe pointers.
It is a useful allocation-layout reference, not evidence that every Swift
collection uses exactly one representation or that Plew should import those
pointer APIs. C++ allocator/placement-construction/destruction likewise illustrates
a viable unsafe-core/safe-container split under a different premise.

Completion requires auditing the finite intrinsic registration/lowering, exact
initialized extents, zero-size/empty/overflow cases, generic-grounded layout and
element glue, nested place reads/writes and CoW independence. Include custom
stack/ring/hash collections, collision repair and parallel columns, last-Ref
release reentry, retained/escaping Eq, final-owner and shared-owner destruction,
and sanitizer runs including self-hosted code generation where applicable.
Functional behavior, sanitizer evidence, fixed-point correctness and performance
are different gates. None was rerun for this document, and absence of an audited
failure is not proof that every operation or composition is implemented correctly.

## Retained Follow-up Investigations

[place, reentrant commit and iteration ownership coverage](../issues/com-zgk9.md). These scoped tasks retain implementation limits or uninspected combinations; their existence is not evidence of a current defect or completed coverage.
