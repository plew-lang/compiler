# Frontend Facts, Admission, and Consumer Handoffs

**Status:** Detailed contract supplement. Logical guarantees below refine the
[session](compiler-state.md), [lookup](name-lookup.md), [type/evidence](types-and-evidence.md),
[body checking](body-checking.md), [instantiation](generics.md),
[ABI](representation-and-abi.md), and [driver](driver-and-execution.md) chapters.
They are not a declaration that every current implementation path satisfies them.
Physical checked-body storage remains unresolved; private arrays or successful
focused probes do not settle that choice or establish whole-owner sealing.

## 1. Guarantees and Request Ownership

Preparation of a lexical body uses its authored source owner, including provided
implementations. Requests retain success or failure in the same session, restore
caller cursor/scratch state on every exit, and consume registered signatures
without recursively preparing callee bodies. A closed call template proves
selection, not successful record, generic, declaration, iteration, or call-bound
checking. Unrequested closures cannot inherit a checked state.

Declaration preparation checks declaration-owned uses and registers bodies;
body requests check local type uses, call visibility, and defaults in their
lexical environment. Generated calls do not create invented source imports.
A `DefaultGeneratorOrigin` identifies the authored declaration and parameter or
field slot. Its request checks self-containment, suspend restrictions, literals,
and compatibility; whole check requests all generators. Generator mode is a
separate selected program, not run's acceptance policy.

A checked declaration body proves canonical Mid and declaration-local ownership
and call borrowing. Static global-effect roots additionally follow static calls
and closed destruction dependencies. Graph-node identity is distinct from
source declaration identity; recursive edges converge on registered nodes.
Closure creation does not execute its body: closures have separate roots.
Symbolic destruction, dynamic calls, and conversions retain obligations. Neither
local success nor a root-analysis result grants execution permission.

A compiler session owns its admitted inputs and request caches. Whole-target
success consumes the same session only after whole frontend and declaration
Mid local/global checks. The resulting checked-program capability cannot be
manufactured by a public factory, injected rows, or mutable arena access. Concrete
preparation consumes that artifact without dropping its unresolved effects.
Generation cannot publish whole-application success. Partial-to-whole extension
reuses valid results without repeating initializer evaluation or blessing failed
partial state. The driver owns final execution publication, not row presence.

## 2. Source Fact Identity and States

Semantic expression types contain complete terms, value shape, and contextual
literal information. Diagnostic spelling is not identity. Source signatures
retain lexical parameter terms separately from public dispatch signatures:
newtype inheritance and provided bodies must not overwrite the authored body's
`Self`. Annotation traversal resolves nested binders, `Self`, associated types,
and views in the declaration environment.

A source-expression key includes its lexical body, source domain, and expression
identity. A type recipe (`Term`, `CallResult`, `Project`, optional payload) is not
an interned type-term ID. Ground IDs cannot serve as source-fact keys. A call site
additionally retains complete source span, origin serial, and slot; expression
IDs are navigation aids, and zero can be a valid expression ID.

Expression state distinguishes Unrecorded, Pending, Value, Unit, and
NoNormalValue. Zero alone cannot distinguish missing from Unit. A known Unit
producer is identified by its completed signature or recorded fact; `Promise[()]`
uses a real closed empty-record payload, not a missing generic argument. Unit
closedness does not establish that a particular value position accepts it.

A saved type reader grounds only the same successful owner's fact under an
explicit body environment. It cannot recover from an identifier, field, index,
AST, parameter ABI, or another argument's type. Missing resolution is failure,
not an invitation to infer again. The array/record/closure context rules in
Body Checking apply before publication; full compatibility still checks all
nominal arguments, including phantom arguments. Cast context affects only the
permitted direct unsuffixed literal and immediate newtype boundary, not arbitrary
expressions, explicit suffixes, Bool, or recursively invented casts.

Sparse pending-expression obligations close before successful owner publication.
An exempt conditional index-set capability root is not an exemption for its
executed children. Global initializers use an explicit declaration target:
a shared synthetic function sentinel cannot prove success for every global.

## 3. Declaration and Lookup Stores

Registration owns declaration rows and their indexes together. Function,
struct, enum, type, and bound additions update the corresponding indexes at the
same boundary; value copying must copy rows and indexes consistently. Readers
must not alter visibility, arity, aliases, or candidate order.

The current name-index scheme uses row ID plus one, zero for absence, and current
row count as a transient missing-reader result. Do not cache that count across
appends. Function indexes cover generated rows too, separately from the source
callable set. Generic struct/enum lookup must seek the first matching generic
row rather than filter only the first same-named row. Additional predicates
continue through same-named candidates instead of stopping at the first failure.

A global type-parameter-spelling query excludes registered nongeneric struct
and enum names, not generic declarations, traits, or newtypes. It is not lexical
binder resolution, type identity, visibility, or conformance. Bare-name indexes
exclude arguments, views, existential/sendable decoration; their result is not
a type-equality decision. Scalar predicates need not materialize aggregate rows.

Resolved nominal declaration identity is authoritative: failure to find it may
not fall back to another same-spelled declaration. Parameters, projections,
structural records, and existentials are not nominal-name queries. Current
source-offset carriers are implementation choices, not universal identity rules.
Import origin retains module and local-name identity plus source/local spans;
parts inherit root provenance. Public export surface and authored module remain
distinct. Reverse declaration lookup preserves category and identity rather
than accepting a same-named row of another kind.

Type registration co-registers terms, child pools, and structural summaries.
Closedness and associated-projection presence account for unknown forward
children; unknown is not false. Projection presence is distinct from parameter
presence. Raw view-selector set comparison and resolved view-source comparison
serve different purposes; ignoring an outer view must not erase nested views.

Read-only conformance inputs borrow ranges from the owning session only for the
request; retained outputs own their data. Copying the whole mutable pool is not
the intended query protocol. Trait-cycle analysis owns a per-request normalized
graph with stable node/edge provenance and deterministic first diagnostics.
SCC ownership is not by itself proof of type-cycle validity: symbolic scopes,
substitution paths, and occurs checks remain required.

## 4. Calls: Selection, Operands, and Defaults

Direct, static, dynamic, protocol, and operator calls retain the same logical
facts: selection identity, instantiated source signature, operand sources,
labels/modes, parameter order, source evaluation order, result recipe, view
boundary, conversions, and bound evidence. Final result projection (identity,
ordering test, Bool negation) is separate from the underlying ABI result.
Unary results come from the selected signature, not the operand type. Core
operator identity is resolved identity, not spelling.

Short-circuit operators retain control flow rather than becoming eager calls or
prior-call-result operands. Canonical Bool checks and conditional RHS access
survive nested blocks/branches. Call selection may be cached as uncomputed,
no-static-selection, or selected; a missing row count is not stable negative
selection. Once selected, a result recipe is immutable across refinement and
omitted arguments. Readers do not rerun `where` selection for a result.

Explicit arguments acquire context and freeze before publication, including
permitted parent result hints. Empty ambient cursor state cannot repair a failed
read. Receiver selection context and receiver evaluation dependency are separate.
The receiver is evaluated once as the appropriate value/place/read/inout/move;
an rvalue does not silently become a mutable named place.

Explicit arguments execute in written order, followed by omitted defaults in
parameter declaration order. ABI parameter order is a separate mapping. Each
omitted occurrence evaluates its generator; sharing authored generator identity
is not caching its value. Its environment includes complete parameter mappings,
including phantom binders. Temporary destruction ends at the generator call's
scope rather than extending to the outer call without an ownership reason.
Provided placement copies share a generator by the authored
`semanticBodyOwner` declaration and parameter slot. Distinct authored declarations
are not merged merely because they share a `ParamRange`. Additional receiver
binders in placement copies must not be removed by positional truncation:
project type arguments onto the generated function's lexical ParamIds. The shared
artifact is the parametric declaration; each caller's instance/proof supplies
concrete bindings and each occurrence still evaluates independently.

An index operation retains explicit ordinary/read/write origin, including
synthesized setters; method names cannot reconstruct this classification.
Lexical checking uses the source owner, not a current cursor or concrete body
function. Selected conformance subjects and trait owners are required facts,
not zero-type/name guesses.

## 5. Constraint and Proof Admission

A trait-instance identity includes owner and positional arguments; associated
outputs are equations to check, not an alternate owner key. An owner name alone
does not establish arity or visibility. Selected extension shadowing is decided
before output-equation checking; failed outputs cannot trigger bare fallback.
Multiple paths to the same terminal witness are not automatically different
implementations. Provided-body requirements remain independently checked.
Proof categories are extensible; concrete, bound-path, and trait-self evidence
must not be reduced to an obsolete fixed three-case classification.

Saved proofs retain subject, constraint, source-view set, explicit selector,
visibility/declaration scope, and static/runtime distinction. Child proofs are
published before parents with contiguous owned child ranges and immutable IDs.
Representation decoders reconstruct values only; they do not admit evidence or
publish successful owners.

Admission checks the complete path: each edge's subject/receiver, trait owner and
arguments, substitution, terminal witness, associated output, and prerequisite
proof. Conditional proof cycles and lexical scope must be checked. Projecting an
output from a bound path is not full integrity validation. Missing path evidence
cannot be repaired by selecting conformance again.

Assumption authority belongs to an exact declaration scope. Function and method
receiver assumptions normalize closure/provided ownership; an associated-type
prerequisite and its cycles are checked with its saved clauses. A function scope
cannot accept a declaration-conformance or trait-subject assumption merely
because the referenced declaration appears among its dependencies.

Before interpreting proof-dependent signatures, call admission validates the
selected function and proof authority. Ordinary direct calls may legitimately
have no conformance proof; provided/static-required routes cannot use that as a
missing-proof escape. Trait-self evidence identifies canonical lexical `Self`,
exact trait arguments, and its scope. Origin trait, provided trait, and source
trait roles are not interchangeable.

A shared source-call signature distinguishes ordinary declaration environments
from trait-instance and method-binder environments. Direct/static requirement
and provided calls use the same operand, label, inout, conversion, and evidence
checks. They project saved trait arguments and associated outputs rather than
selecting another witness. Complete method-type-argument mapping includes every
lexical declaration parameter; zero/missing arity is not Unit. Closedness tests
must not register types or use ambient selection.

Selected call constraints retain ordered conditions, substitution snapshots,
canonical owner, and complete child proofs at the selection frontier. A reader
checks condition count, subject, trait arguments, outputs, scope, and ownership,
including an empty signature's existing plan. Empty conditions are a signature
schema, not proof that an owner with no plan succeeded. Global membership is
indexed by initializer declaration, not a shared sentinel.

Concrete instantiation consumes recorded child proofs in the caller's explicit
environment, then admits them against the callee's grounded signature. It does
not reconstruct obligations from proofs or re-search `where`. Missing, Deferred,
and Ready are different states; only Ready grants executable evidence. A
DeclarationObligation marked Complete has evaluated its obligations and queued
children, not necessarily checked every child's body. Deferred is legal only for
validated lexical dependencies; foreign scopes, missing proofs, and concrete
Deferred states fail.

Conditional projection normalization saves the projection, prerequisite proof,
and output equation in its witness plan. Readers check receiver/trait/output and
scope, then replay the saved equation structurally. Instantiation grounds its
saved prerequisite. Missing output is unknown, not Unit; missing equations cannot
be invented by a new selection.

## 6. Conversion and Existential Handoffs

Every nonidentity conversion carries a typed proof with exact source/target
endpoints and the correct site and successful owner. Identity also requires
compatible endpoints; absence of a plan is not implicit identity. Conversions
through arrays or enum payloads preserve child proofs. Phantom-type compatibility
proof and physical payload conversion are distinct plans.

Argument source type is saved before conversion in its selected context. Final
argument preparation grounds that type once; AST literals and parameter ABI may
not redetermine it. Storage conversions are keyed by body and destination
statement, not only a reused source expression. Place provenance remains the
original access, separate from any ABI temporary. Operator-LHS dispatch view
adjustment is a specific role, not general implicit view conversion.

Existential requirements retain public parameter/result terms and modes before
requesting concrete bodies. A witness plan converts concrete entries to erased
signatures, including necessary reboxing. `Self` inputs normalize through the
trait binder and recursive children. An unsupported member and an invalid
existential formation are different diagnostics.

Final existential resolution retains source/target, proof, ordered slot
signatures, conversions, and body-instance identities. Vtable identity belongs
to a descriptor, not a name hash. An existential adapter has its own body origin;
its source function is provenance, not permission to traverse a source-candidate
chain. Erased receiver binding supplies a physical parameter, not a new source
body type. A nondispatchable slot is explicit, distinct from missing preparation.

Retagging the same interface to erase sendability keeps a conversion plan; it is
not identity across changed types or fresh boxing. Borrowed leaves retain once
when ownership requires it. Box evidence validates the exact target trait,
positional arguments, associated outputs, and source subject including the
permitted outer-view rule. An empty trait does not excuse absent evidence.

## 7. Construction, Locals, and Source Control

Construction retains explicit nominal identity and factory/variant kind, even
with no type arguments. Expected construction arguments come only from the same
nominal owner and arity; explicit arguments and views cannot be overwritten.
No field-set guess chooses a nominal type. Memberwise default expansion occurs
after selection and records written versus synthesized fields. Anonymous records
are structural and do not receive nominal memberwise defaults.
A default memberwise factory has a callable signature even without an executable
`Func`. Declaration conflict checking compares the signature derived from field
types/defaults with custom anonymous factories through the common
`callableFormsMayOverlap` operation, unifying receiver and arguments in one
shared environment. Check unused declarations too; call-site ambiguity alone
cannot replace this declaration check.

Structural records use sorted labels and complete field terms; a layout ID or
synthetic nominal name is not semantic authority. Grounding a record need not
register physical layout. Reachability later visits grounded record children and
registers the necessary shape; colliding names cannot share incompatible ABI.
Field/arrow access retains selected slot and type rather than guessing slot zero.

Lowering preserves syntax, origins, and argument ranges; semantic selection and
context propagation belong to the checker. In particular, the older attempt to
choose a non-generic callee by name/labels during Lower is not an additional
selection authority. Dictionary/range source forms must not introduce independent
context or type decisions. Range iteration uses the common selected iteration
protocol; the old claim that ranges remain a separate protocol is superseded.

A value-region checker serves standalone blocks, if branches, and block-bodied
match arms; bare arms adapt their result into the same aggregation. Source
completion and analytical reachability follow [Explicit Divergence](decisions/divergence.md).
Saved flow includes explicit give/return/loop destinations and remains immutable
under the successful owner. A scope's result joins only paths reaching it;
loop/give consumers handle their own exits, and closures have independent flow.
Evaluation-only aggregate lowering keeps child evaluation order without inventing
a result. Source checks remain required even when execution has no continuation.

Pattern parsing retains mutable bindings and or-pattern agreement. Record
patterns are structural, not empty nominal names. Scalar matches preserve the
whole block body; a single arm is not an excuse for premature if/let lowering.
The scrutinee is evaluated once and its snapshot survives Eq side effects.
Enum variant spelling is checked even when the subject has no normal value,
separately from type compatibility. Shared Bool checking serves conditions;
if-chain binding frontiers exclude later else scopes. Coverage uses structural
facts, not arbitrary user Eq. Diagnostics distinguish an impossible or-alternative
from a whole unreachable arm and compare decoded strings and signed values.

Interpolation shares the string decoder and normalizes ordered String-output
operations. Display operands and Options preserve source order and binding
provenance. A divergent display operand creates no unreachable formatting/default
Options execution obligation; explicit source Options still receive required
static checks. Group/block result metadata passes through the common checker.

Closures retain their own completed signature and capture/body identity; a reused
expression ID is not a shared concrete ABI. Capture discovery visits values,
places, writes, and calls using lexical binding IDs. Globals are not captures;
shadowing cannot redirect a saved capture. Grounded capture metadata belongs to
the body instance, not a second Mono cache of inferred truth.

## 8. Implicit Calls and Reachability

The same selected-call/evidence pipeline covers iterator setup/next, destructuring,
try conversion, formatting, defaults, operators, and destruction. `try` retains
operand/return/success/error types, enum variant identity, lexical owner, and the
selected error conversion. Core From's error requirement slot is explicit;
result-name guessing or silently omitting a missing conversion is invalid.

Await facts are keyed by body and expression and retain final Promise/payload
terms. Demand dependencies are explicit; missing is not Unit and payload is not
re-derived from AST. Async signatures distinguish public Promise result from
logical result. Async entry owns its accepted receiver/arguments; declaration
borrow/inout restrictions and frame ownership cannot be replaced with unique
copies or a different ABI rule.

Final dependencies follow selected calls, globals, aggregate/storage types, and
implicit destruction. Destruction visits fields, enum payloads, Buffer elements,
and strong references with structural type identity and a cycle-safe worklist;
weak references do not drop pointees. Closure creation prepares environment/drop
metadata without making its body effectful execution. Signature registration and
body readiness remain distinct; concrete body requests enqueue rather than
recursively prepare through backend discovery.

Globals have a fixed synthetic body identity and explicit source/target storage
terms. Final storage resolution supplies the LLVM declaration; initialization
transfers ownership once. Global-address facts retain declaration identity,
mutability, and grounded target type. Address formation is not pointee ownership,
and illegal moves remain rejected. Rust's [THIR](https://rustc-dev-guide.rust-lang.org/thir.html)
StaticRef/Deref split and Swift's [SIL](https://github.com/swiftlang/swift/blob/main/docs/SIL.rst)
`global_addr` are references for that distinction.

Finalization publication closes added call/destruction dependencies before Access.
Append preserves existing IDs, repeats are idempotent, and failed partial work is
not executable. Resetting finalization after calls exist must fail before clearing
other state. Provisional reachability is not final reachability: descriptor/type
worklists and body scanning are separate. Registering all methods/types as roots
or recovering dependencies in LLVM is not a valid shortcut.

## 9. ABI, Ownership, and Intrinsic Consumers

A body signature distinguishes no receiver from an associated lexical type
environment, retains a mode for every parameter, and separates logical async
result from physical entry result. Signature preparation restores scratch/cursor
state and does not imply body success. The ABI chapter's common C classifier,
including supported narrow/F32 handling, supersedes older unsupported-width notes.

Physical storage strips only a permitted outer view; nested view meaning survives.
Newtype adapters are reachable on demand through calls and witnesses, keyed by
newtype, original function, complete arguments, and evidence. The original body
keeps its method binders and lexical `Self`; the adapter performs boundary
conversion, including fallible/nested results and inout writeback. Whole-owner
newtype boundary equivalence follows same type, immediate underlying type, and
recursive constructor/label structure, not arbitrary bitcast compatibility.
LLVM additionally validates both physical layouts. Reinstantiating the original
body with newtype `Self` is rejected because it changes meaning; Rust’s [newtype wrappers](https://doc.rust-lang.org/book/ch19-03-advanced-traits.html#using-the-newtype-pattern-to-implement-external-traits) and
Swift’s [type aliases](https://docs.swift.org/swift-book/documentation/the-swift-programming-language/declarations/#Type-Alias-Declaration) are comparison points, not equivalent Plew semantics.

Final ownership classification follows nominal declaration identity, including
unique newtypes, not names. Final destruction descriptors cover reached signature,
local, aggregate, and primitive types; a scalar no-release result is still ready
information. Recursive release need is a least fixed point over String, Buffer,
strong references, closures, existentials, and user deinit roots. An unfinished
recursive descriptor is not no-release. LLVM consumes finalized physical field,
variant, box, and underlying layouts; unknown layout cannot default to an integer.
Named declarations precede recursive layout completion, with boxed enum payloads
forming the intended recursion boundary.

A typed deinit body borrows its receiver while destruction owns the whole value,
then fields drop in declaration order. It cannot recursively self-drop. Generic
unique struct deinit retains declaration function identity and lexical binders;
this does not authorize generic enum/copyable deinit. Destruction's Unit call
contract is validated after body/type reachability without fabricating a source
call site. Matching an owned unique enum evaluates once into an owned home and
commits payload transfer/discard cleanup per selected arm.

Access consumes saved dereference/value recipes and successful source-owner
facts, not reparsed calls. Reference access grants no new mutation permission.
Original source places remain distinct from ABI temporaries. View-transparent
places and value view boundaries differ; field disjointness does not prove index
disjointness. Computed unique temporaries may have a borrow home only when they
own the whole value; this cannot change named moves or projected ownership.

Runtime intrinsic classification uses selected declaration identity and final
types, not names. Retained cases include FFI CString/CFree/StringFromCString and
Array C-pointer access; unchecked Core String bytes must maintain independent ARC
ownership. Numeric conversions preserve truncation/bitcast and float/NaN rules,
separate from checked factory conversions. Checked arithmetic covers width/sign,
overflow, division by zero, MIN/-1, and remainder by -1 without LLVM undefined
operations. Strong-cell construction consumes an owned temporary for a copied
source rather than the source binding; weak lock obtains ownership without
retaining its input. Strong/weak, entropy/Random, and timer/sleep declarations
retain exact intrinsic origin; timer classification alone is not suspension.
Runtime glue need not invent a Mid source body. Buffer's separate intrinsic
contract is in [Collections and the Safe Buffer Floor](collections-and-buffer.md).

## 10. Detailed Reader Obligations

These requirements identify logical payloads and consumers, not a decision to
preserve every current class or helper name.

| Saved producer fact | Required final reader behavior |
|---|---|
| `BodyTypeResult` / selected result recipe | Ground the complete free-call result, generic or otherwise, with its selected substitution before a following receiver consumes it. Closedness shortcuts cannot replace general associated-type substitution. Unknown projections stay symbolic rather than receiving guessed equations. |
| Lexical body parameter terms | Read the source owner's terms, then instantiate explicitly. Selected concrete receiver classification and authored trait provenance remain distinct; method binders precede same-named associated members. Both syntax carriers resolve bare associated names to the same predeclared `Self#Trait.Member` identity. |
| Substitution | Apply binder mappings simultaneously; do not recursively reapply `T → Box[T]` to its caller-owned replacement. Preserve occurrence and replacement view sets recursively (`T#E`, `T = S#F` gives `S#E#F`). Projection output does not inherit receiver views. Never reinterpret a nominal with declaration identity as a same-spelled binder. |
| Dynamic call | Retain the chosen function type or existential trait/slot/binding environment, full parameter/result terms, modes, and conversions despite no concrete function index. Re-publication checks full equality. Vtable ABI consumes that signature and evaluated Mid places; inout CoW acts on the evaluated place. |
| `FinalForResolution` / `ForTypeRecipe` | Retain iterator/next selection, identity-versus-call setup, Optional/Item terms, enum and Some/None identities. One lexical statement recipe is distinct from per-instance final terms. A private row/index query replaces whole-table scans and missing-fact inference from Array/AST/associated names. Typed for bindings desugar to ordinary typed lets with unspellable generated names; moved blocks retain type-use obligations. |
| Closure signature | Publish its source signature before nested-body checking. Store the final function term and capture list on its own body instance, not an expression-ID-wide ABI cache. Mid verifies capture source types, bindings, and modes; LLVM consumes the grounded list. Closure return/try uses that closure's result contract, including global closures. |
| Inferred local storage | Consume its saved initializer term or selected call recipe, not a new expression walk after a match scope exits. Binding storage and storage-conversion destination use the same term; explicit annotations remain a different source constraint. |
| Newtype field representation | Follow resolved declaration identity to the underlying storage term without changing nominal type. Field index/type/count and boxing use the same query. Bound malformed cycles; never choose another same-named newtype. |
| Access input | Retain evaluated key and reference owner per access occurrence, then map prepared value identity to those locals. Getter/setter cannot reread mutable keys or reference variables. Dereference/field paths retain the same shared cell, ordinary scopes retain owner lifetime, and `accessPlace` remains separate from an ABI temporary. Verifier checks place validity and root liveness. |
| Inout facet | Free, ordinary method, and extension calls share selected parameter mapping/write-mode admission. Prior-call-result views preserve one evaluation and the original place. A private `placeSource` query supplies provenance without repeated AST traversal; values still use value-view conversion. |
| Method instance registration | Consume a completed call's receiver, callee, arguments, and result with presence, callee, and arena-range checks. Receiver and result are different fields. Prepared concrete static calls read the matching ready body signature instead of re-grounding; bodyless declarations use the explicit selected environment. Signature readiness is not body success. |
| Final call arguments | Ground saved Expression source types under successful owner authority. A selected signature supplies context only to still-pending operands, never overwrites committed source view/type. Range checks remain independent from type-fact presence. |
| Completion | Require successful lexical preparation or the exact prepared global target before reading children, expressions, statements, or blocks. A prepared owner handle is module-private and session/snapshot-specific; each fact still checks ownership. Completed preparation results are immutable, including failures. Allocated slots and occupied-request count do not prove success. |

An inference adapter must preserve an existing term, state, shape, literal context,
and legacy projection when it cannot construct a complete new term. Numeric
context can refine Unrecorded/Pending zero to a permitted Value; it cannot promote
NoNormalValue or replace Unit/committed types. NoNormalValue does not participate
in inference as a value. A discarded unresolved numeric literal and an evaluated
untyped aggregate are not equivalent obligations. Source-recording owner metadata
alone proves neither type closure nor completion success.

Selected function-result publication must return through common expression
completion/value-use checking; callee selection alone does not complete an
expression. Refinement preserves saved source/execution completion. A new
source-rewriting phase needs an explicit new producer/recheck boundary, not
silent post-success reinterpretation.

Runtime exact-declaration consumers also include Core raw strong/weak-cell
operations and directly imported runtime functions. Selected intrinsic
classification is separate from effect/suspend classification. FFI String/Array
pointers, entropy and timer functions cannot become name-based exceptions to the
shared signature, ownership, or final-dependency contract.

## 11. Implementation Map and Remaining Closure

The following are retained implementation observations and bounded migration
contracts, not certification of the current tree. The audit base and physical
storage question remain those in Compiler State. Evidence lives in meta's
[typechecking remediation evidence](../../../evidence/typechecking-remediation/).
Focused success never replaces whole-compiler, sanitizer, fixed-point, or
performance gates, and historical watchdog failures are not newly reproduced bugs.

| Boundary | Retained state and limitation |
|---|---|
| Static/conversion proofs | Private arenas append complete child-first proofs and expose common readers; no replacement API. Proof-ID-bearing source tables and whole-owner authority still need closure. Decoding/freeze-thaw are not admission. |
| Final calls | Arena owns rows, five payload pools, and index. Publisher owns ranges and rejects duplicate body/site before row/payload publication. A private argument-tail handle checks continuation/ranges, but is neither a rollback transaction nor foreign-arena authority proof. Mid/LLVM use scalar readers; Comp owns semantic preparation/diagnostics. |
| Prepared call constraints | Private Building/Prepared states publish owned immutable snapshots only after successful function/global source obligations and common admission. Mono's Direct reader uses Prepared data without rechecking constraints. This alone does not seal type facts, selection tables, or proof stores. |
| Recorded bound consumption | Written Direct calls pass saved child proofs to concrete body admission. Static/protocol/operator/implicit calls and entry requests retain Declaration paths in the recorded candidate; do not claim complete migration. Extern/bodyless calls still require final call admission. |
| Source templates | Private rows reject selected-site replacement after Prepared; conservative storage classification is auxiliary, not reselection. Private append-only operand/type/view pools and lookup indexes do not yet prohibit every append after owner success. Historical slices: compiler `ce6e87fd` and `16f5af17`. |
| Bounds/projections | FunctionBoundArena owns stable rows and ordered per-owner indexes together. Projection-presence summaries remain tri-state for forward children. Selected normalization equations replay proofs, not lookup. |
| Owner readers | Mono expression, await, construction, assignment, Access projections, call-argument Expression sources, and global closures must share explicit successful owner facts. Global targets and closure owners cannot come from ambient Cursor. Constructing-reader closure remains incomplete. |
| Completion | PreparedSemanticCompletionOwner must identify exact session/snapshot; expressions, statements, and blocks share immutable source/execution flow. Earlier flow migrations are bounded work, not proof all readers use the shared channel. |
| Remaining acceptance | General Unit value binding/conversion, source-place mutability/ownership at all call kinds, captured generic shapes, and full signature/result/bound consumer coverage require audit. No language prohibition or confirmed current bug follows from absence of audit. |

Focused evidence directories retain separate scopes: `source-typing-closure`,
`diagnostic-continuation`, `conversion-proof-boundaries`,
`structural-proof-admission`, `box-proof-admission`, `box-proof-subjects`,
`path-proof-admission`, `assumption-authority`, `call-proof-admission`,
`call-proof-boundary`, `call-signature-admission`, `static-signature-admission`, and
`call-bound-admission`. The last includes append-only proof/final-call publication
and source-template row/pool slice comparisons. These are evidence pointers, not
adopted physical storage APIs or a current all-green claim.

Diagnostic continuation preserves an owner's first failure and independent
conversion errors. Missing owner authority fails the request; an error queue or
rendering severity cannot replace domain failure. Declaration checking may
continue to collect diagnostics without publishing that owner as successful.
Remaining owner/evidence closure is tracked by [met-si6j](../issues/met-si6j.md);
completion migration by [com-tijs](../issues/com-tijs.md).
Physical storage must be decided with concrete saved fields, acquisition/append
cost, copying/retaining, indexing, and failure isolation before paused
implementation resumes. A generic all-types layout-use table with no actual
consumer is not adopted: it duplicates facts and can add quadratic work.
