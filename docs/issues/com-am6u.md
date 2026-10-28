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
contains148 independently accepted thin factual families across entry, source,
package, host, context/loader and common auxiliary boundaries. Exact primary
ranges and any paired header/construction ranges are retained; a listed file
never certifies the whole file. Declared/default/implicit constructors, real
callers and forwarded state are included. In particular, Comp construction's
nested session-ID allocator reads/writes a module global and can panic on ID
exhaustion; the factual record retains this hidden input/effect without labeling
identity allocation a compiler defect.

Eight small LLVM helper records are independently accepted, including distinct
entry/runtime/helper/type/capture/C-ABI/numeric-sign/resume input categories.
Readonly receiver access, inout record updates and raw-handle pointee operations
are distinct capabilities. Repeated member-call locators supplement actual typed
category contexts; they are not a resolved binding graph.

Six native LLVM and one module-path family are independently accepted.
Native lookup preserves first-execution source preparation; nullable failure
latches and production global LLVM-option inputs have actual callers recorded.
The build-support/owner records add11 accepted families; with the resource
emitter, all17 production-support files have exact factual input records.
Nine routing-only source texts add one zero-owned-API family; their child APIs
remain separate targets. Distinct standard-runner IO/control consumers of the
process supervisor are included without certifying fixture/monitor algorithms.
Three frontend adapter families and one Mid ownership-request family are also
independently accepted. The facts retain source-owner literal contexts, keyword
cache writes, syntax/origin allocation and the distinction between full Comp
verification authority and Mid-only drop construction.
Nine Ir declaration/index/evidence/input families are independently accepted
with eight complete part sources and exact paired nominal ranges. Key/default
construction, array versus owner-pool inputs, prepared bindings and worklist
provenance have real caller categories. Full Arena/Decls grants remain distinct
from the few collections actually used; no final capability verdict is implied.
Five additional Ir publication/serialization/module families are independently
accepted, including actual source-public/reexport consumers and the distinct
zero-based method bucket versus one-based associated/supertrait row selectors.
Eight type/body/final-call/name-store families are also independently accepted;
actual phase readers, bodyless signature defaults, scalar recipe keys, numeric
builder bounds and authored/default/provided/extern row constructors are retained.
Three small nominal/LLVM adapter families are also independently accepted,
including direct/generated name spans, indirect declaration-cache/emission
metadata writes and local/access-token storage construction.
Five primitive/cache/interner-value/service families are independently accepted.
Ir versus Toml bindings, forwarded inout arrays, Comp member defaults and the
full Comp grant versus bytes/interner-only accesses are explicit; same-shape
caller domains do not require algorithm-by-algorithm certification.
Thirteen type/local, semantic-descriptor and storage-root families are also
independently accepted. Actual partial clones and field defaults remain explicit;
Arena zero-argument versus Decls public memberwise construction is distinguished.
Bound-store receivers, row producers and nested data defaults are recorded without
converting data presence into semantic success.
Eleven cursor/environment, source-node and declaration descriptor families are
also independently accepted. Cursor registry selectors, metadata-only closure
inputs, partial environment constraint forwarding, origin predicates, child
ranges and default-generator identities are explicit. A one-line caller extent
omission was corrected and independently reaccepted; no product change occurred.
Five trait/proof/conversion value families are also independently accepted.
Table-domain identity, substitutions, recursive proof values and partial witness
construction defaults are explicit. A missing partial-constructor caller was
added and independently reaccepted; data construction is not proof admission.
Eight frontend pool/type/navigation/view families are independently accepted.
Actual child-store/counter/name/type effects are separated from full Comp grants;
pure metadata helpers and Mid external-module forwarding remain explicit.
Caller/delegate citations were corrected and independently reaccepted.
Seven import/diagnostic/trace/leaf and preparation-value families are also
independently accepted. Exact effects, construction visibility/defaults and
private snapshot readers are retained without claiming successful publication.
Two syntax/owner/root/declaration-property query families are independently
accepted; metadata observation does not imply semantic or session admission.
Four private proof/interface metadata constructor families are independently
accepted, including outer Ref-backed cell retention and explicit owner data.
All other targets remain inventory work. The full199-file/273-segment routing
still applies; accepted family counts are not a denominator for API/algorithm
correctness. SCOPE-1/2 have a locally validated record method but remain globally
open until every target family/input is reconciled. This task stays in_progress;
com-mmk9 capability judgments and repair implementation are not completed.
