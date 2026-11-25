---
id: met-wp9l
status: in_progress
deps: [met-u9uu, met-uy77]
links: []
created: 2026-11-24T05:14:39Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-eqw2
tags: [frontend, diagnostics]
---
# Classify qualified declaration members before value admission

## Contract and boundary

Establish argument-independent qualified member category and canonical declaration
set before refusing callable declarations as values. Reuse receiver/view/module/
visibility discovery, not empty-argument applicability or typeHasAssocFn Bool.
Preserve structural fields, assoc values, namespace globals, lexical precedence,
normal invocation and instance/static distinction. Missing/private members and
view/proof prerequisite failures remain distinct. Retain real Lower operation,
owner and negative category through cache to the owning final consumer.

Named declaration transport is [met-5vgp](met-5vgp.md); namespace/type-binder
prerequisites [met-u9uu](met-u9uu.md) and [met-uy77](met-uy77.md) are closed.
Successful binding-reader migration and broader findMethod redesign belong to
[com-tr3a](com-tr3a.md), not this finite refusal repair.

## Implementation decisions

- Shared nominal/trait/interface name cursors retain canonical declaration or
  requirement identity and category. Normal calls alone select labels, defaults,
  types, rank and ambiguity. Label-mismatching calls must not gain proof queries.
- A declaration group is not an applicable call. Retain matching inherent
  receiver patterns, conditional groups and incomplete generic alternatives;
  never invent arguments or select by expected function type. Bound/view/provided
  surfaces retain their actual admitted proof. Bounds/views keep their own
  prerequisite admission before category recording.
- Preserve complete trait instances, intermediate proof-path keys and distinct
  source/fallback families. Dedup only identical declaration/proof identity;
  argument-free family preference cannot discard alternatives.
- Any alternatives use the admitted bound interface and canonical ancestor/slot;
  they do not fabricate existential self-conformance or executable witnesses.
- Record checks actual storage first and derives Field/receiver internally.
  An opaque journal seals source operation, session/root/owner and actual group.
  Consumers take its index, not a caller-supplied group or a new lookup result.
  Raw/foreign/malformed/synthetic expressions cannot gain Source authority.
- Namespace and assoc-value rewrites preserve their existing origins. Authored
  dotted view members use real Lower Field receipts and prefix spans. Synthetic
  fields remain untrusted. Migrated value-Field Bool authorities are removed.

## Guarantees and executed evidence

[Saved native/CLI evidence and runner](../../../evidence/rejection-domains/diagnostic-domain-implementation/member-declaration-admission/)
records immutable inputs, expected failures and actual results. Earlier discovery
and label-frontier poison controls remain in
[reader evidence](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-qualified-member-discovery.json).

- Native:16 positive surfaces,5 negative boundaries and actual function storage.
  Incomplete/MultiTrait/Families/Bridge assert unresolved alternatives, exact
  instance filtering, family retention and intermediate witness keys directly.
  Kind/serial/span/operation/session/root/owner, synthetic/raw/forged admission,
  failed builder, retry and another cursor are checked through retained failure.
- CLI:108 check/AOT/ORC modes pass on the fresh candidate, including associated,
  instance, lexical-bound and Any members; function/global/closure owners;
  overloads/views/newtype inheritance; namespace globals/aliases/lexical binders;
  ordinary calls and unused ORC bodies. New unpassed NewtypeOwn used forbidden
  newtype impl and was removed; inherited behavior remains with an underlying cast.
- Fresh whole build20261125T153718-build-7e8d15 passes with immutable inputs;
  all200 product source files match a09c05e1. The first whole build caught a
  removed pub impl boundary; restoring it preserves existing public APIs.
  Independent source comparison found no other visibility changes.
- Independent source/guarantee review found no remaining mandatory scenario or
  confirmed design defect, excluding outstanding formal/whole gates below.

## Remaining completion gates

Formal run20261125T154512-self-host-889dad passed with immutable inputs, generation2
LLVM/runtime/successor binary fixed point and3-run median7.350999s (<=7.5s).
Whole regression comparison20261125T160113-test-e49efb is running against the
recorded282-failure baseline. Reconcile new differences and obtain independent
final recognition.
Do not count inherited failures as new regressions or claim the whole suite green.
This task and its parents remain open until their respective guarantees close.
