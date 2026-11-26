---
id: met-un2r
status: in_progress
deps: [com-p2qh]
links: []
created: 2026-11-25T20:13:58Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-yeua
tags: [frontend, diagnostics, verification]
---
# Retain authored type visibility refusals through owned consumers

## Contract and scope

Preserve the actual authored missing-import refusal from
Codegen/Check/Visibility.checkTypeName through its declaration/body owner,
failure cache and final adapter. Keep Source semantics, diagnostic/message/status,
module/name/alias behavior and lazy body demand. A matching globally loaded name
is negative lookup evidence, not a selected canonical declaration. Raw gen walks
remain Raw; rendering text cannot grant Source authority.

Existing roots are reject/{ordering_needs_import,
use_type_without_import_localval,use_type_without_import_newtype,
use_type_without_import,private_extern_generic_type_not_ambient}. This finite
repair does not close com-yeua, repair all type collection, change inference or
namespace rules, or certify main/seed adoption.

## Implementation and authority

- Actual Lower privately registers stable scope/use receipts and scalar recipe
  nodes/edges. Public SourceTypeUses terms, offsets, scopes and recipes alone
  cannot mint an owned refusal. Query head/site/role and real occurrence must
  match; matching semantic types do not exchange permission.
- Only fresh SourceAdmission construction enters the declaration construction
  state. Actual Lower completion seals the session/scope/root prefix. Raw caller
  state cannot acquire authority by supplying an origin enum later.
- Declaration roots retain narrow callable/nominal/global/implementation/where/
  trait operand locators. Real slots, ownership and registered recipe paths are
  checked at production and final observation. Function, extern and requirement
  owners are separate; scope kind alone is not a root inventory.
- Actual Conform receiver/arguments/module/extension must match the Lower-bound
  implementation owner. Legitimate nominal receiver and field/enum/newtype
  representation changes use existing occurrence/recipe-bound normalization
  records, without semantic lookup or projection re-resolution.
- Where roots bind to the original clause's own scope range. Deferred completion
  can register only an original sealed clause/scope, not a new synthetic input.
  Own-range checks are consistency defense: no executed direct public mutation
  of the private/write-once scope.bounds field is claimed.
- Trait constraint operands have dedicated private visibility recipes. Existing
  view-only bindings omit plain nominal arguments and are not a complete root
  inventory. Synthetic subjects and trait heads gain no invented occurrence.
- Body recording carries its real checking request. Private annotation slots
  retain their block/index/Stmt or expression binding; shared control paths do
  not walk nested closure bodies as if owned by the parent. Empty occurrence
  rows are not stored because no reader can select them.
- The actual refusal branch creates a private typed negative event. Failed
  body/closure/global caches preserve it. The consumer checks retained identity,
  path, slot and recipe evidence without repeating visibility lookup; owner
  relationships are sealed while the builder exists, not recovered after failure.

Related com-8by9 and com-0huw retain their own broader inputs. The independent
physical writable-path input repair was split into dependency com-p2qh and is
closed; remaining com-0t9x APIs stay outside this task.

## Coverage and decisive evidence

Fixed f329 check/AOT/ORC establishes 14 intended refusals with correct messages
but Unclassified transport; the unused local-body ORC control succeeds.
[Initial RED](../../../evidence/rejection-domains/diagnostic-domain-implementation/type-visibility-refusals/red.json).

Meaningful native RED->GREEN includes Raw-enum declaration escalation, typed
closure lowering panic, detached local annotation/block child, actual Conform
receiver/argument mutation, and lost projected newtype/struct/enum roots.
Setup/compile mistakes are not counted as REDs.

| Guarantee | Executed controls |
|---|---|
| Real owner and cache retention | Function/Closure/Global, builder disposal, retry, another owner, owning adapter |
| Private origin and saved identity | Raw/synthetic registration, query-head mismatch, foreign session/event/location, changed parameter and recipe edge, restoration |
| Declaration coverage | Actual Lower occurrence inventory and every registered slot; parameter/result/factory-error/extern/field/payload/newtype/global/impl/associated/where/trait operands |
| Representation correspondence | Three nominal normalization families, removed/restored retained annotation, unselected representation refusal |
| Producer request boundary | Real Body/Closure recording with correct/Raw/foreign-session/wrong-global-root/other-function request; invalid requests mint zero events |
| Occurrence separation | Two real occurrences of the same semantic type reject exchanged site/ID/owner and accept the peer's own request; same numeric ID reuse is separately tested as public synthetic registration, not claimed as a natural real-Lower fixture |
| Public transport and noninterference | Original CLI15; old/new normal import/alias/binder/ambient and demanded body/closure/global42; declaration roots78; parameter/field default12; measured and saved carrier CLI15 each |

Native probes are private same-module templates, documented in the frontend
README; they do not expose production authority constructors.
[Body checkpoint](../../../evidence/rejection-domains/diagnostic-domain-implementation/type-visibility-refusals/checkpoint.json),
[declarations](../../../evidence/rejection-domains/diagnostic-domain-implementation/type-visibility-refusals/declaration-checkpoint.json),
[remaining roots](../../../evidence/rejection-domains/diagnostic-domain-implementation/type-visibility-refusals/remaining-roots-checkpoint.json),
[completion controls](../../../evidence/rejection-domains/diagnostic-domain-implementation/type-visibility-refusals/completion-controls.json).

## Final validation and review

Product source e27ce3e5 is byte-identical across all205 live/frozen source files.
Formal 20261125T223423-self-host-f967b6 reaches G2 fixed point with unchanged
inputs; samples7.915713/7.361221/7.343559s, median **7.361221s <=7.5**.
Measured compiler ff4a21a5861e38058f4e870571c4cb6c79d73bae4a011a28501409f745ac0d80
is saved with identical frozen std at bin/carriers/ff4a21a5861e/plewc.
The earlier7.563479 ceiling miss was addressed, not waived; optional recipe
indexing without demonstrated gain was removed. com-p2qh's exact-input repair
has matching LLVM and same-source7.506094->7.289006s evidence.
[Formal and transfer evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/physical-write-path-inputs/checkpoint.json).

Whole 20261125T225114-test-caf022 completes with unchanged inputs and no worker
infrastructure failure. All3313 cases and source hashes match f4334c: no new or
removed cases, no skips, no new failures or changed remaining reasons;
**264->259** resolves exactly the five target rejects. Exit1 and the remaining259
failures are explicit; this is not all-green/main/phase-three certification.
[Whole reconciliation](../../../evidence/rejection-domains/diagnostic-domain-implementation/type-visibility-refusals/whole.json).

qualified_member_plan independently reviewed producer-to-final-consumer coverage,
corrected its unproven public-bounds-mutation classification, required and then
accepted the request/occurrence controls, and certifies this finite repair
technically closable after whole/formal reconciliation. No mandatory guarantee
or confirmed code violation remains. Publication precedes status closure.

163 regenerable diagnostic outputs (5.164GiB) are retired after retaining hashes,
IR boundary excerpts, terminal records, runners, RED logs and source/std/manifest
inputs. Keep latest whole259 payloads, frozen e27, formal G2 materials, comparison
inputs/binaries and f329/ff4 carriers through parent com-yeua reconciliation;
then recheck each retention purpose. The opaque native backend archive and user
Plew.toml/bin/plewc were not touched.
[Retirement](../../../evidence/rejection-domains/diagnostic-domain-implementation/type-visibility-refusals/retirement.json).
