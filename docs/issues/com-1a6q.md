---
id: com-1a6q
status: in_progress
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
  in generation mode), and exposed functions seed the worklist. It interleaves
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
