---
id: com-1a6q
status: closed
deps: []
links: []
created: 2026-11-15T03:14:30Z
type: task
priority: 1
assignee: Koji Murata
parent: met-si6j
tags: [frontend, generics, mid, ownership, verification]
---
# Map final dependency collection to checked body operations

Inventory the dependency discovery paths rooted in scanBlockInsts and their handoffs to executable publication. Identify where finalization reads checked facts, where it reconstructs work from source structure, and where a concrete instance or Mid cleanup supplies new information. Define bounded migration tasks from those findings.

## Design

Use [Frontend Handoffs §8](../design/frontend-handoffs.md#8-implicit-calls-and-reachability), [Generics §5](../design/generics.md#5-discharging-saved-obligations), and the [Mid cleanup contract](../design/mid.md#scope-and-cleanup-information). Cross-check the closed coordinator audit com-nd29 and input-boundary repairs com-e6zm and com-j2oe. Keep those scopes intact. This task inventories and assigns work. Product changes and a decision to add an index are outside its scope.

## Acceptance Criteria

Publish an evidence-backed map from producer through final consumer for direct and trait calls, closures, globals, layout and destruction. Name each entry point, the checked facts it consumes, concrete-only decisions, and pre-Access versus executable-publication guarantees. Include AOT and lazy entry, generated bodies and adapters where applicable, argument evaluation that exits before a selected call, and conditional cleanup or replacement. Assign each confirmed gap to an existing ticket or a bounded new task with the old path to retire, positive and negative controls, and real prerequisites. Identify the first end-to-end migration and how to compare same-source output and performance. An independent review must check coverage and dependencies before closure.

## Entry and publication map

- AOT and generation: `Frontend.finalizeFrontendExecutableRequests` enters
  `completeFinalCallables`. Selected globals, the entry (the generated harness
  in generation mode), and exposed functions outside generation mode seed the
  worklist. It interleaves
  `requestFinalBody` with `advanceFinalDependencies` before publishing.
- Lazy: `CheckedProgram.prepareBodyInSession` requires a registered signature,
  requests declaration analysis, then uses the same `requestFinalBody` and
  publishes descriptors after closing the dependency frontiers. Its Access
  preparation can request more Mid bodies when effect analysis needs them.
  Descriptor cache hits do not establish executable readiness.
- Shared body scan: `requestFinalBody` memoizes the outcome per body ID and
  restores the caller's cursor. Ordinary functions enter their concrete
  environment before scanning. Newtype adapters use `finalizeNewtypeAdapter`
  instead of an authored block.
- Globals enter through a selected declaration target. The frontier prepares
  the initializer and scans its statement. The signature, aggregate, call and
  storage frontiers can add destruction requirements even when no explicit
  call in the body names them.

Direct calls are a candidate for the first migration. `scanExprInsts` still
walks arguments through `callArgumentRangeForCurrentBody` before resolving a
saved callee, registering its body and finalizing writeback. Trace the saved
argument evaluation recipe to the actual Mid call emission before choosing the
migration: a selected signature alone does not establish that argument
evaluation reaches the call. Keep this separate from the type/proof work done
for trait methods and cleanup introduced during Mid elaboration.

## Direct call handoff

- [Call.pw](../../src/Codegen/Mono/Call.pw): `resolveBodyCallee` reads the
  lexical `CallTemplate`. Its direct branch keeps the selected function,
  receiver, type arguments, and proof, builds a concrete descriptor, and
  enqueues the selected body. This is not a second source overload lookup.
  The work to remove is the argument-range reconstruction and the dependence
  of discovery on walking the source call node.
- `scanExprInsts` currently builds an AST argument range from the template
  pool, visits each argument, and then registers the enclosing call. Its
  argument loop does not use the continuation gate used for conditions.
  [Mid Build](../../src/Mid/Build.pw) instead orders template inputs by
  `evaluationOrder`, evaluates the receiver and arguments, and emits a
  template call terminator only if each input reaches its continuation.
  An emitted call to a diverging callee has a different contract from an
  outer call that was never emitted.
- This establishes a difference between discovery and executable Mid, not
  by itself a language bug. Determine which non-emitted calls still need
  descriptor, validation or effect obligations. The direct-call migration must
  preserve default-argument order, prior-call values, accessor writeback and
  synthetic call identity, and demonstrate cut-off at a noncontinuing input
  without dropping required diagnostics. Existing controls include
  `default_argument_call_templates`, `call_template_result_arguments` and
  `semantic_call_completion_boundary`; none alone proves that a non-emitted
  outer call is excluded from executable demand.

## Effect and executable-call consumers

- [Declaration access](../../src/Mid/DeclarationAccess.pw) scans reachable
  canonical Mid blocks. It reads the call template named by each emitted
  terminator, records the selected obligation, and follows non-async,
  non-extern direct declaration edges. It also records destruction obligations
  for typed places and can defer them until their recipes are concrete.
- [Mid instantiation](../../src/Mid/Instantiate.pw) maps each emitted template
  target by the full site key and body ID to its final descriptor. A missing
  descriptor fails instantiation. [Concrete global access](../../src/Mid/GlobalAccess.pw)
  follows reachable instantiated call terminators and adds destruction edges
  from typed places. Lazy Access preparation can demand a missing direct body.
  Neither traversal depends on an outer call terminator that Mid never emits.
- [FreeFn](../../src/Codegen/Mono/FreeFn.pw) additionally writes provisional
  generic registrations through `registerCallInst`. The function reads type
  arguments from the final descriptor and does not read its name or AST argument
  parameters. Keep its depth checks accounted for when changing discovery.
  [LLVM provided-function emission](../../src/Backend/Llvm/ProvidedFns.pw) does
  not use this provisional list as its body source.

A likely migration boundary is the already-built canonical Mid call terminator
and its selected site key. The prerequisite is to identify the required
pre-Access descriptor and type-recipe ordering, including concrete descriptors
read while instantiating Mid and obligations that must survive without a call
terminator. This source inspection establishes the consumer split; it does not
yet establish that the old registration may be skipped for every non-emitted
call.

## Ordering boundary for a Mid-based traversal

- [Mid Build](../../src/Mid/Build.pw) constructs the parametric authored body
  from prepared source facts and a checked signature. Its template cache is
  keyed by source function. Declaration effect collection already uses this
  cache; the AOT and lazy executable preparation paths in
  [CheckedProgram](../../src/CheckedProgram.pw) carry it forward.
  Ordinary call terminators retain the selected site key at this stage.
- [Mid Instantiate](../../src/Mid/Instantiate.pw) requires concrete call,
  storage and aggregate descriptors to produce the instantiated body. Therefore
  dependency discovery can start from **parametric** Mid operations. Waiting
  for instantiated Mid would put the descriptors after their own consumers.
- [Mid Build](../../src/Mid/Build.pw) also has synthetic body origins for
  existential witnesses and closure environment drops, and handles newtype
  adapters through established signatures and an adapter call resolution.
  These use distinct prerequisite ordering and cannot be assumed to have an
  authored parametric body keyed by source function.
- An initial direct-call slice should reuse the session's parametric body,
  demand descriptors for reached direct call sites in dependency order, and
  leave source checking and cleanup obligations intact. Verify call-result
  recipes and inout writeback before retiring any source-scan branch. For
  example, instantiation can read a call-result descriptor while resolving a
  place or local type, independently of instantiating the call terminator.

## Dependencies beyond the call terminator

- `PriorCallResult` arguments read an earlier descriptor by its selected
  site key in [Call.pw](../../src/Codegen/Mono/Call.pw). Result type recipes
  can also be consumed through [Mid instantiation](../../src/Mid/Instantiate.pw).
  A collection walk must distinguish descriptor demand from executable-body
  demand and satisfy producer descriptors before resolving dependent recipes.
  The block storage order alone does not prove this dependency order.
- `finalizeAccessWriteFacets` follows saved access uses for a parent call.
  A detached setter may itself have an inner writeback edge, which the
  current routine closes recursively. [Mid Access](../../src/Mid/Access.pw)
  reads the published setter resolution to allocate its result local and
  elaborate the operation. Collecting only explicit Mid call terminators
  would omit these dependencies.
- The first migration must therefore account for result-recipe edges and
  selected writeback edges as well as reached calls. Preserve the complete
  body/site key and existing missing-evidence diagnostics. Exercise a prior
  call result feeding another call, a nested indexed inout writeback, and a
  noncontinuing argument alongside the plain direct-call control. Assess the
  narrower input-boundary tickets separately from this discovery change.

## Remaining dependency families

| Family | Producer and consumer | Migration boundary |
| --- | --- | --- |
| Trait or existential call | The lexical template records the selected requirement and proof. `selectStaticMethodTemplateCall` applies the concrete receiver environment. Interface witness preparation publishes a distinct synthetic body with its own signature. | Keep concrete witness selection and synthetic registration in finalization. Source lookup stays closed. The initial direct-call change does not replace this path. |
| Closure | Checked captures feed `finalizeClosureSignature`; `scanFinalBodyInstance` dispatches a registered closure to its own scanner. Synthetic environment drop has its own origin and Mid builder. | Distinguish signature and capture cleanup from the effects of invoking the closure. Preserve body identity per enclosing instance. |
| Aggregate and layout | `finalizeCurrentBodyAggregate` reads the saved aggregate recipe, grounds the result and element terms and finalizes conversions. Mid instantiation consumes the resulting descriptor. | Move navigation to the typed construction operation only after its operand type recipes are ready. Evaluation-only aggregate operands still contribute their own dependencies. |
| Destruction | The signature and concrete descriptor frontiers and the body scan feed `enqueueFinalDestruction`; `collectFinalDestruction` follows concrete type and deinit dependencies. Mid Access and drop elaboration determine actual cleanup sites. | Keep type dependency closure ahead of its consumers. Validate replacement and conditional cleanup on the elaborated execution path. A source call inventory cannot cover these sites. |

Entry roots, ordinary direct calls and their recipe/writeback dependencies have
enough evidence to define the initial implementation boundary. Before closing
this investigation, reconcile the remaining rows against the corresponding
synthetic and concrete consumers, assign confirmed gaps to tickets, and obtain
independent review. Record fixture paths for the assigned slices.

## Independent review of the migration boundary

The review of compiler revision a13fe2df identified two prerequisites for the
first implementation task:

- Mid Build imports Frontend. Dependency discovery that reads parametric Mid
  must obtain a narrow operation view from the session coordinator or run at
  that boundary. The Frontend scanner cannot import its Mid consumer. Account
  for both session callers and the direct Frontend finalization entry points.
- The selected-call registration currently combines descriptor publication,
  constraint handling, and executable-body demand. Establish those obligations
  separately before replacing discovery. Tests must observe actual body demand
  as well as output, and distinguish a non-emitted outer call from a reached
  diverging callee.

The review also confirmed that ready closure literals enter the AOT body
worklist. Closure creation has no execution-effect edge to the body, but this
is distinct from whether AOT prepares its code. Related tickets com-eatt,
com-59sf, com-qb05, com-e6zm and com-j2oe carry adjacent contracts and should be
checked for overlap. Link confirmed required repairs into the final gate before
closing the inventory.

Mid instantiation also traverses stored blocks and locals beyond the CFG-reachable
subset inspected by declaration effects. Preserve descriptor consumers in that
storage or prove that pruning/remapping happens before they are read. Schedule
cross-family producers (operator, trait, default) before dependent direct
calls. Source divergence rejection fixtures are controls for admission only.
Use a proven legal source path or an internal Mid fixture to observe a selected
call whose input prevents emission.

## Residual scanner and implementation assignment

- Generation mode: `scanBindingInsts` follows the selected global binding
  and may add a global root. Keep that traversal for nested operands until
  global dependency discovery has an equivalent typed input.
- Implicit operations: operators use `recordBodyOperatorCallee`; `try`
  uses `registerTryConversion`; `for` publishes protocol slots through
  `freezeForResolution`; `await` finalizes the checked Promise and payload
  through `finalizeCurrentBodyAwait`. Defaults and formatting can contribute
  ordinary selected templates. Each remains on the residual path while direct
  calls migrate.
- Current local binding terms are installed by the lexical walk. A prepass
  cannot replace those terms with the fallback template terms without proof.
  `freezeFinalAccesses` also reads the getter and setter resolutions for
  published parent descriptors even when a parent is not emitted. Preserve
  required descriptors independently from demanding executable code.

[com-jgy9](com-jgy9.md) owns the first prerequisite: separate descriptor
publication from executable-body demand at the existing lexical points.
The later discovery task can then consume the reached parametric operations
through the session boundary. Current controls include
`mid_default_argument_result_context`, `call_template_result_arguments`,
`nested_field_array_inout` and `mid_inout_shared_writeback_pin`. A scoped
control must still observe actual body demand when a selected outer call is
not emitted.

[com-kphi](com-kphi.md) owns the first end-to-end discovery migration after
descriptor separation. The final performance gate depends on both tasks.

The source-navigation gaps confirmed for ordinary direct calls are assigned to
the two tasks above. The remaining families are accounted for as follows.

- Gen global selection remains on the existing checked binding path. The
  migration keeps this path and exercises the generation suite.
- Static trait and existential descriptors already apply retained evidence.
  Preserve those paths and use the
  [existential evidence fixture](../../tests/fixtures/run/existential_implementation_evidence.pw).
- Closure preparation stays on its existing body-origin path. Verify capture
  cleanup with [closure environment drop](../../tests/fixtures/run/mid_closure_environment_drop.pw).
- Aggregate conversion and destruction already consume saved recipes and
  concrete shapes in the paths listed above. Keep their navigation during this
  slice and run [symbolic drops](../../tests/fixtures/run/mid_symbolic_drops.pw)
  and the [drop verifier control](../../tests/fixtures/run/mid_drop_contract_verify.pw).
  Narrowing their inputs remains with com-vdp1 and com-rad4. The inventory
  establishes no mandatory separate traversal replacement for these families.

## Notes

**2026-11-15T06:30:33Z**

Investigation complete at 1fe22538 after independent re-review. Entry, synthetic, descriptor and executable consumers are mapped. Confirmed migration work is owned by com-jgy9 and com-kphi. Existing residual paths and controls remain documented above. No compiler behavior or performance was certified by this investigation.
