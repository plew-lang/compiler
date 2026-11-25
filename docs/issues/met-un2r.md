---
id: met-un2r
status: in_progress
deps: []
links: []
created: 2026-11-25T20:13:58Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-yeua
tags: [frontend, diagnostics, verification]
---
# Retain authored type visibility refusals through owned consumers


## Contract and finite scope

Preserve the actual authored missing-import type-visibility refusal from
Codegen/Check/Visibility.checkTypeName through its owning declaration/body
consumer and any relevant failure cache. Existing five roots are
reject/{ordering_needs_import,use_type_without_import_localval,
use_type_without_import_newtype,use_type_without_import,
private_extern_generic_type_not_ambient}. Source semantics, message/status and
lazy body demand remain unchanged. Parent com-yeua is not closed by this child.

## Investigation before implementation

Trace each fixture through declaration or requested-body entry, actual
FrontendDeclarationOrigin or body request, Lower occurrence/scope/role, failure
cache (if any) and final adapter. Public type term and loaded offset do not prove
source provenance. Verify actual immutable Lower registration and term/site/scope
correspondence, including mutated/forged/foreign occurrences. Shared term identity
must not lend another occurrence's permission; term-keyed normal cache is not
new Source authority.

Actual refusal means unavailable in the use module while a matching name exists
in another loaded module. It does not select a canonical declaration. Preserve
module/name/alias and actual query outcome; do not turn a first global match into
successful binding or infer domain from text. Keep Raw gen whole-pool walk Raw.

## Scenarios and completion

- Fixed f329fa419735 carrier check/AOT/ORC RED for five existing roots; distinguish
  declaration-wide refusal from demanded local annotation and unused ORC.
- Normal explicit type import/alias, ambient type and lexical binder; unknown
  name/projection failures remain their own producer domains.
- Real declaration and body origin, newtype/extern/local/closure/global relevant
  sites, shared term/different occurrence, Raw/synthetic/malformed/foreign scopes,
  retry/drain/failed owner where relevant and final owning adapter.
- Actual producer owns typed refusal; private retained evidence and consumer
  validate identity without rescanning/reselecting. No successful type/binding
  fabricated for a negative result. Missing provenance fails closed.
- Meaningful native RED/GREEN, fresh candidate public controls, applicable
  regression/formal<=7.5s, independent guarantee and final review, saved evidence
  and bounded cleanup. Gate granularity follows development-workflow.

## Relationships and exclusions

Related com-8by9/type collection and com-0huw/module metadata API narrowing own
other inputs, not this demonstrated rejection transport. No dependency on their
whole implementation. Do not redesign name lookup, all type collection, namespace
rules, generic inference, ambient list or gen semantics. If current duplicate
semantic authority is confirmed during tracing, assign it explicitly rather than
hide it behind diagnostic classification.

## Independent plan review

qualified_member_plan accepts this finite child without confirmed overlap.
Required findings adopted above: separate declaration/body origins, retain exact
occurrence rather than term identity alone, preserve global existence as negative
lookup evidence rather than selected declaration, verify Lower registration
trust boundary. No product implementation or GREEN is claimed.

## Fixed-candidate evidence and entry trace

Actual fixed f329fa419735 results:14 intended missing-import refusals in check/
AOT/ORC have the exact message and exit1 but Unclassified domain. The unused
local-annotation ORC case succeeds without inspecting that body. Inputs remain
unchanged. [RED evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/type-visibility-refusals/red.json).

Declaration entry calls checkSourceTypeUses from
admitFrontendNominalDependencies before nominal annotation admission, carrying
FrontendDeclarationOrigin but currently dropping it at type-use checking. Body
entry comes from Record block/closure type-use sets, currently dropping
SourceRecordingScope.request before checking and relying on current owner.
SourceTypeUses is a public mutable field; signatureOccurrence currently validates
only the range. Lower-private provenance and exact occurrence ownership require
explicit tests, not assumptions from a populated scope or loaded offset.
Implementation checkpoints below supersede the initial unconnected state; no
fresh candidate or task completion has been certified.

## WIP producer and body-frontier checkpoint

Private Lower scope/use receipts now retain only stable provenance and the
name/site query inputs. Declaration origin and body request are distinct private
entries; public/gen Raw entry points retain Raw behavior. The actual visibility
branch produces the retained typed negative event; failed body/closure/global
cache and owning consumer preserve it without another visibility lookup.

Body membership uses a private Lower frontier and the shared structural path
walker (loop wrappers retain their existing API). Direct annotation slots retain
only their locator and relevant type/occurrence fields. Block slots include the
block/index/Stmt binding; closure signatures do not force a control-shape unwrap
or walk into a nested body. The final consumer checks saved edges and slots.

Executed RED->GREEN corrections: actual declaration Source loss; typed closure
normal-lowering panic; detached Let annotation; block child replacement with
unchanged range. Latest native context passes normal typed closure, actual
Body/Closure/Global refusals, discarded builder/cache/retry and another owner.
Shared loop saved-target authority remains GREEN. Independent review confirms
these specific corrections; it has not certified the whole task.
[Checkpoint and runners](../../../evidence/rejection-domains/diagnostic-domain-implementation/type-visibility-refusals/checkpoint.json).

## Declaration frontier checkpoint and remaining work

The fresh SourceAdmission constructor enters a private construction state and
seals the session/scope/root prefix immediately after actual Lower. Raw analysis
cannot seal existing state by supplying an origin enum. Real callable registration
retains scalar root occurrence/slot locators; nominal/global registration is
collected at the trusted seal boundary. No all-slot value snapshot is created.
Private Lower recipe nodes and scalar child edges connect a registered root to
an actual child occurrence; final observers validate saved edges and slot values.

Native evidence establishes the Raw-enum escalation RED->GREEN, correct owned
Core/Ordering/Tok/newtype constructor refusals, wrong session/occurrence/event/
location refusal rejection, parameter replacement and recipe edge corruption.
The latter two invalidate both new producer events and saved consumer authority;
restoration recovers the saved original cause. Body/closure/global/cache and typed
closure controls remain successful. Independent source review found no must-fix
in this implemented portion, without certifying remaining coverage or task closure.
[Declaration checkpoint](../../../evidence/rejection-domains/diagnostic-domain-implementation/type-visibility-refusals/declaration-checkpoint.json).

### Declaration root inventory and pending gates

| Family | Current implementation / next action |
|---|---|
| Function/method, extern, requirement parameter/result/factory-error | root locators and slot readers implemented; extend dedicated source controls |
| Struct/enum fields, newtype underlying, global declared annotation | locators/readers implemented; underlying exercised, expand field/global controls |
| Implementation receiver, receiver/target arguments | implemented; actual Conform receiver/arguments/module/extension checked |
| Impl associated-type binding | implemented with authored occurrence/site/impl identity and real slot |
| Where operands | implemented with PreparedProjectionBound recipes and original scope own range; no source subject for recipe0 |
| Trait supertrait and associated bounds | dedicated private visibility recipe operands and actual pool/owner slots; view-only operands are not a complete inventory |

Actual declaration-occurrence inventory and all registered slot readers pass, including normalizations; this does not certify adversarial coverage or final gates. Private
Lower recipe edges also apply to these roots. Deferred original bound completion
must retain its registered input ownership; do not silently authorize new synthetic
registrations after sealing. Preserve any legitimate normalization correspondence
without a new semantic lookup.

Then complete Raw/forged/foreign scope, shared-term/different-occurrence and
alias/binder/unknown-type controls; all five public roots plus demanded/lazy/body
contrasts on a fresh candidate; regression/formal<=7.5s and final independent
review. Adopted f329 and whole264 baseline are unchanged. The WIP source remains
unmeasured/unadopted. Pre-Lower failures are outside this post-Lower boundary.


### Remaining-root finite checkpoint

Implementation/associated binding, original where clause and trait constraint
roots are connected. Native inventory covers real Lower occurrences plus every
registered slot, with parameter/result/factory/extern/target/predicate families.
Actual Conform receiver/argument mutation exposed a retained-authority RED;
producer and saved consumer now reject the mutation and accept restoration.
Projected newtype/struct/enum representation changes exposed three lost-root
REDs. Exact occurrence/recipe-bound nominal admission results explain those
changes without projection re-resolution. Removing the retained annotation loses
authority; restoring it recovers, and an unselected representation is rejected.

The independent reviewer found no remaining confirmed must-fix in this finite
increment. Own-bound-range checks are consistency defense, not a claimed executed
public mutation RED: individual scope bounds are private/write-once, while a
public whole-store replacement remains a distinct unexecuted concern.
[Results and runners](../../../evidence/rejection-domains/diagnostic-domain-implementation/type-visibility-refusals/remaining-roots-checkpoint.json).
Fresh CLI, missing adversarial contrasts, formal performance and whole remain
pending. Task and parent remain open; adopted carrier and 264-failure baseline
are unchanged.


### Fresh CLI and performance recovery

Fresh 18910c9e build passed. The original five fixtures pass all 15 mode
postconditions (14 Source refusals; unused ORC body succeeds). Additional old/new
controls pass 42 executions for demanded body/closure/global, explicit import,
alias, lexical binder and ambient types, with rejection messages unchanged.
[CLI checkpoint](../../../evidence/rejection-domains/diagnostic-domain-implementation/type-visibility-refusals/cli-checkpoint.json).

Formal second-generation fixed point median is 7.563479s, above 7.5. Alternating
same-source measurements give old f329 7.619205s versus new 7.517756s, all LLVM
hashes identical. This does not establish a compiler slowdown, but does not waive
the absolute ceiling. Recovery continues: 362a7480 avoids constructing empty
occurrence frontiers, which no reader can select. Native context remains GREEN;
independent review confirms unchanged guarantees. Fresh rebuild and formal
recovery are pending. [Performance checkpoint](../../../evidence/rejection-domains/diagnostic-domain-implementation/type-visibility-refusals/performance-checkpoint.json).
