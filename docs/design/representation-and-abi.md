# Representation and ABI

Detailed producer-to-consumer obligations, saved-fact admission, and bounded
implementation observations are retained in [Frontend Handoffs](frontend-handoffs.md).

## Responsibility and Scope

Representation lowering maps completed semantic types and ownership contracts to target storage and calling conventions. It owns physical field types, boxing boundaries, alignment/layout queries, parameter/result representation, implicit environment lanes, and boundary conversions. It does not infer source types, select trait witnesses, change access modes, or turn physical layout equality into semantic type equality.

[Types and Semantic Evidence](types-and-evidence.md) owns identity and conversions; [Generics](generics.md) owns concrete instance environments; [Mid](mid.md) owns evaluation and ownership operations. This chapter defines their physical handoff. LLVM emission, native publication, and runtime execution must agree on the resulting protocol. An internal protocol is not a promise of stable binary compatibility across compiler versions.

## Representation Inputs and Identity

Physical lowering consumes finalized layouts, instantiated types, selected conversion/destruction contracts, and logical callable signatures. Aggregate fields and enum payloads retain their selected indices, types, and boxing relationships. A backend cannot recover these from source names or reselect an implementation because two layouts happen to match.

Finalization retains a native-representation identity separately from semantic
and destruction identity. An outer zero-cost view refers to its base's
representation; a newtype follows its explicit underlying representation edge.
Nested generic arguments keep their semantic identities. Distinct nominal types
are never merged merely because field shapes or byte sizes match. Every ready
contract has a valid edge to a ready representative, terminating at itself;
missing, unfinished or cyclic edges are internal failures. LLVM registers only
representatives, publishing all names before constructing recursive bodies.
Local storage, projections and all callable lanes consume that same identity;
call-site casts cannot repair inconsistent representation selection.

Recursive layout construction needs separate declaration and completion states. Publishing a named LLVM type can break a recursive registration dependency; it does not establish that its body/layout is complete. An opaque declaration must not be interpreted as an empty zero-sized type. All layout-dependent use requires a completed contract or an explicit opaque-pointer representation.

Target identity is part of a physical result's validity. The LLVM module has its intended target triple before layout-sensitive optimization, and layout/ABI queries use the corresponding target configuration. Host defaults, a previous module's layout, or target-independent guesses cannot determine field offsets for a different native target. The target/backend boundary obtains the DataLayout from the selected target machine and ensures its agreement with the module before layout-dependent use; object/JIT admission must reject incompatible layouts. The exact point of DataLayout attachment and every earlier layout-dependent consumer remain part of the implementation audit, not guaranteed by setting a triple alone. Host-generation and application-target configurations remain distinct.

Representation receives an immutable triple/DataLayout description before type
registration or callable planning. Native object compilation obtains it using
the same CPU/features and target-machine policy as final object output; textual
IR selects the native generic target explicitly. Demand execution obtains the
description from its actual LLJIT instance, installs it before publication, and
retains it in the compiler session for declarations, global storage and every
requested body. Re-selecting the same description is harmless; changing it in a
session is an internal contract failure. Representation receives neither the
JIT handle nor target-machine authority. Final native admission still checks
exact agreement. A standalone low-level lowering request may select its native
default, but requested application bodies must reuse their session's selection,
not recreate a target machine or recover alignment from an empty layout.

Internal type names, body symbols, and numeric IDs serve different purposes. A symbol names a linkable entry; a body ID identifies its semantic origin/instance; an LLVM type describes its representation. None substitutes for the others. Physical caches belong to their LLVM context/module and target, even when semantic facts live longer in the compilation session.

Recursive value representation may introduce automatic boxing while preserving
value semantics. Requiring Ref merely to represent a value tree would introduce
shared identity that the program did not request. Boxing is a representation
mechanism, not proof of shared semantic identity; the [recursive-value
specification](https://github.com/plew-lang/spec/blob/main/spec/02-type-system/05-structs-enums.md#再帰的な値型)
owns acceptance rules.

## Logical Calls and Private Physical Signatures

A logical signature preserves the selected receiver lane, ordinary parameters, result type, passing modes, and any closure/witness environment roles. Frontend finalization owns those semantic modes. Physical lowering chooses how each lane travels without changing whether a value is copied, borrowed, lent inout, or consumed.

The private Plew ABI classifies value parameters as omitted, direct, snapshot-indirect, or guaranteed-indirect. Copyable aggregate Borrow lanes use typed `byref(T)` with the admitted alignment; other indirect lanes retain their selected snapshot/ownership contract. Scalars and pointer representations travel directly; zero-sized value parameters are omitted physically and reconstructed at the callee. Explicit unique borrow and inout retain their distinct pointer/access contracts. Classification does not depend on an arbitrary aggregate-size threshold, and omission does not omit source evaluation, access obligations, or destruction.

The callable's classification is independent of the caller's ability to reuse storage. A caller either supplies a proven initialized, stable, aligned home through the call, or materializes the evaluated value in a dedicated snapshot home under the same guaranteed-indirect ABI. The callee binds its guaranteed input without acquiring a local owner, and can forward that contracted home. Async entry still acquires its frame-owned inputs before the caller guarantee ends. C-facing entries retain their separate external ABI and adapt into the same private protocol.

Reusable local homes come from verified owned immutable bindings, dedicated evaluation temporaries, and admitted nonboxed static value-field projections. Ready preparation retains exact body, operation/operand occurrence, local root, projection, semantic/native type and LLVM scope correspondence. Final emission validates and consumes that receipt; an arbitrary pointer, source-binding integer, matching byte size, or a different same-typed parameter is not a proof. Contracted incoming homes use their exact entry/lane binding. A missing optimization proof selects a snapshot; a malformed required receipt is an Internal failure. Globals without admitted readiness, reference/index/cell/boxed storage and async frame homes do not inherit this local proof.

LLVM `byref` describes physical memory transport, not source borrowing, ownership acquisition, immutability or alias freedom. It grants no `readonly`/`noalias` attribute by itself. The frontend/Mid ownership and access contracts establish semantic legality; LLVM lowering cannot remove their Copy, lifetime or cleanup obligations merely because a byte transfer is avoidable.

The declared callable records its logical signature, physical function type, and per-logical-parameter physical index/classification. Direct callers and callee binding consume that same record and validate logical signature/argument correspondence. An indirect callable derives the equivalent mapping from its completed signature under the same classification rules, rather than using a different ad hoc closure ABI.

Completed ordinary closure signatures retain a leading Environment/Borrow pointer
(with no source type term) and indexed Ordinary/Borrow parameters. A template is
cached by finalized semantic function-type identity within one LLVM scope;
declarations check their frozen body signature and share its immutable lane
range with distinct declared body identities. Indirect calls carry a callable
scope identity, not an invented callee body identity. Their consumer validates
the typed fat closure and current-caller provenance before extracting function
and environment together. Ready parameter/environment readers consume the same
completed descriptor. Raw Legacy call and parameter adapters cannot select it.
Physical pointer equality alone is not source correspondence; verified Mid owns
that proof. Explicit compatibility for entries not yet migrated does not claim
that their source function modes are fully supported; known gaps belong in
[implementation issues](../issues/com-xkcb.md).

Completed existential requirement templates belong to a public endpoint:
finalized any target type, trait identity and requirement slot. Concrete witness
declarations share that template's lane range with their own adapter body
identities. The ErasedReceiver pointer lane retains the public target and passing
mode; Ready separately retains the frozen concrete receiver load/address
conversion. An opaque native pointer does not identify either semantic type.
Frozen member and final-call producers perform cache lookup before building
logical parameter vectors, and backend lowering does not rerun requirement
resolution. Calls retain the typed fat any value; the checked consumer extracts
data/vtable and uses the descriptor's slot. Ordinary Borrow/Inout/Move inputs
use typed Value/Home carriers. Completed indirect parameter readers share the
physical decoder, and retired raw Witness calls/parameter bindings cannot
bypass it. Existing CoW receiver privatization, result conversion and ownership
glue remain separate contracts.

Callable result slots use the frontend's common result normalization: a source
Unit expression has no callable payload slot. A selected call and its frozen
requirement member must use that same normalization before comparing or planning
the result. This does not erase named empty structs or authorize backend-specific
semantic normalization.

Completed ownership glue records its exact operation separately from source
callables. Struct/enum retain and release lanes carry the finalized instance
term and explicit borrowed/consumed payload contract. Erased environment/box
storage lanes carry payload access rights, not allocation ownership: their
caller still performs the final free. Copy returns a new box pointer. No opaque
pointer establishes the concrete type, copyability or destruction selection.
Those remain with frozen destruction/capture adapters at declaration. Scoped
operation/type templates serve declaration, typed call and parameter decoding;
dynamic calls retain one checked fat owner and prepare its storage/function
pair once, including when a null-drop guard intervenes. A prepared pair's scope
and provenance are validated at consumption; it is not a public raw-pointer
override interface. Source semantic correspondence still belongs to verified
Mid and finalized producer contracts. User deinit consumes its frozen receiver
through the ordinary typed Body protocol. The payload protocol does not change
RC final-owner tests, null guards, destruction order or recursive witness drains.

Completed async entry and resume descriptors are distinct. Entry retains the
frozen Promise result term and ordinary parameter passing modes; the async body
payload term is recorded separately. Resume returns native void and accepts one
Frame(body identity)/Move pointer with no source type term. This Move transfers
exclusive responsibility for executing the activation, not an additional source
move or ARC operation. Completion releases the frame; suspension hands execution
to the runtime continuation. The caller does not access the frame after first
resume. Allocation produces a private activation-identified frame carrier; the
first-resume consumer checks its activation, native scope and caller provenance.
Runtime callback invocation remains the explicit native boundary, not proof
that an arbitrary pointer may safely resume an activation more than once.
Ready admission proves semantic correspondence once and canonicalizes retained
parameter terms to the frozen signature without rewriting verified Mid locals.
Entry calls, parameter decoding and resume binding consume these same completed
records; raw async compatibility adapters cannot bypass them.

C-to-private entries complete C scalar/Inout conversion first, then supply
typed Ordinary inputs under the frozen BodySignature to the ordinary Body
consumer. C integer attributes, result conversion and Inout writeback remain
the C adapter's responsibility. A raw Body call permission is unnecessary and
cannot substitute native pointer equality for this correspondence.

Program main and global initialization are body-identified native entries, not
foreign host imports. Their cached completed descriptors serve publication,
definition, Ready admission and consumers. Main has native argc/argv lanes with
no source terms and a program-status i32 result; its source parameter count is
zero. The initializer has no inputs and native void. Program argument readers
and initializer calls consume these records rather than rebuilding signatures.
Missing ABI registration cannot identify a main or initializer implicitly.

Requested native publication retains an ABI receipt per source symbol alongside
body/session/preparer identity. The receipt compares structural result/parameter
types, pointer address spaces, packedness, varargs, calling convention and
return/parameter attributes, including typed byval payloads and integer values.
LLVM context pointers, nominal IR names and aggregate byte sizes are not ABI
identity. Type encodings are cached while inspecting one consumed module; saved
receipts contain no context-owned pointers. Unsupported attribute payloads or
type forms fail explicitly instead of comparing by kind alone. Declarations and
requested definitions use the same registration and metadata-identity gate
before reuse, entry replacement or module submission. A known source entry
cannot become an unchecked host/raw declaration by dropping body metadata,
including dependencies and program main. Explicit raw native defer clients
without source receipts remain a separate trusted interface. The execution
runtime and source ownership rules are unchanged.

A byval byte snapshot is a physical copying mechanism, not an additional semantic Copy or an implicit ARC retain. Its source/destination lifetime and ownership follow the already selected passing contract; the callee cannot independently destroy a caller-guaranteed share simply because LLVM supplied private bytes.

ABI attributes must match on definitions/declarations and call sites. A `byval` parameter describes an independent snapshot; passing an unprotected address into mutable caller storage is not a substitute. Temporary storage belongs to the function actually being emitted, including when emitting a thunk inside another generation context. Allocate its slot in that function's entry and store the evaluated value at the original call position, preserving evaluation order and avoiding loop-driven stack growth.

The current private value-parameter mapping leaves the logical LLVM return type unchanged. Aggregate return lowering by the native backend is distinct from the explicit parameter mapping; this chapter does not claim an independently implemented universal sret convention. Any future result-lowering change must update call, definition, indirect entry, and adapter consumers together.

LLVM scalarization/inlining can remove snapshot costs when alias/effect rules permit it. Those optimizations are not a correctness precondition for the unoptimized ABI. Default adapters, methods, closures, existential witnesses, and synthetic destruction entries must obey the applicable common signature contract rather than relying on optimizer repair.

## Stored Values and Ownership Glue

Physical aggregate construction uses the selected result type and destination field slots; child evaluation order remains source order in Mid. Boxed fields contain physical pointers but preserve their logical value types and ownership contracts. Reading does not require CoW separation; mutable projection/replacement operates on the correctly separated storage according to the adopted value semantics.

A Copy operand already acquires an owned value. Storing it into a new local, field, box, or return home transfers that owner without another retain. Borrowed ABI inputs acquire a new share only when an independent owner is stored or returned. Machine glue implements the [type destruction contract](ownership-and-access.md#type-destruction-contracts), including selected user deinit and child order; it does not rediscover those decisions from physical fields.

Async public entries keep this guaranteed-input convention. Their
[Mid input plan](ownership-and-access.md#async-activation-inputs) establishes
activation ownership explicitly before caller guarantees end. Callee binding and
frame emission consume its finalized lane roles; byval bytes, direct pointers or
frame allocation do not acquire another semantic owner or invent its destruction.

An enum's representation retains its discriminant and active payload relationships. A consuming match transfers the whole source ownership to the selected payload destinations; removing a physical box is not permission to leave a partially live source enum. Shared-cell extraction and final-owner extraction have different ownership consequences supplied by the operation contract.

Zero-sized physical load/store handling is centralized. For a completed empty struct/array representation, ordinary loads can reconstruct the empty value and stores need no machine memory instruction. Opaque types are not empty. This rule does not remove allocation identity, source evaluation, moves/copies, access checks, or user destruction, and does not grant permission to omit future volatile/atomic operations.

### Typed Operations and Weak Restoration

Type finalization supplies semantic copy/move/destruction and capability contracts; representation lowering supplies the corresponding private physical operations. A payload descriptor may reference layout and typed operation entries, but cannot independently infer copyability or select deinit. A copyable shared handle retains a cell share rather than copying a unique referent. An erased value's descriptor must not expose a copy entry as usable when its admitted ownership class is unique. Source ownership verification remains necessary even where physical relocation is a byte transfer.

For the adopted `WeakRef[R]` proposal, private construction records the control-cell relationship and a restoration operation compatible with exactly R. Ordinary generic checking and layout of `WeakRef[R]` do not require R to be a standard reference kind. `upgrade` uses the recorded restoration contract; it does not inspect R's name and reject non-reference type arguments downstream. A type may be nameable without a public way to construct a value of it. Construction privacy and typed restoration must hold together, rather than replacing the latter with an unsafe address cast.

A successful upgrade acquires a live strong share before constructing the restored handle. If the final strong release wins, promotion fails and the payload cannot be resurrected, including during deinit. Weak ownership retains the control state until the final weak release, independently of payload destruction. The saved operation restores the original handle's permissions; it cannot manufacture mutable/frozen authority or a MutexGuard. Restoring MutexRef owns a cell share and does not acquire its lock.

The allocation's fixed RC mode covers both final strong release and weak promotion. Sharing analysis includes weak creation, transport and upgrade aliases even when no strong handle is directly sent. JIT's conservative atomic mode uses the same protocol. This is private typed glue plus a common cell protocol, not an additional public reference trait or a runtime test that weak R is admissible. The precise descriptor layout and entry calling convention remain physical implementation details. [Swift type metadata](https://github.com/swiftlang/swift/blob/main/docs/ABI/TypeMetadata.rst) demonstrates typed value-operation descriptors; [Rust Weak::upgrade](https://doc.rust-lang.org/std/sync/struct.Weak.html#method.upgrade) supplies a comparison for acquiring a live strong owner. Neither reference defines Plew's unrestricted nameable WeakRef[R] or grants restoration permission independently of private construction.

## Closures, Existentials, and Adapters

A closure has a callable entry and an environment relationship established from its finalized closure signature and lexical instance environment. Its physical environment pointer is an implicit lane, not an extra source Mid parameter. Captured-by-value slots and shared mutable capture-cell slots have their respective frozen types and ownership modes. Their layout and environment-destruction entry belong to that same closure instance.

Existential values carry the representation and witness relationships selected by semantic conversion. Dynamic calls consume the selected witness slot and its signature; they do not find a same-named member on the boxed type again. Repacking, concrete wrapping, and ownership transfer remain explicit Mid conversions rather than untyped LLVM casts. [Runtime-opened generic calls](generics.md#runtime-opened-self-execution-bridge) use a prepared typed adapter selected by the saved opening operation and concrete descriptor identities. This boundary is private dispatch to an ordinary concrete instance, not an implicit source cast or a general new generic ABI.

Adapters preserve original-body semantics and convert the boundary. The original function body executes under its original types; a synthesized adapter converts arguments/results using retained evidence. Creating a new physical entry does not authorize checking that body under a substituted receiver or losing the implementation/requirement distinction. Entry generation and caching follow body/instance identity, not only a textual symbol.

## Native External Boundaries

The [FFI specification](https://github.com/plew-lang/spec/blob/main/spec/04-execution/15-modules.md) distinguishes `extern(c)` imports from `expose fn` definitions. Native exposed entries use the target platform's C ABI. Private Plew `byval`/omission rules do not automatically apply to C signatures.

`expose` publishes the source function name without an alias syntax. Direct targets are free, synchronous, nongeneric functions; all parameters explicitly suppress labels. Methods and associated functions are excluded. `pub` governs Plew visibility independently of external publication. External-name collisions are errors even when source overloads differ by types. Object-format name decoration is not a source alias.

C lowering owns scalar widths, target-required extension attributes, compatible pointer/inout representation, and conversion into/out of the private body. A private representation different from C's representation requires an explicit boundary conversion, including copy-in/copy-out for inout where appropriate. The same rules apply to imported calls and exposed definitions. Unsupported target ABI cases fail explicitly rather than borrowing a familiar host policy.

The implemented exposure subset distinguishes a source restriction from an ABI
capability refusal. Invalid exposure declarations or conflicting external source
signatures retain Source failure. A checked parameter/result outside the current
C ABI/ownership subset retains Limit failure, including the current Buffer,
Ref, String and Array controls. An error establishing the checked type/destruction
contract propagates unchanged; it is not converted to Limit merely because it
occurred during emission. Tests require the exact domain, normal failed process,
intended reason and absence of sanitizer/supervisor failure. This does not define
a permanent source prohibition or promise a direct C representation for every
managed type. [Managed exposure eligibility](../issues/met-2qbc.md) owns that
future decision separately from aggregate layout.

The shared C signature description must retain physical parameter/result types, target extension attributes, conversions, splitting/indirection where supported, and writeback requirements. Imported declarations, call sites, and exposed definitions consume this same description. Matching LLVM value types alone is insufficient when signext/zeroext or other ABI requirements differ. External declarations and exposed definitions share external-symbol conflict checking; ownership-managed values cannot qualify merely because their private representation is pointer-shaped.

C-compatible memory layout and function-boundary classification are separate. The specification's `repr(c)` struct contract does not imply aggregate call support is implemented. This chapter has not independently established parser, AST, semantic-type, or shared-memory-layout support for that syntax either. Target classification can pass the same field layout using different registers or coercions; a two-float aggregate may be classified differently on Apple arm64, Linux x86_64, and Windows x86_64. Narrow integer/Bool extension rules likewise vary by target. Do not generalize one native Clang comparison into a portable classifier. The compiler owns this classification; reference Clang is a development oracle, not a required product subprocess.

Current implementation uses a private double representation for F32 and converts at the C scalar boundary. That is an audited implementation fact, not a language guarantee that F32 has double storage or double semantic precision. Primitive lowering is allowed to identify compiler-known language items only under the declared intrinsic/type contract; arbitrary user type spellings cannot acquire primitive ABI behavior.

Anonymous functions need no ABI annotation at creation. Passing one as a C function pointer does not require named publication with `expose`. Analysis of a C-pointer use selects an eligible C entry while ordinary uses select a Plew entry, sharing the body where valid. Labels cannot be silently erased. Named functions remain non-values; a named function can be called from an anonymous wrapper without introducing a declaration-to-value exception. Generating both entry kinds must not duplicate body semantics or the runtime. Reuse keys must preserve semantic body/instance and relevant ABI identity; they cannot merge different captured environments. Exact cache storage is not adopted here. Boundary eligibility, including environments and uses through variables/returns, must be established before exposing an entry; a raw C function pointer alone cannot carry an arbitrary closure environment.

The specification leaves callback boundary-type syntax/eligibility and parts of runtime initialization, thread/reentry, lifetime, and publication unresolved. This reference does not resolve them by assuming every closure is C-compatible. The adopted state-callback pattern uses an ID indexing Dictionary-held Ref/MutableRef state. Helpers may receive the Dictionary as a value snapshot; later registrations are not automatically visible through an older snapshot. An external manager unregisters only after callbacks are quiescent, and unknown/stale IDs fail explicitly. This is not an implicit captured-environment ABI, arbitrary integer-to-pointer conversion, or permission to access the registry from foreign threads.

The compiler callback needs only an exposed free function and an integer session ID; it does not depend on general captured-closure conversion. The [internal demand protocol](driver-and-execution.md#worker-demand-coordination) routes native receipt to the compiler-affine owner and gates application reentry under [managed pause](runtime.md#managed-pause-and-native-boundaries). This does not adopt a general public foreign-thread attachment API, manual Ref retain/release, raw environment pointers or dedicated user callback wrappers. Future Wasm publication can retain the `expose` spelling, but its boundary types and export details require a separate target contract.

Bindings generated by bindgen change who writes foreign declarations, not the
ABI or ownership obligations. Safe library wrappers can express foreign resource
lifetime with unique ownership and deinit; generated declarations alone do not
make an external lifetime safe. [Remaining interoperability API
questions](../issues/com-qnyl.md) are distinct from the adopted expose contract
and the callback/layout investigations above.

### Settled Boundaries and Deferred Public Facilities

The following are already consequences of the adopted contracts and do not wait
for a new public C-callback API:

- Native name collision checking uses resolved external names in the selected
  target/artifact scope, including imported declarations and exposed definitions.
  Permitted ABI decoration and source pub visibility are independent. The source
  prohibition is settled; unaudited diagnostics/linker coverage is implementation work.
- Imported, exposed and admitted indirect calls consume one finalized C signature
  description, including attributes and conversions. Memory layout equivalence
  cannot replace boundary classification or semantic ownership eligibility.
- A callable native address alone grants neither startup readiness nor permission
  to enter a paused/closed execution. Admitted callbacks use the existing owner,
  resource retention, managed gate and failure protocol. Reentry keeps existing
  borrow/inout accesses live; known Plew-side conflicts and initializer dependencies
  remain checked. This does not make an arbitrary foreign thread an application worker.
- Target-width integer conversion uses the target's signedness/value ranges:
  lossless inclusion admits From/as; possible out-of-range values require TryFrom.
  CSize/USize/U64 remain nominally distinct even on a target with equal ranges.
  Do not infer conversion from width equality or use the compiler host's widths.

| Remaining topic | Why it stays open / decision point |
|---|---|
| Public C function-pointer types, nullability and parameters/results/storage | A language-surface decision, to be made together before implementing general anonymous-function C interoperability. Existing data-pointer or Plew-function types do not silently answer it |
| Captured environments and C-pointer eligibility | Decide with that public boundary, before implementing any conversion. A context-free thin pointer plus an explicit C context/ID is the recommended baseline, not adopted source eligibility. Optimization must not determine whether a closure counts as capturing |
| Arbitrary foreign-thread entry | Requires a concrete host/API and a choice between owner delivery and attached-thread execution, including synchronous results, root isolation, JIT pause and shutdown. No automatic attachment or thread migration is introduced now |
| C-owned runtime startup, unload and repeated executions | Design with a real embedding host before implementing that facility; do not initialize automatically on first exposed-function call. Current one-execution ownership remains authoritative |
| Handle equality and extra representation syntax | No handle Eq now; aliases, repr(packed), explicit callconv and new targets remain optional additions requiring a concrete use and source decision before implementation |

The recommended context-free pointer direction follows [Rust's noncapturing closure
conversion](https://doc.rust-lang.org/reference/types/function-pointer.html) and
[Swift's C-convention restriction](https://docs.swift.org/swift-book/documentation/the-swift-programming-language/attributes/#convention),
while Plew keeps its own use-site selection and label rules. This comparison does
not adopt either language's public syntax. [Rust's callback guidance](https://doc.rust-lang.org/nomicon/ffi.html#asynchronous-callbacks)
separates same-thread reentry from foreign-thread callbacks and requires correct
synchronization and callback cessation before resources are freed; Plew must also
respect its root isolation and managed-pause contract.

Resolve these language/host choices before the corresponding feature, not as a
prerequisite for the paused source-checking migration. No performance experiment
can decide whether a new callback form or foreign-thread operation should be
accepted source. Physical validation instead fixes target/SDK/toolchain and
compares C↔Plew calls in both directions, direct/indirect entries, scalar/mixed
aggregate parameters/results, inout and extension attributes, at O0/O2 and with
applicable sanitizers. Callback publication tests include prepared/first-JIT calls,
reentry, pause/shutdown races, stale IDs and failure. External unwind/longjmp is
not an adopted way to skip Plew ownership/access cleanup or recover a failed
execution; any such support needs a separate boundary contract.

## AOT, Demand Execution, and Symbol Publication

AOT and requested JIT modules use the same logical/physical conventions. Requested modules retain body identity independently of symbol spelling, including multiple physical entries associated with async execution. Private generated names occupy a namespace distinct from source external names so an exposed symbol cannot capture an internal body reference.

External host lookup is permitted only for declared foreign/runtime symbols. A missing Plew body cannot accidentally resolve to compiler machine code with the same name. Separately materialized modules must agree on signatures, attributes, target/runtime contracts, and semantic instance identity before a reference is callable.

C callback ABI selection occurs at compilation of the use; it is not runtime ABI switching. AOT prepares required implementations ahead of time. Demand execution may provide the spec-permitted stable lazy entry and materialize its body through the ordinary request path. Stable entry publication, compiler/session lifetime, and failure behavior belong to driver/runtime design and cannot be inferred from the existence of a machine pointer. No separate run-only value/runtime representation is adopted.

## Change Paths and Verification

For a new internal parameter representation, update the classification/mapping authority, definition binding, direct and indirect calls, and adapter/environment lanes together. Test raw unoptimized calls as well as optimized calls, including source mutation during argument evaluation and escaping closures; optimizer success alone is not ABI correctness.

For a new layout form, preserve semantic identity and ownership evidence, complete recursive registration, and update projection/conversion/destruction consumers. Include empty and boxed cases. For a C boundary type, define target compatibility, both conversion directions, extension/alignment requirements, inout writeback, and diagnostics before accepting its exposure. Validate bidirectional C/Plew calls, endpoint values, stack arguments, returns, unoptimized/optimized modes, and applicable sanitizers. Value conversion alone cannot prove borrowed/inout or aggregate memory representation compatibility.

Zero-sized argument omission tests must still observe argument side effects and required destruction. Symbol tests must distinguish source external collisions, internal names, missing-body lookup, and separate requested modules. Cross-target ABI claims require evidence for those targets; a native self-host is only one target/control path.

## Comparative Rationale

[Swift's ABI Stability Manifesto](https://github.com/swiftlang/swift/blob/main/docs/ABIStabilityManifesto.md) distinguishes layout, metadata, mangling, calling conventions, and runtime interfaces, and describes abstraction-level signature lowering. Plew uses these responsibility distinctions without adopting Swift's stable framework ABI, resilience machinery, or runtime metadata calling convention.

[The Rust Reference](https://doc.rust-lang.org/reference/type-layout.html) distinguishes language representation from C-compatible layout and warns that layout alone does not establish every function ABI property. Plew likewise separates private representation from external compatibility; an LLVM struct matching C's apparent field shape is not sufficient evidence for a valid C call.

[LLVM's language reference](https://llvm.org/docs/LangRef.html#parameter-attributes) defines ABI-affecting attributes such as byval and requires the relevant agreement between call sites and declarations/definitions. Plew's common mapping makes that agreement explicit. These LLVM mechanisms realize a compiler protocol; they do not choose Plew's source ownership semantics.

[Swift C pointer calls](https://developer.apple.com/documentation/swift/calling-functions-with-pointer-parameters) and its [C convention](https://docs.swift.org/swift-book/documentation/the-swift-programming-language/attributes/#convention) distinguish compatible closures from environments a raw C pointer cannot convey. [Rust function pointers](https://doc.rust-lang.org/reference/types/function-pointer.html) and [FFI callbacks](https://doc.rust-lang.org/nomicon/ffi.html#callbacks-from-c-code-to-rust-functions) similarly separate entry ABI from context ownership. Plew's implicit choice at a compiled use is its own surface policy, not adoption of those languages' syntax or blanket conversion rules. [Swift Unmanaged](https://developer.apple.com/documentation/swift/unmanaged), [Rust Box](https://doc.rust-lang.org/std/boxed/struct.Box.html), and [Zig allocation](https://github.com/ziglang/zig/blob/0.15.2/lib/std/mem/Allocator.zig) illustrate explicit context ownership; the adopted ID/Dictionary/shared-reference bridge instead uses existing Plew ownership without a new unsafe reference-count API.

## Implementation Audit and Open Scope

Focused inspection uses compiler revision `6fe09bc7c0e75260b3f773643921478b5020b94f`: `src/Backend/Llvm/ValueAbi.pw` for parameter mappings, declaration/call/binding agreement, entry temporaries, and requested-module identity metadata; `CAbi.pw` for scalar conversion, inout writeback, and target-specific narrow integer attributes; `Types.pw` for primitive physical widths; and selected `Closures.pw` registration/environment code. `Backend.pw`’s storage predicate/load/store/parameter classification and the registration portion of `GenericStruct.pw` were also inspected for zero-size and finalized-layout boundaries. Existing Mid contracts supply the broader ownership rules.

This is not an audit of every aggregate layout, native ABI target, existential thunk, indirect signature cache, or C boundary validation path. Callback eligibility/context/lifetime and external runtime publication details remain open in the specification. The representation of internal Unit/control types must not be confused with a public named Unit type. Unsupported targets and missing finalized contracts remain failures rather than inferred compatibility.

Retained C/expose probes are preserved in the meta repository's [probe results](https://github.com/plew-lang/meta/blob/main/evidence/2026-10-01/compiler/expose/probes/results.json) and [requested-module results](https://github.com/plew-lang/meta/blob/main/evidence/2026-10-01/compiler/expose/requested-modules/requested-results.json). They are historical scoped evidence, not current-source or cross-target verification. Earlier scratch Clang ABI reference artifacts were cleaned; their old paths are not reproducible artifacts. Scalar/pointer handling, narrow attributes, F32 values and F32 inout conversion are the inspected implementation scope. General aggregate C ABI and anonymous-function C interoperability are not established as implemented by this chapter.

Deferred boundary work is tracked separately: [anonymous C interoperability](../issues/com-0oxy.md) and [repr(c)/aggregate C coverage](../issues/com-042v.md). These issues retain open questions and completion conditions; they do not certify implementation coverage or authorize specification changes.
