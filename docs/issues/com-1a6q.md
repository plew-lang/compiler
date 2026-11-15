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
