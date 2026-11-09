---
id: com-b1em
status: in_progress
deps: [com-kd1s, met-zva3]
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

## Synchronous Whole-Self Source Checkpoint

Signed checkpoint: `self-forwarding-source-checkpoint-20261110`.
[Source-level RED/GREEN and neutral review](../../../evidence/performance-regression-history/value-passing-implementation/stable-self-evaluation.json).
The same parameter producer now includes whole synchronous copy-self by removing
only the old name exclusion. Unique/inout/borrowed/cell/owned-entry barriers and
initial receiver acquisition are unchanged. Exact baseline080cb5ef source executes
the targeted snapshot-count RED; modified source executes self and local controls
GREEN. The self test checks actual target/home and Copy mode, inout snapshot1,
copy-self snapshot0, declaration ownership, and the separate caller's original
receiver Read borrow. Neutral review independently matched all180source hashes,
source delta, fixture, fixed carrier, manifests, outputs and exit status, with no
required correction for this source-level increment.

This original checkpoint was source-only. The subsequent field increment below
adds fresh product and the named receiver preservation controls; it does not
certify every owner/async/escape path or close W1b.

## Typed Value-Field Increment (validated, W1b remains open)

Signed checkpoint: `value-field-homes-validated-20261110`.
[Exact field RED/GREEN, final build/fresh controls and neutral review](../../../evidence/performance-regression-history/value-passing-implementation/stable-value-fields.json).
The Copy path composes the same proved root with typed nonboxed Field chains,
retaining the operand/recipe and the normal type/ownership authorities. Move
remains whole-place only. Deref, Index, boxed and unproved representation
boundaries do not inherit this stability. Temporary recipe metadata is not a
copyability proof; completed private result ownership must still cover the use.

The exact final fixture against all180source files at e1a77646 executes the
intended snapshot RED. Modified source checks five roots across real call and
Struct aggregate consumers: immutable local, guaranteed input and copy-self
omit two redundant snapshots each; mutable local and inout input retain two.
It asserts exact selected target/home/projection, named root acquisition and
real declaration ownership. A separate File/resource test using actual std
proves real Deref and recursive boxed paths retain their evaluated snapshot.
New-fixture environment/index mistakes were setup failures, not product RED.

Standard build `20261109T193729-build-847561` passed with unchanged inputs.
Saved fresh candidate SHA
`8028679c1752770eebb68cd8ee6fb9c9aa02ae04cd5962687f283c771969b4fa`
compiled/ran fields, boundaries, self, local and managed String controls with
exact outputs and empty runtime stderr. The existing production normal dispatcher
also passed run5/panic1/typed-source-reject1 controls: dynamic String backing and
inout replacement, disjoint/read receiver use, shared-field overlap panic,
global reentry rejection, evaluation order, borrowed field owner and boxed inout.
Independent neutral review reconciled the final180source hashes, candidate,
input manifests, actual outputs/artifacts and PASS list. Supplementary fresh
full-source compilation succeeded; its traced time is not formal performance.
No full-suite/ASan/fixed-point, ABI transport or W1b-wide acceptance is implied.

## Remaining W1b Execution Boundary

Retain the original finite inventory. Next cover global fallback, cell/borrowed/
unproved roots, shadowing/loops, getter versus raw Index paths and completed
recipe-result ownership. Reconcile later/default/reordered/normalized-inout and
callback/deinit effects; returned/stored/captured owners and async inputs must
retain their acquisitions. The callback prerequisite below is repaired; the rest of the inventory remains open.

Saved SemanticGlobalAddress supplies target/type/mutable, not initialized
readiness for the current body. globalInitializerPrepared is source checking;
collectGlobalDeps is syntactic. Existing process storage/main-before-init code
is not a published per-body readiness contract. Under the accepted proposal,
keep required immutable-global/field snapshots rather than inventing a new
initialization analysis in W1b. Test that conservative path before reconciliation.

Async parameters have ownsAtEntry=true and are excluded from synchronous entry
forwarding. Existing Backend/Llvm/Async stores frame inputs and retains borrowed
values/transfers moves before first resume and before public entry returns.
The read-only investigation establishes that existing responsibility, not its
execution certification. Immediate-completion and suspended managed-input/
cleanup controls remain necessary. Source references and the independent
findings are in the same field evidence record.

## Callback Prerequisite Repaired

[met-zva3](met-zva3.md) repairs the independently confirmed omitted fn() Unit
representation provenance defect. The unchanged value_snapshot_callback now
compiles/links/runs with fresh candidate SHA
12d8d8342640f67d639d8afa054541643d5138d6a34ddcaeffc0e314dc5c1724;
exact output is 1,3,30,110,3 with empty stderr. This restores the original
callback/snapshot/escaped-owner control rather than substituting another test.
[Finite repair and independent artifact review](../../../evidence/performance-regression-history/value-passing-implementation/callback-unit-investigation/repair.json).
All remaining W1b inventory rows still require explicit reconciliation.

## Reviewed Remaining Execution Plan

Neutral read-only w1b_remaining_matrix_review reconciled the finite inventory
after met-zva3. Finish these three increments, then reconcile every original row;
new global readiness, ABI transport and full entry audits are not W1b additions.

1. Root boundaries/binding identity: actual immutable global whole/field with
   later effects in calls and aggregates; mutable global/capture-cell snapshots
   and actual final uses; shadowed immutable/mutable declarations have distinct
   targets/origins and only the stable one reuses storage; managed loop values
   reinitialize/use/clean up per dynamic iteration. Existing inout/unique controls
   plus actual produced roles cover exclusion. Unproved named roots must fall
   back by source structure; do not add a public test API or accept a production
   body missing W1a origin (that remains InvalidBindingOrigin). No-effect
   immutable-global single calls need no newly invented mandatory snapshot.
2. Completed getter/recipe results: selected getter executes once, its parent
   uses PriorCallResult/completed home rather than raw Index, and typed nonboxed
   fields preserve result ownership through real prepared use. Keep pending
   recipes (including a unique owner) from serving as copyability proof. Raw
   Index exclusion may be source-structural because production source Index is
   normalized to a getter. Reuse index_evaluation_local_array_replace,
   index_evaluation_inout_index and mid_access_getter_key_cfg_lowering for runtime
   counterparts; they alone do not prove the new field-home structure.
3. Runtime gaps: deinit during later argument/default evaluation changes an
   ambient/cell/reference value after its earlier snapshot; assert old callee
   value, changed ambient value and one cleanup. Add immediate-completion async
   managed input/move-resource/result cleanup; reuse suspended async controls.
   Trace owned entry/frame stores/retain-transfer/Promise-before-resume without
   adding a new async ownership mechanism.

Final finite reuse: mid_value_evaluation_order, default_eval_order,
value_snapshot_callback, arg_convention_guaranteed_arc,
stable_field_owner_evaluation, async_entry_ownership, async_enum_param_arc and
the adopted receiver run/panic/reject cases. Relate existing return/store/capture
execution to actual prepared owner acquisition instead of multiplying fixtures.
The selected existing11 production controls already pass exact stdout on fresh
12d8d834...c1724; these executions do not close the above gaps or W1b.

## Remaining Increment A (validated)

The product source is unchanged from 3212fe3a. New
mid_stable_root_boundaries checks actual immutable/mutable global snapshots,
capture-cell role and snapshots, distinct shadow binding targets/origins with
only stable-root reuse, loop static binding acquisition and direct call home.
Both global/cell call and aggregate consumers use the selected dedicated homes.
All real bodies pass declaration ownership requests. The companion
stable_binding_incarnations executes distinct dynamic managed loop values,
retained history, shadowed original values and once-per-iteration Marker cleanup
through normal preparation. Declaration ownership alone is not execution proof.

Final unified run value-abi-root-increment-final uses candidate
12d8d8342640f67d639d8afa054541643d5138d6a34ddcaeffc0e314dc5c1724;
both compile/link/run0, exact stdout, empty runtime stderr, unchanged inputs.
Neutral w1b_root_boundaries_review independently matched all219 input SHAs,
actual outputs/current goldens, final source and candidate, approving A only.
[Exact evidence and source guard audit](../../../evidence/performance-regression-history/value-passing-implementation/stable-root-boundaries/validation.json).
Unproved named roots conservatively return false in the common predicate;
missing required production origins remain InvalidBindingOrigin. Existing
inout/unique/borrowed role controls and the early guards remain unchanged.
New test syntax/index setup errors were corrected, not counted as product RED.
This is existing-contract coverage, not a new product optimization or timing
claim. Next execute increments B and C, then full finite reconciliation.

## Remaining Increment B (validated)

mid_stable_result_homes uses real File source, finalized real BodyInstance and
MidExecutableRequests normal pipeline. It asserts completed generic/getter
producer homes through call/aggregate consumers, exactly one producer per
occurrence, pending recipes, concrete prepared owner/String field/projection
types and executable uses. Known/generic unique-owner field reads retain
marked-role snapshots and verify actual prepared unique type without inferring
copyability from metadata. stable_result_home_evaluation checks getter/producer
counts, old values across replacement, stored values and unique deinit once.
Field-only raw Index exclusion and normalized PriorCallResult materialization
are separate source assertions; no invalid synthetic body or new API.

Final value-abi-result-homes-final: both compile/link/run0, exact stdout, empty
stderr, inputs unchanged, same saved12d8d834...c1724 candidate. Independent
w1b_result_homes_review matched all219 current/before/after input SHAs, actual
outputs/goldens, candidate and IR/binary artifacts, approving B only.
[Evidence](../../../evidence/performance-regression-history/value-passing-implementation/stable-result-homes/validation.json).
No product source change or timing claim. C and whole-inventory reconciliation
remain open, followed by W2-W4/com-ffar.

## Remaining Increment C (validated)

value_snapshot_deinit_reentry checks user deinit during later explicit/default/
aggregate evaluation: old snapshot values, changed global values, exact cleanup
count and stable immutable-local counterpart. async_immediate_entry_ownership
checks noawait completion with managed String input, moved Resource, cleanup
before entry returns, original after-use and later await of returned Promise.
It uses supported scalar result payload; Promise[String] rejection remains
unchanged baseline unsupported behavior, not product RED or new support.

Final value-abi-reentry-async-final: both compile/link/run0, exact stdout, empty
stderr, unchanged inputs with candidate12d8d834...c1724. Neutral
w1b_reentry_async_review matched all219 current/before/after input SHAs, actual
outputs/goldens/candidate/artifacts. Source and generated IR confirm frame stores,
Borrow retain / Move transfer, caller Promise share before first resume, and
normal cleanup after immediate completion.
[Evidence](../../../evidence/performance-regression-history/value-passing-implementation/reentry-and-immediate-async/validation.json).
No product source changes. Final finite reconciliation/reruns remain open,
including async_enum_param_arc and prior local/self/field/owner controls.
