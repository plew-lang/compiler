---
id: com-o7ul
status: in_progress
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
