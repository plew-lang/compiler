---
id: com-o7ul
status: closed
deps: []
links: []
created: 2026-10-24T13:22:40Z
type: bug
priority: 1
assignee: Koji Murata
parent: com-9tau
tags: [mid, frontend, verification]
---
# Materialize diverging calls from their frozen ABI result contract

## Boundary and Evidence

Required finite E3 Mid-consumer repair, independently reviewed by
/root/body_receiver_completion_review, about1–2 active human days. Production
856d661c direct-field isolate fails verify:type-mismatch: diagnostic Unit term3726
versus final call result0. Field projection is absent in this isolate. Meta
phase3e-callable-boundary-before.json retains exact evidence.

## Action

recordDynamicCallTemplate stores InvocationCompletion.Diverges and NoNormalValue,
and may retain a nonzero diagnostic Unit term. selectDynamicTemplateCall correctly
stores ABI result0. materializeMidCallValue currently interprets that term as a
normal Unit destination; canonicalMidTerminatorTypesMatch correctly rejects it.
Consume frozen invocation/result recipe to form the actual call destination,
separating divergence from a normal Unit result. Preserve diagnostic source facts,
argument evaluation/cleanup, continuation Unreachable and strict type verification.
No term-zero blanket requirement, Never type or permissive verifier change.

## Exit

Direct local/field diverging invocation and original associated storage panic
reach exact expected abort; merely storing them still continues. Normal Unit and
ordinary typed dynamic call controls execute; value-position and conversion
rejections remain. Pair com-px0e for original associated path. Fresh sourcecheck,
fixed point, median below7s and independent completion review. E3/G1/E4 depend on
this repair; full final candidate suites remain G2.

## Current Repair Refinement

Initial c9a2319a separates diagnostic Unit from a diverging call destination but
fresh2 exposed the next representation mismatch in existing diverging_call_flow.
The reserved result local stayed untyped because materializeMidCallValue returned
NoContinuation after callee Unreachable, before committing its recipe. Source
selection controls passed; this is not an incorrect surface test.

771150e1 makes the lowering result explicit: buildMidCallEvaluation returns
Ok(true) only at its two actual Call/NormalizedCall emission sites, Ok(false)
when input evaluation cannot continue, and Err for construction failure.
buildMidCallInto preserves that result while applying saved callee divergence.
The result local receives its recipe on actual emission even if the callee never
returns; only normal continuation enters the call-result cache. Additional
invocation lookup is limited to potential normal-Unit calls. Source facts and
strict type verification remain unchanged. Independently reviewed by
/root/body_receiver_completion_review. New mid_call_reached_completion covers
normal and inout input loops plus a returning argument of a diverging callee.
Current-source embedded preparation is a preflight; native/panic execution and
formal measurements remain required.

## Outcome

materializeMidCallValue separates saved diverging invocation from normal Unit and consumes the frozen result recipe. buildMidCallEvaluation returns true only at actual Call/NormalizedCall emission, false for input noncontinuation and Err for failure. Actual call emission commits the reserved local recipe even when the callee closes continuation; only normal continuation enters the result cache. Source diagnostic Unit facts and strict verifier remain unchanged. Direct and associated local/field panic, normal Unit and callee/input noncontinuation controls pass.

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
