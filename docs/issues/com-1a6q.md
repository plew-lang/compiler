---
id: com-1a6q
status: open
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

