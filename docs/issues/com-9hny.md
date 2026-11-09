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
