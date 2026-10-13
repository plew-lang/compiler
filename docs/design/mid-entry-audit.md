# Mid Operation Details and Execution-Entry Audit

**Status:** Contract supplement and retained audit map. [Mid](mid.md) owns canonical
representation and lowering; [Ownership](ownership-and-access.md),
[Passes](passes-and-optimization.md), [ABI](representation-and-abi.md),
[Backend](llvm-backend.md), [Runtime](runtime.md), and [Verification](verification.md)
own their respective invariants. Details here refine those contracts and identify
entry/probe obligations. Symbol names are audit labels, never semantic selectors.
Former meta notes reported implementation progress; carrying their maps here does
not independently certify all current paths. The chapters' focused source base
is `6fe09bc7c0e75260b3f773643921478b5020b94f`; the wider retained map is not a new
exhaustive audit at that revision. No test/performance run was performed here.

## Canonical Schema and Consumer Closure

Canonical body/block/statement/place/rvalue/terminator rows and payloads contain
scalar fields and typed ranges only. Projection, operand, aggregate-element,
call-argument, switch-case, statement, local, scope and block relations have
explicit pools. Nodes are one-based with zero absent; ranges are zero-based
contiguous pool intervals. Required fields include panic/return values, selected
template/resolved call identity and independent receiver, cast source/target terms,
and aggregate/projection/operand ranges. Source types cannot use zero as a
wildcard. Draft arrays exist only during construction; publication freezes once.

Conversion/conformance proofs freeze together with bodies into an immutable DAG.
A canonical node stores the proof ID rather than an owned recursive proof enum.
Children are published before their parents; verification checks child-ID order,
bounds and payload ranges to reject cycles/missing children. Identity,
ExistentialBox, ArrayRepack and EnumRepack remain selected proofs, not choices for
Mid/LLVM to reconstruct. The latter preserves every variant/physical-payload field
in declaration order and its recursively selected child conversion.

Canonical Instantiate, Access and Drop append snapshots directly. Remap every
edge using actual expansion widths, not old statement counts. No thawed body,
cleanup-block owned-array backlog, AST/type-cache fallback or restored draft
proof is the normal rewrite protocol. Verify/LLVM read immutable body/node IDs.
Constant literal token bytes may be retained for physical decoding; ExprId is
provenance, not a carrier asking the backend to reevaluate source.

Rejected substitutes include passing statements by pointer to avoid copies,
suppressing ARC in selected matches/compiler modes, running only with tracing,
or replacing owned nested arrays with ad hoc shared references. They hide the
row-read ownership problem or add identity/lifetime questions. Scalar typed pools
make relation ownership explicit; this does not claim ownership-free cost for all
compiler state or that another language must use the same storage layout.

Declaration-stage symbolic snapshots can retain type recipes and TryBranch/
ForBranch identities with both successors. ScopeExit/EndBinding consumption uses
the same ownership dataflow, not a new AST walk. Unexpanded Access retains an
accessOwner and preparedInputs range from that occurrence, including published
key/reference homes. Declaration checking validates their lifetime without
claiming getter/setter resolution, writeback or exclusivity is complete;
executable verification still rejects unresolved Access. Frozen global-address
recipes retain declaration/type/mutability without reopening global storage rows.

## CFG Operations and Results

The plain non-SSA terminator set is Goto, Switch, Return, Unreachable, Abort, Call
and Suspend. Open is construction-only. Switch retains case order, duplicate
edges and otherwise. Call has selected resolution, separate optional receiver,
arguments, destination and normal target; panic has no unwind edge. A selected
noncontinuing call closes its nominal continuation with Unreachable and publishes
no usable result; already closed argument evaluation is not closed again.
Suspend stores state, resume target, ExprId, evaluated promise and destination.
Its input is a Read borrow of an owned Promise home; resumption independently
initializes the result, without consuming that input owner. FinalAwaitResolution
selects and validates the concrete input/result relationship.

Drop is a statement because it has no normal branching/unwind contract. Return,
break, continue, try propagation and match exits become ordinary edges/terminators.
Side tables retain source scopes/spans; flat CFG does not erase lexical cleanup.
Structured IR plus read-only CFG overlay could be correct, but one inspectable
flat substrate avoids duplicate representations and implicit exit-state plumbing.
The extra representation/pass cost remains real, including in a greenfield
compiler; it is not eliminated by rejecting a migration-only cost comparison.
Future borrow/region analyses can build on places/dataflow, but no particular NLL
implementation is promised by those seams.

Builder results distinguish Value(payload), NoContinuation and Error. Only Value
supplies a receiver, argument, operand or index local. Pure missing-place lookup
is distinct from evaluating a place component that exits/fails. Sequential work
propagates closure; sibling branches restore their evaluation scope/memo and
still build valid continuations. A procedure-to-expression boundary publishes a
result operand only after success with a normal continuation.

Source divergence remains governed by [the adopted decision](decisions/divergence.md).
Old examples allowing direct use of wholly diverging initializer/give operands
are not positive fixtures. Build realizes accepted recorded flow: no result-store,
StorageBoundary, capture-cell initialization, post-call writeback or join edge
exists on a closed path. Reserved result slots alone are not values or a demand
for an ungenerated call's concrete result. Warned analytical-loop regions can
contribute static typing without creating executable edges. A retained ABI type
annotation does not make NoNormalValue a usable result or erase call typing.

Conditional whole-value move is adopted under affine ownership with automatic
destruction of a retained owner. Prohibiting all conditional consumption would
simplify flags but reject useful handoff code; it is not logically impossible
for an affine language to choose that restriction. Accessibility-cliff cleanup
rather than lexical flag retention or arbitrary last-use destruction follows the
adopted lifetime policy. Partial aggregate moves remain outside v1.

## Typed Places, Match and Storage

Field projections retain selected slot, post-projection type and boxing; every
projection type is grounded with the body environment. Deref is its own projection
(tag 3), not an encoded field/index; index/indexLocal are zero and its type term
nonzero. Reference-owner lifetime and pointee access rights remain different.

Canonical Borrow accessPlace identifies the reserved original storage separately
from get-modify-set ABI temporary storage (zero means operand.place).
Instantiation/traversal/verification preserve it; reference roots use one owned
MutableRef temporary, retained through call and reverse writeback. borrowsStorage
preserves source borrowing provenance separately from ordinary guaranteed-ABI
Borrow tags, so tag equality alone cannot decide source conflicts.

Global roots carry declaration target, parametric type and mutability from one
SemanticGlobalAddress publication, not name, initialization-array position or
LLVM symbol. Instantiate grounds the term without replacing the target. Global
is not a local owner: Copy acquires a share, Borrow permits the selected access,
Move is invalid, and ordinary ScopeExit/cliff flags do not destroy globals.
InitializeGlobal transfers a fresh initializer owner once into an unprojected
matching global root in its synthetic body, including immutable globals. It is
neither fresh local Assign nor replacement Overwrite and receives no prior Drop.
Initialization order is the frontend dependency order. Runtime replacement uses
an explicit permitted Drop/Overwrite pair rather than implicit destruction.

Inout locals contain a valid caller/environment-owned value, but are not owners
at entry. isParameter alone maps source ABI positions; captures are not fake
parameters. A borrowed local's Drop is legal only with the required adjacent
same-place Overwrite; ScopeExit, ConditionalDrop, ownership Move and cell-owner
release cannot steal that storage. Deref replacement pins the evaluated MutableRef
in an owned normal temporary through RHS evaluation and emits pointee Drop plus
Overwrite; it does not consume the reference owner. A standalone pointee Drop or
replacement through a read-only Ref is invalid.

SemanticMatch freezes scrutinee term, enum/struct kind, arm reachability, variants,
field slots/types, binding identities and boxing. FinalMatchResolution grounds
these facts; Mid does not recompute coverage or search names. Enum dispatch reads
the tag and switches; an irrefutable struct pattern takes its selected arm.
Nonplace scrutinees evaluate once in a scope lasting through the arm.
Nonconsuming struct/enum bindings acquire owned copies, including boxed payload
copies, so scrutinee replacement cannot invalidate them. Borrowed payload
optimization needs an owner-preservation proof covering overwrite/move/write
loans, not only nested lexical scopes. Consuming DestructureEnum transfers the
whole enum to all payload destinations in declaration order; no partial source
survives. Discards use normal Drop and capture initialization normal Move. A final
boxed owner can transfer its payload and free the cell; shared storage must acquire
independent ownership. Backend layout glue never chooses source destruction order.

The [binding-end contract](ownership-and-access.md#lifetime-boundaries-and-drop-elaboration) defines EndBinding state transitions and exactly-once cleanup. Rewrites store the actual generated statement count after erasing such markers.

## Evaluation Homes and Call Materialization

Call result homes belong to the parent evaluation scope; receiver and argument
retention belongs to a child scope. Normal continuation finishes Access writeback/
borrows, then drops those child temporaries. Default and synthesized forwarding
calls obey the same rule. Return first transfers into an ABI result home outside
source scopes, cleans source owners, then ReturnValue moves that home to the caller.
No backend index exception excludes a source return variable from cleanup.

Child Copy/Move values are captured at their evaluation point if later evaluation
can change storage. The retained implementation subset can elide that home across
literal/identifier/pure physical-field reads; calls, indices, moves, conversions,
control flow and unknown forms retain it. Deferred getters also require retention.
Already evaluated anonymous homes and entire immutable caller-guaranteed ordinary
synchronous value parameters can be reused under their contract. Receivers, owned
parameters, inout/borrow, shared capture cells and projections are not covered by
that parameter exception. This is an implementation subset, not a general purity
classification. Short-circuit calls consume the left condition before RHS work.

A semantic ExprId/CallSiteKey is not a runtime evaluation identity. Consumer-local
memoization is reset for children/statements and sibling contexts; children return
only completed result homes to the restored parent memo. Repeated defaults sharing
a source ID still evaluate independently. Synthetic interpolation Expr.Sequence
uses a result home without creating a new source complete-expression/lexical
scope; expressionSequence/completeEvaluation boundary information prevents its
steps from prematurely dropping retained receiver/Options/builder values. A real
Expr.Block keeps normal lexical and complete-expression cleanup and give exits.
Try failure cleans unfinished generated builders under those same rules.

Final calls retain receiver None/Borrow/Inout/Move and argument Borrow/Inout/Move.
Normal value inputs are caller-guaranteed +0, not implicit consuming ownership.
A nonidentity argument conversion first produces an owned temporary then lends
it for the call; a consuming ABI receives Move of an independently copied source
temporary when appropriate, never Move of the original copyable binding. Call
materialization takes caller-supplied body-relative continuation/cleanup targets;
the caller owns original-edge remapping and registering returned ranges/locals.

Unique results remain Move values; selected read ABI can normalize an owned
anonymous whole-result home to borrowing it. This excludes named bindings,
parameters, capture cells, result homes and projected/partial values and preserves
existing full-expression cleanup. Consumed owners cannot be revived by Read.
Read-only indexed uses are ordinary getter calls and need no mutable writeback
recipe. Mutable access owns the saved base/key/projection recipe and selected
parent/setter; names or method spellings cannot decide writeback.

Identity conversion preserves ReturnBoundary exprId/targetTerm. ViewBoundary
(tag 23) uses frozen applied terms and an evaluated operand; instantiation removes
only permitted outer views, checks nominal identity and retains views inside type
arguments, producing IdentityRetag. Borrow/inout/unexpanded Access cannot be turned
into owned view temporaries. Place views require their own storage contract. The retained executable-type
checker admits explicit retag only at outer-view boundaries, the immediate
newtype boundary, and its existing floating cast cases. This is the documented
checker/operation subset, not permission to erase arbitrary nested nominal or
view identity or an independent expansion of the language's cast rules.

Convert uses its proof DAG directly. Copy repacks acquire an independent result
from borrowed input; Move into an existential box transfers ownership. Move with
structural Array/Enum repack is only a future allowUnique design obligation: it
must dispose the consumed source after reading and leave only the fresh destination.
Current copyable generic restrictions do not make that path an implementation/test
requirement. Nonidentity proofs are never thawed or selected again in LLVM.

Canonical integer magnitude comes from literal spelling while its selected type
comes from the retained term. An integer-spelled float constructs a floating
constant and applies floating negation; it must not pass a float type to
LLVMConstInt. Canonical and draft construction use the same physical constant
builder without reselecting a type from its suffix.

## Closures and Synthetic Ownership Bodies

SemanticClosure freezes synthetic bodyKey, function type, navigation-only body
anchor, parameter identities/types/passing, result contract and source-order
captures. Register the synthetic semantic owner before recording its calls.
Canonical closureBodies uniquely maps bodyKey to parametric body IDs; an instance
uses that body and its lexical InstanceEnvironment, not the cross product of all
parent instances and closure syntax. JIT parent registration alone proves nothing
about closure preparation. Source parameters exclude the physical environment
pointer lane.

ValueCopy captures independently own values, including enum/generic/recursive
payloads under ordinary type/layout/glue. Mutable CellBorrow captures share the
one capture cell selected by bindingTarget; mutability changes capture mode,
not the set of otherwise valid value types. Unique capture restrictions remain
specification-owned. Body entry borrows environment values or refers to the same
mutable cell; escaping values acquire ordinary copies. Creating a closure is not
invoking it, and closure dependency closure includes ownership of the function
value even when it is immediately discarded or bypasses an explicit local.

InitializeCaptureCell creates a cell at binding initialization. Drop/Overwrite
replace its contents without releasing the cell owner. Lexical exit emits
ReleaseCaptureCell to lose that binding's share; MakeClosure retains the selected
cell. LLVM cannot rediscover cell homes from names or local stacks.
ClosureSignature.environmentDropBodyId selects BodyOrigin.ClosureEnvironmentDrop:
frozen captures are owned explicit inputs, ScopeExit elaborates reverse capture
cleanup, and shared cells use ReleaseCaptureCell. No closure AST walk is involved.
LLVM loads capture fields physically and invokes the verified synthetic body;
declaration registration is separate and the same drop body may be shared.

Existential witness adapters retain selected proof, public signature, passing,
concrete callee and result-conversion proof. Their synthetic Mid calls return into
owned homes then move/repack/box, ScopeExit and ReturnValue through common passes.
Any.buildAnyThunk declares/enqueues only; emitExistentialWitnesses emits each body
in its own local environment. Erased-self loads and symbol placement remain physical
glue. Copy thunks load/retain the concrete value and allocate/store a new box;
drop thunks release the concrete value, while emitAnyRelease frees the box itself.
These box operations implement Mid ownership, not a new source evaluator.

## Ownership Analysis and Typed Stage Entries

Ownership/accessibility use canonical rows with FIFO worklist changes from entry;
pending clears before processing so self-loops can reenlist. A MidOwnershipAnalysis
snapshot returns incoming states and reachability together. It is analysis-local,
not a successful-stage token or mutation-stable cache. Recompute for changed
snapshots and applicable verification stages. The independent verifier explores
owner/flag pairs rather than trusting the Drop plan; entry initialization uses
intersection over predecessors and a backedge cannot justify the first read.

Retained implementation cost techniques include body-local predecessor lists,
shared exit-state rows, packed 2-bit MaybeOwned enumeration excluding padding,
block ranges into a local-ID candidate pool in original local order, and inspecting
predecessors only for MaybeOwned plus Unavailable. Empty candidate pools can reuse
unchanged ownership fixed points; added cliff consumes require reanalysis. None
changes flag necessity, destruction order, entry state or reachable-path semantics.
Drop/GlobalAccessGraph/Access counting take only their needed canonical arena;
required type/effect consumers also receive their explicit completed contracts.
Reducing Comp snapshots is not a compiler-specific ARC exemption.

MidParametricBody.input admits unverified input. Successful transitions are
MidInstantiatedBody.instantiate → MidAccessResolvedBody.elaborate → optional
optimizedReturns (same stage) → MidDropElaboratedBody.elaborate →
MidExecutableBody.verify. Completed wrappers have no public manufacturing factory.
Low-level InvalidTarget/VerificationFailed results produce no stronger token.
MidExecutableBody.prepare is the shared sequence, not a builder/ABI/frame driver.
Wrappers certify one unchanged snapshot in the same arena/domain, not arbitrary
arena mutations or cross-arena IDs.

DeclarationProgram.prepareDeclarationProgram checks symbolic ownership/local and
global-access obligations using caller-owned MidFunctionTemplates and returns
DeclarationAccessAnalysis or DeclarationProgramError. It registers no executable
body/destruction/LLVM and unresolved obligations prevent treating it as whole-check
success. AOT PreparedProgram uses it then shares templates for executable work.
Gen target selection belongs to its caller, not an unverified success branch in
declaration checking. PreparedProgram.prepare handles the selected worklist,
ambient plan and global conflicts; it is not proof that all unused bodies passed.
Mid/Diagnostics owns stage error translation without an LLVM context.

MidExecutableRequests caches per-body success/failure in the same session/templates;
signature-not-ready rejects admission before pass-failure caching. It does not
silently prepare other instances or grant effect-closure publication permission.
Backend-local MidLlvmPrepared.Ready additionally records that exact immutable
body's applicability and argument count; emission consumes it without duplicate
verification/preflight or reusing it for a changed body.

FinalDestruction.isUnique prohibits Copy independently of needsRelease or a local
cache. Executable verification rejects missing/unready contracts for Copy, Drop,
ConditionalDrop, payload copies and boxed destructure outputs as applicable.
Conversion children including identity repack leaves need their own ownership
contracts. Mid/Types checks local/global/projection, initialization/replacement,
returns, casts/conversions, aggregates/captures, calls and logical body results,
including dead blocks, using retained facts, not width/name/AST guesses. Identical
IDs still require valid closed types. Receiver outer-view handling cannot erase
nominal identity or type-argument views. This is not a complete arbitrary-mutation
validator: every aggregate-layout correspondence, numeric cast width/kind and
Suspend payload remains a coverage question, also constrained by instantiation,
ownership checks and backend preflight.

## Async and Machine Boundaries

Frame planning reads the instantiated, access/drop-elaborated, verified CFG and
computes backward liveness to fixed point. Drop/ConditionalDrop/ReleaseCaptureCell
are uses. Suspend excludes its result definition and includes the promise Read;
unreachable suspends do not add frame slots. Projected writes use root/index
rather than define the whole root; writing cell content uses the cell pointer.
Borrowed-local dependencies transitively include owners, conservatively unioned
across definitions. Sparse empty dependency rows do not truncate closure. The
analysis adds no retain or new lifetime rule.

LLVM maps saved locals to frame slots; entry-to-resume arguments also use the
frame. Resume reloads the awaited result from the saved Promise instead of using
pre-suspend SSA values. Shared completion cells own waiter lists; resolution
moves each continuation once to ready and frees its list node. Source Drop comes
from Mid, then completion notification, activation Promise release and frame free
follow runtime protocols. The runtime chapter's scalar payload/one-shot-checking
limitations remain; this contract does not certify arbitrary payload support.

ABI/private byval and zero-size rules remain in the ABI chapter. Alloca homes
belong to the actual generated function entry; stores stay at source evaluation
positions. Zero-sized ordinary physical loads/stores use centralized helpers,
exclude opaque/volatile/atomic semantics, and do not erase evaluation, identity,
access or destruction. Concrete generic-instance registration slots, not defining
struct IDs, key retain/drop witnesses so nested Box instances cannot collapse.

## Module and Preparation Dependencies

Mid is a root compiler module, not a frontend submodule. Its Ir, Build, Place,
Instantiate, Access, Drop, Verify and Prepare responsibilities preserve a
one-direction dependency from semantic facts to Mid to Backend. Build can
navigate source structure and consume semantic queries; pure canonical dataflow
accepts its arena, while operations needing concrete type/destruction facts receive
those explicit contracts. This is not an assertion that every existing function
has already eliminated Comp parameters. Required legacy dependence must not be
used to reopen name/conformance selection. The main architecture chapter owns
the actual source-module DAG and current audit.

## Execution Entry Map

Every supported source execution body, including macro execution programs,
generated Plew, resolver/driver, std and Syntax dependencies, uses Mid. Input AST
passed as data to a macro is not an execution body. External runtime C remains
external code; physical helpers are audited separately from semantic bodies.

| Entry / audit symbol | Responsibility and required evidence |
|---|---|
| Entry.genLlvmMain / main | Sync source Mid plus startup ABI/global-init glue |
| ProvidedFns / gf*, pf* | Free/generic/provided bodies through Any.genLlvmFuncBody |
| GenMethods.emitOneGenMethod / gm* | Methods, factories, operators, defaults, deinit through common preparation |
| Entry.genLlvmInitGlobals / plew_init_globals | Synthetic ordered InitializeGlobal body |
| Closures.emitClosures / __closure* | Registered ClosureSignature BodyInstance and capture inputs |
| Closures.emitClosureEnvironmentDrops / pwclodrop* | Verified synthetic environment destruction |
| MidAsync.genLlvmMidAsyncResume / __af*_resume | Verified source Suspend/resume body |
| Async.genLlvmAsyncFunc / async pf*, main | Physical frame/Promise/startup glue, matched to resume ID |
| Any.emitExistentialWitnesses / pfvt* | Verified selected witness forwarding/conversion body |
| Any.buildAnyCopyThunk, buildAnyDropThunk / pfvtcopy*, pfvtdrop* | Separate concrete-value/physical-box ownership glue |
| Arrays / pwretain* | FinalDestruction-selected concrete struct copy/retain glue |
| Arrays.rawbufHeaderValue / pw_buffer_count, pw_buffer_capacity | Null-safe header reading, not source-body success |
| Arrays.boundsCheckFunction / pw_bounds | Selected bounds/panic physical expansion |
| Arith.checkedArithmeticFunction / pw_checked_* | Selected checked overflow behavior across widths/signs |
| StmtDeinit / pwdrop* | Concrete destruction glue; user deinit selected by stored body ID |
| Enums / pwenumrel*, pwenumret* | Frozen active-payload layout/ownership glue |
| CallBasic, CallExt, StringOps.getOrDeclare | External declarations/references; external body excluded |

The retained glue map uses emitRetainWitnessWalk/emitDropWitnessWalk and
emitEnumOwnership with FinalDestruction fields/boxing/release/variants.
FinalOwnershipClass/finalNeedsRelease read completed contracts; destruction-index
completion may match existing type identity, not choose missing destruction again.
These are source-boundary obligations, separate from counting generated definitions.

## Audit Inputs, Probes and Limits

[scripts/diagnostics/measure-mid-coverage.py](../../scripts/diagnostics/measure-mid-coverage.py)
records inputs, carrier hash, source state, manifest/lock, exits, fallback lines and
LLVM definitions (`--output tmp/mid-migration/<label>`). `--emit-mid-coverage`
records `mid-body symbol=… canonical=…` on completed prepared-body emission.
`--require-mid` enforces its selected corpus; a gate's own abort is not a successful
rejection. Compare every LLVM definition with its body/glue category and unique
Mid emission evidence, not merely zero fallback counts. Coverage instrumentation
must not change generated LLVM. Async non-main entry matches its same-ID resume;
async main glue adds global init/frame/Promise/loop, not a hidden source interpreter.

Observe normal run, panic, part, compiler self-input, standalone resolve/_.pw,
Plew tools, gen harness/generated app, dynamic dependency fixtures and auxiliary
execution gates. Std/Syntax inclusion as dependencies is not every public API.
Source-structure checks/mock compilers are not executable-body denominator entries;
reject acceptance soundness is independently tested by the ordinary suite.

Focused guards/fixtures retained for maintenance (existence is not a newly passed
run):

- [canonical production gate](../../tests/compiler/codegen/test-mid-canonical-production.sh): prevent draft consumers/fallback in production entry paths.
- [existential bodies](../../tests/compiler/codegen/test-existential-mid-bodies.py): one-to-one member witness/Mid definitions for Self results, heap Array/Optional, inout and Unit; copy/drop vtable glue excluded.
- [closure environment bodies](../../tests/compiler/codegen/test-closure-environment-mid.py): heap values, cells and multiple captures; `mid_closure_environment_drop` additionally checks escape/alias/final release order.
- [value ABI](../../tests/compiler/codegen/test-value-abi.py): field shrinking plus callback/inout mutation and escaping closure snapshot behavior.
- [static view boundary](../../tests/fixtures/run/mid_static_view_boundary.pw): valid execution and malformed-boundary rejection. The old note also named
  `test-mid-value-views.sh`, which is absent from the current tree; that historical
  name is not evidence of an available or successful gate.
- `mid_type_consistency`: typed valid controls and mismatches through production checking.

The common LLVM preprocessing/ASan boundary belongs to the backend chapter:
SROA/early CSE/InstCombine prepare field simplification before argument promotion,
then ordinary module O1 completes transformations before ASan. Bounded repeated
InstCombine (retained implementation cap 8) is not permission to omit a required
convergence check. Partially promoted remaining byval can add copies if instrumented
too early. This sequence does not justify passing unprotected caller storage.

Current [copy-transfer audit](../issues/com-wqd7.md),
[continuation-state investigation](../issues/com-gyup.md),
[divergence migration](../issues/com-tijs.md), and optional optimization issues own
unclosed work; the meta worklog owns paused implementation/restart conditions.
Future sendability/spawn requires capture/transitive-call/implicit destruction
closure and allocation-mode analysis before sharing/publication, as described by
the runtime and ownership chapters. Existing synchronous checks or this entry map
do not prove that extension. No complete API/combination coverage is claimed.
