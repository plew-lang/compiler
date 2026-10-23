---
id: com-qehq
status: closed
deps: []
links: []
created: 2026-10-23T10:41:58Z
type: task
priority: 1
assignee: Koji Murata
parent: met-ucze
tags: [frontend, verification]
---
# Reconcile the eight current callable paths and remaining closure sites

## Boundary

Phase 3B / B0. **Bounded investigation; no source edits.** Parent criteria: 3, 4, 8.
This is a bounded child of [met-ucze](met-ucze.md); the
[execution policy](met-si6j.md#bounded-task-policy) applies. Active human effort
is intended to fit about 1–2 working days; an unknown repair is not implicitly
included. Split or block a newly evidenced larger repair before widening this task.

## Entry and Action

Entry points: `src/Codegen/Resolve/Record.pw`; `src/Codegen/Check/Generic.pw`; `src/Codegen/Verify/Call.pw`; `src/Codegen/Mono/Call.pw`.

Produce exactly eight path rows: ordinary, method, factory, operator, protocol/iteration, try, inherited/provided adapter, dynamic/interface. For each follow its Record producer, saved CallTemplate/constraint/result IDs, instance environment, actual callee/Mid/LLVM consumer, replaced selector and current control. Reconcile old met-ucze checkpoints against current code once; do not treat every old WIP as pending.

## Exit and Evidence

Every row has exact functions, current evidence revision and a disposition: already closed with applicable evidence, a named missing proof/control, or a specific defect. Assign each residual to B1/B2/B3/B4 or a new bounded repair child and its real dependency. Publish the table in met-ucze; no anonymous remaining path. Closing this investigation does not close the assigned repairs.

Existing starting controls: `source_call_proof_boundary`, `source_call_constraint_evidence`, `source_operation_owner_storage`, `default_argument_call_templates`, `dynamic_call_template_generic_instances`

Record actual functions/removed paths, implementation revision, tested input and
carrier hashes, decisive result/receipt and remaining scope here. Do not infer
current success from this plan. Existing successful evidence can be reused only
with matching scope/inputs. Full final-candidate gates are G2a/G2b; no gate is
waived by a bounded child closing.

## Outcome

Investigated at **4c78bb38**, source/fixtures equal **09e5a277**. The
[eight-row reconciliation](met-ucze.md#current-eight-path-reconciliation)
records exact producers, saved identities, instance environments and final
Mid/LLVM consumers. The
[static receipt](https://github.com/plew-lang/meta/blob/main/evidence/existing-feature-conformance/source-owner-facts/phase3b-call-path-inventory.json)
pins inspected source/control hashes and the unchanged saved candidate. No
compiler, test or performance process was run for this investigation.

The first concrete residual is the live free-call Verify name rescan in
`Verify/Call.pw::checkCallArgCategories`, owned by B1. B2/C4 retain the
operator zero-result/projection closure; B3 retains clause/ParamId/physical-Self
and provided-proof completion; B4 retains universal versus concrete interface
proof admission. D2/D3 and C6 own the explicitly linked source-domain, writer
and descriptor boundaries. Existing source/final call handoffs are preserved,
not scheduled for reinvention. Every row has a required owner; no new repair
bucket or unassigned path was added.

Closing B0 means its finite inventory is complete. It does not close B1–B4,
the selection epic, other phase-three areas or final-candidate gates. Next:
B1, beginning with removing the competing free-call Verify selector while
retaining complete selected-signature validation.
