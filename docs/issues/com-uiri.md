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
The deeper [Swift study](../../../evidence/performance-regression-history/swift-abi-deep/README.md)
and its implementation work packages supersede a transport-only interpretation.
Carry authored mutability/storage facts to Mid and settle redundant semantic
snapshot selection before ownership/drop verification; late LLVM planning must
not erase semantic owners. Use one root/interval/projection predicate rather
than separate heuristics for let, self and temporary spellings. Include admitted
immutable globals and static value-field composition when their existing root
evidence is available; do not cross a reference/accessor boundary by inheritance.
Its investigation closure is not ABI adoption: obtain the explicit decision
required there before beginning product edits. Prototype the shared signature
descriptor and typed Value/Home carrier, caller materialization/callee binding,
and forwarding of contracted incoming homes, completed dedicated temporaries or
ordinary immutable locals under the finite storage proof in that proposal.
Use declared mutability as an existing fact, not a new effect-analysis query.
Include immutable-local direct forwarding and a constant shared handle with a
mutable referent as distinct controls; the latter cannot prove referent stability.
Preserve semantic borrows and consuming/inout lanes. Reconcile every common
helper user through that protocol or an explicit adapter; do not ship a
direct-call-only ABI. Split implementation units before coding if this migration
cannot remain reviewable, retaining one end-to-end acceptance boundary.

After the preceding design decision and any required approval, implement only its bounded prototype. Read [implementation and performance checks](../../../agents/development-workflow.md#実装と性能の確認事項). Record the chosen revision, evidence predicates, ABI lane owner, included entries and fallback boundary before editing product code.

Preserve by-value semantics, evaluation/snapshot order, ARC and deinit boundaries, source-place stability, escape/async acquisition and consistent caller/callee signatures. Natural methods and value APIs remain intact. Do not infer safety merely from immutable bindings or single-thread execution.

## Scenarios and TDD

Derive concrete tests from the design matrix before implementation: stable read-only forwarding/recursion; mutation through later arguments or callbacks/shared aliases; temporary and returned owners; nested aggregate/CoW; direct and representative indirect entries in the prototype scope. New structural copy-removal assertions must fail for the intended reason on the fixed old candidate. Semantic controls may already be GREEN. Malformed/mismatched physical descriptors must not bypass applicable verification.

## Proof Obligations from Independent Design Review

- Validate origin facts against accepted SourceFacts through freeze and
  instantiation. A tag alone is not proof: distinguish authored, synthetic,
  borrowed and capture-cell storage; check initialization and readonly uses.
  Missing/forged-origin controls must exercise the production checker.
- Distinguish forwarding an already guaranteed self from acquiring the first
  copy-self home from a shared place. Cover callback, later-argument and deinit
  reentry with raw and optimized structural/semantic controls.
- Freeze a finite inventory of actual common-helper call sites and assign each
  role to the descriptor/carrier or an adapter. Measure real plan construction
  counts; a list of function families alone is insufficient.
- Include a Mid structural control retaining the authored named-local Copy while
  omitting only a redundant evaluation temporary. Preserve the associated owner
  and destruction operation rather than relying on byte transport.

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

