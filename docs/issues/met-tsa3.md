---
id: met-tsa3
status: closed
deps: []
links: []
created: 2026-11-23T16:21:34Z
type: bug
priority: 1
assignee: Koji Murata
parent: met-ucze
tags: [frontend, verification, diagnostics]
---
# Preserve canonical protocol requirements through dynamic call fallback


## Confirmed violation and contract

[Executed reproduction](../../../evidence/rejection-domains/diagnostic-domain-implementation/phase3-index-dynamic-fallback-bypass.json)
uses adopted compiler1b22eb22: check/AOT/ORC all accept a Shelf that has an
`index` closure field but no Index conformance; ORC prints7. An otherwise
identical ordinary `shelf.index(key: 7I64)` control also passes all3 modes and
must stay valid. Spec12 requires Index conformance for subscript syntax;
ordinary field invocation is not nominal protocol evidence.

Record's static/member query receives requiredTraitOwner, but
recordDynamicMethodCallWithOrigin takes no such requirement and accepts an
ordinary same-named ClosureField. The generated Index call can therefore
publish a successful dynamic target after nominal protocol selection failed.
This is a source-selection defect, not rejection-domain transport.

## Finite work and guarantees

- Carry the source call's canonical requirement through the shared dynamic
  selection boundary. No ordinary closure-field fallback may satisfy a
  synthetic protocol requirement merely by name/signature.
- Preserve ordinary explicit function-field calls and supported genuine
  existential protocol dispatch (including justified inherited requirements).
  Do not blanket-disable dynamic protocol calls or add a field/name exception.
- Inspect the actual shared IndexRead/IndexWrite/Format/TextWrite routes for
  the same lost requirement. Classify unverified routes and retain meaningful
  positive/negative controls; implementing new protocols/existential features
  is excluded. Keep supported canonical proof and selected identity through
  publication/final consumers instead of checking nominality only in LLVM.
- Cover direct/conditional/generic requirements, closure-field false friends,
  ordinary field-call controls and applicable existing dynamic/interface calls.
  Preserve source evaluation/ownership/order and original dependency failures.
- Establish RED with the fixed carrier, implement in the responsible shared
  selector/request, remove the competing unqualified fallback, and run scoped
  source-to-final-use controls, independent review and applicable final gates.

## Ownership and order

Parent met-ucze owns source member selection; met-ia2q depends on this repair
before finite index refusal closure. com-p8xt narrows API inputs and com-l4x2
checks function-value signatures; neither currently specifies this protocol
role leak. The new ticket is a newly confirmed phase-three gap, not a claim that
those tasks or existing valid evidence should all be reopened.

User approved this added repair before met-ia2q and delegated routine task
creation, corrections and ordering. Proceed under existing semantics/design;
new language-surface decisions still require consultation. met-ia2q WIP is not
an adopted candidate; keep its evidence separate until validated.

## Independent finding / ownership review

Reviewer typing_obligation_plan_review confirms the normative violation,
source-selection ownership, distinct scope from the two existing audit tasks,
and selection-before-transport dependency. Carrier/source/output hashes were
cross-checked, including saved AOT reruns equal to both original AOT hashes.
The existing genuine existential dispatch path is separately successful and
must not be disabled indiscriminately. No repair/WIP acceptance is claimed.

## Construction-query boundary and current evidence

Independent source review also found the same lost canonical requirement in
unfinished result construction (`exprTypeWithChainHole`): symbolic-bound/static
selection, existential requirement slots, ChainHole continuation and closure-field
return fallback. Propagate the same demand through these queries; an ineligible
field or unrelated trait must not supply a result type before final recording.
This is part of this finite repair, not a new inference/Index feature.

Scoped RED v2 (fixed adopted1b22eb22) has21 mode controls:9 invalid operations
are actually accepted (field read/write and unrelated existential);3 generic
wrong-bound operations are already rejected but Unclassified;9 positive controls
pass (ordinary field/interface calls, direct anyIndex, generic inheritedIndex).
Do not describe all12 assertion failures as erroneous acceptance.

Intermediate frozen v2 build20261123T164333-build-02336a passed; its21 mode
controls pass, including Source transport supplied by unadopted met-ia2q WIP.
This candidate predates the construction-query correction and is not final
adoption evidence. Final source/gates are recorded below. Direct inherited-anyTaggedIndex
was already unsupported by the adopted carrier and is not implemented here;
generic inheritedIndex is supported and retained as a positive fixture.


Final v4 build5ae294 and39 combined CLI controls pass. Measured fixed-point
compiler0655bae5 passes the same39 controls with compiler/tool/fixture hash
invariance recorded. Shared Format/TextOutput36 old/new controls and gen-eacb2f
pass. Formal341b9f reachesG2 and median7.329713s (ceiling7.5s); final ordinary
suite f44c09 and independent acceptance are pending. Pre-existing inherited
existential refusal is separately assigned to met-ajht under the same area;
it is not a repaired-feature claim for this task.


## Accepted finite outcome

Independent reviewer typing_obligation_plan_review accepts closure against
product26974e78 and tests708ca1cc/a7b73266. Final build5ae294,39 measured-carrier
CLI controls, native28/consumer25, LLVM22 ASan24/consumer, gen-eacb2f and formal
341b9f (G2, median7.329713s<=7.5s) establish the bounded guarantees.
Normal6d65db completed exit1 with immutable inputs, no worker failure and7655
paired workers. Its290 baseline becomes285: only the targeted5 refusals resolve,
no added failures/reason changes,3 registered CLI gates pass. Nine fixture files
are byte-identical; the pre-existing absent generic_index_no_bound.err remains
absent and its diagnostic is asserted by the scoped CLI. No golden was weakened.

The reviewer independently checked source, assertions, saved execution and actual
input/artifact hashes; this is not a second independent full-suite execution.
The ENOSPC predecessor is excluded. met-ajht, met-ucze/com-yeua and remaining285
failures stay open. No main/seed/binary promotion. See combined finite evidence
and phase3-post-index-normal-suite.json in the evidence directory.
