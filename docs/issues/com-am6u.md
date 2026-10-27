---
id: com-am6u
status: open
deps: []
links: []
created: 2026-10-27T02:15:37Z
type: task
priority: 1
assignee: Koji Murata
parent: com-jno0
tags: [verification, tooling]
---
# Inventory compiler API inputs by responsibility

## Scope and Actions

Inventory production compiler APIs across frontend, source/dependency admission,
Mid/async/ownership, backend/native bridges and driver/session execution. Include
functions and struct constructors in compiler sources and production support
code; classify generated/third-party code separately. Standard-library APIs and
new language features are not the target.

For each API family record its intended responsibility, actual caller, passed
values and reachable capabilities (fields, captures, globals or broad context
objects). Identify the API's legitimate required inputs. The question is whether
an API receives information or operations outside its responsibility, not whether
every algorithm in its implementation is correct.

Use architecture and the corresponding domain design chapters to partition the
inventory. Pin input revision and identify omitted/unclassified entries. Prepare
finite audit batches for com-mmk9; split batches exceeding roughly one or two
active human working days before executing them. Do not limit the inventory to
one semantic subsystem or an existing implementation project.

## Completion

A reproducible API/constructor inventory, explicit coverage/exclusions and sized
batches have independent review. This task is discovery/planning, not a compiler
repair, conformance certificate or implementation-milestone prerequisite.
