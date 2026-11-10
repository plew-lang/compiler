---
id: com-9hny
status: in_progress
deps: [com-b1em]
links: [com-xkcb]
created: 2026-11-09T17:11:02Z
type: task
priority: 2
assignee: Koji Murata
parent: com-uiri
tags: [ownership, backend, mid]
---
# Centralize physical signature descriptors and typed value carriers

## Guarantee and Scope

Introduce the deterministic shared logical-role/physical-index/transport descriptor and explicit Value/Home carriers while retaining baseline byval execution. Direct/indirect/adapters all consume the authority or an explicit legacy adapter. Reject role/type/index/context/signature mismatches. Do not independently reclassify in callers.

Canonical proposal: [com-rv7l](com-rv7l.md#investigation-result-and-recommended-design). Parent [com-uiri](com-uiri.md) retains end-to-end prototype and no-go/return responsibilities. This task does not change source language semantics or authorize main/seed promotion.

## Execution and Completion

Enumerate finite assertions and real producer/consumer inventory before editing; use task-start TDD and independent neutral review at each reviewable increment. Structural RED must identify the missing handoff/protocol rather than unrelated fixture failure. Record actual execution and retained snapshots as separate evidence. Each required obligation above must be reconciled; deferred implementation cannot count as completion. Measure metadata/preparation cost at W2/W4 even when this unit does not claim speedup.

## Execution Boundaries

The [W2 protocol inventory and plan](../../../evidence/performance-regression-history/value-passing-implementation/w2-protocol/README.md)
pins the unchanged product revision, helper/native sites, nonlexical binding
adapters and proposed finite checkpoints. It is preparation evidence, not
implementation or acceptance. W1b closure does not prove this task's protocol.

1. Establish the completed logical lane/convention model, target/context
   admission and single physical planner. Connect normal free/method
   declarations; identify not-yet-migrated entries with explicit baseline
   conventions. Test equal LLVM types with distinct roles and malformed lanes.
2. Connect typed Value/Home call and parameter carriers for a complete normal
   declaration/call/binding round trip. Reject type/role/index/context/signature
   mismatch while preserving baseline byval and local copying.
3. Build and retain the body-local binding/storage plan at LLVM-ready admission;
   consume it at emission. Validate capture expansion and erased receiver
   conversion as explicit adapters, not count-only raw binding vectors.
4. Migrate indirect closure/existential calls and ownership glue through the
   same planner and typed bindings. No caller-local role reconstruction.
5. Migrate async entry/frame/resume and C-to-private conversion, plus declarations
   and requested JIT publication. Explicitly account for main/global/native
   boundaries; missing body is never permission for implicit legacy fallback.
6. Remove competing classification and unchecked binding overrides; reconcile
   every inventoried consumer, affected raw/optimized byval and public controls,
   preparation cost, and the whole W2 guarantee through independent review.

These are incremental checkpoints within W2, not separately completed tasks.
Actual guaranteed-address forwarding and its optimization benefit belong to W3;
W2 cannot close with an unused descriptor or an unconsumed storage plan.

## Target Prerequisite Checkpoint

The [target handoff evidence](../../../evidence/performance-regression-history/value-passing-implementation/w2-protocol/target-handoff.json)
records the actual RED, source/native target-description handoff, successful
standard build, native and fresh candidate controls, and neutral review.
Object CPU and actual LLJIT descriptions now reach all three module creation
paths before layout-sensitive planning; session selection is fixed and final
native admission still checks exact agreement. Baseline byval remains intact.
Internal SessionJit/SessionModule diagnostics now perform their missing program
entry registration step; archived old-source reproduction and preserved native
assertions distinguish that repair from a product regression.

This target record closes only checkpoint 1's target precondition. The role
planner increment is recorded below; typed Value/Home carriers, Ready
binding/storage plans and W2 cost reconciliation remain open. The record explicitly excludes full gates, formal performance,
main/seed promotion and overall W2/com-ffar completion.



## Role Planner Checkpoint

[Role planner evidence](../../../evidence/performance-regression-history/value-passing-implementation/w2-protocol/role-planner.json)
records the normal declaration structural RED, native same-module stale-target
readmission RED/GREEN, finalized BodySignature role/mode/type handoff and the
representation-only planner. Normal free/method declarations use its stored
plan. Other private entries explicitly identify their legacy family; they do
not claim completed semantic roles. The leaf owns omission/direct/byval, exact
target/context/revision validation, physical indices and represented alignment.
Baseline result and snapshot behavior remain unchanged.

Standard build `20261109T215505-build-b5b229` passed with immutable inputs. Fresh
candidate `bin/plewc-value-abi-role-planner-20261110` (SHA in evidence) passes
the live-LLVM planner and malformed controls, raw/optimized byval controls,
split globals, separately requested closure/witness and exposed entries,
SessionJit, C callback/host/async execution, and eight lazy CLI golden controls
including unique/default lifetime cases. Initial disk-full failures and a
runner's missing semantic-progress events are explicitly separated from product
RED; the runner now reports actual bounded command stages and those controls
were rerun successfully. Neutral source review fixed two stale-target gaps;
final evidence reconciliation independently accepted checkpoint 1.

This is checkpoint 1 only. Direct call/read paths still use stored descriptor
compatibility adapters, not typed Value/Home inputs. Checkpoints 2–6, actual
address forwarding, benefit/go-no-go and final task gates remain open.

## Normal Semantic Correspondence Prerequisite

[Normal correspondence evidence](../../../evidence/performance-regression-history/value-passing-implementation/w2-protocol/normal-correspondence.json)
records the first checkpoint 2 prerequisite. Executable Mid verification now
checks a normal synchronous callable's contiguous parameter-local prefix against
its completed BodySignature, using semantic equality rather than raw TypeRef IDs,
and checks Inout/Move flags. Closure, global initializer and synthetic/async entry
contracts remain separate. No per-local duplicate role field, AST re-grounding
or backend semantic equality search is introduced.

A real I64-signature/U64-local native RED and an isolated baseline diagnostic
show the original missing correspondence; the final native fixture checks 19
cases. The existing return-type fixture now supplies its previously missing
function declaration; its original return operands/types/assertions remain.
Standard build `20261109T222955-build-05022c` passed with immutable inputs. Fresh
`bin/plewc-value-abi-normal-correspondence-20261110` passes the new fixture and
four existing Mid controls, 12 lazy CLI golden controls (including newtype and
mutable captures), and raw/optimized byval controls. Neutral source review fixed
closure/global keys being mistaken for Func indices; final source/build/input/
artifact/RED/GREEN reconciliation independently accepted this prerequisite.

The verified immutable MidExecutableBody snapshot will qualify the normal
local-index/signature-lane mapping. This prerequisite is not completion of
checkpoint 2: normal typed Value/Home call and binding consumers must still use
that correspondence and the stored physical descriptor. Ready storage/synthetic
maps, all-entry migration, preparation cost and final gates remain open.


## Typed Normal Roundtrip Checkpoint

W2 checkpoint 2 now connects normal declaration, direct call and verified
parameter binding through typed Value/Home inputs. The shared representation
leaf checks canonical semantic term, role, passing, logical index, native type
and native function/module/context provenance. A Home is a typed alloca or
incoming byval aggregate address, distinct from an inout pointer Value.
Baseline call staging and callee local copying remain; this is not W3 forwarding.

The [checkpoint evidence](../../../evidence/performance-regression-history/value-passing-implementation/w2-protocol/typed-normal-roundtrip.json)
records the structural old-path RED, native constant-provenance RED/GREEN,
newtype publisher handoff RED/GREEN, final standard build, fresh CLI12,
internal5, raw/optimized ABI, native leaf, C expose/callback and a mixed
receiver/empty/scalar/inout/aggregate control. Canonical receiver identity now
travels through all three normal-body publishers and the sole row store;
source receiver/view identity remains separate. Raw normal-body calls require
one of the finite ExposedEntry/Destruction compatibility adapters and matching
body identity; raw normal parameter binding/overrides are rejected.

Neutral review checked 188 input/source hashes, 130 artifacts, the 183
source/native build inputs and all 6499 recorded build inputs. It independently
reran architecture checks, baseline/fresh mixed CLI, fresh newtype CLI and the
native leaf harness, then rechecked hashes. The finite checkpoint is accepted.
Malformed private root compatibility guards are source/structure reviewed,
not independently executed malformed root API tests. This limitation is not
relabelled as runtime coverage.

Checkpoints 3–6 remain open: retained Ready binding/storage plans and adapter
conversion, indirect/glue/async/C migration, whole-protocol reconciliation and
preparation cost. The current Home byval-argument index lookup uses a parameter
scan; account for its asymptotics and target-scope checking at the W2 cost
boundary. Prototype adoption, W3/W4, formal timing/fixed point, final suites,
ASan/LSan and promotion remain unproven. No task is closed by this checkpoint.

## Retained Ready Plan Execution

The neutral read-only plan review at `ce9dc79c` selected four bounded increments
inside checkpoint 3, each closing its actual admission-to-emission consumers:

1. Normal/main/global Ready retains exact entry and body-local LLVM value type,
   storage type and parameter mode in flat typed pools. Local allocation,
   normal binding and subsequent local type reads consume the retained rows.
2. Closure ordinary/capture bindings and environment-drop expansion retain
   explicit field-to-local mappings and boxed/value storage distinctions.
3. Witness bindings retain the selected erased receiver load/address conversion
   and ordinary lane mapping.
4. Async frame/resume uses the same retained local representation, followed by
   removal of raw offset/vector/storage overrides and Ready construction bypasses.

A legacy physical lane remains explicitly legacy while its body-local adapter
is migrated; it must not falsely claim a completed semantic lane. Physical
indirect/glue calls and async/C/publication transport migration remain under
checkpoints 4/5. The stored plan must reach final allocation/binding and later
local reads; adding unconsumed metadata cannot complete an increment.

The first normal/main/global increment is independently accepted; the other
three remain open. [Retained local-plan evidence](../../../evidence/performance-regression-history/value-passing-implementation/w2-protocol/ready-normal-local-plan.json)
records source review repairs for emission-plan leakage into async admission,
missing native entry checks, override bypass and malformed canonical bounds.
A test-only exact source snapshot plus appended Backend main exercises real
private producer/consumer APIs without exposing them or rewriting their bodies.
It checks a live retained local alloca and Internal rejection of malformed
body/canonical/entry/override inputs. Standard build, fresh CLI14/internal5,
raw/optimized ABI, split globals, C expose/callback and native controls passed.
Neutral review reconciled 470 distinct path/hash references, including all 191
source/control inputs with the build and 183 snapshot inputs; it independently
reran the private native harness and mixed/async CLI controls. No new source
semantic decision was introduced.

Ready's remaining parameter-count field belongs to unmigrated legacy binding
adapters; it does not select Planned binding. Remove this compatibility data
with the remaining raw overrides at the whole-checkpoint boundary. Preparation
cost and actual guaranteed-address forwarding remain unproven.

## Retained Closure and Environment-Drop Bindings

Checkpoint 3's second increment retains Closure/EnvironmentDrop local adapters.
Admission checks the frozen closure captures and body parameter types/passings
against Mid local identities and flags, then saves existing ABI-pool parameter
rows and explicit environment-field-to-local conversions. Ready keeps their
native environment type with the local type/storage/mode rows. Allocation,
actual input stores/address aliases and subsequent local readers consume those
rows. Emission no longer reconstructs capture correspondence/layout, passes a
leading raw parameter offset or expands an environment into an untyped vector.
Physical signatures remain explicitly Legacy for these families until their
later W2 migration; no completed semantic roles are invented for them.

A cell capture is a pointer stored in a local pointer holder, not a source
inout address alias. Captures are borrowed during closure activation, while
the separate environment-drop body owns its capture inputs and retains Mid's
existing cleanup order. Byval loads/local copies and ARC behavior are unchanged.
Swift's [SIL conventions](https://github.com/swiftlang/swift/blob/main/docs/SIL/SIL.md)
and [generics implementation discussion](https://download.swift.org/docs/assets/generics.pdf)
also distinguish logical captures from context-pointer unpacking. Plew retains
its existing explicit environment ABI rather than importing another language's
capture ownership or escape rules.

The [second-increment evidence](../../../evidence/performance-regression-history/value-passing-implementation/w2-protocol/ready-closure-local-plan.json) records the baseline structural RED, standard
build `20261110T000458-build-b27084` with immutable inputs, fresh CLI22/internal5,
environment Mid coverage for seven fixtures, raw/optimized value ABI and C
expose/callback controls. An exact source snapshot plus appended test main
executes real private admission/emission APIs, checking value/cell allocations
and actual stores, malformed correspondence, native entry and override guards.
Test setup repairs publish required scalar representation contracts and use
correct opaque-handle identities; they are not product RED or relaxed checks.
The final test main differs from the product build's control input, while all
183 product source/native inputs still match that build. The final snapshot
and its executed test-main hash identify the actual tested inputs.

Witness and async/frame local adapters, whole-checkpoint raw override/count
removal, physical indirect/glue/async/C/publication migrations, preparation cost,
W3/W4 and final com-ffar gates remain open. The transient closure types/bindings
arrays and their flat-pool transfer must be included in W2's preparation-cost
reconciliation; this increment makes no performance claim.

Neutral review independently reconciled 542 distinct path/hash references,
183 source/native inputs against all 6513 build inputs, 65 controls, 109 artifacts
and 183 snapshot inputs. It replayed the native harness, fresh mixed lazy CLI,
architecture controls and baseline structural RED. The finite second increment
is accepted. A source ordinary-inout probe fails identically during program Mid
preparation on baseline/fresh candidates; it is not a successful inout execution
claim and remains explicit for whole-W2 entry reconciliation.

## Retained Witness Inputs

Checkpoint 3's third increment retains the selected witness receiver conversion
and ordinary ABI-pool-to-local mappings. BodyOrigin identifies the exact
FinalExistential member and selected target. The adapter signature's sourceRef
and the selected target environment's concrete receiver are checked separately;
the unused adapter environment is not a new semantic authority. Borrow/Move
receivers load their concrete value from the erased address, including pointer
representations; Inout keeps the address. Normal ordinary inputs retain baseline
omitted/direct/byval reads. Allocation, binding and later local type reads use
the Ready plan; witness emission no longer supplies an untyped input vector or
reselects the receiver representation. Physical Witness lanes remain Legacy
until their later physical-protocol migration.

The [witness evidence](../../../evidence/performance-regression-history/value-passing-implementation/w2-protocol/ready-witness-local-plan.json) records structural baseline RED, immutable standard build
`20261110T003314-build-65ae1d`, fresh CLI32/internal5, six unique Mid witness-body
controls, raw/optimized ABI and C expose/callback success. The private exact
source snapshot exercises Borrow/Inout for scalar and CPtr representations,
Move inputs, actual receiver loads/stores or argument address identity, ordinary
bindings, 16 malformed admission cases and native-entry/override rejection.
Its manually supplied physical input contracts are not source conformance
proofs; source selection/calls/cleanup are independently covered by the real
source controls. Neutral source review fixed a passing-mode numeric-key error
using enum patterns and corrected a test that corrupted an unused environment.
No source semantics or ARC acquisition/cleanup changed.

Neutral final review accepted this finite third increment after independently
recalculating 572 distinct hash references: source183/control85/artifact119/
snapshot183. All product source and control hashes match the successful build's
6518 inputs. It replayed the native controls (including Move), representative
source CLI, architecture and baseline RED. Async/W2, preparation cost and final
gates are not included in this acceptance.

## Ready Async Activation and Checkpoint-3 Exit

Checkpoint 3 is independently accepted for every actual Ready family. The
[final async/local-plan evidence](../../../evidence/performance-regression-history/value-passing-implementation/w2-protocol/ready-async-local-plan.json)
records the immutable build `20261110T014617-build-526d8a`, fresh candidate
`compiler/bin/plewc-value-abi-ready-async-20261110` (SHA
`e42eaafeb51308c7c2eb15f7e4f17b2cc8083a60f1a6078beca3a3edd456c8b8`),
49 CLI controls, eight Mid controls, four private native harnesses,
raw/optimized ABI and C expose/callback controls. Source183/control133 all match
the build's 6523 inputs; independent review reconciled 1274 distinct hash
references and replayed native, CLI, architecture and defect REDs.

The [Ready and async contract](../design/mid-entry-audit.md) now owns the
retained entry/frame/resume plan. Raw input/storage vectors, count-only Ready,
external async-mode/closure overrides and the local Legacy fallback are removed.
The retained-only local type reader no longer accepts Comp or mutation authority.
Physical Legacy conventions remain explicit pending checkpoints 4/5.

Real aggregate execution exposed a logical-versus-byval-native signature
comparison mistake, fixed with separate descriptor-side checks. Independent
physical-input reproduction exposed contradictory owned+borrowed metadata,
now rejected by native mode28. Async native cases cover four valid mappings,
18 malformed admissions and six retained mapping corruptions; manually supplied
canonical fixtures are not source ownership proofs. Actual source controls
separately execute ownership, immediate completion, real suspension, shared
Promise waiters, capture cells and program-argument/global initialization.
Removed raw APIs are now tested as signature absence; all remaining meaningful
runtime guards are retained. Generic async/method support is unchanged, not
newly prohibited by the spec. No formal timing/fixed-point/full ASan is claimed.

## Checkpoint 4: Ordinary Completed Closure Increment

The [ordinary closure evidence](../../../evidence/performance-regression-history/value-passing-implementation/w2-protocol/typed-closure-protocol.json)
closes declaration, local/field indirect call and Ready parameter/environment
binding for existing Borrow-call support. One LLVM-scoped finalized function-type
template retains typed lanes; declared owner descriptors share its parameter
range. Calls validate the typed fat value and caller provenance, then extract
function/environment together. Both raw parameter helpers and raw direct calls
reject completed Closure; the retired Legacy.Closure indirect family rejects
before reclassification. Byval staging, local copies and source ownership remain
unchanged. The [ABI contract](../design/representation-and-abi.md) owns this
boundary; a callable scope is not a guessed callee body identity.

Standard build `20261110T024413-build-8782b1` passed with unchanged inputs.
Final product183 matches that build; only the new private test main changed
afterward. Fresh CLI49/internal8, raw/optimized ABI, expose/C callback,
physical-planner native and all four Ready native harnesses passed. Closure's
native controls include two valid and ten malformed Ready mappings, typed
Value/Home calls and 23 malformed call/binding inputs, plus six malformed
declaration/template correspondences. Repeated calls append no physical plans;
multiple owner bodies share a template's lane range. Independent source/native
review required retiring the old raw indirect family, then replayed the final
harness and accepted this finite increment. Initial setup-only failures and
repairs remain distinguished from product defects in the evidence.

The [mode baseline](../../../evidence/performance-regression-history/value-passing-implementation/w2-protocol/closure-mode-baseline.json)
proves ordinary Inout/Move lazy construction-only succeeds while calls/eager
construction already fail. Preserve those uncalled declarations as explicit
Legacy without polluting completed Borrow templates. [com-xkcb](com-xkcb.md)
owns the existing function-type ownership-mode gap; it is not automatically an
optimization prerequisite. No new source restriction or support is claimed.

### Completed Witness Increment

[Witness evidence](../../../evidence/performance-regression-history/value-passing-implementation/w2-protocol/typed-witness-protocol.json)
records the completed public endpoint `(any target, trait, slot)` through frozen
member/selected-call producers, shared template/declaration lanes, typed fat
consumer and Ready receiver/ordinary binding. The receiver's concrete conversion
stays in its frozen adapter. Cache hits avoid logical-vector construction;
retired raw Witness indirect calls and raw completed parameter readers reject.
Byval/local copies, CoW acquisition and source support boundaries stay unchanged.

Standard build `20261110T035711-build-ece0be`, fresh CLI56/internal8, raw/optimized
ABI and source controls, C boundaries, physical native, and both affected Ready
Witness/Closure harnesses pass with immutable inputs. All 183 product inputs
match the build. Native Witness keeps the previous 21 Ready cases, adds six
malformed declarations and 23 malformed call/binding guards, and checks cache
sharing, typed Value/Home, Inout/Move and cold/warm Unit results. Native Move
receiver is not source dispatch support. Independent source/native review accepted this finite increment: 1225 distinct
path/hash records match, all four final gates are immutable, and both private
harnesses plus raw/optimized source executables replayed successfully.

Execution found a real Unit regression in the initial Witness candidate. A
selected source Unit term and the frozen member's no-payload result must use the
existing common `callableResultSlot`, rather than compare unlike result slots or
invent an empty-record return ABI. Warm/cold native and source lazy/raw/optimized
controls cover the correction; named empty structs keep their result. Initial
scratch controls accidentally selected the retained red alias; those terminated
runs are excluded from acceptance. The final fixed alias is distinct.

### Completed Ownership Glue Increment

[Ownership glue evidence](../../../evidence/performance-regression-history/value-passing-implementation/w2-protocol/typed-glue-protocol.json)
closes checkpoint 4's remaining finite boundary. All seven operations connect
scoped operation/type templates to declarations, typed Value/Home calls and
physical parameter decoding. Ready EnvironmentDrop retains its frozen capture
adapter; the dynamic consumer prepares one same-fat function/storage pair for
null guard and call. Payload consumption does not own the allocation: caller
RC/null/free control, destruction order, byval/local copies and recursive drain
order remain unchanged. Frozen user deinit now calls normal typed Body inputs;
raw Destruction compatibility and all seven raw glue families are retired.
The four competing struct/enum signature arrays are removed.

Build `20261110T043117-build-0e540f` passed. Product184 matches it; the only later
change adds private native scope/provenance controls. CLI65/internal8, ABI/C,
Witness and recursive/zero-size source raw/optimized, physical native and both
affected Glue/Closure harnesses pass. Neutral source review removed a duplicate
EnvironmentDrop function load and repaired a new undef-folding fixture. Final
independent review reconciles 1252 hash references (1237 distinct), all five
gates, exact CLI/internal outputs, six native replays and three lossless log
archives. Seven operation roundtrips, 35 malformed typed inputs, 14 raw parameter
rejections and additional scoped/provenance guards are covered. Record payloads
under enum operations test the physical protocol; real enum/generic/recursive
ownership executes separately in source controls. This closes checkpoint 4 only.

### Next Completed Async Increment

Neutral planning selects the complete private async entry -> activation frame
-> resume roundtrip as the next finite checkpoint 5 increment. Finalized
BodySignature.parameterTypes/parameterPassings/resultType already owns ordinary
inputs and the Promise result; bodyResultType owns the async body payload.
Entry/resume need distinct completed conventions: ordinary Borrow/Move plus
Promise result versus a source-term-free Frame lane plus native void. Bind that
frame lane to activation/body identity; never treat equal ptr representations
as equal semantic values. Do not reconstruct/search Promise source types.

Connect Async.declareAsyncFns, Mid's async-call branch, Async.genLlvmAsyncFunc's
frame input acquisition and first resume, Mid's resume frame reader, and
MidAsync admission/validation to common planner and typed readers/calls. Build
frame layout at current Ready admission, not premature declaration. Retire raw
AsyncEntry/AsyncResume call and parameter paths while preserving existing
Borrow acquisition, Move transfer, frame layout/drop order and Promise
retain-before-first-resume. Keep unsupported source modes unchanged.

Preserve all existing ReadyAsync mapping/acquisition/GEP assertions and add
entry/resume confusion, equal-ptr distinct body/frame, ordinary semantic type/
mode/index, Promise versus body result, provenance and raw bypass controls.
Use empty/scalar/aggregate/enum/omitted inputs, Borrow/Move, immediate and
suspended completion; validate raw/optimized and lazy requested execution.

Subsequent finite increments convert C-to-private values to typed Body inputs
(retiring ExposedEntry compatibility), make program main/global initializer
native boundaries explicit, and reconcile requested publication with body-ID
siblings. Preserve C conversions/attributes/writeback, program args/results,
global initialization order and missing-body refusal. Reuse existing expose/
callback, SessionJit/SessionModule and request/initializer controls; do not add
new C ABI support. Checkpoint 6 owns all-consumer/remaining-Legacy reconciliation
and preparation cost. W3/W4, full gates, formal performance/fixed-point and
main/seed/adopted carrier promotion remain open.
