---
id: com-uiri
status: open
deps: [com-rv7l]
links: []
created: 2026-11-09T14:53:00Z
type: task
priority: 2
assignee: Koji Murata
tags: [ownership, backend, mid]
---
# Prototype and measure the selected value-passing design

## Guarantee and Work

The concrete recommendation and finite storage/entry matrix are in
[com-rv7l](com-rv7l.md#investigation-result-and-recommended-design).
Its investigation closure is not ABI adoption: obtain the explicit decision
required there before beginning product edits. Prototype the shared signature
descriptor and typed Value/Home carrier, caller materialization/callee binding,
and forwarding of contracted incoming homes or completed dedicated temporaries.
Preserve semantic borrows and consuming/inout lanes. Reconcile every common
helper user through that protocol or an explicit adapter; do not ship a
direct-call-only ABI. Split implementation units before coding if this migration
cannot remain reviewable, retaining one end-to-end acceptance boundary.

After the preceding design decision and any required approval, implement only its bounded prototype. Read [implementation and performance checks](../../../agents/development-workflow.md#実装と性能の確認事項). Record the chosen revision, evidence predicates, ABI lane owner, included entries and fallback boundary before editing product code.

Preserve by-value semantics, evaluation/snapshot order, ARC and deinit boundaries, source-place stability, escape/async acquisition and consistent caller/callee signatures. Natural methods and value APIs remain intact. Do not infer safety merely from immutable bindings or single-thread execution.

## Scenarios and TDD

Derive concrete tests from the design matrix before implementation: stable read-only forwarding/recursion; mutation through later arguments or callbacks/shared aliases; temporary and returned owners; nested aggregate/CoW; direct and representative indirect entries in the prototype scope. New structural copy-removal assertions must fail for the intended reason on the fixed old candidate. Semantic controls may already be GREEN. Malformed/mismatched physical descriptors must not bypass applicable verification.

## Measurement and Completion

Run representative snapshot/alias/ownership controls through both raw
unoptimized and optimized ABI paths, as required by the representation contract.
If an optional Mid transformation is introduced, also compare its enabled and
disabled behavior under the pass contract.

Build a fresh candidate; show final optimized LLVM/machine-code transfer changes, not only ARC/dump counts. Compare old/new candidates on the identical latest source with fixed pipeline/generation and balanced repeated samples. Measure the probe runtime and compile-time/analysis/code-size costs; keep these separate from the formal fixed-point median. Apply existing validation/stop rules without treating failed local ideas as proof of repair difficulty.

Independent correctness/performance review determines whether the prototype is safe, materially useful and maintainable. Record results and a go/no-go recommendation. A failed or unhelpful prototype may close as investigated after reverting product experiments and recording why; downstream integration must then be explicitly deferred or revised, not run automatically.

## Exclusions

On no-go, explicitly defer integration and follow
[com-1hd3's return procedure](com-1hd3.md#interruption-checkpoint-and-return-procedure)
from this task before choosing further work.

No blanket ABI rollout, new source feature, broad effect-analysis project, main/seed promotion or claim that com-1hd3 is repaired. Temporary implementation limitations must have an owned removal condition. Conservative snapshots required by unknown effects or other safety conditions are part of the valid design, not debt that must be removed.

