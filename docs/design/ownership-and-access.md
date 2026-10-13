# Ownership, Access, and Lifetimes

## Responsibility and Semantic Boundary

The [language specification](https://github.com/plew-lang/spec/blob/main/spec/01-basics/03-values.md) owns value semantics, source access modes, unique ownership, destruction order, and exclusivity. This chapter defines how the compiler enforces those rules on [Mid](mid.md). It does not infer source types, choose callees, or determine physical ABI layouts.

Ownership analysis determines which local owns a value and where that obligation ends. Access analysis determines which storage may be observed or modified during a reservation. Keeping an owner alive does not authorize conflicting access; proving accesses disjoint does not discharge destruction. A retained shared cell can be alive and still illegally accessed through an alias.

The frontend publishes binding identity, selected passing modes, conversions, access provenance, and scope boundaries. Mid construction exposes their execution order. Mandatory analyses validate these operations and produce explicit cleanup/access plans. The backend realizes the plans, and the common runtime performs the selected dynamic comparisons. No layer substitutes a different meaning based on a familiar method name or pointer size.

## Ownership State and Storage

A local owner has an initialized/owned or consumed state, with a join state representing paths on which ownership differs. Accessibility is tracked separately: a value can still have a destruction obligation when its source binding becomes inaccessible. Caller-owned guaranteed parameters and inout storage are not local owners to destroy on return. Top-level/associated roots are outside the local ownership vector. Process exit or host teardown does not implicitly become a language destruction edge or guarantee user deinit for those roots.

Copy acquires an independent owned value; Move transfers an existing owner; reading a guaranteed value does not acquire one. Assigning an owned operand into a fresh home transfers that operand's ownership without acquiring it again. Replacement destroys the previous initialized value and installs the new one. Borrowed contents and the storage holding them remain distinct: overwriting an inout referent changes its contents without creating or destroying ownership of the caller's storage.

Plew's current unique model does not support arbitrary partial moves. Whole-value movement and enum payload transfer must consume the source owner once and initialize the selected destination owners consistently. A struct/enum spelling difference cannot create a different ownership rule. Shared-cell contents cannot be moved out merely because their value type is unique.

Ordinary value parameters may use a guaranteed physical ABI while retaining by-value source semantics. That implementation borrowing does not make their source values aliases of the caller's mutable storage. Conversely, an explicit semantic borrow must retain its storage provenance even if both kinds of operand share a physical representation.

## Lifetime Boundaries and Drop Elaboration

Source-defined obligation-ending edges—including lexical exits, explicit binding ends, and conditional-move accessibility cliffs—are the cleanup authority. An owned unique binding shadowed by a new declaration ends at the frontend-selected shadowing commit, after RHS evaluation and its temporary cleanup. A shadowed copyable binding retains its ordinary scope lifetime. Mid consumes binding IDs rather than re-resolving names to reconstruct this distinction.

EndBinding(local) is an independent binding-end operation, not a fabricated
ScopeExit. Frontend binding-end identity selects the target after initializer
cleanup. Drop elaboration maps Owned/MaybeOwned/Consumed to Drop/ConditionalDrop/
no cleanup, then updates ownership, accessibility and flag state to ended. An
already explicitly dropped local is not destroyed again. Declaration ownership
checking interprets the marker directly, while executable admission rejects any
unelaborated marker at its required stage.

A conditional move can end accessibility before lexical scope exit. When one branch moves a named unique value and another retains it, the retaining edge destroys that owner before the common continuation: the join cannot uniformly name an owned value. Cleanup is not postponed until the surrounding scope ends. A borrow crossing this cliff is rejected rather than extending the owner’s lifetime.

Forward ownership/accessibility dataflow reaches a fixed point over the CFG. At an obligation-ending boundary, an owned value requires Drop, a consumed value requires none, and a path-dependent owner requires conditional destruction. Locals sharing an exit are destroyed in reverse declaration order. Last-use information does not independently authorize earlier observable destruction.

Planning an accessibility-cliff drop changes the ownership state of successor paths. The final plan must therefore be based on analysis incorporating those consume effects, including loop backedges. A candidate drop that becomes unnecessary is removed; the compiler must not preserve it and relax verification. If no planned cliff changes transfer behavior, reusing the unchanged analysis is valid.

Conditional destruction uses compiler-generated flags only where needed. Initialization sets a flag, movement/consumption clears it, and reinitialization restores it. Every flag is initialized on the invocation entry before any possible read. A loop backedge must not execute that initialization again and erase the ownership history. Read-before-initialization and inconsistent owner/flag states are invalid IR.

Return transfers its value to the dedicated result home before exiting source scopes. Panic/abort has no cleanup continuation and does not run user destruction as if it were a normal return. Suspend preserves obligations across resumption; it is not an implicit cancellation or destruction operation. Async liveness must include later cleanup uses and owner dependencies of borrowed values, not only ordinary reads. A synchronous borrow/reservation cannot escape into an async frame.

The drop producer and executable verifier have distinct roles. Verification checks all-path initialization, use-after-consume, legal reinitialization, owner/flag correlation, and exactly-once discharge on normal exits. It must not simply trust the producer's own plan as evidence. Physical release-free types still participate in ownership verification; omitting a machine destructor is not omitting the obligation.

## Type Destruction Contracts

Type finalization owns the destruction contract for a type under its instantiation environment: uniqueness, required release operations, selected user deinit, child destruction relationships, and their order. Recursive type relationships require explicit incomplete/ready states; a placeholder is not an executable contract. Instantiation supplies concrete children and selected operations without repeating name-based deinit selection.

The contract preserves type-level order separately from local cleanup order: run the type’s own deinit while all fields remain valid, then destroy fields in declaration order; an enum destroys only its active payload. Closure environment cleanup uses the frozen capture relationships/order rather than reconstructing captures from the source body. Shared references release their shares; referent destruction occurs only on the final applicable release.

Drop elaboration chooses *where* an owner’s obligation ends. Effect closure consumes the contract’s callable/child destruction dependencies. Verification requires the applicable completed ownership contract. Backend destructor generation consumes that same contract to emit its physical operations. None may independently select a destructor or infer release freedom from layout. Representation-specific glue belongs to [Representation and ABI](representation-and-abi.md) and the backend chapter.

## Places and Exclusivity

Access identity consists of logical storage origin and a normalized path. It is not merely an LLVM address. Local bindings, globals, shared reference cells, capture boxes, and formal/actual relationships must retain their distinct provenance. Zero-sized layout and CoW boxing must not erase logical overlap.

For value-world places, different roots are independent values. Paths through disjoint struct fields can be independent; a path prefix overlaps its descendants. An index normalizes the path to its containing collection: two different indices do not establish disjointness. The compiler rejects statically overlapping inout arguments/receiver positions.

Shared-world paths retain the evaluated cell identity and field/container path. Different cells or disjoint fields can be valid, while equal cells with overlapping paths conflict. Statically established equality permits early rejection; otherwise the required comparison is dynamic. Pinning retains the evaluated cell through the call and writeback so rebinding the reference variable cannot invalidate that place. The pin is a lifetime mechanism, not an exclusivity exemption.

Directly owned unique borrows are checked statically against move, inout, and destruction. Shared cells obey shared-storage checks even when their contents are unique. Read/read is valid; a long write reservation conflicts with an independent overlapping read or write.

## Evaluation, Access Elaboration, and Writeback

All by-value argument/default snapshots and receiver/index subexpressions are evaluated before the long inout reservation begins. Earlier child values are preserved as described in [Mid evaluation](mid.md#places-operands-and-explicit-evaluation). This allows a by-value snapshot of a variable alongside an inout argument to that variable without treating the snapshot as a continued borrow.

Access construction retains a potential path without guessing whether a source method is mutating. Selection/instantiation supplies the actual passing contract. Access elaboration then consumes frozen access inputs and selected getter/setter calls once. A read-only method must not acquire writeback because of its spelling; an inout method must not lose writeback because lookup happened later.

Modification through an index follows get-modify-set: evaluate inputs once, run the necessary getters, perform the parent operation, and write back from inner to outer. Simple assignment of a whole indexed element uses the setter without inventing a getter. Source evaluation order and the reverse writeback spine are different orderings and are represented separately.

A reservation covers the parent call through its final required writeback. Generated setters use that reservation's delegated authority for the intended update. Their independently executed alias accesses are still checked. A formal inout forwarded to another inout call is a reborrow, not an unrelated second write reservation. This relationship follows provenance; raw pointer equality alone cannot distinguish forwarding from an illegal alias.

Construction owns saving evaluated keys and reference owners; Access owns consuming those saved inputs. A prepared value identifies an evaluation occurrence rather than a supported syntax category, so a function call used as an index is an ordinary value input. Each access marker retains the input-local range for that occurrence. Instantiation grounds types while preserving this mapping. Getters and setters must read those same saved keys even if later arguments or the parent call mutate the original key variable. Rebinding a reference variable likewise cannot redirect writeback from the evaluated cell. This does not require an unconditional snapshot of the entire container rooted in a local, global, or physical field; selecting a place and beginning its long reservation are separate events.

Access-scope verification checks the interval, continuation, and delegated destinations before emission. The backend must not infer intervals by recognizing a nearby setter. Normal and early exits close the reservations they own. An abort path does not fabricate subsequent releases or writeback.

## Static Effects and Targeted Runtime Enforcement

Static global analysis gathers mutable-global reads/writes, selected synchronous calls, and destruction dependencies, then closes summaries over the call graph. Known overlap with a call's read borrow/inout reservation is rejected before emission. Recursive call graphs require a converging worklist, not treating an in-progress summary as empty.

Ambient analysis covers paths that can independently reach shared storage: shared cells, mutable capture boxes, globals, indirect calls, and effectful destruction. The local path and closure path for the same reference-captured variable normalize to the same capture box, rather than to unrelated closure-environment addresses.

May-effect summaries select where reservations/checks are needed; they do not execute possible effects. A runtime conflict is checked where the selected body actually performs the ambient access. Untaken branches, uncalled closures, and unexecuted conditional drops must not cause a speculative panic. Hoisting a check requires proof that storage identity and executed paths preserve the same result.

Unknown indirect dispatch, erased destruction, and FFI effects are not pure. A more precise summary can remove unnecessary checks, but missing evidence cannot. Destruction dependencies include user deinit, aggregate children, final shared-cell release, and existential/closure environment destruction. Conditional cleanup retains conditional access checks. Ordinary retain/release operations with no possible user effect need no blanket access instrumentation.

Caller-owned formal access is authorized reborrowing. Independent cell/capture/global aliases in the callee are ambient accesses. The adopted design does not pass hidden reservation tokens through every callee ABI; caller-side argument preparation and generated writeback have limited delegated authority, while independent callee aliases remain checked.

Ordinary local/by-value accesses do not require a runtime registry operation. Targeted instrumentation is an implementation choice that must still cover every conflict required by the specification. Explicit FFI preserves the programmer's responsibility for external alias access, destruction, and pointer retention. Unknown external effects alone do not reject an otherwise valid call, and this exception does not disable known Plew-side checks.

## Body Preparation and Program-Level Enforcement

Body-local access/drop preparation does not establish interprocedural access safety by itself. The driver/mandatory-analysis boundary gathers the required prepared bodies, closures, adapters, and destruction operations, closes their effects, and builds enforcement plans before those bodies become callable. Whole-target checking and demand execution differ in requested scope, not in the meaning of successful enforcement.

A newly materialized body or dependency must receive the same enforcement preparation before publication. A summary derived from a smaller prepared graph cannot silently remain authoritative when new effects become reachable. The driver/runtime chapters must define the publication and invalidation protocol for this boundary; this chapter does not adopt persistent cross-session effect caches or a second runtime.

## Worked Change Paths

For an inout indexed receiver through a MutableRef, the frontend selects the accessor/callee evidence and storage provenance. Construction evaluates and retains the cell/key once. Access elaboration builds getters, the parent call, and reverse setters under one interval. Analysis rejects known overlaps and selects dynamic cell/path comparisons where necessary. LLVM emits that plan; runtime checks occur on actual ambient accesses. Cleanup releases temporaries and the cell pin after writeback. Fixing this path in LLVM by recognizing the source method name would bypass all three authorities.

For a branch that moves a unique owner on only one path, the join carries a path-dependent ownership state. Cliff elaboration destroys the owner on the retaining edge before the common continuation, not at a later lexical exit. Verification checks the flag/owner correlation independently. Adding a loop or a shadowing boundary changes the dataflow, not the type's destruction identity.

## Targeted Verification Paths

Index evaluation tests must distinguish the target updated, not merely memory safety: mutate the original key from a later argument and from the callee, rebind a shared reference, and check getter/setter use of the original key/cell. Cover inout receivers, nested keys, key-call ordering and single evaluation, different generic instances, keys with owned fields, and ordinary-read lifetime. The shared fixtures live under `tests/fixtures/run/index_evaluation_*.pw`; [index diagnostics](../../scripts/diagnostics/index-evaluation/README.md) consume the same inputs. Shared-cell and owning-key inputs also occur in the raw pre-optimization compiler supplement, [ASan E manifest](../../tests/sanitizer/asan-ownership-cases.txt). Both normal and focused sanitizer execution compare specification-derived expected output; ASan alone cannot detect a valid write to the wrong element. The manifest and [test guide](../../tests/README.md) own current suite membership.

Ambient probes cover independent shared-cell aliases, local versus reference-captured closure access, selected indirect implementations, and user destruction during reservations. Positive controls include formal reborrowing, distinct cells, disjoint fields, read/read, snapshots, untaken branches, uncalled closures, unexecuted conditional destruction, early return, loops, and legal get-modify-set. Existing fixtures are `tests/fixtures/{run,panic,reject}/ambient_*`, `run/receiver_shared_access`, and `run/mid_access_scope_verify`. Fixture existence is a test-location map, not evidence of a newly executed gate.

## Comparative Rationale and Cost

[Rust drop elaboration](https://rustc-dev-guide.rust-lang.org/mir/drop-elaboration.html) separates ownership obligations, initialization analysis, and conditional destruction. Plew uses the same general separation, with root-owner granularity under its current partial-move restriction. It does not import Rust's open-drop field machinery or unwind-capable terminators as language requirements.

[Swift exclusivity enforcement](https://www.swift.org/blog/swift-5-exclusivity/) combines static diagnostics and runtime checks for aliases that cannot be excluded statically. Its [enforcement selection](https://github.com/swiftlang/swift/blob/main/lib/SILOptimizer/Mandatory/AccessEnforcementSelection.cpp) distinguishes storage provenance, including caller-enforced inout formals. Plew likewise distinguishes formal forwarding from independent aliases, while choosing targeted ambient instrumentation rather than requiring universal instrumentation of ordinary value accesses.

Ownership and effect dataflow operate over canonical rows without thawing bodies. Worklists and reusable reverse dependencies avoid repeated whole-program scans. Effects absent by proof can avoid runtime operations; uncertain effects retain enforcement. These are cost-management rules, not permission to weaken verification or a measured performance claim. A richer region/NLL system is not adopted by documenting these extension boundaries.

## Implementation Audit and Open Boundaries

Focused inspection uses compiler revision `6fe09bc7c0e75260b3f773643921478b5020b94f`: `src/Mid/Drop.pw` for root-local ownership transfer and canonical processing, and `src/Mid/Access.pw` for frozen-input elaboration, evaluation DAG/writeback separation, and original-container reservation. `Ir.pw`’s FinalDestruction and the checked accessor/collection boundary in `Codegen/Mono/Ownership.pw` were inspected for ready-state enforcement and recursive dependency handling. `CheckedProgram.pw`, `DeclarationProgram.pw`, and `Mid/DeclarationAccess.pw` were inspected for the declaration graph connection. The former meta ownership/ambient contracts supply the remaining adopted effect, verifier, and enforcement boundaries consolidated below; they have not all been independently source-audited here.

The existing module split maps the remaining plan responsibilities as follows. `Mid/GlobalAccessGraph` propagates supplied nodes, call edges, and canonical storage reads/writes; its analysis-local node numbers are not instance IDs, and it neither instantiates nor selects callees. `Mid/GlobalAccess` builds that graph from concrete bodies and completed destruction contracts. The declaration route uses the same graph through `CheckedProgram` → `DeclarationProgram` → `Mid/DeclarationAccess`, retaining abstract call/conversion/destruction gaps as `DeclarationAccessObligation` rather than granting execution permission.

`Mid/Ambient` builds shared-cell, capture-box, and mutable-global storage recipes with physical-field paths and index container boundaries. Its path queries and plan registration take read-only canonical Mid, not the whole compiler/backend state; program target selection and effect resolution stay outside. `Mid/AmbientEffects` closes reverse dependencies of direct calls and completed destruction contracts with a worklist. Only proven effect absence permits reservation omission. `Mid/Access` associates the parent call and generated setters with one interval identity; `Mid/AccessScopes` validates single-entry continuation, final setter, and delegated storage. LLVM allocates the interval's physical region before emitting blocks and starts/ends it on executed paths. These mappings are preserved implementation-contract input from the former ambient note, not an expanded independent source audit.

An older meta note describes declaration-level global analysis as unconnected. Focused inspection of `CheckedProgram.pw`, `DeclarationProgram.pw`, and `Mid/DeclarationAccess.pw` instead shows whole-target checking calling declaration preparation, collecting roots/explicit obligations, and solving the shared graph. This supersedes that narrow stale note; it does not prove that every deferred obligation is discharged. Whole-program or lazy-publication correctness is not proven by the focused inspection above. Demand-driven summary closure/invalidation and all-path runtime reservation emission require further audit in the driver, runtime, and verification chapters.

Upstream checked-body storage remains unresolved. Full lifetime-region inference, generalized partial moves, and finer dynamic-callee effect precision are not implied as implemented or adopted extensions. Current required borrow/exclusivity checks remain mandatory while those extensions are absent.

## Retained Follow-up Investigations

[unique result and region boundaries](../issues/com-5n4i.md), [closure ownership shapes](../issues/com-b1ro.md), [deep destruction stack use](../issues/com-7g6i.md). These scoped tasks retain implementation limits or uninspected combinations; their existence is not evidence of a current defect or completed coverage.
