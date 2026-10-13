# Representation and ABI

## Responsibility and Scope

Representation lowering maps completed semantic types and ownership contracts to target storage and calling conventions. It owns physical field types, boxing boundaries, alignment/layout queries, parameter/result representation, implicit environment lanes, and boundary conversions. It does not infer source types, select trait witnesses, change access modes, or turn physical layout equality into semantic type equality.

[Types and Semantic Evidence](types-and-evidence.md) owns identity and conversions; [Generics](generics.md) owns concrete instance environments; [Mid](mid.md) owns evaluation and ownership operations. This chapter defines their physical handoff. LLVM emission, native publication, and runtime execution must agree on the resulting protocol. An internal protocol is not a promise of stable binary compatibility across compiler versions.

## Representation Inputs and Identity

Physical lowering consumes finalized layouts, instantiated types, selected conversion/destruction contracts, and logical callable signatures. Aggregate fields and enum payloads retain their selected indices, types, and boxing relationships. A backend cannot recover these from source names or reselect an implementation because two layouts happen to match.

Recursive layout construction needs separate declaration and completion states. Publishing a named LLVM type can break a recursive registration dependency; it does not establish that its body/layout is complete. An opaque declaration must not be interpreted as an empty zero-sized type. All layout-dependent use requires a completed contract or an explicit opaque-pointer representation.

Target identity is part of a physical result's validity. The LLVM module has its intended target triple before layout-sensitive optimization, and layout/ABI queries use the corresponding target configuration. Host defaults, a previous module's layout, or target-independent guesses cannot determine field offsets for a different native target. The target/backend boundary obtains the DataLayout from the selected target machine and ensures its agreement with the module before layout-dependent use; object/JIT admission must reject incompatible layouts. The exact point of DataLayout attachment and every earlier layout-dependent consumer remain part of the implementation audit, not guaranteed by setting a triple alone. Host-generation and application-target configurations remain distinct.

Internal type names, body symbols, and numeric IDs serve different purposes. A symbol names a linkable entry; a body ID identifies its semantic origin/instance; an LLVM type describes its representation. None substitutes for the others. Physical caches belong to their LLVM context/module and target, even when semantic facts live longer in the compilation session.

## Logical Calls and Private Physical Signatures

A logical signature preserves the selected receiver lane, ordinary parameters, result type, passing modes, and any closure/witness environment roles. Frontend finalization owns those semantic modes. Physical lowering chooses how each lane travels without changing whether a value is copied, borrowed, lent inout, or consumed.

The private Plew ABI classifies value parameters as omitted, direct, or indirect. Sized aggregate values use indirect `byval` snapshots; scalars and pointer representations travel directly; zero-sized value parameters are omitted physically and reconstructed at the callee. Borrow/inout parameters remain pointers. These categories do not depend on an arbitrary “large struct” threshold, and omission does not omit source evaluation, access obligations, or destruction.

The declared callable records its logical signature, physical function type, and per-logical-parameter physical index/classification. Direct callers and callee binding consume that same record and validate logical signature/argument correspondence. An indirect callable derives the equivalent mapping from its completed signature under the same classification rules, rather than using a different ad hoc closure ABI.

A byval byte snapshot is a physical copying mechanism, not an additional semantic Copy or an implicit ARC retain. Its source/destination lifetime and ownership follow the already selected passing contract; the callee cannot independently destroy a caller-guaranteed share simply because LLVM supplied private bytes.

ABI attributes must match on definitions/declarations and call sites. A `byval` parameter describes an independent snapshot; passing an unprotected address into mutable caller storage is not a substitute. Temporary storage belongs to the function actually being emitted, including when emitting a thunk inside another generation context. Allocate its slot in that function's entry and store the evaluated value at the original call position, preserving evaluation order and avoiding loop-driven stack growth.

The current private value-parameter mapping leaves the logical LLVM return type unchanged. Aggregate return lowering by the native backend is distinct from the explicit parameter mapping; this chapter does not claim an independently implemented universal sret convention. Any future result-lowering change must update call, definition, indirect entry, and adapter consumers together.

LLVM scalarization/inlining can remove snapshot costs when alias/effect rules permit it. Those optimizations are not a correctness precondition for the unoptimized ABI. Default adapters, methods, closures, existential witnesses, and synthetic destruction entries must obey the applicable common signature contract rather than relying on optimizer repair.

## Stored Values and Ownership Glue

Physical aggregate construction uses the selected result type and destination field slots; child evaluation order remains source order in Mid. Boxed fields contain physical pointers but preserve their logical value types and ownership contracts. Reading does not require CoW separation; mutable projection/replacement operates on the correctly separated storage according to the adopted value semantics.

A Copy operand already acquires an owned value. Storing it into a new local, field, box, or return home transfers that owner without another retain. Borrowed ABI inputs acquire a new share only when an independent owner is stored or returned. Machine glue implements the [type destruction contract](ownership-and-access.md#type-destruction-contracts), including selected user deinit and child order; it does not rediscover those decisions from physical fields.

An enum's representation retains its discriminant and active payload relationships. A consuming match transfers the whole source ownership to the selected payload destinations; removing a physical box is not permission to leave a partially live source enum. Shared-cell extraction and final-owner extraction have different ownership consequences supplied by the operation contract.

Zero-sized physical load/store handling is centralized. For a completed empty struct/array representation, ordinary loads can reconstruct the empty value and stores need no machine memory instruction. Opaque types are not empty. This rule does not remove allocation identity, source evaluation, moves/copies, access checks, or user destruction, and does not grant permission to omit future volatile/atomic operations.

## Closures, Existentials, and Adapters

A closure has a callable entry and an environment relationship established from its finalized closure signature and lexical instance environment. Its physical environment pointer is an implicit lane, not an extra source Mid parameter. Captured-by-value slots and shared mutable capture-cell slots have their respective frozen types and ownership modes. Their layout and environment-destruction entry belong to that same closure instance.

Existential values carry the representation and witness relationships selected by semantic conversion. Dynamic calls consume the selected witness slot and its signature; they do not find a same-named member on the boxed type again. Repacking, concrete wrapping, and ownership transfer remain explicit Mid conversions rather than untyped LLVM casts.

Adapters preserve original-body semantics and convert the boundary. The original function body executes under its original types; a synthesized adapter converts arguments/results using retained evidence. Creating a new physical entry does not authorize checking that body under a substituted receiver or losing the implementation/requirement distinction. Entry generation and caching follow body/instance identity, not only a textual symbol.

## Native External Boundaries

The [FFI specification](https://github.com/plew-lang/spec/blob/main/spec/04-execution/15-modules.md) distinguishes `extern(c)` imports from `expose fn` definitions. Native exposed entries use the target platform's C ABI. Private Plew `byval`/omission rules do not automatically apply to C signatures.

`expose` publishes the source function name without an alias syntax. Direct targets are free, synchronous, nongeneric functions; all parameters explicitly suppress labels. Methods and associated functions are excluded. `pub` governs Plew visibility independently of external publication. External-name collisions are errors even when source overloads differ by types. Object-format name decoration is not a source alias.

C lowering owns scalar widths, target-required extension attributes, compatible pointer/inout representation, and conversion into/out of the private body. A private representation different from C's representation requires an explicit boundary conversion, including copy-in/copy-out for inout where appropriate. The same rules apply to imported calls and exposed definitions. Unsupported target ABI cases fail explicitly rather than borrowing a familiar host policy.

Current implementation uses a private double representation for F32 and converts at the C scalar boundary. That is an audited implementation fact, not a language guarantee that F32 has double storage or double semantic precision. Primitive lowering is allowed to identify compiler-known language items only under the declared intrinsic/type contract; arbitrary user type spellings cannot acquire primitive ABI behavior.

Anonymous functions need no ABI annotation at creation. Analysis of a C-pointer use selects an eligible C entry while ordinary uses select a Plew entry, sharing the body where valid. Labels cannot be silently erased. Named functions remain non-values. Boundary eligibility, including environments and uses through variables/returns, must be established before exposing an entry; a raw C function pointer alone cannot carry an arbitrary closure environment.

The specification leaves callback boundary-type syntax/eligibility and parts of runtime initialization, thread/reentry, lifetime, and publication unresolved. This reference does not resolve them by assuming every closure is C-compatible. The adopted state-callback pattern uses an ID indexing Dictionary-held Ref/MutableRef state. Helpers may receive the Dictionary as a value snapshot; later registrations are not automatically visible through an older snapshot. An external manager unregisters only after callbacks are quiescent, and unknown/stale IDs fail explicitly. This is not an implicit captured-environment ABI, arbitrary integer-to-pointer conversion, or permission to access the registry from foreign threads.

## AOT, Demand Execution, and Symbol Publication

AOT and requested JIT modules use the same logical/physical conventions. Requested modules retain body identity independently of symbol spelling, including multiple physical entries associated with async execution. Private generated names occupy a namespace distinct from source external names so an exposed symbol cannot capture an internal body reference.

External host lookup is permitted only for declared foreign/runtime symbols. A missing Plew body cannot accidentally resolve to compiler machine code with the same name. Separately materialized modules must agree on signatures, attributes, target/runtime contracts, and semantic instance identity before a reference is callable.

C callback ABI selection occurs at compilation of the use; it is not runtime ABI switching. AOT prepares required implementations ahead of time. Demand execution may provide the spec-permitted stable lazy entry and materialize its body through the ordinary request path. Stable entry publication, compiler/session lifetime, and failure behavior belong to driver/runtime design and cannot be inferred from the existence of a machine pointer. No separate run-only value/runtime representation is adopted.

## Change Paths and Verification

For a new internal parameter representation, update the classification/mapping authority, definition binding, direct and indirect calls, and adapter/environment lanes together. Test raw unoptimized calls as well as optimized calls, including source mutation during argument evaluation and escaping closures; optimizer success alone is not ABI correctness.

For a new layout form, preserve semantic identity and ownership evidence, complete recursive registration, and update projection/conversion/destruction consumers. Include empty and boxed cases. For a C boundary type, define target compatibility, both conversion directions, extension/alignment requirements, inout writeback, and diagnostics before accepting its exposure.

Zero-sized argument omission tests must still observe argument side effects and required destruction. Symbol tests must distinguish source external collisions, internal names, missing-body lookup, and separate requested modules. Cross-target ABI claims require evidence for those targets; a native self-host is only one target/control path.

## Comparative Rationale

[Swift's ABI Stability Manifesto](https://github.com/swiftlang/swift/blob/main/docs/ABIStabilityManifesto.md) distinguishes layout, metadata, mangling, calling conventions, and runtime interfaces, and describes abstraction-level signature lowering. Plew uses these responsibility distinctions without adopting Swift's stable framework ABI, resilience machinery, or runtime metadata calling convention.

[The Rust Reference](https://doc.rust-lang.org/reference/type-layout.html) distinguishes language representation from C-compatible layout and warns that layout alone does not establish every function ABI property. Plew likewise separates private representation from external compatibility; an LLVM struct matching C's apparent field shape is not sufficient evidence for a valid C call.

[LLVM's language reference](https://llvm.org/docs/LangRef.html#parameter-attributes) defines ABI-affecting attributes such as byval and requires the relevant agreement between call sites and declarations/definitions. Plew's common mapping makes that agreement explicit. These LLVM mechanisms realize a compiler protocol; they do not choose Plew's source ownership semantics.

## Implementation Audit and Open Scope

Focused inspection uses compiler revision `6fe09bc7c0e75260b3f773643921478b5020b94f`: `src/Backend/Llvm/ValueAbi.pw` for parameter mappings, declaration/call/binding agreement, entry temporaries, and requested-module identity metadata; `CAbi.pw` for scalar conversion, inout writeback, and target-specific narrow integer attributes; `Types.pw` for primitive physical widths; and selected `Closures.pw` registration/environment code. `Backend.pw`’s storage predicate/load/store/parameter classification and the registration portion of `GenericStruct.pw` were also inspected for zero-size and finalized-layout boundaries. Existing Mid contracts supply the broader ownership rules.

This is not an audit of every aggregate layout, native ABI target, existential thunk, indirect signature cache, or C boundary validation path. Callback eligibility/context/lifetime and external runtime publication details remain open in the specification. The representation of internal Unit/control types must not be confused with a public named Unit type. Unsupported targets and missing finalized contracts remain failures rather than inferred compatibility.
