---
id: com-9hny
status: in_progress
deps: [com-b1em]
links: []
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
