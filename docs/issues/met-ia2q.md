---
id: met-ia2q
status: in_progress
deps: []
links: []
created: 2026-11-23T16:04:21Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-yeua
tags: [frontend, diagnostics, verification]
---
# Retain authored index protocol selection refusal ownership


## Contract and finite boundary

Within com-yeua, carry actual failed selection of the canonical Index/IndexSet
requirement for an authored subscript through owner failure retention and the
private owned consumer to check/AOT/ORC. Preserve current acceptance, message,
location, status, inference, evaluation order and ordinary method calls.
[Operator specification](../../../spec/spec/03-expressions/12-operators.md#添字アクセス),
[body checking](../design/body-checking.md#5-selected-operations-and-evaluation)
and [diagnostics](../design/diagnostics.md) own the contract.

The refusal must originate from the completed lexical selection query, not from
a missing or context-only CallTemplate row. Keep Raw, wrong owner/session,
unknown receiver/trait identity, unperformed lookup, malformed metadata and
dependency failures unclassified/fail-closed. Do not rerun lookup in observation.

## Work and scenarios

1. Capture the real negative selection at recordUnresolvedMethodTemplate after
   performed static/member selection and failed dynamic selection. Its current
   caller differentiates CachedNonStatic/unperformed from an actual query.
   Authenticate the exact canonical protocol and the actual authored read/write
   operation using Lower provenance; public raw builders and detached write
   facets must not issue source authority. Retain required selector/argument/
   receiver identities, extending private producer evidence only where needed.
2. Propagate private request identity and retained negative evidence through
   function/closure/global failure caches into the existing one read-only owner
   observer. Capture lexical ancestry while live; do not read discarded parent
   builders after failure or create successful facts to explain a refusal.
3. Existing five negatives: generic_index_no_bound,
   generic_index_requires_nominal_bound, index_no_trait,
   index_requires_nominal_conformance, index_set_requires_nominal_conformance.
   Fixed carrier1b22eb22 yields13 intended Unclassified refusals in15modes;
   the2 undemanded generic ORC bodies correctly succeed and remain controls.
4. Positive generic_index_call_template, index_writeonly and operator_index
   pass exact ORC goldens. Add meaningfully distinct read/write, real nominal
   conformance versus same-named member, conditional/generic selection, and
   ordinary explicit index/indexSet method controls as needed. Preserve the
   deferred write-facet behavior instead of requiring IndexSet for a read.
5. Raw/owned, forged/foreign operation/session/owner, serial/selector/argument
   changes, missing selection records versus actual query failure, cached
   retry/drain, closure/global ancestry and required modes need assertions.
   Preserve dependency/Internal/Limit failures without catch-and-relabel.
6. TDD, independent review, final fresh candidate smoke, applicable native
   lifetime/LLVM22 ASanLSan, standard build/gen, normal reconciliation and
   fixed-point/median<=7.5s gates close this finite boundary.

## Excluded

Format/TextOutput synthetic requirements, general absent-selected-row guards,
other rejection domains, new indexing features, runtime/backend changes and
API-input audit scopes remain separate. No message-based classification and
no requirement to repair all290 remaining failures before this child closes.
Parent and phase-three closure remain separate.

## Investigation / RED

[Baseline and producer probe](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-index-requirement-investigation.json).
All5 actual file-input negatives reach the performed-query branch in
recordUnresolvedMethodTemplate (Record.pw1118), with nonzero receiver terms;
none reaches the later missing-published-selection guard (Record.pw2693).
The separate File-source probe uses the canonical standard-root separator.
Earlier malformed instrumentation / missing std-root separator are setup
failures, not RED or compiler findings. No product source repair is made yet.

## Independently reviewed implementation boundary

Reviewer typing_obligation_plan_review checked the contracts and actual probe /
baseline receipts (including213 compile inputs and16 frozen runtime inputs).
No specification change is needed. The following finite provenance repairs
are required before implementing the owned failure:

- Read: lowerIndexRead is public and emits AccessCandidate+SyntheticCallSite.
  Those alone cannot distinguish a raw builder from authored syntax. Issue a
  private read receipt only at the two actual source-Lower entrances, without
  changing the public builder signature or giving it source authority.
- Write: retainAssignmentIndexWrites is private and excludes detached facets,
  but its current serial/receiver/ArgRange receipt lacks the original selector
  and argument contents. Retain and compare selector plus each argument's
  expression/label/inout correspondence before minting a failure event.
- Keep the real performed-query negative, canonical protocol identity,
  receiver term, operation receipt, session/owner/root, serial/selector/args and
  location. Validate ancestry while live; failed closure builders are not a
  later ancestry service. Observation validates saved evidence and persistent
  ownership without lookup or a second missing-conformance decision.
- Pay the storage cost only at real Index Lower operations and on failure;
  add no general expression/method lookup or observer re-search.

This review admits the finite plan, not an implementation or closure. Current
product source remains5f12e9a1; only tickets and evidence changed in this step.
