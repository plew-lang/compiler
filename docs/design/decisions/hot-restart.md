# Hot Restart: Feasibility and Host Lifecycle

**Decision:** LLVM ORC is adopted for development execution. Whole-environment Hot
Restart is an approved future host direction, not a feature promised by the
current one-shot execution API. [Driver and Execution](../driver-and-execution.md)
owns current publication and process lifetime; [Runtime](../runtime.md) owns the
common execution implementation. This note retains the restart decision and its
boundaries, not a second runtime specification.

## Purpose and Scope

The development benchmark is Flutter's Hot Restart: an already running app,
saved source, and an explicit user operation. Reading changes, checking, and
compilation begin only after that operation; saving does not trigger preparation.
Previously prepared analysis/code/host infrastructure may be reused, but the
application state starts fresh. The target is operation-to-new-application-ready
within 500 ms for demonstrated input and initialization sizes, not a guarantee
for arbitrary edits, programs, or expensive initialization. The initial proof is
headless; native windows and framework implementation are outside it.

Hot Reload is rejected because its implementation/maintenance cost and mixed
old-state/new-code behavior can harm predictability. State migration,
compatibility checks, and machinery solely anticipating Hot Reload are not part
of the design. Incremental compilation and code caches can independently improve
Hot Restart. Recreating the execution environment does not require eagerly
compiling every function.

The compiler exposes common execution facilities; frameworks own windows and
restart orchestration. External watch tools can restart a process. Current run
is a thin one-shot execution adapter, with terminal demand-compilation failure,
not a reusable surviving-host recovery protocol. Its completion criteria do not
include environment recreation or the 500 ms restart target. Check/build/run
retain their specification-owned checking scopes. Historical full-compilation
restart timings are not measurements of current demand checking/JIT latency.

## Approved Future Environment Contract

A development host ends the old application's environment and creates a new one.
Explicit application shutdown and natural completion of all Promises are not
prerequisites. Ordinary Promise-handle release remains non-cancelling and ordinary
ARC/deinit semantics remain unchanged. Development environment termination does
not promise that every user destructor or business cleanup finishes. This choice
is already adopted; an implementation must not shrink it to rejecting ordinary
pending timers or Promises.

Every managed global root, heap allocation, async frame, queue, timer, closure,
and callable reference needs an environment owner. At a quiescent boundary the
host makes the old generation uncallable, rejects old notifications, and reclaims
its managed resources. Removing an ORC ResourceTracker alone is not environment
termination. Dropping queues alone neither releases all frame owners nor makes
unloaded resume pointers safe. Re-running global initializers is not old-value
cleanup. No restart-only destructor order is implicitly added to source semantics.

Host-mediated notifications carry generation tokens and payloads rather than raw
old-code callback pointers. FFI-owned resources and retained native pointers need
registration/unregistration and lifetime contracts. Arbitrary third-party native
execution, external resources, or another thread's callback cannot be stopped or
reclaimed merely by discarding the Plew environment. Identify unsafe boundaries
and when process restart is required; do not claim universal foreign cleanup.

Candidate checking/compilation/link failures discovered before commitment leave
the old environment usable. After ending it, new initialization failure does not
promise rollback. Later demand checking/JIT failure likewise cannot guarantee an
old environment to resume. Diagnose the failed/nonrunning state and verify what
happens on the next restart. Lazy execution cannot establish all bodies' success
before startup. The proof's injected host-readiness failure is not panic recovery.

The initial boundary is when native application execution has returned to the
host. It does not forcibly interrupt a long synchronous computation/native call,
or recover in process from panic or an OS fault. Compiler/runtime execution and
state ownership stay shared under the runtime chapter's rules; a separate AOT
and JIT execution implementation remains prohibited. A custom VM or GC is not a
prerequisite. If required termination semantics cannot follow existing decisions,
seek a new decision before implementing them.

## Evidence and Limits

[Saved evidence](../../../../evidence/2026-10-01/compiler/orc-restart/README.md)
records the historical macOS/ARM64, LLVM 20.1.1 diagnosis and its scoped conclusions.
The [probe guide](../../../scripts/diagnostics/orc-restart/README.md) owns executable
commands and diagnostic implementation details. Controlled function replacement,
whole-source recompilation, and environment teardown were separate experiments.
The results support ORC feasibility for the measured small programs, including
layout/signature/generic/module edits, and do not establish a production
incremental frontend, stable embedding ABI, or general sub-500-ms scalability.

The teardown proof used checked transformations of generated runtime C and a
linear allocation ledger. These are diagnostic devices, not adopted production
allocation tracking or a compiler/runtime implementation change. Old callbacks
were simulated through the host, not arbitrary FFI. The sanitizer proof included
intentional fault controls and instrumented generated functions/runtime/host;
prebuilt LLVM itself was not instrumented. AOT comparisons cover their recorded
examples, not every language feature or timing difference.

A deep expression calling 100 helpers stalled before LLVM output in the recorded
compiler and was interrupted by the 60-second no-progress watchdog. A flat input
with 100 helpers succeeded. The failed shape cannot support a general function
count performance claim; its current reproducibility and responsible stage remain
unverified. The linked investigation owns that question.

## Measurement and Product Completion

Measure backend-only work separately from end-to-end restart. Backend measurement
includes IR reading/patching, verification/optimization, native generation/link,
lookup/first invocation, and old-code reclamation; registration alone hides lazy
work. It excludes frontend and application initialization and cannot establish
restart latency. Separate first host/application load from updates and distinguish
warm caches from newly compiled changes.

End-to-end timing starts at the explicit operation and includes source reading,
checking/dependency processing, LLVM generation, JIT/link, old-environment ending,
new initialization, and a successful new-generation request. Do not announce ready
while work necessary for that measured readiness event is deferred beyond it.
The historical full-source probe materialized all candidate code before readiness;
that is its measurement condition, not a rule requiring current demand execution
to prepare future first-call bodies eagerly. Record every sample, median/p95/max,
500-ms exceedances, target/LLVM/optimization settings, input/tool hashes, and first
load separately. Keep sanitizer timing separate. Repeated restarts must account
for code, symbols, managed memory and external resources; distinguish retained
caches from leaked generations. Compare each source version with fresh compilation
and AOT, including dependency/layout/signature/generic changes. Diagnose the
dominant stage when the target is missed rather than assuming ORC is responsible.

Production work must replace diagnostic runtime rewriting with explicit ownership,
resource tracking, host interfaces and failure transitions. The
[host lifecycle issue](../../issues/com-yr1o.md) owns this deferred work;
[current compiler stall investigation](../../issues/com-0k37.md) is separate.
Existing process-lifetime runtime storage and direct resume/frame pointers do not
establish reusable embedding. No implementation completion is claimed here.

## Platform and Reference Boundaries

[Flutter's restart documentation](https://docs.flutter.dev/tools/hot-reload)
distinguishes debug restart from native-code changes requiring a full restart.
It supplies the state-reset development benchmark, not a mandate to use Dart's
collector or Hot Reload. [Flutter iOS setup](https://docs.flutter.dev/platform-integration/ios/setup)
is not evidence that an independent ORC host has solved device signing/executable
memory restrictions.

[Apple's JIT guidance](https://developer.apple.com/documentation/apple-silicon/porting-just-in-time-compilers-to-apple-silicon)
describes hardened-runtime entitlement, MAP_JIT, and Apple-silicon write/execute
constraints. Local macOS success does not certify signed GUI distribution, iOS
hardware/simulators, Android, or other operating systems. Target admission and
host packaging require platform-specific verification.

[LLVM ORC](https://llvm.org/docs/ORCv2.html) supplies native materialization/linking
and resource management, not application-state ownership.
[Swift's materialization unit](https://github.com/swiftlang/swift/blob/main/include/swift/Immediate/SwiftMaterializationUnit.h),
[Clang-Repl](https://clang.llvm.org/docs/ClangRepl.html), and
[PostgreSQL's LLVM integration](https://github.com/postgres/postgres/blob/master/src/backend/jit/llvm/llvmjit.c)
are references for compiler/JIT integration and resource management. They do not
prove Plew's environment termination or mobile-host feasibility. Their existence
and the scoped ORC proof remove any current need to migrate to a JVM/custom VM;
future changes still require evidence and a design decision.
