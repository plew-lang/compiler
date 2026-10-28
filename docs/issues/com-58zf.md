---
id: com-58zf
status: open
deps: []
links: []
created: 2026-10-27T20:20:53Z
type: task
priority: 3
assignee: Koji Murata
tags: [frontend, runtime, verification]
---
# Plan Buffer factory migration while preserving existing construction controls

## Finite Migration Planning Boundary

Source-only admission audit at compiler9665094d/spec5bd65a5. Exact representative inputs: tests/fixtures/panic/buffer_capacity_bytes.pw, tests/fixtures/panic/buffer_reserve_overflow.pw and tests/fixtures/run/array_drop_count.pw. They call current public assoc Buffer.new()/withCapacity(). spec02's Buffer API adopts named factories; current Core exposes assoc methods. This does not make their ordinary method-call syntax inherently invalid or their capacity/drop behavior a wrong oracle. com-p10m explicitly validates the current assoc lane and excludes absent factory migration; do not silently reopen it.

## Deliverables

Trace Buffer's defining type/module, current public construction producers, typed intrinsic/synthetic handoffs, factory publication and external call consumers. Produce a bounded migration/control plan for the two construction operations using adopted named factory syntax, retaining capacity overflow/no-change, empty count/capacity, final-owner release and current valid positive controls. Distinguish ordinary source construction from private compiler-generated construction authority. Account for current standard module ownership and generic T handling; do not bypass owner/private rules or remove legacy guards before replacements exist.

The investigation closes with concrete finite repair owners/required controls, not just a broad promise to migrate all Std. Actual changes use TDD and scoped independent review; no API/compiler/fixture edits or test executions occurred in audit. Existing com-qbwg synthetic identity and com-m0bf type-term repairs are not this API migration; met-b2la unique generic support is not automatically a prerequisite. Preserve adopted surface, ask user if a new public semantic/architecture decision is needed. Evidence frontend-batch-0002.json/runtime-batch-0088.json under meta/evidence/test-audit/scoped-reviews. Unread audit units are not transferred by this issue.


## Explicit Capacity and Field-Place Buffer Contexts

Batch0038 adds exactly run/{buffer_capacity_cow,buffer_cow_field}.pw/.out. Current Buffer.withCapacity/new associated construction differs from the adopted named-factory surface. Preserve capacity/reserve, alias independence, zero-sized unit elements, indexed insertion and mutable struct-field buffer writes/returned removal values through the same canonical construction handoff. Current public APIs are real; their use is not intrinsically invalid call syntax. This admission audit does not newly certify physical memory retirement, sanitizer execution or unread outcome obligations.

## Explicit Eight Buffer Surface Admission Roots

Batch0039 adds exactly run/{buffer_floor,buffer_index,buffer_insert,buffer_metadata,buffer_nested,buffer_removal,buffer_string,buffer_struct_field}.pw/.out. Current Buffer.new associated construction is real public API but differs from adopted named factory. Preserve empty/capacity/growth, scalar/String/nested/struct-field elements, indexing, reserve/insert/remove and logical copy independence through the canonical construction migration. This source-role intake does not certify exact memory layout, element-retirement/sanitizer outcome or all collection performance paths.

## Explicit Final Callable Buffer Field Methods

Batch0047 adds exactly run/{final_callable_generic_field_method,final_callable_trait_field_method}.pw/.out. Buffer.new is a real current public associated API differing from adopted named construction; method/inout/IndexSet receiver T propagation remains meaningful. Reconcile construction through existing finite migration without special-case Buffer type inference or declaring ordinary call syntax illegal.

## Explicit Generic Receiver Buffer Creation

Batch0051 adds exactly run/generic_receiver_indexed_eq.pw/.out. Current Buffer.new API is not intrinsically forbidden; reconcile adopted factory-based Buffer creation while preserving receiver binder substitution, nested generic Hash/Index/Eq and I64/String instances. Hash digest equality here does not prove all keys collision-free.

## Explicit Mid Buffer Intrinsic and Return Contexts

Batch0056 adds exactly run/{mid_buffer_append_cfg_lowering,mid_buffer_clear_arc_cfg_lowering,mid_buffer_clear_cfg_lowering,mid_buffer_eq_cfg_lowering,mid_buffer_insert_arc_cfg_lowering,mid_buffer_insert_cfg_lowering,mid_buffer_remove_at_arc_cfg_lowering,mid_buffer_remove_at_cfg_lowering,mid_buffer_remove_last_arc_cfg_lowering,mid_buffer_remove_last_cfg_lowering,mid_buffer_reserve_cfg_lowering,mid_buffer_set_arc_cfg_lowering,mid_buffer_set_cfg_lowering,mid_buffer_swap_remove_arc_cfg_lowering,mid_buffer_swap_remove_cfg_lowering,mid_buffer_truncate_arc_cfg_lowering,mid_buffer_truncate_cfg_lowering,mid_call_result_return_context}.pw/.out and registered IR companions. Eighteen roots use current real public Buffer.new associated construction. Preserve typed safe intrinsic append/clear/equality/insert/removal/reserve/set/truncate, current alias/drop/return-context controls through adopted named-factory migration; ordinary method syntax is not intrinsically illegal. Capacity retention for clear/truncate is current observation, not adopted guarantee; no fresh IR/runtime/sanitizer proof.

## Explicit User Collection Buffer Construction API

Batch0080 adds exactly run/user_collection.pw/.out. Stack factory uses current real associated Buffer.new(), while adopted named-factory construction differs. Preserve user-authored safe-floor operations, scalar/String behavior and copied collection divergence; generic Stack factory publication shorthand remains separately unresolved in com-owb3. This is not a ban on every constructor-like ordinary associated function.
