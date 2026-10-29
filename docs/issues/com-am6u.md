---
id: com-am6u
status: closed
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

## Discovery Candidate and Scenarios

At compiler ac0ac083 / meta52d02657, the source-only
[inventory candidate](../../../evidence/compiler-api-audit/README.md) classifies
all6327 tracked paths and assigns199 production/source-support files /82074lines
to273 finite source-family ranges. Every included line is assigned once;
API markers and lexical reference locators are not a resolved call graph or
completed capability judgment. Hidden zero-API stub, memberwise/default factories,
native RAII/captures, generated C runtime and generated resource API obligations
are explicit. The snapshot is pending independent coverage/applicability review.

Discovery scenarios: exact tracked-file classification; hidden/zero API files;
Plew fn/factory/record/default/extern contexts; C++ headers/private RAII/lambdas;
Python functions/classes/lambdas and shell ambient environment; runtime/resource
source templates; resolver/product CLI/build-support entries; third-party,
standard-library and generated artifacts; actual caller/indirect-state traversal
and finite splitting when primary line bounds understate the work. Any missing
actual caller/required-input evidence remains pending, not silently completed by
locator counts. No compiler/source/test/expectation/runtime/binary modifications
or product execution. Current dirty binary and caches are preserved.

## Independent Inventory Review and Required Continuation

[Contract-first scope review](../../../evidence/compiler-api-audit/review-inventory-scope.json)
accepts the exact tracked-file classification, target source hashes, hidden stub,
generated templates, exclusion grounds and complete line routing. It does not
accept inventory closure. Parent adopts both evidenced omissions:

- SCOPE-1:600-line chunks are coverage segments, not semantic API families.
  Replace placeholder responsibility/caller/value/capability/required-input
  instructions with thin factual records for each real API family; preserve
  individual unresolved caller identities rather than claim a resolved graph.
- SCOPE-2:record rough caller/context traversal size per family, not merely
  primary line counts, and split oversize work before audit execution.

These requirements are now fulfilled for the pinned inventory, as recorded below.
No compiler repair or product execution was part of this task.

## Outcome and Next Boundary

Closed as investigated. [Inventory acceptance](../../../evidence/compiler-api-audit/inventory-acceptance.json)
adopts the exact final reconciliation and independent full review: 199 unchanged
source/support files, 82,074 primary lines assigned once, 1,504 factual families,
185 individually adopted reviews, 17,522 source contexts and 1,195 exact reused
delegate snapshots. All 5,570 routing locator occurrences have an owned primary
range; locators are not a resolved semantic call graph.

SCOPE-1/2 are closed for factual discovery, including typed caller/supplied/default
inputs, receiver/capture/global reach, required inputs, constructor/generated API
boundaries and finite traversal estimates. The final review supplements three
recursive/fixture-only routes whose caller arrays must not be interpreted alone.
The resource provider rough-line counter has a documented nonblocking emitter/header
distinction; exact ownership includes both. Required corrections remaining: zero.

The [family reconciliation](../../../evidence/compiler-api-audit/family-reconciliation.json)
and [guide](../../../evidence/compiler-api-audit/README.md) own exact source,
facts/review hashes and local limits. Baseline compiler source is 9665094dcec8aa63ed20573b1306a0015058f595;
all 199 source/support bytes remain unchanged. Existing dirty compiler binary and
caches were preserved. No product build/test/native/JIT/runtime/performance execution
or source/expectation repair was performed.

[com-mmk9](com-mmk9.md) consumes these records for capability judgments and finite
follow-up ownership. This closure is not capability sufficiency, compiler algorithm
correctness, repair completion, GREEN, or an implementation milestone.
