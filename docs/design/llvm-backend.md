# LLVM Backend

## Responsibility and Input Boundary

The backend consumes prepared Mid, completed semantic/representation contracts, and explicit emission configuration to produce an LLVM module. It realizes selected operations and physical signatures; it does not choose overloads, infer types from AST, reconstruct cleanup, or repair missing evidence. [Representation and ABI](representation-and-abi.md) owns the physical mapping; [Mid](mid.md) and [Ownership/Access](ownership-and-access.md) own the executable operations and enforcement plan.

The native LLVM consumer owns target-machine integration, machine optimization, instrumentation, object emission, and ORC module admission. The driver chooses what to request, links or executes successful results, and reports failure. LLVM implementation details do not become a second source-checking path.

The adopted backend is LLVM for both AOT and demand execution. This separation is not an adoption of a pluggable backend framework, an interpreter, or a run-specific runtime. Text IR remains an explicit diagnostic/bootstrap artifact rather than the normal exchange format between Plew emission and the embedded LLVM consumer.

## Prepared Bodies and Emission Scope

Whole-program emission consumes a prepared program with the required body worklist and access plans. Requested emission consumes the selected body from that same canonical program model, with global storage referenced rather than independently redefined. The owning session must close the required source/effect obligations before granting emission/publication permission. A registered symbol alone is insufficient.

Before emitting a body, the backend checks LLVM applicability: supported concrete operations, compatible physical parameter/result roles, and required layout/ownership descriptors. Successful backend-local preparation identifies that exact immutable body and argument mapping. Emission consumes it without rerunning the same preflight. Failure means no body emission, not an AST fallback.

Functions, methods, closures, synthetic adapters, global initializers, and async bodies share this admission boundary. Helper registration can create physical dependencies and emission queues, but must not discover a different source meaning. Queues drain until their registered physical dependencies are emitted; processed cursors prevent replaying a body into an existing function. A requested body must be explicitly observed as emitted before returning success.

Declarations precede body emission where recursive references require them. Named layouts are registered before recursive layout bodies are filled. This registration breaks physical dependency cycles; it grants neither source-checking success nor callable publication. Each entry retains its semantic body identity independently of its generated name.

Runtime declarations are indexed by the interned actual C symbol identity in the
same external namespace as declared C imports. Reusing an entry requires a
compatible LLVM function signature and applicable ABI attributes, not merely a
matching name. Named struct-instance registration and its reverse index update
through one registration boundary so readers cannot observe independently
maintained identities. These physical indexes do not select source operations.

## LLVM Resource Ownership

One unique module owner holds its LLVM Module and the Context that actually owns that module together. The context has no independent competing owner. Arbitrary nonnull handles from different contexts are not a valid pair. Builders borrow the context and are disposed before the owner. Normal disposal destroys the module before its context. LLVM values, types, blocks, and metadata cannot outlive their context through a cached raw handle.

The object-lowering boundary releases no-longer-needed frontend arenas before LLVM optimization, avoiding overlap of their retained memory where the result no longer depends on them. Demand sessions retain the facts required for subsequent requests under their session lifetime; this is not permission to discard those facts at every emission.

Object emission borrows the module/context; it may mutate the module through optimization, so the raw module is not implicitly reusable as an unchanged diagnostic artifact afterward. Text printing borrows the module and copies the returned message into Plew storage before disposing the LLVM message. Native errors and output buffers also have explicit disposal obligations.

ORC handoff consumes the module/context pair together, including failure. The Plew owner is marked transferred before it can be disposed. The native consumer immediately owns both handles, wraps them in a ThreadSafeModule, and either transfers that owner to ORC or releases it on error. A callback returning an output pair obeys this same consuming boundary. The output is either an empty pair or a complete matching pair with explicit consuming ownership; a half pair is invalid. A failed callback disposes its still-owned resources or transfers a complete pair for native cleanup, never leaving ambiguous ownership.

A ThreadSafeModule provides LLVM context access coordination; it does not authorize application event processing during compilation. The adopted driver suspends application execution while compiling. Session ownership, callback lifetime, and callable publication belong to driver/runtime design; ThreadSafe ownership is not a substitute for those contracts.

## Function-Local Emission State

Physical emission state belongs to the function currently being built. Entry allocas, locals, environment bindings, result homes, async frame references, and block mappings cannot be inherited accidentally from an enclosing body when a helper/thunk is emitted.

Mid local/block identities are body-relative; canonical pool locations and LLVM objects are separate domains. The backend maps validated IDs to physical objects rather than interpreting source variable names. Flat CFG statements/terminators emit their corresponding operations and edges. Alloca placement in entry prevents repeated loop allocation; stores remain at the selected evaluation point.

Explicit per-body parameters choose synchronous versus async return/suspend emission. Async frame planning consumes the prepared CFG's live-across-suspend results, including cleanup and owner dependencies. Resumption reloads saved state rather than reusing pre-suspend LLVM SSA values. Source-value Drop comes from Mid; runtime completion notification and frame bookkeeping are physical/runtime operations, not an alternate source cleanup stack.

## Target and Native Output

The target/backend boundary selects the native triple, CPU policy, target machine, and DataLayout. Module, machine optimization, and object/JIT execution must agree on the applicable target/layout contract. A nonempty incompatible layout is rejected rather than silently reinterpreting previously generated offsets. An absent layout can be attached before any consumer that needs it.

The current native object consumer deliberately supports its native target and rejects a different module triple. This is an implementation scope limit, not a promise of arbitrary cross-compilation. Host-generated code and target application code must not mix configuration merely because the current machine makes them equal.

Object output verifies the module, applies its configured optimization/instrumentation pipeline, verifies again, emits an owned object buffer, and writes that artifact. Successful object emission is not successful OS linking or application startup; those belong to the driver. On failure, no partial output is treated as a completed binary.

ORC admission verifies the LLVM module and checks its target contract before making its resources available to the engine. Source body symbols and explicitly allowed host/runtime symbols remain distinct. A missing source body cannot bind to a coincidentally named compiler function. Admission is not application startup or permission to call a body whose required semantic preparation failed.

## Optimization and Sanitizer Boundaries

LLVM optimization preserves already established meaning. It may scalarize aggregate snapshots, inline calls, and remove redundant physical operations where its alias/effect information permits. Unoptimized raw output must still implement the Mid ownership/ABI contract; a successful optimizer is not a repair stage for invalid IR.

The shared native preprocessing definition lives in `native/llvm_pipeline.h` and is consumed by both the embedded object path and the text-IR link helper. Its current sequence simplifies functions within SCC processing before private argument promotion, then completes ordinary module optimization. The object path additionally applies its configured standard optimization tier before sanitizer instrumentation. This single definition prevents independently maintained preprocessing strings from drifting; it does not mean every AOT/JIT mode uses identical optimization levels.

Normal sanitizer compilation marks emitted definitions for instrumentation, not merely runtime C code. Required language/ownership checks remain enabled. Optimizing a partially transformed aggregate ABI and instrumenting it before the intended preprocessing completes can change physical copy cost, so the stage order is explicit. Sanitizer diagnostics must still be capable of checking unoptimized compiler behavior through the separate raw-IR validation route.

LLVM tools, optimization, sanitizer passes, runtime support, and link drivers must be compatible with the selected LLVM/toolchain configuration. An ASan runtime startup failure is distinct from a Plew memory error. The compiler's release/static-link packaging policy does not authorize mixing an incompatible local opt/clang with the module producer.

## Verification, Artifacts, and Failure

Mid verification proves compiler-level invariants; LLVM verification proves LLVM structural/type rules. Neither subsumes the other. Verification occurs at the relevant native consumer boundary. Every consumer that transforms LLVM IR must verify the final transformed module before machine code generation and publication, including any future ORC transform layer; this is not specific to object output. Diagnostic text output must identify whether it is raw emission or transformed output; printing does not itself certify executable readiness.

Failed source preparation, failed Mid preflight, invalid LLVM, failed machine optimization, unsupported target, native emission failure, and ORC materialization failure retain their domain distinction. A no-continuation source operation is not backend failure. A terminal lazy failure cannot return a guessed value of an arbitrary callee ABI; the run contract terminates instead.

Bootstrap fixed-point artifacts retain raw LLVM/runtime material under their own validation protocol. Object generation mutates an owned module and is not compared as if it were raw source emission. Backend tests should therefore name their level: semantic execution, raw IR shape, optimized IR shape, native ABI behavior, sanitizer observation, or resource-transfer failure.

## Change Paths

Adding a Mid operation starts with its prepared schema/verification, then physical emission and required runtime/ABI declarations. The backend consumes explicit operands and contracts; it must not re-enter an old AST emitter for the missing case.

Adding a helper entry requires a body/instance identity, signature, function-local emission context, ownership protocol, and request/emission registration. Test it when generated during another body's emission and in requested-module mode, not only as a whole-program root.

Changing native optimization requires updating the shared definition or explicit mode policy, checking pre/post verification, and keeping sanitizer placement intentional. Changing module ownership requires normal/failure transfer tests, including callback failure after ownership crosses C. A new target requires layout/ABI/native integration evidence rather than changing only the triple string.

## Comparative Rationale

[Rust code generation](https://rustc-dev-guide.rust-lang.org/backend/codegen.html) separates MIR-to-backend lowering from native work, while its documentation acknowledges remaining LLVM-specific coupling. Plew takes the responsibility distinction without treating another compiler's source structure as a clean blueprint or adopting multiple backends/codegen units by analogy.

[Swift SIL](https://github.com/swiftlang/swift/blob/main/docs/SIL/SIL.md) describes IRGen lowering canonical SIL into LLVM IR. Plew follows the same principle of lowering an already meaningful checked intermediate form; its place-based Mid, concrete generics, and driver protocol remain Plew decisions.

[LLVM ORCv2](https://llvm.org/docs/ORCv2.html) defines ownership/context wrappers and materialization abstractions. Plew uses ThreadSafeModule for the native ownership boundary while keeping source demand preparation in its compiler session. ORC manages executable resources and linking; it does not supply Plew type checking, ownership rules, or whole-program effect closure.

## Implementation Audit and Open Scope

Focused inspection uses compiler revision `6fe09bc7c0e75260b3f773643921478b5020b94f`: selected `Backend.pw` module/builder owners, lowering and emission entry points, transfer/text/object methods, and queue drains; `native/llvm_backend.cpp` module consumption, object target/layout checks, verification/optimization, and ORC add; `native/llvm_pipeline.h`; and selected `scripts/support/llvm_link.py` shared preprocessing/toolchain code. Existing Mid contracts supply the detailed preflight and async boundaries, not a complete source audit here.

The inspected ORC DataLayout admission differs from the adopted agreement/rejection contract. The [tracked discrepancy](../issues/com-6ygf.md) owns its current evidence, affected consumers, and completion conditions; this chapter does not claim the whole ORC layout path has been audited.

The focused inspection does not certify every resource-failure path, LLVM verifier entry, helper queue, async output, sanitizer mode, or foreign target. Requested publication and runtime lifetime require the following chapters. Upstream checked-body storage implementation and the unique-Copy preservation audit recorded in earlier chapters remain incomplete; backend success is not evidence that those boundaries have been closed.

## Demand Execution Integration Audit

The [declaration/execution supplement](declaration-and-execution-audit.md)
retains the abstract-versus-concrete obligation map, request/cache integration,
and native probe boundaries. Historical evidence is indexed there; it does not
certify the current implementation or broaden this chapter's publication guarantees.

## Retained Follow-up Investigations

[historical backend libcall resolution](../issues/com-8w4c.md), [additional target scope](../issues/com-ej0z.md). These scoped tasks retain implementation limits or uninspected combinations; their existence is not evidence of a current defect or completed coverage.
