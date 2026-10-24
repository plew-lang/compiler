---
id: com-fbqh
status: closed
deps: []
links: []
created: 2026-10-24T12:54:50Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-9tau
tags: [frontend, ownership, backend, verification]
---
# Close projected aggregate fields before publishing destruction shapes


## Boundary and Evidence

Required finite repair discovered during E3, parent criteria2/3/5/6/8. Intended
active human effort1–2 days. Independently reviewed by
`/root/body_receiver_completion_review`, with producer findings from
`/root/associated_context_completion_review`. Existing admitted source behavior;
no new callable, associated-type or ownership feature.

At production041b451e / controls40320a47, a Holder field typed
Contract#CallableStorage.Callback causes finalized-type physical representation
failure. The same field using associated normal fn()→I64 or I64 fails; making
only the field's type explicit diverge fn() succeeds. Ordinary source error,
not an incorrect test setup. The decisive source and5-case isolation are kept
in meta phase3e-projected-field-before.json. E3's remaining initial cases were
not run after the first compile failure and are not claimed as successes.

## Entry and Action

- Codegen/Mono/Ownership.closedDestructionShape is the shared producer for
  closedDestructionDependencies and collectFinalDestruction. Its current
  groundTermInEnvironment substitution leaves associated projections in fields.
  FinalDestruction then sends them to Backend/Llvm/GenericStruct and llvmTypeOfRef.
- Make shape closure fallible. Ground through explicit declaration ParamId→args
  and Self/receiver environment and close projections using the existing canonical
  groundTermForBody/closeBodyProjectionTerms authority. Preserve the fast path
  for terms without projections. Treat struct/enum payloads, structural fields
  and newtype underlying storage consistently at this contract boundary.
- Normalization may return an unchanged unresolved projection as Ok. Check
  final field/underlying closedness before publication; propagate failures rather
  than classifying a projection as Scalar or retrying source/name inference.
- Complete the newly fallible shape before registering collectFinalDestruction's
  placeholder, avoiding an indexed partial row caused solely by shape failure.
  Preserve existing recursive dependency worklist behavior; general rollback is
  not silently included.
- Propagate Result through the2 production consumers and the existing internal
  DestructionShape probe, preserving its original no-executable-body/no-layout
  side-effect intent and successful finalized-contract comparisons. No private
  API exposure, LLVM normalization, permissive fallback or verifier weakening.
- Reconcile source field/aggregate slot readers against the same final contract;
  do not assert the shape producer alone suffices until actual Mid/native tests
  pass. A further independent boundary repair must be separately bounded if found.

## Exit

- Original diverging_callable_storage run/panic path passes unchanged; stored
  callable values continue normally, actual field invocation reaches expected
  SIGABRT/panic. Existing E3 normal/reject/callable identity controls pass.
- Numeric associated struct/enum and generic field controls pass; unresolved
  projection query fails before final-contract publication, with no body/instance/
  layout/final-row side effects for the failed shape.
- Internal DestructionShape probe keeps no-body/no-layout and exact field/boxing/
  variant/deinit comparison. Appropriate existing recursive/newtype/heap-field
  ownership cases and E1/E2 controls pass on fresh compiler; register a newly
  exercised ownership path for final ASan E where applicable.
- Fresh whole sourcecheck, generation fixed point and formal median below7s;
  target failure is retained and investigated under the goal stop conditions.
- Independent completion review, producer→saved contract→actual consumer evidence,
  synchronized design/E3/E4/G1/worklog. Full final-candidate suites remain G2.

E3/G1/E4 require this repair; it does not depend on its unfinished parent.

## Outcome

closedDestructionShape now returns Result, closes associated nominal fields under explicit instance substitutions and rejects remaining open fields before publication. Both dependency queries and final destruction use it. Shape failure precedes placeholder insertion; query controls show no body/instance/layout/final-row side effects. Numeric struct/enum, generic I64/String receiver projections, heap ownership and original callable storage pass. Newtype underlying stays under its existing shared ARC/unique identity contract. Internal probe includes every published final contract; only incomplete declaration heads are excluded.

Independent completion admission by /root/body_receiver_completion_review:
production771150e1, contracts6e119a73. Meta evidence source-owner-facts/
phase3e-callable-authority.json records fresh35 normal/4 panic/21 reject, two
DestructionShape inputs, whole sourcecheck and standard build success. Inputs
305/190 match current source. phase3e-callable-authority-self-host.json records
generation2 LLVM/runtime fixed point;7.467912/6.978049/6.943662s, median6.978049s
(<7), exit0,5926 unchanged formal inputs and matching measured/saved compiler
SHA b2f2c229f04b738de42541b31ef440921043d92efde8c3baeca0bdd991e35168.
The functional compiler's separate identity remains explicit in the receipt.
E4's missing saved source exit identities are separately required work; no E4,
G2, main, seed or adopted-carrier completion follows from this admission.
