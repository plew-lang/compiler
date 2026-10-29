---
id: com-am6u
status: in_progress
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

These are remaining inventory work under this task, not compiler repair tasks
or reasons to defer unread APIs as findings. No task scope, stopping rule or
specification changed. Inventory is in_progress; com-mmk9 is not yet started.

## Factual Inventory Progress

The [family reconciliation](../../../evidence/compiler-api-audit/family-reconciliation.json)
contains1259 independently accepted thin factual families. It owns exact primary
ranges, source hashes, facts/review hashes and acceptance limits. A listed source
path does not certify its whole file; metadata construction, successful admission
and execution publication are distinct. The [evidence guide](../../../evidence/compiler-api-audit/README.md)
links the accepted source/caller/input records. All199 target source/support
hashes remain unchanged from the inventory baseline; product execution/repair
has not been performed.

Accepted facts retain actual typed callers, supplied/default/forwarded values,
full receiver grants versus fields/delegates used, captured/retained references,
nonlocal host inputs and required inputs. Important distinctions include the
Comp default's module-global session allocator, Ref-backed prepared payloads,
owner-provenance versus current cursor selection, private/public construction,
and file-loading package/lock/shell observations outside SourceAccess.
Missing caller shapes, direct effects and imprecise wording found in independent
reviews were corrected and reaccepted at exact candidate hashes.

Other targets remain inventory work. The full199-file/273-segment routing still
applies; accepted family counts are not a denominator for API/algorithm
correctness. SCOPE-1/2 remain globally open until every target family/input is
reconciled and independently reviewed. This task stays in_progress; com-mmk9
capability judgments and repair implementation are not completed.
