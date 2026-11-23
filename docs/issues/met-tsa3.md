---
id: met-tsa3
status: open
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

The active goal's stop condition for a missing/incorrect task is reached.
Record the concrete repair and dependency, then obtain user confirmation of
this added work/order before implementation. met-ia2q's refusal/provenance WIP
is unvalidated and must not be promoted or used to claim repair of this defect.

## Independent finding / ownership review

Reviewer typing_obligation_plan_review confirms the normative violation,
source-selection ownership, distinct scope from the two existing audit tasks,
and selection-before-transport dependency. Carrier/source/output hashes were
cross-checked, including saved AOT reruns equal to both original AOT hashes.
The existing genuine existential dispatch path is separately successful and
must not be disabled indiscriminately. No repair/WIP acceptance is claimed.
