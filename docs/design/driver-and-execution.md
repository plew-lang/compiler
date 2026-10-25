# Driver and Demand-Driven Execution

**Status:** Reviewed draft. This chapter defines command orchestration and one-execution ownership. It does not adopt a stable embedding ABI, reusable in-process execution environments, or compiler-owned Hot Restart.

Detailed producer-to-consumer obligations, saved-fact admission, and bounded
implementation observations are retained in [Frontend Handoffs](frontend-handoffs.md).

## Responsibility

The driver turns an explicit target/configuration into requests to compiler services, selects artifact consumers, reports results, and manages execution resources. It does not provide alternative checking, ownership, or overload rules. CLI parsing is an adapter to these requests, not the authority for language acceptance.

Diagnostic observation follows the same boundary. The CLI can opt in through
`PLEW_TRACE_RUN=1`; only its native driver adapter reads this environment value.
Reusable execution receives explicit frontend options and passes phase observation
to the session and native JIT instance. Default application execution stays quiet.
Source preparation and module submission report only newly completed work, with
session/body identity and a monotonic per-instance counter. Submission is not
machine-code materialization or semantic success. Observation never changes JIT
policy, runtime behavior, request boundaries or the no-progress deadline, and a
stuck preparation unit cannot generate periodic progress merely by remaining alive.

The [source/module boundary](sources-and-modules.md) owns input discovery and provenance; the [session model](compiler-state.md) owns request identity and retained results. Checking, instantiation, Mid preparation, and the [LLVM backend](llvm-backend.md) own their respective publication guarantees. The driver combines those guarantees without promoting a weaker result into execution permission. [Runtime](runtime.md) owns the common execution protocol; this chapter owns when it can be entered and how long its code/state dependencies remain alive.

A framework may eventually use the common compiler/execution services independently of the CLI. That intent does not promise that an arbitrary Plew stack can unwind into a surviving host after terminal failure. Window management, watching, installation, and Restart orchestration belong to external tools/frameworks.

## Command Requests

The [command specification](https://github.com/plew-lang/spec/blob/main/spec/04-execution/15-modules.md#runcheckbuild-の検査と実行) fixes the following distinctions:

| Request | Required checking | Machine code and execution | Success means |
|---|---|---|---|
| check | Whole selected target, including unused and generic bodies under their bounds | No application execution or machine code generation | Static semantic rules have passed for that target/input |
| build | The same whole-target static checking, followed by concrete executable preparation | LLVM optimization and native artifact generation; unreachable code may be omitted | Requested build artifact is complete, including the driver's required link step |
| run | Requested bodies and the dependencies needed to validate execution | Demand preparation and ORC execution | This execution succeeded; unchecked unrelated bodies may remain |

The scope is the selected target, dependency set, and configuration, not every file in a workspace. Check success does not promise that every concrete instance or target-specific implementation facility can be generated. Such failures remain implementation limitations, not permission to omit static semantic checking.

Run checks an entire requested source body before entering it, including untaken branches. It is not line-by-line validation. Generic declarations are checked under their bounds; a favorable concrete instance cannot repair an invalid declaration. Closures, initializers, destruction helpers, and other generated bodies use the corresponding common checking/preparation contracts.

Checking dependencies can be broader than machine-code dependencies. Visibility, coherence, layout, effects, and access obligations must close before execution, even if that requires preparing bodies whose machine code is never requested. Unknown effects are not harmless effects. Optimizing code reachability does not reduce check's source coverage.

Generation is a separate target/request as described in [Metaprogramming](metaprogramming.md). Checking a synthesized generator harness cannot issue a whole-application check result. The CLI must carry that distinction explicitly.

## Fixed Inputs and Session Authority

One session owns admitted source bytes, dependency/configuration identity, source/instance facts, diagnostics, and request caches. A body ID is meaningful only with its session. Later demand cannot reload edited source into that execution or reuse a result from another session merely because IDs or filenames coincide.

Input admission must establish a coherent version before granting its guarantees. Reading a DAG of files sequentially is not inherently an atomic filesystem snapshot. The loader/admission contract must account for changes during discovery; this chapter does not claim an operating-system snapshot facility exists. Persistent cache reuse requires the input/compiler/target/dependency validity conditions in the session chapter. A separate check process is not automatically a reusable certificate for run after edits.

The execution host receives requests/results and owned LLVM resources, not permission to mutate compiler arenas or manufacture whole-target success. Partial declaration analysis can retain unresolved obligations. A concrete body can be locally prepared while still requiring interprocedural closure; neither result alone is a callable-publication token.

AOT and demand execution use the same session preparation machinery. Extending a partially requested session to whole-target checking must preserve the same admitted inputs, reuse valid results, and retain prior failures. It must not bless partial rows left by a failed request. This is an internal capability, not a promise that a CLI command runs twice in the same process.

## Startup and Global Storage

Startup distinguishes entry registration, storage definition, initializer preparation, initializer execution, and main execution. Entry signatures can be registered without compiling their source bodies. Initializers are mandatory startup roots with their own checking/effect dependencies; required global values are initialized according to the specification before main. Delay in checking/code generation does not delay language-mandated evaluation.

One execution owns one definition of program global storage. Requested body modules reference it. Static access analysis retains declaration identity, while dynamic global access uses execution-owned storage identity, including distinct identity storage for zero-sized globals. Source offsets or compiler-owned addresses cannot substitute for those identities.

Immutable shared metadata such as generated tables likewise needs an explicit semantic/session identity and compatible physical definition. Repeated emission must reuse the same intended storage rather than create unrelated identity or silently accept conflicting contents. Physical byte-size agreement is a necessary check, not a complete proof of semantic equivalence.

Installing storage does not run its initializer. Preparing an initializer does not run it either. The host and generated entry wrapper must agree on the single initialization path; calling both cannot initialize twice. Async initialization follows the language's static initialization and one-time publication rules rather than an invented driver traversal order.

### Static Initialization Plan

The compiler closes a static initialization plan before any application initializer executes. For each global or nongeneric stored associated value A, an edge A → B means that A's execution may access B and therefore B must be fully initialized before A's body starts. Reads, writes and inout accesses count: replacement can destroy an existing value. Defining storage and the final InitializeGlobal publication into A are not self-access dependencies. Generic stored associated values remain excluded in v1, as specified for [associated values](https://github.com/plew-lang/spec/blob/main/spec/02-type-system/07-methods-impl.md).

Keep two graphs distinct. An execution may-effect graph follows saved call selections, generic evidence, defaults, adapters and implicit typed operations. Recursion in that graph is legal; close summaries over recursive components to a fixed point. Project the resulting global-access sets onto initializer roots. A self-edge or cycle in this global graph is a compile-time error, including possible dependencies in mutually exclusive branches. Do not make acceptance depend on an optional optimizer proving a branch dead. No runtime attempt to choose a noncyclic branch replaces this rule. Diagnose a cycle with its global roots and the source/call edges that establish the dependencies, distinguishing it from ordinary function recursion or a module-use cycle.

The analysis consumes the existing semantic/effect contracts rather than performing another overload or witness search. Summaries include:

- Synchronous callees, defaults, factories/operators, copy/drop and final-release destruction that may execute during initialization. Process-exit global finalization is not promised and creates no startup dependency.
- Async continuations, completion and abandoned-result cleanup, plus spawned work and its execution dependencies whether or not the initializer joins it. Suspension or worker creation does not end the dependency summary.
- Invoked closure bodies and admitted dynamic witness/callable targets. Creating or storing a closure includes capture evaluation and ownership operations, but does not itself execute its body. Higher-order summaries preserve which callable arguments may be invoked or returned; imprecision widens the admitted target set rather than treating it as empty.
- Managed callbacks that may execute during startup, including registered completions and native calls through admitted callback entries. Existing exact runtime-primitive contracts can bound these effects. Opaque native code is not presumed pure. General callback eligibility, foreign-thread attachment and external runtime initialization remain within the [ABI chapter's unresolved boundary](representation-and-abi.md#native-external-boundaries); this plan does not silently admit those facilities, ban all startup FFI, or replace the programmer's responsibility for raw external accesses. For an admitted managed callback boundary, its possible targets/effects must propagate into the initiating initializer summary and close before startup; an unproved empty set is never sufficient.

The session retains root declaration/storage identities, required summaries and their dependencies, edges with source/call provenance, and successful closure/noncycle validation. Ordinary reads of B contribute an A → B edge, not an implicit call to B's initializer: analysis must not retain a second force-on-read authority. The driver consumes this saved plan; Mid and runtime do not rediscover dependencies from names or storage order. These are contracts on existing results, not a required general-purpose effect solver or public annotation system.

Check and build validate this mandatory graph. Run must close the same startup safety information before the first initializer runs, even when doing so requires checking bodies beyond the initial machine-code demand. Machine code can remain lazy. Later body preparation must respect the frozen summary/target bounds; it cannot add a newly discovered startup dependency after application side effects have begun. Missing required information prevents publication, and a broken published invariant is a compiler failure, not a runtime forcing fallback. After startup, all global roots are ready and ordinary demand execution continues under its usual publication contract.

### Ready Initializers and Publication

The common startup scheduler starts an initializer only after every prerequisite is initialized. Independent ready initializers may overlap their ordinary asynchronous waits; their relative side-effect order is unspecified. A synchronous initializer can run directly without an async frame merely to wait for prerequisites. An initializer that actually awaits uses the common prepared async entry/resume and ownership protocols. A completed await continues immediately as specified; an incomplete await yields normally.

Completion transfers the initializer's result owner exactly once into its execution-owned global storage, then publishes the initialized state and releases dependent roots. Uninitialized, running and initialized states enforce one-time execution/publication; they do not authorize waiting in an arbitrary global read. A normal Result.Err is still a completed value of its declared type. A panic, preparation failure or other terminal execution failure publishes no incomplete value and does not enter main under a fabricated success state.

This places prerequisite waiting before the body, its synchronous calls and their access scopes. Global loads, writes and inout accesses do not suspend, pump application events, or rewrite a synchronous/native stack into an async frame. Workers use the same already initialized roots and never ask the root loop to force another initializer. The design does not prove termination of I/O, channel or lock waits: an acyclic global graph is not general deadlock freedom. Code that relied on an initializer's early side effect before its prerequisites completed must respect the planned start boundary.

For example, when A calls a synchronous inout helper that reads async-initialized B, the plan waits for B before starting A. No mutable access is active during that wait. Verify this path alongside recursive functions without global cycles, conditional cycles, write-only dependencies, closure creation versus invocation, async/worker/callback/destruction edges, normal Result.Err publication, and corrupted/missing dependency evidence. This resolves [F1](../issues/com-7knz.md#f1--p1-synchronous-reads-during-asynchronous-global-initialization) within the admitted execution boundaries; it does not certify implementation or resolve the wider public embedding scope.

## Demand Call and Publication

The following states describe responsibilities, not a required new enum or general-purpose request framework:

1. **Registered:** a session/body identity, calling contract, and public entry are known. A stable lazy entry can exist without its source body being prepared.
2. **Preparing:** the synchronous bridge requests that exact body. Common checking, instantiation, dependency closure, and Mid preparation establish execution permission before LLVM emission.
3. **Publishing:** the native consumer validates the returned module and its identity, registers dependencies, and supplies ORC definitions under the agreed target/ABI/resource contract.
4. **Callable:** required ORC materialization/linking has succeeded. The entry forwards to the published implementation without repeating source preparation on ordinary subsequent calls.
5. **Failed:** required preparation or publication failed. No fabricated result or unsafe callee execution follows through that execution.

These states must not be collapsed into one `emitted` bit. LLVM module emission, ORC submission, symbol registration, and successfully materialized code are different guarantees. Native implementations may track several physical entries for one body, but the body identity remains independent of symbol spelling.

Callable publication must also validate the frozen allocation/typed-operation mode contract described in [Storage, ARC, and CoW](runtime.md#storage-arc-and-cow). AOT consumes a closed sharing plan; demand execution uses its conservative atomic baseline without reclassifying live allocations when another body is requested.

Callable publication also depends on the effect information used to justify access enforcement or its omission. Ownership/access analysis owns the summaries and their validity conditions; the session retains them, and the driver must require their dependency closure before permitting publication. Delaying machine code is distinct from delaying safety information. Required static effect dependencies must be complete; unknown dynamic dependencies require conservative enforcement, not an assumption of purity.

Later demand must not weaken assumptions of already published callers. If graph expansion changes an assumption, execution cannot continue under the stale result: dependent analysis, code generation, and publication would need to be renewed before entry. The current design does not adopt such a replacement protocol; a request requiring it must fail before unsafe execution. A prepared new callee alone does not repair a caller compiled from an incomplete summary. This is a publication invariant, not a choice of graph epoch or cache API.

The adopted ORC connection uses lazy reexports and call-through stubs. Entry lookup can produce the stub without preparing the body. Its first call synchronously requests preparation; ORC resolves the implementation and updates the forwarding target. The pause protocol covers every application thread inside ORC lazy call-through or lookup, including followers waiting for an existing materialization without invoking the compiler callback. Such waits publish a stable blocked participant state, and transfer to the resolved implementation passes the managed-entry gate. The ABI mechanism preserves already evaluated arguments across preparation. It must not reevaluate source arguments, duplicate moves, or rebuild borrowed places. Existing caller-owned values and access scopes remain valid across this pause.

One body request can define several physical entries, such as async entry/resume or an exposed wrapper. Self references and sibling-entry references use canonical public entries; implementation renaming must not leave alternate externally observed callable identities. Newly discovered dependencies can register entries without eagerly generating every dependent body. Recursive source graphs are permitted through registered identities; recursive compiler callback entry or symbol lookup during preparation is not an alternative cycle-resolution mechanism.

Each requesting application call waits synchronously for preparation and publication. Preparation runs on the compiler-affine service defined below, after all Plew-managed application participants have quiesced. Already entered external C work may continue, but managed return and callback entry remain gated. ORC's concurrent capabilities do not supply this Plew protocol. Signals must still reach process termination while compilation or the pause handshake is busy.

## Worker Demand Coordination

One demand session has one compiler-affine control thread, independent of the application's root event loop and workers. It owns session construction and mutation, the compiler registry and the preparation/publication sequence. Construct the session on that owner; do not transfer a nonsendable session or MutableRef across application workers. A worker's native demand bridge routes a stable session/entry/instance identity to the service and waits for an owned result. It does not read the Plew Dictionary registry, acquire session inout, or execute source checking on the requesting worker. Existing whole-target commands can keep their ordinary single owner; this requirement is for an active demand execution.

The service and application share runtime code and value protocols, with separately owned scheduling/global state. Compiler-private work is not an application continuation. Neither preparation nor its generated-code dependencies may wait for an application event, application lock or application callback. The service must remain available when the root thread is in C, awaiting a worker, or retaining a guard. If compiler work needs its own scheduling or an isolated generator, it uses that domain's admitted resources, never the paused application's loop or lazy entries. This defines ownership and routing without adopting a public thread or embedding API.

The native request transport and application pause registry belong to the execution owner. The control service drives this sequence:

1. **Admit and coalesce.** Validate the execution/session identity and complete physical entry key, retain the request's resource dependencies, and queue it under synchronization. Concurrent demands for the same key share one preparation result; distinct keys are serialized by the service. A registered entry, a semantic result and a completed materialization remain different states. Reject closed/stale owners before touching compiler state.
2. **Close managed entry.** Announce a pause generation and close application entry, event dispatch and managed callback gates. The requesting caller has preserved its ABI arguments/access scopes and joins the stopped set. Worker creation, exit and native/blocking transitions participate in the same handshake. Wait for the [runtime participant acknowledgements](runtime.md#managed-pause-and-native-boundaries), not for all external C calls to return.
3. **Prepare privately.** Only after quiescence may the service mutate the session, check/instantiate, close mandatory safety dependencies and emit code. Failure stays attached to the exact request and cannot publish partial semantic rows. Compile dependencies through normal request identities; register stable lazy entries for recursive source calls rather than invoking application code or recursively calling the native compiler callback.
4. **Publish completely.** The service coordinates ORC definitions, linking/materialization, required sibling entries, effect and allocation-mode admission, resource retention and forwarding-target publication. No requester may use an address merely because an LLVM module was emitted or submitted. Release/acquire synchronization must make completed code and its metadata visible before callers are admitted; target instruction-cache synchronization belongs to backend publication.
5. **Resume or terminate.** Mark the exact entry callable and wake its waiters through the entry gate. Queued requests can be processed under the same pause or a later generation; every compiler mutation still requires quiescence. Reopen managed execution only after the active publication work is complete. Failure keeps application entry closed and routes diagnostics to terminal process failure; no guessed return value, arbitrary-stack recovery or normal deinit completion is promised.

No request/coordinator lock is held while waiting for application acknowledgements or compilation. ORC callbacks must also release any lock required by the service before waiting; retained materialization responsibilities are not permission to hold a blocking ORC/session lock. The service cannot wait on a materialization whose completion requires the suspended requesting stack. Its adapter must transfer/delegate that completion responsibility or perform the work without such a dependency. Internal synchronization sections finish before acknowledgement, and waiters retain ownership records rather than a mutex the compiler needs. Source-level application mutexes can remain logically held because the compiler does not acquire them. This exclusion is transitive through common runtime support, allocators, symbol resolvers and other native services. Compiler/host service admission must establish that a native return or callback waiting at the managed gate cannot retain a lock needed by compilation/publication. Prefer services with no application callbacks under their internal locks, or separate compiler-owned resources; an unexamined shared native service is not evidence for this guarantee. Arbitrary external C is not automatically analyzed or made deadlock-free: unsafe native lock/callback contracts remain at the explicit FFI boundary.

For example, worker A may wait inside C for worker B; B demands an unprepared body. A is registered outside managed execution, B parks, and the independent compiler service can prepare/publish. After resumption B can reply to A. The same protocol works when the root awaits B or is inside C. It does not promise to resolve application-created lock cycles: if B genuinely needs a lock retained by A while A waits for B, that remains an application deadlock.

Execution-owner shutdown closes new demand/callback admission, preserves request and native-boundary resources until their obligations end, and orders registry removal after quiescence. Process termination remains possible without cooperative application progress. A reusable host's recovery/unload protocol is separately out of scope. Required validation scenarios include two workers demanding one entry (including a follower blocked inside ORC without entering the compiler callback), distinct queued demands, compute-only loops, root-waits-worker, blocked lock acquisition, native return/callback racing a pause, worker start/exit, recursive source dependencies, publication failure and signal termination. These are design obligations, not claims of passing implementation tests.

## Native Symbol Admission

Plew source-body references, shared metadata, program storage, declared foreign/runtime imports, and backend-introduced native services have distinct admission paths. A missing Plew body cannot fall back to an identically named compiler function in the process symbol table.

Source declarations carry frozen session-local body identities. Declared host imports carry explicit permission for host resolution and compatible physical signatures. Only those declared imports may be bound to existing process addresses. Selected backend-introduced memory services can use a restricted fallback library without exposing unrestricted process lookup to source modules. Explicit definitions retain precedence over fallback services.

Host registration must preserve state ownership as well as function signature. Common runtime code does not permit an application service to bind accidentally to compiler-private state. The compiler callback itself is a named `expose fn` with its established C boundary; connecting it does not require named functions to become values, general closure capture conversion, or a new unsafe Ref pointer API.

## Registry and Lifetime

The adopted callback bridge passes a nonzero session ID, not a raw Plew object pointer, through C. The compiler-affine owner stores Dictionary entries containing MutableRef-owned unique compiler sessions. Native demand receipt routes to that owner before taking a registry snapshot; application or foreign threads never read this nonsendable registry directly. On the owner, a fresh value snapshot keeps the selected shared cell alive during a request. Older snapshots do not observe later registrations; IDs are not recycled or wrapped into a previously valid identity.

A failed/unknown ID returns failure. A snapshot's continued ownership is not permission to execute after the execution owner has closed publication. Unregistration, quiescence, and executable-resource disposal must be ordered explicitly; self-unregistration from the session's destructor cannot solve registry ownership cycles.

The one-execution process owner keeps ORC code/globals, program arguments, and registration alive through all permitted callbacks, including native exit callbacks. Main return alone does not end their lifetime. For any finite-lifetime owner, first prevent further entry and finish callbacks, then destroy ORC/executable resources before releasing callback/session ownership; borrowed argument views must be restored before their owned strings disappear. ORC's engine/generators must not outlive the trampoline resources they use.

The current process-lifetime owner is not a reusable in-process Restart API. Process termination can let the OS reclaim resources without adding a guarantee to run every user deinit. A future reusable host must separately establish callback quiescence, pending-work disposal, global/state teardown, and resource reconstruction. Reusing the current global owner without that protocol is not an implementation shortcut. The [Hot Restart decision](decisions/hot-restart.md) retains the approved future host direction, rejected Hot Reload alternative, historical feasibility evidence, and limits without extending the current execution API.

For that future host, the fixed requirements above are not deferred: one common
runtime, explicit environment ownership, closed entry/notification admission,
quiescent callbacks and retained code/state until their last permitted use. The
open choice is the public host protocol and concrete teardown/reconstruction
mechanism. Revisit it when a framework needs multiple executions in one process,
with a defined native callback/resource model. Evaluate the 500 ms target only
for fixed edits, application initialization and host conditions, measuring input
admission, checking, JIT/linking, teardown and startup separately. The current
one-shot run and paused type-checking work do not depend on that host protocol.

## Failure and OS Integration

Compiler services return structured diagnostics or domain failures. CLI/process adapters render them and choose exit status. Native lazy materialization cannot recover by returning through an arbitrary function signature with a guessed value; terminal execution failure aborts/stops the execution process. Prior I/O is not rolled back, and user destruction is not guaranteed on that path.

The one-shot worker isolates compiler/application execution from the outer command's process orchestration. The outer command owns spawning, signal forwarding, waiting, exit-status propagation, temporary files, and final artifact publication. Build output must not replace a previous good artifact until generation and linking succeed. A compiler object file alone is not a completed executable.

A stable package-manager/tool installation strategy is separate from these runtime contracts. Single-binary distribution can embed standard resources and runtime objects while still using the permitted OS SDK/linker services. Development versus distribution linking must not change source checking or runtime meaning.

## Distribution Boundary

The adopted distribution unit is one native `plew` executable per supported OS/CPU, containing CLI dispatch, compiler modes, package resolver, required LLVM optimization/object/ORC facilities, standard source resources, runtime materials, version identity, and third-party notices. A single distribution file does not require a single process: isolated workers may reenter the same executable in an internal mode. A compatibility `plewc` symlink may select compiler mode, but a separate compiler binary, shell wrapper, or Python entry is not a required user dependency. Internal CLI/compiler responsibilities remain separate despite this packaging.

The user's dependency boundary follows Rust's native toolchain model: OS runtime and official SDK/linker/C toolchain for final native linking are permitted. A user-installed LLVM, libLLVM, opt, or llvm-config is not. Sending object files to an OS clang/cc linker driver is distinct from asking that external LLVM to process Plew IR. Project sources, external packages, git/cache, and explicitly selected native dependency toolchains are project requirements, not resources bundled into Plew.

Distribution LLVM components and non-OS dependencies are statically linked with fixed build inputs; OS libraries need not be fully static. The recipe must retain required verification, optimization, object output, and ORC capabilities. Standard sources are immutable embedded loader resources with logical diagnostic/module paths; checkout resources require explicit selection. Runtime materials are built for the distribution's target/ABI/instrumentation conditions and embedded, rather than compiled from C for each user build. This changes packaging, not the common AOT/JIT runtime contract. The initial host-native recipe does not establish cross-compilation SDK/runtime support.

Tool installation, version selection, and updates belong to external tools such as mise. Plew does not add its own version manager, updater, or toolchain-switching proxy, nor require mise at runtime. Package dependency resolution remains Plew's responsibility. Embedding LLD or a complete Clang frontend is not necessary under the permitted OS-linker boundary; adding either requires a separate decision.

Ordinary development retains the existing dynamic LLVM path and separate checkout scripts. Distribution archives are not the default development carrier, and packaging optimization is not a prerequisite for demand execution. [Build instructions](../../scripts/build/README.md) own actual commands, supported recipe targets, and evidence capture. A release candidate must be rebuilt from the selected current inputs and pass applicable gates; an older candidate's success cannot certify newer sources.

[Release admission work](../issues/com-ao7z.md) remains separate from feasibility. Release admission additionally requires non-OS dynamic-dependency inspection, relocation without LLVM/Python/adjacent std/separate compiler, and clean-host/minimum-OS/signing checks. OS-only PATH isolation alone cannot exclude absolute-path dynamic dependencies or prove compatibility on another host. Package acquisition/native dependency cases disclose their own required tools. Full-suite, sanitizer, fixed-point, and performance/promotion rules remain the operational validation authority; packaging success alone cannot promote the seed or public release.

## Change Paths

Adding a command starts with its target/input and required success guarantee, then invokes the existing session services and artifact consumers. A new CLI spelling must not introduce independent source-checking rules. Test unused invalid bodies to distinguish whole-target and demand coverage, and use the same dependency/configuration inputs when comparing modes.

Adding a callable kind requires retained body identity, an agreed physical entry signature, registration, requested-body emission, dependency admission, and publication before execution. Test multiple entries per body, recursion, first and repeated calls, and failure before the callee starts. Callback lifetime tests must exercise the final native consumer, not only registry lookup.

Changing startup or global storage requires tracing preparation, definition, initialization, and main entry together, including zero-sized identity and repeated requests. Changing process ownership or enabling a second execution requires a lifecycle design covering native exit callbacks, pending work, signal handling, registry closure, and code disposal; resetting one global flag is insufficient.

## Reference Designs and Rationale

[Go package initialization](https://go.dev/ref/spec#Package_initialization) and its [dependency-order implementation](https://go.dev/src/cmd/compile/internal/types2/initorder.go) provide a useful precedent for transitive static dependencies and cycle diagnostics. Plew retains asynchronous initializers and schedules only dependency-ready bodies. It also requires conservative bounds for admitted dynamic/callback execution; Go's deliberately unspecified order for hidden dependencies is not permission to observe incomplete Plew values. Static possible-dependency cycles are rejected even if no single runtime path traverses the cycle. This changes the former dynamic forcing policy rather than pretending the two orders accept the same programs.

[Rust's driver/interface separation](https://rustc-dev-guide.rust-lang.org/rustc-driver/intro.html) distinguishes phase orchestration from lower-level compiler services and notes that internal APIs are unstable. Plew uses that responsibility distinction without promising stable embedding interfaces or copying Rust's crate/query organization.

[Swift's driver design](https://github.com/swiftlang/swift/blob/main/docs/Driver.md) describes planning and executing frontend/link jobs. Plew similarly keeps OS work outside semantic checking. Swift's compilation-job structure does not imply that Plew needs file-per-job compilation, independent binary modules, or a general distributed build scheduler.

[ORCv2 lazy reexports](https://llvm.org/docs/ORCv2.html#laziness) provide stable lazy entries and materialization. Plew supplies source demand, preparation permission, session lifetime, and terminal failure policy. ORC's concurrency guarantees for its own linking operations do not prove application reentry or runtime thread safety. Dart's [VM architecture](https://github.com/dart-lang/sdk/blob/main/runtime/docs/README.md) is a reference for separating compilation facilities from execution support; Plew's synchronous application pause and common runtime constraint are explicit differences.

[Rust installation requirements](https://doc.rust-lang.org/book/ch01-01-installation.html) are the reference for allowing platform linking tools while shipping the language compiler itself. Plew intentionally chooses a single distribution unit rather than adopting Cargo/rustc/rustup's separate executables and toolchain manager. [LLVM distribution guidance](https://llvm.org/docs/BuildingADistribution.html) and [CMake options](https://llvm.org/docs/CMake.html) guide component/dependency selection, but a Release label alone does not prove optimization of archives after downstream bitcode conversion. That property belongs to recorded recipe/tool inputs. [LLD embedding](https://lld.llvm.org/) is a future option, not an adopted user dependency or requirement.

### Lazy Compilation Placement Comparisons

Frontend placement, machine-code JIT placement, and runtime placement are separate
axes. Source-body checking, machine-code laziness, and execution-frequency-based
tiering are likewise separate choices. An in-process JIT does not imply deferring
every required source check until the first call. The adopted Plew arrangement
combines requested whole-body checking/generation with compiler, ORC, and
application execution in one process; compilation pauses the application. AOT
and run share runtime implementation, ABI, and semantic rules. If implementation
requires splitting those runtimes, stop for a design decision rather than silently
introducing a run-only executor. Shared implementation still has explicit state
ownership and reentry restrictions.

The following source accounts are comparison inputs, not claims of current CLI
compatibility or Plew performance equivalence:

| Reference design | Relevant distinction and Plew implication |
|---|---|
| [Dart VM / Flutter](https://github.com/dart-lang/sdk/blob/main/runtime/docs/README.md) | CFE produces Kernel; the VM can compile through first-call stubs. The described standalone kernel service isolate and Flutter's development-host frontend_server illustrate different frontend placements. An isolate is not an OS process. This is not Plew's adopted external frontend. |
| [Julia JIT](https://docs.julialang.org/en/v1/devdocs/jit/), [compiler](https://docs.julialang.org/en/v1/devdocs/compiler/) | Inferred IR reaches LLVM/ORCv2 and is linked into the process. This is a close reference for requested compilation, reuse, and publication, without importing Julia's type semantics. |
| [V8 preparser](https://v8.dev/blog/preparser), [Sparkplug](https://v8.dev/blog/sparkplug), [compile hints](https://v8.dev/blog/explicit-compile-hints) | Early syntax/scope work and deferred detailed parsing/bytecode differ from later machine-code tiers. These dated design accounts motivate distinguishing required checks, not adding a Plew interpreter or tier. |
| [.NET execution](https://learn.microsoft.com/en-us/dotnet/standard/managed-execution-process) | Source-to-CIL compilation precedes first-method-call JIT and reuse. Lazy machine entry is not source-checking laziness; the account does not cover every modern tier/AOT mode. |
| [Ruby YJIT](https://docs.ruby-lang.org/en/3.4/yjit/yjit_md.html), [Ruby 3.3 RJIT](https://www.ruby-lang.org/en/news/2023/12/25/ruby-3-3-0-released/) | In-process lazy block versioning and the historical experimental Ruby-written JIT illustrate compiler/executor coexistence. Neither implies duplicating Plew's runtime, and RJIT is not a production recommendation. |
| [PyPy architecture](https://doc.pypy.org/architecture.html) | Meta-tracing generated for an RPython interpreter illustrates runtime/compiler cooperation, but is a different project from adding ORC to the existing LLVM backend. |
| [OpenJ9 JITServer](https://eclipse.dev/openj9/docs/jitserver/) | Optional external JIT shifts CPU/memory costs under communication constraints. It is a valid alternative placement, not evidence that a local CLI must use it. |

External frontends or JIT services remain future placement options requiring a
new decision. Their existence neither overturns Plew's chosen synchronous bridge
nor establishes a need for separate AOT/JIT runtimes. Plew validates its own common
runtime and execution semantics instead of importing the other systems' timings.

## Implementation Evidence and Open Boundaries

Focused source inspection uses compiler revision `6fe09bc7c0e75260b3f773643921478b5020b94f`:

- `Compiler.pw` adapts low-level run/check/object/text requests. `CheckedProgram.pw` owns CompilerSession, declaration/concrete/Mid request state, execution failure, partial-to-whole checking, and AOT preparation. Check and executable preparation are distinct consuming operations.
- `CompilerExecution.pw` opens/registers a session, creates the process owner, registers declarations, installs global storage, and invokes main. Declaration lowering first prepares initializers; main/exposed entries can remain body-lazy. The global process owner rejects a second execution and remains retained after main return or post-publication failure. Field order is ORC, arguments, registration for eventual ordinary destruction; process teardown does not guarantee that destruction occurs.
- `CompilerSessions.pw` uses monotonically increasing nonrecycled IDs and value snapshots of Dictionary-held MutableRef cells. `CompilerCallbacks.pw` retrieves a fresh snapshot, requests the body, emits diagnostics, and transfers the owned module/context pair through C.
- `native/llvm_backend.cpp` uses synchronous LLJIT, prohibits lookup during preparation, distinguishes source/host metadata, registers multiple entries, checks shared metadata's session/identity/size, and rewrites uses to canonical stubs. Native `emitted` bookkeeping precedes successful IR-module submission and is therefore not by itself proof of callable success; failures are terminal. The DataLayout admission discrepancy remains recorded in the backend chapter.
- `distribution/_.pw` dispatches check directly and run to the worker adapter. `native/tool.cpp` resolves dependencies for build/run, invokes the one-shot worker, forwards signals, waits for completion, and links through a pending output before committing it. This is selected-path inspection, not proof of complete command parity.

This audit does not certify every source snapshot race, target selector, package command, dependency-resolution path, request cache, foreign signature, global initialization path, signal race, failure cleanup, or ABI trampoline. Check's dependency-resolution parity with build/run requires explicit audit; direct dispatch alone does not prove it. The Runtime chapter defines AOT sharing-plan admission and the conservative atomic demand baseline; implementation of those protocols remains unaudited. A finite reusable embedding lifecycle and stable public API remain outside the adopted current execution scope. No compiler/test/performance run was performed for this chapter.

## Demand Execution Integration Audit

The [declaration/execution supplement](declaration-and-execution-audit.md)
retains the abstract-versus-concrete obligation map, request/cache integration,
and native probe boundaries. Historical evidence is indexed there; it does not
certify the current implementation or broaden this chapter's publication guarantees.

## Retained Follow-up Investigations

[process entry and associated storage](../issues/com-8j0w.md), [additional target scope](../issues/com-ej0z.md). These scoped tasks retain implementation limits or uninspected combinations; their existence is not evidence of a current defect or completed coverage.
