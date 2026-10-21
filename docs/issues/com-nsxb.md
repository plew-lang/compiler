---
id: com-nsxb
status: closed
deps: []
links: []
created: 2026-10-21T12:58:26Z
type: task
priority: 1
assignee: Koji Murata
tags: [design, verification]
---
# Audit adopted design contracts through implementation consumers

## Scope and Pinned Inputs

Detailed read-only design/implementation audit requested after closing the
canonical design review. Design/source input: compiler `78bd96912aacb39ee2601e95a877c33e0b556ac7`;
spec `1e0c4d08777edc521e0e64f42588d4996b1c66d8`; Syntax pin
`00f740e1178e5b992cfdd30ddaa5a0612ce27b43`. Preserve the dirty compiler binary and
untracked Python caches; neither supplies execution evidence.

[met-z0ro](met-z0ro.md) is the representative-domain inventory, not this audit's
completion evidence. Reuse its owning tasks, but recheck source and saved-result
consumers rather than copying its conclusions.

## Method and Completion Boundary

For each adopted boundary record the contract, concrete producer/key, storage and
publication, substitution/consumer and failure/cleanup path. Distinguish a traced
conforming route, mismatch, absent family, partial closure, unverified combination
and intentionally deferred feature. A matching declaration or verifier alone is
not end-to-end evidence. Cite exact source symbols and the pinned revision.

Cover the 18 reference domains and storage/library/collection supplements. Dig
into source-to-final-reader closure, synthetic and global owners, proof/instance
identity, Mid stages, async ownership and driver/resource boundaries. Record
uninspected combinations explicitly; do not infer a newly reproduced runtime bug
from source-only architectural gaps. Existing tests may be read, not rerun.

Finish with owning follow-ups, dependency/order reasoning and a bounded coverage
statement. Do not repair compiler code, change language semantics, run compilation
or performance gates, promote carriers or enlarge met-si6j automatically.

## Audit Results

### A. Source Authority, Storage and Concrete Consumption

Contract owners: [body checking](../design/body-checking.md),
[checked storage](../design/checked-body-storage.md),
[types/evidence](../design/types-and-evidence.md) and [instantiation](../design/generics.md).

| Boundary | Traced source chain and decisive observation | Result / repair owner |
|---|---|---|
| Session-owned checking and execution | CheckedProgram.pw CompilerSession owns Comp, requests, templates and executionFailure; lowerBody passes prepareBodyAccess's program/ambient into lowerRequestedLlvm. No mutable Comp accessor is exported by that session. | Conforming scoped outer boundary; not certification of inner stores |
| One source construction authority | Resolve/Preparation.pw prepareLexicalBodyUncached performs Record(false), Generic, Verify, Record(true); global preparation performs record/verify/record. Record.pw selects static members and verification reads/rechecks selected signatures. | Partial; met-ucze. Unifying the helper alone would not remove repeated decision authority |
| Successful owner publication/failure | Resolve/Record.pw prepareLexicalBody and Resolve/Global.pw prepareGlobalInitializer save Result and restore Cursor; expression/binding/statement writers reject completed owners, including Failed. | Existing bounded protection; no new universal Active state is claimed or required for non-recursive local requests |
| Owner-local sealed backing | Frontend.pw preparedSemanticFacts checks the owner, then retains all-owner expression/aggregate/try/match/binding/statement arrays and global indexes; Mid/Build.pw state.sourceFacts and Mono/Call.pw preparedAccessUseFacts consume them. | Partial; met-acfl. CoW snapshots preserve an older view but are not the adopted per-owner payload/cost boundary |
| Source header sealing | Resolve/Record.pw recordSourceBodySignature validates types then replaces sourceBodySignatures[fnIdx]; it has no completed-owner guard. Frontend.pw preparedFunctionBodySignature and Mid/Build.pw buildParametricMidBody consume this table. | Missing structural write closure; met-acfl. No production post-success overwrite is reproduced |
| Provided-body provenance | Resolve/Expr.pw semanticBodyOwner checks lexicalOwnerFnId and shared body identity; Mono/Call.pw sourceFunctionOwner maps closure and global initializer owners explicitly. | Existing mechanism to preserve, not wholly absent provenance |
| Synthetic declaration provenance | Resolve/Module.pw moduleOf returns entry module for unregistered offsets; methodInEntryModule uses the first statement and returns false for empty bodies. | Partial; met-ucze/met-acfl. Cannot substitute for a header's explicit module/origin; no fresh visibility miscompile claimed |
| Value/Unit/no-normal-value and binding consumption | Frontend.pw PreparedSemanticFacts expression/binding/completion readers validate owner; Mid/Build.pw buildMidStmt and buildParametricMidBody require saved facts/signature; Mono/Call.pw preparedSourceExpression and requiredAccessExpression reject missing records. | Existing successful lanes. Header/record completeness and all optional-versus-required branches remain met-acfl; do not erase these migrations |
| Aggregate, pattern and try | Record.pw publishes selected semantic aggregates/matches; Mono/Call.pw preparedBodyAggregate/preparedBodyMatch/preparedBodyTry carry body+initializer owner; Mid/Build.pw builds operands and payloads from sourceFacts. Global composite Mid switches to each initializer's facts. | Existing lanes, physical seal/final-reader closure partial; met-acfl/met-6e6k |
| Generic environment identity | Mono/Call.pw sameInstanceEnvironment compares receiver, complete proof, declaration-bound evidence, ParamIds and argument types; findBodyInstance keys by declaration plus that environment. | Conforming inspected key. It is false that body identity currently ignores all proof/bound inputs |
| Simultaneous substitution | Mono/Ground.pw groundTermInEnvironment substitutes ParamId-bound replacements outside the callee map; a legacy bare-name fallback remains for unstamped terms. | Partial migration; met-ia09/met-6e6k. Preserve the correct simultaneous lane and remove fallback only with producer stamping |
| Call publication to consumption | resolveBodyCallee reads Direct/Dynamic/StaticMethod templates; recordSelectedBodyCallee retains signature/modes/conversions; requirementCallConstraintEvidence consumes a retained implementation plan; Mid/Instantiate materializeCanonicalMidCall reads final resolution IDs. | Existing lanes, not a universal reader-reselection defect. The StaticMethod default still uses CallableConstraintEvidence.Declaration; met-ia09 owns whether each synthetic/protocol lane closes its declaration evidence |
| Independent closure publication | Record.pw publishes closure metadata then checks its body inline; Mono/Call.pw putSemanticClosure stores the parent Function/Global completion owner, while bodyKey is separate for execution. | Partial; met-acfl. A separate Mono key is not an independent successful CheckedBody request |
| Completion ownership | SourceCompletion.pw centrally composes source/execution edges; completionBlock consumes give and completionLoop keeps source continuation separate. Mid/Build lowers saved facts into scope exits/CFG. | Shared completion core exists; full expression-shape/control coverage remains met-si6j/com-gyup, not a new implementation of old give semantics |

File paths in this table are relative to src unless otherwise qualified. These
are source traces, not new passing tests or proof of every language combination.

### B. Mid, Ownership and Representation Boundaries

| Boundary | Traced source chain and decisive observation | Result / repair owner |
|---|---|---|
| Mandatory stage chain | Mid/Prepare.pw privately constructs instantiated/access/drop/executable tokens in order; Mid/Program.pw caches Result per body and requires a ready signature. Backend/Llvm/Mid.pw preflight reads executable input. | Conforming inspected preparation path; foreign-arena raw IDs still require admission discipline |
| Structural operation vocabulary | Mid/Ir/Structure.pw owns opcode recognition and occurrence/successor queries; Mid/Async.pw uses them rather than collecting AST locals. Unknown opcodes and parametric-only forms are rejected at stage boundaries. | Existing shared structure, not a missing visitor framework |
| Ownership/effect guarantee distinction | DeclarationProgram.pw CheckedDeclarationBody and Mid/OwnershipAnalysis.pw cache local verification; declaration graph retains unresolved calls/destruction; PreparedProgram/CheckedProgram close concrete global/ambient effects. | Existing distinct scopes; generic/dynamic effect combinations remain explicit, not silently certified by local tokens |
| Async activation ownership | Mid/Build.pw marks async input locals ownsAtEntry; Backend/Llvm/Async.pw genLlvmAsyncFunc retains Borrow arguments directly into frame slots and transfers Move; MidAsync completes source drops before Promise/frame release. | Partial; com-tn1m. No explicit common Mid activation-input acquisition plan exists; move decision out of backend without double acquisition |
| Async suspension/ready await | Mid/Async.pw includes Drop and borrowed-owner dependencies in liveness; Backend/Llvm/MidAsync.pw midAsyncSuspend branches done Promises directly to completion. | Existing lanes; do not claim all await operations reschedule |
| Async supported result family | Verify/Func.pw restricts payloads; Backend.pw PlewPromise value and MidAsync completion use i64; Async.pw rejects generic/method entries. | Partial; com-tn1m/met-b2la, separate from a reproduced ownership failure |
| By-value private ABI | Backend/Llvm/ValueAbi.pw maps logical types to omitted/direct/byval lanes; parameter binding and call emission consume those lanes. | Existing common ABI, no struct-size threshold asserted by this audit |
| C ABI conversion | Backend/Llvm/CAbi.pw centralizes F32 conversion, inout temporary/writeback, target narrow-integer extension; ValueAbi remains private. | Conforming scalar subset; aggregate/public-callback coverage remains com-042v/com-0oxy/com-qnyl |
| Optional return-copy transform | Mid/Optimize.pw returnTransferOperand lacks scopeTransferOperand's explicit isUnique exclusion, rewrites Copy to Move before final executable verification. Verify.pw rejects unique Copy at declaration/executable stages. | Confirmed eligibility omission; malformed-input acceptance still needs a controlled end-to-end case (com-wqd7). Authored declaration checking is a real earlier guard, not assumed absent |
| Buffer lifetime and failure | Backend/Llvm/Mid.pw Set commits new slot before old release; Clear/Truncate commit count before retired-range release; Remove* transfers its result. Arrays.pw cowArraySlot performs typed retains after shared backing separation. | Existing lanes. Reentrant retired-range traversal and dictionary/set invariants remain com-zgk9, not certified by commit order alone |
| Buffer capacity safety | std/Core.pw reserve -> Mid.pw plain count+additional -> Arrays.pw wrappers -> Backend.pw emitted allocation/grow/reserve. Addition/multiplication/growth and malloc-null have no checked failure boundary on this route. | Source-confirmed mismatch, new owning bug com-p10m; no runtime crash reproduced |

### C. Source Admission, Syntax, Lookup and Generated Inputs

Contract owners: [sources/modules](../design/sources-and-modules.md),
[syntax](../design/syntax.md), [lookup](../design/name-lookup.md),
[metaprogramming](../design/metaprogramming.md) and [library ownership](../design/standard-library.md).

| Boundary | Traced source chain and decisive observation | Result / repair owner |
|---|---|---|
| Shared parser entry and spans | Loader.pw parseFileSyntax lexes/parses into one SyntaxFile with the original base; syntax parseExprAst/parseBlockAst materialize from direct parser results. SourceFiles.pw append/containing preserve disjoint ranges and return None for synthetic gaps. | Existing common entry/provenance. All arena/value-AST constructs and retired helper reachability remain com-2p9p; private old helpers alone do not prove a competing active grammar |
| Admitted source lifetime | Frontend loads bytes/syntax before body demand; CompilerSession holds that Comp. SourceAccess separates embedded paths and never falls back to disk for a missing embedded resource. | Conforming scoped session path. Filesystem existence/read races and failed-read versus empty-file handling are not proved safe by existence checks alone |
| Module graph/membership | Frontend queues part/use distinctly, rejects duplicate admitted part targets; Loader rejects non-impl part items; Check/Visibility detectImportCycles walks source import edges. | Existing module/forest checks; exhaustive filesystem alias/cycle combinations unverified |
| Overload sets and provenance | Resolve/Module appendFreeFunctionSurface combines public declaration identities and re-export origins, deduplicates Func IDs; visibleFreeFunctions combines local/imported candidates before callableArgMatchRank. | Existing overload combination to preserve; the file-scope defect below is separate from declaring imports universally broken |
| File-local use scope | Frontend.recordSyntaxImportOrigins -> Ir/Modules.registerImportOrigin indexes module+NameId; Visibility.moduleBindingAt/checkImports and Resolve/Module.visibleFreeFunctions omit the file when reading/merging. | Source-confirmed mismatch; new com-w4c2. Root/part bindings leak or collide despite spec15's file-local rule |
| Top-level lock/direct package binding | Frontend captures entryLock once; each file's manifest supplies direct names to resolveGitDepImport with that root lock. | Existing intended authority. Manifest.loadLock's per-package comment is not the actual loader behavior |
| Reachable version-resolution closure | resolve/Resolver.runResolver queues all manifest git edges, skips path-to-git closure, and first-wins deduplicates by url+major after per-edge pickLatest. Lock.lockCommitForConstraint can reject an unsatisfied later edge but cannot find the omitted joint solution. | Source-confirmed resolution gap; new com-9ttw. Independent from native builds and command-entry asymmetry |
| Capability syntax/summary/proof | Pinned Syntax binder fields and Lower/Decl.lowerTypeParamBinds carry sendable only; Ir Bind/nominal declarations lack allowunique/autounique ranges; Check/Unique recursively skips boxed/array-owned edges and rejects unique generic use under the old restrictions. | Absent end-to-end family; met-b2la. No implementation of the new shared capability SCC/Boolean relation/L limit is claimed; existing sendability's 32-depth false result is a different query, not that protocol |
| Impl-only deinit | Pinned Syntax accepts struct-body deinit; Lower/Decl emits its Func; CompilerExecution SessionRegistration, Backend LLVM owners and current fixtures use it. | Source-confirmed mismatch; met-2t3l. Includes real compiler/library migration, not only parser rejection |
| Macro identity/form | Codegen/Gen.synthGenMain validates name/field visibility, constructs parseItem/derive/write calls and branches on argument count zero; the required library deriveFromSource/form/role handoff is not represented by this chain. | Partial; com-vy62. Bare X and X() cannot be distinguished from argument count alone |
| Generator result framing | Native tool.cpp builds one harness per requested file and captures all stdout into PendingFile before rename; the harness writes returned fragments through ordinary write. | Output staging exists; no separate per-invocation result channel protects output from incidental provider prints, no compatible-host-unit plan/receipt publication; com-vy62 |
| Ordinary generated-part admission | Frontend sawDirective -> generated sibling exists -> queue. Absent sibling is silently skipped; no receipt/source/provider/configuration match is validated. | Source-confirmed absent admission boundary; com-vy62. Arbitrary provider I/O freshness is deliberately not required |
| Native package plan/execution | Manifest parses name/dependencies; resolve owns Plew git/path selection; native tool build links the compiler's own runtime/harness recipe. | Package-native trust/sandbox/tool-loader/host-target/provenance family absent on these routes; met-nm1w. Existing tool link code is not that service |
| Compiler-known operations | Lower/Impl.runtimeIntrinsicDeclaration qualifies bundled extern function ownership and saves Func.runtimeIntrinsic; Mono/Call and backend consume this selected enum. Mono/Helpers Ref classifiers still use head spelling+arity. | Useful operation identity lane; standard type/projection identity migration remains met-op15. Full trusted-signature validation is unverified, not implied by an intrinsic tag |
| Language test declarations | Pinned Syntax TopItemAst/SyntaxTopItemKind and compiler CLI requests have no language-test discovery/runner lane. tests/harness discovers external fixtures instead. | Adopted language-test feature absent; com-8ec0. External test infrastructure itself is present |

The local syntax checkout was clean and matched the exact lock pin. This audit
uses its implementation as evidence, not comments claiming full grammar coverage.

### D. Runtime, Driver, Native Ownership and Diagnostics

Contract owners: [runtime](../design/runtime.md),
[driver](../design/driver-and-execution.md), [ABI](../design/representation-and-abi.md),
[LLVM](../design/llvm-backend.md) and [diagnostics](../design/diagnostics.md).

| Boundary | Traced source chain and decisive observation | Result / repair owner |
|---|---|---|
| Source/check/executable guarantees | Compiler.pw runCheck -> CheckedProgram.check stops before LLVM; CompilerSession requests rooted declarations before concrete Mid/access and lowerBody. Gen explicitly selects a harness route rather than whole-target check. | Existing separation; all requested-body equivalence remains met-si6j/met-0139/com-vy62, not permission for weaker typing |
| CLI dependency admission | distribution/_.pw routes check directly to runCheck; native/tool.cpp resolves before build/run, gen uses its harness path; Resolver.needsResolution trusts any existing lock. | Structural asymmetry; met-0139 still needs cold/warm fixed-input controls before claiming a wrong result |
| Startup execution closure | Resolve/Global.collectGlobalDeps follows Call arguments and direct operands, defaults unhandled block forms; globalDfs/orderGlobalsByDependency sort that restricted graph (single-root early return). CheckedProgram separately prepares a combined initializer root. | Partial; met-c58b. Declaration global-access analysis does not establish initializer readiness or transitive effects |
| Frozen type destruction | Mono/Ownership.checkedFinalDestruction/finalizeDestructorCalls validate ready contracts and selected deinit body signatures; backend StmtDeinit consumes frozen children/calls. | Existing end-to-end lane. All recursive/generic/implicit effects and late mutation need met-6e6k/met-ia09/com-zgk9 controls, not a new backend destructor selector |
| Standard reference/lock/weak family | std/Core has Ref/MutableRef, separate WeakRef[T]/WeakMutableRef[T] and upgrade operations; no FrozenRef/MutexRef/Guard/Weakable family. Current source is Arrow/ArrowMethod, not new .*. | Adopted family absent; met-op15, with unique-generic integration met-b2la and transport com-qzpm |
| Sendability | Infer/Sendability returns false at depth 0, propagates Ref/WeakRef payload sendability; pinned syntax loudly rejects spawn expression/fn. | Ref rule mismatch and unsupported worker feature (com-qzpm). No live worker race is inferred from a feature not executable today |
| RC plan and shared weak ownership | Backend.emitLlvmRuntime emits ordinary non-atomic rawbuf/weak counts; common reference operations use that runtime. No AOT may-share plan or conservative atomic demand variant is carried into these allocations. | Absent adopted concurrency/RC family; com-qzpm. Do not enable spawn first and repair atomicity later |
| Event loop/outcomes | Backend.emitLlvmRuntime uses ready tasks, timers, virtual-now advancement and scalar Promise values; MidAsync uses that same Promise protocol. | Existing single-thread subset. OS readiness/pending-worker lifetime/typed and unique result transport are partial or absent; com-tn1m/com-qzpm |
| Shared AOT/JIT runtime | LlvmJit registers host runtime imports, native LLVM isolates process-symbol fallback and supplies only selected memory libcalls; CompilerCallbacks calls the same compiler preparation/lowering pipeline. | Existing common runtime/import lane. No evidence of a second JIT application runtime; future worker support must preserve this |
| Demand request routing/pause | CompilerCallbacks resolves session ID then directly invokes MutableRef.lowerBody; native SourceBodyGenerator invokes it synchronously with preparing guard, no compile threads. | Current single-thread lane. Independent compiler owner, managed worker quiescence/native gates/coalescing absent; met-b04w/com-qzpm |
| Semantic/native session lifetime | CompilerSessions registry returns value snapshots of shared cells, never recycles IDs and rejects unknown IDs; ProcessExecution roots JIT+arguments+registration through process exit, rejects a second execution. | Existing one-shot lifetime policy. Reusable teardown/restart is deferred com-yr1o, not an audit failure or a requirement to destroy process roots early |
| LLVM Module/Context handoff | Backend LlvmModule deinit disposes module then context unless consumed; transferLlvmModule and LlvmJit.add/registerDeclarations disarm the unique owner. Native consumeModule adopts both via RAII, keeps terminal failed state; lazyFailure aborts. | Existing single-owner handoff and terminal semantics. Arbitrary malformed foreign pairs/fault-injected allocation paths remain unverified |
| Target/layout agreement | Native consumeModule checks IR/triple then unconditionally replaces nonempty DataLayout; object emission compares the existing layout first. | Source-confirmed mismatch remains com-6ygf; no user-code miscompile claimed |
| Symbol/publication identity | Native generator registers dependency bodies from plew.body metadata, rejects other body definitions, checks shared metadata session/identity/size; explicit host imports and memory-libcall fallback remain separate. | Existing selected-publication mechanism. Full collision/foreign-thread/reentrant/error injection coverage remains unverified; unrestricted process lookup is not the source policy |
| Signals/process failure | native/tool.cpp run forwards INT/TERM/HUP, restores masks/handlers, reaps its child and reports exit/signal status; Compiler callbacks retain diagnostics and fail demand terminally. | Existing outer process lane. No sanitizer/signal-race execution performed; no reusable-host semantics inferred |
| Diagnostic cause/provenance | Diag CompileDiagnostic owns severity+location+message; location is unpositioned/line/file+line. Infer/Check retains tcLog failures and source owner admission rejects them; native/tool failures still print separately. | Existing warnings/stable source failure protection; original generated/instantiated causes and all returning-service boundaries partial (met-k7ks/com-lndr) |

### E. Verification Evidence and Uninspected Combinations

[Verification](../design/verification.md) requires independent validity checks
and distinguishes every gate's scope. Mid/Verify verifies structural ranges,
concrete statement/terminator types (also dead blocks), ownership and required
stage forms before executable publication. Its declaration mode separately
rejects unique Copy and admits explicit symbolic obligations. These source paths
are present; they do not certify every opcode's transfer or all malformed input.

Read fixture intent in `prepared_aggregate_source_owner`,
`recorded_binding_value_compatibility`, `mid_async_body_contract`,
`async_unique_frame` and `mid_declaration_ownership`, and inspected references to
`mid_unique_copy_verify` / `mid_copy_contract_verify`. The aggregate fixture
constructs actual successful owners, checks unprepared/foreign access and retained
snapshot stability; it is not merely a manually stamped success token. The async
body fixture checks saved logical result versus public Promise and required
owner preparation. The unique-frame fixture checks lifetime across suspension
but still uses the obsolete struct-body deinit. Migrate intent when its owning
language feature changes; this audit neither edits tests nor declares them wrong
for the older implementation they target.

No compiler, build, check, fixture, sanitizer, bootstrap or performance command
was executed. Prior fresh-baseline results remain evidence for their original
inputs, not fresh execution of this audit's adopted feature set. Test presence
alone never upgrades a Partial/Unverified entry to completed conformance.

Remaining questions are attached to explicit boundaries, not silently called bugs:

- All expression constructors/expectation/label/ownership combinations and all
  implicit-call constraint lanes: met-si6j/met-acfl/met-ia09/met-6e6k/com-uutc.
  The inspected tcCheckValue reads expressionSourceType/typeCompatibility after
  construction context; recordValueBlock/recordBlockContents are shared by
  Block/If/Match. Their existence is positive evidence, not an exhaustive proof.
- Retired parser-helper reachability and every paired macro-AST syntax/error:
  com-2p9p. Existing macro wrappers using direct parsing are not ignored.
- Every Mid opcode transfer, malicious range/ID/arena input, optimizer
  on/off negative controls and return unique-Copy bypass: com-wqd7 plus applicable
  existing Mid/verification tasks. The typed production chain remains intact.
- Collection reentry through final Ref payload deinit, retired-range traversal,
  Dictionary/Set multi-buffer commits and every allocator-failure step:
  com-zgk9; checked storage arithmetic is separately evidenced in com-p10m.
- C aggregate targets, general anonymous C callbacks/foreign threads and their
  source contracts: com-042v/com-0oxy/com-qnyl. Do not fill a deliberate design-open
  public boundary with guessed behavior to complete this audit.
- All asynchronous ownership input lanes, typed/unique outcomes and indirect
  entries: com-tn1m. Current scalar success tests do not certify those lanes.
- Cold/warm dependency/receipt/snapshot races, every sandbox/loader closure and
  host-unit graph combination: met-0139/com-9ttw/com-vy62/met-nm1w. Unimplemented
  features remain distinct from races reproduced in a supported feature.

### Reference-Domain Closure Map

This map relates the detailed paths above to every reference domain. It is a
coverage statement at the pinned input, not a live issue-status index or a
claim that every normative sentence has an executable control.

| Reference domain | Audit paths |
|---|---|
| Architecture | A session/single authority; B scoped stages; D shared runtime/driver |
| Compiler state/identity | A source/instance/header/caches; D native session lifetime |
| Sources/packages/modules | C file provenance, graph, import scope, lock/resolution/native admission |
| Syntax | C shared parser, new surfaces, deinit; E explicit paired-path limit |
| Lookup | A source selection/provided provenance; C overload identity/file scope |
| Types/evidence | A substitution/proof/environment keys; C capability surface and trusted identity |
| Body checking | A source/global/closure/binding/aggregate/completion; E contextual compatibility |
| Generics | A environment/call/evidence consumption; C capability/conditional family |
| Metaprogramming | C macro provider/form, output channel, host units and freshness |
| Mid | B stage, structure, ownership/effects; E final structural/type checks |
| Ownership/access | B async/drop/access boundaries; D destruction/reference family |
| Passes/optimization | B return-copy eligibility and shared traversal; E negative-control limits |
| Representation/ABI | B private/C ABI; D weak/destruction/LLVM boundary |
| LLVM | D resource/target/symbol/failure; B async physical responsibilities |
| Runtime | D RC, event loop/outcomes, workers and native boundary |
| Driver | D requested/check/startup/session/signals; C generated/native input closure |
| Diagnostics | D cause/owner recovery/reporting; E failure cannot certify success |
| Verification | B typed admission; E fixture scope, unexecuted gates and open controls |
| Storage/library/collection supplements | A owner payload/header; C/D exact standard declarations/APIs; B storage failure/reentry |

### Repair Boundaries and Recommended Order

1. **Independent current correctness fixes:** com-p10m (checked storage arithmetic
   and allocation failure), com-w4c2 (file-local external bindings) and the already
   known com-6ygf (ORC layout agreement). Their contracts are settled; none requires
   all new concurrency/capability APIs. Reproduce them with focused controls before
   repair; no repair is authorized by merely closing this audit.
2. **Resume the selected type-checking foundation as a closed vertical increment:**
   source owner/header/expression/binding/completion -> sealed local payload ->
   Parametric Mid/final readers, removing all-owner snapshots and competing
   interpretation for that increment. Include closure construction versus body
   success and authored provided/default/global provenance. Existing met-j9mv
   restart evidence is preserved; met-si6j's scope/gates/performance are unchanged.
3. **Close call/evidence/instance consumers on that foundation:** met-ucze,
   met-ia09, met-acfl and met-6e6k. Preserve implemented binder/proof keys and
   successful Direct/Requirement/aggregate/try paths rather than restarting them.
   A saved table, wrapper or extra verifier is not completion.
4. **Introduce adopted surface families in coherent units:** capabilities and
   summaries (met-b2la), impl-only deinit (met-2t3l), references/projections/weak
   restoration (met-op15). The API plan must account for their consumers, but
   these tasks do not all become blockers for the current type-checking parent.
5. **Keep runtime/worker requirements coupled before enabling spawn:** typed async
   ownership/outcomes, sendability/effects, fixed RC modes and managed JIT pause
   (com-tn1m/com-qzpm/met-b04w). Do not enable a surface that outruns these safety
   protocols. Shared runtime identity is a preservation requirement.
6. **Select independent admission/tooling families separately:** global readiness
   DAG (met-c58b), dependency closure (com-9ttw)/command parity (met-0139), macro
   host/framing/receipts (com-vy62), native package execution (met-nm1w), diagnostics
   and language test discovery. Their semantic dependencies matter; they are not
   one all-features implementation goal or asserted hard tk dependency edges.

Only the actual restart design/gates authorize restarting met-si6j; this ordering
is a recommendation. Optional optimizations, ARC cycle collection, general closure
move captures, public lifetimes, arbitrary user projections, general specialization
and reusable Hot Restart remain their adopted future scope.

## Outcome

The detailed static audit is complete for the recorded contract paths across all
reference domains. It goes beyond met-z0ro by tracing retained-source readers,
closure/header publication, body-key evidence, async acquisition/cleanup,
file-local lookup, root-lock selection, Buffer failure and native ownership gates.
Three new owning tasks record newly evidenced gaps (com-p10m, com-w4c2, com-9ttw);
existing tasks retain all other repairs and unknown combinations. No implementation
issue was closed and no source/runtime/test/seed/carrier was changed.

This is not exhaustive certification of all programs or a fresh compiler test run.
The explicit Unverified items above remain follow-up work; the conclusion is a
concrete repair map with preserved successful lanes, not a claim of zero bugs or
that every design feature has already been implemented.
