# Mid Representation and Lowering

## Responsibility and Boundary

Mid makes evaluation, storage, control flow, and ownership operations explicit after [body checking](body-checking.md). It provides the common substrate for access elaboration, ownership analysis, verification, and LLVM emission. It does not choose overloads, infer source types, or establish conformance again.

The frontend owns the meaning of an expression and its selected operations. Mid construction owns the sequence of operations and CFG edges that realizes that meaning. Instantiation applies the environment and evidence described in [Generics and Body Instantiation](generics.md). Access elaboration and drop elaboration discharge their respective abstract operations. LLVM emission consumes the verified result and chooses physical instructions; it must not repair missing semantic evidence or cleanup.

A source construct requiring new evaluation behavior therefore changes its frontend result and Mid builder. A different cleanup algorithm changes ownership analysis and elaboration. A different machine representation changes ABI/backend lowering. These are separate decisions even when one feature affects all three.

## Input and Published Result

Construction consumes a checked body owner with stable bindings, expression types, selected calls, conversions, patterns, source completion, and provenance. The concrete physical frontend storage contract remains unresolved as described in [Compiler State](compiler-state.md); a design-level input contract is not evidence that all current readers satisfy it.

Parametric construction may retain explicit type recipes and selected call templates whose environment-dependent application belongs to instantiation. Such a recipe names the decision to apply; it is not permission to repeat name lookup. Missing required facts are an internal failure, not a request to infer again from syntax.

Each published body identifies one immutable canonical body in its arena. IDs are meaningful only in the corresponding compilation/arena domain. Stage wrappers describe preparation guarantees for that body; they do not establish that the entire source program has been checked, that every reachable body is prepared, or that arbitrary IDs from another arena are valid.

## Places, Operands, and Explicit Evaluation

Mid uses a non-SSA, place-based representation. A place identifies storage through a root and typed projections. Roots distinguish locals, globals, and frame storage; projections preserve field, index, dereference, and approved representation-boundary information. Projection construction uses frontend identities and types rather than repeating source member lookup.

An index expression is evaluated once into a local before its value participates in a place/access. A place description is not an instruction to execute the source index expression again. The same rule applies when access elaboration later introduces address acquisition, writeback, or borrowing operations.

Operands distinguish reading a guaranteed value, creating an owned copy, and transferring an existing owner. A call's passing mode and a value's ownership operation are not interchangeable: a borrowed call can observe an owned temporary without consuming it, while a consuming call needs an owner to transfer. Access and ownership chapters define the detailed legality conditions; physical size does not determine source ownership.

Nested expressions are lowered into ordered operations and temporaries. Source binding identity is retained across shadowing. An expression ID identifies a semantic source site, not a globally reusable runtime result. Repeated default-argument evaluation must remain repeated evaluation even when it shares the same source expression ID. Builder memoization is restricted to the current evaluation context and must not leak a temporary across sibling regions or invocations.

## Control Flow and Expression Results

A body consists of basic blocks with ordered statements and one terminator each. Only terminators introduce CFG successors. Builder-only open-block sentinels cannot reach a published executable body.

Joins use a destination place allocated before the branches. Continuing predecessors initialize that destination and branch to the join; a predecessor that exits elsewhere supplies neither a fabricated value nor a join edge. Mid has no block arguments or phi nodes. Later machine-level SSA construction does not change this contract.

Lowering distinguishes a produced value, absence of continuation, and an error. Failure is never encoded as a dummy local. A failed optional place lookup is also distinct from evaluating an index expression that exits the current path.

The frontend's source-completion classification and Mid's CFG reachability serve different purposes. Source rules determine whether a construct is legal in a value position and whether following source statements are errors or warnings. The builder realizes the already accepted behavior as edges. It must not rederive source rules from the last statement, from a syntactic `give`, or from whether a generated block happens to have predecessors.

Calls terminate their current block and identify their normal continuation and result destination. A nonreturning selected call has no usable normal continuation. No post-call writeback, cleanup, or enclosing join is emitted on that absent path. Other branches still retain their own valid continuation. Panic/abort has no unwind cleanup edge.

Suspend is an explicit terminator with a resume edge and result destination. It preserves the input promise owner; resumption initializes the result destination according to the selected await operation. Live-across-suspend storage is a frame-lowering concern derived from this CFG, not a second interpretation of the source body. Cancellation behavior must not be invented as an implicit drop edge.

## Scope and Cleanup Information

Flattening control flow does not erase lexical scopes, provenance, or destruction order. Scope identity and exit markers retain the information needed to elaborate cleanup on normal exits, return, break, continue, and other accepted nonlocal transfers.

Call results live in the enclosing result home. Receiver/argument evaluation can use a child scope whose temporary obligations end on the normal continuation after required access completion. Default-argument adapters obey the same rules; they do not acquire a special lifetime extension merely because they are synthesized.

Return values are transferred into a return home outside the exiting lexical scope before cleanup. The return terminator then transfers that result. The backend must not infer a magic local-index exception to avoid destroying the result.

Initialization, copying, movement, replacement, and destruction remain distinct operations. Replacing an initialized mutable value cannot masquerade as fresh initialization. Drop elaboration converts abstract exit obligations into explicit destruction and any necessary conditional operations. An executable body has no unresolved scope-exit cleanup marker. Ownership dataflow, flag rules, and access conflicts belong to their detailed chapter rather than being independently specified by the builder.

## Draft Construction and Canonical Storage

Temporary builder collections may own arrays. Publication freezes them into closed scalar rows and typed ranges in canonical pools. Persistent rows do not embed independently owned recursive arrays. This avoids repeated CoW reconstruction of whole bodies when a pass changes a small subset of operations.

Canonical transformations consume an immutable input body and append the changed rows/ranges needed for a new body identity. Existing snapshots remain valid. A pass must not thaw the whole canonical body into a draft and freeze it again as its routine transformation protocol. This storage choice is specific to Plew's value/CoW implementation costs; it is not a claim that other compilers should avoid in-place IR mutation.

Node IDs and ranges have explicit domains and indexing conventions. Zero as an absent node/body reference does not make a zero type term an unspecified wildcard: Unit and synthetic control types must retain their defined meaning. Structural verification checks references before semantic consumers traverse them.

## Preparation Stages and Executable Admission

The preparation chain is parametric construction and freezing, instantiation, access elaboration, optional ownership-preserving copy optimization, drop elaboration, and executable verification. Structural checks guard the applicable intermediate boundaries. Each transition publishes its stronger wrapper only after success; failure does not return a partially prepared success value.

Declaration-level symbolic analysis is a separate product. It can inspect abstract alternatives and recipes to establish source obligations without materializing an executable instance. Its success does not discharge concrete conversions, access operations, or destruction obligations.

Functions, closures, global initializer bodies, and synthesized adapters use the same Mid preparation boundary. Global initialization retains the frontend's initialization order and distinguishes initialized from uninitialized storage. Runtime helper operations arrive as selected intrinsic targets, not as permission for the backend to recognize source names.

Executable admission checks structural integrity, typed places/projections and calls, and ownership obligations. Verification runs before LLVM lowering in normal compiler configurations; debug mode can enrich dumps without changing correctness checks. A verifier reports invalid IR and does not synthesize missing frontend decisions. Body-local success is not whole-program readiness: the driver must still prepare the required bodies and enforce the applicable global contracts.

## Comparative Rationale

[Rust MIR](https://rustc-dev-guide.rust-lang.org/mir/index.html) provides a useful model for a typed CFG with locals, places, and explicit operands. Plew adopts this general shape to make nonlocal exits and ownership analysis share one substrate, rather than rebuilding hidden control flow in each syntax visitor. Plew does not inherit Rust's language borrowing rules or unwind behavior from that representational choice.

[Swift SIL](https://github.com/swiftlang/swift/blob/main/docs/SIL/SIL.md) uses SSA with high-level semantics. Its [Ownership SSA](https://github.com/swiftlang/swift/blob/main/docs/SIL/Ownership.md) makes lifetime-ending uses and ownership invariants explicit. Plew takes the latter verification principle, while retaining place-based non-SSA Mid and delegating machine-level SSA optimization to LLVM. An additional SSA optimization layer is not an adopted requirement.

A structured representation plus a derived CFG could also support analysis. Plew chooses one flat canonical substrate so exits, dataflow, dumps, and transformations operate on the same concrete graph. This is a simplicity and inspectability choice, not a proof that structured IR cannot be correct.

## Change Paths and Verification

- Adding a source expression: define its checked result and completion in the frontend, then its evaluation sequence, result home, and exits in construction. Verify nested and noncontinuing operands as well as the direct form.
- Adding a projection or Mid operation: update the closed schema, structural traversal, type rules, relevant analyses, transformation behavior, and backend consumer. Missing opcode handling must fail explicitly.
- Changing temporary lifetime: update the scope/ownership contract and cleanup elaboration, with normal and nonlocal-exit cases. Do not fix one expression spelling in LLVM.
- Changing stage order: demonstrate that each consumer still receives its preconditions, including malformed-IR rejection. A wrapper rename is not that demonstration.

Tests should compare equivalent direct and wrapped expressions, sibling branches, repeated default evaluation, dynamic indices, and early exits. Corrupted-IR tests must exercise the production verifier alongside valid controls. Self-hosting or a green source suite alone cannot establish these internal invariants.

## Implementation Audit and Remaining Scope

Focused source inspection uses compiler revision `6fe09bc7c0e75260b3f773643921478b5020b94f`: `src/Mid/Ir.pw` for canonical rows/body IDs and draft vocabulary, `src/Mid/Prepare.pw` for stage wrappers and the preparation chain, and `src/Mid/Types.pw` for selected typed consistency checks. The existing meta Mid contracts supply the adopted lowering/cleanup boundaries pending their migration into the remaining detailed chapters.

The implementation names its draft structure `MidBody`; this chapter's “draft” describes its role rather than prescribing a completed rename. The audited preparation entry establishes body-local executable verification and registers body access information; it does not alone prove a complete global access analysis.

This inspection is not a complete audit of every builder exit, projection, async transformation, or execution entry. Physical checked-body storage remains unresolved upstream. The ownership/access, pass infrastructure, ABI, backend, runtime, and verification chapters must refine their own contracts without reopening source semantic selection in Mid.
