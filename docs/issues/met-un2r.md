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

## Next mandatory unit and remaining gates

Declaration role/scope/frontier membership alone is insufficient: still seal
actual declaration slot binding. The independently accepted location is the
real SourceAdmission constructor immediately after Lower completes, before
nominal admission. Seal private Lower receipt to registered declaration slots;
do not seal a caller-populated Raw Comp or let a later origin enum manufacture
permission. Consume saved declaration identity/slot bindings without a rescan.
Preserve correspondence through any intervening legitimate normalization.
Pre-Lower failures are outside this post-Lower missing-import boundary.

Then complete Raw/forged/foreign scope, shared-term/different-occurrence and
alias/binder/unknown-type controls; all five public roots plus demanded/lazy/body
contrasts on a fresh candidate; required regression, formal<=7.5s and final
independent review. Current adopted f329 carrier and whole264 baseline are
unchanged. The WIP source is not an adopted compiler and remains unmeasured.
