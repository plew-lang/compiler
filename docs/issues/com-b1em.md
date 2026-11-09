---
id: com-b1em
status: in_progress
deps: [com-kd1s]
links: []
created: 2026-11-09T17:11:02Z
type: task
priority: 2
assignee: Koji Murata
parent: com-uiri
tags: [ownership, backend, mid]
---
# Select stable evaluated homes before ownership preparation

## Guarantee and Scope

Consume W1a facts with the common root/interval/projection proof before drop/ownership verification. Preserve named-local ownership and required evaluation snapshots; omit only redundant evaluation temporaries. Cover initial self acquisition versus guaranteed self forwarding, globals/static fields, reference/accessor exclusions, callback/later argument/deinit reentry and async acquisition. Keep baseline byval ABI.

Canonical proposal: [com-rv7l](com-rv7l.md#investigation-result-and-recommended-design). Parent [com-uiri](com-uiri.md) retains end-to-end prototype and no-go/return responsibilities. This task does not change source language semantics or authorize main/seed promotion.

## Execution and Completion

Enumerate finite assertions and real producer/consumer inventory before editing; use task-start TDD and independent neutral review at each reviewable increment. Structural RED must identify the missing handoff/protocol rather than unrelated fixture failure. Record actual execution and retained snapshots as separate evidence. Each required obligation above must be reconciled; deferred implementation cannot count as completion. Measure metadata/preparation cost at W2/W4 even when this unit does not claim speedup.


## Finite Execution Inventory

The current baseline is compiler `617ec3cd`; W1a origin authenticity is closed.
The existing evaluated-value helper has two consumers: aggregate children and
selected template arguments (`Mid/Build.pw::materializeMidAggregateValue` and
`midTemplateArgumentOperand`). Both must consume the same storage proof.
Receiver acquisition is a separate selected Access/read-borrow path through
`midSourceCallReceiver`/`midCallReceiver`; do not equate that operation with an
ordinary Copy merely to optimize forwarding. `Mid/Verify.pw` owns initialized
availability, and source scopes own destruction. LLVM consumes the resulting
Mid operations; baseline byval is unchanged throughout this unit.

| Increment | Required assertions and controls |
| --- | --- |
| Authored local root | Real accepted immutable binding reuses its home across a later call; mutable binding snapshots; authored StorageBoundary Copy and destruction remain. Missing/unproved/synthetic, borrowed/cell/inout/unique roots never gain a const proof. Initialization and owner availability remain verifier obligations. Test shadowing and loop incarnations. |
| Root and projection composition | Guaranteed ordinary inputs and completed dedicated temporaries retain their existing behavior; distinguish guaranteed copy-self forwarding from initial receiver acquisition. Nonboxed static fields compose a proven root; Deref, Index/getter and boxed fields without stable-box evidence remain conservative. No spelling/size/whole-body-search heuristic. |
| Ambient and effect boundaries | Inspect actual immutable-global initialization/lifetime evidence before allowing global reuse; absence remains snapshot, not invented proof. Preserve mutable-global/capture-cell/reference snapshots across later explicit/default arguments, unknown callbacks and user deinit reentry. Exercise aggregate children and calls, reordered/default arguments and normalized inout calls. |
| Ownership and escape | Named binding initialization, returned/stored/captured values still acquire their own owners. Async entry acquires its frame inputs before caller lifetime ends; frame-owned inputs are not guessed to be guaranteed synchronous parameters. Read/borrow/inout/move selected modes retain their meaning. |
| Final reconciliation | Real built and prepared Mid decisions, fresh raw native controls and matching output/destruction assertions; independent neutral review at finite increments. Reconcile every row and conservatively unsupported projection against source evidence. Full prototype/final gates and measurement remain W2–W4/com-ffar. |

First TDD increment: a real source-body test inspects the original local selected
by accepted origin, its authored initialization, and the first argument at the
actual target call. The immutable case must currently fail because a redundant
anonymous evaluation snapshot is selected; the mutable control must retain that
snapshot. Setup failures and mere overall count changes do not establish RED.
No product edit precedes that actual failure. Additional increments retain this
finite inventory; unresolved evidence is not silently counted as completion.

## Whole-Local Increment (validated, W1b remains open)

Signed checkpoint: `immutable-local-evaluation-validated-20261110`.
[Exact evidence and incremental neutral review](../../../evidence/performance-regression-history/value-passing-implementation/stable-local-evaluation.json).
The shared `midLocalHasStableEvaluationValue` consumes the W1a row without a
new search/index. Both call arguments and aggregate children omit the redundant
whole immutable-local evaluation snapshot. Named StorageBoundary copies,
initialized availability, selected receiver/argument modes and byval stay intact.
The exact final fixture on all 180 baseline source files at `617ec3cd` executes
RED at the extra-owner count; the modified source executes GREEN. Both inputs
are unchanged. It asserts named Copy2 retention, mutable snapshot2/immutable0,
actual selected call/aggregate homes, real declaration/destruction requests and
MoveUnavailable on the exact uninitialized local in a separate malformed clone.

Standard build `20261109T190730-build-5219f9` passed with unchanged inputs. Fresh
candidate SHA `369d4de548900e139cec5ac4f1bd710a1f811d3b615683baaabefd5ab5d552d8`
compiled/ran this fixture, mid_value_evaluation_order and
mid_binding_origin_families with exact goldens and empty runtime stderr. Neutral
review independently reconciled final source, RED/GREEN, build/candidate/input
hashes and these fresh controls, approving only this focused increment.
Fresh full-source compilation also succeeded as supplementary diagnostic smoke;
its traced wall time is not formal performance or fixed-point evidence.
Transient ambient Array/String setup errors were not counted as defect RED;
the explicit Pair aggregate and input-returning child isolate the same path.

The authored-local inventory row as a whole remains open (shadowing, loops and
conservative-role controls), as do every remaining W1b obligation and later gates.

## Next Increment: Guaranteed Self and Root Composition

The read-only independent investigation located the current copy-self entry's
stable outer bytes in baseline byval/callee binding, plus the original receiver's
semantic read reservation in Backend/Llvm/Ambient.pw. Body-local forwarding can
use that guarantee. Initial receiver acquisition must remain the selected Read
borrow/Access operation: snapshotting it to make an overlapping write succeed
would change semantics. Add focused TDD for whole synchronous copy-self only,
retaining inout/move/async/Deref exclusions, named acquisitions and receiver
shared-field overlap rejection/panic versus disjoint success. No new semantic
judgment is required to preserve that existing contract. Follow with the other
finite inventory rows; this is not full receiver or full W1b certification.

## Existing Callback Validation Gap

`run/value_snapshot_callback.pw` is rejected by the unchanged df968 carrier
before linking: source argument changed without a representation mapping. It
imports no compiler implementation, so loading the modified Mid builder is not
the cause. Retain the callback obligation for fresh product investigation;
passing another fixture is not substitute coverage. No existing test is changed.
